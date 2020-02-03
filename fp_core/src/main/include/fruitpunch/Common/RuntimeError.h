/*
 * RuntimeError.h
 *
 *  Created on: 2012-04-16
 *      Author: leo
 */

#ifndef RUNTIMEERROR_H_
#define RUNTIMEERROR_H_

#include <string>
#include <boost/shared_ptr.hpp>

namespace fp_core {
namespace common{

class RuntimeError {
public:
  typedef boost::shared_ptr<RuntimeError> ref;

  RuntimeError();
  virtual ~RuntimeError();

  virtual std::string getDescription() =0;
  virtual int getCode() =0;
  virtual std::string getShortDescription() =0;
};

} /* namespace common */
} /* namespace fp_core */
#endif /* RUNTIMEERROR_H_ */
