#include <FpCoreTest.h>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <fruitpunch/Physics/PhysicsWorld.h>
#include <fruitpunch/Graphics/Sprite.h>
#include <fruitpunch/Elements/Tween.h>
#include <fruitpunch/Common/Runtime.h>
#include <fruitpunch/Physics/Body.h>

using namespace std;
using namespace boost;
using namespace fp_core;
using namespace fp_core::physics;
using namespace fp_core::common;

// ---------------------------------------------------------------------------
// Test Class
// ---------------------------------------------------------------------------

class BodyTest : public FpCoreTest {
protected:
  PhysicsWorld::ref world;

  virtual void SetUp() {
    initEnvironment();
    world = PhysicsWorld::ref(new PhysicsWorld());
    world->init();
  }
};

TEST_F(BodyTest, create) {
  Body::ref body = Body::ref(new Body());

  // test class validation (it will only accept transformables)
  Sprite::ref transformable = Sprite::ref(new Sprite("pedoBear.png"));
  Tween::ref nonTransformable = Tween::ref(new Tween());

  ASSERT_EQ(0, Runtime::getCurrent()->getErrors().size());

  transformable->add(body);
  body->create();
  ASSERT_EQ(0, Runtime::getCurrent()->getErrors().size());

  nonTransformable->add(body);
  ASSERT_EQ(1, Runtime::getCurrent()->getErrors().size());
}

TEST_F(BodyTest, renderFrame) {
  Body::ref body = Body::ref(new Body());
  Sprite::ref transformable = Sprite::ref(new Sprite("pedoBear.png"));
  transformable->setX(0.0);
  transformable->setY(0.0);
  transformable->add(body);
  body->create();

  // run 10 frames
  for (int i=0; i < 10; i++) {
    world->renderFrame();
    body->renderFrame();
  }

  ASSERT_GT(transformable->getY(), 0.0);

}
