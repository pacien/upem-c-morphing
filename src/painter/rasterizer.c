#include "painter/rasterizer.h"
#include <math.h>
#include <assert.h>

/**
 * File: rasterizer.c
 *
 * Author:
 *   Pacien TRAN-GIRARD
 */

static inline IntVector i(double (*f)(double, double), RealVector a, RealVector b) {
  return (IntVector) floor(f(a, b));
}

static inline CartesianVector vertex_at_frame(CartesianMapping m, TimeVector t) {
  return (CartesianVector) {(IntVector) round((TIME_UNIT - t) * m.origin.x + t * m.target.x),
                            (IntVector) round((TIME_UNIT - t) * m.origin.y + t * m.target.y)};
}

static inline RealVector slope(CartesianVector a, CartesianVector b) {
  return (((RealVector) b.x) - ((RealVector) a.x)) / (((RealVector) b.y) - ((RealVector) a.y));
}

static inline int positive_y_vertex_comparator(const void *l, const void *r) {
  return ((CartesianVector *) l)->y - ((CartesianVector *) r)->y;
}

static inline Color color_at(Canvas *c, Triangle ref, BarycentricVector b) {
  CartesianVector v = barycentric_to_cartesian(ref, b);
  return canvas_get_pixel(c, v);
}

static inline TriangleContext build_triangle_context(Triangle current, TriangleMap *map) {
  TriangleContext c;
  int cursor;

  for (cursor = 0; cursor < 3; ++cursor) {
    c.current.v[cursor] = current.v[cursor];
    c.source.v[cursor] = map->vertices[cursor].origin;
    c.target.v[cursor] = map->vertices[cursor].target;
  }

  return c;
}

static inline void draw_pixel(CartesianVector pos, TriangleContext *tctx, RasterizationContext *rctx) {
  BarycentricVector b = cartesian_to_barycentric(tctx->current, pos);
  Color c = color_blend(color_at(rctx->source, tctx->source, b), color_at(rctx->target, tctx->target, b), rctx->frame);
  canvas_set_pixel(rctx->result, pos, c);
}

static inline void draw_flat_triangle(IntVector top, IntVector bottom,
                                      RealVector dx1, RealVector dx2, RealVector *x1, RealVector *x2,
                                      TriangleContext *tctx, RasterizationContext *rctx) {

  IntVector y, l, r;
  for (y = top; y <= bottom; ++y, *x1 += dx1, *x2 += dx2)
    for (l = i(fmin, *x1, *x2), r = i(fmax, *x1, *x2); l <= r; ++l)
      draw_pixel(v(l, y), tctx, rctx);
}

static inline void draw_triangle(TriangleMap *t, RasterizationContext *rctx) {
  Triangle triangle = {{vertex_at_frame(t->vertices[0], rctx->frame),
                        vertex_at_frame(t->vertices[1], rctx->frame),
                        vertex_at_frame(t->vertices[2], rctx->frame)}};

  TriangleContext tctx = build_triangle_context(triangle, t);
  CartesianVector *v = triangle.v;
  qsort(v, 3, sizeof(CartesianVector), positive_y_vertex_comparator);

  {
    RealVector dx1 = slope(v[0], v[1]), dx2 = slope(v[0], v[2]), dx3 = slope(v[1], v[2]);
    RealVector x1 = v[0].x, x2 = v[0].x, x3 = v[1].x;

    draw_flat_triangle(v[0].y, v[1].y - 1, dx1, dx2, &x1, &x2, &tctx, rctx);
    draw_flat_triangle(v[1].y, v[2].y, dx2, dx3, &x2, &x3, &tctx, rctx);
  }
}

Canvas *rasterize(Canvas *source, Canvas *target, Morphing *m, TimeVector frame) {
  RasterizationContext rctx;
  TriangleMap *t;

  assert(source != NULL && target != NULL && m != NULL);
  assert(vector_equals(canvas_get_dim(source), m->dim) && vector_equals(canvas_get_dim(target), m->dim));
  assert(frame >= TIME_ORIGIN && frame <= TIME_UNIT);

  rctx = (RasterizationContext) {canvas_create(m->dim.x, m->dim.y), source, target, frame};
  for (t = m->first; t != NULL; t = t->next) draw_triangle(t, &rctx);

  return rctx.result;
}
