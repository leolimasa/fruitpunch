/*
 * Transformable.h
 *
 *  Created on: 2012-02-25
 *      Author: leo
 */

#ifndef TRANSFORMABLE_H_
#define TRANSFORMABLE_H_

#include <fruitpunch/Graphics/Vertex.h>
#include <boost/shared_ptr.hpp>

namespace fp_core {

// ---------------------------------------------------------------------------
// Class Declaration
// ---------------------------------------------------------------------------

/// Interface to be implemented by any class that can be transformed
/**
 * Those are classes like Primitives and Group, that can be moved freely on the
 * window.
 */
class Transformable {
public:
	virtual void  setPosition(point pos) =0;
	virtual point getPosition() const =0;
	virtual void  setRotation(float angle) =0;
	virtual float getRotation() const =0;
	virtual void  setScale(point scal) =0;
	virtual point getScale() const =0;
};

typedef boost::shared_ptr<Transformable> TransformablePtr;

}

#endif /* TRANSFORMABLE_H_ */
