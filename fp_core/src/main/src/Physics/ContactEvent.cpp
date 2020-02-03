/*
 * ContactEvent.cpp
 *
 *  Created on: Sep 9, 2012
 *      Author: leo
 */

#include <fruitpunch/Physics/ContactEvent.h>
#include <boost/shared_ptr.hpp>
#include <fruitpunch/Elements/Element.h>
#include <fruitpunch/Physics/PhysicsWorld.h>
#include <cstdio>

using namespace fp_core;

namespace fp_core {
namespace physics {

ContactEvent::ContactEvent(b2Contact& contact, std::string name, boost::shared_ptr<PhysicsWorld> world) : Event(name) {
	mElementA = world->getElementFromFixture(contact.GetFixtureA());
	mElementB = world->getElementFromFixture(contact.GetFixtureB());

	if (!mElementA) {
		printf("ERROR: contact.GetFixtureA on ContactEvent has returned NULL.\n");
		printf("ContactEvent has not been created properly.");
		return;
	}

	if (!mElementB) {
		printf("ERROR: contact.GetFixtureB on ContactEvent has returned NULL. Stopping.");
		printf("ContactEvent has not been created properly.");
		return;
	}
}

ContactEvent::~ContactEvent() {
    // TODO Auto-generated destructor stub
}

boost::shared_ptr<Element> ContactEvent::getElementA() {
	return mElementA;
}

void ContactEvent::setElementA(boost::shared_ptr<Element> elementA) {
	mElementA = elementA;
}

boost::shared_ptr<Element> ContactEvent::getElementB() {
	return mElementB;
}

ContactEvent::ContactEvent() : Event("undefined") {
}

void ContactEvent::setElementB(boost::shared_ptr<Element> elementB) {
	mElementB = elementB;
}

} /* namespace physics */
} /* namespace fp_core */
