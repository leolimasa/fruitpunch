/*
 * PhysicsShape.cpp
 *
 *  Created on: Sep 9, 2012
 *      Author: leo
 */

#include <fruitpunch/Physics/PhysicsShape.h>

namespace fp_core {
namespace physics {

PhysicsShape::PhysicsShape() {
    // TODO Auto-generated constructor stub

}

PhysicsShape::~PhysicsShape() {
    // TODO Auto-generated destructor stub
}

boost::shared_ptr<b2Shape> PhysicsShape::getBox2dShape(float scale) {
	return boost::shared_ptr<b2Shape>();
}

} /* namespace physics */
} /* namespace fp_core */
