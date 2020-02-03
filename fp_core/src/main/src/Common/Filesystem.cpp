/*
 * Filesystem.cpp
 *
 *  Created on: Jul 10, 2013
 *      Author: leo
 */

#include <fruitpunch/Common/Filesystem.h>
#include <boost/filesystem.hpp>
namespace fp_core {
namespace common {


Filesystem::Filesystem() {
	// TODO Auto-generated constructor stub

}

Filesystem::~Filesystem() {
	// TODO Auto-generated destructor stub
}

std::string Filesystem::search(std::string file, std::string base, int levels) {
	// open the base
	// list the files
	// check for matches
	// no match, do recursion on any folders

	namespace fs = boost::filesystem;
	using namespace std;

	if (levels == 0) {
		return "";
	}

	// search the immediate files first
	fs::directory_iterator it(base);
	fs::directory_iterator end;
	for (; it != end; it++) {
		// if it's a file and the name matches, return
		if (fs::is_regular_file(it->status()) && it->path().filename().generic_string() == file) {
			return it->path().generic_string();
		}
	}

	// if the file has not been found, search the folders
	it = fs::directory_iterator(base);
	for (; it != end; it++) {
		if (fs::is_directory(it->path())) {
			string result = Filesystem::search(file, it->path().generic_string(), levels-1);
			if (result != "") {
				return result;
			}
		}
	}

	// haven't found anything
	return "";
}

}
} /* namespace fp_desktop */
