#include <fruitpunch/Common/Iterator.h>


namespace fp_core {
namespace common{

Iterator::Iterator() : Object() {
}


void Iterator::goTo(int i) {
}

boost::shared_ptr<Object> Iterator::get() {
	return boost::shared_ptr<Object>();
}

bool Iterator::next() {
	return false;
}

void Iterator::remove() {
}

}
}

