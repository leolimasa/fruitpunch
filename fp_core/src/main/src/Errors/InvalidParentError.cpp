/*
 * InvalidParentError.cpp
 *
 *  Created on: Sep 9, 2012
 *      Author: leo
 */

#include <fruitpunch/Errors/InvalidParentError.h>
#include <fruitpunch/Errors/ErrorCodes.h>
#include <sstream>

using namespace std;

namespace fp_core {

InvalidParentError::InvalidParentError(string reporting, string expected) :
  mReportingElement(reporting), mExpectedParent(expected) {

}

int InvalidParentError::getCode() {
	return INVALID_PARENT_ERROR;
}

std::string InvalidParentError::getDescription() {
  stringstream str;
  str << "You have tried to add an element of type " << mReportingElement
      << " to an element that it does not support. You can only add " <<
      mReportingElement << " to elements of type " << mExpectedParent << ".";
  return str.str();
}

std::string InvalidParentError::getShortDescription() {
  stringstream str;
  str << "Elements of type " << mReportingElement << " can only be added to"
      << "elements of type " << mExpectedParent << ".";
  return str.str();
}

InvalidParentError::~InvalidParentError() {
    // TODO Auto-generated destructor stub
}

} /* namespace fp_core */
