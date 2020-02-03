#include <FpCoreTest.h>
#include <gtest/gtest.h>
#include <fruitpunch/Elements/App.h>
#include <boost/shared_ptr.hpp>
#include <fruitpunch/Graphics/Renderer.h>
#include <main.h>

using namespace fp_core;
using namespace boost;
using namespace fp_core::common;

// ---------------------------------------------------------------------------
// Stub Classes
// ---------------------------------------------------------------------------

class AppImpl : public App {
public:
  bool initCalled;
  bool renderCalled;
  bool sceneChangeCalled;

  AppImpl() : App() {
    initCalled = false;
    renderCalled = false;
    sceneChangeCalled = false;
  }

  virtual void onInit() {
    initCalled = true;
  }

  virtual void onRender() {
    renderCalled = true;
  }

  virtual void onSceneChange() {
    sceneChangeCalled = true;
  }
};

class SceneImpl : public Scene {
public:
  bool initCalled;
  bool renderFrameCalled;
  bool destroyCalled;

  SceneImpl() : Scene() {
    initCalled = false;
    renderFrameCalled = false;
    destroyCalled = false;
  }

  void init() {
    initCalled = true;
  }

  virtual void renderFrame() {
    renderFrameCalled = true;
  }

  void destroy() {
    destroyCalled = true;
  }

  virtual void onInit() {

  }

  virtual void onDestroy() {

  }

  virtual void onRender() {

  }

};

// ---------------------------------------------------------------------------
// Test Class
// ---------------------------------------------------------------------------

class AppTest : public FpCoreTest {
protected:
  virtual void SetUp() {
//    Runtime::create();
//
//    shared_ptr<Window> win(new Window());
//    Runtime::getCurrent()->setWindow(win);
//    win->init(800,600, shared_ptr<Renderer>(new RendererImpl()));
    //Runtime::getCurrent()->setRenderer(shared_ptr<Renderer>(new RendererImpl()));

    initEnvironment();
    mApp = boost::shared_ptr<AppImpl>(new AppImpl);
    mApp->init();

  }

  boost::shared_ptr<AppImpl> mApp;

};

// ---------------------------------------------------------------------------
// Test Cases
// ---------------------------------------------------------------------------

TEST_F(AppTest, init) {
  ASSERT_TRUE(mApp->initCalled);
}

TEST_F(AppTest, renderFrame) {
  boost::shared_ptr<SceneImpl> scene(new SceneImpl());

  mApp->renderFrame();
  ASSERT_TRUE(mApp->renderCalled);

  // check if the runtime is calling the frame
  mApp->renderCalled = false;
  Runtime::getCurrent()->renderFrame();
  ASSERT_TRUE(mApp->renderCalled);

}

TEST_F(AppTest, goToScene) {
  boost::shared_ptr<SceneImpl> scene(new SceneImpl());
  boost::shared_ptr<SceneImpl> scene2(new SceneImpl());

  mApp->goToScene((boost::shared_ptr<Scene>) scene);
  ASSERT_EQ(scene, mApp->getCurrentScene());

  mApp->goToScene((boost::shared_ptr<Scene>) scene2);
  ASSERT_EQ(scene2, mApp->getCurrentScene());

  ASSERT_TRUE(mApp == scene2->getApp());
}
