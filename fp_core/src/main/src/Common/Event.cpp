/*
 * Event.cpp
 *
 *  Created on: Sep 9, 2012
 *      Author: leo
 */

#include <fruitpunch/Common/Event.h>

using namespace std;

namespace fp_core {
namespace common {

Event::Event(std::string name) : Object() {
    mName = name;
}

Event::~Event() {
    // TODO Auto-generated destructor stub
}

const std::string Event::getName() const {
    return mName;
}

void Event::setName(const std::string name) {
    mName = name;
}

} /* namespace common */
} /* namespace fp_core */
