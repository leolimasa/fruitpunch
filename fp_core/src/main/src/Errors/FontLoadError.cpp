/*
 * ResourceLoadError.cpp
 *
 *  Created on: May 30, 2012
 *      Author: leo
 */

#include <fruitpunch/Errors/FontLoadError.h>
#include <fruitpunch/Errors/ErrorCodes.h>
#include <ft2build.h>

#include FT_FREETYPE_H

using namespace std;

namespace fp_core {

FontLoadError::FontLoadError(std::string extension,
    int code) : mFontErrorCode(code) {
}

int FontLoadError::getCode() {
  return FONT_LOAD_ERROR;
}

std::string FontLoadError::getDescription() {
  string desc = "Error unknown";

  switch (mFontErrorCode) {
  case (FT_Err_Unknown_File_Format):
    desc = "Font file format unknown";
  break;
  case (FT_Err_Corrupted_Font_Glyphs):
  case (FT_Err_Corrupted_Font_Header):
    desc = "The font file is corrupt";
  break;
  }

  string result = "You tried to load the font file '" + mPath + "'. However ";
  result += "there was an error while I was trying to decode it. The error was: ";
  result += desc;

  return desc;
}

std::string FontLoadError::getShortDescription() {
  string desc = "Could not load " + mPath + ". I cannot decode the file.";
  return desc;
}

}
 /* namespace fp_core */
