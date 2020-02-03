/*
 * ResourceLoadError.h
 *
 *  Created on: May 30, 2012
 *      Author: leo
 */

#ifndef RESOURCELOADERROR_H_
#define RESOURCELOADERROR_H_

#include <fruitpunch/Common/RuntimeError.h>

namespace fp_core {

class ResourceLoadError : public common::RuntimeError {
public:
  ResourceLoadError(std::string extension, std::string path);
  virtual int getCode();
  virtual std::string getDescription();
  virtual std::string getShortDescription();
  std::string getExtension() const;

private:
  std::string mExtension;
  std::string mPath;
};

} /* namespace fp_core */
#endif /* RESOURCELOADERROR_H_ */
