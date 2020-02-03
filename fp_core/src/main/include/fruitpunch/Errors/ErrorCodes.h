/*
 * ErrorCodes.h
 *
 *  Created on: 2012-04-16
 *      Author: leo
 */

#ifndef ERRORCODES_H_
#define ERRORCODES_H_

namespace fp_core {
  enum ErrorCode  {
    FILE_ERROR,
    PYTHON_ERROR,
    INTEGRITY_ERROR,
    RESOURCE_LOAD_ERROR,
    FONT_LOAD_ERROR,
    IO_ERROR,
    INVALID_PARENT_ERROR,
    NODE_NOT_FOUND_ERROR,
    PYTHON_PATH_ERROR
  };
}


#endif /* ERRORCODES_H_ */
