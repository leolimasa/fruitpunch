/*
 * Element.h
 *
 *  Created on: 2012-05-21
 *      Author: leo
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_

#include <boost/shared_ptr.hpp>
#include <fruitpunch/Common/Observable.h>
#include <fruitpunch/Common/Vector.h>
#include <fruitpunch/Common/Iterator.h>

using namespace std;
using namespace fp_core::common;

namespace fp_core {

class Scene;

/// A generic container for everything that goes into a Scene
class Element : public common::Observable {
public:
  typedef boost::shared_ptr<Element> ref;

  Element();
  virtual ~Element();

  // ---------------------------------------------------------------------------
  // Member Methods
  // ---------------------------------------------------------------------------

  /// Adds an element to the children of the current element.
  /**
   * @return Element::ref the added element
   */
  virtual Element::ref add(Element::ref element);

  /// Adds an element as children, but does not set the element's parent
  virtual Element::ref addOrphan(Element::ref element);

  /// Removes a child Element equals to the one passed in the argument from the list of children.
  /**
   * @return Element::ref the removed element or a null shared ptr if the element was not found
   */
  virtual Element::ref remove(Element::ref element);

  /// Removes this element from its parent and does the same for the children
  virtual void destroy();

  // ---------------------------------------------------------------------------
  // Callbacks
  // ---------------------------------------------------------------------------
  /// Called when this element has been added to a scene or another element
  virtual void onAdd();

  /// Called when this element is removed from a scene or another element
  virtual void onRemove();

  /// Called by the scene every frame
  virtual void renderFrame();

  /// Called by the scene/app every millisecond
  /**
   * The main difference between a tick and a frame is that the tick
   * has an interval of at least one millisecond. This makes it possible
   * to implement logic that will maintain a consistent speed across
   * platforms.
   */
  virtual void tick();

  /// Called every frame and meant to be overriden
  virtual void onRender();

  // ---------------------------------------------------------------------------
  // Getters and Setters
  // ---------------------------------------------------------------------------
  boost::shared_ptr<Scene> getScene() const;
  void setScene(boost::shared_ptr<Scene> scene);
  boost::shared_ptr<fp_core::common::Collection> getChildren() const;
  Element::ref getParent() const;
  void setParent(Element::ref parent);

  template <class T>
  boost::shared_ptr<T> getChildOfType() {
	  boost::shared_ptr<T> child;
	  boost::shared_ptr<Iterator> it = mChildren->getIterator();
	  while (it->next()) {
		  child = boost::dynamic_pointer_cast<T>(it->get());
		  if (child) {
			  return (child); // found the child...return it
		  } // end if
	  }

	  return (boost::shared_ptr<T>()); // we didn't find the child of type...return NULL
  } // end getChildOfType


private:
  boost::shared_ptr<Scene>  mScene;
  boost::shared_ptr<Vector> mChildren;
  Element::ref              mParent;
  bool mChildChanged;
};

} /* namespace fp_core */
#endif /* ELEMENT_H_ */
