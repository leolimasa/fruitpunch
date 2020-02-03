/*
 * Body.h
 *
 *  Created on: Sep 9, 2012
 *      Author: leo
 */

#ifndef BODY_H_
#define BODY_H_

#include <fruitpunch/Elements/Element.h>
#include <fruitpunch/Graphics/Vertex.h>
#include <Box2D/Box2D.h>

namespace fp_core {

class Transformable;

namespace physics {

class PhysicsWorld;
class PhysicsShape;

/// Represents a box2d body and inherits Element.
/** Any element that is a transformable and has a body added to it will
 *  automatically be transformed into a body that behaves physically on the
 *  screen by the means of Shapers registered into the world class.
 */
class Body : public Element {
public:
    typedef boost::shared_ptr<Body> ref;

	enum BodyType {
		DYNAMIC,STATIC,KINEMATIC
	};

    Body();
    virtual ~Body();

    /// Creates the body fixture and shape based on its parent
    void create();

    /// Updates the parent with the position and rotation of the body in the physics world
    virtual void renderFrame();

    /// Erases the body from the physics world
    virtual void onRemove();

    /// Automatically calls the create() method when the body is added
    virtual void onAdd();

    const boost::shared_ptr<b2BodyDef>& getBodyDef() const;
    void setBodyDef(const boost::shared_ptr<b2BodyDef>& bodyDef);
    const boost::shared_ptr<b2FixtureDef>& getFixtureDef() const;
    void setFixtureDef(const boost::shared_ptr<b2FixtureDef>& fixtureDef);
    const boost::shared_ptr<PhysicsShape>& getShape() const;
    void setShape(const boost::shared_ptr<PhysicsShape>& shape);
    const boost::shared_ptr<Transformable>& getTransformable() const;
    void setTransformable(const boost::shared_ptr<Transformable>& transformable);
    boost::shared_ptr<PhysicsWorld> getWorld() const;
    void setWorld(const boost::shared_ptr<PhysicsWorld>& world);
    BodyType getType() const;
    void setType(BodyType type);
	float getShapeScale() const;
	void setShapeScale(float shapeScale);
	fp_core::point getLinearVelocity() const;
	void setLinearVelocity(fp_core::point velocity);
	const float getAngularVelocity() const;
	void setAngularVelocity(float angularVelocity);
	b2Body * getBox2dBody();
	void setBox2dBody(b2Body * Box2dBody);
	float getFriction();
	void setFriction(float friction);
	float getLinearDamping();
	void setLinearDamping(float linearDamping);
	void applyTorque(float torque);
	void applyAngularImpulse(float impulse);
	void applyForce(point force, point point);
	bool getIsSensor() const;
	void setIsSensor(bool isSensor);

private:
    void updateBodyDef();
    void updateFixtureDef();

    boost::shared_ptr<b2BodyDef>     mBodyDef;
    boost::shared_ptr<b2FixtureDef>  mFixtureDef;
    boost::shared_ptr<PhysicsShape>  mShape;
    boost::shared_ptr<Transformable> mTransformable;
    boost::shared_ptr<PhysicsWorld>  mWorld;
    boost::shared_ptr<b2Shape>       mBox2dShape;

    BodyType mType;
    b2Body * mBody;
    b2Fixture * mFixture;

    float mDensity;

    float mFriction;
    float mRestitution;
    float mShapeScale;
    float mAngularVelocity;
    float mLinearDamping;
    bool  mIsSensor;

    point mLinearVelocity;

};

} /* namespace physics */
} /* namespace fp_core */
#endif /* BODY_H_ */
