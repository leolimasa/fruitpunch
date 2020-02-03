/*
 * Playable.h
 *
 *  Created on: May 10, 2012
 *      Author: leo
 */

#ifndef PLAYABLE_H_
#define PLAYABLE_H_

#include <fruitpunch/Elements/Element.h>

namespace fp_core {

/// Interface for anything that can be played in a sequence of frames
class Playable : public Element {
public:
  Playable();
  virtual ~Playable();

  virtual void start();
  virtual void stop();
  virtual void tick();

  /// Executes logic regarding rendering a single frame
  /**
   * Meant to be overriden by derived class. The frame argument will not be
   * the current frame number, but a nominal value that takes into account
   * the duration and the start frame of the playable.
   *
   * For example, if startFrame is 2 and the current frame is 2, then
   * the frame argument will be 0.
   */
  virtual void renderSingle(int frame);

  /// Executed when the playable reaches the first frame
  /**
   * Meant to be overriden by derived classes
   */
  virtual void onFirstFrame();

  /// Returns the total duration of the playable sequence
  /**
   * Meant to be overriden by derived classes. Will fire a CALCULATE_DURATION
   * event so that scripting languages (python) can override this method.
   */
  virtual int calculateDuration();


  int getCurrentFrame() const;
  void setCurrentFrame(int currentFrame);
  bool isPlaying() const;
  void setPlaying(bool isPlaying);
  bool isLoop() const;
  void setLoop(bool loop);
  int getStartFrame() const;
  void setStartFrame(int startFrame);
  int getEndFrame();

  /// Calls the renderSingle abstract method during the correct frames
  void performRenderSingle();

  virtual void onAdd();
  virtual void onRemove();
	int getFrameDuration() const;
	void setFrameDuration(int frameDuration);

private:
  int mCurrentFrame;
  int mStartFrame;
  int mFrameDuration;
  int mDurationCounter;
  bool mLoop;
  bool mIsPlaying;

};

} /* namespace fp_core */
#endif /* PLAYABLE_H_ */
