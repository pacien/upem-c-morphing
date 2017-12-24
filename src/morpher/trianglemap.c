#include "morpher/trianglemap.h"
#include <stdlib.h>
#include <assert.h>
#include "morpher/quadrilateral.h"
#include "common/mem.h"

static void propagate_delaunay(TriangleMap *start, TriangleMap *neighbor) {
  assert(start != NULL && neighbor != NULL);
  if (!quadrilateral_is_delaunay(start, neighbor)) {
    quadrilateral_flip_diagonal(start, neighbor);
    trianglemap_foreach_neighbor(neighbor, propagate_delaunay);
  }
}

TriangleMap *trianglemap_create(CartesianMapping v1, CartesianMapping v2, CartesianMapping v3) {
  TriangleMap *triangle = malloc_or_die(sizeof(TriangleMap));
  triangle->vertices[0] = v1;
  triangle->vertices[1] = v2;
  triangle->vertices[2] = v3;
  return triangle;
}

TriangleMap *trianglemap_destroy(TriangleMap *t) {
  TriangleMap *next = t->next;
  free(t);
  return next;
}

TriangleMap *trianglemap_to(TriangleMap *t, CartesianVector v) {
  int edge;

  for (edge = 0; edge < 3; ++edge)
    if (triangle_area(t->vertices[edge].origin, t->vertices[(edge + 1) % 3].origin, v) >= 0)
      return t->neighbors[edge];

  return t;
}

int trianglemap_find_common_edge(TriangleMap *t, TriangleMap *neighbor) {
  int edge;
  for (edge = 0; t->neighbors[edge] != neighbor && edge < 3; ++edge);
  assert(t->neighbors[edge] == neighbor && neighbor != NULL);
  return edge;
}

void trianglemap_set_neighbors(TriangleMap *t, TriangleMap *n1, TriangleMap *n2, TriangleMap *n3, TriangleMap *next) {
  t->neighbors[0] = n1;
  t->neighbors[1] = n2;
  t->neighbors[2] = n3;
  t->next = next;
}

void trianglemap_replace_neighbor(TriangleMap *t, TriangleMap *old, TriangleMap *new) {
  if (t != NULL) t->neighbors[trianglemap_find_common_edge(t, old)] = new;
}

void trianglemap_foreach_neighbor(TriangleMap *t, void (*f)(TriangleMap *, TriangleMap *)) {
  int cursor;
  assert(t != NULL);
  for (cursor = 0; cursor < 3; ++cursor) if (t->neighbors[cursor] != NULL) f(t, t->neighbors[cursor]);
}

void trianglemap_propagate_delaunay(TriangleMap *t) {
  trianglemap_foreach_neighbor(t, propagate_delaunay);
}

TriangleMap *trianglemap_split(TriangleMap *t, CartesianMapping v) {
  assert(trianglemap_to(t, v.origin) == t);

  TriangleMap *triangle2 = trianglemap_create(t->vertices[1], t->vertices[2], v);
  TriangleMap *triangle3 = trianglemap_create(t->vertices[2], t->vertices[0], v);
  t->vertices[2] = v;

  trianglemap_replace_neighbor(t->neighbors[1], t, triangle2);
  trianglemap_replace_neighbor(t->neighbors[2], t, triangle3);

  trianglemap_set_neighbors(triangle3, t->neighbors[2], t, triangle2, t->next);
  trianglemap_set_neighbors(triangle2, t->neighbors[1], triangle3, t, triangle3);
  trianglemap_set_neighbors(t, t->neighbors[0], triangle2, triangle3, triangle2);

  return t;
}
