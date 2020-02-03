/*
 * Png.cpp
 *
 *  Created on: 2012-06-06
 *      Author: leo
 */

#include <fruitpunch/Resources/Png.h>
#include <fruitpunch/Resources/lodepng.h>
#include <fruitpunch/Graphics/Image.h>
#include <vector>
#include <string>
#include <stdio.h>

using namespace std;

namespace fp_core {

void Png::load(std::string fullPath) {

  vector<unsigned char> buffer;
  boost::shared_ptr < vector<unsigned char> > image(new vector<unsigned char>);

  unsigned width, height;

  lodepng::load_file(buffer, fullPath);
  // decode
  unsigned error = lodepng::decode(*image, width, height, fullPath);
  // old decoder
  //lodepng::Decoder decoder;
  if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

  mData = image;
  mWidth = width;
  mHeight = height;

}

boost::shared_ptr<Image> Png::getImage() {
  boost::shared_ptr<Image> img(new Image());
  img->setFormat(Image::RGBA);
  img->setWidth(mWidth);
  img->setHeight(mHeight);
  img->setData(mData);
  img->flipY();
  return img;
}

fp_core::Png::Png() : ImageResource() {
}

fp_core::Png::~Png() {
}

}/* namespace fp_core */


