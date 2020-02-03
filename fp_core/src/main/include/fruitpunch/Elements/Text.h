
/*
 * Text.h
 *
 *  Created on: 2012-06-24
 *      Author: leo
 */

#ifndef TEXT_H_
#define TEXT_H_

#include <boost/shared_ptr.hpp>
#include <fruitpunch/Graphics/Sprite.h>
#include <fruitpunch/Resources/Font.h>

namespace fp_core {

/// A text that can be drawn on a scene
class Text : public Sprite {
public:
  typedef boost::shared_ptr<Text> ref;

  Text(std::string text);
  
  virtual void onFontChange();
  virtual void renderFrame();

  /// Updates the internal sprite with a new texture of the text
  void update();

  // ---------------------------------------------------------------------------
  // Getters
  // ---------------------------------------------------------------------------
  std::string getText() const;
  Font::ref getFont() const;

  // ---------------------------------------------------------------------------
  // Setters
  // ---------------------------------------------------------------------------
  void setText(std::string text);
  void setFont(Font::ref font);

private:
  Font::ref mFont;
  std::string mText;
  bool mFontChanged;
};

}

#endif
