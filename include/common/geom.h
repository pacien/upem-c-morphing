#ifndef UPEM_MORPHING_GEOM
#define UPEM_MORPHING_GEOM

/**
 * File: geom.h
 */

#include <stdbool.h>
#include <inttypes.h>

/**
 * Type: IntVector
 * An abstract 1-D vector.
 */
typedef int32_t IntVector;

/**
 * Struct: CartesianVector
 * An abstract 2-D vector in cartesian coordinates.
 *
 * Fields:
 *   x - the horizontal component
 *   y - the vertical component
 */
typedef struct {
  IntVector x, y;
} CartesianVector;

/**
 * Struct: CartesianMapping
 * A tuple of cartesian vectors representing a mapping.
 *
 * Fields:
 *   origin - preimage vector
 *   target - image vector
 */
typedef struct {
  CartesianVector origin, target;
} CartesianMapping;

/**
 * Function: vector_equals
 * Compares two cartesian vectors.
 *
 * Parameters:
 *   v1 - the first vector
 *   v2 - the second vector
 *
 * Returns:
 *   T(v1 is equal to v2)
 */
bool vector_equals(CartesianVector v1, CartesianVector v2);

#endif
