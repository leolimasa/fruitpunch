/*
 * MockRenderer.cpp
 *
 *  Created on: Jul 22, 2012
 *      Author: leo
 */

#include <MockRenderer.h>
#include <armadillo>
#include <fruitpunch/Graphics/Vertex.h>

using namespace fp_core;

void MockRenderer::init(int width, int height) {
}

void MockRenderer::pre_render() {
}

void MockRenderer::post_render() {
}

arma::fmat33 MockRenderer::viewport() {
    arma::fmat33 mat;
    mat.eye();
    return mat;
}

void MockRenderer::render_polygon(float* float_array, float* uv_array,
        int vertices, Image& image, float alpha) {
}

point MockRenderer::transform_point(point p, fmat33 trans_matrix) {
    // creates the matrix the represents the vertex
    fmat::fixed<3,1> vmat;
    vmat << p.x << endr
          << p.y << endr
          << 1 << endr;

    // transform the vertex by multiplying its matrix by the transformation matrix
    fmat res = trans_matrix * vmat;

    // updates the vertex with the new transformation
    point newpos;
    newpos.x = res.at(0,0);
    newpos.y = res.at(1,0);
    return newpos;
}

void MockRenderer::unload() {
}

void MockRenderer::addTexture(Image& img) {
}

void MockRenderer::removeTexture(Image& img) {
}
