/*
 * Sprite.h
 *
 *  Created on: 2012-03-05
 *      Author: leo
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include <fruitpunch/Graphics/Primitive.h>
#include <fruitpunch/Graphics/Image.h>
#include <boost/shared_ptr.hpp>
#include <string.h>

namespace fp_core {

/// CLASS UNDER CONSTRUCTION
class Sprite : public Primitive {
public:
  typedef boost::shared_ptr<Sprite> ref;

  Sprite();
  Sprite(std::string image);
  Sprite(boost::shared_ptr<Image> image);
  void setImage(boost::shared_ptr<Image> image);
  virtual ~Sprite();
  void init();
  void crop(float x, float y, float width, float height);

private:

};

} /* namespace fp_core */
#endif /* SPRITE_H_ */
