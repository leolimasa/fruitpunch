#include <fruitpunch/Common/PropertyEvent.h>

namespace fp_core {
namespace common {

float PropertyEvent::getValue() {
	return mValue;
}

PropertyEvent::PropertyEvent(std::string event) : Event(event), mValue(0) {
}

void PropertyEvent::setValue(float value) {
	mValue = value;
}

}
}
