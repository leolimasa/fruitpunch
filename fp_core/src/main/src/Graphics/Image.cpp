/*
 * Image.cpp
 *
 *  Created on: 2012-03-19
 *      Author: leo
 */

#include <fruitpunch/Graphics/Image.h>
#include <boost/algorithm/string.hpp>
#include <boost/shared_ptr.hpp>
#include <fruitpunch/Resources/ImageResource.h>
#include <fruitpunch/Common/Runtime.h>
#include <vector>

using namespace std;
using namespace fp_core::common;

namespace fp_core {

unsigned int Image::m_image_count = 0;

Image::Image() : Object(), mTextureLoaded(false) {
	mData = boost::shared_ptr<vector<unsigned char> >(new vector<unsigned char>);
	mImageId = m_image_count;
	m_image_count++;

}

Image::Image(std::string resourcePath) : Object(), mTextureLoaded(false) {
  boost::shared_ptr<ImageResource> res =  boost::static_pointer_cast<ImageResource>(
      Runtime::getCurrent()->loadResource(resourcePath));
  boost::shared_ptr<Image> img = res->getImage();

  setWidth(img->getWidth());
  setHeight(img->getHeight());
  setFormat(img->getFormat());
  setData(img->getData());

  mImageId = m_image_count;
  m_image_count++;
  Runtime::getCurrent()->print("Loaded image " + resourcePath, Runtime::MSG_INFO);
}

Image::Image(boost::shared_ptr<Image> image) : Object(), mTextureLoaded(false) {
  mImageId = m_image_count;
  m_image_count++;

}


Image::~Image() {
}

Color Image::pixelAt(int row, int col) {
  int index = (row * mWidth + col) * getBytesPerPixel();

  PixelIterator it(this);
  it.goToIndex(index);
  return pixelAtIterator(it);

}

void Image::toRGBA() {
  if (mFormat == RGBA) return;

  boost::shared_ptr < vector<unsigned char> > data(new vector<unsigned char>);
  PixelIterator it(this);
  do {
    Color c = pixelAtIterator(it);
    data->push_back(c.R);
    data->push_back(c.G);
    data->push_back(c.B);
    data->push_back(c.A);
  } while (it.next());
  mData = data;
  setFormat (RGBA);
}

void Image::fill(Color color) {
  boost::shared_ptr < vector<unsigned char> > data(new vector<unsigned char>);
  PixelIterator it(this);
  do {
    Color c = pixelAtIterator(it);
    long alpha = (c.R + c.G + c.B) / 3;
    data->push_back(color.R);
    data->push_back(color.G);
    data->push_back(color.B);
    data->push_back(alpha);
  } while (it.next());
  mData = data;
  setFormat (RGBA);
}

void Image::setPixel(int row, int col, Color color) {
  int index = (row * mWidth + col) * getBytesPerPixel();
  PixelIterator it(this);
  it.goToIndex(index);
  setPixelAtIterator(it, color);
}

int Image::getBytesPerPixel() {
  switch (mFormat) {
  case (RGB):
    return 3;
  case (ARGB):
  case (RGBA):
  case (BGRA_MULT):
    return 4;
  case (MASK):
    return 1;
  }
}

unsigned char* Image::rawData() {
  return &(*mData)[0];
}

Color Image::pixelAtIterator(PixelIterator it) {
  // checks if the buffer has anything in it. If its empty, just return white
  if (mData->size() == 0) {
    return Color(255,255,255,255);
  }

  switch (mFormat) {
  case (RGBA):
    return Color(it.get(0), it.get(1), it.get(2), it.get(3));
    break;
  case (RGB):
    return Color(it.get(0), it.get(1), it.get(2), 255);
  case (MASK):
    return Color(it.get(0), it.get(0), it.get(0), 255);
    break;
  case (ARGB):
    return Color(it.get(1), it.get(2), it.get(3), it.get(0));
    break;
  case(BGRA):
    return Color(it.get(2), it.get(1), it.get(0), it.get(3));
    break;
  case(BGRA_MULT):
    double alpha = (double) it.get(3) / (double) 255.0;
    if (alpha == 0) {
      return Color(0x000000);
    }
    return Color(it.get(2) / alpha,
        it.get(1) / alpha,
        it.get(0) / alpha,
        it.get(3));
  }
}



void Image::flipY() {
  vector<unsigned char>::iterator it = mData->begin();
  int width = getBytesPerPixel() * mWidth;
  boost::shared_ptr < vector<unsigned char> > flipped(new vector<unsigned char>);
  flipped->reserve(mData->size());
  for (int row = mHeight - 1; row >= 0; row--) {
    for (int col = 0; col < width; col++) {
      int index = row * width + col;
      flipped->push_back((*mData)[index]);
    }
  }

  mData = flipped;
}

void Image::applyAlpha(boost::shared_ptr<Image> mask) {
  PixelIterator thisIt(this);
  PixelIterator maskIt(mask.get());

  do {
    Color maskPix = mask->pixelAtIterator(maskIt);
    Color thisPix = pixelAtIterator(thisIt);
    unsigned char alpha = (maskPix.R + maskPix.G + maskPix.B) / 3;
    thisPix.A = alpha;
    setPixelAtIterator(thisIt, thisPix);
    thisIt.next();
  } while (maskIt.next());
}

void Image::setPixelAtIterator(PixelIterator it, Color color) {
  unsigned char pixel;

  switch (mFormat) {
  case (RGB):
    it.get(0) = color.R;
    it.get(1) = color.G;
    it.get(2) = color.B;
    break;
  case (RGBA):
    it.get(0) = color.R;
    it.get(1) = color.G;
    it.get(2) = color.B;
    it.get(3) = color.A;
    break;
  case (MASK):
    pixel = 0.3f * color.R + 0.59f * color.G + 0.11f * color.B;
    it.get(0) = pixel;
    break;
  case (ARGB):
    it.get(0) = color.A;
    it.get(1) = color.R;
    it.get(2) = color.G;
    it.get(3) = color.B;
    break;
  case (BGRA):
    it.get(0) = color.B;
    it.get(1) = color.G;
    it.get(2) = color.R;
    it.get(3) = color.A;
    break;
  case (BGRA_MULT):
    double alpha = (double) color.A / (double) 255.0;
    char B = color.B * alpha;
    it.get(0) = color.B * alpha;
    it.get(1) = color.G * alpha;
    it.get(2) = color.R * alpha;
    it.get(3) = color.A;
    break;

  }
}

void Image::copyTo(boost::shared_ptr<Image> image) {

  image->setWidth(getWidth());
  image->setHeight(getHeight());
  image->setFormat(getFormat());

  // copies the image bytes
  boost::shared_ptr<vector<unsigned char> > dataCopy(new vector<unsigned char>);
  vector<unsigned char>::iterator it = mData->begin();
  for (; it != mData->end(); it++) {
    dataCopy->push_back(*it);
  }

  image->setData(dataCopy);
}

void Image::release_data() {
  if (mData != NULL) {
    //delete m_data;
  }
}

void Image::setData(boost::shared_ptr<std::vector<unsigned char> > data) {
  mData = data;
}

boost::shared_ptr<vector<unsigned char> > Image::getData() const {
  return mData;
}

int Image::getHeight() const {
  return mHeight;
}

int Image::getWidth() const {
  return mWidth;
}

void Image::setHeight(int height) {
  mHeight = height;
}

void Image::setWidth(int width) {
  mWidth = width;
}

unsigned int Image::getImageId() const {
  return mImageId;
}

void Image::setImageId(unsigned int imageId) {
  mImageId = imageId;
}

unsigned int Image::getImageCount() {
  return m_image_count;
}

Image::PixelIterator::PixelIterator(Image* img) : mImg(img) {
  mIt = img->getData()->begin();
}

bool Image::PixelIterator::next() {
  mIt += mImg->getBytesPerPixel();

  return (mIt != mImg->getData()->end());
}
void Image::PixelIterator::goToIndex(int index) {
  mIt = mImg->getData()->begin() + index;
}

unsigned char & Image::PixelIterator::get(int n) {
  vector<unsigned char>::iterator itCopy = mIt;
  itCopy += n;
  return *itCopy;
}

Image::FORMAT Image::getFormat() const {
  return mFormat;
}

void Image::setFormat(FORMAT format) {
  mFormat = format;}

int Image::getCurrentFrame() const {
	return mCurrentFrame;
}

void Image::setCurrentFrame(int currentFrame) {
	mCurrentFrame = currentFrame;
}

unsigned int Image::getTextureId() const {
	return mTextureId;
}

void Image::setTextureId(unsigned int textureId) {
	mTextureId = textureId;
}


}
/* namespace fp_core */


