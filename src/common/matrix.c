#include "common/matrix.h"
#include <assert.h>
#include <memory.h>
#include <stdlib.h>
#include "common/mem.h"

static inline IntSquareMatrix *matrix_without_row(IntSquareMatrix *target, IntSquareMatrix *origin,
                                                  IntVector omitted_row) {
  int origin_row, target_row;

  for (origin_row = 0, target_row = 0; origin_row < origin->dim; ++origin_row)
    if (origin_row != omitted_row)
      target->elements[target_row++] = origin->elements[origin_row];

  return target;
}

static inline IntVector det_dev_sign(IntVector row, IntVector col) {
  assert(row > 0 && col > 0);
  return ((row + col) % 2 == 0) ? 1 : -1;
}

static inline IntVector det_reduce(IntSquareMatrix *matrix) {
  IntSquareMatrix sub_matrix;
  int row;
  IntVector det = 0;

  assert(matrix->dim > 2);

  sub_matrix.dim = matrix->dim - 1;
  sub_matrix.elements = malloc_or_die(sub_matrix.dim * sizeof(IntVector *));

  for (row = 0; row < matrix->dim; ++row)
    det += matrix->elements[row][matrix->dim - 1]
           * det_dev_sign(row + 1, matrix->dim)
           * matrix_int_det(matrix_without_row(&sub_matrix, matrix, row));


  free(sub_matrix.elements);
  return det;
}

IntVector matrix_int_det(IntSquareMatrix *matrix) {
  assert(matrix->dim > 0);
  switch (matrix->dim) {
    case 1:
      return matrix->elements[0][0];

    case 2:
      return matrix->elements[0][0] * matrix->elements[1][1] - matrix->elements[0][1] * matrix->elements[1][0];

    default:
      return det_reduce(matrix);
  }
}

void matrix_reshape(IntVector **bi_dim, IntVector *flat, int width, int height) {
  int row;
  assert(width > 0 && height > 0);

  for (row = 0; row < height; ++row)
    bi_dim[row] = flat + row * width;
}
