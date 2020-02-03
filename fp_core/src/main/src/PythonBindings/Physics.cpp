/*
 * Physics.cpp
 *
 *  Created on: Nov 2, 2012
 *      Author: leo
 */

#include <boost/python/detail/prefix.hpp>
#include <fruitpunch/PythonBindings/Physics.h>
#include <boost/python.hpp>
#include <string>

// ---------------------------------------------------------------------------
// Fp core includes
// ---------------------------------------------------------------------------
#include <fruitpunch/Physics/PhysicsWorld.h>
#include <fruitpunch/Physics/Body.h>
#include <fruitpunch/Physics/ContactEvent.h>
#include <fruitpunch/Physics/PhysicsJoint.h>
#include <fruitpunch/Physics/DistanceJoint.h>
#include <fruitpunch/Physics/MouseJoint.h>


// ---------------------------------------------------------------------------
// Imports
// ---------------------------------------------------------------------------

using namespace fp_core::physics;
using namespace boost::python;
using namespace std;

namespace fp_core {
namespace python {

// ---------------------------------------------------------------------------
// Methods
// ---------------------------------------------------------------------------

// ____________________________________________________________________________

void Physics::declareClasses() {
	class_<PhysicsWorld, bases<Element>, boost::shared_ptr<PhysicsWorld> >("PhysicsWorld")
		.def("init", &PhysicsWorld::init)
		.def("render_frame", &PhysicsWorld::renderFrame)
		.def("get_bodies", &PhysicsWorld::getBodies)
		.def("get_gravity", &PhysicsWorld::getGravity)
		.def("get_joints", &PhysicsWorld::getJoints)
		.def("get_pixel_size", &PhysicsWorld::getPixelSize)
		.def("get_position_iterations", &PhysicsWorld::getPositionIterations)
		.def("get_timestep", &PhysicsWorld::getTimestep)
		.def("get_velocity_iterations", &PhysicsWorld::getVelocityIterations)
		.def("get_bodies_sensor_by_default", &PhysicsWorld::getBodiesSensorByDefault)
		.def("set_bodies", &PhysicsWorld::setBodies)
		.def("set_gravity", &PhysicsWorld::setGravity)
		.def("set_pixel_size", &PhysicsWorld::setPixelSize)
		.def("set_position_iterations", &PhysicsWorld::setPositionIterations)
		.def("set_timestep", &PhysicsWorld::setTimestep)
		.def("set_velocity_iterations", &PhysicsWorld::setVelocityIterations)
		.def("set_bodies_sensor_by_default", &PhysicsWorld::setBodiesSensorByDefault);

	class_<Body, bases<Element>, boost::shared_ptr<Body> >("Body")
		.def("create", &Body::create)
		.def("render_frame", &Body::renderFrame)
		.def("get_world", &Body::getWorld)
		.def("set_world", &Body::setWorld)
		.def("get_type", &Body::getType)
		.def("set_type", &Body::setType)
		.def("get_shape_scale", &Body::getShapeScale)
		.def("set_shape_scale", &Body::setShapeScale)
		.def("get_linear_velocity", &Body::getLinearVelocity)
		.def("set_linear_velocity", &Body::setLinearVelocity)
		.def("get_angular_velocity", &Body::getAngularVelocity)
		.def("set_angular_velocity", &Body::setAngularVelocity)
		.def("get_friction", &Body::getFriction)
		.def("set_friction", &Body::setFriction)
		.def("get_linear_damping", &Body::getLinearDamping)
		.def("set_linear_damping", &Body::setLinearDamping)
		.def("apply_torque", &Body::applyTorque)
		.def("apply_angular_impulse", &Body::applyAngularImpulse)
		.def("apply_force", &Body::applyForce)
		.def("get_is_sensor", &Body::getIsSensor)
		.def("set_is_sensor", &Body::setIsSensor);

	class_<ContactEvent, bases<Event>, boost::shared_ptr<ContactEvent> >("ContactEvent")
		.def("get_element_a", &ContactEvent::getElementA)
		.def("set_element_a", &ContactEvent::setElementA)
		.def("get_element_b", &ContactEvent::getElementB)
		.def("set_element_b", &ContactEvent::setElementB);

	enum_<Body::BodyType>("BodyType")
	    .value("static", Body::STATIC)
	    .value("dynamic", Body::DYNAMIC)
	    .value("kinematic", Body::KINEMATIC)
	    .export_values();

	class_<PhysicsJoint, bases<Element>, boost::shared_ptr<PhysicsJoint> >("PhysicsJoint")
	    .def("create", &PhysicsJoint::create)
	    .def("retrieve_body_a", &PhysicsJoint::retrieveBodyA)
	    .def("retrieve_body_b", &PhysicsJoint::retrieveBodyB)
	    .def("get_world", &PhysicsJoint::getWorld)
	    .def("get_element_a", &PhysicsJoint::getElementA)
	    .def("set_element_a", &PhysicsJoint::setElementA)
	    .def("get_element_b", &PhysicsJoint::getElementB)
	    .def("set_element_b", &PhysicsJoint::setElementB);

	class_<DistanceJoint, bases<PhysicsJoint>, boost::shared_ptr<DistanceJoint> >("DistanceJoint")
	    .def("create", &DistanceJoint::create);

	class_<MouseJoint, bases<PhysicsJoint>, boost::shared_ptr<MouseJoint> > ("MouseJoint")
		.def("create", &MouseJoint::create)
		.def("update", &MouseJoint::update);
}


} /* namespace python */
} /* namespace fp_core */
