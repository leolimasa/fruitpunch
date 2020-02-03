/*
 * App.h
 *
 *  Created on: 2012-05-06
 *      Author: leo
 */

#ifndef APP_H_
#define APP_H_

#include <fruitpunch/Elements/Scene.h>
#include <fruitpunch/Common/Runtime.h>
#include <fruitpunch/Common/Observable.h>
#include <boost/shared_ptr.hpp>

namespace fp_core {

class App : public common::Observable {
public:

  // ---------------------------------------------------------------------------
  // Member Methods
  // ---------------------------------------------------------------------------

  App();

  /// Associates the app to the runtime
  /**
   * Associates this App to the runtime by attaching the renderFrame to
   * the current runtime PRE_RENDER event.
   *
   * Fires: EV_INIT
   *
   * @param runtime
   */
  void init();

  /// Renders the frame of the current scene, if there is one
  void renderFrame();

  /// Unloads the currently loaded scene and loads a new one
  void goToScene(boost::shared_ptr<Scene> scene);

  /// Method to be implemented by the client
  virtual void onInit();

  /// Method to be implemented by the client
  virtual void onRender();

  /// Method to be implemented by the client
  virtual void onSceneChange();

  /// Executed on every tick of the runtime
  virtual void tick();
  // ---------------------------------------------------------------------------
  // Getters
  // ---------------------------------------------------------------------------

  boost::shared_ptr<Scene> getCurrentScene() const;
  boost::shared_ptr<common::Runtime> getRuntime() const;

  // ---------------------------------------------------------------------------
  // Setters
  // ---------------------------------------------------------------------------

  void setCurrentScene(boost::shared_ptr<Scene> currentScene);

private:
  boost::shared_ptr<Scene> mCurrentScene;
};

} /* namespace fp_core */
#endif /* APP_H_ */
