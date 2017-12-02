#include "common/geom.h"

bool vector_equals(CartesianVector v1, CartesianVector v2) {
  return v1.x == v2.x && v1.y == v2.y;
}
