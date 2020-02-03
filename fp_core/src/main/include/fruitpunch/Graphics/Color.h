/*
 * Color.h
 *
 *  Created on: May 28, 2012
 *      Author: leo
 */

#ifndef COLOR_H_
#define COLOR_H_

#include <fruitpunch/Common/Object.h>

namespace fp_core {

/**
 * Represents a 32 bit color in the RGBA format
 */
class Color : public common::Object {
public:
  Color();

  /// Creates a color with discreet rgba values
  Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

  /// Creates a color from a long number in the format RGBA
  Color(unsigned long hexColor);

  /// Creates a color using a hex value, or a long if you are hardcore enough
  /**
   * The hex value is in the format RGBA. So the example below:
   *
   * Color(0x00FF00FF)
   *
   * Will be r=0, g=255, b=0, a=255
   *
   * @param hexColor
   */
  void fromLong(unsigned long hexColor);

  /// Converts the color to a ulong in the pixel order RGBA
  unsigned long toLong();

  /// Returns the value of the byte at position byteIndex
  static unsigned char byteValue(unsigned long number, int byteIndex);

  unsigned char R;
  unsigned char G;
  unsigned char B;
  unsigned char A;

  void setRed(float red);
  void setGreen(float green);
  void setBlue(float blue);
  void setAlpha(float alpha);

  float getRed() const;
  float getGreen() const;
  float getBlue() const;
  float getAlpha() const;
};

} /* namespace fp_core */
#endif /* COLOR_H_ */
