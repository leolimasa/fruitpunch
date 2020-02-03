/*
 * Png.h
 *
 *  Created on: 2012-06-06
 *      Author: leo
 */

#ifndef PNG_H_
#define PNG_H_

#include <fruitpunch/Resources/ImageResource.h>
#include <boost/shared_ptr.hpp>
#include <vector>

namespace fp_core {

class Png : public ImageResource {
public:
  Png();
  virtual ~Png();
  virtual void load(std::string fullPath);
  virtual boost::shared_ptr<Image> getImage();

private:
  boost::shared_ptr<std::vector<unsigned char> > mData;
  int mWidth;
  int mHeight;
};

} /* namespace fp_core */
#endif /* PNG_H_ */
