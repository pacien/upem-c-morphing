#include "gui/window.h"
#include <assert.h>
#include <MLV/MLV_all.h>
#include "painter/rasterizer.h"
#include "common/mem.h"

Window *window_create(int width, int height, char *title) {
  assert(width > 0);
  assert(height > 0);
  assert(title != NULL);
  Window *window = malloc_or_die(sizeof(Window));
  window->width = width;
  window->height = height;
  window->title = malloc_or_die(sizeof(char) * (strlen(title) + 1));
  strcpy(window->title, title);
  window->group_buttons = malloc_or_die(sizeof(Group));
  group_init(window->group_buttons, window->width, 100, 0, window->height - 100, 5);
  window->group_pictureframe = malloc_or_die(sizeof(Group));
  group_init(window->group_pictureframe, window->width, window->height - 100, 0, 0, 5);
  MLV_create_window(window->title, window->title, (unsigned int) window->width, (unsigned int) window->height);
  return window;
}

void window_destroy(Window *window) {
  assert(window != NULL);
  free(window->title);
  group_free(window->group_buttons);
  group_free(window->group_pictureframe);
  free(window);
}

void window_add_button(Window *window, Button *button) {
  assert(window != NULL);
  assert(button != NULL);
  group_add_component(window->group_buttons, &(button->component));
}

void window_add_pictureframe(Window *window, PictureFrame *pictureFrame) {
  assert(window != NULL);
  assert(pictureFrame != NULL);
  group_add_component(window->group_pictureframe, &(pictureFrame->component));
}

void window_print_buttons(Window *window) {
  assert(window != NULL);
  window->group_buttons->component.print_method(&(window->group_buttons->component));
  MLV_actualise_window();
}

void window_print_pictureframes(Window *window) {
  assert(window != NULL);
  window->group_pictureframe->component.print_method(&(window->group_pictureframe->component));
  MLV_actualise_window();
}

void window_wait_keyboard_or_mouse(MLV_Keyboard_button *keyboardButton, MLV_Keyboard_modifier *keyboardModifier,
                                   int *unicode, int *mouse_x, int *mouse_y) {
  *mouse_x = -1;
  *mouse_y = -1;
  *keyboardButton = MLV_KEYBOARD_NONE;
  MLV_wait_keyboard_or_mouse(keyboardButton, keyboardModifier, unicode, mouse_x, mouse_y);
}

void window_click_keyboard_handler(Window *window, MLV_Keyboard_button *keyboardButton,
                                   MLV_Keyboard_modifier *keyboardModifier,
                                   int *unicode, int *mouse_x, int *mouse_y) {
  window_wait_keyboard_or_mouse(keyboardButton, keyboardModifier, unicode, mouse_x, mouse_y);
  group_click_handler(*mouse_x, *mouse_y, &(window->group_buttons->component));
  group_click_handler(*mouse_x, *mouse_y, &(window->group_pictureframe->component));
}

void window_rendering(Window *window, PictureFrame pictureFrame1, Canvas *canvasSrc, Canvas *canvasTarget,
                      Morphing *morphing) {
  int i;
  window_print_pictureframes(window);
  for (i = 1; i <= frame; ++i) {
    pictureFrame1.canvas = rasterize(canvasSrc, canvasTarget, morphing, (TimeVector) (i / (float) frame));
    pictureframe_draw_canvas(&pictureFrame1);
    MLV_actualise_window();
    canvas_destroy(pictureFrame1.canvas);
    MLV_wait_milliseconds(16);
  }
  mode = WAITING_BUTTON_SHOW;
  window_print_pictureframes(window);
  MLV_actualise_window();
}
