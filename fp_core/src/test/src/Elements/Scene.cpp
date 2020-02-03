#include <FpCoreTest.h>
#include <gtest/gtest.h>
#include <fruitpunch/Elements/Animation.h>
#include <boost/shared_ptr.hpp>
#include <fruitpunch/Elements/Tween.h>
#include <fruitpunch/Graphics/Sprite.h>
#include <fruitpunch/Elements/App.h>
#include <fruitpunch/Common/Runtime.h>
#include <fruitpunch/Common/Events.h>
#include <fruitpunch/Common/Observer.h>

using namespace boost;
using namespace fp_core;
using namespace fp_core::common;

// ---------------------------------------------------------------------------
// Stub Classes
// ---------------------------------------------------------------------------

class SceneObserver : public Observer {
public:
	void virtual action() {
		boost::shared_ptr<Scene> scene = static_pointer_cast<Scene>(getInstance());
		ASSERT_EQ(scene->getScene(), scene);
	}
};

class AppImpl2 : public App {
public:
  bool initCalled;
  bool renderCalled;
  bool sceneChangeCalled;

  AppImpl2() : App() {
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


class Pri : public Primitive {
public:
  int framesRendered;

  virtual void renderFrame() {
    framesRendered++;
  }
};

class SceneImpl2 : public Scene {
public:

  bool initCalled;
  bool destroyCalled;
  bool renderCalled;

  SceneImpl2() : Scene() {
    initCalled = false;
    destroyCalled = false;
    renderCalled = false;
  }

  virtual void onInit() {
    initCalled = true;

    // make sure the scene initializes its elements before init
    ASSERT_EQ(getScene(), getThis<Scene>());
  }

  virtual void onDestroy() {
    destroyCalled = true;
  }

  virtual void onRender() {
    renderCalled = true;
  }

};

// ---------------------------------------------------------------------------
// Test Class
// ---------------------------------------------------------------------------

class SceneTest : public FpCoreTest {
public:
  boost::shared_ptr<Scene> mScene;
  boost::shared_ptr<Pri> mP1;
  boost::shared_ptr<Pri> mP2;

protected:
  virtual void SetUp() {
	initEnvironment();

    mP1 = boost::shared_ptr<Pri>(new Pri());
    mP2 = boost::shared_ptr<Pri>(new Pri());

    mScene = boost::shared_ptr<Scene>(new SceneImpl2());
    mScene->attachObserver(EV_INIT, boost::shared_ptr<Observer>(new SceneObserver()));
    mScene->init();

  }
};

// ---------------------------------------------------------------------------
// Test Cases
// ---------------------------------------------------------------------------

TEST_F(SceneTest, add) {
  mScene->add((boost::shared_ptr<Primitive>) mP1);

  // the scene is not associated with a runtime, so do not expect add to work
  ASSERT_EQ(0, mScene->getChildren()->getSize());

  // make the scene as its supposed to be
  boost::shared_ptr<AppImpl2> app(new AppImpl2);
  mScene->setApp(app);

  // now we should be good
  mScene->add(mP1);
  ASSERT_EQ(1, mScene->getChildren()->getSize());
}

TEST_F(SceneTest, remove) {
  // make the scene as its supposed to be
  boost::shared_ptr<AppImpl2> app(new AppImpl2);
  mScene->setApp(app);

  // add the element
  mScene->add(mP1);
  ASSERT_EQ(1, mScene->getChildren()->getSize());

  // remove the element
  boost::shared_ptr<Element> copy = mP1;
  mScene->remove(copy);
  ASSERT_EQ(0, mScene->getChildren()->getSize());
}

TEST_F(SceneTest, removeTwo) {
  // make the scene as its supposed to be
  boost::shared_ptr<AppImpl2> app(new AppImpl2);
  mScene->setApp(app);

  // add the element
  mScene->add(mP1);
  ASSERT_EQ(1, mScene->getChildren()->getSize());
  mScene->add(mP2);
  ASSERT_EQ(2, mScene->getChildren()->getSize());

  // remove the element
  boost::shared_ptr<Element> copy = mP1;
  mScene->remove(copy);
  ASSERT_EQ(1, mScene->getChildren()->getSize());

  boost::shared_ptr<Element> copy2 = mP2;
  mScene->remove(copy2);
  ASSERT_EQ(0, mScene->getChildren()->getSize());
}

TEST_F(SceneTest, renderFrame) {
  // Initialize the scene
  boost::shared_ptr<AppImpl2> app(new AppImpl2);
  app->goToScene(mScene);

  mScene->add((boost::shared_ptr<Primitive>) mP1);
  ASSERT_EQ(0, mP1->framesRendered);

  mScene->renderFrame();

  ASSERT_EQ(1, mP1->framesRendered);

  mScene->add((boost::shared_ptr<Primitive>) mP2);
  mScene->renderFrame();
  ASSERT_EQ(2, mP1->framesRendered);
  ASSERT_EQ(1, mP2->framesRendered);

  // check if the app is rendering our scene
  boost::shared_ptr<SceneImpl2> scene = static_pointer_cast<SceneImpl2>(mScene);
  scene->renderCalled = false;
  app->renderFrame();
  ASSERT_TRUE(scene->renderCalled);
  ASSERT_EQ(3, mP1->framesRendered);
}

TEST_F(SceneTest, destroy) {
	// Initialize the scene
    boost::shared_ptr<AppImpl2> app(new AppImpl2);
	app->goToScene(mScene);

	mScene->add((boost::shared_ptr<Primitive>) mP1);
	mScene->add((boost::shared_ptr<Primitive>) mP2);

	// now are testing destroy
	mScene->destroy();

	// well we should probably check for something...
	//ASSERT_NO_FATAL_FAILURE();
}
