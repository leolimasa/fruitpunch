/*
 * Iterator.h
 *
 *  Created on: Jan 15, 2013
 *      Author: leo
 */

#ifndef FP_CORE_COMMON_ITERATOR_H_
#define FP_CORE_COMMON_ITERATOR_H_

#include <fruitpunch/Common/Object.h>
#include <boost/shared_ptr.hpp>

namespace fp_core {
namespace common {

class Iterator : public Object {
public:

	Iterator();

	/// Abstract. Moves the iterator to index i
	virtual void goTo(int i);

	/// Abstract. Returns the object that the iterator is currently pointing
	virtual boost::shared_ptr<Object> get();

	/// Abstract. Moves the iterator to the next element. Returns false at the end.
	virtual bool next();

	/// Abstract. Removes the current object from the collection.
	virtual void remove();
};


}
}

#endif /* ITERATOR_H_ */
