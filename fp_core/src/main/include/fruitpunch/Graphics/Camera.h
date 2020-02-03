/*
 * Camera.h
 *
 *  Created on: 2012-02-20
 *      Author: leo
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <fruitpunch/Graphics/Vertex.h>
#include <armadillo>

namespace fp_core {

// ---------------------------------------------------------------------------
// Class Declaration
// ---------------------------------------------------------------------------

/// A camera that provides a matrix with position, rotation, and zoom.
/**
 *  The main purpose of this class is to generate a transformation matrix
 *  suitable to transform vertices by a given camera position, rotation
 *  and zoom. This class is used in the Window class to manipulate all the
 *  vertices on the canvas.
 */
class Camera {
public:
  Camera();
  virtual ~Camera();

  /// Returns a matrix with all the transformations applied.
  arma::fmat33 matrix();

  /// Returns a matrix that undoes the camera transformation
  arma::fmat33 inverseMatrix();

  // ------------------------------
  // Getters
  // ------------------------------
  point getPosition() const;
  float getRotation() const;
  point getZoom() const;

  // ------------------------------
  // Setters
  // ------------------------------
  void setPosition(point position);
  void setRotation(float rotation);
  void setZoom(point zoom);

private:
  float m_rotation;
  point m_zoom;
  point m_position;

};

} /* namespace fp_core */
#endif /* CAMERA_H_ */
