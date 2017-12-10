#ifndef UPEM_MORPHING_MATRIX
#define UPEM_MORPHING_MATRIX

/**
 * File: matrix.h
 * Matrices representation and useful operations.
 *
 * See also:
 *   The film
 */

#include "geom.h"

/**
 * Struct: IntSquareMatrix
 * Represents a square integer matrix.
 *
 * Fields:
 *   **elements - NULL-terminated array of element pointers
 *   dim        - dimension
 */
typedef struct {
  IntVector **elements;
  IntVector dim;
} IntSquareMatrix;

/**
 * Function: matrix_int_det
 * Computes and returns the determinant of a square integer matrix.
 *
 * Parameters:
 *   *matrix - pointer to input matrix
 *
 * Returns:
 *   The integer determinant
 */
IntVector matrix_int_det(IntSquareMatrix *matrix);

/**
 * Function: matrix_reshape
 * Reshapes a flat vector into a bi-dimensional row pointer array.
 *
 * Parameters:
 *   **bi_dim - pointer to the result row array
 *   *flat    - flat vector
 *   width    - number of elements per row
 *   height   - number of rows
 */
void matrix_reshape(IntVector **bi_dim, IntVector *flat, int width, int height);

#endif
