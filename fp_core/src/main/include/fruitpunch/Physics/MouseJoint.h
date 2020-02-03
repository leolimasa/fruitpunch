/*
 * MouseJoint.h
 *
 *  Created on: Nov 4,2012
 *      Author: Steven
 */

#ifndef MOUSEJOINT_H_
#define MOUSEJOINT_H_

#include <fruitpunch/Physics/PhysicsJoint.h>
#include <boost/shared_ptr.hpp>
#include <Box2D/Box2D.h>
#include <fruitpunch/Elements/Element.h>


namespace fp_core {
namespace physics {

class MouseJoint : public PhysicsJoint {
public:
	typedef boost::shared_ptr<MouseJoint> ref;

	MouseJoint();
	MouseJoint(boost::shared_ptr<Element> elementA,
			boost::shared_ptr<Element> elementB);
	virtual ~MouseJoint();
	virtual boost::shared_ptr<b2JointDef> create();
	void update(point newLocation);
private:
	boost::shared_ptr<b2MouseJoint> m_b2MouseJoint;
};
} /* namespace fp_core */
} /* namespace fp_core::physics */
#endif /* MOUSEJOINT_H_ */
