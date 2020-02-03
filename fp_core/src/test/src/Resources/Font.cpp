#include <FpCoreTest.h>
#include <fruitpunch/Common/Runtime.h>
#include <fruitpunch/Resources/lodepng.h>
#include <fruitpunch/Resources/Font.h>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
#include <gtest/gtest.h>
#include <fruitpunch/Resources/Raw.h>

using namespace fp_core;
using namespace boost;
using namespace std;
using namespace fp_core::common;

// ---------------------------------------------------------------------------
// Test Class
// ---------------------------------------------------------------------------

class FontTest : public FpCoreTest {
protected:
  string mPath;

  virtual void SetUp() {
	initEnvironment();
  }

  void compare(boost::shared_ptr<Image> image, Raw& fixture) {
    for (int i=0; i<image->getData()->size(); i++) {
      char saved = (*fixture.getData())[i];
      char test = (*image->getData())[i];

      // we want some error margin, just in case we change antialias
      ASSERT_LT(fabs((double)(saved - test)), 3);
    }
  }
};

// ---------------------------------------------------------------------------
// Test Cases
// ---------------------------------------------------------------------------

TEST_F(FontTest, makeImage) {
#ifdef WIN32
	ASSERT_TRUE(false);
#else
  Font font;
  string fullPath = mEnvironment->mFullResourcePath + "Ubuntu-R.ttf";
  font.load(fullPath);

  string testStr = "Finally, a game engine\nMade for DEVELOPERS.\nFruitPunch.";
  font.setColor(boost::shared_ptr<Color>(new Color(0xAAAAFFBB)));

  // makes the tests
  font.setAlignment(Font::LEFT);
  boost::shared_ptr<Image> left = font.makeImage(testStr);
  printf("(%d,%d)", left->getWidth(), left->getHeight());

  font.setAlignment(Font::CENTER);
  boost::shared_ptr<Image> center = font.makeImage(testStr);

  font.setAlignment(Font::RIGHT);
  boost::shared_ptr<Image> right = font.makeImage(testStr);

  // loads the fixtures
  Raw leftfile;
  leftfile.load(mEnvironment->mFullResourcePath + "font_test_left.dat");

  Raw centerfile;
  centerfile.load(mEnvironment->mFullResourcePath + "font_test_center.dat");

  Raw rightfile;
  rightfile.load(mEnvironment->mFullResourcePath + "font_test_right.dat");

  // compare pixels
  compare(left, leftfile);
  compare(center, centerfile);
  compare(right, rightfile);
#endif
}
