/*
 * ContactEvent.h
 *
 *  Created on: Sep 9, 2012
 *      Author: leo
 */

#ifndef CONTACTEVENT_H_
#define CONTACTEVENT_H_

#include <fruitpunch/Common/Event.h>
#include <Box2D/Box2D.h>

namespace fp_core {

class Element;

namespace physics {

class PhysicsWorld;

/// Event thrown when two physics bodies contact each other.
class ContactEvent : public fp_core::common::Event {
public:
	typedef boost::shared_ptr<ContactEvent> ref;

	ContactEvent();
    ContactEvent(b2Contact& contact, std::string name, boost::shared_ptr<PhysicsWorld> world);
    virtual ~ContactEvent();

	boost::shared_ptr<Element> getElementA();
	void setElementA(boost::shared_ptr<Element> elementA);
	boost::shared_ptr<Element> getElementB();
	void setElementB(boost::shared_ptr<Element> elementB);

private:
    boost::shared_ptr<Element> mElementA;
    boost::shared_ptr<Element> mElementB;
};

} /* namespace physics */
} /* namespace fp_core */
#endif /* CONTACTEVENT_H_ */
