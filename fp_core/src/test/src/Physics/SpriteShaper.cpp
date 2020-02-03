#include <FpCoreTest.h>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <fruitpunch/Physics/PhysicsWorld.h>
#include <fruitpunch/Physics/PhysicsBox.h>
#include <fruitpunch/Physics/SpriteShaper.h>
#include <fruitpunch/Graphics/Sprite.h>

using namespace std;
using namespace boost;
using namespace fp_core::physics;
using namespace fp_core;

// ---------------------------------------------------------------------------
// Test Class
// ---------------------------------------------------------------------------

class SpriteShaperTest : public FpCoreTest {
protected:

  virtual void SetUp() {
	initEnvironment();
  }
};

TEST_F(SpriteShaperTest, test) {
	boost::shared_ptr<Element> sp(new Sprite());
	boost::shared_ptr<Primitive> pri(new Primitive());
	SpriteShaper ss;
	ASSERT_TRUE(ss.test(sp));
	ASSERT_FALSE(ss.test(pri));
}

TEST_F(SpriteShaperTest, make) {
	boost::shared_ptr<Element> sp(new Sprite("pedoBear.png"));
	boost::shared_ptr<PhysicsWorld> world(new PhysicsWorld());
	SpriteShaper ss;
	world->setPixelSize(10);

	boost::shared_ptr<PhysicsBox> box = static_pointer_cast<PhysicsBox>(ss.make(sp, world));
	ASSERT_EQ(41.2f, box->getWidth());
	ASSERT_EQ(74.4f, box->getHeight());

}
