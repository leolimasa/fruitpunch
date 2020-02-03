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

class FontLoadError : public common::RuntimeError {
public:
  FontLoadError(std::string path, int errorCode);

  virtual int getCode();
  virtual std::string getDescription();
  virtual std::string getShortDescription();
private:
  int mFontErrorCode;
  std::string mPath;
};

} /* namespace fp_core */
#endif /* RESOURCELOADERROR_H_ */
