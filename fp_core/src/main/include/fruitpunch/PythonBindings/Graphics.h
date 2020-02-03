/*
 * Common.h
 *
 *  Created on: Oct 26, 2012
 *      Author: leo
 */

#ifndef GRAPHICS_PYTHON_H_
#define GRAPHICS_PYTHON_H_

#include <boost/python/detail/prefix.hpp>
#include <fruitpunch/PythonBindings/PythonPackage.h>

namespace fp_core {
namespace python {

class Graphics: public fp_core::python::PythonPackage {
public:
	virtual void declareClasses();
};

} /* namespace python */
} /* namespace fp_core */
#endif /* COMMON_H_ */
