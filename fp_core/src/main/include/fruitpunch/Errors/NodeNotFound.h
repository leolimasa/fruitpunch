/*
 * NodeNotFound.h
 *
 *  Created on: Feb 10, 2013
 *      Author: leo
 */

#ifndef NODENOTFOUND_H_
#define NODENOTFOUND_H_

#include <fruitpunch/Common/RuntimeError.h>

namespace fp_core {
namespace errors {

class NodeNotFound :  public common::RuntimeError {
public:
	NodeNotFound(std::string nodeName);
	virtual ~NodeNotFound();

	virtual int getCode();
	virtual std::string getDescription();
	virtual std::string getShortDescription();
private:
	std::string mNodeName;
};

}
}

#endif /* NODENOTFOUND_H_ */
