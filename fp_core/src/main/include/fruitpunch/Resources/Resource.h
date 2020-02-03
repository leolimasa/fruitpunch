/*
 * Resource.h
 *
 *  Created on: 2012-05-30
 *      Author: leo
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <string>
#include <fruitpunch/Common/Observable.h>

namespace fp_core {

class Resource : public common::Observable {
public:
  Resource();
  virtual void load(std::string fullPath) =0;
};

} /* namespace fp_core */
#endif /* RESOURCE_H_ */
