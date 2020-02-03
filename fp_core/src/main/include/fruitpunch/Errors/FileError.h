/*
 * FileError.h
 *
 *  Created on: 2012-04-16
 *      Author: leo
 */

#ifndef FILEERROR_H_
#define FILEERROR_H_

#include <fruitpunch/Common/RuntimeError.h>
#include <string>

namespace fp_core {

class FileError : public common::RuntimeError {
public:
  FileError(std::string file);
  virtual ~FileError();

  virtual int getCode();
  virtual std::string getDescription();
  virtual std::string getShortDescription();
  std::string getFile() const;
  void setFile(std::string file);

private:
  std::string  mFile;
};

} /* namespace fp_core */
#endif /* FILEERROR_H_ */
