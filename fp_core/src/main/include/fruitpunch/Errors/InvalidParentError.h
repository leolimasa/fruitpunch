/*
 * InvalidParentError.h
 *
 *  Created on: Sep 9, 2012
 *      Author: leo
 */

#ifndef INVALIDPARENTERROR_H_
#define INVALIDPARENTERROR_H_

#include <fruitpunch/Common/RuntimeError.h>

namespace fp_core {

class InvalidParentError : public common::RuntimeError {
public:
    typedef boost::shared_ptr<InvalidParentError> ref;

    InvalidParentError(std::string reportingElement, std::string expectedParent);

    virtual int getCode();
    virtual std::string getDescription();
    virtual std::string getShortDescription();

    virtual ~InvalidParentError();
private:
    std::string mReportingElement;
    std::string mExpectedParent;
};

} /* namespace fp_core */
#endif /* INVALIDPARENTERROR_H_ */
