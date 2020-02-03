#include <boost/python.hpp>
#include <fruitpunch/PythonBindings/Common.h>
#include <fruitpunch/PythonBindings/Graphics.h>
#include <fruitpunch/PythonBindings/Elements.h>
#include <fruitpunch/PythonBindings/Resources.h>
#include <fruitpunch/PythonBindings/Physics.h>
#include <string.h>

using namespace boost::python;
using namespace fp_core::python;

namespace fp_core {


scope newModule(std::string module) {
  object newmodule(handle<>(borrowed(PyImport_AddModule(module.c_str()))));

  std::string modName = module.substr(module.find_last_of('.'));

  scope().attr(modName.c_str()) = newmodule;
  scope newscope = newmodule;
  return newscope;
}


/**
 * Makes the libfp_core package. Take a look at
 * http://isolation-nation.blogspot.com/2008/09/packages-in-python-extension-modules.html
 */

/*
BOOST_PYTHON_MODULE(libfp_core) {

  Common common;
  Elements elements;
  Graphics graphics;
  Resources resources;
  Physics physics;

  common.declareClasses();
  graphics.declareClasses();
  elements.declareClasses();
  resources.declareClasses();
  physics.declareClasses();

}*/



}
