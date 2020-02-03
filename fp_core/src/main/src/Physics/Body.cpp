/*
 * Body.cpp
 *
 *  Created on: Sep 9, 2012
 *      Author: leo
 */

#include <fruitpunch/Physics/Body.h>
#include <fruitpunch/Graphics/Transformable.h>
#include <fruitpunch/Common/Runtime.h>
#include <fruitpunch/Physics/PhysicsWorld.h>
#include <fruitpunch/Errors/InvalidParentError.h>
#include <fruitpunch/Physics/PhysicsShape.h>
#include <typeinfo>

float PI180 = 0.01745329251f;

using namespace fp_core;
using namespace fp_core::common;

namespace fp_core {
namespace physics {

Body::Body() : Element(),
	mBody(NULL),
	mFixture(NULL) {
    mWorld = PhysicsWorld::getCurrent();
    mDensity = 1.0f;
    mFriction = 0.3f;
    mRestitution = 0.5f;
    mType = DYNAMIC;
    mShapeScale = 1.0f;

    if (mWorld) {
    	mIsSensor = mWorld->getBodiesSensorByDefault();
    }
}

// ____________________________________________________________________________

Body::~Body() {
    onRemove();
}

// ____________________________________________________________________________

void Body::create() {
  // ---------------------------------------------------------------------------
  // Checks if we are adding this body to an element
  // ---------------------------------------------------------------------------
  mTransformable = boost::dynamic_pointer_cast<Transformable>(getParent());
  if (!mTransformable) {
	 Runtime::getCurrent()->addError(InvalidParentError::ref(new InvalidParentError("Body", "Transformable")));
	 return;
  }


  // ---------------------------------------------------------------------------
  // Checks if this body exists. If so, destroy the old copy
  // ---------------------------------------------------------------------------
  if (mBody != NULL) {
    getWorld()->getWorld()->DestroyBody(mBody);
  }

  // ---------------------------------------------------------------------------
  // Creates the box2d body definition
  // ---------------------------------------------------------------------------
  mBodyDef = boost::shared_ptr<b2BodyDef>(new b2BodyDef());
  updateBodyDef();

  // ---------------------------------------------------------------------------
  // Creates the box2d fixture definition
  // ---------------------------------------------------------------------------
  mFixtureDef = boost::shared_ptr<b2FixtureDef>(new b2FixtureDef());

  // If the user has already defined a shape, then use that
  if (!mShape) {
	  mShape = getWorld()->makeShapeFor(getParent());

	  mBox2dShape = mShape->getBox2dShape(mShapeScale);
  }

  // if we still have a null shape, it's because the Shaper could not find a
  // valid one
  if (!mShape) {
    // TODO add proper runtime error handling
    printf("No shape generated!\n");
    return;
  }

  updateFixtureDef();

  // ---------------------------------------------------------------------------
  // Creates the box2d body
  // ---------------------------------------------------------------------------
  mBody = getWorld()->getWorld()->CreateBody(mBodyDef.get());
  mFixture = mBody->CreateFixture(mFixtureDef.get());

  // ---------------------------------------------------------------------------
  // Maps the fixture to the element in the PhysicsWorld so we can retrieve
  // in the contact event later.
  // ---------------------------------------------------------------------------
  getWorld()->addFixtureToElementMapping(getParent(), mFixture);
}

// ____________________________________________________________________________

void Body::updateBodyDef() {

  // ---------------------------------------------------------------------------
  // Define body type
  // ---------------------------------------------------------------------------
  switch (mType) {
  case (DYNAMIC):
      mBodyDef->type = b2_dynamicBody;
  break;
  case (STATIC):
      mBodyDef->type = b2_staticBody;
  break;
  case (KINEMATIC):
      mBodyDef->type = b2_kinematicBody;
  break;
  }

  // ---------------------------------------------------------------------------
  // Define body position and angle
  // ---------------------------------------------------------------------------
  float pixelSize = getWorld()->getPixelSize();
  mBodyDef->position.Set(mTransformable->getPosition().x / pixelSize,
      mTransformable->getPosition().y / pixelSize );
  mBodyDef->angle = mTransformable->getRotation() * PI180;
}

// ____________________________________________________________________________

void Body::renderFrame() {
  b2Vec2 position = mBody->GetPosition();
  point newPosition;
  newPosition.x = position.x * getWorld()->getPixelSize();
  newPosition.y = position.y * getWorld()->getPixelSize();
  getTransformable()->setPosition(newPosition);
  getTransformable()->setRotation(mBody->GetAngle() / PI180);

}

// ____________________________________________________________________________

void Body::onRemove() {

	if (mBody != NULL) {
		getWorld()->removeFixtureToElementMapping(mFixture);
		getWorld()->getWorld()->DestroyBody(mBody);
		mBody = NULL;
		mFixture = NULL;
	}

}

// ____________________________________________________________________________

void Body::onAdd() {
	create();
}

// ____________________________________________________________________________

float Body::getShapeScale() const {
	return mShapeScale;
}

void Body::setShapeScale(float shapeScale) {
	mShapeScale = shapeScale;
}

point Body::getLinearVelocity() const {
	return mLinearVelocity;
}

void Body::setLinearVelocity(point velocity) {
	mLinearVelocity = velocity;
	b2Vec2 vel;
	vel.x = velocity.x;
	vel.y = velocity.y;
	mBody->SetAwake(true);
	mBody->SetLinearVelocity(vel);
}

const float Body::getAngularVelocity() const {
	return mAngularVelocity;
}

void Body::setAngularVelocity(float angularVelocity) {
	mAngularVelocity = angularVelocity;
	mBody->SetAwake(true);
	mBody->SetAngularVelocity(angularVelocity);
}

void Body::updateFixtureDef() {
  mFixtureDef->density = mDensity;
  mFixtureDef->restitution = mRestitution;
  mFixtureDef->friction = mFriction;
  mFixtureDef->isSensor = mIsSensor;
  mFixtureDef->shape = mBox2dShape.get();
}

// ____________________________________________________________________________

Body::BodyType Body::getType() const {
  return mType;
}

// ---------------------------------------------------------------------------
// Getters and Setters
// ---------------------------------------------------------------------------

void Body::setType(Body::BodyType type) {
  mType = type;
}

const boost::shared_ptr<b2BodyDef>& Body::getBodyDef() const {
  return mBodyDef;
}

void Body::setBodyDef(const boost::shared_ptr<b2BodyDef>& bodyDef) {
  mBodyDef = bodyDef;
}

const boost::shared_ptr<b2FixtureDef>& Body::getFixtureDef() const {
  return mFixtureDef;
}

void Body::setFixtureDef(const boost::shared_ptr<b2FixtureDef>& fixtureDef) {
  mFixtureDef = fixtureDef;
}

const boost::shared_ptr<PhysicsShape>& Body::getShape() const {
  return mShape;
}

void Body::setShape(const boost::shared_ptr<PhysicsShape>& shape) {
  mShape = shape;
}

const boost::shared_ptr<Transformable>& Body::getTransformable() const {
  return mTransformable;
}

void Body::setTransformable(
    const boost::shared_ptr<Transformable>& transformable) {
  mTransformable = transformable;
}

boost::shared_ptr<PhysicsWorld> Body::getWorld() const {
  return mWorld;
}

void Body::setWorld(const boost::shared_ptr<PhysicsWorld>& world) {
  mWorld = world;
}

b2Body * Body::getBox2dBody() {
	return mBody;
}

void Body::setBox2dBody(b2Body * Box2dBody) {
	mBody = Box2dBody;
}

float Body::getFriction() {
	return mFriction;
}

void Body::setFriction(float friction) {
	mFriction = friction;
}

float Body::getLinearDamping() {
	return mLinearDamping;
}

void Body::setLinearDamping(float linearDamping) {
	mLinearDamping = linearDamping;
	mBody->SetLinearDamping(mLinearDamping);
}

void Body::applyTorque(float torque) {
	mBody->ApplyTorque(torque);
}

void Body::applyAngularImpulse(float impulse) {
	mBody->ApplyAngularImpulse(impulse);
}

void Body::applyForce(point force, point point) {
	b2Vec2 b2Force;
	b2Force.x = force.x;
	b2Force.y = force.y;

	b2Vec2 b2Point;
	b2Point.x = point.x;
	b2Point.y = point.y;
	mBody->ApplyForce(b2Force, b2Point);
}

bool Body::getIsSensor() const {
	return mIsSensor;
}

void Body::setIsSensor(bool isSensor) {
	mIsSensor = isSensor;
	mFixture->SetSensor(isSensor);
}

} /* namespace physics */
} /* namespace fp_core */
