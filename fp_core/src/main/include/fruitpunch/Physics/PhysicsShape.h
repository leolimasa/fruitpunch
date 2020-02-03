/*
 * PhysicsShape.h
 *
 *  Created on: Sep 9, 2012
 *      Author: leo
 */

#ifndef PHYSICSSHAPE_H_
#define PHYSICSSHAPE_H_

#include <Box2D/Box2D.h>
#include <boost/shared_ptr.hpp>

namespace fp_core {
namespace physics {

/// Abstract class that wraps a b2Shape
class PhysicsShape {
public:
	typedef boost::shared_ptr<PhysicsShape> ref;

    PhysicsShape();
    virtual ~PhysicsShape();

    virtual boost::shared_ptr<b2Shape> getBox2dShape(float scale);
};

} /* namespace physics */
} /* namespace fp_core */
#endif /* PHYSICSSHAPE_H_ */
