/*
 * Vertex.cpp
 *
 *  Created on: 2012-02-19
 *      Author: leo
 */

#include <fruitpunch/Graphics/Vertex.h>
#include <fruitpunch/Graphics/Renderer.h>
#include <fruitpunch/Graphics/Matrices.h>
#include <math.h>
#include <armadillo>

#ifndef PI
#define PI 3.141592
#endif

using namespace std;

namespace fp_core {

Vertex::Vertex(point p) {
	setPosition(p);
}

Vertex::~Vertex() {
	// TODO Auto-generated destructor stub
}

point Vertex::getPosition() const {
	return mPosition;
}

point Vertex::getUvmap() const {
	return mUvmap;
}

void Vertex::setPosition(point position) {
	mPosition.x = position.x;
	mPosition.y = position.y;
}

Vertex::Vertex(const Vertex & v) {
	copy_from(v);
}

void Vertex::setUvmap(point uvmap) {
	mUvmap = uvmap;
}

Vertex & Vertex::operator =(const Vertex & v) {
	copy_from(v);
	return *this;
}

void Vertex::copy_from(const Vertex & v) {
	mPosition.x = v.getPosition().x;
	mPosition.y = v.getPosition().y;
	mUvmap.x = v.getUvmap().x;
	mUvmap.y = v.getUvmap().y;
}

bool point::comesBeforeCC(point a, point b, point center, Renderer& r) {

  // convert to local space
  arma::fmat33 trans = to_local_space_matrix(center);
  a = r.transform_point(a, trans);
  b = r.transform_point(b, trans);

  // convert to polar coordinate
  float aPolar = atan(a.y / a.x);
  float bPolar = atan(b.y / b.x);

  // If a or b falls in quadrants II, III, or IV, we will have to compensate
  // see: http://www.mathsisfun.com/polar-cartesian-coordinates.html
  float aAdd = 0;
  float bAdd = 0;

  // Quadrant II or III
  if (a.x < 0) aAdd = PI;
  if (b.x < 0) bAdd = PI;

  // Quadrant IV
  if (a.x > 0 && a.y < 0) aAdd = 2 * PI;
  if (b.x > 0 && b.y < 0) bAdd = 2 * PI;

  aPolar += aAdd;
  bPolar += bAdd;

  // compares the angles
  // Here, we consider we are using a flipped Y (standard screen coordinates)
  // if not, change the > to a < to have counter clockwise
  return aPolar > bPolar;
}

std::vector<point> point::boundaries(const std::vector<point> & points) {
  vector<point> result;
  point max;
  point min;

  if (points.size() == 0)
    return result;
  max = points[0];
  min = max;

  vector<point>::const_iterator it = points.begin();

  for (; it != points.end(); it++) {
    point p = *it;
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

std::vector<point> Vertex::positionPointVector(const std::vector<Vertex> vertices) {
  vector<point> result;

  vector<Vertex>::const_iterator it;
  for (it = vertices.begin(); it != vertices.end(); ++it) {
    result.push_back(it->getPosition());
  }

  return result;
}

}
 /* namespace fp_core */
