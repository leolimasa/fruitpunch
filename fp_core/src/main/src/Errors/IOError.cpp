/*
 * IOError.cpp
 *
 *  Created on: 2012-06-22
 *      Author: leo
 */

#include <fruitpunch/Errors/IOError.h>
#include <fruitpunch/Errors/ErrorCodes.h>
#include <sstream>

using namespace std;

namespace fp_core {

std::string IOError::getDescription() {
  stringstream ss;
  ss << "I could not open the file \"" << mFile
      << "\". Please, make sure the file exists and you have permissions to read"
      << " or write to it.";
  return ss.str();
}

int IOError::getCode() {
  return IO_ERROR;
}

std::string IOError::getShortDescription() {
  stringstream ss;
  ss << "I cannot not open the file: " << mFile;
  return ss.str();
}

IOError::IOError(std::string file) {
  mFile = file;

}

}
