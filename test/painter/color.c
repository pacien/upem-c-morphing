#include "painter/color.h"
#include <assert.h>

static void test_color_blend() {
  Color a = {{1, 10, 100, 200}}, b = {{100, 1, 200, 10}};
  assert(color_equals(color_blend(a, b, TIME_ORIGIN), a));
  assert(color_equals(color_blend(a, b, TIME_UNIT), b));
  assert(color_equals(color_blend(a, b, 0.25), (Color) {{50, 9, 132, 173}}));
}

int main(int argc, char **argv) {
  test_color_blend();
  return 0;
}
