#include "blender/blender.h"
#include <assert.h>

static void test_color_blending() {
  Color a = {{0xFF, 0xED, 0x00, 0x00}};
  Color b = {{0x00, 0x47, 0xAB, 0x00}};
  Color result = blender_blend_colors(a, b, 0.125);

  assert(result.rgba.r == 0xEE &&
         result.rgba.g == 0xDF &&
         result.rgba.b == 0x3C &&
         result.rgba.a == 0x00);
}

int main(int argc, char **argv) {
  test_color_blending();
  return 0;
}
