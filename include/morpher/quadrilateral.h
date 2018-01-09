#ifndef UPEM_MORPHING_QUADRILATERAL
#define UPEM_MORPHING_QUADRILATERAL

/**
 * File: quadrilateral.h
 * Operations on quadrilaterals formed by adjacent triangles pairs.
 *
 * Author:
 *   Pacien TRAN-GIRARD
 */

#include <stdbool.h>
#include "common/geom.h"
#include "morpher/trianglemap.h"

/**
 * Function: quadrilateral_flip_diagonal
 * Flips the diagonal of a quadrilateral formed by two triangles sharing a common edge,
 * using a positive rotation-like transform inverting both references.
 * This transforms keeps the positive orientation of the vertices.
 * Pointers to surrounding triangles are updated accordingly.
 *
 * Parameters:
 *   *t1 - the first triangle
 *   *t2 - the second triangle
 */
void quadrilateral_flip_diagonal(TriangleMap *t1, TriangleMap *t2);

/**
 * Function: quadrilateral_is_delaunay
 * Tells whether the quadrilateral formed by the two supplied adjacent triangle forms a Delaunay triangulation.
 *
 * Parameters:
 *   *t1 - first triangle
 *   *t2 - second triangle adjacent to the first one
 *
 * Returns:
 *   T(t1 and t2 are a Delaunay triangulation in the quadrilateral formed by the twos)
 */
bool quadrilateral_is_delaunay(TriangleMap *t1, TriangleMap *t2);

#endif
