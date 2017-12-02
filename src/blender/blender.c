#include "blender/blender.h"
#include <assert.h>
#include <math.h>

static ColorComponent blend_components(ColorComponent origin, ColorComponent target, TimeVector frame) {
  return (ColorComponent) sqrt((TIME_UNIT - frame) * pow(origin, 2) + frame * pow(target, 2));
}

Color blender_blend_colors(Color origin, Color target, TimeVector frame) {
  assert(frame >= TIME_ORIGIN && frame <= TIME_UNIT);
  return (Color) {{blend_components(origin.rgba.r, target.rgba.r, frame),
                   blend_components(origin.rgba.g, target.rgba.g, frame),
                   blend_components(origin.rgba.b, target.rgba.b, frame),
                   blend_components(origin.rgba.a, target.rgba.a, frame)}};
}
