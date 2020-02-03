/*
 * Common.cpp
 *
 *  Created on: Oct 26, 2012
 *      Author: leo
 */

#include <boost/python/detail/prefix.hpp>
#include <boost/python.hpp>
#include <fruitpunch/PythonBindings/Common.h>
#include <vector>
#include <string>

// ---------------------------------------------------------------------------
// Fp core includes
// ---------------------------------------------------------------------------
#include <fruitpunch/Common/Object.h>
#include <fruitpunch/Common/Runtime.h>
#include <fruitpunch/Common/Property.h>
#include <fruitpunch/Common/Event.h>
#include <fruitpunch/Common/Observer.h>
#include <fruitpunch/Common/Observable.h>
#include <fruitpunch/Common/NativeBridge.h>
#include <fruitpunch/Common/PropertyEvent.h>
#include <fruitpunch/Common/Iterator.h>
#include <fruitpunch/Common/Collection.h>
#include <fruitpunch/Common/Node.h>
#include <fruitpunch/Common/NumberEvent.h>
#include <fruitpunch/Elements/Element.h>

// ---------------------------------------------------------------------------
// Imports
// ---------------------------------------------------------------------------

using namespace fp_core::common;
using namespace boost::python;
using namespace fp_core;
using namespace std;

namespace fp_core {
namespace python {

/// A wrapper on the observer for python
/**
 * The Observer is THE ONLY class that has a wrapper. Other classes should
 * use events to communicate back and forth with python.
 */
class ObserverWrap : public Observer, public wrapper<Observer> {
public:
	ObserverWrap() : Observer() {

	}

	virtual void action() {
		this->get_override("action")();
	}
};

// ---------------------------------------------------------------------------
// Methods
// ---------------------------------------------------------------------------

Common::Common() {
}

// ____________________________________________________________________________

void Common::declareClasses() {
	class_<Object, boost::shared_ptr<Object> >("Object")
	    .add_property("instance_id", &Object::getInstanceId)
		.def("get_instance_id", &Object::getInstanceId)
		.def("get_py_object", &Object::getPyObject)
		.def("set_py_object", &Object::setPyObject);

	class_<Event, bases<Object>, boost::shared_ptr<Event> >("Event", init<string>() )
		.def("get_name", &Event::getName);

	  class_<NumberEvent, bases<Event>, boost::shared_ptr<NumberEvent> >("NumberEvent", init<string>())
		.def("get_number", &NumberEvent::getNumber)
	  	.def("set_number", &NumberEvent::setNumber);

	class_<Observable, bases<Object>, boost::shared_ptr<Observable> >("Observable")
		.def("attach_observer", &Observable::attachObserver)
		.def("detach_observer", &Observable::detachObserver)
		.def("notify", &Observable::notify);

	class_<ObserverWrap, bases<Object>, boost::noncopyable >("ObserverWrap")
		.def("get_event", &ObserverWrap::getEvent)
		.def("get_event_name", &ObserverWrap::getEventName)
		.def("get_instance", &ObserverWrap::getInstance);

	class_<Runtime, bases<Object>, boost::shared_ptr<Runtime> >("Runtime")
	    .def("get_window", &Runtime::getWindow)
	    .def("get_fps", &Runtime::getFps)
	    .def("set_fps", &Runtime::setFps)
	    .def("get_bridge", &Runtime::getBridge);

	class_<Property, bases<Observable>, boost::shared_ptr<Property> >("Property")
		.def("get", &Property::get)
		.def("set", &Property::set);

	class_<PropertyEvent, bases<Event>, boost::shared_ptr<PropertyEvent> >("PropertyEvent", init<string>())
		.def("get_value", &PropertyEvent::getValue)
		.def("set_value", &PropertyEvent::setValue);

	class_<Iterator, bases<Object>, boost::shared_ptr<Iterator> >("Iterator")
		.def("go_to", &Iterator::goTo)
		.def("get", &Iterator::get)
		.def("next", &Iterator::next)
		.def("remove", &Iterator::remove);

	typedef fp_core::common::Collection Coll;
	class_<Coll, bases<Object>, boost::shared_ptr<Coll> >("Collection")
		.def("get_first", &Coll::getFirst)
		.def("get_last", &Coll::getLast)
		.def("get", &Coll::get)
		.def("get_iterator", &Coll::getIterator)
		.def("get_size", &Coll::getSize)
		.def("is_empty", &Coll::isEmpty);


	class_<Node, bases<Object>, boost::shared_ptr<Node> >("Node")
		.def("__init__", make_constructor(&construct_simple<string,Node>))
		.def("get_children", &Node::getChildren)
		.def("get_parent", &Node::getParent)
		.def("set_parent", &Node::setParent)
		.def("get", &Node::get)
		.def("add", &Node::add)
		.def("remove", &Node::remove)
		.def("get_name", &Node::getName)
		.def("set_name", &Node::setName)
		.def("get_namespace", &Node::getNamespace)
		.def("set_namespace", &Node::setNamespace)
		.def("get_value", &Node::getValue)
		.def("set_value", &Node::setValue);


}

// ____________________________________________________________________________

Common::~Common() {
}

} /* namespace python */
} /* namespace fp_core */
