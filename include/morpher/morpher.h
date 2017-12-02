#ifndef UPEM_MORPHING_MORPHER
#define UPEM_MORPHING_MORPHER

/**
 * File: morpher.h
 * Coordinate mapping for morphing transforms.
 */

#include "common/geom.h"

/**
 * Type: Morphing
 * Represents an abstract coordinate transform from a source to a destination coordinate matrix,
 * constrained by a given set of points.
 */
typedef void *Morphing;

/**
 * Function: morpher_init
 * Initialises a morphing.
 *
 * Parameters:
 *   *morphing - pointer to the morphing to initialise
 *   width     - coordinate matrix width in pixels
 *   height    - coordinate matrix height in pixels
 */
void morpher_init(Morphing *morphing, IntVector width, IntVector height);

/**
 * Function: morpher_free
 * Frees any resources allocated to a morphing.
 *
 * Parameters:
 *   *morphin* - pointer to the morphing to destroy
 */
void morpher_free(Morphing *morphing);

/**
 * Function: morpher_add_constraint
 * Adds a constraint point to a morphing.
 *
 * Parameters:
 *   *morphing   - pointer to the morphing to alter
 *   origin      - constraint point coordinates on the origin matrix
 *   destination - constraint point coordinates on the target matrix
 */
void morpher_add_constraint(Morphing *morphing, CartesianVector origin, CartesianVector destination);

/**
 * Function: morpher_get_point_mapping
 * Computes and returns the coordinates of a given point at the given transform step
 * in the origin and destination matrices.
 *
 * Parameters:
 *   *morphing - the base morphing
 *   point     - point to map in cartesian coordinates
 *   frame     - time coefficient corresponding to the transform state, [0;1]
 *
 * Returns:
 *   A cartesian coordinate mapping from the origin to the target matrix of the given point
 */
CartesianMapping morpher_get_point_mapping(Morphing *morphing, CartesianVector point, TimeVector frame);

#endif
