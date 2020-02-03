/*
 * PythonError.h
 *
 *  Created on: 2012-04-16
 *      Author: leo
 */

#ifndef PYTHONERROR_H_
#define PYTHONERROR_H_

#include <fruitpunch/Common/RuntimeError.h>

namespace fp_core {

class PythonError: public common::RuntimeError {
public:
  PythonError(std::string mMessage);
  virtual ~PythonError();

  virtual std::string getDescription();
  virtual int getCode();
  virtual std::string getShortDescription();

private:
  std::string mMessage;
};

} /* namespace fp_core */
#endif /* PYTHONERROR_H_ */
