/*
 * Tween.cpp
 *
 *  Created on: May 10, 2012
 *      Author: leo
 */

#include <fruitpunch/Elements/Tween.h>

using namespace fp_core::common;

namespace fp_core {

Tween::Tween() {
  mStartValue = 0;
  mEndValue = 0;
  mDuration = 0;

}

Tween::~Tween() {
  // TODO Auto-generated destructor stub
}

int Tween::getDuration() const {
  return mDuration;
}

void Tween::setDuration(int duration) {
  mDuration = duration;
}

float Tween::getEndValue() const {
  return mEndValue;
}

void Tween::setEndValue(float endValue) {
  mEndValue = endValue;
}

boost::shared_ptr<Property> Tween::getProperty() const {
  return mProperty;
}

void Tween::setProperty(
    boost::shared_ptr<Property> property) {
  mProperty = property;
}

float Tween::getStartValue() const {
  return mStartValue;
}

#include <iostream>

void Tween::renderSingle(int frame) {

  // Calculates the step, or the percentage where the animation is.
  // For example, if we are at the first frame of the animation,
  // step will be 0. If we are at the last frame of the animation,
  // step will be 1. If we are in the middle of the animation,
  // step will be 0.5.
  float step = (float) frame / ((float) mDuration - 1.0f);

  // Calculates the change in value
  float valueChange = mEndValue - mStartValue;

  // Returns the percentage of the position to be applied
  float percent = interpolate(step);

  // Applies the percentage to the property
  float value = mStartValue + (valueChange * percent);
  mProperty->set(value);

}

int Tween::calculateDuration() {
  return mDuration;
}

void Tween::setStartValue(float startValue) {
  mStartValue = startValue;
}

float Tween::interpolate(float step) {
  return step;

}

}
 /* namespace fp_core */
