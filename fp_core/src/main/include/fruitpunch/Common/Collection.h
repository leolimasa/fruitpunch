/*
 * Collection.h
 *
 *  Created on: Jan 15, 2013
 *      Author: leo
 */

#ifndef FP_CORE_COMMONCOLLECTION_H_
#define FP_CORE_COMMONCOLLECTION_H_

#include <fruitpunch/Common/Object.h>
#include <boost/shared_ptr.hpp>

namespace fp_core {
namespace common {

class Iterator;

/// An iterable collection of objects, such as a vector or linked list
/**
 * Unlike collections in C++ std, this only holds objects of type
 * shared_ptr<Object>.
 *
 * Abstract class.
 */
class Collection : public Object {
public:

	Collection();

	///Returns the first object in the collection
	/**
	 * Will return null if the collection is empty
	 */
	virtual boost::shared_ptr<Object> getFirst();

	/// Returns the last object in the collection
	/**
	 * Will return null if the collection is empty
	 */
	virtual boost::shared_ptr<Object> getLast();

	/// [] Operator that points to the get() function
	virtual boost::shared_ptr<Object> operator[](int i);

	/// Returns the object at position i then casts it to T type
	template <typename T> boost::shared_ptr<T> getAndCast(int i);

	/// Abstract. Returns the object at position i
	virtual boost::shared_ptr<Object> get(int i);

	/// Abstract. Create and returns an iterator for this collection
	virtual boost::shared_ptr<Iterator> getIterator();

	/// Abstract. Returns the number of elements in the collection
	virtual int getSize();

	/// Abstract. Whether this collection contains any objects
	virtual bool isEmpty();

};

}
}

template<typename T>
inline boost::shared_ptr<T> fp_core::common::Collection::getAndCast(int i) {
	return boost::static_pointer_cast<T>(get(i));
}

#endif /* COLLECTION_H_ */
