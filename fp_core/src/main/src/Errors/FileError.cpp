/*
 * FileError.cpp
 *
 *  Created on: 2012-04-16
 *      Author: leo
 */

#include <fruitpunch/Errors/FileError.h>
#include <fruitpunch/Errors/ErrorCodes.h>

namespace fp_core {

FileError::FileError(std::string file) : mFile(file) {

}

FileError::~FileError() {
  // TODO Auto-generated destructor stub
}

std::string FileError::getDescription() {
  std::string desc = "The file '";
  desc += mFile;
  desc += "' could not be opened. Please check if the file exists at the"
      "specified path";
  return desc;

}

int FileError::getCode() {
  return FILE_ERROR;
}

std::string FileError::getShortDescription() {
  std::string desc = "The file '";
  desc += mFile;
  desc += "' could not be opened.";
  return desc;
}

std::string FileError::getFile() const {
  return mFile;
}

void FileError::setFile(std::string file) {
  mFile = file;
}

} /* namespace fp_core */
