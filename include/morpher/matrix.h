#ifndef UPEM_MORPHING_MATRIX
#define UPEM_MORPHING_MATRIX

/**
 * File: matrix.h
 * Determinant operations.
 *
 * See also:
 *   The film
 */

#include "common/geom.h"

/**
 * Function: matrix_int_det2
 * Computes and returns the determinant of a square integer matrix of size 2.
 *
 * Parameters:
 *   uij - element at the i-th row and j-th column, counting from 1
 *
 * Returns:
 *   The integer determinant
 */
IntVector matrix_int_det2(IntVector u11, IntVector u12,
                          IntVector u21, IntVector u22);

/**
 * Function: matrix_int_det3
 * Computes and returns the determinant of a square integer matrix of size 3.
 *
 * Parameters:
 *   uij - element at the i-th row and j-th column, counting from 1
 *
 * Returns:
 *   The integer determinant
 */
IntVector matrix_int_det3(IntVector u11, IntVector u12, IntVector u13,
                          IntVector u21, IntVector u22, IntVector u23,
                          IntVector u31, IntVector u32, IntVector u33);

#endif
