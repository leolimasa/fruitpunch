/*
 * Playable.cpp
 *
 *  Created on: May 10, 2012
 *      Author: leo
 */

#include <fruitpunch/Elements/Playable.h>
#include <fruitpunch/Common/Events.h>
#include <fruitpunch/Common/Event.h>
#include <fruitpunch/Common/NumberEvent.h>
#include <boost/make_shared.hpp>

namespace fp_core {

Playable::Playable() :
		Element(), mIsPlaying(false), mFrameDuration(0), mDurationCounter(0) {
	mCurrentFrame = 0;
	mStartFrame = 0;
}

Playable::~Playable() {
	// TODO Auto-generated destructor stub
}

void Playable::start() {
	mIsPlaying = true;
}

void Playable::stop() {
	mIsPlaying = false;
}

void Playable::tick() {
	performRenderSingle();
	Element::tick();
}

void Playable::performRenderSingle() {
	if (!mIsPlaying)
		return;

	// Do not execute the render single until the frame duration
	if (mDurationCounter < mFrameDuration) {
		mDurationCounter++;
		return;
	}
	mDurationCounter = 0;

	// Don't do anything if the current frame is not the starting frame, but
	// keep incrementing the frames.
	if (mCurrentFrame < mStartFrame) {
		mCurrentFrame++;
		return;
	}

	// Get the nominal frame value to pass into renderSingle
	int duration = calculateDuration();
	int lastFrame = duration + mStartFrame;
	int nominalFrame = (mCurrentFrame - mStartFrame) % duration;

	renderSingle(nominalFrame);

	// fire the first frame event if we are in the first frame
	if (mCurrentFrame == mStartFrame) {
		notify(Event::ref(new Event(EV_FIRST_FRAME)));
		onFirstFrame();
	}

	mCurrentFrame++;

	// If we reached the end of the animation, go back to frame zero.
	// Only stop playing if looping is not enabled
	if (mCurrentFrame > lastFrame) {
		notify(Event::ref(new Event(EV_LAST_FRAME)));
		mCurrentFrame = 0;
		if (!mLoop)	stop();
	}
}

void Playable::onFirstFrame() {
	return;
}

int Playable::getCurrentFrame() const {
	return mCurrentFrame;
}

void Playable::setCurrentFrame(int currentFrame) {
	mCurrentFrame = currentFrame;
}

bool Playable::isPlaying() const {
	return mIsPlaying;
}

void Playable::setPlaying(bool isPlaying) {
	mIsPlaying = isPlaying;
}

bool Playable::isLoop() const {
	return mLoop;
}

void Playable::setLoop(bool loop) {
	mLoop = loop;
}

int Playable::getStartFrame() const {
	return mStartFrame;
}

void Playable::setStartFrame(int startFrame) {
	mStartFrame = startFrame;
}

int Playable::getEndFrame() {
	return mStartFrame + calculateDuration() - 1;
}

void Playable::onAdd() {
}

void Playable::renderSingle(int frame) {
	boost::shared_ptr<NumberEvent> ev = boost::make_shared<NumberEvent>(
			EV_RENDER_SINGLE);
	ev->setNumber(frame);
	notify(ev);
}

int Playable::calculateDuration() {
	boost::shared_ptr<NumberEvent> ev = boost::make_shared<NumberEvent>(
			EV_CALCULATE_DURATION);
	notify(ev);

	return ev->getNumber();
}

void Playable::onRemove() {
}

int Playable::getFrameDuration() const {
	return mFrameDuration;
}

void Playable::setFrameDuration(int frameDuration) {
	mFrameDuration = frameDuration;
}

}/* namespace fp_core */

