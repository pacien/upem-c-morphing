#include "common/geom.h"
#include "morpher/matrix.h"

CartesianMapping m(int x, int y) {
  return (CartesianMapping) {{x, y},
                             {x, y}};
}

CartesianVector v(int x, int y) {
  return (CartesianVector) {x, y};
}

bool mappings_equals(CartesianMapping m1, CartesianMapping m2) {
  return vector_equals(m1.origin, m2.origin) && vector_equals(m1.target, m2.target);
}

bool vector_equals(CartesianVector v1, CartesianVector v2) {
  return v1.x == v2.x && v1.y == v2.y;
}

IntVector triangle_area(CartesianVector v1, CartesianVector v2, CartesianVector v3) {
  return matrix_int_det2(v1.x - v3.x, v2.x - v3.x,
                         v1.y - v3.y, v2.y - v3.y);
}
