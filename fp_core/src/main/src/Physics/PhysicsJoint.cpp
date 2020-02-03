/*
 * PhysicsJoint.cpp
 *
 *  Created on: Sep 9, 2012
 *      Author: leo
 */

#include <fruitpunch/Physics/PhysicsJoint.h>
#include <fruitpunch/Errors/InvalidChildrenError.h>
#include <fruitpunch/Errors/InvalidParentError.h>
#include <fruitpunch/Physics/PhysicsWorld.h>
#include <fruitpunch/Common/Runtime.h>

using namespace std;

namespace fp_core {
namespace physics {

PhysicsJoint::PhysicsJoint(boost::shared_ptr<Element> elementA, boost::shared_ptr<Element> elementB) : Element() {
    mElementA = elementA;
    mElementB = elementB;
}

PhysicsJoint::~PhysicsJoint() {
    // TODO Auto-generated destructor stub
}

boost::shared_ptr<Body> getBody(boost::shared_ptr<Element> e) {
	boost::shared_ptr<Body> b;
	b = e->getChildOfType<Body>();

	if (b.get() != NULL) {
		return b;
	}
	else {
		Runtime::getCurrent()->addError(InvalidChildrenError::ref
		    (new InvalidChildrenError("PhysicsJoint", "Body")));
		return boost::shared_ptr<Body>(); // return NULL
	}
}

void PhysicsJoint::onAdd() {
	boost::shared_ptr<PhysicsWorld> pw = boost::dynamic_pointer_cast<PhysicsWorld>(getParent());

	if (pw) {
		mWorld = pw;
		getBody(mElementA);
		getBody(mElementB);
		boost::shared_ptr<b2JointDef> def = create();
		mB2Joint = mWorld->getWorld()->CreateJoint(def.get());
	}
	else {
		string reporting = typeid(*getParent()).name();
		Runtime::getCurrent()->addError(InvalidParentError::ref
		    (new InvalidParentError(reporting, "PhysicsWorld")));
	}
}

void PhysicsJoint::onRemove() {
	getWorld()->getWorld()->DestroyJoint(getB2Joint());
}

boost::shared_ptr<Body> PhysicsJoint::retrieveBodyA() {
	return getBody(mElementA);
}

boost::shared_ptr<Body> PhysicsJoint::retrieveBodyB() {
	return getBody(mElementB);
}

boost::shared_ptr<b2JointDef> PhysicsJoint::create() {
	return boost::shared_ptr<b2JointDef>();
}

PhysicsJoint::PhysicsJoint() {
}

const boost::shared_ptr<PhysicsWorld> PhysicsJoint::getWorld() const {
	return mWorld;
}

const boost::shared_ptr<Element> PhysicsJoint::getElementA() {
  return mElementA;
}

void PhysicsJoint::setElementA(const boost::shared_ptr<Element> elementA) {
  mElementA = elementA;
}

const boost::shared_ptr<Element> PhysicsJoint::getElementB() {
  return mElementB;
}

void PhysicsJoint::setElementB(const boost::shared_ptr<Element> elementB) {
  mElementB = elementB;
}

b2Joint* PhysicsJoint::getB2Joint() {
	return mB2Joint;
}

void PhysicsJoint::setB2Joint(b2Joint* newB2Joint) {
	mB2Joint = newB2Joint;
}

} // namespace fp_core
} // namespace physics
