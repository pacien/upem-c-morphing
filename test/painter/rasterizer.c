#include "painter/rasterizer.h"
#include <assert.h>

/**
 * File: rasterizer.c
 *
 * Author:
 *   Pacien TRAN-GIRARD
 */

static void test_rasterize() {
  Morphing *morphing;
  Canvas *origin, *target, *result;
  CartesianVector sample_point = {13, 17};

  morphing = morphing_create(100, 100);
  origin = canvas_create(100, 100);
  target = canvas_create(100, 100);
  canvas_set_pixel(origin, sample_point, (Color) {{0xFF, 0x00, 0xED, 0xFF}});
  canvas_set_pixel(target, sample_point, (Color) {{0xFF, 0xAB, 0x47, 0x00}});

  result = rasterize(origin, target, morphing, 0.125);
  assert(color_equals(canvas_get_pixel(result, sample_point), (Color) {{0xFF, 0x3C, 0xDF, 0xEF}}));

  canvas_destroy(result);
  canvas_destroy(target);
  canvas_destroy(origin);
  morphing_destroy(morphing);
}

int main(int argc, char **argv) {
  test_rasterize();
  return 0;
}
