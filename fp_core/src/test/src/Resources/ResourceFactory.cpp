#include <FpCoreTest.h>
#include <fruitpunch/Resources/ResourceFactory.hpp>
#include <fruitpunch/Common/Runtime.h>
#include <fruitpunch/Errors/ErrorCodes.h>
#include <fruitpunch/Errors/ResourceLoadError.h>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <boost/filesystem.hpp>

using namespace fp_core;
using namespace boost;
using namespace fp_core::common;

// ---------------------------------------------------------------------------
// Stubs
// ---------------------------------------------------------------------------
class MockResource : public Resource {
public:
  std::string mFile;
  void load(std::string path) {
    mFile = path;
  }

};

// ---------------------------------------------------------------------------
// Test Class
// ---------------------------------------------------------------------------

class ResourceFactoryTest : public FpCoreTest {
protected:
  std::string mPath;

  virtual void SetUp() {
	initEnvironment();
  }
};

// ---------------------------------------------------------------------------
// Test Cases
// ---------------------------------------------------------------------------

TEST_F(ResourceFactoryTest, loadResource) {
  ResourceFactory r;

  boost::shared_ptr<Resource> resource;
  boost::shared_ptr<Runtime> runtime = Runtime::getCurrent();
  runtime->setPathSeparator("/");

  // should throw a runtime error if there is no resource association
  resource = r.loadResource("/home/leo/myresource.png");
  ASSERT_EQ(RESOURCE_LOAD_ERROR, runtime->getErrors()[0].get()->getCode());

  r.associate<MockResource>("png");

  boost::shared_ptr<MockResource> loaded =  boost::static_pointer_cast<MockResource>(r.loadResource(mEnvironment->mFullResourcePath + "/font_test_center.png"));
  ASSERT_EQ(loaded->mFile, mEnvironment->mFullResourcePath + "/font_test_center.png");

  loaded =  boost::static_pointer_cast<MockResource>(r.loadResource(mEnvironment->mFullResourcePath + "/font_test_center.PNG"));
  ASSERT_EQ(loaded->mFile, mEnvironment->mFullResourcePath + "/font_test_center.PNG");

  runtime->getResourcePath().clear();
  runtime->getResourcePath().push_back(mEnvironment->mFullResourcePath);
  loaded =  boost::static_pointer_cast<MockResource>(r.loadResource("font_test_center.png"));
  ASSERT_EQ(loaded->mFile, mEnvironment->mFullResourcePath + "font_test_center.png");

  runtime->flushErrors();

  loaded =  boost::static_pointer_cast<MockResource>(r.loadResource("img/myresource.png"));
  boost::shared_ptr<ResourceLoadError> error = static_pointer_cast<ResourceLoadError>(runtime->getErrors()[0]);
  ASSERT_EQ(IO_ERROR, error->getCode());

//  ASSERT_EQ(loaded->mFile, mPath + "/data/font_test_center.png");

//  runtime->getResourcePath().clear();
//  runtime->getResourcePath().push_back("/home/leo");
//  loaded =  boost::static_pointer_cast<MockResource>(r.loadResource("myresource.png"));
//  ASSERT_EQ(loaded->mFile, "/home/leo/myresource.png");
//
//  loaded =  boost::static_pointer_cast<MockResource>(r.loadResource("img/myresource.png"));
//  ASSERT_EQ(loaded->mFile, "/home/leo/img/myresource.png");

}
