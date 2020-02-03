/*
 * PythonPackage.h
 *
 *  Created on: Oct 26, 2012
 *      Author: leo
 */

#ifndef PYTHONPACKAGE_H_
#define PYTHONPACKAGE_H_

#include <boost/shared_ptr.hpp>

namespace fp_core {
namespace python {

class PythonPackage {
public:
	PythonPackage();
	virtual void declareClasses() = 0;
	virtual ~PythonPackage();

	template <typename INPUT, typename OUTPUT>
	static boost::shared_ptr<OUTPUT> construct(boost::shared_ptr<INPUT> in) {
		boost::shared_ptr<OUTPUT> out(new OUTPUT(in));
		return out;
	}

	template <typename INPUT, typename OUTPUT>
	static boost::shared_ptr<OUTPUT> construct_simple(INPUT in) {
			boost::shared_ptr<OUTPUT> out(new OUTPUT(in));
			return out;
	}
};

} /* namespace python */
} /* namespace fp_core */
#endif /* PYTHONPACKAGE_H_ */
