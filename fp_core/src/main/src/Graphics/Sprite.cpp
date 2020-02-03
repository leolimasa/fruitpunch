/*
 * Sprite.cpp
 *
 *  Created on: 2012-03-05
 *      Author: leo
 */

#include <fruitpunch/Graphics/Sprite.h>
#include <boost/shared_ptr.hpp>

using namespace fp_core::common;

namespace fp_core {

Sprite::Sprite() : Primitive() {
	init();

}

Sprite::~Sprite() {
	// TODO Auto-generated destructor stub
}

Sprite::Sprite(std::string image) : Primitive() {
  boost::shared_ptr<Image> i(new Image(image));

  init();
  setImage(i);
}

Sprite::Sprite(boost::shared_ptr<Image> image) : Primitive() {

  init();
  setImage(image);
}

void Sprite::init() {

    // The max here is 2 because we need a number that is a power of 2
    // so when we transform the primitive to local space, it won't have
    // a weird floating point center. For example: if this was just 1, then
    // the center of the primitive would be 0.5, and therefore when it scales
    // it will be off by those 0.5
    static float MAX = 2.0f;

	// Makes a MAXxMAX (2x2) square primitive
	point p1;
	p1.x = 0;
	p1.y = MAX;

	point uv1;
	uv1.x = 0;
	uv1.y = 0;

	point p2;
	p2.x = 0;
	p2.y = 0;

	point uv2;
	uv2.x = 0;
	uv2.y = 1;

	point p3;
	p3.x = MAX;
	p3.y = MAX;

    point uv3;
    uv3.x = 1;
    uv3.y = 0;

	point p4;
	p4.x = MAX;
	p4.y = 0;

    point uv4;
    uv4.x = 1;
    uv4.y = 1;

	Vertex v1(p1);
	v1.setUvmap(uv1);

	Vertex v2(p2);
	v2.setUvmap(uv2);

	Vertex v3(p3);
	v3.setUvmap(uv3);

	Vertex v4(p4);
	v4.setUvmap(uv4);

	addVertex(v1);
	addVertex(v2);
	addVertex(v3);
	addVertex(v4);

	// positions at 0x0 by default
//	setTop(0);
//	setLeft(0);
}

//void Sprite::renderFrame() {
//
//}
//
//void Sprite::onAdd() {
//}
//
//void Sprite::onRemove() {
//}

}/* namespace fp_core */

void fp_core::Sprite::setImage(boost::shared_ptr<Image> image) {
	Primitive::setImage(image);

	// defaults to the width and height of the image
	setWidth(getImage()->getWidth());
	setHeight(getImage()->getHeight());
}

void fp_core::Sprite::crop(float x, float y, float width, float height) {

	point uv1;
	uv1.x = x / getImage()->getWidth();
	uv1.y = (getImage()->getHeight() - y - height) / getImage()->getHeight();

	point uv2;
	uv2.x = x / getImage()->getWidth();
	uv2.y = (getImage()->getHeight() - y) / getImage()->getHeight();

	point uv3;
	uv3.x = (x + width) / getImage()->getWidth();
	uv3.y = (getImage()->getHeight() - y - height) / getImage()->getHeight();

	point uv4;
	uv4.x = (x + width) / getImage()->getWidth();
	uv4.y = (getImage()->getHeight() - y) / getImage()->getHeight();

	getVertex(0).setUvmap(uv1);
	getVertex(1).setUvmap(uv2);
	getVertex(2).setUvmap(uv3);
	getVertex(3).setUvmap(uv4);
}
