/*
 * Primitive.cpp
 *
 *  Created on: 2012-02-19
 *      Author: leo
 */

#include <fruitpunch/Graphics/Vertex.h>
#include <fruitpunch/Graphics/Matrices.h>
#include <fruitpunch/Graphics/Renderer.h>
#include <fruitpunch/Graphics/Window.h>
#include <fruitpunch/Graphics/Primitive.h>
#include <fruitpunch/Graphics/Image.h>
#include <fruitpunch/Common/Runtime.h>
#include <fruitpunch/Elements/Scene.h>

#include <boost/shared_ptr.hpp>
#include <list>
#include <stdio.h>
#include <armadillo>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;
using namespace arma;
using namespace fp_core::common;

namespace fp_core {

Primitive::Primitive() : Element(), m_trans_vertices(NULL) {

  point zero;
  zero.x = 0;
  zero.y = 0;

  point one;
  one.x = 1;
  one.y = 1;
  m_center = zero;
  m_rotation = 0;
  m_scale = one;
  m_position = zero;

  point center;
  center.x = 0.5f;
  center.y = 0.5f;
  mTexScale = one;
  mTexPosition = zero;
  mTexRotation = 0;
  mTexCenter = center;

  m_alpha = 1;

  m_window = Runtime::getCurrent()->getWindow().get();
}

//______________________________________________________________________________

Primitive::Primitive(const Primitive & p) : m_trans_vertices(NULL) {
  copy_from(p);
}

//______________________________________________________________________________

Primitive::~Primitive() {

}

//______________________________________________________________________________

Primitive & Primitive::operator =(const Primitive & p) {
  copy_from(p);
  return *this;
}

//______________________________________________________________________________

void Primitive::addVertex(const Vertex& vertex) {
  m_vertices.push_back(vertex);

  // if we have at least three vertices, generate a center
  if (m_vertices.size() >= 3) {
    m_center = verticesCenter();
  }
}

//______________________________________________________________________________

point * Primitive::pointArray() const {

  // Allocates memory
  point * result = new point[m_vertices.size()];

  // Gets the transformation matrix
  fmat33 main = transformationMatrix();

  // create point array
  for (unsigned int i = 0; i < m_vertices.size(); i++) {

    // gets the point
    point p = m_vertices[i].getPosition();

    // transforms the point
    p = getWindow()->getRenderer()->transform_point(p, main);
    result[i] = p;
  }

  return result;
}

//______________________________________________________________________________

void Primitive::move(float x, float y) {
  m_position.x = m_position.x + x;
  m_position.y = m_position.y + y;
}

//______________________________________________________________________________

void Primitive::rotate(float amount) {
  m_rotation = m_rotation + amount;
}

//______________________________________________________________________________

void Primitive::scale(float x, float y) {
  m_scale.x = m_scale.x * x;
  m_scale.y = m_scale.y * y;
}

//______________________________________________________________________________

void Primitive::copy_from(const Primitive & p) {
  m_center = p.getCenter();
  m_rotation = p.getRotation();
  m_position = p.getPosition();
  m_scale = p.getScale();
  m_stick = p.isStick();
  m_vertices = p.getVertices();
  m_window = p.getWindow();
  mImage = p.getImage();
  mTexCenter = p.getTexCenter();
  mTexPosition = p.getTexPosition();
  mTexRotation = p.getTexRotation();
  mTexScale = p.getTexScale();  
  m_alpha = p.getAlpha();
}

//______________________________________________________________________________

std::vector<point> Primitive::boundaries() const {
  vector<point> positions = Vertex::positionPointVector(m_vertices);
  return point::boundaries(positions);
}

//______________________________________________________________________________

Box Primitive::boundingBox() const {
  vector<point> bounds = boundaries();
  Box b;
  point bottom_left;
  point bottom_right;
  point top_left;
  point top_right;

  bottom_left.x = bounds[0].x;
  bottom_left.y = bounds[0].y;
  bottom_right.x = bounds[1].x;
  bottom_right.y = bounds[0].y;
  top_left.x = bounds[0].x;
  top_left.y = bounds[1].y;
  top_right.x = bounds[1].x;
  top_right.y = bounds[1].y;

  b.setCoordinates(top_left, top_right, bottom_left, bottom_right);
  return b;
}

//______________________________________________________________________________

point Primitive::verticesCenter() const {
  vector<point> bounds = boundaries();
  point center;
  point min = bounds[0];
  point max = bounds[1];
  center.x = (min.x + max.x) / 2;
  center.y = (min.y + max.y) / 2;
  return center;
}

//______________________________________________________________________________

point * Primitive::uvPointArray() const {
  vector<Vertex>::const_iterator it;

  fmat33 main;
  main.eye(); // assigns identity

  // ---------------------------------------------------------------------------
  // Uv Transformations
  // ---------------------------------------------------------------------------

  // goes to local space
   main = (arma::fmat33) (to_local_space_matrix(mTexCenter) * main);

   // concatenates the transformations
   main = (arma::fmat33) (rotation_matrix(mTexRotation) * main);
   main = (arma::fmat33) (scale_matrix(mTexScale) * main);

   // goes to world space
   main = (arma::fmat33) (to_global_space_matrix(mTexCenter) * main);

   // moves to position
   main = (arma::fmat33) (translation_matrix(mTexPosition) * main);

   point * result = new point[m_vertices.size()];
   int i = 0;
  for (it = m_vertices.begin(); it != m_vertices.end(); it++) {
    point uv = it->getUvmap();

    // transforms the UV coordinates before pushing it
    uv = getWindow()->getRenderer()->transform_point(uv, main);

    result[i] = uv;
    i++;
  }
  return result;
}

//______________________________________________________________________________

struct Primitive::comparator {
  boost::shared_ptr<Renderer> renderer;
  point center;

  bool operator ()(const point& i, const point& j) const {
    Renderer& r = *renderer;
    return point::comesBeforeCC(i, j, center, r);
  }
};

bool Primitive::contains(point p) {

  vector<point> V = this->pointVector();
  if (V.size() < 3) return false;

  // checks if the point intersects any of the vertices
  vector<point>::iterator it = V.begin();
  for (; it != V.end(); it++) {
      if (it->x == p.x && it->y == p.y) {
          return true;
      }
  }

  /*
   * Checks if the point is inside the primitive (polygon) by using the
   * first algorithm described in
   * http://local.wasp.uwa.edu.au/~pbourke/geometry/insidepoly/
   */

  // Order points counter clockwise
  comparator comp;
  comp.renderer = getWindow()->getRenderer();
  comp.center = getCenter();
  std::sort(V.begin(), V.end(), comp);

  // close the polygon
  V.push_back(V[0]);

  int crossings = 0;

  // loops through all the edges
  for (unsigned int i=0; i<V.size()-1; i++) {
    point vA = V[i];
    point vB = V[i+1];

    // orders vA and vB according to which one is at the bottom - biggest
    // Y coordinate. vB will always be the highest Y.
    if (vA.y > vB.y) {
      point temp = vA;
      vA = vB;
      vB = temp;
    }

    // gets the minimum and maximum x,y values and checks if the point
    // falls right on the edge
    vector<point> edge;
    edge.push_back(vA);
    edge.push_back(vB);
    vector<point> bounds = point::boundaries(edge);
    if (p.x <= bounds[1].x && p.x >= bounds[0].x && p.y <= bounds[1].y && p.y >= bounds[0].y) {
        return true;
    }

    //printf("vA: (%f,%f), vB: (%f,%f) \n", vA.x, vA.y, vB.x, vB.y);
    // Checks if the point is between the Ys of the edges
    if (vA.y == vB.y) continue; // no point doing anything if its a horizontal line
    if (p.y > vB.y || p.y < vA.y) continue;

    // Checks if its a vertical edge and if the point comes to the left of the
    // edge
    if (vA.x == vB.x && p.x <= vA.x) {
      crossings++;
      continue;
    }

    // If it gets here, its because the edge is not a horizontal or vertical
    // line. In this case, we have to get a line equation in the form
    // f(x) = ax + b in order to get the X value of the edge that intercepts
    // the Y value of our point.
    float a = (vA.y - vB.y) / (vA.x - vB.x);
    float b = vB.y - a * vB.x;
    float ex = (p.y - b) / a;
    if (p.x <= ex) crossings++;
  }

  return (crossings % 2 != 0); // true if its odd
}

//______________________________________________________________________________

std::vector<point> Primitive::transformedBounds() {
  vector<point> points = pointVector();
  return point::boundaries(points);
}

//______________________________________________________________________________

vector<point> Primitive::pointVector() {
	vector<point> result;
	point * points = pointArray();
	for (int i =0; i<m_vertices.size(); i++) {
		result.push_back(points[i]);
	}
	delete points;
	return result;
}

//______________________________________________________________________________

vector<point> Primitive::uvPointVector() {
	vector<point> result;
	point * points = uvPointArray();
	for (int i =0; i<m_vertices.size(); i++) {
		result.push_back(points[i]);
	}
	delete points;
	return result;
}

//______________________________________________________________________________

arma::fmat33 Primitive::transformationMatrix() const {
  fmat33 main;
  main.eye(); // assigns identity

  // goes to local space
  main = (arma::fmat33) (to_local_space_matrix(m_center) * main);

  // concatenates the transformations
  main = (arma::fmat33) (rotation_matrix(m_rotation) * main);
  main = (arma::fmat33) (scale_matrix(m_scale) * main);

  // goes to world space
  main = (arma::fmat33) (to_global_space_matrix(m_center) * main);

  // moves to position
  main = (arma::fmat33) (translation_matrix(m_position) * main);

  return main;
}

// ---------------------------------------------------------------------------
// Getters and setters
// ---------------------------------------------------------------------------

float Primitive::getWidth() const {
  vector<point> bounds = boundaries();

  // original width is the maximum X - minimum X
  float origWidth = bounds[1].x - bounds[0].x;

  return origWidth * m_scale.x;
}

float Primitive::getHeight() const {
  vector<point> bounds = boundaries();

  // original width is the maximum X - minimum X
  float origHeight = bounds[1].y - bounds[0].y;

  return origHeight * m_scale.y;
}

void Primitive::setWidth(float width) {
  vector<point> bounds = boundaries();

  // original width is the maximum X - minimum X
  float origWidth = bounds[1].x - bounds[0].x;

  m_scale.x = width / origWidth;
}

void Primitive::setHeight(float height) {
  vector<point> bounds = boundaries();

  // original width is the maximum X - minimum X
  float origHeight = bounds[1].y - bounds[0].y;

  m_scale.y = height / origHeight;
}

float Primitive::getTop() {
  return transformedBounds()[0].y;
}

float Primitive::getLeft() {
  return transformedBounds()[0].x;
}

void Primitive::setTop(float top) {
  // we need minimum Y
  vector<point> bounds = transformedBounds();
  float minY = bounds[0].y;

  // calculates the difference
  float delta = top - minY;

  // corrects it
  move(0, delta);

}

void Primitive::setLeft(float left) {
  // we need minimum X
  vector<point> bounds = transformedBounds();
  float minX = bounds[0].x;

  // calculates the difference
  float delta = left - minX;

  // corrects it
  move(delta, 0);
}

float Primitive::getX() const {
  return m_position.x;
}

float Primitive::getY() const {
  return m_position.y;
}

void Primitive::setX(float x) {
  m_position.x = x;
}

void Primitive::setY(float y) {
  m_position.y = y;
}

point Primitive::getCenter() const {
  return m_center;
}

point Primitive::getPosition() const {
  return m_position;
}

float Primitive::getRotation() const {
  return m_rotation;
}

point Primitive::getScale() const {
  return m_scale;
}

vector<Vertex> Primitive::getVertices() const {
  return m_vertices;
}

Window *Primitive::getWindow() const {
  return m_window;
}

void Primitive::setCenter(point center) {
  m_center = center;
}

void Primitive::setPosition(point position) {
  m_position = position;
}

void Primitive::setRotation(float rotation) {
  m_rotation = rotation;
}

void Primitive::setScale(point scale) {
  m_scale = scale;
}

void Primitive::setWindow(Window *window) {
  m_window = window;
}

bool Primitive::isStick() const {
  return m_stick;
}

void Primitive::setStick(bool stick) {
  m_stick = stick;
}

point * Primitive::getTransVertices() const
{
    return m_trans_vertices;
}

void Primitive::setTransVertices(point * transVertices)
{
	if (m_trans_vertices != NULL) {
		delete[] m_trans_vertices;
	}

	m_trans_vertices = new point[m_vertices.size()];
	for (int i=0; i<m_vertices.size(); i++) {
		m_trans_vertices[i] = transVertices[i];
	}
}

Vertex& Primitive::getVertex(int index) {
	return m_vertices[index];
}

boost::shared_ptr<Image> Primitive::getImage() const {
  return mImage;
}

void Primitive::setImage(boost::shared_ptr<Image> image) {
  mImage = image;
}

point Primitive::getTexCenter() const {
  return mTexCenter;
}

float Primitive::getAlpha() const {
	return m_alpha;
}
point Primitive::getTexPosition() const {
  return mTexPosition;
}

void Primitive::setAlpha(float alpha) {
	m_alpha = alpha;
}
point Primitive::getTexScale() const {
  return mTexScale;
}

void Primitive::setTexCenter(point texCenter) {
  mTexCenter = texCenter;
}

void Primitive::setTexPosition(point texPosition) {
  mTexPosition = texPosition;
}

void Primitive::setTexScale(point texScale) {
  mTexScale = texScale;
}

float Primitive::getTexRotation() const {
  return mTexRotation;
}

void Primitive::setTexRotation(float texRotation) {
  mTexRotation = texRotation;
}

void fp_core::Primitive::onAdd() {
  Runtime::getCurrent()->getWindow()->addPrimitive(getThis<Primitive>());
}

void fp_core::Primitive::onRemove() {
	getScene()->getWindow()->removePrimitive(getThis<Primitive>());
}

float Primitive::getTexX() {
	return mTexPosition.x;
}

float Primitive::getTexY() {
	return mTexPosition.y;
}

void Primitive::setTexX(float val) {
	mTexPosition.x = val;
}

void Primitive::setTexY(float val) {
	mTexPosition.y = val;
}

/* namespace fp_core */
}


