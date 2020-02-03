#include <FpCoreTest.h>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <fruitpunch/Physics/PhysicsWorld.h>
#include <fruitpunch/Graphics/Primitive.h>
#include <fruitpunch/Graphics/Sprite.h>
#include <fruitpunch/Physics/PhysicsBox.h>
#include <fruitpunch/Physics/ContactEvent.h>
#include <fruitpunch/Physics/Body.h>
#include <fruitpunch/Elements/Element.h>
#include <fruitpunch/Common/Observer.h>
#include <fruitpunch/Elements/Scene.h>


using namespace std;
using namespace boost;
using namespace fp_core::physics;
using namespace fp_core;

// ---------------------------------------------------------------------------
// Stub Class
// ---------------------------------------------------------------------------

class MockFixture : public b2Fixture {
public:
	MockFixture(Element::ref * element, PhysicsWorld::ref world) {
		SetUserData(element);
	}
};

class MockContact : public b2Contact {
public:
	MockContact(Element::ref el1, Element::ref el2, PhysicsWorld::ref world) {
		m_fixtureA = world->getFixtureFromElement(el1);
		m_fixtureB = world->getFixtureFromElement(el2);
	}

	virtual void Evaluate(b2Manifold* manifold, const b2Transform& xfA, const b2Transform& xfB) {
	}
};

class ContactObserver : public Observer {
public:
	bool triggered;

	void action() {
		triggered = true;
	}
};

// ---------------------------------------------------------------------------
// Test Class
// ---------------------------------------------------------------------------

class ContactEventTest : public FpCoreTest {
protected:
  boost::shared_ptr<PhysicsWorld> world;

  virtual void SetUp() {
	initEnvironment();
	world = PhysicsWorld::ref(new PhysicsWorld());
	world->init();
  }
};

TEST_F(ContactEventTest, Constructor) {
	Element::ref sp1(new Sprite("pedoBear.png"));
	Element::ref sp2(new Sprite("pedoBear.png"));

	sp1->add(boost::shared_ptr<Body>(new Body()));
	sp2->add(boost::shared_ptr<Body>(new Body()));

	MockContact contact(sp1, sp2, world);

	ContactEvent ev(contact, "pre_collide", world);
	ASSERT_TRUE(ev.getElementA() == sp1);
	ASSERT_TRUE(ev.getElementB() == sp2);
}

TEST_F(ContactEventTest, getElement) {
	Scene::ref scene(new Scene());
	scene->add(world);
	Sprite::ref sp1(new Sprite("pedoBear.png"));
	Sprite::ref sp2(new Sprite("pedoBear.png"));

	scene->add(sp1);
	scene->add(sp2);

	sp1->setWidth(100);
	sp1->setHeight(100);

	sp1->setY(0);

	sp2->setWidth(100);
	sp2->setHeight(100);

	sp2->setY(150);

	Body::ref b1(new Body());
	Body::ref b2(new Body());

	b2->setType(Body::STATIC);

	sp1->add(b1);
	sp2->add(b2);

	boost::shared_ptr<Observer> obs(new ContactObserver());
	world->attachObserver("pre_solve", obs);

	// cycle a few frames to give it enough time for the event to fire.
	float sp1y = 0;
	float sp2y = 0;
	for (int i=700;i--;) {
		sp1y = sp1->getY();
		sp2y = sp2->getY();
		world->renderFrame();
		b1->renderFrame();
		b2->renderFrame();
	}

	ContactEvent::ref ev = static_pointer_cast<ContactEvent>(obs->getEvent());
	ASSERT_TRUE(static_pointer_cast<ContactObserver>(obs)->triggered);

	if (ev->getElementA() != sp1) {
		ASSERT_TRUE(ev->getElementA() == sp2);
	    ASSERT_TRUE(ev->getElementB() == sp1);
	} else {
		ASSERT_TRUE(ev->getElementA() == sp1);
	    ASSERT_TRUE(ev->getElementB() == sp2);
	}


}
