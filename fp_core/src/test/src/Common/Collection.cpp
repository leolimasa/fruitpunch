#include <FpCoreTest.h>
#include <gtest/gtest.h>
#include <fruitpunch/Common/Vector.h>
#include <fruitpunch/Errors/ErrorCodes.h>

using namespace fp_core;
using namespace std;
using namespace boost;
using namespace fp_core::common;


class CollectionTest : public FpCoreTest {
protected:
  boost::shared_ptr<Object> a;
  boost::shared_ptr<Object> b;
  boost::shared_ptr<Object> c;
  Vector v;

  virtual void SetUp() {
	a = boost::shared_ptr<Object>(new Object());
	b = boost::shared_ptr<Object>(new Object());
	c = boost::shared_ptr<Object>(new Object());

	v.append(a);
	v.append(b);
	v.append(c);
  }
};

TEST_F(CollectionTest, getFirstAndLast) {
	ASSERT_TRUE(a == v.getFirst());
	ASSERT_TRUE(c == v.getLast());
}

