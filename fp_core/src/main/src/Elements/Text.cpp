
/*
 * Text.cpp
 *
 *  Created on: 2012-06-24
 *      Author: leo
 */

#include <fruitpunch/Elements/Text.h>
#include <fruitpunch/Common/Events.h>
#include <fruitpunch/Common/Runtime.h>
#include <fruitpunch/Common/NativeBridge.h>
#include <fruitpunch/Common/Observer.h>

using namespace fp_core::common;

namespace fp_core {

class FontObserver : public Observer {
public:
	Text * text;
	FontObserver(Text& text) {
		this->text = &text;
	}

	void action() {
		text->onFontChange();
	}
};

Text::Text(std::string text) {
	mText = text;
	mFont = Runtime::getCurrent()->getBridge()->defaultFont();
	mFont->setSize(30);
	setFont(mFont);
	Image::ref img = mFont->makeImage(mText);
	setImage(img);
	init();
	update();

}

Font::ref Text::getFont() const {
  return mFont;
}

std::string Text::getText() const {
	return mText;
}

void Text::setText(std::string text) {
	mText = text;
	mFontChanged = true;
}

void Text::setFont(Font::ref font) {
  mFont = font;
  Observer::ref obs(new FontObserver(*this));
  mFont->attachObserver(EV_PROPERTY_CHANGED, obs);
  mFontChanged = true;
}

void Text::onFontChange() {
  mFontChanged = true;
}

void Text::renderFrame() {
  Sprite::renderFrame();
  if (mFontChanged) {
	  update();
  }
}

void Text::update() {
  Image::ref img = mFont->makeImage(mText);
  setImage(img);
  setWidth(img->getWidth());
  setHeight(img->getHeight());
}

}
