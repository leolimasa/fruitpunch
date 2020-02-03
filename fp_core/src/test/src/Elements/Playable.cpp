#include <FpCoreTest.h>
#include <gtest/gtest.h>
#include <fruitpunch/Common/Observable.h>
#include <fruitpunch/Common/Observer.h>
#include <fruitpunch/Elements/Playable.h>
#include <boost/shared_ptr.hpp>
#include <fruitpunch/Common/Events.h>


using namespace fp_core;
using namespace boost;

// ---------------------------------------------------------------------------
// Stub Classes
// ---------------------------------------------------------------------------

class PlayableImpl : public Playable {
public:
  bool renderSingleCalled;
  int frameRendered;

  PlayableImpl() : Playable() {
    renderSingleCalled = false;
  }

  virtual void renderSingle(int frame) {
    renderSingleCalled = true;
    frameRendered = frame;
  }

  virtual int calculateDuration() {
    return 10;
  }
};

class DummyObserver : public Observer {
public:

	bool triggered;

	virtual void action() {
		triggered = true;
	}
};

// ---------------------------------------------------------------------------
// Test Class
// ---------------------------------------------------------------------------

class PlayableTest : public FpCoreTest {
protected:
  virtual void SetUp() {
	  initEnvironment();

  }
};

// ---------------------------------------------------------------------------
// Test Cases
// ---------------------------------------------------------------------------

/**
 * Tests methods that have simple test cases
 */
TEST_F(PlayableTest, SmallMethods) {
  PlayableImpl p;

  ASSERT_EQ(p.getCurrentFrame(), 0);

  p.start();
  ASSERT_TRUE(p.isPlaying());

  p.stop();
  ASSERT_FALSE(p.isPlaying());
}

TEST_F(PlayableTest, tick) {
  PlayableImpl p;

  p.tick();
  ASSERT_FALSE(p.renderSingleCalled);
  ASSERT_EQ(0, p.getCurrentFrame());

  p.start();
  p.tick();
  ASSERT_TRUE(p.renderSingleCalled);
  ASSERT_EQ(1, p.getCurrentFrame());

  p.setCurrentFrame(10);
  p.tick();
  ASSERT_EQ(p.getCurrentFrame(), 0);

  p.stop();
  ASSERT_FALSE(p.isPlaying());

  p.setCurrentFrame(10);
  p.start();
  p.setLoop(true);
  p.tick();
  ASSERT_EQ(p.getCurrentFrame(), 0);
  ASSERT_TRUE(p.isPlaying());
}

TEST_F(PlayableTest, getEndFrame) {
  PlayableImpl p;

  ASSERT_EQ(9, p.getEndFrame());

  p.setStartFrame(10);

  ASSERT_EQ(19, p.getEndFrame());
}

TEST_F(PlayableTest, frameEvents) {
	boost::shared_ptr<PlayableImpl> p(new PlayableImpl());
	boost::shared_ptr<DummyObserver> first(new DummyObserver());
	boost::shared_ptr<DummyObserver> last(new DummyObserver());
	first->triggered = false;
	last->triggered = false;


	p->attachObserver(EV_FIRST_FRAME, first);
	p->attachObserver(EV_LAST_FRAME, last);

	p->setStartFrame(10);
	p->start();

	p->setCurrentFrame(9);
	p->tick();
	ASSERT_FALSE(first->triggered);
	ASSERT_FALSE(last->triggered);

	p->setCurrentFrame(10);
	p->tick();
	ASSERT_TRUE(first->triggered);
	ASSERT_FALSE(last->triggered);
	first->triggered = false;

	p->setCurrentFrame(19);
	p->tick();
	ASSERT_FALSE(first->triggered);
	ASSERT_FALSE(last->triggered);

	p->setCurrentFrame(20);
	p->tick();
	ASSERT_FALSE(first->triggered);
	ASSERT_TRUE(last->triggered);
}

TEST_F(PlayableTest, startFrame) {
	boost::shared_ptr<PlayableImpl> p(new PlayableImpl());
	p->setStartFrame(3);
	p->start();

	p->tick();
	ASSERT_FALSE(p->renderSingleCalled);

	p->tick();
	ASSERT_FALSE(p->renderSingleCalled);

	p->tick();
	ASSERT_FALSE(p->renderSingleCalled);

	p->tick();
	ASSERT_TRUE(p->renderSingleCalled);
	ASSERT_EQ(0, p->frameRendered);


	// the end frame should not be the duration, but the sum of the duration
	// and the start frame
	p->setCurrentFrame(10);
	p->tick();
	ASSERT_EQ(11, p->getCurrentFrame());


	// if we go to a frame greater than the duration, and loop is enabled it
	// should go back to frame zero and keep going from there
	p->setCurrentFrame(14);
	p->setLoop(true);
	p->tick();
	ASSERT_EQ(0, p->getCurrentFrame());

	p->tick();
	ASSERT_EQ(1, p->getCurrentFrame());

	// assures it stops if loop is disabled
	p->setLoop(false);
	p->setCurrentFrame(14);
	p->tick();
	ASSERT_FALSE(p->isPlaying());
}
