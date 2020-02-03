/*
 * MockEnvironment.h
 *
 *  Created on: Sep 8, 2012
 *      Author: steven
 */

#ifndef MOCKENVIRONMENT_H_
#define MOCKENVIRONMENT_H_

#include <string>
#include <boost/filesystem.hpp>

class MockEnvironment {
public:
	MockEnvironment();
	virtual ~MockEnvironment();
	std::string mFullResourcePath;
	std::string mRoot;
	boost::filesystem::path mCurrentPath;
};

#endif /* MOCKENVIRONMENT_H_ */
