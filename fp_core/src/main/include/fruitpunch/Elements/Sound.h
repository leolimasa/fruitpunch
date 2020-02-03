/*
 * Sound.h
 *
 *  Created on: 2012-08-26
 *      Author: Steven
 *
 *      Represents a sound with information like channels,
 *      frequency, and abilities to play, stop, and play looping.
 */

#ifndef SOUND_H_
#define SOUND_H_

#include <boost/shared_ptr.hpp>
#include <fruitpunch/Elements/Element.h>
#include <vector>
#include <string>

namespace fp_core {

// A sound that can be played and stopped
class Sound : public Element {
public:
	Sound();
	Sound(std::string resourcePath);
	virtual ~Sound();

	// Plays the sound file
	void play();

	// Stops playing the sound file
	void stop();

	// Calls NativeBridge to see if sound file is actually playing
	bool isSoundPlaying();

	// This will be fired every time the frame is rendered and will be
	// checking the status of the sound to see if should still be making noise.
	virtual void renderFrame();

	virtual void onAdd();
	virtual void onRemove();

    // ---------------------------------------------------------------------------
	// Getters
	// ---------------------------------------------------------------------------
    int getChannels() const;
    int getFreq() const;
    int getSoundId() const;
    bool getSoundIsPlaying();
    bool getIsLoop();
    const boost::shared_ptr<std::vector<char> >& getData() const;
    static std::vector<int> getGarbageIds();

    // ---------------------------------------------------------------------------
    // Setters
    // ---------------------------------------------------------------------------
    void setChannels(int channels);
    void setFreq(int freq);
    void setData(const boost::shared_ptr<std::vector<char> >& data);
    void setSoundIsPlaying(bool isPlaying);
    void setIsLoop(bool isLoop);

private:
	boost::shared_ptr<std::vector<char> > 	mData;
	int 									mFreq;
	int 									mChannels;
	bool 									mIsPlaying;
	bool									mIsLoop;
	bool 									mKeepPlaying;
	int 									mSoundId;
	static unsigned int					m_sound_count;
	static std::vector < int > 			m_garbage_ids;
}; // end class Sound

} // end namespace fp_core
#endif /*SOUND_H_ */
