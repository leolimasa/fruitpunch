/*
 * Xml.cpp
 *
 *  Created on: Feb 5, 2013
 *      Author: leo
 */

#include <fruitpunch/Resources/Xml.h>
#include <fruitpunch/Common/Node.h>
#include <pugixml.hpp>

using namespace fp_core::common;


namespace fp_core {
namespace resources {

Xml::Xml() : NodeResource() {
	// TODO Auto-generated constructor stub

}

Xml::~Xml() {
	// TODO Auto-generated destructor stub
}

void Xml::load(std::string fullPath) {
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(fullPath.c_str());

	mRoot = this->makeNode(doc.root().first_child());
}

boost::shared_ptr<fp_core::common::Node> Xml::getRoot() {
	return mRoot;
}

boost::shared_ptr<fp_core::common::Node> Xml::makeNode(const pugi::xml_node& node) {
	boost::shared_ptr<Node> result(new Node());

	// ------------------------------------------------------------------------
	// Set Node name based on its type
	// ------------------------------------------------------------------------
	switch (node.type()) {
	case pugi::node_cdata:
		result->setName("@cdata");
		break;
	case pugi::node_comment:
		result->setName("@comment");
		break;
	default:
		result->setName(node.name());
		break;
	}

	result->setValue(node.value());

	// ------------------------------------------------------------------------
	// Attributes
	// ------------------------------------------------------------------------
	pugi::xml_attribute_iterator it = node.attributes_begin();
	boost::shared_ptr<Node> attributes(new Node());
	attributes->setName("@attributes");

	for (; it != node.attributes_end(); it++) {
		boost::shared_ptr<Node> attrNode(new Node());
		attrNode->setName(it->name());
		attrNode->setValue(it->value());

		attributes->add(attrNode);
	}
	result->add(attributes);

	// ------------------------------------------------------------------------
	// Children
	// ------------------------------------------------------------------------
	pugi::xml_node_iterator nit = node.children().begin();
	for (; nit != node.children().end(); nit++) {
		result->add(makeNode(*nit));
	}

	return result;
}

} /* namespace common */
} /* namespace fp_core */
