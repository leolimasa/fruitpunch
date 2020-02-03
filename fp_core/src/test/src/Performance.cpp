#include <FpCoreTest.h>
#include <gtest/gtest.h>
#include <fruitpunch/Common/Runtime.h>
#include <fruitpunch/Python/PyLoader.h>

using namespace fp_core;
using namespace boost;
using namespace fp_core::common;
using namespace std;

class PerformanceTest : public FpCoreTest {
protected:
  virtual void SetUp() {
	  initEnvironment();
  }
};

TEST_F(PerformanceTest, fps) {

	// loads fps.py
	boost::shared_ptr<PyLoader> loader(new PyLoader);
	loader->getPythonPath().push_back("target/dependencies/linux-x64");
	loader->getPythonPath().push_back("src/test/resources");
	loader->setModule("fps");
	loader->startup(Runtime::getCurrent());

	// render the frames
	static long FRAMES=100;
	long ms = Runtime::getTimeInMs();
	for (int i=0; i<FRAMES; i++) {
		Runtime::getCurrent()->getWindow()->renderFrame();
	}
	long delta = Runtime::getTimeInMs() - ms;
	float deltaSeconds = (float)delta / 1000.0;
	float fps = (float)FRAMES/deltaSeconds;
	ASSERT_GT(fps, 60);

}
