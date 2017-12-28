#include "painter/canvas.h"
#include "common/mem.h"

Canvas *canvas_create(IntVector width, IntVector height) {
  Canvas *c = malloc_or_die(sizeof(Canvas));
  c->mlv = MLV_create_image(width, height);
  return c;
}

Canvas *canvas_create_from_image(const char *fpath) {
  Canvas *c = malloc_or_die(sizeof(Canvas));
  c->mlv = MLV_load_image(fpath);
  return c;
}

void canvas_destroy(Canvas *c) {
  MLV_free_image(c->mlv);
  free(c);
}

void canvas_set_pixel(Canvas *c, CartesianVector pos, Color color) {
  MLV_set_pixel_on_image(pos.x, pos.y, color.mlv, c->mlv);
}

Color canvas_get_pixel(Canvas *c, CartesianVector pos) {
  int r, g, b, a;
  MLV_get_pixel_on_image(c->mlv, pos.x, pos.y, &r, &g, &b, &a);
  return (Color) {{a, b, g, r}};
}

CartesianVector canvas_get_dim(Canvas *c) {
  return (CartesianVector) {MLV_get_image_width(c->mlv), MLV_get_image_height(c->mlv)};
}
