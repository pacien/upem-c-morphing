#ifndef UPEM_MORPHING_MATRIX
#define UPEM_MORPHING_MATRIX

/**
 * File: matrix.h
 *
 * See also:
 *   The film
 */

#include "geom.h"

/**
 * Type: IntSquareMatrix
 * Represents a square integer matrix.
 */
typedef struct {
  IntVector *elements;
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

#endif
