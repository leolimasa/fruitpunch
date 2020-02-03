/*
 * PythonError.cpp
 *
 *  Created on: 2012-04-16
 *      Author: leo
 */

#include <fruitpunch/Errors/PythonError.h>
#include <fruitpunch/Errors/ErrorCodes.h>

namespace fp_core {

PythonError::PythonError(std::string message) : mMessage(message) {
}

PythonError::~PythonError() {

}

std::string PythonError::getDescription() {
  return mMessage;
}

int PythonError::getCode() {
  return PYTHON_ERROR;
}

std::string PythonError::getShortDescription() {
  return "Error interpreting your python script.";
}

} /* namespace fp_core */
