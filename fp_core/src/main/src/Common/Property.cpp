#include <fruitpunch/Common/Property.h>
#include <fruitpunch/Common/Events.h>
#include <fruitpunch/Common/PropertyEvent.h>

using namespace std;

namespace fp_core {
namespace common {

float Property::get() {
	// create the event
	boost::shared_ptr<PropertyEvent> getEvent = boost::shared_ptr<PropertyEvent>(new PropertyEvent(EV_GET));
	boost::shared_ptr<Event> ev = boost::static_pointer_cast<Event>(getEvent);

	// triggers and returns the value
	this->notify(ev);
	return getEvent->getValue();

}

Property::Property() : Observable() {
}

void Property::set(float value) {
	// create the event
	boost::shared_ptr<PropertyEvent> setEvent = boost::shared_ptr<PropertyEvent>(new PropertyEvent(EV_SET));
	setEvent->setName(EV_SET);
	setEvent->setValue(value);

	// triggers the event
	this->notify(boost::static_pointer_cast<Event>(setEvent));
}

} /* namespace common */
} /* namespace fp_core */
