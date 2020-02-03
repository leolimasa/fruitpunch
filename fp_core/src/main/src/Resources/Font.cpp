/*
 * Font.cpp
 *
 *  Created on: 2012-06-13
 *      Author: leo
 */

#include <fruitpunch/Resources/Font.h>
#include <fruitpunch/Errors/FontLoadError.h>
#include <boost/shared_ptr.hpp>
#include <fruitpunch/Common/Runtime.h>
#include <fruitpunch/Common/Events.h>
#include <fruitpunch/Common/Event.h>
#include <cairo/cairo-ft.h>

using namespace std;
using namespace fp_core::common;

namespace fp_core {

Font::Font() : Resource() {
  mAntialias = true;
  mAlignment = RIGHT;
  mColor = boost::shared_ptr<Color>(new Color(0x000000FF));
  mLineSpacing = 10;
  mSize = 50;
}

// ____________________________________________________________________________

Font::Font(string path) : Resource() {
  boost::shared_ptr<Font> font = boost::static_pointer_cast<Font>(
      Runtime::getCurrent()->loadResource(path));
  mAlignment = font->getAlignment();
  mColor = font->getColor();
  mLibrary = font->getFtLibrary();
  mFace = font->getFtFace();
  mSize = font->getSize();
  mLineSpacing = font->getLineSpacing();
}

// ____________________________________________________________________________

void Font::load(std::string fullPath) {
  int error = 0;
  error = FT_Init_FreeType(&mLibrary);
  if (error) {
    throwError(fullPath, error);
    return;
  }
  error = FT_New_Face(mLibrary, fullPath.c_str(), 0, &mFace);
  if (error) {
    throwError(fullPath, error);
    return;
  }

  // we do this to update the face information
  setSize(mSize);

  this->notify(Event::ref(new Event(EV_PROPERTY_CHANGED)));
}

// ____________________________________________________________________________

point Font::canvasDimensions(const std::vector<std::string>& lines,
    cairo_t* cairoContext) {

  int height = (mSize + mLineSpacing) * lines.size();
  double longest = 0;
  vector<string>::const_iterator it = lines.begin();
  for (; it != lines.end(); it++) {
    cairo_text_extents_t extents;
    cairo_text_extents(cairoContext, it->c_str(), &extents);
    if (extents.x_advance > longest) {
      longest = extents.x_advance;
    }
  }

  point p;
  p.x = longest;
  p.y = height;
  return p;
}

// ____________________________________________________________________________

void Font::throwError(std::string path, int code) {
  boost::shared_ptr < RuntimeError > err(new FontLoadError(path, code));
  Runtime::getCurrent()->addError(err);
}

// ____________________________________________________________________________

point Font::penPosition(int lineNumber, std::string text, cairo_t* cairoContext,
    point canvasSize) {

  int x;

  // the negative line spacing at the end is necessary to not have the first
  // line spaced out. Do the math.
  int y = (lineNumber * (mSize + mLineSpacing)) - mLineSpacing;

  cairo_text_extents_t extents;
  cairo_text_extents(cairoContext, text.c_str(), &extents);
  int textWidth = extents.x_advance;

  switch (mAlignment) {
  case (RIGHT):
    x = canvasSize.x - textWidth;
    break;
  case (CENTER):
    x = (canvasSize.x / 2) - (textWidth / 2);
    break;
  default:
    x = 0;
    break;
  }

  point p;
  p.x = x;
  p.y = y;
  return p;
}

// ____________________________________________________________________________

boost::shared_ptr<Image> Font::makeImage(std::string text) {
  cairo_font_face_t * face;

  // ---------------------------------------------------------------------------
  // Break down text into lines
  // ---------------------------------------------------------------------------
  vector<string> lines;
  string strbuffer = "";
  for (int i=0; i<text.length(); i++) {
    if (text[i] == '\n') {
      lines.push_back(strbuffer);
      strbuffer = "";
      continue;
    }

    strbuffer += text[i];
  }
  lines.push_back(strbuffer);

  // ---------------------------------------------------------------------------
  // Creates a temporary cairo context to get the canvas size
  // ---------------------------------------------------------------------------
  cairo_rectangle_t rec;
  rec.height = 2;
  rec.width = 2;
  rec.x = 0;
  rec.y = 0;
  cairo_surface_t *tmpSurface = cairo_recording_surface_create(CAIRO_CONTENT_COLOR_ALPHA, &rec);
  cairo_t * tmpContext = cairo_create(tmpSurface);

  // ---------------------------------------------------------------------------
  // Calculate the canvas size and allocate important variables
  // ---------------------------------------------------------------------------

  // we need to know what font we are using so we can calculate the canvas size
  face = loadFontData(tmpContext);

  // get the canvas size
  point canvas = canvasDimensions(lines, tmpContext);

  // creates the pen
  point pen;

  cairo_surface_finish(tmpSurface);
  cairo_surface_destroy(tmpSurface);
  cairo_destroy(tmpContext);
  cairo_font_face_destroy(face);

  // ---------------------------------------------------------------------------
  // Creates the real canvas
  // ---------------------------------------------------------------------------
  long dataSize = canvas.x * canvas.y * 4;
  unsigned char * imgBufferPtr = new unsigned char[dataSize];
  cairo_surface_t *surface = cairo_image_surface_create_for_data(
           imgBufferPtr, CAIRO_FORMAT_ARGB32, canvas.x, canvas.y, canvas.x * 4 );
  cairo_t * context = cairo_create(surface);

  // ---------------------------------------------------------------------------
  // Clears any junk there might be at the surface
  // ---------------------------------------------------------------------------
  cairo_set_operator (context, CAIRO_OPERATOR_CLEAR);
  cairo_paint (context);
  cairo_set_operator(context, CAIRO_OPERATOR_OVER);

  // ---------------------------------------------------------------------------
  // Renders the lines
  // ---------------------------------------------------------------------------
  face = loadFontData(context);
  vector<string>::iterator it = lines.begin();
  int i = 1;
  for (; it != lines.end(); it++) {
    pen = penPosition(i, *it, context, canvas);
    cairo_move_to(context, pen.x, pen.y);
    cairo_text_path(context, it->c_str());
    i++;
  }

  // fills the rendered text with the color
  cairo_fill(context);
  cairo_surface_flush(surface);

  // ---------------------------------------------------------------------------
  // Makes the image
  // ---------------------------------------------------------------------------
  boost::shared_ptr<vector<unsigned char> > imgBuffer(new vector<unsigned char>);
  imgBufferPtr = cairo_image_surface_get_data(surface);
  for (int i=0; i < dataSize; i++) {
    imgBuffer->push_back(imgBufferPtr[i]);
  }

  cairo_surface_finish(surface);
  cairo_surface_destroy(surface);
  cairo_destroy(context);
  cairo_font_face_destroy(face);
  delete imgBufferPtr;

  boost::shared_ptr<Image> img(new Image());
  img->setWidth(canvas.x);
  img->setHeight(canvas.y);
  img->setFormat(Image::BGRA_MULT);
  img->setData(imgBuffer);
  img->toRGBA();
  img->flipY();
  return img;
}

// ____________________________________________________________________________

cairo_font_face_t* Font::loadFontData(cairo_t* cairoContext) {

  // face
  cairo_font_face_t * face = cairo_ft_font_face_create_for_ft_face(mFace, 0);
  cairo_set_font_face(cairoContext, face);
  cairo_set_font_size(cairoContext, mSize );

  // antialias
  cairo_font_options_t * fontOptions = cairo_font_options_create();
  if (mAntialias) {
    cairo_font_options_set_antialias(fontOptions, CAIRO_ANTIALIAS_SUBPIXEL);
  } else {
    cairo_font_options_set_antialias(fontOptions, CAIRO_ANTIALIAS_NONE);
  }
  cairo_set_font_options(cairoContext, fontOptions);

  // color
  double red = (double) (mColor->R) / 255.0;
  double green = (double) (mColor->G) / 255.0;
  double blue = (double) (mColor->B) / 255.0;
  double alpha = (double) (mColor->A) / 255.0;
  cairo_set_source_rgba(cairoContext, red, green, blue, alpha);

  return face;
}

// ---------------------------------------------------------------------------
// Getters and Setters
// ---------------------------------------------------------------------------

FT_Library Font::getFtLibrary() const {
  return mLibrary;
}

FT_Face Font::getFtFace() const {
  return mFace;
}

Font::ALIGNMENT Font::getAlignment() const {
  return mAlignment;
}

void Font::setAlignment(ALIGNMENT alignment) {
  mAlignment = alignment;
  this->notify(Event::ref(new Event(EV_PROPERTY_CHANGED)));
}

bool Font::isAntialias() const {
  return mAntialias;
}

void Font::setAntialias(bool antialias) {
  mAntialias = antialias;
  this->notify(Event::ref(new Event(EV_PROPERTY_CHANGED)));
}

bool Font::isBold() const {
  return mBold;
}

void Font::setBold(bool bold) {
  mBold = bold;
  this->notify(Event::ref(new Event(EV_PROPERTY_CHANGED)));
}

boost::shared_ptr<Color> Font::getColor() const {
  return mColor;
}

void Font::setColor(boost::shared_ptr<Color> color) {
  mColor = color;
  this->notify(Event::ref(new Event(EV_PROPERTY_CHANGED)));
}

bool Font::isItalic() const {
  return mItalic;
}

void Font::setItalic(bool italic) {
  mItalic = italic;
  this->notify(Event::ref(new Event(EV_PROPERTY_CHANGED)));
}

int Font::getLineSpacing() const {
  return mLineSpacing;
}

void Font::setLineSpacing(int lineSpacing) {
  mLineSpacing = lineSpacing;
  this->notify(Event::ref(new Event(EV_PROPERTY_CHANGED)));
}

int Font::getSize() const {
  return mSize;
}

void Font::setSize(int size) {
  mSize = size;
  this->notify(Event::ref(new Event(EV_PROPERTY_CHANGED)));
}

}/* namespace fp_core */
