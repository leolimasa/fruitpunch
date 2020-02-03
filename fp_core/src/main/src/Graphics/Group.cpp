/*
 * Group.cpp
 *
 *  Created on: 2012-03-17
 *      Author: leo
 */

#include <fruitpunch/Graphics/Group.h>
#include <fruitpunch/Graphics/Matrices.h>
#include <armadillo>

using namespace arma;

namespace fp_core {
using namespace fp_core::common;

Group::Group() : Object() {
	point zero;
	zero.x = 0;
	zero.y = 0;

	point one;
	one.x = 1;
	one.y = 1;

	m_center = zero;
	m_position = zero;
	m_scale = one;
	m_rotation = 0;
}

Group::~Group() {
	// TODO Auto-generated destructor stub
}

//void Group::move(point delta) {
//	std::vector<TransformablePtr>::iterator it;
//	for (it = m_content.begin(); it != m_content.end(); it++) {
//		point pos = (**it).getPosition();
//		pos.x = pos.x + delta.x;
//		pos.y = pos.y + delta.y;
//		(**it).setPosition(pos);
//	}
//}

void Group::add(TransformablePtr transformable) {
	m_content.push_back(transformable);
	m_center = groupCenter();
}

point Group::groupCenter() const {
	std::vector<point> bounds = boundaries();
	point center;
	point min = bounds[0];
	point max = bounds[1];
	center.x = (min.x + max.x) / 2;
	center.y = (min.y + max.y) / 2;
	return center;
}

std::vector<point> Group::boundaries() const {
	std::vector<point> result;
	point max;
	point min;

	if (m_content.size() == 0)
		return result;
	max = m_content[0]->getPosition();
	min = max;

	std::vector<TransformablePtr>::const_iterator it;

	for (it = m_content.begin(); it != m_content.end(); it++) {
		point p = (**it).getPosition();
		if (p.x < min.x)
			min.x = p.x;
		if (p.y < min.y)
			min.y = p.y;
		if (p.x > max.x)
			max.x = p.x;
		if (p.y > max.y)
			max.y = p.y;
	}
	result.push_back(min);
	result.push_back(max);

	return result;
}

void Group::setPosition(point pos) {
	/**
	 * We calculate a delta to be added/subtracted from
	 * each transformable in the list, because we want
	 * to preserve the transformable original position
	 * within the group
	 */

	point delta;
	delta.x = pos.x - m_position.x;
	delta.y = pos.y - m_position.y;

	std::vector<TransformablePtr>::iterator it;
	for (it = m_content.begin(); it != m_content.end(); it++) {
		point contpos = (**it).getPosition();
		contpos.x = pos.x + delta.x;
		contpos.y = pos.y + delta.y;
		(**it).setPosition(contpos);
	}
	m_position = pos;

}

point Group::getPosition() const {
	return m_position;
}

void Group::setRotation(float angle) {
	float delta = angle - m_rotation;

	// calculates the transformation matrix
	fmat33 trans = to_local_space_matrix(m_center);
	trans = (arma::fmat33) (rotation_matrix(delta) * trans);
	trans = (arma::fmat33) (to_global_space_matrix(m_center) * trans);

	std::vector<TransformablePtr>::iterator it;
	for (it = m_content.begin(); it != m_content.end(); it++) {
		point oldpos = (**it).getPosition();
		point newpos = m_renderer->transform_point(oldpos, trans);
		(**it).setPosition(newpos);
		(**it).setRotation(angle);
	}

	m_rotation = angle;

}

float Group::getRotation() const {
	return m_rotation;
}

void Group::setScale(point scal) {
	point delta;
	delta.x = scal.x - m_scale.x;
	delta.y = scal.y - m_scale.y;

	// calculates the transformation matrix
	fmat33 trans = to_local_space_matrix(m_center);
	trans = (arma::fmat33) (scale_matrix(delta) * trans);
	trans = (arma::fmat33) (to_global_space_matrix(m_center) * trans);

	std::vector<TransformablePtr>::iterator it;
	for (it = m_content.begin(); it != m_content.end(); it++) {
		point oldpos = (**it).getPosition();
		point newpos = m_renderer->transform_point(oldpos, trans);
		(**it).setPosition(newpos);
		(**it).setScale(scal);
	}

	m_scale = scal;
}

point Group::getScale() const {
	return m_scale;
}

} /* namespace fp_core */
