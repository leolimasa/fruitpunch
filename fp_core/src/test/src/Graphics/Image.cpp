#include <FpCoreTest.h>
#include <gtest/gtest.h>
#include <fruitpunch/Graphics/Image.h>
#include <fruitpunch/Resources/lodepng.h>
#include <boost/shared_ptr.hpp>
#include <vector>

using namespace boost;
using namespace std;

using namespace fp_core;

class ImageTest : public FpCoreTest {
protected:
  Image img;

  virtual void SetUp() {
	  initEnvironment();
  }

  virtual void loadMask() {
      boost::shared_ptr<vector<unsigned char> > data(new vector<unsigned char>);

      // 2x2 8bpp image = 4 pixels = 4 bytes
      data->push_back(255);
      data->push_back(128);
      data->push_back(64);
      data->push_back(0);

      img.setFormat(Image::MASK);
      img.setData(data);
      img.setWidth(2);
      img.setHeight(2);
  }

  // if A is true, then loads the alpha channel too, making it RGBA
  virtual void loadRGB(bool a = false) {
      // 2x2 RGBA image = 4 pixels = 16 bytes
      boost::shared_ptr<vector<unsigned char> > data(new vector<unsigned char>);

      // First pixel - RED - 0x0
      data->push_back(255);
      data->push_back(0);
      data->push_back(0);
      if (a) data->push_back(255);

      // Second pixel - GREEN - 0x1
      data->push_back(0);
      data->push_back(200);
      data->push_back(0);
      if (a) data->push_back(255);

      // Third pixel - Blue 1x0
      data->push_back(0);
      data->push_back(0);
      data->push_back(255);
      if (a) data->push_back(64);

      // Fourth pixel - Yellow 1x1
      data->push_back(255);
      data->push_back(255);
      data->push_back(0);
      if (a) data->push_back(255);

      img.setFormat(a ? Image::RGBA : Image::RGB);
      img.setData(data);
      img.setWidth(2);
      img.setHeight(2);
  }
};

TEST_F(ImageTest, pixelAt) {
  loadMask();
  Color c = img.pixelAt(0, 0);
  ASSERT_EQ(0xFFFFFFFF, c.toLong());

  c = img.pixelAt(0, 1);
  ASSERT_EQ(0x808080FF, c.toLong());

  loadRGB();
  c = img.pixelAt(0, 0);
  ASSERT_EQ(0xFF0000FF, c.toLong());

  c = img.pixelAt(1, 0);
  ASSERT_EQ(0x0000FFFF, c.toLong());

  loadRGB(true);
  c = img.pixelAt(1, 0);
  ASSERT_EQ(0x0000FF40, c.toLong());

  img.setFormat(Image::ARGB);
  c = img.pixelAt(1, 0);
  ASSERT_EQ(0x00FF4000, c.toLong());
}

TEST_F(ImageTest, toRGBA) {
  loadMask();
  img.toRGBA();
  ASSERT_EQ(Image::RGBA, img.getFormat());
  ASSERT_EQ(16, img.getData()->size());
  Color c = img.pixelAt(0, 1);
  ASSERT_EQ(0x808080FF, c.toLong());

  loadRGB();
  img.toRGBA();
  ASSERT_EQ(Image::RGBA, img.getFormat());
  ASSERT_EQ(16, img.getData()->size());
  c = img.pixelAt(1, 0);
  ASSERT_EQ(0x0000FFFF, c.toLong());
}

TEST_F(ImageTest, fill) {
  loadMask();
  img.fill(Color(0xAAAAAAFF));
  Color c = img.pixelAt(0, 1);
  ASSERT_EQ(0xAAAAAA80, c.toLong());
}

TEST_F(ImageTest, setPixel) {
  loadRGB();
  img.setPixel(0,0,Color(0xAABBCC33));
  Color c1 = img.pixelAt(0,0);
  Color c2 = img.pixelAt(0,1);
  ASSERT_EQ(0xAABBCCFF, c1.toLong());
  ASSERT_EQ(0x00C800FF, c2.toLong());

  loadRGB(true);
  img.setPixel(0,0,Color(0xAABBCC33));
  c1 = img.pixelAt(0,0);
  c2 = img.pixelAt(0,1);
  ASSERT_EQ(0xAABBCC33, c1.toLong());
  ASSERT_EQ(0x00C800FF, c2.toLong());

  img.setFormat(Image::ARGB);
  img.setPixel(0,0,Color(0xAABBCC33));
  c1 = img.pixelAt(0,0);
  ASSERT_EQ(0xAABBCC33, c1.toLong());

  loadMask();
  img.setPixel(0,0,Color(0xAABBCC33));
  c1 = img.pixelAt(0,0);
  c2 = img.pixelAt(0,1);
  ASSERT_EQ(0xB7B7B7FF, c1.toLong());
  ASSERT_EQ(0x808080FF, c2.toLong());

}

TEST_F(ImageTest, flipY) {
  loadRGB();
  Color c1 = img.pixelAt(0,0);
  Color c2 = img.pixelAt(1,1);
  ASSERT_EQ(0xFF0000FF, c1.toLong());
  ASSERT_EQ(0xFFFF00FF, c2.toLong());
  img.flipY();

  c1 = img.pixelAt(0,0);
  c2 = img.pixelAt(1,1);
  ASSERT_EQ(0x0000FFFF, c1.toLong());
  ASSERT_EQ(0x00C800FF, c2.toLong());
}

TEST_F(ImageTest, applyAlpha) {
  loadMask();
  boost::shared_ptr<Image> mask(new Image);
  img.copyTo(mask);

  loadRGB(true);
  img.applyAlpha(mask);

  Color c1 = img.pixelAt(0,0);
  Color c2 = img.pixelAt(1,1);
  ASSERT_EQ(0xFF0000FF, c1.toLong());
  ASSERT_EQ(0xFFFF0000, c2.toLong());

}
