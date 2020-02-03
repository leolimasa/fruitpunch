/*
 * InvalidChildrenError.cpp
 *
 *  Created on: Sep 9, 2012
 *      Author: leo
 */

#include <fruitpunch/Errors/InvalidChildrenError.h>

using namespace std;

namespace fp_core {

InvalidChildrenError::InvalidChildrenError(std::string className, std::string child) :
	mClassName(className), mChild(child) {
}

InvalidChildrenError::~InvalidChildrenError() {
    // TODO Auto-generated destructor stub
}

int InvalidChildrenError::getCode() {
	return INVALID_PARENT_ERROR;
}

std::string InvalidChildrenError::getDescription() {
	string message = getShortDescription();
	message += " This is usually called if you are trying to find a child";
	message += " of a certain class and it is not found while looping through the";
	message += " tree of elements in an element";
	return message;
}

std::string InvalidChildrenError::getShortDescription() {
	string message = "The child " + mChild;
	message += " was not found while looking through the children of an";
	message += " element in class "  + mClassName + ".";
	return message;
}

} /* namespace fp_core */
