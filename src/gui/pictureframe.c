#include <assert.h>
#include <gui/pictureframe.h>
#include <MLV/MLV_all.h>

CartesianVector pictureframe_origin_split(const CartesianMapping *cartesianMapping) {
  return cartesianMapping->origin;
}

CartesianVector pictureframe_target_split(const CartesianMapping *cartesianMapping) {
  return cartesianMapping->target;
}

void pictureframe_draw_canvas(PictureFrame *pictureFrame){
  MLV_draw_image(pictureFrame->canvas->mlv, pictureFrame->component.x_pos, pictureFrame->component.y_pos);
}

void pictureframe_print(Component *parameterSelf) {
  PictureFrame *self = (PictureFrame *) parameterSelf;
  pictureframe_draw_canvas(self);
  if (mode != WAITING_BUTTON_HIDE && mode != RENDERING) {
    TriangleMap *p = self->morphing->first;
    CartesianVector p1;
    CartesianVector p2;
    CartesianVector p3;
    CartesianVector pointToPrint1;
    CartesianVector pointToPrint2;
    CartesianVector pointToPrint3;
    while (p != NULL) {
      p1 = self->cartesianMappingDivision(&(p->vertices[0]));
      p2 = self->cartesianMappingDivision(&(p->vertices[1]));
      p3 = self->cartesianMappingDivision(&(p->vertices[2]));

      pointToPrint1 = pictureframe_conversion_to_origin(p1.x, p1.y, self);
      pointToPrint2 = pictureframe_conversion_to_origin(p2.x, p2.y, self);
      pointToPrint3 = pictureframe_conversion_to_origin(p3.x, p3.y, self);

      MLV_draw_filled_circle(pointToPrint1.x, pointToPrint1.y, 2, MLV_COLOR_RED);
      MLV_draw_filled_circle(pointToPrint2.x, pointToPrint2.y, 2, MLV_COLOR_RED);
      MLV_draw_filled_circle(pointToPrint3.x, pointToPrint3.y, 2, MLV_COLOR_RED);

      MLV_draw_line(pointToPrint1.x, pointToPrint1.y, pointToPrint2.x, pointToPrint2.y, MLV_COLOR_RED);
      MLV_draw_line(pointToPrint1.x, pointToPrint1.y, pointToPrint3.x, pointToPrint3.y, MLV_COLOR_RED);
      MLV_draw_line(pointToPrint3.x, pointToPrint3.y, pointToPrint2.x, pointToPrint2.y, MLV_COLOR_RED);
      p = p->next;
    }
  }
}

bool pictureframe_is_selected(int x, int y, PictureFrame *pictureFrame) {
  assert(pictureFrame != NULL);
  int x1 = pictureFrame->component.x_pos;
  int y1 = pictureFrame->component.y_pos;
  int x2 = pictureFrame->component.x_pos + pictureFrame->component.width;
  int y2 = pictureFrame->component.y_pos + pictureFrame->component.height;
  if (x >= x1 && x <= x2 && y >= y1 && y <= y2) {
    return true;
  }
  return false;
}

CartesianVector pictureframe_conversion_to_pic(int x, int y, PictureFrame *pictureFrame) {
  CartesianVector vector;
  vector.x = x - pictureFrame->component.x_pos;
  vector.y = y - pictureFrame->component.y_pos;
  return vector;
}

CartesianVector pictureframe_conversion_to_origin(int x, int y, PictureFrame *pictureFrame) {
  CartesianVector vector;
  vector.x = x + pictureFrame->component.x_pos;
  vector.y = y + pictureFrame->component.y_pos;
  return vector;
}

void pictureframe_click_handler_origin(int x_pos, int y_pos, Component *parameterSelf) {
  PictureFrame *self = (PictureFrame *) parameterSelf;
  if (pictureframe_is_selected(x_pos, y_pos, self) && mode == INSERT_ORIGIN) {
    CartesianVector vector = pictureframe_conversion_to_pic(x_pos, y_pos, self);
    MLV_draw_filled_circle(x_pos, y_pos, 2, MLV_COLOR_BLUE);
    savedPoint = vector;
    MLV_actualise_window();
    mode = INSERT_TARGET;
  }
}

void pictureframe_click_handler_target(int x_pos, int y_pos, Component *parameterSelf) {
  PictureFrame *self = (PictureFrame *) parameterSelf;
  if (pictureframe_is_selected(x_pos, y_pos, self) && mode == INSERT_TARGET) {
    CartesianVector vector = pictureframe_conversion_to_pic(x_pos, y_pos, self);
    morphing_add_constraint(self->morphing, savedPoint, vector);
    mode = PRINTING;
  }
}

void pictureframe_init(PictureFrame *pictureFrame, int width, int height, int x_pos, int y_pos,
                       CartesianMappingDivision cartesianMappingDivision, Morphing *morphing, Canvas *canvas,
                       ClickHandler clickHandler) {
  assert(pictureFrame != NULL);
  assert(width > 0);
  assert(height > 0);
  assert(x_pos >= 0);
  assert(y_pos >= 0);
  assert(cartesianMappingDivision != NULL);
  assert(morphing != NULL);
  assert(canvas != NULL);
  pictureFrame->component.width = width;
  pictureFrame->component.height = height;
  pictureFrame->component.x_pos = x_pos;
  pictureFrame->component.y_pos = y_pos;
  pictureFrame->component.print_method = pictureframe_print;
  pictureFrame->component.click_handler = clickHandler;
  pictureFrame->morphing = morphing;
  pictureFrame->canvas = canvas;
  pictureFrame->cartesianMappingDivision = cartesianMappingDivision;
}