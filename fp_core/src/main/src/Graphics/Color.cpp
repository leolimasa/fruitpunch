/*
 * Color.cpp
 *
 *  Created on: May 28, 2012
 *      Author: leo
 */

#include <fruitpunch/Graphics/Color.h>
#include <math.h>

using namespace std;

namespace fp_core {

Color::Color() : Object() {
}

Color::Color(unsigned long hexColor) : Object() {
  fromLong(hexColor);
}

Color::Color(unsigned char r, unsigned char g, unsigned char b,
    unsigned char a) : Object() {
  A = a;
  B = b;
  G = g;
  R = r;
}

void Color::fromLong(unsigned long hexColor) {
  R = byteValue(hexColor, 3);
  G = byteValue(hexColor, 2);
  B = byteValue(hexColor, 1);
  A = byteValue(hexColor, 0);
}

unsigned long Color::toLong() {
  unsigned long result = A * pow(256.0, 0) + B * pow(256.0, 1)
      + G * pow(256.0, 2) + R * pow(256.0, 3);
  return result;
}

unsigned char Color::byteValue(unsigned long number, int byteIndex) {
  unsigned long bitmask = 255 * pow((double) (256), byteIndex);
  unsigned long result = number & bitmask;
  int shifted = result >> (byteIndex * 8);

  return shifted;
}

void Color::setRed(float red) {
  R = red;
}

void Color::setGreen(float green) {
  G = green;
}

void Color::setBlue(float blue) {
  B = blue;
}

void Color::setAlpha(float alpha) {
  A = alpha;
}

float Color::getRed() const {
  return R;
}

float Color::getGreen() const {
  return G;
}

float Color::getBlue() const {
  return B;
}

float Color::getAlpha() const {
  return A;
}

} /* namespace fp_core */
