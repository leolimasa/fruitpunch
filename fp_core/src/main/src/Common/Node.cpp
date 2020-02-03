/*
 * Node.cpp
 *
 *  Created on: Feb 4, 2013
 *      Author: leo
 */

#include <fruitpunch/Common/Node.h>
#include <fruitpunch/Common/Collection.h>
#include <fruitpunch/Common/Vector.h>
#include <fruitpunch/Common/Event.h>
#include <fruitpunch/Common/Events.h>
#include <fruitpunch/Common/Iterator.h>
#include <fruitpunch/Common/Runtime.h>
#include <fruitpunch/Resources/NodeResource.h>
#include <boost/algorithm/string.hpp>

using namespace fp_core::common;
using namespace fp_core::resources;

namespace fp_core {
namespace common {

Node::Node() : Observable(), mChildren(boost::shared_ptr<Vector>(new Vector())) {
	// TODO Auto-generated constructor stub

}

Node::Node(std::string path) : Observable(), mChildren(boost::shared_ptr<Vector>(new Vector())) {
	boost::shared_ptr<Resource> res = Runtime::getCurrent()->getResourceFactory()->loadResource(path);
	boost::shared_ptr<NodeResource> nodeRes = boost::dynamic_pointer_cast<NodeResource>(res);
	boost::shared_ptr<Node> node = nodeRes->getRoot();

	mChildren = boost::static_pointer_cast<Vector>(node->getChildren());
	mName = node->getName();
	mValue = node->getValue();
}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

// ____________________________________________________________________________

const boost::shared_ptr<Collection> Node::getChildren() const {
	return boost::static_pointer_cast<Collection>(mChildren);
}

// ____________________________________________________________________________

const boost::shared_ptr<Node> Node::getParent() const {
	return mParent;
}

// ____________________________________________________________________________

void Node::setParent(const boost::shared_ptr<Node> parent) {
	mParent = parent;
}

// ____________________________________________________________________________

boost::shared_ptr<Node> Node::add(boost::shared_ptr<Node> node) {
	if (node->getParent()) {
			node->getParent()->remove(node);
	}

	node->setParent(getThis<Node>());

	mChildren->append(node);
	node->notify(boost::shared_ptr<Event>(new Event(EV_ADD)));

	return node;
}

// ____________________________________________________________________________

boost::shared_ptr<Node> Node::remove(boost::shared_ptr<Node> node) {
	node->setParent(boost::shared_ptr<Node>());

	boost::shared_ptr<Iterator> it = mChildren->getIterator();

	bool found = false;
	while (it->next()) {
		if (it->get() == node) {
			found = true;
			break;
		}
	}

	if (found) {
		it->remove();
		node->notify(boost::shared_ptr<Event>(new Event(EV_REMOVE)));
		return node;
	}

	return boost::shared_ptr<Node>();
}

std::string Node::getName() {
	return mName;
}

void Node::setName(std::string name) {
	mName = name;
}

std::string Node::getNamespace() {
	return mNamespace;
}

void Node::setNamespace(std::string _namespace) {
	mNamespace = _namespace;
}

std::string Node::getValue() {
	return mValue;
}

void Node::setValue(std::string value) {
	mValue = value;
}

boost::shared_ptr<Node> Node::get(std::string name) {
	boost::shared_ptr<Iterator> it = mChildren->getIterator();
	while(it->next()) {
		boost::shared_ptr<Node> current = boost::static_pointer_cast<Node>(it->get());
		if (boost::iequals(name, current->getName())) {
			return current;
		}
	}

	return boost::shared_ptr<Node>();
}

} /* namespace common */
} /* namespace fp_core */


