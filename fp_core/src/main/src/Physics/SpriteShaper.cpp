/*
 * SpriteShaper.cpp
 *
 *  Created on: Sep 9, 2012
 *      Author: leo
 */

#include <fruitpunch/Physics/SpriteShaper.h>
#include <fruitpunch/Physics/PhysicsBox.h>
#include <fruitpunch/Physics/PhysicsWorld.h>
#include <fruitpunch/Graphics/Sprite.h>


namespace fp_core {
namespace physics {

SpriteShaper::SpriteShaper() : Shaper() {
    // TODO Auto-generated constructor stub

}

SpriteShaper::~SpriteShaper() {
    // TODO Auto-generated destructor stub
}

bool SpriteShaper::test(boost::shared_ptr<Element> element) {
	Sprite * sp = dynamic_cast<Sprite *>(element.get());
	return sp != NULL;
}

boost::shared_ptr<PhysicsShape> SpriteShaper::make(
		boost::shared_ptr<Element> element,
		boost::shared_ptr<PhysicsWorld> world) {
	boost::shared_ptr<Sprite> sprite = boost::static_pointer_cast<Sprite>(element);
	float w = sprite->getWidth() / world->getPixelSize();
	float h = sprite->getHeight() / world->getPixelSize();

	// compensate for the physics skin
	//w = w - 4;
	//h = h - 4;


	boost::shared_ptr<PhysicsShape> shape(new PhysicsBox(w, h));


	return shape;
}

} /* namespace physics */
} /* namespace fp_core */
