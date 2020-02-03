/*
 * Node.h
 *
 *  Created on: Feb 4, 2013
 *      Author: leo
 */

#ifndef NODE_H_
#define NODE_H_

#include <fruitpunch/Common/Observable.h>

#define NODE_ATTRIBUTES "@attributes";
#define NODE_CDATA "@cdata";

namespace fp_core {
namespace common {

class Collection;
class Vector;

class Node : public Observable {
public:
	Node();
	Node(std::string path);
	virtual ~Node();
	const boost::shared_ptr<Collection> getChildren() const;
	const boost::shared_ptr<Node> getParent() const;
	void setParent(const boost::shared_ptr<Node> parent);

	/// Searches and returns the first child node with the specified name
	/**
	 * This method is case insensitive. Returns a null pointer if it cannot
	 * find the node.
	 */
	boost::shared_ptr<Node> get(std::string name);

	boost::shared_ptr<Node> add(boost::shared_ptr<Node> node);
	boost::shared_ptr<Node> remove(boost::shared_ptr<Node> node);
	std::string getName();
	void setName(std::string name);
	std::string getNamespace();
	void setNamespace(std::string _namespace);
	std::string getValue();
	void setValue(std::string value);

private:
	boost::shared_ptr<Vector> mChildren;
	boost::shared_ptr<Node> mParent;
	std::string mNamespace;
	std::string mName;
	std::string mValue;
};

} /* namespace common */
} /* namespace fp_core */
#endif /* NODE_H_ */
