/*
 * Common.cpp
 *
 *  Created on: Oct 26, 2012
 *      Author: leo
 */

#include <boost/python/detail/prefix.hpp>
#include <boost/python.hpp>
#include <fruitpunch/PythonBindings/Graphics.h>
#include <string>

// ---------------------------------------------------------------------------
// Fp core includes
// ---------------------------------------------------------------------------
#include <fruitpunch/Common/Observable.h>
#include <fruitpunch/Elements/Element.h>
#include <fruitpunch/Elements/Scene.h>
#include <fruitpunch/Graphics/Vertex.h>
#include <fruitpunch/Graphics/Primitive.h>
#include <fruitpunch/Graphics/Sprite.h>
#include <fruitpunch/Graphics/Color.h>
#include <fruitpunch/Graphics/Group.h>
#include <fruitpunch/Graphics/Image.h>
#include <fruitpunch/Graphics/Transformable.h>


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

void Graphics::declareClasses() {
  class_<Element, bases<Observable>, boost::shared_ptr<Element> >("Element")
    .def("add", &Element::add)
    .def("add_orphan", &Element::addOrphan)
    .def("remove", &Element::remove)
    .def("destroy", &Element::destroy)
    .def("render_frame", &Element::renderFrame)
    .def("tick", &Element::tick)
    .def("get_scene", &Element::getScene)
    .def("set_scene", &Element::setScene)
    .def("get_children", &Element::getChildren)
    .def("get_parent", &Element::getParent)
    .def("set_parent", &Element::setParent);

  class_<point>("Point")
    .def_readwrite("x", &point::x)
    .def_readwrite("y", &point::y);

  class_<Vertex>("Vertex", init<point>())
    .def("get_position", &Vertex::getPosition)
    .def("get_uvmap", &Vertex::getUvmap)
    .def("set_position", &Vertex::setPosition)
    .def("set_uvmap", &Vertex::setUvmap);

  class_<Primitive, bases<Element>, boost::shared_ptr<Primitive> >("Primitive")
    .def("add_vertex", &Primitive::addVertex)
    .def("point_vector", &Primitive::pointVector)
    .def("uv_point_vector", &Primitive::uvPointVector)
    .def("bounding_box", &Primitive::boundingBox)
    .def("boundaries", &Primitive::boundaries)
    .def("transformed_bounds", &Primitive::transformedBounds)
    .def("contains", &Primitive::contains)
    .def("vertices_center", &Primitive::verticesCenter)
    .def("move", &Primitive::move)
    .def("rotate", &Primitive::rotate)
    .def("scale", &Primitive::scale)
    .def("get_center", &Primitive::getCenter)
    .def("get_width", &Primitive::getWidth)
    .def("get_height", &Primitive::getHeight)
    .def("get_x", &Primitive::getX)
    .def("get_y", &Primitive::getY)
    .def("get_top", &Primitive::getTop)
    .def("get_left", &Primitive::getLeft)
    .def("get_tex_center", &Primitive::getTexCenter)
    .def("get_tex_position", &Primitive::getTexPosition)
    .def("get_tex_scale", &Primitive::getTexScale)
    .def("get_tex_rotation", &Primitive::getTexRotation)
    .def("get_tex_x", &Primitive::getTexX)
    .def("get_tex_y", &Primitive::getTexY)
    .def("get_position", &Primitive::getPosition)
    .def("get_rotation", &Primitive::getRotation)
    .def("get_scale", &Primitive::getScale)
    .def("get_vertices", &Primitive::getVertices)
    .def("is_stick", &Primitive::isStick)
    .def("get_image", &Primitive::getImage)
    .def("get_alpha", &Primitive::getAlpha)
    .def("set_center", &Primitive::setCenter)
    .def("set_width", &Primitive::setWidth)
    .def("set_height", &Primitive::setHeight)
    .def("set_x", &Primitive::setX)
    .def("set_y", &Primitive::setY)
    .def("set_top", &Primitive::setTop)
    .def("set_left", &Primitive::setLeft)
    .def("set_alpha", &Primitive::setAlpha)
    .def("set_position", &Primitive::setPosition)
    .def("set_rotation", &Primitive::setRotation)
    .def("set_scale", &Primitive::setScale)
    .def("set_window", &Primitive::setWindow)
    .def("set_stick", &Primitive::setStick)
    .def("set_image", &Primitive::setImage)
    .def("set_tex_center", &Primitive::setTexCenter)
    .def("set_tex_position", &Primitive::setTexPosition)
    .def("set_tex_scale", &Primitive::setTexScale)
    .def("set_tex_rotation", &Primitive::setTexRotation)
    .def("set_tex_x", &Primitive::setTexX)
    .def("set_tex_y", &Primitive::setTexY);

  class_<Sprite, bases<Primitive>, boost::shared_ptr<Sprite> >("Sprite")
    .def("__init__", make_constructor(&construct_simple<string,Sprite>))
    .def("__init__", make_constructor(&construct<Image,Sprite>))
    .def("crop", &Sprite::crop);

  class_<Window, bases<Observable>, boost::shared_ptr<Window> >("Window")
    .def("add_primitive", &Window::addPrimitive)
    .def("remove_primitive", &Window::removePrimitive)
    .def("get_primitives", &Window::getPrimitives)
    .def("get_window_height", &Window::getWindowHeight)
    .def("get_window_width", &Window::getWindowWidth)
    .def("get_pointer", &Window::getPointer)
    .def("get_fps", &Window::getFps)
    .def("set_fps", &Window::setFps)
    .def("set_pointer", &Window::setPointer)
    .def("set_pointer_x", &Window::setPointerX)
    .def("set_pointer_y", &Window::setPointerY);

  class_<Color, bases<Object>, boost::shared_ptr<Color> >("Color", init<unsigned long>())
      .def("from_long", &Color::fromLong)
      .def("to_long", &Color::toLong)
      .def("set_red", &Color::setRed)
      .def("set_green", &Color::setGreen)
      .def("set_blue", &Color::setBlue)
      .def("set_alpha", &Color::setAlpha)
      .def("get_red", &Color::getRed)
      .def("get_green", &Color::getGreen)
      .def("get_blue", &Color::getBlue)
      .def("get_alpha", &Color::getAlpha);

  class_<Group, bases<Object>, boost::shared_ptr<Group> >("Group")// Transformable is essentially an interface...I don't believe I need to extend it for python?
	  .def("add", &Group::add)
	  .def("group_center", &Group::groupCenter)
	  .def("boundaries", &Group::boundaries)
	  .def("set_position", &Group::setPosition)
	  .def("get_position", &Group::getPosition)
	  .def("set_rotation", &Group::setRotation)
	  .def("get_rotation", &Group::getRotation)
	  .def("set_scale", &Group::setScale)
	  .def("get_scale", &Group::getScale);

  class_<Image, bases<Object>, boost::shared_ptr<Image> >("Image", init<string>())
		.def("pixel_at", &Image::pixelAt)
		.def("fill", &Image::fill)
		.def("set_pixel", &Image::setPixel)
		.def("copy_to", &Image::copyTo)
		.def("apply_alpha", &Image::applyAlpha)
		.def("get_bytes_per_pixel", &Image::getBytesPerPixel)
		.def("flip_y", &Image::flipY)
		.def("get_height", &Image::getHeight)
		.def("get_width", &Image::getWidth)
		.def("get_image_id", &Image::getImageId)
		.def("get_format", &Image::getFormat);

}


} /* namespace python */
} /* namespace fp_core */
