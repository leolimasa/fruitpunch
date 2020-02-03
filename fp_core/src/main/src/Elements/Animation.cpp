/*
 * Animation.cpp
 *
 *  Created on: May 14, 2012
 *      Author: leo
 */

#include <fruitpunch/Common/Events.h>
#include <fruitpunch/Elements/Animation.h>
#include <stdio.h>

using namespace std;

namespace fp_core {

Animation::Animation() {
	setStartFrame(0);
	setLoop(false);

}

int Animation::calculateDuration() {
	int highestEndFrame = 0;

	// find the tween that has the highest end frame
	vector<boost::shared_ptr<Playable> >::const_iterator it = mChildren.begin();
	for (; it != mChildren.end(); it++) {
		if ((*it)->getEndFrame() > highestEndFrame) {
			highestEndFrame = (*it)->getEndFrame();
		}
	}

	return highestEndFrame + 1;
}

void Animation::renderSingle(int frame) {
	vector<boost::shared_ptr<Playable> >::iterator it = mChildren.begin();
	for (; it != mChildren.end(); it++) {
		(*it)->setCurrentFrame(frame);
	}

}

void Animation::start() {
	Playable::start();

	vector<boost::shared_ptr<Playable> >::iterator it = mChildren.begin();
	for (; it != mChildren.end(); it++) {
		(*it)->start();
	}
}

void Animation::stop() {
	Playable::stop();

	vector<boost::shared_ptr<Playable> >::iterator it = mChildren.begin();
	for (; it != mChildren.end(); it++) {
		(*it)->stop();
	}
}

void Animation::add(boost::shared_ptr<Playable> playable) {
	mChildren.push_back(playable);
	addOrphan(playable);
}

void Animation::onFirstFrame() {
	if (!isPlaying()) {
		return;
	}

	vector<boost::shared_ptr<Playable> >::iterator it = mChildren.begin();
	for (; it != mChildren.end(); it++) {
		(*it)->start();
	}
}

}/* namespace fp_core */


