
/*
 * IOError.h
 *
 *  Created on: 2012-06-22
 *      Author: leo
 */

#ifndef IOERROR_H_
#define IOERROR_H_

#include <boost/shared_ptr.hpp>
#include <string>
#include <fruitpunch/Common/RuntimeError.h>

namespace fp_core {

class IOError : public common::RuntimeError {
public:
  typedef boost::shared_ptr<IOError> ref;

  virtual std::string getDescription();
  virtual int getCode();
  virtual std::string getShortDescription();

  IOError(std::string file);
private:
  std::string mFile;
};

}

#endif
