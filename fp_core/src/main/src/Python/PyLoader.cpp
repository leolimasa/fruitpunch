/*
 * PyLoader.cpp
 *
 *  Created on: 2012-02-27
 *      Author: leo
 */

#include <python2.7/Python.h>
#include <fruitpunch/Common/Observable.h>
#include <fruitpunch/Common/Runtime.h>
#include <fruitpunch/Common/RuntimeError.h>
#include <fruitpunch/Common/Filesystem.h>
#include <fruitpunch/Graphics/Window.h>
#include <fruitpunch/Python/PyLoader.h>
#include <fruitpunch/Errors/FileError.h>
#include <fruitpunch/Errors/PythonError.h>
#include <fruitpunch/Errors/PythonPathError.h>
#include <fruitpunch/PythonBindings/Common.h>
#include <fruitpunch/PythonBindings/Graphics.h>
#include <fruitpunch/PythonBindings/Elements.h>
#include <fruitpunch/PythonBindings/Resources.h>
#include <fruitpunch/PythonBindings/Physics.h>
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::python;
using namespace fp_core::python;
using namespace fp_core::common;
using namespace boost::filesystem;

// Declare the libfp_core module
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
}

namespace fp_core {

PyLoader::PyLoader() {
	m_python_initialized = false;
	mFruitpunchImported = false;
	mPythonHome = NULL;
}

PyLoader::~PyLoader() {

}


bool PyLoader::init(boost::shared_ptr<Runtime> runtime) {
	PyObject *module, *file_name, *fun, *wargs;
		m_python_initialized = false;

		// ------------------------------------------------------------------------
		// Checks if we have a valid python file. If not, quit.
		// ------------------------------------------------------------------------
		if (!mModule.size()) {
			Runtime::getCurrent()->addError(boost::make_shared<PythonError>("No python script was specified."));
			return false;
		}

		// ------------------------------------------------------------------------
		// loads libfp_core into the namespace
		// ------------------------------------------------------------------------
		PyImport_AppendInittab("libfp_core",&initlibfp_core);

		// ------------------------------------------------------------------------
		// Startup the python interpreter
		// ------------------------------------------------------------------------
		loadEnvironmentVariables();
		Py_Initialize();
		m_python_initialized = true;

		#ifdef WIN32
				importPythonPath();
		#endif

		// ------------------------------------------------------------------------
	    // Creates the runtime python object
		// ------------------------------------------------------------------------
		initlibfp_core();
		object runtimePy(runtime);
		Py_IncRef(runtimePy.ptr());

		// ------------------------------------------------------------------------
		// loads the python file
		// ------------------------------------------------------------------------

		// takes away the .py if it has one - we just want the module name
		std::string extension = boost::algorithm::to_upper_copy(
				mModule.substr(mModule.size()-2));
		std::string module_name = mModule;
		if (extension.compare("PY") == 0) {
		  module_name = mModule.substr(0, mModule.size() - 3);
		}

		file_name = PyString_FromString(module_name.c_str());
		module = PyImport_Import(file_name);
		Py_DECREF(file_name);

		// checks if the file was loaded successfully
		if (module == NULL) {
		  if (this->hasError()) {
		    m_error = boost::shared_ptr<PythonError>(new PythonError(getPythonError()));
		  } else {
			m_error = boost::shared_ptr<FileError>(new FileError(module_name));
		  }
		  Runtime::getCurrent()->addError(m_error);
		  return false;
		}

		// ------------------------------------------------------------------------
		// Calls the init function
		// ------------------------------------------------------------------------
		fun = PyObject_GetAttrString(module, "init");
		if (!fun || !PyCallable_Check(fun)) {
			m_error = boost::shared_ptr<PythonError>(
					new PythonError("Could not find a init() function"));
			Runtime::getCurrent()->addError(m_error);
			return false;
		}

		wargs = PyTuple_New(1);
		PyTuple_SetItem(wargs, 0, runtimePy.ptr());

		try {
			PyObject_CallObject(fun, wargs);
		} catch (error_already_set const&) {
			m_error = boost::shared_ptr<PythonError>(new PythonError(getPythonError()));
			m_python_initialized = false;
			Runtime::getCurrent()->addError(m_error);
			return false;
		}

		// ------------------------------------------------------------------------
		// Clean up python memory
		// ------------------------------------------------------------------------
		Py_DECREF(wargs);
		Py_DecRef(fun);
		Py_DecRef(module);

		mFruitpunchImported = true;

		// ------------------------------------------------------------------------
		// Final check for errors
		// ------------------------------------------------------------------------
		if (hasError()) {
		  m_error = boost::shared_ptr<PythonError>(new PythonError(getPythonError()));
		  m_python_initialized = false;
		  Runtime::getCurrent()->addError(m_error);
		  return false;
		}

		return true;
}

void PyLoader::importPythonPath() {
	vector<string>::iterator it = mPythonPath.begin();
	eval("import sys");
	for (; it != mPythonPath.end(); it++) {
		try {
			string absolute = boost::filesystem::canonical(*it, Runtime::getCurrent()->getRuntimeRoot()).generic_string();
			eval("sys.path.append(\"" + absolute + "\")");
		} catch (exception &e) {
			Runtime::print("I could not find the following file in the PYTHONPATH: " + *it, Runtime::MSG_WARNING);
		}
	}
}

bool PyLoader::eval(string python) {
	try {
		char * runChar = new char[python.size()];
		strcpy(runChar,python.c_str());
		PyRun_SimpleString(runChar);
		return true;
	} catch (boost::python::error_already_set e) {
		string msg= parse_python_exception();
		Runtime::getCurrent()->addError(boost::shared_ptr<RuntimeError>(new PythonError(msg)));
		return false;
	}
}

bool PyLoader::startup(boost::shared_ptr<Runtime> runtime) {
	try {
		return init(runtime);
	} catch (boost::python::error_already_set e) {
		string msg= parse_python_exception();
		runtime->addError(boost::shared_ptr<RuntimeError>(new PythonError(msg)));
		return false;
	}
}

std::string PyLoader::parse_python_exception() {
	namespace py = boost::python;
	PyObject *type_ptr = NULL, *value_ptr = NULL, *traceback_ptr = NULL;
	PyErr_Fetch(&type_ptr, &value_ptr, &traceback_ptr);
	std::string ret("Unfetchable Python error");
	if (type_ptr != NULL) {
		py::handle<> h_type(type_ptr);
		py::str type_pstr(h_type);
		py::extract<std::string> e_type_pstr(type_pstr);
		if (e_type_pstr.check())
			ret = e_type_pstr();
		else
			ret = "Unknown exception type";
	}
	if (value_ptr != NULL) {
		py::handle<> h_val(value_ptr);
		py::str a(h_val);
		py::extract<std::string> returned(a);
		if (returned.check())
			ret += ": " + returned();
		else
			ret += std::string(": Unparseable Python error: ");
	}
	if (traceback_ptr != NULL) {
		/*PyObject * moduleName = PyString_FromString("traceback");
		PyObject * traceback = PyImport_Import(moduleName);
		Py_DECREF(moduleName);

		if (traceback == NULL) {
			ret += std::string("Could not import the traceback python module");
			return ret;
		}

		PyObject * formatException = PyObject_GetAttrString(traceback,"format_exception");
		if (formatException == NULL || !PyCallable_Check(formatException)) {
			ret += std::string("Could not retrieve traceback.format_exception()");
			return ret;
		}

		PyObject * result = PyObject_CallFunctionObjArgs(formatException, type_ptr, value_ptr, traceback_ptr, NULL);
		PyObject * resultStr = PyObject_Str(result);
		char * str = PyString_AsString(resultStr);
		ret += std::string(str); */

		py::handle<> h_tb(traceback_ptr);
		py::object tb(py::import("traceback"));
		py::object fmt_tb(tb.attr("format_tb"));
		py::object tb_list(fmt_tb(h_tb));
		py::object tb_str(py::str("\n").join(tb_list));
		py::extract<std::string> returned(tb_str);
		if (returned.check())
			ret += ": " + returned();
		else
			ret += std::string(": Unparseable Python traceback");
	}
	return ret;
}

// ____________________________________________________________________________

std::string PyLoader::makePythonPath() {

	#ifdef WIN32
		char sep = ';';
	#else
		char sep = ':';
	#endif

	string result = "";
	vector<string>::iterator it = mPythonPath.begin();
	for (; it != mPythonPath.end(); it++) {
		try {
			string absolute = boost::filesystem::canonical(*it, Runtime::getCurrent()->getRuntimeRoot()).generic_string();
			result += absolute + sep;
		} catch (exception &e) {
			Runtime::print("I could not find the following file in the PYTHONPATH: " + *it, Runtime::MSG_WARNING);
		}
	}

	// remove the last separator
	result = result.substr(0, result.length() - 1);
	return result;
}

// ____________________________________________________________________________

bool PyLoader::hasError() {
  if (!m_python_initialized) return false;
  return PyErr_Occurred() != NULL;
}

// ____________________________________________________________________________

bool PyLoader::reloadModule() {

  // DEAD CODE. THIS IS ONLY HERE IN CASE WE NEED A REFERENCE ON HOW
  // TO RESET THE PYTHON INTEPRETER IN THE FUTURE

  PyObject *module, *file_name, *fun, *wargs;

  // deallocates the old window object
//  Py_DecRef(mPythonWindow.ptr());
//  delete mPythonWindow.ptr();

  // Creates the window object
  //boost::python::object win(new Window);
  //mPythonWindow = object(new Window);

  //Py_IncRef(mPythonWindow.ptr());
  //m_window = extract<shared_ptr<Window> >(win);
  //m_window = extract<Window*>(win);

  // loads the python file
  // -- takes away the .py if it has one - we just want the module name
  std::string extension = boost::algorithm::to_upper_copy(
      mModule.substr(mModule.size() - 2));
  std::string module_name = mModule;

  if (extension.compare("PY") == 0) {
    module_name = mModule.substr(0, mModule.size() - 3);
  }

  file_name = PyString_FromString(module_name.c_str());

  // do we have to import it or reimport it?

  //module = PyImport_Import(file_name);
  object modulepy = boost::python::import(module_name.c_str());
  module = modulepy.ptr();
  Py_DECREF(file_name);

  if (module == NULL) {
    m_error = boost::shared_ptr<FileError>(new FileError(mModule));
    return false;
  }

  // loads the init function
  fun = PyObject_GetAttrString(module, "init");
  if (!fun || !PyCallable_Check(fun)) {
    //m_error = NO_INIT_FUNCTION;
    return false;
  }

  // creates a new argument with the window instance
  wargs = PyTuple_New(1);
  PyTuple_SetItem(wargs, 0, mPythonWindow.ptr());

  // calls the init function
  try {
    PyObject_CallObject(fun, wargs);
  } catch (error_already_set const&) {
    //m_error = PYTHON_ERROR;
    m_python_initialized = false;
    return false;
  }

  return true;
}

// ____________________________________________________________________________

void PyLoader::loadEnvironmentVariables() {
	string pypath = makePythonPath();
	Runtime::setEnv("PYTHONPATH", pypath);
	string pyhome = figureOutPythonHome();
	Runtime::setEnv("PYTHONHOME", pyhome);
	
	#ifdef WIN32
		char * writable = new char[pyhome.size() + 1];
		std::copy(pyhome.begin(), pyhome.end(), writable);
		writable[pyhome.size()] = '\0';
		Py_SetPythonHome(writable);
	#endif
}

// ____________________________________________________________________________

std::string PyLoader::figureOutPythonHome() {

	vector<string>::iterator it = mPythonPath.begin();
	string ospy = "";
	for (; it != mPythonPath.end(); it++) {
		try {
			// -----------------------------------------------------------------
			// Search for os.py
			// -----------------------------------------------------------------
			string absolute = boost::filesystem::canonical(*it, Runtime::getCurrent()->getRuntimeRoot()).generic_string();
			ospy = Filesystem::search("os.py", absolute,4);

			if (ospy == "") {
				continue;
			}

			// -------------------------------------------------------------
			// Check if the os.py is in a valid folder
			// -------------------------------------------------------------
			Runtime::print("Found os.py at " + ospy, Runtime::MSG_INFO);
			path ospyPath(ospy);

			#ifdef WIN32
				string filename = boost::to_lower_copy(ospyPath.parent_path().filename().generic_string());
				if (filename != "lib") {
					continue;
				}
				string finalPath = ospyPath.parent_path().parent_path().generic_string();

				// replace the slashes for windows slashes
				boost::algorithm::replace_all(finalPath, "/","\\");

				return finalPath;
			#else
				Runtime::print("Looking for a PYTHONHOME in lib/python2.7", Runtime::MSG_INFO);
				if (ospyPath.parent_path().filename() != "python2.7"
						|| ospyPath.parent_path().parent_path().filename() != "lib") {
					continue;
				}

				return ospyPath.parent_path().parent_path().parent_path().generic_string();
			#endif

		} catch (exception& e) {
			continue;
		}	
	}

	Runtime::getCurrent()->addError(boost::shared_ptr<RuntimeError>(new PythonPathError()));
	return "";

}

// ============================================================================
// Getters and Setters
// ============================================================================

void PyLoader::setModule(std::string file) {
	mModule = file;
}

boost::shared_ptr<RuntimeError> PyLoader::getError() const {
	return m_error;
}

void PyLoader::setError(boost::shared_ptr<RuntimeError> error) {
	m_error = error;
}


std::string PyLoader::getPythonError() {
	return parse_python_exception();
}

void PyLoader::addPath(std::string path) {
	mPythonPath.push_back(path);
}

std::vector<std::string>& PyLoader::getPythonPath() {
	return mPythonPath;
}

std::string PyLoader::getModule() const {
	return mModule;
}


}

