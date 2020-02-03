/*
 * StandardIterator.cpp
 *
 *  Created on: Jan 15, 2013
 *      Author: leo
 */

#include <fruitpunch/Common/StandardIterator.h>


namespace fp_core {
namespace common {

template<typename T, typename IT>
StandardIterator<T,IT>::StandardIterator(boost::shared_ptr<T> obj) : Iterator() {
	mObj = obj;
	reset();
}

template<typename T, typename IT>
void StandardIterator<T,IT>::goTo(int i) {

	// Cannot go to a position that doesn't exist
	if (mObj->size() == 0) {
		return;
	}

	int norm = i % mObj->size();

	mIterator = mObj->begin();
	mIterator += norm;
	mIndex = norm;
}

template<typename T, typename IT>
boost::shared_ptr<Object> StandardIterator<T,IT>::get() {
	return *mIterator;
}

template<typename T, typename IT>
bool StandardIterator<T,IT>::next() {
	// Zero size then no next
	if (mObj->size() == 0) {
		return false;
	}

	// First item
	if (mIndex < 0) {
		mIndex++;
		return true;
	}

	mIterator++;

	// end has been reached
	if (mIterator == mObj->end()) {
		return false;
	}

	mIndex++;
	return true;

}

template<typename T, typename IT>
void StandardIterator<T,IT>::remove() {
	mObj->erase(mIterator);

	int oldIndex = mIndex;

	// When we perform an erase, the iterator becomes invalid
	// so we have to reset it.
	reset();

	goTo(oldIndex);
}

template<typename T, typename IT>
void StandardIterator<T,IT>::reset() {
	mIterator = mObj->begin();
	mIndex = -1;
}

void standardIteratorTypes() {
	using namespace std;

	typedef vector<boost::shared_ptr<Object> > V;
	typedef vector<boost::shared_ptr<Object> >::iterator IT;
	boost::shared_ptr<V> tmpVec(new V());

	StandardIterator<V,IT> a(tmpVec);
}

}
}






