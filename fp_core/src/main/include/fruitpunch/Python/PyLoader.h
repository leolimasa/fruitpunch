/*
 * PyLoader.h
 *
 *  Created on: 2012-02-27
 *      Author: leo
 */

#ifndef PYLOADER_H_
#define PYLOADER_H_

#include <boost/shared_ptr.hpp>
#include <boost/python.hpp>
#include <string>
#include <fruitpunch/Graphics/Window.h>
#include <fruitpunch/Common/Runtime.h>


namespace fp_core {

namespace common {
    class RuntimeError;
}

// ---------------------------------------------------------------------------
// Class Declaration
// ---------------------------------------------------------------------------

/// Loads, binds, and controls Python in the library
/**
 * Its main function is to load the python library, and create a valid window
 * object that will serve as the mediator between the client and the python
 * code.
 */
class PyLoader {
public:
  PyLoader();
  virtual ~PyLoader();

  // ---------------------------------------------------------------------------
  // Member Methods
  // ---------------------------------------------------------------------------
  /// Main method of this class. Loads the python file and creates the window
  /**
   * The client should call this method when it is ready to have the engine
   * going. When called, startup() will try to load the file specified by
   * setFile(), create a new Window instance, and try to execute the init(window)
   * function inside that python file.
   *
   * @return True if no errors are found, false otherwise
   */
  bool startup(boost::shared_ptr<fp_core::common::Runtime> runtime);

  /**
   * Returns a string with all the mPythonPaths concatenated. If the path is
   * relative, then it will be converted to absolute automatically. The array
   * will be changed with the absolute value.
   */
  std::string makePythonPath();

  /// Sets the PYTHONPATH and PYTHONHOME environment variables
  void loadEnvironmentVariables();

  /// Evaluates a line of python in the interpreter. Returns false on error.
  bool eval(std::string python);

  /// Forcibly inserts the resolved contents of mPythonPath into sys.path
  void importPythonPath();

  /**
    * Imports the libfp_core into the python namespace
	*/
  bool importLibfpcore();

  /// Appends a path to the current PYTHONPATH
  void addPath(std::string path);

  /// Checks if a Python error has occured
  bool hasError();

  /// Reloads the module set by the module property
  /**
   * This will throw away the current window and generate a new one. Then it will
   * try to reload the module specified in mModule
   * @return if there is an error
   */
  bool reloadModule();

  /// Searches the python path array for os.py and returns the directory
  /**
   * Attemps to automatically detect where the python path is located for the
   * runtime. The python path set by addPath() will be searched for os.py.
   * To be a valid path, that file must be inside the lib folder in windows, and
   * on python27/lib on linux. If nothing can be found, it will return an
   * empty string.
   *
   * The search is recursive on the directories, but it will only go 4 levels
   * deep at max.
   */
  std::string figureOutPythonHome();


  // ---------------------------------------------------------------------------
  // Getters
  // ---------------------------------------------------------------------------
  std::string               getModule() const;
  boost::shared_ptr<common::RuntimeError> getError() const;
  std::string               getPythonError();
  std::vector<std::string>& getPythonPath();

  // ---------------------------------------------------------------------------
  // Setters
  // ---------------------------------------------------------------------------
  void                      setModule(std::string file);
  void                      setError(boost::shared_ptr<common::RuntimeError> error);


private:
  std::string                             mModule;
  bool                                    m_python_initialized;
  bool                                    mFruitpunchImported;
  bool init(boost::shared_ptr<fp_core::common::Runtime> rt);
  boost::shared_ptr<common::RuntimeError> m_error;
  std::string                             m_python_error;
  std::vector<std::string>                mPythonPath;
  boost::python::object                   mPythonWindow;
  char *								  mPythonHome;
  // ---------------------------------------------------------------------------
  // Private Member Methods
  // ---------------------------------------------------------------------------

  /// Returns a python exception in a human readable format
  /**
   * It checks if there are any errors messages in the Python C API. If there
   * are, it takes it and tries to return a meaningful error message.
   *
   * @return
   */
  std::string               parse_python_exception();

};
}
#endif /* PYLOADER_H_ */
