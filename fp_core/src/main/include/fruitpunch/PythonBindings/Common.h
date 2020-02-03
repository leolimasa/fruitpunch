/*
 * Common.h
 *
 *  Created on: Oct 26, 2012
 *      Author: leo
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <boost/python/detail/prefix.hpp>
#include <boost/python.hpp>
#include <fruitpunch/PythonBindings/PythonPackage.h>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <string>

namespace fp_core {
namespace python {

class Common: public fp_core::python::PythonPackage {
public:
	Common();
	virtual void declareClasses();
	virtual ~Common();

	/// Shortcut to declare a vector type
	/**
	 * This makes it possible to access vectors from the python side.
	 * Each vector type must be exported, such as:
	 *
	 * declareVector<Element>("ElementVector")
	 */
	template <typename T>
	void declareVector(std::string name) {
		using namespace boost::python;
		using namespace boost;

		typedef std::vector<T> Vector;

		class_<Vector, shared_ptr<Vector> >(name.c_str())
			.def(vector_indexing_suite<Vector>());
	}
};

} /* namespace python */
} /* namespace fp_core */
#endif /* COMMON_H_ */
