/*
 * Runtime.cpp
 *
 *  Created on: 2012-04-16
 *      Author: leo
 */

#include <fruitpunch/Common/Runtime.h>
#include <fruitpunch/Common/RuntimeError.h>
#include <fruitpunch/Common/NativeBridge.h>
#include <fruitpunch/Common/Event.h>
#include <fruitpunch/Python/PyLoader.h>
#include <fruitpunch/Errors/PythonError.h>
#include <fruitpunch/Errors/ResourceLoadError.h>
#include <fruitpunch/Errors/IOError.h>
#include <fruitpunch/Resources/ResourceFactory.hpp>
#include <fruitpunch/Resources/Png.h>
#include <fruitpunch/Resources/Font.h>
#include <fruitpunch/Resources/Ogg.h>
#include <fruitpunch/Resources/Xml.h>
#include <fruitpunch/Resources/Resource.h>
#include <fruitpunch/Graphics/Renderer.h>
#include <fruitpunch/Graphics/Window.h>
#include <fruitpunch/version.h>
#include <fruitpunch/Common/Events.h>
#include <boost/chrono.hpp>
#include <boost/make_shared.hpp>

#include <fstream>

#ifndef WIN32
	#include <stdlib.h>
#else
	#include <Windows.h>
#endif
	

using namespace std;
using namespace fp_core::resources;

namespace fp_core {
namespace common {

boost::shared_ptr<Runtime> Runtime::mCurrentRuntime;

Runtime::Runtime() :
	Observable(),
	mLastTick(0),
    debug(false),
    mPyLoader(boost::shared_ptr<PyLoader>(new PyLoader())),
    mWindow(boost::shared_ptr<Window>(new Window())),
    mTickEvent(boost::shared_ptr<Event>(new Event(EV_TICK))) {
}

Runtime::~Runtime() {
}

void Runtime::print(string message, MsgLevel level) {
	string prefix;
	switch (level) {
	case Runtime::MSG_WARNING:
		prefix = "[WARNING] ";
		break;
	case Runtime::MSG_ERROR:
		prefix = "[ERROR] ";
		break;
	case Runtime::MSG_INFO:
		prefix = "[INFO] ";
		break;
	}

	cout << prefix << message << endl;
}

void Runtime::setEnv(string var, string value) {
	// since we are dealing with putenv, we have to use good ole C libraries
	string envStr = var + "=" + value;

	int success;
	#ifdef WIN32
		success = _putenv(envStr.c_str());
	#else
		success = setenv(var.c_str(), value.c_str(), 1);
	#endif

	if (success == 0) {
		print(envStr, MSG_INFO);
		return;
	} 
	print("Could not set the " + var + "variable", MSG_ERROR);
}

bool Runtime::init(int width, int height, boost::shared_ptr<NativeBridge> bridge) {

  cout << endl << "Initializing fp_core " << FP_CORE_VERSION_MAJOR << "." << FP_CORE_VERSION_MINOR << endl;

  mBridge = bridge;

  // --------------------------------------------------------------------------
  // Copies the PythonPath from the runtime to the loader
  // --------------------------------------------------------------------------
  vector<string>::iterator it;
  for (it = mPythonPath.begin(); it != mPythonPath.end(); it++) {
	mPyLoader->getPythonPath().push_back(*it);
  }

  // --------------------------------------------------------------------------
  // Resolves the python module name
  // --------------------------------------------------------------------------
  int loc = mPythonModule.rfind(mPathSeparator);
  string moduleName = mPythonModule.substr(loc + 1);
  mPyLoader->setModule(moduleName);
  print("Python module: " + moduleName, MSG_INFO);

  // --------------------------------------------------------------------------
  // Initializes the window and the python loader
  // --------------------------------------------------------------------------
  mWindow->init(width, height, mRenderer);
  try {
    if (!mPyLoader->startup(getThis<Runtime>())) {
      addError(mPyLoader->getError());
      return false;
    }
  } catch (const boost::python::error_already_set&) {
    boost::shared_ptr < RuntimeError
        > error(new PythonError(mPyLoader->getPythonError()));
    addError (error);
    return false;
  }
  return true;
}

bool Runtime::renderFrame() {
  try {
    mWindow->renderFrame();

     // fires a tick, if needed
     long ms = getTimeInMs();
	 if (ms - mLastTick > 1) {
		 notify(mTickEvent);
		 mLastTick = ms;
	 }

  } catch (const boost::python::error_already_set&) {
    boost::shared_ptr <RuntimeError> error(new PythonError(mPyLoader->getPythonError()));
    addError (error);
    return false;
  }

  if (mPyLoader->hasError()) {
    boost::shared_ptr<RuntimeError> error(new PythonError(mPyLoader->getPythonError()));
    addError (error);
    return false;
  }
  return true;
}

void Runtime::addError(boost::shared_ptr<RuntimeError> error) {
  mErrors.push_back(error);
  if (debug) {
	  print(error->getShortDescription(), Runtime::MSG_ERROR);
	  print(">>> " + error->getDescription(), Runtime::MSG_ERROR);
  }
}

long Runtime::getTimeInMs() {
	#ifdef WIN32
		return timeGetTime();
	#else
		struct timeval tv;
		gettimeofday(&tv, NULL);
		return tv.tv_sec * 1000 + tv.tv_usec / 1000;
	#endif
}

void Runtime::flushErrors() {
  mErrors.clear();
}

std::string Runtime::getPathSeparator() const {
  return mPathSeparator;
}

std::string Runtime::getPythonModule() const {
  return mPythonModule;
}

boost::shared_ptr<PyLoader> Runtime::getPythonLoader() const {
	return mPyLoader;
}


boost::shared_ptr<Renderer> Runtime::getRenderer() const {
  return mRenderer;
}

//std::string Runtime::getRuntimeRoot() const {
//  return mRuntimeRoot;
//}

void Runtime::setPathSeparator(std::string pathSeparator) {
  mPathSeparator = pathSeparator;
}

void Runtime::setPythonModule(std::string pythonModule) {
  mPythonModule = pythonModule;
}

void Runtime::setRenderer(boost::shared_ptr<Renderer> renderer) {
  mRenderer = renderer;
}

std::vector<boost::shared_ptr<RuntimeError> > Runtime::getErrors() const {
  return mErrors;
}

std::string Runtime::getPythonDir() const {
  return mPythonDir;
}

void Runtime::setPythonDir(std::string pythonDir) {
  mPythonDir = pythonDir;
}

void Runtime::addPythonPath(std::string path) {
  mPythonPath.push_back(path);
}

boost::shared_ptr<fp_core::Window> Runtime::getWindow() const {
  return mWindow;
}

void Runtime::setWindow(boost::shared_ptr<Window> window) {
  mWindow = window;
}

boost::shared_ptr<NativeBridge> Runtime::getBridge() const {
  return mBridge;
}

void Runtime::setBridge(boost::shared_ptr<NativeBridge> bridge) {
  mBridge = bridge;
}

std::string Runtime::getPythonHome() const {
  return mPythonHome;
}

boost::shared_ptr<Runtime> Runtime::getCurrent() {
  return mCurrentRuntime;
}

void Runtime::create() {
  boost::shared_ptr < Runtime > rt(new Runtime());
  mCurrentRuntime = rt;
  rt->setResourceFactory(
      boost::shared_ptr < ResourceFactory > (new ResourceFactory()));
  rt->getResourceFactory()->associate < Png > ("png");
  rt->getResourceFactory()->associate < Font > ("ttf");
  rt->getResourceFactory()->associate < Ogg > ("ogg");
  rt->getResourceFactory()->associate < Xml >("xml");
}

void Runtime::setPythonHome(std::string pythonHome) {
  mPythonHome = pythonHome;
}

boost::shared_ptr<ResourceFactory> Runtime::getResourceFactory() const {
  return mResourceFactory;
}

std::string Runtime::resolve(std::string path) {

  if (mPathSeparator.empty()) {
        printf(
            "WARNING: The path separator is empty. I hope you know what you are doing.\n");
  }

  // checks if its a full path
  if (path[0] == '/') {
    return path;
  }

  std::vector<std::string>::iterator it = mResourcePath.begin();
  for (; it != mResourcePath.end(); it++) {
    string root = *it;

    // checks if we need to append the separator
    if (root[root.length() - 1] != mPathSeparator.c_str()[0]) {
      root += mPathSeparator;
    }

    // checks if the file exists
    string fullPath = root + path;
    ifstream ifile;
    ifile.open(fullPath.c_str());
    print("Trying " + fullPath, Runtime::MSG_INFO);
    if (ifile.is_open()) {
      return fullPath;
    }

  }

  addError(IOError::ref(new IOError(path)));

  return "";
}

std::vector<std::string>& Runtime::getResourcePath() {
  return mResourcePath;
}

void Runtime::setResourceFactory(
    boost::shared_ptr<ResourceFactory> resourceFactory) {
  mResourceFactory = resourceFactory;
}

boost::shared_ptr<Resource> Runtime::loadResource(string path) {
  return mResourceFactory->loadResource(path);
}

int Runtime::getFps() const
{
    return mFps;
}

void Runtime::setFps(int fps)
{
	mFps = fps;
	mWindow->setFps(getFps());
}

} /* namespace common */
} /* namespace fp_core */

const std::string& Runtime::getRuntimeRoot() const {
	return mRuntimeRoot;
}

void Runtime::setRuntimeRoot(const std::string& runtimeRoot) {
	mRuntimeRoot = runtimeRoot;
}
