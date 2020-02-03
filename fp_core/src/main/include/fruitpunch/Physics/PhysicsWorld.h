/*
 * PhysicsWorld.h
 *
 *  Created on: Sep 9, 2012
 *      Author: leo
 */

#ifndef PHYSICSWORLD_H_
#define PHYSICSWORLD_H_

#include <fruitpunch/Elements/Element.h>
#include <fruitpunch/Graphics/Vertex.h>
#include <boost/shared_ptr.hpp>
#include <Box2D/Box2D.h>
#include <vector>
#include <map>

namespace fp_core {
namespace physics {

class Body;
class Shaper;
class PhysicsJoint;
class PhysicsShape;

/// A container for processing physics and detect collision events.
/**
 * Extends b2ContactListener so it can act as a wrapper to translate box2d
 * contact events to fruitpunch events.
 */
class PhysicsWorld : public Element, public b2ContactListener {
public:
	typedef boost::shared_ptr<PhysicsWorld> ref;

    PhysicsWorld();
    virtual ~PhysicsWorld();

    /// Makes the physics world ready to accept bodies and trigger contact events
    void init();

    /// Updates the physical world
    /**
     * Executed every frame, and is responsible for executing a single step
     * that updates the status of the bodies, contacts, and joints in the
     * physics world. The framerate can be set by setting the timeStep member
     * variable.
     */
    virtual void renderFrame();

    /// Converts an element to a box2d shape
    /**
     * The association between an element and a box2d shape is made by shapers.
     * Shapers can be registered by adding Shaper instances to the shapers
     * list. Will raise a Shaper runtime error if no shapers are found for that
     * element.
     */
    boost::shared_ptr<PhysicsShape> makeShapeFor(Element::ref element);

    /// Executed by the methods implemented to satisfy the b2ContactListener class.
    /**
     * This will transform a b2Contact reference into a ContactEvent and notify
     * the world about it.
     */
    void triggerContact(b2Contact& contact, std::string eventName);

    /// Checks if parent is a scene object. If it's not, raise an InvalidParent error.
    void onAdd();

    /// Indicates that a certain element is related to a certain fixture
    /**
     * This will be used during a ContactEvent, when we try to get which element
     * is related to the fixtures involved in the event.
     */
    void addFixtureToElementMapping(boost::shared_ptr<Element> element, b2Fixture * fixture);

    /// Removes the existing relation between a fixture and an element
    void removeFixtureToElementMapping(b2Fixture * fixture);

    /// Retrieves an element that is related to the provided fixture
    /**
     * The element has to be mapped using addFixtureToElementMapping.
     * It will return a null shared_ptr if the relation cannot be found.
     */
    boost::shared_ptr<Element> getElementFromFixture(b2Fixture * fixture);

    /// Returns the fixture associated with an element
    /**
     * Avoid using this function whenever necessary, since it is slower than
     * getElementFromFixture().
     */
    b2Fixture * getFixtureFromElement(boost::shared_ptr<Element> element);

    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

    // ---------------------------------------------------------------------------
	// Getters
	// ---------------------------------------------------------------------------

	const boost::shared_ptr<std::vector<Body> >          getBodies() const;
	point                                                getGravity() const;
	const std::vector<boost::shared_ptr<PhysicsJoint> >  getJoints() const;
	static boost::shared_ptr<PhysicsWorld>               getCurrent();
	float                                                getPixelSize() const;
	int                                                  getPositionIterations() const;
	const std::vector<boost::shared_ptr<Shaper> >&       getShapers() const;
	float                                                getTimestep() const;
	int                                                  getVelocityIterations() const;
	const boost::shared_ptr<b2World>                     getWorld() const;
	bool												 getBodiesSensorByDefault() const;

	// ---------------------------------------------------------------------------
	// Setters
	// ---------------------------------------------------------------------------
	void setBodies            (const boost::shared_ptr<std::vector<Body> > bodies);
	static void setCurrent    (boost::shared_ptr<PhysicsWorld> current);
	void setGravity           (point gravity);
	void setPixelSize         (float pixelSize);
	void setPositionIterations(int positionIterations);
	void setTimestep          (float timestep);
	void setVelocityIterations(int velocityIterations);
	void setBodiesSensorByDefault(bool isSensor);

private:
    float                                         mPixelSize;
    float                                         mTimestep;
    int                                           mVelocityIterations;
    int                                           mPositionIterations;
    point                                         mGravity;
    boost::shared_ptr<std::vector<Body> >         mBodies;
    boost::shared_ptr<b2World>                    mWorld;
    std::vector<boost::shared_ptr<Shaper> >       mShapers;
    std::vector<boost::shared_ptr<PhysicsJoint> > mJoints;
    static boost::shared_ptr<PhysicsWorld>        mCurrent;
    std::map<b2Fixture *, boost::weak_ptr<Element> >     mFixtureElementMapping;
    bool 										  mBodiesSensorByDefault;


};

} /* namespace physics */
} /* namespace fp_core */
#endif /* PHYSICSWORLD_H_ */
