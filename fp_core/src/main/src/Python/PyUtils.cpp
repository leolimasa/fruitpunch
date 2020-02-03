/*
 * PyUtils.cpp
 *
 *  Created on: 2012-05-26
 *      Author: leo
 */

#include <fruitpunch/Python/PyUtils.h>
#include <boost/python/call_method.hpp>

namespace fp_core {

PyUtils::PyUtils() {
  // TODO Auto-generated constructor stub

}

bool PyUtils::hasMethod(PyObject* obj, std::string methodName) {
  int hasIt = PyObject_HasAttrString(obj, methodName.c_str());
  if (hasIt == 0) return false;

  PyObject * attr = PyObject_GetAttrString(obj, methodName.c_str());
  return PyCallable_Check(attr) == 1;

}

void PyUtils::call(PyObject* obj, std::string method) {
  if (!hasMethod(obj, method)) return ;
  boost::python::call_method<void>(obj, method.c_str());
}

}/* namespace fp_core */
