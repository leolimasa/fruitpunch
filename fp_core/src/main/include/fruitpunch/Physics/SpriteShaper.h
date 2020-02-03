/*
 * SpriteShaper.h
 *
 *  Created on: Sep 9, 2012
 *      Author: leo
 */

#ifndef SPRITESHAPER_H_
#define SPRITESHAPER_H

#include <fruitpunch/Physics/Shaper.h>

namespace fp_core {
namespace physics {

/// Shaper to generate PhysicalShapes for Sprite elements
class SpriteShaper : public Shaper {
public:
    SpriteShaper();
    virtual ~SpriteShaper();

    /// True if Element is an instance of Primitive. False otherwise.
    virtual bool test(boost::shared_ptr<Element> element);

    /// Creates a PhyisicsBox with the width and height of the sprite and returns it.
    virtual boost::shared_ptr<PhysicsShape> make(boost::shared_ptr<Element> element, boost::shared_ptr<PhysicsWorld> world);
};

} /* namespace physics */
} /* namespace fp_core */
#endif /* SPRITESHAPER_H_ */
