#include <FpCoreTest.h>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <fruitpunch/Common/Observable.h>
#include <fruitpunch/Common/Observer.h>
#include <fruitpunch/Common/Event.h>

using namespace std;
using namespace boost;
using namespace fp_core;
using namespace fp_core::common;

class MockObserver : public Observer {
	bool triggered;

	void action() {
		triggered = true;
	}
};

// ---------------------------------------------------------------------------
// Test Class
// ---------------------------------------------------------------------------

class ObservableTest : public FpCoreTest {
protected:

  virtual void SetUp() {
    initEnvironment();
  }

};

TEST_F(ObservableTest, notify) {
	boost::shared_ptr<Observable> observable(new Observable());
	boost::shared_ptr<Observer> mockobs(new MockObserver());

	observable->attachObserver("my_event", mockobs);
	observable->notify(Event::ref(new Event("my_event")));

	ASSERT_EQ("my_event", mockobs->getEvent()->getName());
}

/**
 * Checks if notify will still work when there are no observers registered.
 * This will most likely segfault if it fails.
 */
TEST_F(ObservableTest, emptyObserver) {
	boost::shared_ptr<Observable> observable(new Observable());
	observable->notify(Event::ref(new Event("my_event")));
	ASSERT_TRUE(true);
}
