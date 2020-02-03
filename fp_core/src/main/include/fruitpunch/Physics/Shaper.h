/*
 * Shaper.h
 *
 *  Created on: Sep 9, 2012
 *      Author: leo
 */

#ifndef SHAPER_H_
#define SHAPER_H_

#include <boost/shared_ptr.hpp>
#include <Box2D/Box2D.h>

namespace fp_core {

class Element;

namespace physics {

class PhysicsWorld;
class PhysicsShape;

class Shaper {
public:
	typedef boost::shared_ptr<Shaper> ref;

    Shaper();
    virtual ~Shaper();

    virtual bool test(boost::shared_ptr<Element> element);
    virtual boost::shared_ptr<PhysicsShape> make(boost::shared_ptr<Element> element, boost::shared_ptr<PhysicsWorld> world);
};

} /* namespace physics */
} /* namespace fp_core */
#endif /* SHAPER_H_ */
