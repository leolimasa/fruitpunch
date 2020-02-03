/*
 * Renderer.h
 *
 *  Created on: 2012-02-19
 *      Author: leo
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include <armadillo>
#include <fruitpunch/Graphics/Vertex.h>
#include <fruitpunch/Graphics/Camera.h>
#include <fruitpunch/Graphics/Image.h>
#include <boost/shared_ptr.hpp>

using namespace arma;

namespace fp_core {

// ---------------------------------------------------------------------------
// Class Declaration
// ---------------------------------------------------------------------------

/// Interface to be implemented by rendering engines such as OpenGl and DirectX
/**
 * Interface to be implemented by a renderer. Provides standard methods so
 * that it is possible to transparently change rendering engines without having
 * to change any code in other classes.
 */
class Renderer {
public:

  /// Called only once, when the render is asked to initialize itself
  void  virtual init(int width, int height) = 0;

  /// Called before rendering every frame
  void  virtual pre_render() = 0;

  /// Called after rendering every frame
  void  virtual post_render() = 0;

  /// Returns a matrix that will be applied to every polygon
  /**
   * Usually this matrix will be a viewport transformation, hence the method
   * name. The viewport transformation is responsible for transforming
   * coordinates from a regular screen space - origin at the top left corner
   * and a flipped Y - to the space that is used by the renderer.
   * @return
   */
  arma::fmat33 virtual viewport() =0;

  /// Loads a new texture into video memory
  /**
   * Tells the renderer that a new texture is supposed to be allocated based on
   * the provided image. The renderer is supposed to set the textureId of the
   * image accordingly.
   */
  void virtual addTexture(Image& image) =0;

  /// Removes an existing texture from video memory
  /**
   * Tells the renderer that a texture is no longer being used, and that it
   * can deallocate it.
   */
  void virtual removeTexture(Image& image) =0;

  /// Renders a polygon on the screen
  virtual void render_polygon(float * float_array, float * uv_array, int vertices, Image& image, float alpha) =0;

  /// Transforms a point given a matrix
  /**
   * It is asked that renderers implement this method because on some platforms
   * it might be more efficient to have matrix transformations executed by
   * shaders.
   *
   * @param p
   * @param trans_matrix
   * @return
   */
  point virtual transform_point(point p, fmat33 trans_matrix) = 0;

  /// Called when the renderer is asked to be unloaded, like when the window closes
  void  virtual unload() = 0;
};

typedef boost::shared_ptr<Renderer> RendererPtr;

} /* namespace fp_core */
#endif /* RENDERER_H_ */
