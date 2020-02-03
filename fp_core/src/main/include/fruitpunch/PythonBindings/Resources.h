/*
 * Common.h
 *
 *  Created on: Oct 26, 2012
 *      Author: leo
 */

#ifndef RESOURCES_PYTHON_H_
#define RESOURCES_PYTHON_H_

#include <fruitpunch/PythonBindings/PythonPackage.h>

namespace fp_core {
namespace python {

class Resources: public fp_core::python::PythonPackage {
public:
	virtual void declareClasses();
};

} /* namespace python */
} /* namespace fp_core */
#endif /* COMMON_H_ */
