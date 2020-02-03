#include <FpCoreTest.h>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <fruitpunch/Resources/Raw.h>
#include <fruitpunch/Physics/PhysicsBox.h>

using namespace std;
using namespace boost;
using namespace fp_core::physics;

// ---------------------------------------------------------------------------
// Test Class
// ---------------------------------------------------------------------------

class PhysicsBoxTest : public FpCoreTest {
protected:
  string mPath;

  virtual void SetUp() {
	initEnvironment();
  }
};

TEST_F(PhysicsBoxTest, Constructor) {
	PhysicsBox box(300,400);
	boost::shared_ptr<b2PolygonShape> shape = static_pointer_cast<b2PolygonShape>(box.getBox2dShape(1.0f));
	ASSERT_EQ(4, shape->GetVertexCount());
	ASSERT_EQ(300, shape->GetVertex(1).x - shape->GetVertex(0).x);
	ASSERT_EQ(400, shape->GetVertex(2).y - shape->GetVertex(0).y);
}
