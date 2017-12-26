#include "morpher/morphing.h"
#include "common/mem.h"

static inline TriangleMap *init_trianglemap(IntVector width, IntVector height) {
  TriangleMap *bottom_left = trianglemap_create(m(0, 0), m(0, height), m(width, height));
  TriangleMap *top_right = trianglemap_create(m(0, 0), m(width, height), m(width, 0));
  trianglemap_set_neighbors(bottom_left, NULL, NULL, top_right, top_right);
  trianglemap_set_neighbors(top_right, bottom_left, NULL, NULL, NULL);
  return bottom_left;
}

static inline TriangleMap *find_triangle(TriangleMap *start, CartesianVector target) {
  TriangleMap *t = trianglemap_to(start, target);
  return t == start ? t : find_triangle(t, target);
}

static inline void update_center(Morphing *m) {
  m->center = find_triangle(m->center, v(m->dim.x / 2, m->dim.y / 2));
}

static inline void ensure_delaunay_neighborhood(TriangleMap *t) {
  trianglemap_propagate_delaunay(t);
  trianglemap_propagate_delaunay(t->next);
  trianglemap_propagate_delaunay(t->next->next);
}

Morphing *morphing_create(IntVector width, IntVector height) {
  Morphing *m = malloc_or_die(sizeof(Morphing));
  m->dim = (CartesianVector) {width, height};
  m->first = init_trianglemap(width, height);
  m->center = m->first;
  return m;
}

void morphing_destroy(Morphing *m) {
  while (m->first != NULL) m->first = trianglemap_destroy(m->first);
}

void morphing_add_constraint(Morphing *m, CartesianVector origin, CartesianVector destination) {
  TriangleMap *target = find_triangle(m->center, origin);
  TriangleMap *split = trianglemap_split(target, (CartesianMapping) {origin, destination});
  ensure_delaunay_neighborhood(split);
  update_center(m);
}
