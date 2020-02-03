/*
 * TextureManager.h
 *
 *  Created on: Jul 24, 2013
 *      Author: leo
 */

#ifndef FPCORE_GRAPHICS_TEXTUREMANAGER_H_
#define FPCORE_GRAPHICS_TEXTUREMANAGER_H_

#include <vector>

namespace fp_core {

class Image;
class Renderer;

namespace graphics {

/**
 * Memory manager of textures for any Renderer. Images that are not used in a
 * frame are automatically removed from the renderer's texture cache by calling
 * renderer.removeTexture.
 */
class TextureManager {
public:
	TextureManager();
	virtual ~TextureManager();

	/// Should be called on the start of a frame.
	/**
	 * Will increment the frameNumber by one, mod 100.
	 */
	void startFrame();

	/// Should be called when an image is requested to be rendered, mid frame.
	/**
	 * Will set the img.currentFrame to the same value as this.currentFrame.
	 * Also, if the image's textureId is 0, calls renderer.addTexture(img) and
	 * adds that image to the cache vector.
	 */
	void renderImage(Image& img);

	/// Disposes of any unused textures in the cache
	/**
	 * Should be called when all the polygons are done rendering, and will
	 * dispose of any textures not used during the current frame. Will cycle
	 * through the cache and call renderer.remove(img) on any images that have
	 * a frameNumber different than the current frame.
	 */
	void endFrame();
	Renderer* getRenderer();
	void setRenderer(Renderer* renderer);

private:
	int mFrameNumber;
	std::vector<Image*> mCache;
	Renderer * mRenderer;
};

} /* namespace graphics */
} /* namespace fp_core */
#endif /* TEXTUREMANAGER_H_ */
