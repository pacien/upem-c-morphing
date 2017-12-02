#include "blender/blender.h"
#include <assert.h>

static void test_color_blending() {
  Color origin = {{0xFF, 0xED, 0x00, 0x00}};
  Color target = {{0x00, 0x47, 0xAB, 0x00}};
  Color result = blender_blend_colors(origin, target, 0.125);

  assert(color_equals(result, (Color) {{0xEE, 0xDF, 0x3C, 0x00}}));
}

static void test_canvas_blending() {
  Morphing morphing;
  Canvas origin, target, result;
  CartesianVector sample_point = {13, 17};

  morpher_init(&morphing, 64, 64);
  canvas_init(&origin, 64, 64);
  canvas_init(&target, 64, 64);
  canvas_init(&result, 64, 64);

  canvas_set_pixel(&origin, sample_point, (Color) {{0xFF, 0xED, 0x00, 0x00}});
  canvas_set_pixel(&target, sample_point, (Color) {{0x00, 0x47, 0xAB, 0x00}});

  blender_blend_canvas(&result, &origin, &target, &morphing, 0.125);
  assert(color_equals(canvas_get_pixel(&result, sample_point), (Color) {{0xEE, 0xDF, 0x3C, 0x00}}));

  canvas_free(&result);
  canvas_free(&target);
  canvas_free(&origin);
  morpher_free(&morphing);
}

int main(int argc, char **argv) {
  test_color_blending();
  test_canvas_blending();
  return 0;
}
