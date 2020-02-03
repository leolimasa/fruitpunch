/*
 * SoundResource.h
 *
 * Created on: 2012-08-26
 * 	Author: Steven
 *
 * 	Represents a SoundResource. This is an abstract class used
 * 	as a template for all sound filetypes
 */

#ifndef SOUNDRESOURCE_H_
#define SOUNDRESOURCE_H_

#include <fruitpunch/Resources/Resource.h>
#include <string>
#include <fruitpunch/Elements/Sound.h>

namespace fp_core {

class SoundResource : public Resource {
public:
	SoundResource();
	virtual void load(std::string fullpath) =0;
	virtual boost::shared_ptr<Sound> getSound() =0;
};

} /* namespace fp_core */
#endif /*SOUNDRESOURCE_H_ */
