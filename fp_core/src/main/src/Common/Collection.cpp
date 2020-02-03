#include <fruitpunch/Common/Collection.h>


namespace fp_core {
namespace common {

Collection::Collection() : Object() {
}

boost::shared_ptr<Object> Collection::getFirst() {
	if (this->isEmpty()) {
		return boost::shared_ptr<Object>();
	}

	return this->get(0);
}

boost::shared_ptr<Object> Collection::getLast() {
	if (this->isEmpty()) {
			return boost::shared_ptr<Object>();
	}

	return this->get(this->getSize() - 1);
}

boost::shared_ptr<Object> Collection::get(int i) {
	// Abstract method
	return boost::shared_ptr<Object>();
}

boost::shared_ptr<Iterator> Collection::getIterator() {
	// Abstract method
	return boost::shared_ptr<Iterator>();
}

int Collection::getSize() {
	// Abstract method
	return 0;
}

bool Collection::isEmpty() {
	// Abstract method
	return true;
}

boost::shared_ptr<Object> Collection::operator [](int i) {
	return get(i);
}


}
}


