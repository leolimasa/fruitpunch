/*
 * PhysicsBox.h
 *
 *  Created on: 2012-09-14
 *      Author: leo
 */

#ifndef PHYSICSBOX_H_
#define PHYSICSBOX_H_

#include <Box2D/Box2D.h>
#include <boost/shared_ptr.hpp>
#include <fruitpunch/Physics/PhysicsShape.h>

namespace fp_core {
namespace physics {

class PhysicsBox : public PhysicsShape {
public:
	typedef boost::shared_ptr<PhysicsBox> ref;

	PhysicsBox(float width, float height);
	virtual ~PhysicsBox();

    boost::shared_ptr<b2Shape> getBox2dShape(float scale);

	float getHeight() const;
	void setHeight(float height);
	float getWidth() const;
	void setWidth(float width);

private:
    float mWidth;
    float mHeight;
};

}
}
#endif /* PHYSICSBOX_H_ */
