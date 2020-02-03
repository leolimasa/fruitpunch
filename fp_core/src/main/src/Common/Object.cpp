/*
 * Object.cpp
 *
 *  Created on: 2012-09-24
 *      Author: leo
 */

#include <fruitpunch/Common/Object.h>

namespace fp_core {
namespace common {

long Object::objectCounter = 0;

Object::Object() : mPyObject(NULL) {
	//mInstanceId = objectCounter;
	//objectCounter++;
	//std::cout << "NEW " << mInstanceId << std::endl;

}

Object::~Object() {
	if (mPyObject != NULL) {
		Py_DECREF(mPyObject);
	}
}

long Object::getInstanceId() const {
	return mInstanceId;
}

PyObject * Object::getPyObject() {
	if (mPyObject == NULL) {
		return Py_BuildValue("");
	}

	Py_INCREF(mPyObject);
	return mPyObject;
}

void Object::setPyObject(PyObject * pyObject) {
	if (mPyObject != NULL) {
		Py_DECREF(pyObject);
	}

	mPyObject = pyObject;
	Py_INCREF(pyObject);
}

} /* namespace common */
} /* namespace fp_core */


