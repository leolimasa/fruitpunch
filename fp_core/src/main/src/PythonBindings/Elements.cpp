/*
 * Elements.cpp
 *
 *  Created on: Oct 26, 2012
 *      Author: leo
 */

#include <boost/python/detail/prefix.hpp>
#include <fruitpunch/PythonBindings/Elements.h>
#include <boost/python.hpp>
#include <string>

// ---------------------------------------------------------------------------
// Fp core includes
// ---------------------------------------------------------------------------
#include <fruitpunch/Elements/App.h>
#include <fruitpunch/Elements/Text.h>
#include <fruitpunch/Elements/Playable.h>
#include <fruitpunch/Elements/Animation.h>
#include <fruitpunch/Elements/Tween.h>


// ---------------------------------------------------------------------------
// Imports
// ---------------------------------------------------------------------------

using namespace fp_core::common;
using namespace boost::python;
using namespace std;

namespace fp_core {
namespace python {

// ---------------------------------------------------------------------------
// Methods
// ---------------------------------------------------------------------------

// ____________________________________________________________________________

void Elements::declareClasses() {
  class_<App, bases<Observable>, boost::shared_ptr<App> >("App")
      .def("init", &App::init)
      .def("render_frame", &App::renderFrame)
      .def("go_to_scene", &App::goToScene)
      .def("get_current_scene", &App::getCurrentScene)
      .def("get_runtime", &App::getRuntime)
      .def("set_current_scene", &App::setCurrentScene);

  class_<Scene, bases<Element>, boost::shared_ptr<Scene> >("Scene")
      .def("init", &Scene::init)
      .def("destroy", &Scene::destroy)
      .def("add", &Scene::add)
      .def("get_pointer", &Scene::getPointer)
      .def("get_runtime", &Scene::getRuntime)
      .def("get_window", &Scene::getWindow)
      .def("get_app", &Scene::getApp)
      .def("get_elements", &Scene::getElements)
      .def("get_width", &Scene::getWidth)
      .def("get_height", &Scene::getHeight)
      .def("set_app", &Scene::setApp)
      .def("set_pointer", &Scene::setPointer)
      .def("set_pointer_x", &Scene::setPointerX)
      .def("set_pointer_y", &Scene::setPointerY);

  class_<Text, bases<Sprite>, boost::shared_ptr<Text> >("Text", init<string>())
      .def("render_frame", &Text::renderFrame)
      .def("update", &Text::update)
      .def("get_text", &Text::getText)
      .def("get_font", &Text::getFont)
      .def("set_text", &Text::setText)
      .def("set_font", &Text::setFont);

  class_<Playable, bases<Element>, boost::shared_ptr<Playable> >("Playable")
  	.def("start", &Playable::start)
  	.def("stop", &Playable::stop)
  	.def("render_frame", &Playable::renderFrame)
  	.def("get_current_frame", &Playable::getCurrentFrame)
  	.def("set_current_frame", &Playable::setCurrentFrame)
  	.def("is_playing", &Playable::isPlaying)
  	.def("set_playing", &Playable::setPlaying)
  	.def("is_loop", &Playable::isLoop)
  	.def("set_loop", &Playable::setLoop)
  	.def("get_start_frame", &Playable::getStartFrame)
  	.def("set_start_frame", &Playable::setStartFrame)
  	.def("get_end_frame", &Playable::getEndFrame)
  	.def("get_frame_duration", &Playable::getFrameDuration)
  	.def("set_frame_duration", &Playable::setFrameDuration);

  class_<Animation, bases<Playable>, boost::shared_ptr<Animation> >("Animation")
  	.def("calculate_duration", &Animation::calculateDuration)
  	.def("render_single", &Animation::renderSingle)
  	.def("add", &Animation::add);

  class_<Tween, bases<Playable>, boost::shared_ptr<Tween> >("Tween")
  	.def("render_single", &Tween::renderSingle)
  	.def("calculate_duration", &Tween::calculateDuration)
  	.def("interpolate", &Tween::interpolate)
  	.def("get_property", &Tween::getProperty)
  	.def("set_property", &Tween::setProperty)
  	.def("get_duration", &Tween::getDuration)
  	.def("set_duration", &Tween::setDuration)
  	.def("get_end_value", &Tween::getEndValue)
  	.def("set_end_value", &Tween::setEndValue)
  	.def("get_start_value", &Tween::getStartValue)
  	.def("set_start_value", &Tween::setStartValue);

}


} /* namespace python */
} /* namespace fp_core */
