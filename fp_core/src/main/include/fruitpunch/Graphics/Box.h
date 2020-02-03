/*
 * Box.h
 *
 *  Created on: 2012-03-17
 *      Author: leo
 */

#ifndef BOX_H_
#define BOX_H_

#include <fruitpunch/Graphics/Vertex.h>

namespace fp_core {

// ---------------------------------------------------------------------------
// Class Declaration
// ---------------------------------------------------------------------------

/// Represents a generic box.
/**
 *  Represents a box that can be used for any purpose where
 *  a standard set of four points applies. This is not a primitive
 *  and cannot be added to a window.
 */
class Box {
public:
  Box();
  virtual ~Box();

  // -------------------------------------------------------------------------
  // Member methods
  // -------------------------------------------------------------------------

  /// Sets all the four box coordinates at once.
  void setCoordinates(point top_left, point top_right, point bottom_left,
			point bottom_right);

  /// Calculates and returns the center of the box.
  /**
   *  This method has not been implemented yet.
   */
  point center() const;

  // -------------------------------------------------------------------------
  // Getters
  // -------------------------------------------------------------------------
  point getBottomLeft() const;
  point getBottomRight() const;
  point getTopLeft() const;
  point getTopRight() const;

  // -------------------------------------------------------------------------
  // Setters
  // -------------------------------------------------------------------------
  void setBottomLeft (point bottomLeft);
  void setBottomRight(point bottomRight);
  void setTopLeft    (point topLeft);
  void setTopRight   (point topRight);

private:
  point m_topLeft;
  point m_top_right;
  point m_bottom_left;
  point m_bottom_right;
};

} /* namespace fp_core */
#endif /* BOX_H_ */
