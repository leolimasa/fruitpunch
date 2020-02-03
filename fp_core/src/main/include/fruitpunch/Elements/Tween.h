/*
 * Tween.h
 *
 *  Created on: May 10, 2012
 *      Author: leo
 */

#ifndef TWEEN_H_
#define TWEEN_H_

#include <fruitpunch/Common/Property.h>
#include <fruitpunch/Elements/Playable.h>
#include <fruitpunch/Graphics/Primitive.h>
#include <boost/shared_ptr.hpp>

namespace fp_core {

class Tween : public Playable {
public:
  Tween();
  virtual void renderSingle(int frame);
  virtual int calculateDuration();

  /**
   * Should return a normalized function from which the tween will be calculated.
   *
   * A normalized function has boundaries between 0 and 1, where 0 is the start
   * of the tween, and 1 is the end. Those values will be provided by the step
   * argument.
   *
   * @param step
   * @return
   */
  virtual float interpolate(float step);
  virtual ~Tween();

  int getDuration() const;
  void setDuration(int duration);
  float getEndValue() const;
  void setEndValue(float endValue);
  boost::shared_ptr<common::Property> getProperty() const;
  void setProperty(boost::shared_ptr<common::Property> property);
  float getStartValue() const;
  void setStartValue(float startValue);

private:
  int mDuration;
  float mStartValue;
  float mEndValue;
  boost::shared_ptr<common::Property> mProperty;

};

} /* namespace fp_core */
#endif /* TWEEN_H_ */
