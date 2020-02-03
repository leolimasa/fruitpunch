/*
 * Camera.cpp
 *
 *  Created on: 2012-02-20
 *      Author: leo
 */

#include <fruitpunch/Graphics/Camera.h>
#include <fruitpunch/Graphics/Vertex.h>
#include <fruitpunch/Graphics/Matrices.h>

namespace fp_core {

Camera::Camera() {
	point zero;
	zero.x = 0;
	zero.y = 0;

	point one;
	one.x = 1;
	one.y = 1;
	m_zoom = one;
	m_rotation = 0;
	m_position = zero;
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}


fp_core::point Camera::getPosition() const
{
    return m_position;
}

float Camera::getRotation() const
{
    return m_rotation;
}

point Camera::getZoom() const
{
    return m_zoom;
}

void Camera::setPosition(point position)
{
    m_position = position;
}

void Camera::setRotation(float rotation)
{
    m_rotation = rotation;
}

void Camera::setZoom(point zoom)
{
    m_zoom = zoom;
}

arma::fmat33 fp_core::Camera::matrix()
{
  arma::fmat33 trans;
  trans.eye(); // load identity

  // Remember: rotation and position camera transformations are the inverse
  // of normal transformations. Hence the - (minus) before
  // each parameter

  point negative_position;
  negative_position.x = -m_position.x;
  negative_position.y = -m_position.y;

//	point negative_scale;
//	negative_scale.x = -m_zoom.x;
//	negative_scale.y = -m_zoom.y;

  trans = (arma::fmat33) (rotation_matrix(-m_rotation) * trans);
  trans = (arma::fmat33) (scale_matrix(m_zoom) * trans);
  trans = (arma::fmat33) (translation_matrix(negative_position) * trans);

  return trans;
}

arma::fmat33 fp_core::Camera::inverseMatrix()
{
  arma::fmat33 trans;
  trans.eye(); // load identity

  point inverse_zoom;
  inverse_zoom.x = 1/m_zoom.x;
  inverse_zoom.y = 1/m_zoom.y;

  trans = (arma::fmat33) (translation_matrix(m_position) * trans);
  trans = (arma::fmat33) (scale_matrix(inverse_zoom) * trans);
  trans = (arma::fmat33) (rotation_matrix(m_rotation) * trans);

  return trans;
}

}



 /* namespace fp_core */
