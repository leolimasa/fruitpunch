/*
 * ResourceLoadError.cpp
 *
 *  Created on: May 30, 2012
 *      Author: leo
 */

#include <fruitpunch/Errors/ResourceLoadError.h>
#include <fruitpunch/Errors/ErrorCodes.h>

using namespace std;

namespace fp_core {

ResourceLoadError::ResourceLoadError(std::string extension,
    std::string path) : mExtension(extension), mPath(path) {
}

int ResourceLoadError::getCode() {
  return RESOURCE_LOAD_ERROR;
}

std::string ResourceLoadError::getDescription() {
  string desc = "You tried to load the resource '" + mPath + "'. Unfortunatelly";
  desc += " Fruit punch does not know how to open files with the extension ";
  desc += mExtension + ". Try creating a new Resource or use a different file type.";
  return desc;
}

std::string ResourceLoadError::getShortDescription() {
  string desc = "Could not load " + mPath + ". Extension unknown.";
  return desc;
}

std::string ResourceLoadError::getExtension() const {
  return mExtension;}

}
 /* namespace fp_core */
