/*
 * InvalidChildrenError.h
 *
 *  Created on: Sep 9, 2012
 *      Author: leo
 */

#ifndef INVALIDCHILDRENERROR_H_
#define INVALIDCHILDRENERROR_H_

#include <fruitpunch/Common/RuntimeError.h>
#include <fruitpunch/Errors/ErrorCodes.h>

namespace fp_core {

class InvalidChildrenError : public common::RuntimeError {
public:
    InvalidChildrenError(std::string classname, std::string child);
    virtual ~InvalidChildrenError();

    virtual int getCode();
    virtual std::string getDescription();
    virtual std::string getShortDescription();
private:
    std::string mClassName;
    std::string mChild;
};

} /* namespace fp_core */
#endif /* INVALIDCHILDRENERROR_H_ */
