/*
 * Runtime.h
 *
 *  Created on: 2012-04-16
 *      Author: leo
 */

#ifndef RUNTIME_H_
#define RUNTIME_H_

#include <string>
#include <boost/shared_ptr.hpp>
#include <fruitpunch/Graphics/Renderer.h>
#include <fruitpunch/Common/RuntimeError.h>
#include <fruitpunch/Common/Object.h>
#include <fruitpunch/Graphics/Window.h>
#include <fruitpunch/Resources/Resource.h>
#include <fruitpunch/Resources/ResourceFactory.hpp>
#include <fruitpunch/Common/Observable.h>
#include <map>

#include <vector>

namespace fp_core {

class Renderer;
class Window;
class Resource;
class ResourceFactory;
class PyLoader;

namespace common {

class RuntimeError;
class NativeBridge;

// ---------------------------------------------------------------------------
// Class declaration
// ---------------------------------------------------------------------------

/// Initializes the FruitPunch library and makes it ready for use
/**
 * Contains instances of the window, pyloader, and controlfactory.
 * Is instantiated by the clients and is a one stop location for context
 * information.
 *
 * The client should be NEVER instantiate a runtime directly. Instead, he
 * should call Runtime::create() and then access the current runtime by
 * Runtime::current.
 */
class Runtime : public Observable {
public:
  typedef boost::shared_ptr<Runtime> ref;

  enum MsgLevel {
	  MSG_INFO, MSG_WARNING, MSG_ERROR
  };

  Runtime();
  virtual ~Runtime();

  // ---------------------------------------------------------------------------
  // Member Methods
  // ---------------------------------------------------------------------------

  /// Initializes the runtime object and associates it to the current runtime
  bool init(int width, int height, boost::shared_ptr<NativeBridge> bridge);

  /// Needs to be called by the client every time he wants a frame to be rendered
  bool renderFrame();

  /// Creates a new runtime error
  void addError(boost::shared_ptr<RuntimeError> error);

  /// Cleans all the errors that have been reported
  void flushErrors();

  /// Adds a new python path
  void addPythonPath(std::string path);

  /// Returns the full path taking into consideration the runtime path
  /**
   * For example, if the runtime path is
   *
   * /home/leo
   *
   * And the user passes an argument
   *
   * img/tuqui.png
   *
   * Then this function will return /home/leo/img/tuqui.png
   *
   * @param path
   * @return
   */
  std::string resolve(std::string path);

  /// Loads a resource from a file path
  /**
   * If the file path starts with a bar "/" it will not be modified. If it does
   * not, then it will be resolved relative to runtimeRoot
   *
   * @return
   */
  boost::shared_ptr<Resource> loadResource(std::string path);

  // ---------------------------------------------------------------------------
  // Static public members
  // ---------------------------------------------------------------------------

  /// Access to the current running runtime
  static boost::shared_ptr<Runtime> getCurrent();

  /// Creates a new current runtime. It still has to be initialized with init()
  static void create();

  /// Prints out a debug message
  static void print(std::string message, MsgLevel level);

  /// Sets an environment variable
  static void setEnv(std::string var, std::string value);

  /// Returns the current time in milliseconds
  static long getTimeInMs();

  // ---------------------------------------------------------------------------
  // Getters
  // ---------------------------------------------------------------------------
  std::vector<std::string>&                     getResourcePath();
  std::string                                   getPathSeparator() const;
  std::string                                   getPythonModule() const;
  boost::shared_ptr<PyLoader>					getPythonLoader() const;
  boost::shared_ptr<Renderer>                   getRenderer() const;
  std::vector<boost::shared_ptr<RuntimeError> > getErrors() const;
  std::string                                   getPythonDir() const;
  boost::shared_ptr<Window>                     getWindow() const;
  boost::shared_ptr<NativeBridge>               getBridge() const;
  std::string                                   getPythonHome() const;
  boost::shared_ptr<ResourceFactory>            getResourceFactory() const;
  int                                           getFps() const;
  const std::string&                            getRuntimeRoot() const;

  // ---------------------------------------------------------------------------
  // Setters
  // ---------------------------------------------------------------------------

  void setPathSeparator (std::string pathSeparator);
  void setPythonModule  (std::string pythonModule);
  void setRenderer      (boost::shared_ptr<Renderer> renderer);
  void setPythonDir     (std::string pythonDir);
  void setWindow        (boost::shared_ptr<Window> window);
  void setBridge        (boost::shared_ptr<NativeBridge> bridge);
  void setPythonHome    (std::string pythonHome);
  void setResourceFactory(boost::shared_ptr<ResourceFactory> resourceFactory);
  void setFps(int fps);
  void setRuntimeRoot   (const std::string& runtimeRoot);

  bool debug;
private:
    static boost::shared_ptr<Runtime>               mCurrentRuntime;
    std::map<std::string, boost::shared_ptr<Resource> >                mResourceMap;
    boost::shared_ptr<NativeBridge>                 mBridge;
    std::string                                     mRuntimeRoot;
    std::string                                     mPathSeparator;
    boost::shared_ptr<Renderer>                     mRenderer;
    std::string                                     mPythonModule;
    std::string                                     mPythonDir;
    std::vector<boost::shared_ptr<RuntimeError> >   mErrors;
    std::vector<std::string>                        mPythonPath;
    std::string                                     mPythonHome;
    boost::shared_ptr<PyLoader>                     mPyLoader;
    boost::shared_ptr<fp_core::Window>              mWindow;
    boost::shared_ptr<ResourceFactory>              mResourceFactory;
    std::vector<std::string>                        mResourcePath;
    int 											mFps;
    long                                            mLastTick;
    boost::shared_ptr<Event>                        mTickEvent;
};

} /* namespace common */
} /* namespace fp_core */
#endif /* RUNTIME_H_ */
