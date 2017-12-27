#include "morpher/trianglemap.h"
#include <stdlib.h>
#include <assert.h>
#include "morpher/quadrilateral.h"

static inline bool neighbors_equals(TriangleMap *neighbors[],
                                    TriangleMap *n1, TriangleMap *n2, TriangleMap *n3) {
  return neighbors[0] == n1 && neighbors[1] == n2 && neighbors[2] == n3;
}

static inline bool vertices_equals(CartesianMapping maps[],
                                   CartesianMapping m1, CartesianMapping m2, CartesianMapping m3) {
  return mappings_equals(maps[0], m1) && mappings_equals(maps[1], m2) && mappings_equals(maps[2], m3);
}

static void test_trianglemap_to() {
  CartesianMapping A = m(50, 0), B = m(0, 100), C = m(100, 100), D = m(0, 200), E = m(100, 200);
  TriangleMap *t = trianglemap_create(A, B, C);
  TriangleMap *r = trianglemap_create(C, B, E);
  TriangleMap *l = trianglemap_create(B, D, E);
  trianglemap_set_neighbors(t, NULL, r, NULL, r);
  trianglemap_set_neighbors(r, t, l, NULL, l);
  trianglemap_set_neighbors(l, NULL, NULL, r, NULL);

  assert(trianglemap_to(t, v(80, 80)) == t);
  assert(trianglemap_to(t, v(0, 0)) == t->neighbors[0]);
  assert(trianglemap_to(t, v(55, 170)) == t->neighbors[1]);

  while (t != NULL) t = trianglemap_destroy(t);
}

static void test_trianglemap_split() {
  CartesianMapping A = m(50, 0), B = m(0, 100), C = m(100, 100), D = m(0, 200), E = m(100, 200), F = m(90, 110);
  TriangleMap *t = trianglemap_create(A, B, C);
  TriangleMap *r = trianglemap_create(C, B, E);
  TriangleMap *l = trianglemap_create(B, D, E);
  trianglemap_set_neighbors(t, NULL, r, NULL, r);
  trianglemap_set_neighbors(r, t, l, NULL, l);
  trianglemap_set_neighbors(l, NULL, NULL, r, NULL);

  TriangleMap *r1 = trianglemap_split(r, F);
  TriangleMap *r2 = r1->next;
  TriangleMap *r3 = r2->next;

  assert(vertices_equals(r1->vertices, C, B, F));
  assert(vertices_equals(r2->vertices, B, E, F));
  assert(vertices_equals(r3->vertices, E, C, F));
  assert(neighbors_equals(r1->neighbors, t, r2, r3));
  assert(neighbors_equals(r2->neighbors, l, r3, r1));
  assert(neighbors_equals(r3->neighbors, NULL, r1, r2));
  assert(t->neighbors[1] == r1 && l->neighbors[2] == r2);

  while (t != NULL) t = trianglemap_destroy(t);
}

static void test_trianglemap_propagate_delaunay() {
  CartesianMapping A = m(0, 0), B = m(0, 10), C = m(10, 10), D = m(10, 0), E = m(4, 6), F = m(8, 7);
  TriangleMap *l = trianglemap_create(A, B, C);
  TriangleMap *r = trianglemap_create(A, C, D);
  trianglemap_set_neighbors(l, NULL, NULL, r, r);
  trianglemap_set_neighbors(r, l, NULL, NULL, NULL);
  trianglemap_split(l, E);
  trianglemap_split(r, F);

  trianglemap_propagate_delaunay(r);

  {
    TriangleMap *triangle;
    int neighbor_index;
    for (triangle = l; triangle != NULL; triangle = triangle->next)
      for (neighbor_index = 0; neighbor_index < 3; ++neighbor_index)
        if (triangle->neighbors[neighbor_index] != NULL)
          assert(quadrilateral_is_delaunay(triangle, triangle->neighbors[neighbor_index]));
  }

  while (l != NULL) l = trianglemap_destroy(l);
}

int main(int argc, char **argv) {
  test_trianglemap_to();
  test_trianglemap_split();
  test_trianglemap_propagate_delaunay();
  return 0;
}
