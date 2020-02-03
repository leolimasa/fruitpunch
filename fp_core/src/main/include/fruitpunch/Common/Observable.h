/*
 * Observable.h
 *
 *  Created on: 2012-02-29
 *      Author: leo
 */

#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

#include <list>
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>
#include <fruitpunch/Common/Object.h>

namespace fp_core {
namespace common {

class Observer;
class Event;

// ---------------------------------------------------------------------------
// Class Declaration
// ---------------------------------------------------------------------------
/// Allows a class to handle events.
/**
 *  When a class extends Observable, it is able to fire an event, and register
 *  handlers to events.
 *
 *  Example:
 *
 *  if I have a class called Square and I want
 *  an event fired every time someone clicks that Square, I would extend Square
 *  with an Observable. Then, whenever I detect a click, I can call
 *  Square->notify("click") and that will execute the action() method of all the
 *  observers registered in Square.
 */
class Observable : public Object {
public:
  Observable();
  virtual ~Observable();

  typedef boost::shared_ptr<Observable> Ptr;

  // ---------------------------------------------------------------------------
  // Member Methods
  // ---------------------------------------------------------------------------

  /// Attaches an Observer instance that will handle the event.
  /** The observer will be fired every time this class fires the event
   *  specified
   *  @param event The name of the event
   *  @param observer The observer instance that will be fired
   */
  virtual void attachObserver(std::string event, boost::shared_ptr<Observer> observer);

  /// Removes an Observer from handling an event in this class
  /** @param observer The observer to be removed
   */
  void detachObserver(boost::shared_ptr<Observer> observer);

  /// Notifies all the observers of an event
  /** Goes through all the observers that have been registered to an event by
   *  attachObserver, and fires each one.
   *  @param event The name of the event
   */
  void notify(boost::shared_ptr<Event> event);

  void removeAllObservers();

private:
  std::list<boost::shared_ptr<Observer> >  mObserver;
};

} /* namespace common */
} /* namespace fp_core */
#endif /* OBSERVABLE_H_ */
