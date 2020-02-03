/*
 * Image.h
 *
 *  Created on: 2012-03-19
 *      Author: leo
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include <boost/date_time.hpp>
#include <string>
#include <vector>
#include <fruitpunch/Graphics/Color.h>
#include <boost/shared_ptr.hpp>
#include <fruitpunch/Common/Object.h>

namespace fp_core {

// ---------------------------------------------------------------------------
// Class Declaration
// ---------------------------------------------------------------------------

/// Represents the raw data of an Image file, and loads files from the hard drive.
/**c
 * This class is able to automatically open a file from the hard drive, detect
 * its extension, and create a char array that represents the image in a pixel
 * format that OpenGl can understand.
 *
 * Currently, only the PNG file format is supported.
 */
class Image : public common::Object {
public:
  typedef boost::shared_ptr<Image> ref;

  enum FORMAT {
     RGBA,
     RGB,
     MASK,
     ARGB,
     BGRA,
     BGRA_MULT // The alpha is pre multiplied
   };

  Image();
  Image(std::string resourcePath);
  Image(boost::shared_ptr<Image> image);
  virtual ~Image();

  class PixelIterator {
  public:
    PixelIterator(Image * img);

    /// Points the iterator at the specified index
    /**
     * This is the absolute index to the char array, and not the index of the
     * pixel.
     * @param index
     */
    void goToIndex(int index);

    /// returns false if it reached the end of the image
    bool next();

    /// returns a pointer to the n byte in the current pixel
    unsigned char & get(int n);


    int mBytesPerPixel;
    int mCurrentPixel;
    Image * mImg;
    std::vector<unsigned char>::iterator mIt;

  };

  // ---------------------------------------------------------------------------
  // Member Methods
  // ---------------------------------------------------------------------------

  /// Returns the color of the pixel at the coordinates specified.
  /**
   * Images with different pixel orders will behave differently:
   *
   * RGBA: returns the color as it is
   * RGB: returns the color with a 1 alpha channel
   * MASK: sets all the three rgb components with the single byte value
   *
   * @param width
   * @param height
   * @return
   */
  Color pixelAt(int row, int col);

  /**
   * Converts the current image to an RGBA format. This will overwrite the
   * current image and add an extra channel to it if its not RGBA already.
   */
  void toRGBA();

  /**
   * Converts the entire image to a solid color and sets the alpha channel
   * to a value from 0 to 255 according to the value of each pixel.
   *
   * @param color
   */
  void fill(Color color);

  /**
   * Changes the color of the pixel at the specified coordinates.
   * @param row
   * @param col
   * @param color
   */
  void setPixel(int row, int col, Color color);

  /**
     * Changes the color of the pixel at the iterator
     * @param row
     * @param col
     * @param color
     */
  void setPixelAtIterator(PixelIterator it, Color color);

  /**
   * Sets the alpha channel based on pixel data of another image.
   * The target image must have the same width and height as this
   * one.
   * @return
   */
  void applyAlpha(boost::shared_ptr<Image> image);

  /**
   * Returns a pointer to the first byte in the image
   * @return char pointer
   */
  unsigned char * rawData();

  /**
   * Returns the amount of bytes per pixel according to the image format
   * as follows:
   *
   * RGBA: 4
   * RGB: 3
   * MASK: 1
   *
   * @return
   */
  int getBytesPerPixel();

  /// The color of the pixel at the specified iterator position
  Color pixelAtIterator(PixelIterator it);

  /// reorders the pixels so that the Y is flipped
  void flipY();

  /**
   * Copies the content of this image to another. This actually copies
   * the entire pixel array - not just a reference.
   *
   * @param image
   */
  void copyTo(boost::shared_ptr<Image> image);

  // ---------------------------------------------------------------------------
  // Static Member Methods
  // ---------------------------------------------------------------------------


  /// Total number of Image objects created
  /**
   * Returns the number of Image objects that have been loaded
   * so far. This number is also automatically used to generate
   * new image IDs.
   */
  static unsigned int getImageCount();


  // ---------------------------------------------------------------------------
  // Getters
  // ---------------------------------------------------------------------------
  //unsigned char *getData()   const;
  boost::shared_ptr<std::vector<unsigned char> >  getData() const;
  int                 getHeight() const;
  int                 getWidth()  const;
  unsigned int        getImageId() const;
  FORMAT              getFormat() const;
  int                 getCurrentFrame() const;
  unsigned int        getTextureId() const;

  // ---------------------------------------------------------------------------
  // Setters
  // ---------------------------------------------------------------------------
  //void setData        (unsigned char *data);
  void setFormat      (FORMAT format);
  void setData        (boost::shared_ptr<std::vector<unsigned char> > data);
  void setHeight      (int height);
  void setWidth       (int width);
  void setImageId     (unsigned int imageId);
  void setCurrentFrame(int currentFrame);
  void setTextureId   (unsigned int textureId);

	bool isTextureLoaded() const {
		return mTextureLoaded;
	}

	void setTextureLoaded(bool textureLoaded) {
		mTextureLoaded = textureLoaded;
	}

private:
  FORMAT                                         mFormat;
  int                                            mWidth;
  int                                            mHeight;
  boost::shared_ptr<std::vector<unsigned char> > mData;
  unsigned int                                   mImageId;
  unsigned int                                   mTextureId;
  bool                                           mTextureLoaded;
  int                                            mCurrentFrame;

  // ---------------------------------------------------------------------------
  // Static Member Variables
  // ---------------------------------------------------------------------------
  static unsigned int        m_image_count;

  // ---------------------------------------------------------------------------
  // Static Private Methods
  // ---------------------------------------------------------------------------

  /// Releases the m_data pointer if it has data in it
  void release_data();
};

} /* namespace fp_core */
#endif /* IMAGE_H_ */
