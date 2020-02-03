/*
 * Sound.cpp
 *
 *   Created on: 2012-08-26
 *   	Author: Steven
 */

#include <fruitpunch/Elements/Sound.h>
#include <boost/shared_ptr.hpp>
#include <fruitpunch/Resources/SoundResource.h>
#include <fruitpunch/Common/Runtime.h>
#include <fruitpunch/Common/NativeBridge.h>

using namespace std;
using namespace fp_core::common;

namespace fp_core {

// these are static
unsigned int Sound::m_sound_count = 0;
std::vector<int> Sound::m_garbage_ids; // not yet, but probably later

// instance specific
boost::shared_ptr<Sound> snd;

Sound::Sound() : Element() {
	mData = boost::shared_ptr<std::vector<char> >(new vector<char>);
	mSoundId = m_sound_count;
	m_sound_count++;
}

Sound::Sound(std::string resourcePath) {
	boost::shared_ptr<SoundResource> res = boost::static_pointer_cast<SoundResource>(
			Runtime::getCurrent()->loadResource(resourcePath));
	snd = res->getSound();

	setData(snd->mData);
	setFreq(snd->mFreq);
	setChannels(snd->mChannels);

	mSoundId = m_sound_count;
	m_sound_count++;
	//printf("Loaded Sound %s .\n", resourcePath.c_str());
	Runtime::getCurrent()->print("Loaded sound " + resourcePath, Runtime::MSG_INFO);
}

Sound::~Sound() {
	m_garbage_ids.push_back(mSoundId);
}

void Sound::play() {
	mIsPlaying = true;
	mKeepPlaying = true;
	Runtime::getCurrent()->getBridge()->playSound(snd);
}

void Sound::stop() {
	mIsPlaying = false;
	mKeepPlaying = false;
	Runtime::getCurrent()->getBridge()->stopSound(snd);
}

bool Sound::isSoundPlaying() {
	mIsPlaying = Runtime::getCurrent()->getBridge()->isSoundPlaying(snd);
	return (mIsPlaying);
}

void Sound::renderFrame() {
	// play again when it has finished

	if (mIsPlaying == false && mKeepPlaying == true && mIsLoop == true) {
		play();
	}

	mIsPlaying = isSoundPlaying();
} // end renderFrame

void Sound::onAdd() {

} // end onAdd


void Sound::onRemove() {

}

int Sound::getChannels() const {
    return mChannels;
}

int Sound::getFreq() const {
    return mFreq;
}

int Sound::getSoundId() const {
	return mSoundId;
}

bool Sound::getSoundIsPlaying() {
	return mIsPlaying;
}

bool Sound::getIsLoop() {
	return (mIsLoop);
}

const boost::shared_ptr<std::vector<char> >& Sound::getData() const {
    return mData;
}

std::vector<int> Sound::getGarbageIds() {
  return m_garbage_ids;
}

void Sound::setFreq(int freq) {
    mFreq = freq;
}

void Sound::setData(const boost::shared_ptr<std::vector<char> >& data) {
    mData = data;
}

void Sound::setChannels(int channels) {
    mChannels = channels;
}

void Sound::setSoundIsPlaying(bool isPlaying) {
	mIsPlaying = isPlaying;
}

void Sound::setIsLoop(bool isLoop) {
	mIsLoop = isLoop;
}

}// end namespace fp_core
