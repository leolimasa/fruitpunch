/*
 * Filesystem.h
 *
 *  Created on: Jul 10, 2013
 *      Author: leo
 */

#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include <string>

namespace fp_core {
namespace common {


class Filesystem {
public:
	Filesystem();
	virtual ~Filesystem();

	static std::string search(std::string file, std::string base, int levels);
};

}
} /* namespace fp_desktop */
#endif /* FILESYSTEM_H_ */
