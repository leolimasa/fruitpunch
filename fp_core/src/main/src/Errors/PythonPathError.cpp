/*
 * PythonPathError.cpp
 *
 *  Created on: Sep 9, 2012
 *      Author: leo
 */

#include <fruitpunch/Errors/PythonPathError.h>
#include <fruitpunch/Errors/ErrorCodes.h>

using namespace std;

namespace fp_core {

PythonPathError::PythonPathError() {
}

PythonPathError::~PythonPathError() {
    // TODO Auto-generated destructor stub
}

int PythonPathError::getCode() {
	return PYTHON_PATH_ERROR;
}

std::string PythonPathError::getDescription() {
	string message = getShortDescription();
	message += " Please, make sure";
	message += " that the core python libraries (the standard .py files) are";
	message += " located under a lib/ directory on windows, or a lib/python27";
	message += " directory on linux, and that those directories are added to";
	message += " the command line python path.";
	return message;
}

std::string PythonPathError::getShortDescription() {
	string message = "I could not detect a valid python home in the python path.";
	return message;
}

} /* namespace fp_core */
