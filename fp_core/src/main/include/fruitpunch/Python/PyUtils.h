/*
 * PyUtils.h
 *
 *  Created on: 2012-05-26
 *      Author: leo
 */

#ifndef PYUTILS_H_
#define PYUTILS_H_

#include <python2.7/Python.h>
#include <boost/python.hpp>
#include <string>

namespace fp_core {

class PyUtils {
public:
  PyUtils();

  static bool hasMethod(PyObject * obj, std::string method);

  static void call(PyObject * obj, std::string method);

  template<typename T>
  static boost::shared_ptr<T> string_constructor(std::string str) {
    return boost::shared_ptr<T>(new T(str));
  }
};

}
 /* namespace fp_core */
#endif /* PYUTILS_H_ */
