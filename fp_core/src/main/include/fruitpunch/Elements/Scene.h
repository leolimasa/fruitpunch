/*
 * Scene.h
 *
 *  Created on: 2012-05-06
 *      Author: leo
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <list>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/weak_ptr.hpp>
#include <fruitpunch/Common/Observable.h>
#include <fruitpunch/Graphics/Window.h>
#include <fruitpunch/Common/Runtime.h>
#include <fruitpunch/Elements/Element.h>

namespace fp_core {

class App;

/// Controls what is displayed on the screen and its underlying application logic.
/**
 * In an MVC model, the Scene can be considered the Controller. Only one scene
 * may be loaded at a time per application. Scenes are made up of Elements, that
 * attach to the scene's render event and therefore are able to encapsulate
 * fine grained application logic.
 * \n\n
 * Abstract class.
 */
class Scene : public Element {
public:
  typedef boost::shared_ptr<Scene> ref;

  Scene();

  // ---------------------------------------------------------------------------
  // Member methods
  // ---------------------------------------------------------------------------

  /// Called by the App to initialize the scene
  void init();

  /// Called by the App every time the current frame is rendered
  //void renderFrame();

  /// Called by the App when the scene is no longer needed
  void destroy();

  /// Adds an Element to the scene
  boost::shared_ptr<Element> add(boost::shared_ptr<Element> element);

  /// Removes an Element from the scene
 // boost::shared_ptr<Element> remove(boost::shared_ptr<Element> element);

  // ---------------------------------------------------------------------------
  // Callbacks
  // ---------------------------------------------------------------------------

  /// Called when the scene is initialized
  virtual void onInit();

  /// Called when the scene is destroyed
  virtual void onDestroy();

  /// Called every frame when the scene is on the screen
  //virtual void onRender();

  // ---------------------------------------------------------------------------
  // Getters
  // ---------------------------------------------------------------------------

  /// Returns a point representing the current absolute position of the pointer on the screen
  point getPointer();
  boost::shared_ptr<common::Runtime> getRuntime();
  boost::shared_ptr<Window> getWindow();
  boost::shared_ptr<App> getApp() const;
  std::list<boost::shared_ptr<Element> > getElements() const;
  int getWidth();
  int getHeight();

  // ---------------------------------------------------------------------------
  // Setters
  // ---------------------------------------------------------------------------
  void setApp(boost::weak_ptr<App> app);
  void setPointer(point pointer);
  void setPointerX(float x);
  void setPointerY(float y);

private:
  /**
   * Checks if this scene has a valid app, runtime, and window
   * @return true if its OK, false otherwise
   */
  bool checkIntegrity();

  std::list<boost::shared_ptr<Element> > mElements;
  boost::weak_ptr<App> mApp;
};

} /* namespace fp_core */
#endif /* SCENE_H_ */
