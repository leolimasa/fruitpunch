/*
 * IntegrityError.h
 *
 *  Created on: 2012-05-25
 *      Author: leo
 */

#ifndef INTEGRITYERROR_H_
#define INTEGRITYERROR_H_

#include <fruitpunch/Common/RuntimeError.h>
#include <string>

namespace fp_core {

class IntegrityError : public common::RuntimeError {
public:
  IntegrityError(std::string className, std::string property);

  virtual int getCode();
  virtual std::string getDescription();
  virtual std::string getShortDescription();
private:
  std::string mClassName;
  std::string mProperty;
};

} /* namespace fp_core */
#endif /* INTEGRITYERROR_H_ */
