#include <FpCoreTest.h>
#include <gtest/gtest.h>
#include <fruitpunch/Elements/Element.h>
#include <fruitpunch/Elements/Scene.h>
#include <fruitpunch/Elements/App.h>

using namespace boost;
using namespace fp_core;

// ---------------------------------------------------------------------------
// Test Class
// ---------------------------------------------------------------------------

class ElementImpl : public Element {
public:
	  typedef boost::shared_ptr<ElementImpl> ref;

      bool onAddCalled;
      bool onRemoveCalled;
      bool removeOnRenderFrame;
      bool destroyOnRenderFrame;


	  virtual void onAdd() {
		  onAddCalled = true;
	  }

	  virtual void onRemove() {
		  onRemoveCalled = true;
	  }

	  virtual void renderFrame() {
		  Element::renderFrame();

		  if (removeOnRenderFrame) {
			  getParent()->remove(getThis<Element>());
		  }

		  if (destroyOnRenderFrame) {
		    getParent()->destroy();
		  }
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

class SceneImpl3 : public Scene {
public:

  bool initCalled;
  bool destroyCalled;
  bool renderCalled;

  SceneImpl3() : Scene() {
    initCalled = false;
    destroyCalled = false;
    renderCalled = false;
  }

  virtual void onInit() {
    initCalled = true;
  }

  virtual void onDestroy() {
    destroyCalled = true;
  }

  virtual void onRender() {
    renderCalled = true;
  }

};

class ElementTest : public FpCoreTest {

protected:
  virtual void SetUp() {
	  initEnvironment();

  }
};

// ---------------------------------------------------------------------------
// Test Cases
// ---------------------------------------------------------------------------

TEST_F(ElementTest, addAndRemove) {
	ElementImpl::ref parent(new ElementImpl());
	ElementImpl::ref child(new ElementImpl());
	ElementImpl::ref child2(new ElementImpl());


	Scene::ref scene(new SceneImpl3());
	parent->setScene(scene);
	parent->add(child);

	ASSERT_EQ(1, parent->getChildren()->getSize());
	ASSERT_EQ(parent, child->getParent());
	ASSERT_TRUE(child->onAddCalled);
	ASSERT_EQ(scene, child->getScene());

	parent->add(child2);

	// checks the child / parent relationship
	ASSERT_EQ(2, parent->getChildren()->getSize());
	ASSERT_EQ(parent, child2->getParent());

	ElementImpl::ref child3(new ElementImpl());
	Element::ref removed;

	removed = parent->remove(child3);
	ASSERT_FALSE(removed);

	removed = parent->remove(child);

	// checks the child / parent relationship
	ASSERT_EQ(child, removed);
	ASSERT_EQ(1, parent->getChildren()->getSize());
	ASSERT_FALSE(child->getParent());
	ASSERT_TRUE(child->onRemoveCalled);

	parent->remove(child2);
	ASSERT_EQ(0, parent->getChildren()->getSize());
}

TEST_F(ElementTest, removeOnRenderFrame) {
#ifdef WIN32
	ASSERT_TRUE(false);
#else

	/**
	 * This test is designed to throw a segmentation fault
	 * if the remove algorithm is not implemented correctly.
	 *
	 * Essentially, if an element is removed from inside a
	 * renderElement() call, the parent has to update its
	 * iterator, since the old iterator is no longer valid.
	 */
	ElementImpl::ref root(new ElementImpl());
	ElementImpl::ref child1(new ElementImpl());
	ElementImpl::ref child2(new ElementImpl());

	root->add(child1);
	root->add(child2);

	ASSERT_EQ(child1->getParent(), root);
	ASSERT_EQ(2, root->getChildren()->getSize());

	child2->removeOnRenderFrame = true;

    root->renderFrame();

	ASSERT_EQ(1, root->getChildren()->getSize());
#endif
}

TEST_F(ElementTest, appSceneElementIntegration) {
#ifdef WIN32
	ASSERT_TRUE(false);
#else

	// tests a full blown environment, with app, scene and element

	boost::shared_ptr<AppImpl2> app(new AppImpl2());
	boost::shared_ptr<SceneImpl3> scene(new SceneImpl3());
	ElementImpl::ref element(new ElementImpl());

	app->init();
	app->goToScene(scene);
	scene->add(element);

	ASSERT_TRUE(scene->initCalled);
	ASSERT_TRUE(element->onAddCalled);
#endif
}

TEST_F(ElementTest, destroy) {
#ifdef WIN32
	ASSERT_TRUE(false);
#else
  ElementImpl::ref root(new ElementImpl());
  ElementImpl::ref child1(new ElementImpl());
  ElementImpl::ref child2(new ElementImpl());
  ElementImpl::ref child3(new ElementImpl());
  ElementImpl::ref zero();

  root->add(child1);
  child1->add(child2);
  child2->add(child3);

  ASSERT_EQ(root, child1->getParent());
  ASSERT_EQ(child1, child2->getParent());
  ASSERT_EQ(child2, child3->getParent());

  child1->destroy();

  ASSERT_FALSE(child1->getParent());
  ASSERT_FALSE(child2->getParent());
  ASSERT_FALSE(child3->getParent());

  // check destroy during a render frame
  root->add(child1);
  child1->add(child2);
  child1->add(child3);

  ASSERT_EQ(root, child1->getParent());
  ASSERT_EQ(child1, child2->getParent());
  ASSERT_EQ(child1, child3->getParent());

  child3->destroyOnRenderFrame = true;
  root->renderFrame();
  root->renderFrame();

  ASSERT_FALSE(child1->getParent());
  ASSERT_FALSE(child2->getParent());
  ASSERT_FALSE(child3->getParent());
#endif

}
