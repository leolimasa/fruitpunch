/*
 * PhysicsWorld.cpp
 *
 *  Created on: Sep 9, 2012
 *      Author: leo
 */

#include <fruitpunch/Physics/PhysicsWorld.h>
#include <fruitpunch/Physics/Shaper.h>
#include <fruitpunch/Physics/Body.h>
#include <fruitpunch/Physics/SpriteShaper.h>
#include <fruitpunch/Physics/ContactEvent.h>
#include <fruitpunch/Common/Events.h>
#include <Box2D/Box2D.h>
#include <boost/shared_ptr.hpp>
#include <cstdio>

using namespace std;

namespace fp_core {
namespace physics {

boost::shared_ptr<PhysicsWorld> PhysicsWorld::mCurrent;

PhysicsWorld::PhysicsWorld() : Element() {
	point p;
	p.x = 0;
	p.y = 10.0;
	mGravity = p;
	mTimestep = 1.0f/60.0f;
	mPositionIterations = 6;
	mVelocityIterations = 3;
	mPixelSize = 15.0f;
	mBodiesSensorByDefault = false;

}

// ____________________________________________________________________________

PhysicsWorld::~PhysicsWorld() {

}

// ____________________________________________________________________________

void PhysicsWorld::init() {
	b2Vec2 gravity(mGravity.x, mGravity.y);
	mWorld = boost::shared_ptr<b2World>(new b2World(gravity));
	mWorld->SetContactListener(this);
	mCurrent = getThis<PhysicsWorld>();

	mShapers.push_back(SpriteShaper::ref(new SpriteShaper()));

}

// ____________________________________________________________________________

void PhysicsWorld::renderFrame() {
	mWorld->Step(mTimestep, mVelocityIterations, mPositionIterations);
}

// ____________________________________________________________________________

boost::shared_ptr<PhysicsShape> PhysicsWorld::makeShapeFor(
		Element::ref element) {
	vector<Shaper::ref>::iterator it = mShapers.begin();
	for(; it != mShapers.end(); it++) {
		if ((*it)->test(element)) {
			return (*it)->make(element,
					getThis<PhysicsWorld>());
		}
	}
	return boost::shared_ptr<PhysicsShape>();
}

// ____________________________________________________________________________

void PhysicsWorld::triggerContact(b2Contact& contact, std::string eventName) {
	ContactEvent::ref event(new ContactEvent(contact, eventName, getThis<PhysicsWorld>()));
	this->notify(event);
}

// ____________________________________________________________________________

void PhysicsWorld::onAdd() {
	init();
}

// ____________________________________________________________________________

void PhysicsWorld::BeginContact(b2Contact* contact) {
	triggerContact(*contact, EV_BEGIN_CONTACT);
}

// ____________________________________________________________________________

void PhysicsWorld::EndContact(b2Contact* contact) {
	triggerContact(*contact, EV_END_CONTACT);
}

// ____________________________________________________________________________

void PhysicsWorld::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
	triggerContact(*contact, EV_PRE_SOLVE);
}

// ____________________________________________________________________________

void PhysicsWorld::PostSolve(b2Contact* contact,
		const b2ContactImpulse* impulse) {
	triggerContact(*contact, EV_POST_SOLVE);
}

// ____________________________________________________________________________

void PhysicsWorld::addFixtureToElementMapping(
		boost::shared_ptr<Element> element, b2Fixture* fixture) {
	mFixtureElementMapping.insert(pair<b2Fixture *, boost::weak_ptr<Element> >(fixture, element));
}

// ____________________________________________________________________________

void PhysicsWorld::removeFixtureToElementMapping(b2Fixture* fixture) {
	map<b2Fixture *, boost::weak_ptr<Element> >::iterator it;
	it = mFixtureElementMapping.find(fixture);

	mFixtureElementMapping.erase(it);
}

// ____________________________________________________________________________

boost::shared_ptr<Element> PhysicsWorld::getElementFromFixture(
		b2Fixture* fixture) {

	map<b2Fixture *, boost::weak_ptr<Element> >::iterator it;
	it = mFixtureElementMapping.find(fixture);

	// could not find a fixture. Return null.
	if (it == mFixtureElementMapping.end()) {
		return boost::shared_ptr<Element>();
	}

	return it->second.lock();
}

// ____________________________________________________________________________

b2Fixture* PhysicsWorld::getFixtureFromElement(
		boost::shared_ptr<Element> element) {
	map<b2Fixture *, boost::weak_ptr<Element> >::iterator it = mFixtureElementMapping.begin();
	for (; it != mFixtureElementMapping.end(); it++) {
		if (it->second.lock() == element) {
			return it->first;
		}
	}

	return NULL;
}


// ____________________________________________________________________________

const boost::shared_ptr<std::vector<Body> > PhysicsWorld::getBodies() const {
	return mBodies;
}

void PhysicsWorld::setBodies(
		const boost::shared_ptr<std::vector<Body> > bodies) {
	mBodies = bodies;
}

boost::shared_ptr<PhysicsWorld> PhysicsWorld::getCurrent() {
	return mCurrent;
}

void PhysicsWorld::setCurrent(boost::shared_ptr<PhysicsWorld> current) {
	mCurrent = current;
}

point PhysicsWorld::getGravity() const {
	return mGravity;
}

void PhysicsWorld::setGravity(point gravity) {
	mGravity = gravity;
	b2Vec2 grav;
	grav.x = gravity.x;
	grav.y = gravity.y;
	mWorld->SetGravity(grav);
}

const std::vector<boost::shared_ptr<PhysicsJoint> > PhysicsWorld::getJoints() const {
	return mJoints;
}

float PhysicsWorld::getPixelSize() const {
	return mPixelSize;
}

void PhysicsWorld::setPixelSize(float pixelSize) {
	mPixelSize = pixelSize;
}

int PhysicsWorld::getPositionIterations() const {
	return mPositionIterations;
}

void PhysicsWorld::setPositionIterations(int positionIterations) {
	mPositionIterations = positionIterations;
}

const std::vector<boost::shared_ptr<Shaper> >& PhysicsWorld::getShapers() const {
	return mShapers;
}

float PhysicsWorld::getTimestep() const {
	return mTimestep;
}

void PhysicsWorld::setTimestep(float timestep) {
	mTimestep = timestep;
}

int PhysicsWorld::getVelocityIterations() const {
	return mVelocityIterations;
}

void PhysicsWorld::setVelocityIterations(int velocityIterations) {
	mVelocityIterations = velocityIterations;
}

const boost::shared_ptr<b2World> PhysicsWorld::getWorld() const {
	return mWorld;
}

bool PhysicsWorld::getBodiesSensorByDefault() const {
	return mBodiesSensorByDefault;
}

void PhysicsWorld::setBodiesSensorByDefault(bool isSensorDefault) {
	mBodiesSensorByDefault = isSensorDefault;
}

} /* namespace physiscs */
} /* namespace fp_core */
