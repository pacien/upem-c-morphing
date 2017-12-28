#include "common/geom.h"
#include <math.h>
#include <common/geom.h>
#include "morpher/matrix.h"

static inline IntVector int_round(RealVector x) {
  return (IntVector) round(x);
}

CartesianMapping m(int x, int y) {
  return (CartesianMapping) {{x, y},
                             {x, y}};
}

CartesianVector v(int x, int y) {
  return (CartesianVector) {x, y};
}

BarycentricVector b(double a, double b) {
  return (BarycentricVector) {a, b};
}

bool mappings_equals(CartesianMapping m1, CartesianMapping m2) {
  return vector_equals(m1.origin, m2.origin) && vector_equals(m1.target, m2.target);
}

bool vector_equals(CartesianVector v1, CartesianVector v2) {
  return v1.x == v2.x && v1.y == v2.y;
}

bool barycentric_vector_equals(BarycentricVector b1, BarycentricVector b2) {
  return b1.a == b2.a && b1.b == b2.b;
}

IntVector square_area(CartesianVector v1, CartesianVector v2, CartesianVector v3) {
  return matrix_int_det2(v1.x - v3.x, v2.x - v3.x,
                         v1.y - v3.y, v2.y - v3.y);
}

BarycentricVector cartesian_to_barycentric(Triangle t, CartesianVector p) {
  RealVector total_area = square_area(t.v[0], t.v[1], t.v[2]);
  return (BarycentricVector) {square_area(t.v[1], t.v[2], p) / total_area,
                              square_area(t.v[2], t.v[0], p) / total_area};
}

CartesianVector barycentric_to_cartesian(Triangle t, BarycentricVector p) {
  return (CartesianVector) {int_round(p.a * (t.v[0].x - t.v[2].x) + p.b * (t.v[1].x - t.v[2].x) + t.v[2].x),
                            int_round(p.a * (t.v[0].y - t.v[2].y) + p.b * (t.v[1].y - t.v[2].y) + t.v[2].y)};
}
