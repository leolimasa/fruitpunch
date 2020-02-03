/*
 * NativeBridge.h
 *
 *  Created on: 2012-05-02
 *      Author: leo
 */

#ifndef NATIVEBRIDGE_H_
#define NATIVEBRIDGE_H_

#include <string>
#include <boost/shared_ptr.hpp>
#include <fruitpunch/Common/Object.h>
#include <map>

namespace fp_core {

class Sound;
class Font;

namespace common {

/// Methods to be implemented by the program that will use libfruitpunch
/**
 * Every runtime instance has to have a NativeBridge instance attached to it.
 * This allows libfruitpunch to call native methods that might vary from
 * system to system.
 */
class NativeBridge : public Object {
public:
  /// Displays a popup with a textbox for the user with the specified message
  /**
   *
   *
   * @param message The text to be displayed in the popup
   * @return
   */
  virtual std::string prompt(std::string message) =0;

  /// Returns the default font used by the system
  virtual boost::shared_ptr<Font> defaultFont() =0;

  // implement playSound on all systems...
  virtual void playSound(boost::shared_ptr<Sound> sound) =0;

  // implement stopSound on all systems...
  virtual void stopSound(boost::shared_ptr<Sound> sound) =0;

  // implement isSoundPlaying on all systems
  virtual bool isSoundPlaying(boost::shared_ptr<Sound> sound) =0;

  virtual ~NativeBridge() {};
private:
  std::map<unsigned int, unsigned int> static mSoundMap;
};

} /* namespace common */
} /* namespace fp_core */
#endif /* NATIVEBRIDGE_H_ */
