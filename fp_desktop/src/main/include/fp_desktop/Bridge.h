/*
 * Bridge.h
 *
 *  Created on: Jun 27, 2013
 *      Author: leo
 */

#ifndef BRIDGE_H_
#define BRIDGE_H_

#include <fruitpunch/Common/NativeBridge.h>
#include <fruitpunch/Resources/Font.h>
#include <fruitpunch/Elements/Sound.h>
#include <boost/shared_ptr.hpp>

namespace fp_desktop {

class Bridge : public fp_core::common::NativeBridge {
public:
  Bridge();
  virtual std::string prompt(std::string message); // this was virtual
  virtual fp_core::Font::ref defaultFont();
  virtual void playSound(boost::shared_ptr<fp_core::Sound> sound);
  virtual void stopSound(boost::shared_ptr<fp_core::Sound> sound);
  virtual bool isSoundPlaying(boost::shared_ptr<fp_core::Sound> sound);

private:
  std::map <unsigned int, unsigned int> mSoundMap; // may want to add this to interface...
  bool alutInitialized;
  int loadSound(boost::shared_ptr<fp_core::Sound> sound);
  void flush_sound_map(boost::shared_ptr<fp_core::Sound> sound);
  // adding the openal error check would be quite thorough huh?
  // someone might appreciate it...
};

} /* namespace fp_desktop */
#endif /* BRIDGE_H_ */
