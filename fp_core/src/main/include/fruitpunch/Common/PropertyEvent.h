/*
 * Property.h
 *
 *  Created on: May 10, 2012
 *      Author: leo
 */

#ifndef PROPERTY_EVENT_H_
#define PROPERTY_EVENT_H_

#include <fruitpunch/Common/Event.h>

namespace fp_core {
namespace common{

/// Event triggered when a property is set or returned
/**
 *
 */
class PropertyEvent : public Event {
public:
	PropertyEvent(std::string event);

	float getValue();
	void setValue(float value);

private:
	float mValue;

};

} /* namespace common */
} /* namespace fp_core */
#endif /* PROPERTY_EVENT_H_ */
