/*
 * NodeResource.h
 *
 *  Created on: Feb 7, 2013
 *      Author: leo
 */

#ifndef NODERESOURCE_H_
#define NODERESOURCE_H_

#include <fruitpunch/Resources/Resource.h>

namespace fp_core {

namespace common {
	class Node;
}

namespace resources {

class NodeResource : public Resource {
public:
	NodeResource();
	virtual ~NodeResource();
	virtual void load(std::string fullPath);
	virtual boost::shared_ptr<fp_core::common::Node> getRoot();
};

} /* namespace resources */
} /* namespace fp_core */
#endif /* NODERESOURCE_H_ */
