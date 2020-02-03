/*
 * RenderSingleEvent.h
 *
 *  Created on: Aug 20, 2013
 *      Author: leo
 */

#ifndef FP_CORE_NUMBER_EVENT_H_
#define FP_CORE_NUMBER_EVENT_H_

#include <fruitpunch/Common/Event.h>

namespace fp_core {
namespace common {

class NumberEvent : public Event {
public:
	NumberEvent(std::string eventName);
	virtual ~NumberEvent();
	int getNumber() const;
	void setNumber(int number);

private:
	int mNumber;
};

}
}



#endif /* RENDERSINGLEEVENT_H_ */
