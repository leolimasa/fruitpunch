/*
 * Shaper.cpp
 *
 *  Created on: Sep 9, 2012
 *      Author: leo
 */

#include <fruitpunch/Physics/Shaper.h>

namespace fp_core {
namespace physics {

Shaper::Shaper() {
    // TODO Auto-generated constructor stub

}

Shaper::~Shaper() {
    // TODO Auto-generated destructor stub
}


bool Shaper::test(boost::shared_ptr<Element> element) {
	return false;
}

boost::shared_ptr<PhysicsShape> Shaper::make(
		boost::shared_ptr<Element> element,
		boost::shared_ptr<PhysicsWorld> world) {
			return boost::shared_ptr<PhysicsShape>();
}

} /* namespace physics */
} /* namespace fp_core */
