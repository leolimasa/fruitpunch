#include <FpCoreTest.h>
#include <gtest/gtest.h>
#include <fruitpunch/Elements/Text.h>
#include <boost/shared_ptr.hpp>
#include <fruitpunch/Common/NativeBridge.h>
#include <boost/filesystem.hpp>
#include <fruitpunch/Elements/Scene.h>
#include <fruitpunch/Elements/Sound.h>

using namespace fp_core;
using namespace std;
using namespace fp_core::common;


class TextImpl : public Text {
public:
  bool mFontChanged;

  TextImpl(string txt) : Text(txt) {
    mFontChanged = false;
  }

  virtual void onFontChange() {
    mFontChanged = true;
  }
};

class Bridge : public NativeBridge {
  virtual std::string prompt(std::string message) {
    return "";
  }

  /// Returns the default font used by the system
  virtual Font::ref defaultFont() {
    boost::filesystem::path current = boost::filesystem::current_path();
    return Font::ref(new Font("Ubuntu-R.ttf"));
  }

  virtual void playSound(boost::shared_ptr<fp_core::Sound> sound) {

  }

  virtual void stopSound(boost::shared_ptr<fp_core::Sound> sound) {

  }

  virtual bool isSoundPlaying(boost::shared_ptr<fp_core::Sound> sound) {
	  return false; // we don't care in this instance
  }
};

// ---------------------------------------------------------------------------
// Test Class
// ---------------------------------------------------------------------------

class TextTest : public FpCoreTest {
public:

protected:
  virtual void SetUp() {
	initEnvironment();
    Runtime::getCurrent()->setBridge(boost::shared_ptr<Bridge>(new Bridge()));

  }
};

TEST_F(TextTest, fontPropertyUpdates) {
  TextImpl text("Hello World");

  ASSERT_FALSE(text.mFontChanged);

  text.getFont()->setAlignment(Font::LEFT);

  ASSERT_TRUE(text.mFontChanged);
}






