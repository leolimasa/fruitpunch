#include <FpCoreTest.h>
#include <gtest/gtest.h>
#include <fruitpunch/Graphics/Color.h>

using namespace fp_core;

class ColorTest : public FpCoreTest {
protected:
  virtual void SetUp() {
	  initEnvironment();
  }
};

TEST_F(ColorTest, ByteValue) {
  unsigned char val = Color::byteValue(0xFF00,1);
  ASSERT_EQ(255, val);

  val = Color::byteValue(0x0944FF,2);
  ASSERT_EQ(9, (int) val);
}

TEST_F(ColorTest, fromLong) {
  Color c = Color();
  c.fromLong(0x09FF0110);
  ASSERT_EQ(16, c.A);
  ASSERT_EQ(1, c.B);
  ASSERT_EQ(255, c.G);
  ASSERT_EQ(9, c.R);
}

TEST_F(ColorTest, toLong) {
  Color c = Color(0x09FF0110);
  ASSERT_EQ(0x09FF0110, c.toLong());
}
