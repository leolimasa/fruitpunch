/*
 * Matrices.h
 *
 *  Created on: 2012-02-24
 *      Author: leo
 *
 * This is a helper file that provides functions that generates matrices
 * to be used on transformation calculations.
 */

#ifndef MATRICES_H_
#define MATRICES_H_

#include <fruitpunch/Graphics/Renderer.h>
#include <armadillo>
#include <vector>

namespace fp_core {

struct point;

/// Returns a rotation matrix given the angle
arma::fmat33 rotation_matrix(float angle);

/// Returns a translation matrix given the delta by p
arma::fmat33 translation_matrix(point p);

/// Returns a scale matrix with the x and y scale rations defined by p
arma::fmat33 scale_matrix(point p);

/// Returns a matrix that transforms to local space in regards to center
arma::fmat33 to_local_space_matrix(point center);

/// Returns a matrix that transforms to global space in regards to center
arma::fmat33 to_global_space_matrix(point center);

/// Applies a matrix transformation to an array of points
void apply_matrix_transformation(point * points, int size,
        Renderer& renderer, arma::fmat33 transformation);
}


#endif /* MATRICES_H_ */
