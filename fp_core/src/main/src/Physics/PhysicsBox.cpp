/*
 * PhysicsBox.cpp
 *
 *  Created on: 2012-09-14
 *      Author: leo
 */

#include <fruitpunch/Physics/PhysicsBox.h>

namespace fp_core {
namespace physics {

PhysicsBox::PhysicsBox(float width, float height) : PhysicsShape() {
	mWidth = width;
	mHeight = height;

}

PhysicsBox::~PhysicsBox() {
}

float PhysicsBox::getHeight() const {
	return mHeight;
}

void PhysicsBox::setHeight(float height) {
	mHeight = height;
}

float PhysicsBox::getWidth() const {
	return mWidth;
}

void PhysicsBox::setWidth(float width) {
	mWidth = width;
}

boost::shared_ptr<b2Shape> PhysicsBox::getBox2dShape(float scale) {
	boost::shared_ptr<b2PolygonShape> shape(new b2PolygonShape);

	shape->SetAsBox((mWidth / 2.0f) * scale, (mHeight / 2.0f) * scale);
	return shape;
}

}
}
