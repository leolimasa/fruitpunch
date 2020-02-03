/*
 * Window.cpp
 *
 *  Created on: 2012-02-25
 *      Author: leo
 */

#include <boost/python.hpp>
#include <vector>
#include <fruitpunch/Graphics/Renderer.h>
#include <fruitpunch/Graphics/Camera.h>
#include <fruitpunch/Graphics/Window.h>
#include <fruitpunch/Graphics/Primitive.h>
#include <fruitpunch/Graphics/Matrices.h>
#include <fruitpunch/Common/Events.h>
#include <fruitpunch/Common/Event.h>
#include <fruitpunch/Common/Observer.h>
#include <time.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/gregorian/greg_month.hpp>
#include <boost/date_time/gregorian_calendar.hpp>
#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include <fruitpunch/Python/PyLoader.h>

#ifdef WIN32

#include <Windows.h>

#else

#include <unistd.h>

#endif

using namespace std;
using namespace fp_core::common;

namespace fp_core {

    class WindowClickObserver : public Observer
    {
    public:
        void action()
        {
        	boost::shared_ptr<Window> w = boost::static_pointer_cast<Window>(getInstance());

        	try {
        		w->pointerEvent(getEventName());
            } catch (const boost::python::error_already_set&) {
            	printf("%s", Runtime::getCurrent()->getPythonLoader()->getPythonError().c_str());
            }
        }

    };

    Window::~Window()
    {

    }

    boost::shared_ptr<Camera>& Window::getCamera()
    {
        return m_camera;
    }

    vector<PrimitivePtr> Window::getPrimitives() const
    {
        return m_primitives;
    }

    boost::shared_ptr<Renderer>& Window::getRenderer()
    {
        return m_renderer;
    }

    int Window::getWindowHeight() const
    {
        return m_window_height;
    }

    int Window::getWindowWidth() const
    {
        return m_window_width;
    }

    void Window::setCamera(boost::shared_ptr<Camera> camera)
    {
        m_camera = camera;
    }

    void Window::setPrimitives(vector<PrimitivePtr> primitives)
    {
        m_primitives = primitives;
    }

    void Window::setRenderer(boost::shared_ptr<Renderer> renderer)
    {
        m_renderer = renderer;
    }

    void Window::setWindowHeight(int windowHeight)
    {
        m_window_height = windowHeight;
    }

    void Window::init(int width, int height, boost::shared_ptr<Renderer> renderer)
    {
        m_camera = boost::shared_ptr<Camera>(new Camera());
        m_renderer = renderer;
        m_renderer->init(width, height);
        m_window_width = width;
        m_window_height = height;
        m_lastFrameRend = 0;
        createDefaultObservers();

        mTextureManager.setRenderer(renderer.get());
    }

    void Window::renderFrame()
    {
    	notify(mPreRenderEvent);

    	// ---------------------------------------------------------------------------
		// Detectes if we should render the frame based on the FPS
		// ---------------------------------------------------------------------------
        float frameTimeMs = (1.0f / (float) m_fps) * 1000.0f;
        long curTimeInMs = Runtime::getTimeInMs();

		// TODO make windows respect this
		#ifndef WIN32
        if((curTimeInMs - m_lastFrameRend) < frameTimeMs){
        	usleep(10); // give some time for the cpu to breathe
            return;
        }
		#endif
        m_lastFrameRend = curTimeInMs;
        m_renderer->pre_render();

        mTextureManager.startFrame();

        // ---------------------------------------------------------------------------
		// Cycles through the primitives and renders them
		// ---------------------------------------------------------------------------
        vector<boost::shared_ptr<Primitive> >::iterator it = m_primitives.begin();
        for (; it != m_primitives.end(); it++) {
			const PrimitivePtr& p = *it;

			mTextureManager.renderImage(*(p->getImage().get()));
			point * parr = p->pointArray();
			point * uvarr = p->uvPointArray();
			int parrSize = p->getVertices().size();

			// camera transformation
			if (!p->isStick()) {
				apply_matrix_transformation(parr, parrSize, *m_renderer,
						m_camera->matrix());
			}

			// viewport transformation
			apply_matrix_transformation(parr, parrSize, *m_renderer,
					m_renderer->viewport());

			// updates the primitive vertex information
			p->setTransVertices(parr);

			// renders the vertices
			float * farr = pointArrToFloatArr(parr, parrSize);
			float * fuvarr = pointArrToFloatArr(uvarr, parrSize);

			m_renderer->render_polygon(farr, fuvarr, p->getVertices().size(), *(p->getImage()), p->getAlpha());

			delete[] farr;
			delete[] fuvarr;
			delete[] parr;
			delete[] uvarr;


        }
        mTextureManager.endFrame();
        m_renderer->post_render();
        notify(mPostRenderEvent);
    }

    int Window::getFps() const
    {
        return m_fps;
    }

    void Window::setFps(int fps)
    {
        m_fps = fps;
    }



    void Window::addPrimitive(boost::shared_ptr<Primitive> primitive)
    {
        primitive->setWindow(this);
        m_primitives.push_back(primitive);
        boost::shared_ptr<Primitive> p = m_primitives[0];
    }

    void Window::setWindowWidth(int windowWidth)
    {
        m_window_width = windowWidth;
    }

    Window::Window() :
    		mPreRenderEvent(Event::ref(new Event(EV_PRE_RENDER))),
    		mPostRenderEvent(Event::ref(new Event(EV_POST_RENDER)))
    {
    	// Default to 60 frames per second...
    	setFps(60);

    }

    float *Window::pointArrToFloatArr(point * points, int size)
    {
        int vsize = size * 2;
        float *result = new float[vsize];
        int i = 0;
        int ii = 0;
        for(;i < size;i++){
            result[ii++] = points[i].x;
            result[ii++] = points[i].y;
        }
        return result;
    }

    void Window::pointerEvent(std::string event)
    {
        point cPointer = m_renderer->transform_point(m_pointer, m_camera->inverseMatrix());
        vector<PrimitivePtr>::const_iterator it = m_primitives.begin();
        for(;it != m_primitives.end();it++){
            if((**it).contains(cPointer)){
                (**it).notify(Event::ref(new Event(event)));
                //return;
            }
        }
    }

    point Window::getPointer() const
    {
        return m_pointer;
    }

    void Window::setPointer(point pointer)
    {
        m_pointer = pointer;
    }

    void Window::setPointerX(float x) {
    	m_pointer.x = x;
    }

    void Window::setPointerY(float y) {
    	m_pointer.y = y;
    }

    void Window::reset()
    {
    	m_primitives.clear();

    	removeAllObservers();
    	createDefaultObservers();
    }

void Window::createDefaultObservers()
{
  typedef boost::shared_ptr<WindowClickObserver> observer;

   observer o1(new WindowClickObserver());
   observer o2(new WindowClickObserver());
   observer o3(new WindowClickObserver());

   this->attachObserver(EV_POINTER_DOWN, o1);
   this->attachObserver(EV_POINTER_UP, o2);
   this->attachObserver(EV_POINTER_MOVE, o3);

   this->notify(Event::ref(new Event(EV_INIT)));
}

void Window::removePrimitive(boost::shared_ptr<Primitive> primitive) {
  vector<boost::shared_ptr<Primitive> >::iterator it = m_primitives.begin();
  for (; it != m_primitives.end(); it++) {
    if (it->get() == primitive.get()) {
      m_primitives.erase(it);
      break;
    }
  }
}

}


 /* namespace fp_core */
