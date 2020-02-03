/*
 * Bridge.cpp
 *
 *  Created on: Jun 27, 2013
 *      Author: leo
 */


#include <fp_desktop/Bridge.h>
#include <boost/shared_ptr.hpp>
#include <fruitpunch/Elements/Sound.h>
#include <AL/al.h>
#include <AL/alut.h>
#include <cstdio>
#include <iostream>
#include <vector>
#include <iterator>

using namespace fp_core;
using namespace std;

namespace fp_desktop {

bool alutInitialized = false;

Bridge::Bridge() {
  // TODO Auto-generated constructor stub

}

std::string Bridge::prompt(std::string message) {
  //PromptWindow window;
  //return window.prompt(message);
        return "PROMPT not supported on this platform";
}

fp_core::Font::ref Bridge::defaultFont() {
  using namespace fp_core;
  return Font::ref(new Font("Ubuntu-R.ttf"));
}

void Bridge::playSound(boost::shared_ptr<Sound> sound) {
        //Initialize the OpenAL library...one time
        if (alutInitialized == false) {
                alutInit(NULL, 0);
                alutInitialized = true;
        }

        // get the sourceId
        unsigned int sourceId = loadSound(sound);
        ALint state;

        // I'm going to add looping once I veriy that this is all working as expected...

        // play the source
        alSourcePlay(sourceId);

        // just set it to true...if we query for it in a loop
        // here without starting another thread...it will freeze the game
    sound->setSoundIsPlaying(true);
}

int Bridge::loadSound(boost::shared_ptr<Sound> sound) {
  // checks if the texture is inside the map
  map<unsigned int, unsigned int>::iterator it;
  it = mSoundMap.find(sound->getSoundId());
  if (it != mSoundMap.end()) {
    // there is a texture already. Returns the texid
    return it->second;
  }

  // If it gets here, there is no decoded buffer. We will have to create one.
  unsigned int sourceId;
  unsigned int bufferId;
  unsigned int format;

  // generate the sourceId and bufferId
  alGenSources(1, &sourceId);
  alGenBuffers(1, &bufferId);

  // Set the source and listener to the same location
  alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f); // same everytime
  alSource3f(sourceId, AL_POSITION, 0.0f, 0.0f, 0.0f);

  // Check the number of channels... always use 16-bit samples
  if (sound->getChannels() == 1)
      format = AL_FORMAT_MONO16;
  else
      format = AL_FORMAT_STEREO16;

  alBufferData(bufferId, format, &sound->getData()->at(0),
                  static_cast<ALsizei>(sound->getData()->size()), sound->getFreq());

  // Attach sound buffer to source
  alSourcei(sourceId, AL_BUFFER, bufferId);

  // adds the newly created image to the map
  mSoundMap.insert(pair<unsigned int, unsigned int>(sound->getSoundId(), sourceId));

  return sourceId;
}

void Bridge::flush_sound_map(boost::shared_ptr<Sound> sound)
{
        for (int i=0; i<sound->getGarbageIds().capacity(); i++)
        {
                  map<unsigned int, unsigned int>::iterator it;
                  it = mSoundMap.find(sound->getSoundId()); // assume they match for now
                  unsigned int sourceId;
                  sourceId = it->second;

                  //unload sound sourceID and bufferID using OpenAL calls
                  alDeleteSources(1, &sourceId);
                  // we are assuming that sourceId and bufferId match
                  // if sound gets more complex...we will want to store it
                  // and reference &bufferId instead...
                  alDeleteBuffers(1, &sourceId);

                  //remove texture from texture map
                  mSoundMap.erase(sound->getSoundId());
        } // end for
} // end flush_sound_map

void Bridge::stopSound(boost::shared_ptr<Sound> sound) {
        map<unsigned int, unsigned int>::iterator it;
        it = mSoundMap.find(sound->getSoundId()); // assume they match for now
    unsigned int sourceId;
    sourceId = it->second;
        alSourceStop(sourceId);
} // end stopSound

bool Bridge::isSoundPlaying(boost::shared_ptr<Sound> sound) {
        // if I don't just return true...we lose sound...
        map<unsigned int, unsigned int>::iterator it;
        it = mSoundMap.find(sound->getSoundId()); // assume they match for now
    unsigned int sourceId;
    sourceId = it->second;
        ALint state;

        // query the state of the source
        alGetSourcei(sourceId, AL_SOURCE_STATE, &state);

        if (state == AL_PLAYING)
                return true;
        else if(state == AL_STOPPED)
                return false;
        return false;

} // end isSoundPlaying

} /* namespace fp_desktop */
