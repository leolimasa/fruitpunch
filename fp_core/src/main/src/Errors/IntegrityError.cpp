/*
 * IntegrityError.cpp
 *
 *  Created on: 2012-05-25
 *      Author: leo
 */

#include <fruitpunch/Errors/IntegrityError.h>
#include <fruitpunch/Errors/ErrorCodes.h>

using namespace std;

namespace fp_core {

IntegrityError::IntegrityError(std::string className,
    std::string property) : mClassName(className), mProperty(property) {
}

int IntegrityError::getCode() {
  return INTEGRITY_ERROR;
}

std::string IntegrityError::getDescription() {
  string message = getShortDescription();
  message += " This is usually called if you are calling a method that needs that";
  message += " the ";
  message += mClassName;
  message += " is associated to a ";
  message += mProperty;
  message += " but this association has not been made. Try making an association";
  message += " by using something like '";
  message += mClassName;
  message += "->set";
  message += mProperty;
  message += "(value).";
  return message;
}

std::string IntegrityError::getShortDescription() {

  string message = "The class ";
  message += mClassName;
  message += " is not attached to a ";
  message += mProperty;
  message += ".";

  return message;
}

} /* namespace fp_core */
