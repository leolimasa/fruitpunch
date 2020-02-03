/*
 * Event.h
 *
 *  Created on: Sep 9, 2012
 *      Author: leo
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <string>
#include <boost/shared_ptr.hpp>
#include <fruitpunch/Common/Object.h>

namespace fp_core {
namespace common {

/// An event fired by the notify() method of the observable
/**
 * Will be eventually passed to the observer.  This base class implements just
 * a member variable to store the event name, with its getters and setters,
 * but can be extended to form other types of events.
 */
class Event : public Object {
public:
	typedef boost::shared_ptr<Event> ref;

    Event(std::string name);
    virtual ~Event();

    const std::string getName() const;
    void setName(const std::string name);

private:
    std::string mName;
};

} /* namespace common */
} /* namespace fp_core */
#endif /* EVENT_H_ */
