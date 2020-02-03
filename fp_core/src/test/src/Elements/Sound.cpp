#include <FpCoreTest.h>
#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <fruitpunch/Elements/Sound.h>
#include <fruitpunch/Resources/Font.h>
//#include <fruitpunch/Resources/SoundResource.h>
#include <fruitpunch/Common/NativeBridge.h>
#include <fruitpunch/Common/Runtime.h>
#include <boost/filesystem.hpp>

using namespace fp_core;
using namespace std;
using namespace fp_core::common;


class BridgeSoundTest : public NativeBridge {
  virtual std::string prompt(std::string message) {
    return "";
  }

  /// Returns the default font used by the system
  virtual Font::ref defaultFont() {
    boost::filesystem::path current = boost::filesystem::current_path();
    return Font::ref(new Font("Ubuntu-R.ttf"));
  }

  virtual void playSound(boost::shared_ptr<fp_core::Sound> sound) {
	  sound->setSoundIsPlaying(true);
  }

  virtual void stopSound(boost::shared_ptr<fp_core::Sound> sound) {
	  sound->setSoundIsPlaying(false);
  }

  virtual bool isSoundPlaying(boost::shared_ptr<fp_core::Sound> sound) {
	  return (sound->getSoundIsPlaying());
  }
};

// ---------------------------------------------------------------------------
// Test Class ---
// ---------------------------------------------------------------------------

class SoundTest : public FpCoreTest {
public:
	Sound snd;
	string path;
	string fullPath;
protected:
	virtual void SetUp() {
		initEnvironment();

		Runtime::getCurrent()->setPathSeparator("/");
		Runtime::getCurrent()->debug = true;
		Runtime::getCurrent()->setBridge(boost::shared_ptr<BridgeSoundTest>(new BridgeSoundTest()));
		boost::filesystem::path current = boost::filesystem::current_path();
	}
};

TEST_F(SoundTest, SoundReadOgg) {
	fullPath ="sounds/Bomb.ogg";
	Sound snd(fullPath);
	snd.setIsLoop(true);
	ASSERT_EQ(snd.getChannels(), 1);
	ASSERT_EQ(snd.getFreq(), 22050);
	ASSERT_EQ(snd.getIsLoop(), true);
	snd.setIsLoop(false);
	ASSERT_EQ(snd.getIsLoop(), false);
}

TEST_F(SoundTest, SoundNativeBridge) {
	fullPath = "sounds/Bomb.ogg";
	Sound snd(fullPath);
	snd.play();
	ASSERT_EQ(snd.getSoundIsPlaying(), true);
	snd.stop();
	ASSERT_EQ(snd.getSoundIsPlaying(), false);
	snd.play();
    ASSERT_EQ(snd.isSoundPlaying(), true);
}
