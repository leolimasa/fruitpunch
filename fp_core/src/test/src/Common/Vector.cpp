#include <FpCoreTest.h>
#include <gtest/gtest.h>
#include <fruitpunch/Common/Vector.h>
#include <fruitpunch/Errors/ErrorCodes.h>
#include <fruitpunch/Common/Iterator.h>

using namespace fp_core;
using namespace std;
using namespace boost;
using namespace fp_core::common;


class VectorTest : public FpCoreTest {
protected:
  virtual void SetUp() {

  }
};

TEST_F(VectorTest, getAndAppend) {
	Vector v;

	boost::shared_ptr<Object> a(new Object());
	boost::shared_ptr<Object> b(new Object());
	boost::shared_ptr<Object> c(new Object());

	v.append(a);
	v.append(b);
	v.append(c);

	ASSERT_TRUE(a == v.get(0));
	ASSERT_TRUE(b == v.get(1));
	ASSERT_TRUE(c == v.get(2));

	ASSERT_TRUE(a == v[0]);
	ASSERT_TRUE(b == v[1]);
	ASSERT_TRUE(c == v[2]);
}

TEST_F(VectorTest, sizeAndEmpty) {
	Vector v;

	ASSERT_TRUE(v.isEmpty());
	ASSERT_EQ(0, v.getSize());

	boost::shared_ptr<Object> a(new Object());
	boost::shared_ptr<Object> b(new Object());
	boost::shared_ptr<Object> c(new Object());

	v.append(a);
	v.append(b);
	v.append(c);

	ASSERT_FALSE(v.isEmpty());
	ASSERT_EQ(3, v.getSize());
}

TEST_F(VectorTest, vectorIterator) {
	Vector v;

	boost::shared_ptr<Iterator> it = v.getIterator();
	ASSERT_FALSE(it->next());

	boost::shared_ptr<Object> a(new Object());
	boost::shared_ptr<Object> b(new Object());
	boost::shared_ptr<Object> c(new Object());

	v.append(a);
	v.append(b);
	v.append(c);

	it = v.getIterator();

	ASSERT_TRUE(it->next());
	ASSERT_TRUE(it->get() == a);

	ASSERT_TRUE(it->next());
	ASSERT_TRUE(it->get() == b);

	ASSERT_TRUE(it->next());
	ASSERT_TRUE(it->get() == c);

	ASSERT_FALSE(it->next());

	it->goTo(1);
	ASSERT_TRUE(it->get() == b);

	it->remove();
	ASSERT_TRUE(it->get() == c);
}
