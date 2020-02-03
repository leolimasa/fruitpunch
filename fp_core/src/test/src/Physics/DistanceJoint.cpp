#include <FpCoreTest.h>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <fruitpunch/Physics/PhysicsWorld.h>
#include <fruitpunch/Physics/PhysicsJoint.h>
#include <fruitpunch/Physics/DistanceJoint.h>
#include <fruitpunch/Physics/Body.h>
#include <fruitpunch/Graphics/Sprite.h>
#include <fruitpunch/Graphics/Primitive.h>
#include <fruitpunch/Elements/Element.h>
#include <fruitpunch/Common/Vector.h>
#include <fruitpunch/Common/Iterator.h>
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

class DistanceJointTest : public FpCoreTest {
protected:
  boost::shared_ptr<PhysicsWorld> world;

  virtual void SetUp() {
	initEnvironment();
	world = PhysicsWorld::ref(new PhysicsWorld());
	world->init();
  }
};

TEST_F(DistanceJointTest, Constructor) {
	boost::shared_ptr<Sprite> sp1(new Sprite("pedoBear.png"));
	boost::shared_ptr<Sprite> sp2(new Sprite("pedoBear.png"));

	// test with bodies
	Body::ref body1 = Body::ref(new Body());
	Body::ref body2 = Body::ref(new Body());

	sp1->add(body1);
	body1->create();
	sp2->add(body2);
	body2->create();

	boost::shared_ptr<DistanceJoint> distanceJoint(new DistanceJoint(sp1, sp2));

	ASSERT_TRUE(distanceJoint->retrieveBodyA() == body1);
	ASSERT_TRUE(distanceJoint->retrieveBodyB() == body2);
}

TEST_F(DistanceJointTest, onAdd) {
  boost::shared_ptr<Sprite> sp1(new Sprite("pedoBear.png"));
  boost::shared_ptr<Sprite> sp2(new Sprite("pedoBear.png"));

  sp1->add(boost::shared_ptr<Element>(new Body()));
  sp2->add(boost::shared_ptr<Element>(new Body()));

  boost::shared_ptr<DistanceJoint> distanceJoint(new DistanceJoint(sp1, sp2));

  world->add(distanceJoint);

  bool found = false;
  boost::shared_ptr<Iterator> it = world->getChildren()->getIterator();
  while (it->next()) {
	  if (it->get() == distanceJoint) {
	    found = true;
	  }
  }

  ASSERT_TRUE(found);
}

TEST_F(DistanceJointTest, onRemove) {
  boost::shared_ptr<Sprite> sp1(new Sprite("pedoBear.png"));
  boost::shared_ptr<Sprite> sp2(new Sprite("pedoBear.png"));

  sp1->add(boost::shared_ptr<Element>(new Body()));
  sp2->add(boost::shared_ptr<Element>(new Body()));

  boost::shared_ptr<DistanceJoint> distanceJoint(new DistanceJoint(sp1, sp2));

  world->add(distanceJoint);
  boost::shared_ptr<Iterator> it = world->getChildren()->getIterator();

  bool found = false;
  world->remove(distanceJoint);

  while (it->next()) {
	  if (it->get() == distanceJoint) {
	    found = true;
	  }
  }
  ASSERT_FALSE(found);
}


