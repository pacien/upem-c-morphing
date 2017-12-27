#ifndef UPEM_MORPHING_MORPHING
#define UPEM_MORPHING_MORPHING

/**
 * File: morphing.h
 * Coordinate mapping for morphing transforms.
 */

#include "common/geom.h"
#include "common/time.h"
#include "morpher/trianglemap.h"

/**
 * Struct: Morphing
 * Represents an abstract coordinate transform from a source to a destination coordinate matrix,
 * constrained by a given set of points.
 *
 * Fields:
 *   dim     - dimension in pixels
 *   *first  - the first triangle in the linked list
 *   *center - the center triangle
 */
typedef struct {
  CartesianVector dim;
  TriangleMap *first, *center;
} Morphing;

/**
 * Function: morphing_init
 * Initialises a morphing.
 *
 * Parameters:
 *   width  - coordinate matrix width in pixels
 *   height - coordinate matrix height in pixels
 */
Morphing *morphing_create(IntVector width, IntVector height);

/**
 * Function: morphing_free
 * Frees any resources allocated to a morphing.
 *
 * Parameters:
 *   *m - pointer to the morphing to destroy
 */
void morphing_destroy(Morphing *m);

/**
 * Function: morphing_add_constraint
 * Adds a constraint point to a morphing.
 *
 * Parameters:
 *   *m          - pointer to the morphing to alter
 *   origin      - constraint point coordinates on the origin matrix
 *   destination - constraint point coordinates on the target matrix
 */
void morphing_add_constraint(Morphing *m, CartesianVector origin, CartesianVector destination);

#endif
