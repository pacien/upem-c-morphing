#include "blender/blender.h"
#include <assert.h>
#include <math.h>
#include "morpher/morpher.h"

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

void blender_blend_canvas(Canvas *canvas, Canvas *source, Canvas *target, Morphing *morphing, TimeVector frame) {
  IntVector flat_dim;
  CartesianVector dim, point;
  CartesianMapping mapping;
  Color pixel;

  dim = morpher_get_dim(morphing);

  assert(dim.x > 0 && dim.y > 0);
  assert(vector_equals(dim, canvas_get_dim(canvas)));
  assert(vector_equals(dim, canvas_get_dim(source)));
  assert(vector_equals(dim, canvas_get_dim(target)));
  assert(frame >= TIME_ORIGIN && frame <= TIME_UNIT);

  for (flat_dim = (dim.x - 1) * (dim.y - 1); flat_dim >= 0; --flat_dim) {
    point.x = flat_dim % dim.y;
    point.y = flat_dim / dim.y;

    mapping = morpher_get_point_mapping(morphing, point, frame);

    pixel = blender_blend_colors(canvas_get_pixel(source, mapping.origin),
                                 canvas_get_pixel(target, mapping.target),
                                 frame);

    canvas_set_pixel(canvas, point, pixel);
  }
}
