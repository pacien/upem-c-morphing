#include "morpher/quadrilateral.h"
#include <stdlib.h>
#include <assert.h>
#include "morpher/matrix.h"

static inline IntVector p2(IntVector n) {
  return n * n;
}

static inline bool in_circumcircle(TriangleMap *t, CartesianVector v) {
  CartesianVector a = t->vertices[0].origin, b = t->vertices[1].origin, c = t->vertices[2].origin;
  IntVector v2 = p2(v.x) + p2(v.y);
  return matrix_int_det3(a.x - v.x, a.y - v.y, p2(a.x) + p2(a.y) - v2,
                         b.x - v.x, b.y - v.y, p2(b.x) + p2(b.y) - v2,
                         c.x - v.x, c.y - v.y, p2(c.x) + p2(c.y) - v2) < 0;
}

static inline void rotate_vertices(TriangleMap *t1, TriangleMap *t2, int e1, int e2) {
  CartesianMapping quad[] = {
   t1->vertices[(e1 + 1) % 3],
   t1->vertices[(e1 + 2) % 3],
   t2->vertices[(e2 + 1) % 3],
   t2->vertices[(e2 + 2) % 3]
  };

  t1->vertices[(e1 + 1) % 3] = quad[1];
  t1->vertices[(e1 + 2) % 3] = quad[2];
  t1->vertices[(e1 + 3) % 3] = quad[3];
  t2->vertices[(e2 + 1) % 3] = quad[3];
  t2->vertices[(e2 + 2) % 3] = quad[0];
  t2->vertices[(e2 + 3) % 3] = quad[1];
}

static inline void rotate_neighbors(TriangleMap *t1, TriangleMap *t2, int e1, int e2) {
  TriangleMap *neighbors[] = {
   t1->neighbors[(e1 + 1) % 3],
   t1->neighbors[(e1 + 2) % 3],
   t2->neighbors[(e2 + 1) % 3],
   t2->neighbors[(e2 + 2) % 3]
  };

  t1->neighbors[(e1 + 1) % 3] = neighbors[1];
  t1->neighbors[(e1 + 2) % 3] = neighbors[2];
  t2->neighbors[(e2 + 1) % 3] = neighbors[3];
  t2->neighbors[(e2 + 2) % 3] = neighbors[0];
  trianglemap_replace_neighbor(t1->neighbors[(e1 + 2) % 3], t2, t1);
  trianglemap_replace_neighbor(t2->neighbors[(e2 + 2) % 3], t1, t2);
}

void quadrilateral_flip_diagonal(TriangleMap *t1, TriangleMap *t2) {
  int e1, e2;
  assert(t1 != NULL && t2 != NULL);
  e1 = trianglemap_find_common_edge(t1, t2);
  e2 = trianglemap_find_common_edge(t2, t1);
  rotate_vertices(t1, t2, e1, e2);
  rotate_neighbors(t1, t2, e1, e2);
}

bool quadrilateral_is_delaunay(TriangleMap *t1, TriangleMap *t2) {
  assert(t1 != NULL && t2 != NULL);
  return !in_circumcircle(t1, t2->vertices[(trianglemap_find_common_edge(t2, t1) + 2) % 3].origin) &&
         !in_circumcircle(t2, t1->vertices[(trianglemap_find_common_edge(t1, t2) + 2) % 3].origin);
}
