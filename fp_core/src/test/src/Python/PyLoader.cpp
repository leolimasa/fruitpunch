#include <FpCoreTest.h>
#include <gtest/gtest.h>
#include <fruitpunch/Python/PyLoader.h>
#include <fruitpunch/Common/Runtime.h>

using namespace fp_core;
using namespace boost;
using namespace fp_core::common;
using namespace std;

class PyLoaderTest : public FpCoreTest {
protected:
  virtual void SetUp() {
	  initEnvironment();
  }
};

TEST_F(PyLoaderTest, makePythonPath) {
	PyLoader loader;
	loader.addPath("target");
	loader.addPath("src/main");
	loader.addPath("/home");
	string path = loader.makePythonPath();
	string root = this->mEnvironment->mRoot;
	#ifdef WIN32
		string expect = root + "/target;" + root + "/src/main" ;
	#else
		string expect = root + "/target:" + root + "/src/main:/home";
	#endif
	ASSERT_EQ(path, expect);
}

TEST_F(PyLoaderTest, figureOutPythonHome) {
	PyLoader loader;
	#ifdef WIN32
		string expect = this->mEnvironment->mRoot  + "/src/test/resources/pyhomewin";
		boost::algorithm::replace_all(expect, "/","\\");
		loader.addPath("src/test/resources/pyhomewin");
	#else
		string expect = this->mEnvironment->mRoot  + "/src/test/resources/pyhomelinux";
		loader.addPath("src/test/resources/pyhomelinux");
	#endif
	string pyhome = loader.figureOutPythonHome();
	
	ASSERT_EQ(expect, pyhome);

}

TEST_F(PyLoaderTest, startup) {
	/**
	 * This will most likely crash the entire thing if Python is not properly
	 * initialized.
	 */

	boost::shared_ptr<PyLoader> loader(new PyLoader);
	/*boost::filesystem::path pyHomeRelative = "..\\..\\..\\target\\dependencies\\windows-x32\\lib\\python27";
	boost::filesystem::path pyHomeAbs = boost::filesystem::canonical(pyHomeRelative, this->mEnvironment->mCurrentPath); */
	/*; */

	#ifdef WIN32
		string p = "target/dependencies/windows-x32";
	#else
		string p = "target/dependencies/linux-x64";
	#endif

	loader->getPythonPath().push_back(p);
	loader->getPythonPath().push_back("src/test/resources");
	loader->getPythonPath().push_back("c:\\Users\\leo");
	loader->setModule("pytest");
	bool success = loader->startup(Runtime::getCurrent());
	ASSERT_TRUE(success);
	ASSERT_EQ(Runtime::getCurrent()->getFps(), 777);
}
