/*
 * Ogg.cpp
 *
 * Created on: 2012-08-26
 * 		Author: Steven
 */

#include <fruitpunch/Resources/Ogg.h>
#include <fruitpunch/Elements/Sound.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <vorbis/vorbisfile.h>
#include <cstdio>
#include <iostream>

#define BUFFER_SIZE 32768       // 32 KB buffers

using namespace std;

namespace fp_core {


Ogg::Ogg() : SoundResource() {
}

void Ogg::load(std::string fullPath) {
    boost::shared_ptr<vector<char> > bufferData(new vector<char>);                // The sound buffer data from file
	boost::shared_ptr<vector<char> > sound(new vector<char>);
	OggVorbis_File oggFile;

	// convert this piece of shit
	const char * fullPathUsable = fullPath.c_str();
	ov_fopen(fullPathUsable, &oggFile); // 16 bit audio file...

    int endian = 0;                         // 0 for Little-Endian, 1 for Big-Endian
    int bitStream;
    long bytes;
    char array[BUFFER_SIZE];                // Local fixed size array
    vorbis_info *pInfo;

    // Get some information about the OGG file
    pInfo = ov_info(&oggFile, -1);

    // Keep reading until all is read
    do{
        // Read up to a buffer's worth of decoded sound data
        bytes = ov_read(&oggFile, array, BUFFER_SIZE, endian, 2, 1, &bitStream);

        if (bytes < 0){
            ov_clear(&oggFile);
            cerr << "Error decoding " << "this" << "..." << endl;
            //exit(-1);
            }
        // end if

        // Append to end of buffer
        bufferData->insert(bufferData->end(), array, array + bytes);
        }
    while (bytes > 0);

	// get what we need
	mData = bufferData;
	mFreq = pInfo->rate;
	mChannels = pInfo->channels;

    // Clean up!
    ov_clear(&oggFile);
} // end Ogg::load

// make the sound object and return it...
boost::shared_ptr<Sound> Ogg::getSound() {
	boost::shared_ptr<Sound> mySound(new Sound());
	mySound->setData(mData);
	mySound->setFreq(mFreq);
	mySound->setChannels(mChannels);
	return mySound;
} // end makeSoundObj

} // end namespace fp_core
