/*
 * Vector.h
 *
 *  Created on: Jan 15, 2013
 *      Author: leo
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <fruitpunch/Common/Collection.h>
#include <vector>

namespace fp_core {
namespace common {

class Vector : public Collection {
public:

	Vector();

	/// Returns the object at position i
	virtual boost::shared_ptr<Object> get(int i);

	/// Create and returns an iterator for this collection
	virtual boost::shared_ptr<Iterator> getIterator();

	/// Returns the number of elements in the collection
	virtual int getSize();

	/// Whether this collection contains any objects
	virtual bool isEmpty();

	/// Adds an element to the end of the vector
	virtual void append(boost::shared_ptr<Object> obj);

private:
	boost::shared_ptr<std::vector<boost::shared_ptr<Object> > > mVector;
};

}
}


#endif /* VECTOR_H_ */
