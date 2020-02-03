#include <FpCoreTest.h>
#include <gtest/gtest.h>
#include <fruitpunch/Common/Runtime.h>
#include <fruitpunch/Errors/ErrorCodes.h>
#include <fruitpunch/Common/Events.h>
#include <fruitpunch/Common/Observer.h>
#include <fruitpunch/Common/Event.h>
#include <boost/make_shared.hpp>
#include <vector>

using namespace fp_core;
using namespace std;
using namespace boost;
using namespace fp_core::common;


class RuntimeTest : public FpCoreTest {
protected:
  virtual void SetUp() {
	  initEnvironment();
  }
};

class TickObserver : public Observer {
public:
	vector<long> times;

	void action() {
		times.push_back(Runtime::getTimeInMs());
	}
};

TEST_F(RuntimeTest, tick) {

	boost::shared_ptr<TickObserver> obs = boost::make_shared<TickObserver>();
	Runtime::getCurrent()->attachObserver(EV_TICK, obs);

	for (int i=0; i<1000; i++) {
		Runtime::getCurrent()->renderFrame();
	}

	// make sure we have at least 3 results for measurement.
	ASSERT_GT(obs->times.size(), 2);

	// check that all captured times are at least 1 ms appart
	vector<long>::iterator it = obs->times.begin();
	long lastTime = 0;
	for (; it != obs->times.end(); it++) {
		ASSERT_GT(*it - lastTime, 1);
		lastTime = *it;
	}

}

TEST_F(RuntimeTest, notify) {
	Runtime::getCurrent()->notify(boost::make_shared<Event>(EV_TICK));
}
