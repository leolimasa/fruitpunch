/*
 * Window.h
 *
 *  Created on: 2012-02-25
 *      Author: leo
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include <vector>
#include <fruitpunch/Common/Observable.h>
#include <boost/shared_ptr.hpp>
#include <fruitpunch/Graphics/Vertex.h>
#include <fruitpunch/Graphics/TextureManager.h>

namespace fp_core {
class Primitive;
class Renderer;
class Camera;

typedef boost::shared_ptr<Primitive> PrimitivePtr;

/// Represents the canvas in which polygons will be drawn
/**
 * The window is the core of the engine. It is responsible for storing all
 * primitives and render frames. It is also responsible for interfacing with
 * the clients and taking care of mouse events.
 */
class Window : public common::Observable {
public:
  Window();
  virtual ~Window();
    void init(int width, int height, boost::shared_ptr<Renderer> renderer);
    void renderFrame();
    void addPrimitive(boost::shared_ptr<Primitive> primitive);
    void removePrimitive(boost::shared_ptr<Primitive> primitive);
    void pointerEvent(std::string event);
    void reset();
    void createDefaultObservers();
    boost::shared_ptr<Camera>& getCamera();
    std::vector<PrimitivePtr> getPrimitives() const;
    boost::shared_ptr<Renderer>& getRenderer();
    int getWindowHeight() const;
    int getWindowWidth() const;
    point getPointer() const;
    void setCamera(boost::shared_ptr<Camera> camera);
    void setPrimitives(std::vector<PrimitivePtr> primitives);
    void setRenderer(boost::shared_ptr<Renderer> renderer);
    void setWindowHeight(int windowHeight);
    void setWindowWidth(int windowWidth);
    void setPointer(point pointer);
    void setPointerX(float x);
    void setPointerY(float y);
    int getFps() const;
    void setFps(int fps);

private:
    std::vector<PrimitivePtr> m_primitives;
    boost::shared_ptr<Camera> m_camera;
    boost::shared_ptr<Renderer> m_renderer;
    int m_window_width;
    int m_window_height;
    point m_pointer;
    int m_fps;
    long m_lastFrameRend;
    float				              *pointArrToFloatArr(point * points, int size);
    boost::shared_ptr<fp_core::common::Event>    mPreRenderEvent;
    boost::shared_ptr<fp_core::common::Event>    mPostRenderEvent;
    fp_core::graphics::TextureManager mTextureManager;

};

} /* namespace fp_core */
#endif /* WINDOW_H_ */
