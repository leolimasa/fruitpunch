/*
 * Animation.h
 *
 *  Created on: May 14, 2012
 *      Author: leo
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <fruitpunch/Elements/Playable.h>
#include <boost/shared_ptr.hpp>
#include <vector>

namespace fp_core {

class Animation : public Playable {
public:
  Animation();
  virtual int calculateDuration();
  virtual void renderSingle(int frame);
  virtual void start();
  virtual void stop();
  virtual void onFirstFrame();
  void add(boost::shared_ptr<Playable> playable);

private:
  std::vector<boost::shared_ptr<Playable> > mChildren;
};

} /* namespace fp_core */
#endif /* ANIMATION_H_ */
