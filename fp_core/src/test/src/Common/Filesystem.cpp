#include <FpCoreTest.h>
#include <gtest/gtest.h>
#include <fruitpunch/Common/Node.h>
#include <fruitpunch/Errors/ErrorCodes.h>
#include <fruitpunch/Common/Collection.h>
#include <fruitpunch/Common/Filesystem.h>

using namespace fp_core;
using namespace std;
using namespace boost;
using namespace fp_core::common;


class FilesystemTest : public FpCoreTest {
protected:

  virtual void SetUp() {
	  initEnvironment();
  }
};

TEST_F(FilesystemTest, search) {
	string path = Filesystem::search("Filesystem.cpp", this->mEnvironment->mRoot, 5);
	ASSERT_EQ(this->mEnvironment->mRoot + "/src/main/src/Common/Filesystem.cpp", path);

	path = Filesystem::search("ThisDoesntExist.txt", this->mEnvironment->mRoot, 5);
	ASSERT_EQ("", path);

	path = Filesystem::search("Filesystem.cpp", this->mEnvironment->mRoot, -1);
	ASSERT_EQ(this->mEnvironment->mRoot + "/src/main/src/Common/Filesystem.cpp", path);
}
