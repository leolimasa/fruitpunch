/*
 * Property.h
 *
 *  Created on: May 10, 2012
 *      Author: leo
 */

#ifndef PROPERTY_H_
#define PROPERTY_H_

#include <fruitpunch/Common/Object.h>
#include <fruitpunch/Common/Observable.h>
#include <fruitpunch/Common/Event.h>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

namespace fp_core {
namespace common{

/// A wrapper that allows changing a parameter of a class
/**
 * Abstract class.
 *
 * This class makes it possible to abstract the process of
 * assigning values to a member variable (or method) of any
 * object.
 *
 * For example:
 *
 * say we have an Animation class that changes the
 * position, scale, or rotation of an element every frame.
 *
 * It would be cumbersome to write a method for every property
 * of Element in the Animation class (changePosition, changeScale...),
 * and if we change the interface of Element, we would have to add
 * extra methods to Animation.
 *
 * Instead, we can wrap those properties each one in a single class
 * that extends Property, such as: class Alpha : public Property<Element, float>
 * This makes it possible to assign any property to Animation, like
 *
 * Element e;
 * Animation a;
 *
 * a.willChange(Alpha(e))
 *
 * The code above means that the animation will change the Alpha property
 * of Element. This is done by passing "e" through the Alpha wrapper.
 *
 * Using events instead of inheritance
 * -----------------------------------
 *
 * Property also fires a get/set event where an observer can be set to
 * set the property without the need to extend the class.
 *
 */
class Property : public Observable {
public:
  Property();
  virtual float get();
  virtual void set(float value);

};

} /* namespace common */
} /* namespace fp_core */
#endif /* PROPERTY_H_ */
