/*
 * Common.cpp
 *
 *  Created on: Oct 26, 2012
 *      Author: leo
 */

#include <boost/python/detail/prefix.hpp>
#include <boost/python.hpp>
#include <fruitpunch/PythonBindings/Resources.h>
#include <string>

// ---------------------------------------------------------------------------
// Fp core includes
// ---------------------------------------------------------------------------
#include <fruitpunch/Resources/Font.h>

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

void Resources::declareClasses() {

	class_<Font, bases<Observable>, boost::shared_ptr<Font> >("Font", init<string>())
		.def("make_image", &Font::makeImage)
		.def("get_alignment", &Font::getAlignment)
		.def("set_alignment", &Font::setAlignment)
		.def("is_antialias", &Font::isAntialias)
		.def("set_antialias", &Font::setAntialias)
		.def("is_bold", &Font::isBold)
		.def("set_bold", &Font::setBold)
		.def("get_color", &Font::getColor)
		.def("set_color", &Font::setColor)
		.def("is_italic", &Font::isItalic)
		.def("set_italic", &Font::setItalic)
		.def("get_line_spacing", &Font::getLineSpacing)
		.def("set_line_spacing", &Font::setLineSpacing)
		.def("get_size", &Font::getSize)
		.def("set_size", &Font::setSize);


}

} /* namespace python */
} /* namespace fp_core */
