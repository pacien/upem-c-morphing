#ifndef UPEM_MORPHING_GEOM
#define UPEM_MORPHING_GEOM

/**
 * File: geom.h
 *
 * Author:
 *   Pacien TRAN-GIRARD
 */

#include <stdbool.h>
#include <inttypes.h>

/**
 * Type: IntVector
 * An abstract 1-D vector.
 */
typedef int64_t IntVector;

/**
 * Type: RealVector
 * An abstract 1-D real vector.
 */
typedef double RealVector;

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
 * Struct: BarycentricVector
 * An abstract barycentric coordinate tuple relative to a triangle.
 * The third barycentric coordinate is deduced from the first two ones.
 *
 * Fields:
 *   a - the first barycentric coordinate
 *   b - the second barycentric coordinate
 */
typedef struct {
  RealVector a, b;
} BarycentricVector;

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
 * Struct: Triangle
 * Represents a simple triangle with three vertices.
 *
 * Fields:
 *   v[] - array of vertices
 */
typedef struct {
  CartesianVector v[3];
} Triangle;

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
 * Function: b
 * Shorthand for a barycentric vector.
 *
 * Parameters:
 *   a - the a-coordinate
 *   b - the b-coordinate
 *
 * Returns:
 *   A barycentric vector
 */
BarycentricVector b(double a, double b);

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
 * Function: barycentric_vector_equals
 * Compares two barycentric vectors.
 *
 * Parameters:
 *   v1 - the first vector
 *   v2 - the second vector
 *
 * Returns:
 *   T(v1 is equal to v2)
 */
bool barycentric_vector_equals(BarycentricVector b1, BarycentricVector b2);

/**
 * Function: square_area
 * Computes the area of a square spawned by three positively oriented vertices.
 *
 * Parameters:
 *   vi - vertices
 *
 * Returns:
 *   The area of the square
 */
IntVector square_area(CartesianVector v1, CartesianVector v2, CartesianVector v3);

/**
 * Function: cartesian_to_barycentric
 * Computes and returns the barycentric coordinates of a given point in the given reference triangle.
 *
 * Parameters:
 *   t - reference triangle
 *   p - the vector to convert
 *
 * Returns:
 *   The barycentric coordinates vector
 */
BarycentricVector cartesian_to_barycentric(Triangle t, CartesianVector p);

/**
 * Function: barycentric_to_cartesian
 * Computes and returns the cartesian coordinates of a given point in the given reference triangle.
 *
 * Parameters:
 *   t - reference triangle
 *   p - the vector to convert
 *
 * Returns:
 *   The cartesian coordinate vector
 */
CartesianVector barycentric_to_cartesian(Triangle t, BarycentricVector p);

#endif
