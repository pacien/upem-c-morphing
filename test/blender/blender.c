#include "blender/blender.h"
#include <assert.h>

static void test_color_blending() {
  Color a = {{0xFF, 0xED, 0x00, 0x00}};
  Color b = {{0x00, 0x47, 0xAB, 0x00}};
  Color result = blender_blend_colors(a, b, 0.125);

  assert(color_equals(result, (Color) {{0xEE, 0xDF, 0x3C, 0x00}}));
}

int main(int argc, char **argv) {
  test_color_blending();
  return 0;
}
