#include "morpher/trianglemap.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "common/geom.h"

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
 *  l |\| r
 *    ---
 */
static inline TriangleMap *create_test_map() {
  TriangleMap *t = trianglemap_create(m(50, 0), m(0, 100), m(100, 100));
  TriangleMap *r = trianglemap_create(m(100, 100), m(0, 100), m(100, 200));
  TriangleMap *l = trianglemap_create(m(0, 100), m(0, 200), m(100, 200));
  trianglemap_set_neighbors(t, NULL, r, NULL, r);
  trianglemap_set_neighbors(r, t, l, NULL, l);
  trianglemap_set_neighbors(l, NULL, NULL, r, NULL);
  return t;
}

static inline void free_map(TriangleMap *t) {
  while (t != NULL) t = trianglemap_destroy(t);
}

static void test_triangle_to() {
  TriangleMap *t = create_test_map();

  assert(trianglemap_to(t, v(80, 80)) == t);
  assert(trianglemap_to(t, v(0, 0)) == t->neighbors[0]);
  assert(trianglemap_to(t, v(55, 170)) == t->neighbors[1]);

  free_map(t);
}

static void test_triangle_split() {
  TriangleMap *t = create_test_map();
  TriangleMap *r = t->next;
  TriangleMap *l = r->next;
  TriangleMap *r1 = trianglemap_split(r, m(90, 110));
  TriangleMap *r2 = r1->next;
  TriangleMap *r3 = r2->next;

  assert(vertices_equals(r1->vertices, m(100, 100), m(0, 100), m(90, 110)));
  assert(vertices_equals(r2->vertices, m(0, 100), m(100, 200), m(90, 110)));
  assert(vertices_equals(r3->vertices, m(100, 200), m(100, 100), m(90, 110)));
  assert(neighbors_equals(r1->neighbors, t, r2, r3));
  assert(neighbors_equals(r2->neighbors, l, r3, r1));
  assert(neighbors_equals(r3->neighbors, NULL, r1, r2));
  assert(t->neighbors[1] == r1 && l->neighbors[2] == r2);

  free_map(t);
}

int main(int argc, char **argv) {
  test_triangle_to();
  test_triangle_split();
  return 0;
}
