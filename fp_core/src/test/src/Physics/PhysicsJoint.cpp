#include <FpCoreTest.h>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <fruitpunch/Physics/PhysicsWorld.h>
#include <fruitpunch/Physics/PhysicsJoint.h>
#include <fruitpunch/Physics/Body.h>
#include <fruitpunch/Graphics/Sprite.h>
#include <fruitpunch/Graphics/Primitive.h>
#include <fruitpunch/Elements/Element.h>
#include <fruitpunch/Errors/InvalidChildrenError.h>
#include <fruitpunch/Common/Runtime.h>
#include <fruitpunch/Errors/ErrorCodes.h>



using namespace std;
using namespace boost;
using namespace fp_core::physics;
using namespace fp_core;


// ---------------------------------------------------------------------------
// Stub Class
// ---------------------------------------------------------------------------


class FakeJoint : public PhysicsJoint {
public:
	typedef boost::shared_ptr<b2JointDef> ref;

	FakeJoint(boost::shared_ptr<Element> elementA, boost::shared_ptr<Element> elementB) :
		PhysicsJoint(elementA, elementB) {
	}
	ref create() {
		return boost::shared_ptr<b2JointDef>();
	}
private:

};


// ---------------------------------------------------------------------------
// Test Class
// ---------------------------------------------------------------------------

class PhysicsJointTest : public FpCoreTest {
protected:
  boost::shared_ptr<PhysicsWorld> world;

  virtual void SetUp() {
	initEnvironment();
	world = PhysicsWorld::ref(new PhysicsWorld());
	world->init();
  }
};

TEST_F(PhysicsJointTest, Constructor) {
	boost::shared_ptr<Runtime> runtime = Runtime::getCurrent();

	boost::shared_ptr<Sprite> sp1(new Sprite("pedoBear.png"));
	boost::shared_ptr<Sprite> sp2(new Sprite("pedoBear.png"));

	// no bodies so InvalidChildrenError should be thrown...
	boost::shared_ptr<FakeJoint> fakeJoint1(new FakeJoint(sp1, sp2));
	fakeJoint1->retrieveBodyA();
	fakeJoint1->retrieveBodyB();
	ASSERT_EQ(INVALID_PARENT_ERROR, runtime->getErrors()[0].get()->getCode());

	// test with bodies
	Body::ref body1 = Body::ref(new Body());
	Body::ref body2 = Body::ref(new Body());

	sp1->add(body1);
	body1->create();
	sp2->add(body2);
	body2->create();

	boost::shared_ptr<FakeJoint> fakeJoint2(new FakeJoint(sp1, sp2));

	ASSERT_TRUE(fakeJoint2->retrieveBodyA() == body1);
	ASSERT_TRUE(fakeJoint2->retrieveBodyB() == body2);
}
