/*
 * NodeNotFound.cpp
 *
 *  Created on: Feb 10, 2013
 *      Author: leo
 */

#include <fruitpunch/Errors/NodeNotFound.h>
#include <fruitpunch/Errors/ErrorCodes.h>
#include <sstream>

using namespace std;

fp_core::errors::NodeNotFound::NodeNotFound(std::string nodeName) {
	mNodeName = nodeName;
}

fp_core::errors::NodeNotFound::~NodeNotFound() {
}

int fp_core::errors::NodeNotFound::getCode() {
	return NODE_NOT_FOUND_ERROR;
}

std::string fp_core::errors::NodeNotFound::getDescription() {
	stringstream str;
	str << "I could not find the node named \"" << mNodeName << "."
		<< "This is usually caused when you are trying to find a node using the wrong parent.";
	return str.str();
}

std::string fp_core::errors::NodeNotFound::getShortDescription() {
	return "Could not find node.";
}
