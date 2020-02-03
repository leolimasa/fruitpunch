#include <armadillo>
#include <math.h>
#include <fruitpunch/Graphics/Matrices.h>
#include <fruitpunch/Graphics/Vertex.h>
#include <fruitpunch/Graphics/Renderer.h>
#include <vector>

#define PI180 0.0174532925

using namespace arma;
using namespace std;

namespace fp_core {

/**
 * Returns
 */
fmat33 rotation_matrix(float angle) {
  float rad = angle * PI180;

  fmat33 rot;
  rot << cos(rad) << -sin(rad) << 0 << endr
      << sin(rad) << cos(rad) << 0 << endr
      << 0 << 0 << 1 << endr;
  return rot;
}

fmat33 translation_matrix(point p) {
  // generates the translation matrix
  fmat33 trans;
  trans.eye();
  trans.at(0, 2) = p.x;
  trans.at(1, 2) = p.y;

  return trans;
}

fmat33 scale_matrix(point p) {
  fmat33 trans;
  trans.eye();
  trans.at(0, 0) = p.x;
  trans.at(1, 1) = p.y;

  return trans;
}

fmat33 to_local_space_matrix(point center) {
  center.x = -center.x;
  center.y = -center.y;
  return translation_matrix(center);
}

fmat33 to_global_space_matrix(point center) {
  return translation_matrix(center);
}

void apply_matrix_transformation(point * points, int size,
    Renderer& renderer, fmat33 transformation) {

  // create point array
  for (int i = 0; i < size; i++) {
    // gets the point

    point& p = points[i];
    //printf("Added %d,%d", m_vertices[i].position().x, m_vertices[i].position().y);
    // transforms the point
    points[i] = renderer.transform_point(p, transformation);
    //printf("Transformed (%f,%f) \n", parr[i].x, parr[i].y);
  }

}

}

