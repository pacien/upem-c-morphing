#include "morpher/quadrilateral.h"
#include <assert.h>
#include <stdlib.h>

static inline bool neighbors_equals(TriangleMap *neighbors[],
                                    TriangleMap *n1, TriangleMap *n2, TriangleMap *n3) {
  return neighbors[0] == n1 && neighbors[1] == n2 && neighbors[2] == n3;
}

static inline bool vertices_equals(CartesianMapping maps[],
                                   CartesianMapping m1, CartesianMapping m2, CartesianMapping m3) {
  return mappings_equals(maps[0], m1) && mappings_equals(maps[1], m2) && mappings_equals(maps[2], m3);
}

/*
 *     -
 *    / \ t
 *    ---
 *  r |/| l
 *    ---
 */
static void test_quadrilateral_flip_diagonal() {
  TriangleMap *t = trianglemap_create(m(50, 0), m(0, 100), m(100, 100));
  TriangleMap *r = trianglemap_create(m(100, 100), m(0, 100), m(100, 200));
  TriangleMap *l = trianglemap_create(m(0, 100), m(0, 200), m(100, 200));
  trianglemap_set_neighbors(t, NULL, r, NULL, r);
  trianglemap_set_neighbors(r, t, l, NULL, l);
  trianglemap_set_neighbors(l, NULL, NULL, r, NULL);
  quadrilateral_flip_diagonal(r, l);

  assert(vertices_equals(t->vertices, m(50, 0), m(0, 100), m(100, 100)));
  assert(vertices_equals(r->vertices, m(0, 100), m(0, 200), m(100, 100)));
  assert(vertices_equals(l->vertices, m(0, 200), m(100, 200), m(100, 100)));
  assert(neighbors_equals(t->neighbors, NULL, r, NULL));
  assert(neighbors_equals(r->neighbors, NULL, l, t));
  assert(neighbors_equals(l->neighbors, NULL, NULL, r));

  while (t != NULL) t = trianglemap_destroy(t);
}

static void test_quadrilateral_is_delaunay() {
  {
    TriangleMap *l = trianglemap_create(m(0, 0), m(0, 3), m(3, 3));
    TriangleMap *r = trianglemap_create(m(0, 0), m(3, 3), m(2, 1));
    trianglemap_set_neighbors(l, NULL, NULL, r, r);
    trianglemap_set_neighbors(r, l, NULL, NULL, NULL);

    assert(!quadrilateral_is_delaunay(l, r));

    trianglemap_destroy(l);
    trianglemap_destroy(r);
  }

  {
    TriangleMap *l = trianglemap_create(m(0, 0), m(0, 3), m(3, 3));
    TriangleMap *r = trianglemap_create(m(0, 0), m(3, 3), m(4, -1));
    trianglemap_set_neighbors(l, NULL, NULL, r, r);
    trianglemap_set_neighbors(r, l, NULL, NULL, NULL);

    assert(quadrilateral_is_delaunay(l, r));

    trianglemap_destroy(l);
    trianglemap_destroy(r);
  }
}

int main(int argc, char **argv) {
  test_quadrilateral_flip_diagonal();
  test_quadrilateral_is_delaunay();
  return 0;
}
