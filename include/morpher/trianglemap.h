#ifndef UPEM_MORPHING_TRIANGLEMAP
#define UPEM_MORPHING_TRIANGLEMAP

/**
 * File: trianglemap.h
 * Represents a triangle map in a triangulation, in a plane oriented left to right and top to bottom.
 */

#include <stdbool.h>
#include "common/geom.h"

/**
 * Struct: TriangleMap
 * Represents a triangle mapping.
 *
 * Fields:
 *   vertices[]   - array of vertices
 *   *neighbors[] - array of neighboring triangles ordered by the edges spawned by the vertices
 *   *next        - pointer to another triangle for linear browsing, or NULL
 */
typedef struct _TriangleMap {
  CartesianMapping vertices[3];
  struct _TriangleMap *neighbors[3];
  struct _TriangleMap *next;
} TriangleMap;

/**
 * Function: trianglemap_create
 * Creates a TriangleMap, instantiating it on the heap.
 *
 * Parameters:
 *   vertex1 - first vertex
 *   vertex2 - second vertex
 *   vertex3 - third vertex
 *
 * Returns:
 *   A pointer to the newly created triangle
 */
TriangleMap *trianglemap_create(CartesianMapping v1, CartesianMapping v2, CartesianMapping v3);

/**
 * Function: trianglemap_destroy
 * Destroys a triangle, freeing its dynamically allocated resources.
 * Also returns the next triangle for convenience.
 * Does not update surrounding triangles.
 *
 * Parameters:
 *   *t - pointer to the triangle to destroy
 *
 * Returns:
 *   A pointer to the next linear triangle
 */
TriangleMap *trianglemap_destroy(TriangleMap *t);

/**
 * Function: trianglemap_to
 * Returns a pointer to the current or the closest adjacent neighbour TriangleMap
 * minimizing the distance to the targeted position.
 *
 * Parameters:
 *   *t - the origin triangle
 *   v  - the target position vector
 *
 * Returns:
 *   A pointer to the current or an immediate neighbour TriangleMap
 */
TriangleMap *trianglemap_to(TriangleMap *t, CartesianVector v);

/**
 * Function: trianglemap_find_common_edge
 * Finds the index of the commonly shared edge in the neighbourhood of t.
 *
 * Parameters:
 *   *t        - the base triangle
 *   *neighbor - the neighbour to search for
 *
 * Returns:
 *   The index of the common neighbour in the listing of t.
 */
int trianglemap_find_common_edge(TriangleMap *t, TriangleMap *neighbor);

/**
 * Function: trianglemap_set_neighbors
 * Updates a triangle neighbors.
 * Vertices must be given in a positively oriented (trigonometric) order.
 * Neighbours must be given in the same order as the vertices.
 *
 * Parameters:
 *   *t    - the triangle to modify
 *   *n1   - first neighbour
 *   *n2   - second neighbour
 *   *n3   - third neighbour
 *   *next - linear neighbour
 */
void trianglemap_set_neighbors(TriangleMap *t, TriangleMap *n1, TriangleMap *n2, TriangleMap *n3, TriangleMap *next);

/**
 * Function: triangle_replace_neighbor
 * Substitutes a given neighbour in a neighbourhood.
 *
 * Parameters:
 *   *t   - the base triangle
 *   *old - the neighbour to replace
 *   *new - the new neighbour
 */
void trianglemap_replace_neighbor(TriangleMap *t, TriangleMap *old, TriangleMap *new);

/**
 * Function: trianglemap_split
 * Splits a triangle into three sub-triangles at the supplied center vertex, updating the surrounding triangles.
 * The first triangle resulting from the split is returned, with the two others chained as linear neighbours.
 * Those generated triangles each have one of the original surrounding neighbour as first element in their listings.
 *
 * Parameters:
 *   *t - the triangle to split
 *   v  - the new vertex to add
 *
 * Returns:
 *   The first generated TriangleMap
 */
TriangleMap *trianglemap_split(TriangleMap *t, CartesianMapping v);

#endif
