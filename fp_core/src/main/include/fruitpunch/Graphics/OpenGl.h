/*
 * Gles2.h
 *
 *  Created on: 2012-02-19
 *      Author: leo
 */

#ifndef OPENGL_H_
#define OPENGL_H_

#include <fruitpunch/Graphics/Renderer.h>
#include <fruitpunch/Graphics/Camera.h>
#include <fruitpunch/Graphics/Image.h>
#include <map>
#include <armadillo>

using namespace arma;

namespace fp_core {

// ---------------------------------------------------------------------------
// Class Declaration
// ---------------------------------------------------------------------------

/// Implements an OpenGl renderer
/**
 * This class can be used as an argument for Window if you want OpenGl to
 * be the graphics library that fruitpunch will use to render its graphics.
 */
class OpenGl : public Renderer {
public:
  OpenGl();
  virtual ~OpenGl();

  // ---------------------------------------------------------------------------
  // Member Methods
  // ---------------------------------------------------------------------------

  /// Creates the shaders and initializes the OpenGl viewport
  /**
   * Initializes the shaders and creates a viewport matrix. The viewport
   * matrix is responsible for converting screen coordinates, where the
   * origin is at the top left of the screen and have a flipped Y, to
   * OpenGl coordinates, where the origin is at the center of the screen.
   *
   * @param width Width of the screen, in pixels
   * @param height Height of the screen, in pixels
   */
  void init(int width, int height);

  /// Returns the viewport matrix created during the init()
  virtual fmat33 viewport();

  /// Clears the screens and loads the compiled shaders
  virtual void  pre_render();

  /// Right now, this doesn't do anything, just a placeholder.
  /**
   * Might be useful in the future
   */
  virtual void  post_render();

  /// Loads a new texture into video memory
  /**
   * Tells the renderer that a new texture is supposed to be allocated based on
   * the provided image. The renderer is supposed to set the textureId of the
   * image accordingly.
   */
  virtual void addTexture(Image& image);

  /// Removes an existing texture from video memory
  /**
   * Tells the renderer that a texture is no longer being used, and that it
   * can deallocate it.
   */
  virtual void removeTexture(Image& image);

  /// Renders a polygon on the screen given an array of float vertices
  /**
   * Each two items in the array represents a vertex. For example, if the array
   * is [2,3,2,6] we have two vertices, where the first one has an X of 2 and
   * a Y of 3.
   *
   * This uses a triangle strip to render the polygon, so make sure you vertices
   * are in the right order for a triangle before passing to this method.
   *
   * @param float_array array of floats with the coordinates
   * @param vertices how many vertices there are in the array
   */
  virtual void  render_polygon(float * float_array, float * uv_array, int vertices, Image& image, float alpha);

  /// Multiplies a point by a given matrix and returns the result.
  /**
   * The reason that this method is here, in the renderer, and not somewhere
   * else is that in the future we might wanna use shaders to perform matrix
   * calculations for performance reasons.
   *
   * Right now, this just uses the CPU to perform the calculations, and has
   * does not use any OpenGl calls.
   *
   * @param p The point to be transformed
   * @param trans_matrix the transformation matrix
   * @return the transformed point
   */
  virtual point transform_point(point p,fmat33 trans_matrix);

  /// Called when there is a need to unload the OpenGl from the system
  /**
   * Right now this doesn't do anything. This is just a placeholder for future
   * needs.
   */
  virtual void unload();

private:
	unsigned int m_program;
	unsigned int m_vPosition;
	unsigned int m_texCoord;
	fmat33 m_viewport_matrix;
	unsigned int m_alpha;

	std::string getGlError(int error);
	void printGlError();
};

} /* namespace fp_core */
#endif /* GLES2_H_ */
