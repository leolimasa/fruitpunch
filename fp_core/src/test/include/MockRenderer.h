/*
 * MockRenderer.h
 *
 *  Created on: Jul 22, 2012
 *      Author: leo
 */

#ifndef MOCKRENDERER_H_
#define MOCKRENDERER_H_

#include <fruitpunch/Graphics/Renderer.h>

using namespace fp_core;

class MockRenderer: public Renderer {
public:
    void init(int width, int height);
    void pre_render();
    void post_render();
    arma::fmat33 viewport();
    void render_polygon(float * float_array, float * uv_array, int vertices,
            Image& image, float alpha);
    point transform_point(point p, fmat33 trans_matrix);
    void addTexture(Image& img);
    void removeTexture(Image& img);
    void unload();
};

#endif /* MOCKRENDERER_H_ */
