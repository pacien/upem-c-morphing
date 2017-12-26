#include "blender/blender.h"
#include <assert.h>

static void test_canvas_blending() {
  Morphing *morphing;
  Canvas origin, target, result;
  CartesianVector sample_point = {13, 17};

  morphing = morphing_create(64, 64);
  canvas_init(&origin, 64, 64);
  canvas_init(&target, 64, 64);
  canvas_init(&result, 64, 64);

  canvas_set_pixel(&origin, sample_point, (Color) {{0xFF, 0xED, 0x00, 0x00}});
  canvas_set_pixel(&target, sample_point, (Color) {{0x00, 0x47, 0xAB, 0x00}});

  blender_blend_canvas(&result, &origin, &target, morphing, 0.125);
  assert(color_equals(canvas_get_pixel(&result, sample_point), (Color) {{0xEE, 0xDF, 0x3C, 0x00}}));

  canvas_free(&result);
  canvas_free(&target);
  canvas_free(&origin);
  morphing_destroy(morphing);
}

int main(int argc, char **argv) {
  test_canvas_blending();
  return 0;
}
