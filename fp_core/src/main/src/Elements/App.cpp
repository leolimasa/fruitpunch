/*
 * App.cpp
 *
 *  Created on: 2012-05-06
 *      Author: leo
 */

#include <fruitpunch/Elements/App.h>
#include <fruitpunch/Common/Events.h>
#include <fruitpunch/Common/Event.h>
#include <fruitpunch/Common/Observer.h>
#include <boost/make_shared.hpp>

using namespace fp_core::common;

namespace fp_core {

class RenderObserver : public Observer {
public:
  App * app;

  void action() {
    app->renderFrame();
  }
};

class TickObserver : public Observer {
public:
	App * app;

	void action() {
		app->tick();
	}
};

App::App() : Observable() {
  // TODO Auto-generated constructor stub

}

void App::init() {
  boost::shared_ptr<RenderObserver> obs(new RenderObserver());
  boost::shared_ptr<TickObserver> tickobs(new TickObserver());
  obs->app = this;
  tickobs->app = this;
  Runtime::getCurrent()->getWindow()->attachObserver(EV_PRE_RENDER, obs);
  Runtime::getCurrent()->attachObserver(EV_TICK, tickobs);
  notify(Event::ref(new Event(EV_INIT)));
  onInit();

}

void App::renderFrame() {
  if (mCurrentScene) {
    mCurrentScene->renderFrame();
  }
  notify(Event::ref(new Event(EV_RENDER)));
  onRender();
}

void App::tick() {
	notify(boost::make_shared<Event>(EV_TICK));

	if (mCurrentScene) {
		mCurrentScene->tick();
	}
}

void App::goToScene(boost::shared_ptr<Scene> scene) {
  if (mCurrentScene) {
    mCurrentScene->destroy();
  }
  mCurrentScene = scene;
  mCurrentScene->setApp(getThis<App>());
  mCurrentScene->init();
  notify(Event::ref(new Event(EV_CHANGE_SCENE)));
  onSceneChange();
}

boost::shared_ptr<Scene> App::getCurrentScene() const
{
    return mCurrentScene;
}

boost::shared_ptr<Runtime> App::getRuntime() const
{
    return Runtime::getCurrent();
}

void App::onInit() {
}

void App::onRender() {
}

void App::onSceneChange() {
}

void App::setCurrentScene(boost::shared_ptr<Scene> currentScene)
{
    mCurrentScene = currentScene;
}

} /* namespace fp_core */
