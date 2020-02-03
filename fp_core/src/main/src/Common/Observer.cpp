/*
 * Observer.cpp
 *
 *  Created on: 2012-02-29
 *      Author: leo
 */

#include <boost/shared_ptr.hpp>
#include <fruitpunch/Common/Observer.h>
#include <fruitpunch/Common/Observable.h>

namespace fp_core {
namespace common {

Observer::Observer() : Object() {
	// TODO Auto-generated constructor stub

}

Observer::~Observer() {
	// TODO Auto-generated destructor stub
}

std::string Observer::getEventName() {
  return mEventName;
}

void Observer::setEventName(std::string event) {
  mEventName = event;
}

Observable::Ptr Observer::getInstance() const {
  return mInstance;
}

boost::shared_ptr<Event> Observer::getEvent() const {
	return mEvent;
}

void Observer::setEvent(boost::shared_ptr<Event> event) {
	mEvent = event;
}

void Observer::setInstance(Observable::Ptr instance) {
  mInstance = instance;
}

} /* namespace common */
} /* namespace fp_core */
