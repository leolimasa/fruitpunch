/*
 * MouseJoint.cpp
 *
 * A mouse joint. Add more shit here later.
 *
 *  Created on: Nov 4, 2012
 *      Author: Steven
 */

#include <fruitpunch/Physics/MouseJoint.h>
#include <fruitpunch/Elements/Element.h>
#include <fruitpunch/Physics/PhysicsWorld.h>
#include <fruitpunch/Graphics/Transformable.h>
#include <math.h>
#include <vector>

using namespace std;

namespace fp_core {
namespace physics {

/* Creates a new b2MouseJoint with elementA, and elementB */
MouseJoint::MouseJoint(boost::shared_ptr<Element> elementA, boost::shared_ptr<Element> elementB) :
	PhysicsJoint(elementA, elementB){
}

MouseJoint::~MouseJoint() {
    // TODO Auto-generated destructor stub
}

MouseJoint::MouseJoint() : PhysicsJoint() {

}

// create this on mouseDown
boost::shared_ptr<b2JointDef> MouseJoint::create() {
	boost::shared_ptr<b2MouseJointDef> mjDef(new b2MouseJointDef);
	mjDef->bodyA = retrieveBodyA()->getBox2dBody(); // add a getGroundBody method soon
	mjDef->bodyB = retrieveBodyB()->getBox2dBody();

	mjDef->maxForce = 1000.0f * retrieveBodyB()->getBox2dBody()->GetMass();

	point b = retrieveBodyB()->getTransformable()->getPosition();
	b2Vec2 vector;
	vector.x = b.x / getWorld()->getPixelSize();
	vector.y = b.y / getWorld()->getPixelSize();

	mjDef->target =  vector;

	boost::shared_ptr<b2JointDef> jdef = boost::dynamic_pointer_cast<b2JointDef>(mjDef);

	return jdef;
}

// keep calling this from python as long as the mouse is still down...
void MouseJoint::update(point newLocation) {
	b2Vec2 newPosition;
	newPosition.x = newLocation.x / getWorld()->getPixelSize();
	newPosition.y = newLocation.y / getWorld()->getPixelSize();
	b2MouseJoint *mJ = (b2MouseJoint *) getB2Joint();
	mJ->SetTarget(newPosition);
}

} /* namespace phsyics */
} /* namespace fp_core*/
