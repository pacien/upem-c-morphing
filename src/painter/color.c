#include "painter/color.h"
#include <math.h>

/**
 * File: color.c
 *
 * Author:
 *   Pacien TRAN-GIRARD
 */

static inline ColorComponent blend_component(ColorComponent origin, ColorComponent target, TimeVector frame) {
  return (ColorComponent) round(sqrt((TIME_UNIT - frame) * pow(origin, 2) + frame * pow(target, 2)));
}

bool color_equals(Color c1, Color c2) {
  return c1.rgba.r == c2.rgba.r &&
         c1.rgba.g == c2.rgba.g &&
         c1.rgba.b == c2.rgba.b &&
         c1.rgba.a == c2.rgba.a;
}

Color color_blend(Color origin, Color target, TimeVector distance) {
  return (Color) {{blend_component(origin.rgba.a, target.rgba.a, distance),
                   blend_component(origin.rgba.b, target.rgba.b, distance),
                   blend_component(origin.rgba.g, target.rgba.g, distance),
                   blend_component(origin.rgba.r, target.rgba.r, distance)}};
}
