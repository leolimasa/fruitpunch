#include <FpCoreTest.h>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <fruitpunch/Physics/PhysicsWorld.h>
#include <fruitpunch/Physics/PhysicsJoint.h>
#include <fruitpunch/Physics/MouseJoint.h>
#include <fruitpunch/Physics/Body.h>
#include <fruitpunch/Graphics/Sprite.h>
#include <fruitpunch/Graphics/Primitive.h>
#include <fruitpunch/Elements/Element.h>
#include <fruitpunch/Common/Iterator.h>
#include <fruitpunch/Common/Vector.h>
#include <fruitpunch/Errors/InvalidChildrenError.h>

using namespace std;
using namespace boost;
using namespace fp_core::physics;
using namespace fp_core;
using namespace fp_core::common;

// ---------------------------------------------------------------------------
// Stub Class
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// Test Class
// ---------------------------------------------------------------------------
inline double round2(double x) { return floor(x + 0.5); }

class MouseJointTest : public FpCoreTest {
protected:
  boost::shared_ptr<PhysicsWorld> world;

  virtual void SetUp() {
	initEnvironment();
	world = PhysicsWorld::ref(new PhysicsWorld());
	world->init();
  }
};

TEST_F(MouseJointTest, Constructor) {
	boost::shared_ptr<Sprite> sp1(new Sprite("pedoBear.png")); // fakeground
	boost::shared_ptr<Sprite> sp2(new Sprite("pedoBear.png")); // pedobear

	// test with bodies
	Body::ref body1 = Body::ref(new Body());
	Body::ref body2 = Body::ref(new Body());

	sp1->add(body1);
	body1->create();
	body1->STATIC; // this is our ground...
	sp2->add(body2);
	body2->create();

	boost::shared_ptr<MouseJoint> mouseJoint(new MouseJoint(sp1, sp2));
	world->add(mouseJoint);
	boost::shared_ptr<Iterator> it = world->getChildren()->getIterator();

	bool found = false;
	 while (it->next()) {
		  if (it->get() == mouseJoint) {
		    found = true;
		  }
	  }
	ASSERT_TRUE(found);
	ASSERT_TRUE(mouseJoint->retrieveBodyA() == body1);
	ASSERT_TRUE(mouseJoint->retrieveBodyB() == body2);
}

TEST_F(MouseJointTest, update) {
	boost::shared_ptr<Sprite> sp1(new Sprite("pedoBear.png")); // fakeground
	boost::shared_ptr<Sprite> sp2(new Sprite("pedoBear.png")); // pedobear

	// test with bodies
	Body::ref body1 = Body::ref(new Body());
	Body::ref body2 = Body::ref(new Body());

	sp1->add(body1);
	body1->setType(Body::STATIC);
	body1->create();
	sp2->add(body2);
	body2->create();

	boost::shared_ptr<MouseJoint> mouseJoint(new MouseJoint(sp1, sp2));
	world->add(mouseJoint);

	point targetPoint;
	point returnPoint;
	targetPoint.x = 4.0f;
	targetPoint.y = 15.0f;

	mouseJoint->update(targetPoint);

	int i = 0;
	for (i=0; i < 100; i++) {
		world->renderFrame();
		body1->renderFrame();
		body2->renderFrame();
	}

	returnPoint = sp2->getPosition();

	point testPoint;
	testPoint.x = round2(returnPoint.x);
	testPoint.y = round2(returnPoint.y);

	ASSERT_EQ(targetPoint.x, testPoint.x);
	ASSERT_EQ(targetPoint.y, testPoint.y);
}

