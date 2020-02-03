/*
 * Environment.h
 *
 *  Created on: Jun 24, 2013
 *      Author: leo
 */

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include <vector>
#include <string>
#include <boost/program_options.hpp>
#include <boost/shared_ptr.hpp>
#include <fruitpunch/Common/Runtime.h>

namespace fp_desktop {

class Environment {
public:
	Environment();
	virtual ~Environment();

	bool createFromArgs(int ac, char* av[]);
	boost::shared_ptr<fp_core::common::Runtime> createRuntime();
	void printRuntimeErrors();
	int getHeight() const;
	std::string getPyfile() const;
	std::string getPyhome() const;
	std::vector<std::string> getPypath() const;
	std::vector<std::string> getResourcePath() const;
	int getWidth() const;

private:
	int width;
	int height;

	std::string pyhome;
	std::string pyfile;
	std::vector<std::string> pypath;
	std::vector<std::string> resourcePath;

	void processVm(boost::program_options::variables_map& vm);
};

} /* namespace fp_desktop */
#endif /* ENVIRONMENT_H_ */
