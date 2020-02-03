/*
 * Object.h
 *
 *  Created on: 2012-09-24
 *      Author: leo
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <boost/python/detail/prefix.hpp>
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace fp_core {
namespace common {

class Object : public boost::enable_shared_from_this<Object> {
public:
	Object();
	virtual ~Object();

	long getInstanceId() const;
	PyObject * getPyObject();
	void setPyObject(PyObject * pyObject);

	template <class T>
	boost::shared_ptr<T> getThis() {
		return boost::static_pointer_cast<T>(shared_from_this());
	}

	static long objectCounter;

private:
	long mInstanceId;
	PyObject * mPyObject;
};

} /* namespace common */
} /* namespace fp_core */
#endif /* OBJECT_H_ */
