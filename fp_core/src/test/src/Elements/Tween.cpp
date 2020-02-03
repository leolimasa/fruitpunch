#include <FpCoreTest.h>
#include <gtest/gtest.h>
#include <fruitpunch/Common/Property.h>
#include <fruitpunch/Graphics/Primitive.h>
#include <fruitpunch/Elements/Tween.h>
#include <boost/shared_ptr.hpp>

using namespace fp_core;
using namespace boost;
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

// ---------------------------------------------------------------------------
// Test Class
// ---------------------------------------------------------------------------

class TweenTest : public FpCoreTest {
protected:
  virtual void SetUp() {
	initEnvironment();
    alpha = boost::shared_ptr<Alpha>(new Alpha());
  }

  Tween mTween;
  boost::shared_ptr<Alpha> alpha;
};

// ---------------------------------------------------------------------------
// Test Cases
// ---------------------------------------------------------------------------

/**
 * Tests methods that have simple test cases
 */
TEST_F(TweenTest, renderSingle) {
  /**
   * CONSIDERATION: Tween is on the form [start_frame, end_frame)
   *
   * WHAT THAT MEANS: It means that end_frame is exclusive and start_frame is
   * inclusive.
   *
   * SO?: So, that means that, if you set a tween where the start frame is 0 and
   * the duration is 3, then the last frame will be 3. BUT, the tween will reach
   * its final value on frame 2.
   */


  mTween.setStartFrame(0);
  mTween.setDuration(5);
  mTween.setStartValue(0);
  mTween.setEndValue(10);
  mTween.setProperty(alpha);

  mTween.renderSingle(2);

  ASSERT_EQ(5.0f, alpha->get());

  mTween.renderSingle(0);

  ASSERT_EQ(0.0f, alpha->get());

  mTween.renderSingle(4);

  ASSERT_EQ(10.0f, alpha->get());

  mTween.setStartFrame(2);
  mTween.setDuration(7);
  mTween.setStartValue(4);
  mTween.setEndValue(16);
  mTween.setProperty(alpha);

  mTween.renderSingle(5);

  ASSERT_EQ(14.0f, alpha->get());
}
