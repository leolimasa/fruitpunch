#include <FpCoreTest.h>
#include <fruitpunch/Common/Runtime.h>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
#include <gtest/gtest.h>
#include <fruitpunch/Resources/Xml.h>
#include <fruitpunch/Common/Node.h>
#include <fruitpunch/Common/Collection.h>

using namespace fp_core;
using namespace boost;
using namespace std;
using namespace fp_core::common;
using namespace fp_core::resources;

// ---------------------------------------------------------------------------
// Test Class
// ---------------------------------------------------------------------------

class XmlTest : public FpCoreTest {
protected:
  string mPath;

  virtual void SetUp() {
	initEnvironment();
  }
};

// ---------------------------------------------------------------------------
// Test Cases
// ---------------------------------------------------------------------------
TEST_F(XmlTest, getRoot) {
	string fullPath = mEnvironment->mFullResourcePath + "scene.xml";
	boost::shared_ptr<Xml> xml(new Xml());
	xml->load(fullPath);

	boost::shared_ptr<Node> node = xml->getRoot();


	ASSERT_EQ("scene", node->getName());
	ASSERT_EQ("@attributes", node->getChildren()->getAndCast<Node>(0)->getName());
	ASSERT_EQ("player", node->getChildren()->getAndCast<Node>(1)->getName());

	boost::shared_ptr<Node> player = node->getChildren()->getAndCast<Node>(1);
	boost::shared_ptr<fp_core::common::Collection> playerAttrs = player->getChildren()->getAndCast<Node>(0)->getChildren();

	ASSERT_EQ("x", playerAttrs->getAndCast<Node>(0)->getName());
	ASSERT_EQ("30", playerAttrs->getAndCast<Node>(0)->getValue());
	ASSERT_EQ("y", playerAttrs->getAndCast<Node>(1)->getName());
	ASSERT_EQ("60", playerAttrs->getAndCast<Node>(1)->getValue());

	ASSERT_EQ("enemy", node->get("group")->getChildren()->getAndCast<Node>(1)->getName());
}
