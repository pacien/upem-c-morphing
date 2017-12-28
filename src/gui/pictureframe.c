#include <assert.h>
#include <gui/pictureframe.h>
#include <MLV/MLV_all.h>

CartesianVector pictureframe_origin_split(const CartesianMapping *cartesianMapping) {

}

CartesianVector pictureframe_target_split(const CartesianMapping *cartesianMapping) {

}

void pictureframe_print(Component *parameterSelf) {
  PictureFrame *self = (PictureFrame *) parameterSelf;
  /*DEBUG*/
  MLV_draw_filled_rectangle(self->component.x_pos, self->component.y_pos, self->component.width, self->component.height,
                            MLV_COLOR_RED);
  /**/
}

void pictureframe_click_handler(int x_pos, int y_pos, Component *parameterSelf) {
  printf("ClickHandler pictureframe activated \n");
}

void pictureframe_init(PictureFrame *pictureFrame, int width, int height, int x_pos, int y_pos,
                       CartesianMappingDivision cartesianMappingDivision, Morphing *morphing, Canvas *canvas) {
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
  pictureFrame->component.activated = true;
  pictureFrame->component.print_method = pictureframe_print;
  pictureFrame->component.click_handler = pictureframe_click_handler;
  pictureFrame->morphing = morphing;
  pictureFrame->canvas = canvas;
  pictureFrame->cartesianMappingDivision = cartesianMappingDivision;
}