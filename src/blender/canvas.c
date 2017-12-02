#include "blender/canvas.h"

void canvas_init(Canvas *canvas, IntVector width, IntVector height) {
  canvas->mlv = MLV_create_image(width, height);
}

void canvas_free(Canvas *canvas) {
  MLV_free_image(canvas->mlv);
}

void canvas_set_pixel(Canvas *canvas, CartesianVector position, Color color) {
  MLV_set_pixel_on_image(position.x, position.x, color.mlv, canvas->mlv);
}

Color canvas_get_pixel(Canvas *canvas, CartesianVector position) {
  int r, g, b, a;
  MLV_get_pixel_on_image(canvas->mlv, position.x, position.y, &r, &g, &b, &a);
  return (Color) {{r, g, b, a}};
}

CartesianVector canvas_get_dim(Canvas *canvas) {
  return (CartesianVector) {MLV_get_image_width(canvas->mlv), MLV_get_image_height(canvas->mlv)};
}
