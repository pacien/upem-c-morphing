#ifndef UPEM_MORPHING_GEOM
#define UPEM_MORPHING_GEOM

/**
 * File: geom.h
 */

#include <inttypes.h>

/**
 * Type: IntVector
 * An abstract 1-D vector.
 */
typedef int32_t IntVector;

/**
 * Type: CartesianVector
 * An abstract 2-D vector in cartesian coordinates.
 */
typedef struct {
  IntVector x, y;
} CartesianVector;

/**
 * Type: CartesianMapping
 * A tuple of cartesian vectors representing a mapping.
 */
typedef struct {
  CartesianVector origin, target;
} CartesianMapping;

#endif
