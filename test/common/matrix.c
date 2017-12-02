#include "common/matrix.h"
#include <assert.h>

static void test_matrix_int_det() {
  IntSquareMatrix matrix;
  IntVector *elements[3];

  matrix_reshape(elements, (IntVector[]) {-2, +2, -3,
                                          -1, +1, +3,
                                          +2, +0, -1}, 3, 3);

  matrix.dim = 3;
  matrix.elements = elements;

  assert(matrix_int_det(&matrix) == 18);
}

int main(int argc, char **argv) {
  test_matrix_int_det();
  return 0;
}
