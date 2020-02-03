#include <FpCoreTest.h>

#include <fruitpunch/Graphics/Window.h>
#include <fruitpunch/Graphics/Primitive.h>
#include <fruitpunch/Graphics/Renderer.h> // may or may not need this...

#include <fruitpunch/Common/Observable.h>
#include <fruitpunch/Common/Events.h>
#include <fruitpunch/Common/Runtime.h>
#include <fruitpunch/Common/Observer.h>

#include <boost/shared_ptr.hpp>
#include <boost/date_time.hpp>
#include <gtest/gtest.h>

using namespace fp_core;
using namespace boost;
using namespace fp_core::common;

class WindowObserver: public Observer {

public:
    double totalFramesRendered;

    void action() {
        totalFramesRendered++;
    }
    double getTotalFramesRendered() {
        return totalFramesRendered;
    }
    void reset() {
        totalFramesRendered = 0;
    }
};


// ---------------------------------------------------------------------------
// Test Class
// ---------------------------------------------------------------------------

class WindowTest: public FpCoreTest {
public:
	  int framesToAttempt;
	  double start, finish, seconds, fps;

protected:
    virtual void SetUp() {
    	initEnvironment();
    	framesToAttempt = 10;
    }
};

// ---------------------------------------------------------------------------
// Test Cases
// ---------------------------------------------------------------------------


TEST_F(WindowTest, removePrimitive) {
    boost::shared_ptr<Primitive> p(new Primitive());

    Window w;
    w.addPrimitive(p);

    ASSERT_EQ(1, w.getPrimitives().size());
    ASSERT_EQ(p.get(), w.getPrimitives()[0].get());

    boost::shared_ptr<Primitive> copy = p;

    w.removePrimitive(copy);

    ASSERT_EQ(0, w.getPrimitives().size());
}


TEST_F(WindowTest, DefaultFps) {
    initEnvironment();
    boost::shared_ptr<WindowObserver> obs(new WindowObserver());
    boost::shared_ptr<Window> w = Runtime::getCurrent()->getWindow();

    w->attachObserver(EV_POST_RENDER, obs);

    ASSERT_EQ(w->getFps(), 60);

    start = Runtime::getTimeInMs();

    obs->reset();
    while (obs->getTotalFramesRendered() < framesToAttempt) {
        w->renderFrame();
    }

	finish = Runtime::getTimeInMs();

	ASSERT_GE(obs->getTotalFramesRendered(), 1);

	ASSERT_LE(obs->getTotalFramesRendered()/((finish - start) / 1000.0), 66);
	ASSERT_GE(obs->getTotalFramesRendered()/((finish - start) / 1000.0), 55);
}

TEST_F(WindowTest, setFps) {
    initEnvironment();
    boost::shared_ptr<WindowObserver> obs(new WindowObserver());
    boost::shared_ptr<Window> w = Runtime::getCurrent()->getWindow();
    w->attachObserver(EV_POST_RENDER, obs);
    w->setFps(30);
    ASSERT_EQ(w->getFps(), 30);

    // make sure the value is right...
    start = Runtime::getTimeInMs();

    while (obs->getTotalFramesRendered() < framesToAttempt) {
        w->renderFrame();
    }

    finish = Runtime::getTimeInMs();

    double total = obs->getTotalFramesRendered();
    double difference = finish - start;
    float t = (float) total / (difference / 1000);
    printf("%f, %f, %f", total, difference, t);

    ASSERT_LE(t, 33);
    ASSERT_GE(t, 28.0f);

    obs->reset();
    w->setFps(45);
    ASSERT_EQ(w->getFps(), 45);
    start = Runtime::getTimeInMs();

    while (obs->getTotalFramesRendered() < framesToAttempt) {
        w->renderFrame();
    }

    finish = Runtime::getTimeInMs();

    ASSERT_LE(obs->getTotalFramesRendered()/(((finish - start)) / 1000.0), 48);
    ASSERT_GE(obs->getTotalFramesRendered()/(((finish - start)) / 1000.0), 41);

    obs->reset();
    w->setFps(90);
    ASSERT_EQ(w->getFps(), 90);
    start = Runtime::getTimeInMs();

    while (obs->getTotalFramesRendered() < framesToAttempt) {
            w->renderFrame();
    }

    finish = Runtime::getTimeInMs();

    ASSERT_LE(obs->getTotalFramesRendered()/(((finish - start)) / 1000.0), 99);
    ASSERT_GE(obs->getTotalFramesRendered()/(((finish - start)) / 1000.0), 80);

}


