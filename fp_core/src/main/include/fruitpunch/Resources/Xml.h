/*
 * Xml.h
 *
 *  Created on: Feb 5, 2013
 *      Author: leo
 */

#ifndef XML_H_
#define XML_H_

#include <fruitpunch/Resources/NodeResource.h>
#include <pugixml.hpp>

namespace fp_core {
namespace resources {

class Xml : public NodeResource {
public:
	Xml();
	virtual ~Xml();
	virtual void load(std::string fullPath);
	virtual boost::shared_ptr<fp_core::common::Node> getRoot();
private:
	boost::shared_ptr<fp_core::common::Node> makeNode(const pugi::xml_node& node);
	boost::shared_ptr<fp_core::common::Node> mRoot;

};

} /* namespace common */
} /* namespace fp_core */
#endif /* XML_H_ */
