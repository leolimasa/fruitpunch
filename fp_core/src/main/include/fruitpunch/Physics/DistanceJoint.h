/*
 * DistanceJoint.h
 *
 *  Created on: Sep 9, 2012
 *      Author: leo
 */

#ifndef DISTANCEJOINT_H_
#define DISTANCEJOINT_H_

#include <fruitpunch/Physics/PhysicsJoint.h>
#include <boost/shared_ptr.hpp>
#include <Box2D/Box2D.h>
#include <fruitpunch/Elements/Element.h>

namespace fp_core {
namespace physics {

//class Element;

class DistanceJoint : public PhysicsJoint {
public:
	typedef boost::shared_ptr<DistanceJoint> ref;

	DistanceJoint();
	DistanceJoint(boost::shared_ptr<Element> elementA,
    		boost::shared_ptr<Element> elementB);
    virtual ~DistanceJoint();
    virtual boost::shared_ptr<b2JointDef> create();
};

} /* namespace fp_core */
} /* namespace fp_core::physics */
#endif /* DISTANCEJOINT_H_ */
