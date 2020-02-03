#include <gtest/gtest.h>
#include <fruitpunch/Elements/Animation.h>
#include <boost/shared_ptr.hpp>
#include <fruitpunch/Elements/Tween.h>
#include <FpCoreTest.h>

using namespace boost;
using namespace fp_core;
using namespace fp_core::common;

// ---------------------------------------------------------------------------
// Stub Classes
// ---------------------------------------------------------------------------

class Alpha : public Property {
public:
  bool renderSingleCalled;
  float val;

  Alpha() {
  }

  virtual float get() {
    return val;
  }

  virtual void set(float alpha) {
    val = alpha;
  }

};

class AnimationImpl : public Animation {
  virtual void onInit() {

  }

  virtual void onDestroy() {

  }
};

// ---------------------------------------------------------------------------
// Test Class
// ---------------------------------------------------------------------------

class AnimationTest : public FpCoreTest {
public:
  boost::shared_ptr<Animation> anim;
  boost::shared_ptr<Tween> t1;
  boost::shared_ptr<Tween> t2;
  boost::shared_ptr<MockEnvironment> mEnvironment;


protected:
  virtual void SetUp() {
	initEnvironment();

    t1 = boost::shared_ptr<Tween>(new Tween);
    t2 = boost::shared_ptr<Tween>(new Tween);

    t1->setStartFrame(3);
    t1->setDuration(3);

    t2->setStartFrame(0);
    t2->setDuration(4);

    anim = boost::shared_ptr<Animation>(new AnimationImpl);
    anim->add(t1);
    anim->add(t2);
  }
};

// ---------------------------------------------------------------------------
// Test Cases
// ---------------------------------------------------------------------------

TEST_F(AnimationTest, calculateDuration) {
  ASSERT_EQ(6, anim->calculateDuration());

  anim->setStartFrame(3);

  ASSERT_EQ(6, anim->calculateDuration());
}

TEST_F(AnimationTest, renderSingle) {
  boost::shared_ptr<Property> a1(new Alpha);
  boost::shared_ptr<Property> a2(new Alpha);
  anim->start();
  anim->setStartFrame(0);

  t1->setProperty(a1);
  t1->setStartValue(0);
  t1->setEndValue(2);

  t2->setProperty(a2);
  t2->setStartValue(4);
  t2->setEndValue(8);

  anim->setCurrentFrame(3);
  anim->tick();

  ASSERT_EQ(0.0f, a1->get());
  ASSERT_EQ(8.0f, a2->get());

  anim->setCurrentFrame(8);
  anim->tick();

  ASSERT_EQ(0.0f, a1->get());
  ASSERT_EQ(8.0f, a2->get());

  anim->setLoop(true);
  anim->start();
  anim->setCurrentFrame(10);
  anim->tick();

  // should be equal to frame 4
  ASSERT_EQ(1.0f, a1->get());
  ASSERT_EQ(4.0f, a2->get());

}

TEST_F(AnimationTest, tick) {
  boost::shared_ptr<Property> a1(new Alpha);
  boost::shared_ptr<Property> a2(new Alpha);

  anim->setStartFrame(0);

  t1->setProperty(a1);
  t1->setStartValue(0);
  t1->setEndValue(2);

  t2->setProperty(a2);
  t2->setStartValue(4);
  t2->setEndValue(8);

  anim->start();

  anim->tick();
  anim->tick();
  anim->tick();
  anim->tick();

  ASSERT_EQ(0.0f, a1->get());
  ASSERT_EQ(8.0f, a2->get());


}
