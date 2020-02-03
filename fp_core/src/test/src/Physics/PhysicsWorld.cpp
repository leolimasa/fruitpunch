#include <FpCoreTest.h>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <fruitpunch/Physics/PhysicsWorld.h>
#include <fruitpunch/Physics/PhysicsJoint.h>
#include <fruitpunch/Graphics/Primitive.h>
#include <fruitpunch/Graphics/Sprite.h>
#include <fruitpunch/Physics/PhysicsBox.h>
#include <fruitpunch/Physics/ContactEvent.h>
#include <fruitpunch/Common/Observer.h>
#include <Box2D/Box2D.h>

using namespace std;
using namespace boost;
using namespace fp_core::physics;
using namespace fp_core;
using namespace fp_core::common;

// ---------------------------------------------------------------------------
// Mockup classes
// ---------------------------------------------------------------------------
class MockupJoint : public PhysicsJoint {
public:
  bool added;

  MockupJoint(boost::shared_ptr<Element> a, boost::shared_ptr<Element> b) : PhysicsJoint(a, b), added(false) {

  }

  virtual boost::shared_ptr<b2JointDef> create() {
	  return boost::shared_ptr<b2JointDef>();
  }

  virtual void onAdd() {
    added = true;
  }
};

class ContactObserver : public Observer {
public:
	bool mTriggered;

	ContactObserver() {
		mTriggered = false;
	}

	virtual void action() {
		mTriggered = true;
	}
};

class MockContact2 : public b2Contact {
public:
	MockContact2(Element::ref el1, Element::ref el2, PhysicsWorld::ref world) {
		m_fixtureA = world->getFixtureFromElement(el1);
		m_fixtureB = world->getFixtureFromElement(el2);
	}

	virtual void Evaluate(b2Manifold* manifold, const b2Transform& xfA, const b2Transform& xfB) {
	}
};

// ---------------------------------------------------------------------------
// Test Class
// ---------------------------------------------------------------------------

class PhysicsWorldTest : public FpCoreTest {
protected:
  boost::shared_ptr<PhysicsWorld> world;

  virtual void SetUp() {
	initEnvironment();
	world = PhysicsWorld::ref(new PhysicsWorld());
	world->init();
  }
};

TEST_F(PhysicsWorldTest, init) {

	ASSERT_EQ(15.0f, world->getPixelSize());
	ASSERT_EQ(world, PhysicsWorld::getCurrent());
}

TEST_F(PhysicsWorldTest, makeShapeFor) {
	boost::shared_ptr<Primitive> pri(new Primitive());
	Sprite::ref sprite(new Sprite("pedoBear.png"));
	boost::shared_ptr<PhysicsBox> shape = static_pointer_cast<PhysicsBox>(world->makeShapeFor(sprite));

	// the shape width has to be equal to the physicsworld pixel size
	// divided by the width of the image
	float val = sprite->getWidth() / world->getPixelSize();

	ASSERT_TRUE(world->makeShapeFor(pri) == boost::shared_ptr<PhysicsShape>());
	ASSERT_EQ(val, shape->getWidth());
}

TEST_F(PhysicsWorldTest, triggerContact) {
	boost::shared_ptr<ContactObserver> obs(new ContactObserver());
	world->attachObserver("contact",static_pointer_cast<Observer>(obs));
	boost::shared_ptr<Element> el1(new Sprite("pedoBear.png"));
	boost::shared_ptr<Element> el2(new Sprite("pedoBear.png"));
	el1->add(boost::shared_ptr<Body>(new Body()));
	el2->add(boost::shared_ptr<Body>(new Body()));

	MockContact2 contact(el1, el2 , world);
	world->triggerContact(contact, "contact");
	ASSERT_TRUE(obs->mTriggered);
	boost::shared_ptr<ContactEvent> ev = static_pointer_cast<ContactEvent>(obs->getEvent());

	ASSERT_EQ(ev->getElementA(), el1);
	ASSERT_EQ(ev->getElementB(), el2);
}

TEST_F(PhysicsWorldTest, testAddJoint) {
  Sprite::ref pedo(new Sprite("pedoBear.png"));

  boost::shared_ptr<MockupJoint> joint(new MockupJoint(pedo, pedo));
  ASSERT_FALSE(joint->added);

  world->add(joint);

  ASSERT_TRUE(joint->added);

}
