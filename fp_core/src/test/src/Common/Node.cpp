#include <FpCoreTest.h>
#include <gtest/gtest.h>
#include <fruitpunch/Common/Node.h>
#include <fruitpunch/Errors/ErrorCodes.h>
#include <fruitpunch/Common/Collection.h>

using namespace fp_core;
using namespace std;
using namespace boost;
using namespace fp_core::common;


class NodeTest : public FpCoreTest {
protected:

  virtual void SetUp() {
	  initEnvironment();
  }
};

TEST_F(NodeTest, addAndRemove) {
	boost::shared_ptr<Node> n1(new Node());
	boost::shared_ptr<Node> n2(new Node());
	boost::shared_ptr<Node> n3(new Node());

	ASSERT_EQ(0, n1->getChildren()->getSize());

	n1->add(n2);

	ASSERT_EQ(1, n1->getChildren()->getSize());
	ASSERT_EQ(n1, n2->getParent());

	n1->add(n3);

	ASSERT_EQ(2, n1->getChildren()->getSize());
	ASSERT_EQ(n1, n3->getParent());

	n1->remove(n2);

	ASSERT_EQ(1, n1->getChildren()->getSize());
}

TEST_F(NodeTest, get) {
	boost::shared_ptr<Node> n1(new Node());
	boost::shared_ptr<Node> n2(new Node());
	boost::shared_ptr<Node> n3(new Node());

	n2->setName("node2");
	n2->setValue("2");
	n3->setName("node3");
	n3->setValue("3");

	n1->add(n2);
	n1->add(n3);

	ASSERT_EQ("2", n1->get("node2")->getValue());
	ASSERT_EQ("3", n1->get("node3")->getValue());
	ASSERT_EQ(n3, n1->get("node3"));
	ASSERT_FALSE(n1->get("node4"));
}

TEST_F(NodeTest, constructor) {
	boost::shared_ptr<Node> scene(new Node("scene.xml"));

	ASSERT_EQ("scene", scene->getName());
	ASSERT_EQ("30", scene->get("player")->get("@attributes")->get("x")->getValue());
}
