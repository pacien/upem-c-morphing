#include "blender/color.h"

bool color_equals(Color c1, Color c2) {
  return c1.rgba.r == c2.rgba.r &&
         c1.rgba.g == c2.rgba.g &&
         c1.rgba.b == c2.rgba.b &&
         c1.rgba.a == c2.rgba.a;
}
