/*
 * Ogg.h
 *
 *
 *	Created on: 2012-08-26
 *		Author: Steven
 *
 *		Represents an Ogg Sound. The first of it's kind. This is
 *		where the sound data will be and will be decoded into a
 *		vector of chars for the buffer
 */

#ifndef OGG_H_
#define OGG_H_

#include <fruitpunch/Resources/SoundResource.h>
#include <boost/shared_ptr.hpp>
#include <vector>

namespace fp_core {

class Ogg : public SoundResource {
public:
	Ogg();

	// This will be doing the actual loading of the
	// ogg file into the system and decoding it.
	virtual void load(std::string fullPath);

	// Returns the instance of shared_pr<Sound>, which is now "sound"
	virtual boost::shared_ptr<Sound> getSound();

private:
	boost::shared_ptr<std::vector<char> >    mData;
	int mFreq;
	int mChannels;
};

} // end namespace fp_core
#endif
