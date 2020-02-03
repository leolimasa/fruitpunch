/*
 * PhysicsJoint.h
 *
 *  Created on: Sep 9, 2012
 *      Author: leo
 *
 *      Represents a physical joint between two bodies in space.
 *      Abstract class.
 */

#ifndef PHYSICSJOINT_H_
#define PHYSICSJOINT_H_

#include <Box2D/Box2D.h>
#include <boost/shared_ptr.hpp>
#include <fruitpunch/Elements/Element.h>
#include <fruitpunch/Physics/Body.h>
#include <vector>

namespace fp_core {
namespace physics {

class PhysicsWorld;

class PhysicsJoint : public Element {
public:
  PhysicsJoint();
  PhysicsJoint(boost::shared_ptr<Element> elementA, boost::shared_ptr<Element> elementB);
  virtual ~PhysicsJoint();

  //Abstract method responsible for creating a joint
  virtual boost::shared_ptr<b2JointDef> create();

  virtual void onAdd();

  // Returns the shared_ptr of the Body instance representing the Body that
  // is a children of mElementA/B
  virtual boost::shared_ptr<Body> retrieveBodyA();
  virtual boost::shared_ptr<Body> retrieveBodyB();
  const virtual boost::shared_ptr<PhysicsWorld> getWorld() const;

  const boost::shared_ptr<Element> getElementA();
  void setElementA(const boost::shared_ptr<Element> elementA);
  const boost::shared_ptr<Element> getElementB();
  void setElementB(const boost::shared_ptr<Element> elementB);

  b2Joint * getB2Joint();
  void setB2Joint(b2Joint *newB2Joint);

  virtual void onRemove();

private :
    boost::shared_ptr<PhysicsWorld>  mWorld;
    boost::shared_ptr<Element> mElementA;
    boost::shared_ptr<Element> mElementB;
    b2Joint *mB2Joint;
};

} /* namespace physics */
} /* namespace fp_core */
#endif /* PHYSICSJOINT_H_ */
