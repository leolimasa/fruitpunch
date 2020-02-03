/*
 * NumberEvent.cpp
 *
 *  Created on: Aug 20, 2013
 *      Author: leo
 */

#include <fruitpunch/Common/NumberEvent.h>
#include <fruitpunch/Common/Events.h>

namespace fp_core {
namespace common {

NumberEvent::NumberEvent(std::string eventName) :
		Event(eventName),
		mNumber(-1) {

}

NumberEvent::~NumberEvent() {

}

int NumberEvent::getNumber() const {
	return mNumber;
}

void NumberEvent::setNumber(int number) {
	mNumber = number;
}

}
}


