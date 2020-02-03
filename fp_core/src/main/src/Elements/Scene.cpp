/*
 * Scene.cpp
 *
 *  Created on: 2012-05-06
 *      Author: leo
 */

#include <fruitpunch/Elements/Scene.h>
#include <fruitpunch/Common/Events.h>
#include <fruitpunch/Common/Event.h>
#include <fruitpunch/Elements/Element.h>
#include <fruitpunch/Elements/App.h>
#include <fruitpunch/Errors/IntegrityError.h>
#include <fruitpunch/Common/Observable.h>

using namespace std;
using namespace fp_core::common;

namespace fp_core {

Scene::Scene() : Element() {

}

void Scene::init() {
  setScene(getThis<Scene>());
  notify(Event::ref(new Event(EV_INIT)));
  onInit();

}

void Scene::destroy() {
  onDestroy();
  notify(Event::ref(new Event(EV_DESTROY)));

  while (getChildren()->getSize() > 0) {
	  remove(getChildren()->getAndCast<Element>(0));
  }
}

boost::shared_ptr<App> Scene::getApp() const {
  return mApp.lock();
}

void Scene::setApp(boost::weak_ptr<App> app) {
  mApp = app;
}

Element::ref Scene::add(boost::shared_ptr<Element> element) {
  if (!checkIntegrity()) return Element::ref();
  return Element::add(element);
}

boost::shared_ptr<Runtime> Scene::getRuntime() {
  return Runtime::getCurrent();
}

boost::shared_ptr<Window> Scene::getWindow() {
  return getRuntime()->getWindow();
}

point Scene::getPointer() {
	return getWindow()->getPointer();
}

void Scene::setPointer(point pointer) {
	getWindow()->setPointer(pointer);
}

void Scene::setPointerX(float x) {
	getWindow()->setPointerX(x);
}

void Scene::setPointerY(float y) {
	getWindow()->setPointerY(y);
}

void Scene::onInit() {
}

void Scene::onDestroy() {
}

bool Scene::checkIntegrity() {
  boost::shared_ptr<App> app = getApp();

  bool hasError = !app || !getRuntime() || !getWindow();

  if (!hasError) return true;

  // Adds an error to the runtime IF we have one
  printf("Fatal error: the Scene has failed integrity check.");
  if (app && (bool) getRuntime()) {
    getRuntime()->addError(boost::shared_ptr<RuntimeError>(new IntegrityError("Scene", "App")));
  }

  return false;
}

std::list<boost::shared_ptr<Element> > Scene::getElements() const {
  return mElements;
}

int Scene::getWidth() {
	return getWindow()->getWindowWidth();
}

int Scene::getHeight() {
	return getWindow()->getWindowHeight();
}

}
/* namespace fp_core */
