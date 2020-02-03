/*
 * TextureManager.cpp
 *
 *  Created on: Jul 24, 2013
 *      Author: leo
 */

#include <fruitpunch/Graphics/TextureManager.h>
#include <fruitpunch/Graphics/Image.h>
#include <fruitpunch/Graphics/Renderer.h>

namespace fp_core {
namespace graphics {

TextureManager::TextureManager() {
	// TODO Auto-generated constructor stub

}

TextureManager::~TextureManager() {
	// TODO Auto-generated destructor stub
}

void TextureManager::startFrame() {
	mFrameNumber = mFrameNumber++ % 10;
}

void TextureManager::renderImage(Image& img) {
	img.setCurrentFrame(mFrameNumber);
	if (!img.isTextureLoaded()) {
		mRenderer->addTexture(img);
		mCache.push_back(&img);
	}
}

void TextureManager::endFrame() {
	std::vector<Image*>::iterator it = mCache.begin();
	while (it != mCache.end()) {
		Image * img = *it;
		it++;
		if (it != mCache.end() && img->getCurrentFrame() != mFrameNumber) {
			mCache.erase(it);
			mRenderer->removeTexture(*img);
		}
	}

}

Renderer* TextureManager::getRenderer() {
	return mRenderer;
}

void TextureManager::setRenderer(Renderer* renderer) {
	mRenderer = renderer;
}

} /* namespace graphics */
} /* namespace fp_core */
