/*
 * NodeResource.cpp
 *
 *  Created on: Feb 7, 2013
 *      Author: leo
 */

#include <fruitpunch/Resources/NodeResource.h>
#include <fruitpunch/Common/Node.h>

using namespace fp_core::common;

namespace fp_core {
namespace resources {

NodeResource::NodeResource() : Resource() {
	// TODO Auto-generated constructor stub

}

NodeResource::~NodeResource() {
	// TODO Auto-generated destructor stub
}

void NodeResource::load(std::string fullPath) {
}

boost::shared_ptr<Node> NodeResource::getRoot() {
	return boost::shared_ptr<Node>();
}

} /* namespace resources */
} /* namespace fp_core */
