#include "common/geom.h"
#include <assert.h>

static void test_square_area() {
  assert(square_area(v(0, 0), v(10, 0), v(10, 10)) == 100);
  assert(square_area(v(0, 0), v(0, 10), v(10, 10)) == -100);
}

static void test_cartesian_barycentric_vectors() {
  Triangle t = {{v(0, 0), v(10, 0), v(10, 10)}};
  CartesianVector c = v(3, 2);
  BarycentricVector bv = cartesian_to_barycentric(t, c);
  assert(barycentric_vector_equals(bv, b(0.7, 0.1)));
  assert(vector_equals(barycentric_to_cartesian(t, bv), c));
}

int main(int argc, char **argv) {
  test_square_area();
  test_cartesian_barycentric_vectors();
  return 0;
}
