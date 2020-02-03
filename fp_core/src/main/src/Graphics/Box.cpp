/*
 * Box.cpp
 *
 *  Created on: 2012-03-17
 *      Author: leo
 */

#include <fruitpunch/Graphics/Box.h>

namespace fp_core {

Box::Box() {
	// TODO Auto-generated constructor stub

}

Box::~Box() {
	// TODO Auto-generated destructor stub
}

point Box::getBottomLeft() const {
	return m_bottom_left;
}

point Box::getBottomRight() const {
	return m_bottom_right;
}

point Box::getTopLeft() const {
	return m_topLeft;
}

point Box::getTopRight() const {
	return m_top_right;
}

void Box::setBottomLeft(point bottomLeft) {
	m_bottom_left = bottomLeft;
}

void Box::setBottomRight(point bottomRight) {
	m_bottom_right = bottomRight;
}

void Box::setTopLeft(point topLeft) {
	m_topLeft = topLeft;
}

void Box::setCoordinates(point top_left, point top_right, point bottom_left,
		point bottom_right) {
	m_topLeft = top_left;
	m_top_right = top_right;
	m_bottom_left = bottom_left;
	m_bottom_right = bottom_right;
}

point Box::center() const {	point z;
	z.x = 0;
	z.y = 0;
	return z;
}

void Box::setTopRight(point topRight) {
	m_top_right = topRight;
}

} /* namespace fp_core */
