#include <fruitpunch/Common/Vector.h>
#include <fruitpunch/Common/StandardIterator.h>
#include <vector>

using namespace std;

namespace fp_core {
namespace common {

Vector::Vector() : mVector(boost::shared_ptr<vector<boost::shared_ptr<Object> > >(new vector<boost::shared_ptr<Object> >)) {
}

boost::shared_ptr<Object> Vector::get(int i) {
	return (*mVector)[i];
}

boost::shared_ptr<Iterator>Vector::getIterator() {
	typedef vector<boost::shared_ptr<Object> > V;
	typedef vector<boost::shared_ptr<Object> >::iterator IT;
	boost::shared_ptr<StandardIterator<V,IT> > it(new StandardIterator<V,IT>(mVector));
	return it;
}

int Vector::getSize() {
	return mVector->size();
}

bool Vector::isEmpty() {
	return mVector->size() == 0;
}

void Vector::append(boost::shared_ptr<Object> obj) {
	mVector->push_back(obj);
}

}
}


