/*
 * Observable.cpp
 *
 *  Created on: 2012-02-29
 *      Author: leo
 */

#include <boost/shared_ptr.hpp>
#include <fruitpunch/Common/Observable.h>
#include <fruitpunch/Common/Observer.h>
#include <fruitpunch/Common/Event.h>

using namespace std;

namespace fp_core {
namespace common {

Observable::Observable() : Object() {
  // TODO Auto-generated constructor stub

}

// ____________________________________________________________________________

Observable::~Observable() {
  // TODO Auto-generated destructor stub
}

// ____________________________________________________________________________

void Observable::attachObserver(std::string event, boost::shared_ptr<Observer> observer) {
  observer->setInstance(getThis<Observable>());
  observer->setEventName(event);
  mObserver.push_back(observer);
}

// ____________________________________________________________________________

void Observable::detachObserver(boost::shared_ptr<Observer> observer) {
  mObserver.remove(observer);
}

// ____________________________________________________________________________

void Observable::notify(Event::ref event) {
  if (mObserver.empty()) {
	  return;
  }

  list<boost::shared_ptr<Observer> >::iterator it;
 // int s = mObserver.size();
  for (it = mObserver.begin(); it != mObserver.end(); it++) {
    Observer& o = **it;
    if (o.getEventName().compare(event->getName()) == 0) {
      o.setEvent(event);
      o.action();
    }
  }
}

// ____________________________________________________________________________

void Observable::removeAllObservers() {
  mObserver.clear();
}

} /* namespace common */
} /* namespace fp_core */
