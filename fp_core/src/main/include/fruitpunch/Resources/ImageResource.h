/*
 * ImageResource.h
 *
 *  Created on: 2012-05-30
 *      Author: leo
 */

#ifndef IMAGERESOURCE_H_
#define IMAGERESOURCE_H_

#include <fruitpunch/Resources/Resource.h>
#include <string>
#include <fruitpunch/Graphics/Image.h>
#include <boost/shared_ptr.hpp>

namespace fp_core {

class ImageResource : public Resource {
public:
  ImageResource();
  virtual void load(std::string fullPath) =0;
  virtual boost::shared_ptr<Image> getImage() =0;
};

} /* namespace fp_core */
#endif /* IMAGERESOURCE_H_ */
