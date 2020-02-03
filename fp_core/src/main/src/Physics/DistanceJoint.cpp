/*
 * DistanceJoint.cpp
 *
 * A joint that maintains two bodies at a constant distance.
 *
 *  Created on: Sep 9, 2012
 *      Author: leo
 */

#include <fruitpunch/Physics/DistanceJoint.h>
#include <fruitpunch/Elements/Element.h>
#include <fruitpunch/Physics/PhysicsWorld.h>
#include <fruitpunch/Graphics/Transformable.h>
#include <math.h>

using namespace std;

namespace fp_core {
namespace physics {


/* Creates a new b2DistanceJoint with bodyA and bodyB
 * and then initializes the joint */
DistanceJoint::DistanceJoint(boost::shared_ptr<Element> elementA, boost::shared_ptr<Element> elementB) :
		PhysicsJoint(elementA, elementB) {
}

DistanceJoint::~DistanceJoint() {
    // TODO Auto-generated destructor stub
}

DistanceJoint::DistanceJoint() : PhysicsJoint() {
}

boost::shared_ptr<b2JointDef> DistanceJoint::create() {
	boost::shared_ptr<b2DistanceJointDef> djDef(new b2DistanceJointDef);

	point a = retrieveBodyA()->getTransformable()->getPosition();
	point b = retrieveBodyB()->getTransformable()->getPosition();

	float l = sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));

	djDef->length = l / getWorld()->getPixelSize();
	djDef->bodyA = retrieveBodyA()->getBox2dBody();
	djDef->bodyB = retrieveBodyB()->getBox2dBody();
    boost::shared_ptr<b2JointDef> jdef = boost::dynamic_pointer_cast<b2JointDef>(djDef);
    getWorld()->getWorld()->CreateJoint(djDef.get());
	return jdef;
}

} /* namespace physics */
} /* namespace fp_core */
