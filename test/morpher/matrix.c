#include "morpher/matrix.h"
#include <assert.h>

static void test_matrix_int_det2() {
  assert(matrix_int_det2(5, 7,
                         2, 3) == 1);
}

static void test_matrix_int_det3() {
  assert(matrix_int_det3(-2, +2, -3,
                         -1, +1, +3,
                         +2, +0, -1) == 18);
}

int main(int argc, char **argv) {
  test_matrix_int_det2();
  test_matrix_int_det3();
  return 0;
}
