
/*
 * Raw.cpp
 *
 *  Created on: 2012-06-22
 *      Author: leo
 */

#include <fruitpunch/Resources/Raw.h>
#include <fruitpunch/Errors/IOError.h>
#include <fruitpunch/Common/Runtime.h>
#include <fstream>

using namespace std;
using namespace fp_core::common;

namespace fp_core {

Raw::Raw() : Resource() {

}

Raw::Raw(std::string filepath) : Resource() {
  filepath = Runtime::getCurrent()->resolve(filepath);
  load(filepath);
}

void Raw::load(std::string fullPath) {
  ifstream file;
  unsigned long int size;

  mData = boost::shared_ptr<vector<unsigned char> >(new vector<unsigned char>);
  file.open(fullPath.c_str(), ios::binary | ios::in);
  if (!file.is_open()) {
    Runtime::getCurrent()->addError(IOError::ref(new IOError(fullPath)));
    printf("Could not open file!");
    return;
  }

  mData->clear();
  char byte;
  while (file.get(byte)) {
    mData->push_back(byte);
  }
  file.close();

}

boost::shared_ptr<std::vector<unsigned char> > Raw::getData() const {
  return mData;
}

void Raw::setData(boost::shared_ptr<std::vector<unsigned char> > data) {
  mData = data;
}

void Raw::save(std::string fullPath) {
  ofstream file;

  file.open(fullPath.c_str(), ios::binary | ios::out);
  if (!file.is_open()) {
    Runtime::getCurrent()->addError(IOError::ref(new IOError(fullPath)));
    return;
  }

  file.write((char *) &(*mData)[0], mData->size());
  file.close();
}

}
