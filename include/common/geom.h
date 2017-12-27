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
 * Function: m
 * Shorthand for an identity mapping.
 *
 * Parameters:
 *   x - the x-coordinate
 *   y - the y-coordinate
 *
 * Returns:
 *   A cartesian identity mapping
 */
CartesianMapping m(int x, int y);

/**
 * Function: v
 * Shorthand for a vector.
 *
 * Parameters:
 *   x - the x-coordinate
 *   y - the y-coordinate
 *
 * Returns:
 *   An integer vector
 */
CartesianVector v(int x, int y);

/**
 * Function: mappings_equals
 * Compares two cartesian mappings.
 *
 * Parameters:
 *   m1 - the first mapping
 *   m2 - the second mapping
 *
 * Returns:
 *   T(m1 is equal to m2)
 */
bool mappings_equals(CartesianMapping m1, CartesianMapping m2);

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

/**
 * Function: triangle_area
 * Computes the area of a triangle.
 *
 * Parameters:
 *   v1 - first vertex
 *   v2 - second vertex
 *   v3 - third vertex
 *
 * Returns:
 *   The area of the triangle spawned by the three supplied vertices
 */
IntVector triangle_area(CartesianVector v1, CartesianVector v2, CartesianVector v3);

#endif
