/*
 * StandardIterator.h
 *
 *  Created on: Jan 15, 2013
 *      Author: leo
 */

#ifndef FP_CORE_COMMON_STANDARD_ITERATOR_H_
#define FP_CORE_COMMON_STANDARD_ITERATOR_H_

#include <fruitpunch/Common/Object.h>
#include <boost/shared_ptr.hpp>
#include <fruitpunch/Common/Iterator.h>
#include <vector>

namespace fp_core {
namespace common {

/// Iterator wrapper for classes belonging to the C++ STL.
template <typename T, typename IT>
class StandardIterator : public Iterator {
public:
	StandardIterator(boost::shared_ptr<T> obj);

	/// Moves the iterator to index i
	virtual void goTo(int i);

	/// Returns the object that the iterator is currently pointing
	virtual boost::shared_ptr<Object> get();

	/// Moves the iterator to the next element. Returns false at the end.
	virtual bool next();

	/// Removes the current object from the collection.
	virtual void remove();

	virtual void reset();


private:
	IT mIterator;
	boost::shared_ptr<T> mObj;
	int mIndex;
};

}
}

#endif /* ITERATOR_H_ */
