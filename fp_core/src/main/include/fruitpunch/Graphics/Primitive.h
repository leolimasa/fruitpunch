/*
 * Primitive.h
 *
 *  Created on: 2012-02-19
 *      Author: leo
 */

#ifndef PRIMITIVE_H_
#define PRIMITIVE_H_

#include <fruitpunch/Graphics/Transformable.h>
#include <fruitpunch/Graphics/Vertex.h>
#include <fruitpunch/Graphics/Window.h>
#include <fruitpunch/Graphics/Box.h>
#include <fruitpunch/Graphics/Image.h>
#include <fruitpunch/Elements/Element.h>
#include <armadillo>
#include <boost/shared_ptr.hpp>
#include <vector>

namespace fp_core {

typedef boost::shared_ptr<Primitive> PrimitivePtr;

// ---------------------------------------------------------------------------
// Class Declaration
// ---------------------------------------------------------------------------

/// A polygon that is able to receive events and be rendered to the screen
/**
 * A Primitive is the base class for everything that will be shown on the
 * screen. It is formed by a list of vertices that will form a polygon,
 * and a texture to be applied to that polygon.
 */
class Primitive :
  public Transformable,
  public Element {

public:
  Primitive();
  Primitive(const Primitive& p);
  virtual ~Primitive();

  // -------------------------------------------------------------------------
  // Member Methods
  // -------------------------------------------------------------------------

  Primitive& operator=(const Primitive& p);

  /// Adds a new vertex that will be part of this primitive
  void addVertex(const Vertex& vertex);

  /// Returns an array of points with transformations applied
  /**
   * Goes through each vertex of the Primitive and transforms its position,
   * scale, and rotation with the values given to the Primitive. The original
   * vertex list is not changed. The result is just a copy of the vertices,
   * but with transformations applied.
   */
  point * pointArray() const;

  /// Returns an array of points with all the vertices UV coordinates
  /**
   * Returns a point array of all the uv point coordinates
   * of every single vertex of this primitive. The order
   * of those points will match the order of pointVector()
   */
  point * uvPointArray() const;

  /// Returns a vector of points with all the vertices UV coordinates
  /**
   * Returns a vector array of all the uv point coordinates
   * of every single vertex of this primitive. The order
   * of those points will match the order of pointVector()
   */
  vector<point> pointVector();

  /// Returns a vector of points with all the vertices UV coordinates
  /**
   * Returns a point vector of all the uv point coordinates
   * of every single vertex of this primitive. The order
   * of those points will match the order of pointVector()
   */
  vector<point> uvPointVector();

  /// Calculates and returns the primitive's bounding box
  /**
   * Returns a box representing a bounding
   * box around the primitive
   */
  Box boundingBox() const;

  /// Returns the minimum and maximum values of X and Y of all vertices
  /**
   * Returns a vector of points that represent the minimum and maximum vertex
   * coordinates. This information can be used to create a bounding box.
   * Format: [min, max]
   */
  std::vector<point> boundaries() const;

  /// The bounding box of all vertices after they have been transformed
  std::vector<point> transformedBounds();


  /// Checks if a point is inside a primitive
  /** Checks if the specified point is inside the area delimited by the
   *  primitive. The area already accounts for transformations.
   *
   * @param p
   * @return true if the point is inside the area. False otherwise.
   */
  bool contains(point p);

  /// Returns a reference to a vertex specified by the index
  Vertex& getVertex(int index);

  /// Center of the primitive
  /**
   * Returns a point that represents the center of a bonding box that
   * encapsulates all the vertices in the primitive.
   */
  point verticesCenter() const;

  /// Increases the Primitive position by the specified value
  void move(float x, float y);

  /// Increases the Primitive rotation by the specified value
  void rotate(float amount);

  /// Increases the Primitive scale by the specified value
  void scale(float x, float y);

  /// Element event. Adds the primitive to the window
  virtual void onAdd();

  /// Element event. Remove the primitive from the window
  virtual void onRemove();

  // -------------------------------------------------------------------------
  // Getters
  // -------------------------------------------------------------------------

  /// Center that will be used when the primitive is rotated or scaled
  /**
   * This center is local space, and will not ever be transformed.
   * @return
   */
  point getCenter  () const;

  /// Width of the bounding box after scale transformation
  float getWidth() const;

  /// Height of the bounding box after scale transformation
  float getHeight() const;

  /// X component of the position
  float getX() const;

  /// Y component of the position
  float getY() const;

  ///Distance between the top of the bounding box and the screen
  float getTop();

  /// Distance between the left edge of the bounding box and the screen
  float getLeft();

  /// UV coordinate that is the transformation center for the texture
  point getTexCenter() const;

  /// UV position offset of the texture inside this primitive
  point getTexPosition() const;

  /// UV scale factor of the texture
  point getTexScale() const;

  float getTexRotation() const;

  virtual point       getPosition() const;
  virtual float       getRotation() const;
  virtual point       getScale() const;
  std::vector<Vertex> getVertices() const;
  Window             *getWindow() const;
  bool                isStick() const;
  point *             getTransVertices() const;
  boost::shared_ptr<Image> getImage() const;
  virtual float       getAlpha() const;
  virtual float       getTexX();
  virtual float       getTexY();
  // -------------------------------------------------------------------------
  // Setters
  // -------------------------------------------------------------------------

  /// Center that will be used when the primitive is rotated or scaled
  /**
   * This center is local space, and will not ever be transformed.
   * @return
   */
  void setCenter(point center);

  /// Recalculates the scale to attain the desired width AFTER scale transformation
  void setWidth(float width);

  /// Recalculates the scale to attain the desired height AFTER scale transformation
  void setHeight(float height);

  /// Sets the X component of the position
  void setX(float x);

  /// Sets the Y component of the position
  void setY(float y);

  /// Sets the distance of the topmost vertex to the top of the screen
  void setTop(float top);

  /// Sets the distance of the leftmost vertex to the top of the screen
  void setLeft(float left);

  virtual void setAlpha(float alpha);

  /// Sets vertices after they are transformed by an outside class
  /**
   * This usually represents vertices transformed by the window. The primitive
   * can store those vertices to make accessing them easier in the future.
   *
   * @param transVertices
   */
  void         setTransVertices(point * transVertices);

  virtual void setPosition(point position);
  virtual void setRotation(float rotation);
  virtual void setScale(point scale);
  void         setWindow(Window *window);
  void         setStick(bool stick);
  virtual void setImage(boost::shared_ptr<Image> image);

    void setTexCenter(point texCenter);
    void setTexPosition(point texPosition);
    void setTexScale(point texScale);
    void setTexX(float val);
    void setTexY(float val);

    void setTexRotation(float texRotation);

private:
  void                copy_from(const Primitive & p);

  /// Returns the transformation matrix for this primitive
  arma::fmat33        transformationMatrix() const;

  struct              comparator;
  point *             m_trans_vertices; // vertices after Window transformation
  std::vector<Vertex> m_vertices;
  point               m_position;
  float               m_rotation;
  point               m_scale;
  Window             *m_window;
  point               m_center;
  bool                m_stick; // will this primitive be affected by camera?
  point               mTexScale;
  point               mTexPosition;
  point               mTexCenter;
  float               mTexRotation;
  boost::shared_ptr<Image> mImage;
  float               m_alpha;
};

} /* namespace fp_core */
#endif /* PRIMITIVE_H_ */
