#include <stdlib.h>
#include <gui/window.h>
#include <gui/button.h>
#include <gui/pictureframe.h>
#include <gui/group.h>
#include "common/mem.h"
#include "string.h"
#include "assert.h"
#include "MLV/MLV_window.h"

void window_init(Window *window, int width, int height, char *title) {
  assert(window != NULL);
  assert(width > 0);
  assert(height > 0);
  assert(title != NULL);
  window->width = width;
  window->height = height;
  window->title = malloc_or_die(sizeof(char) * (strlen(title) + 1));
  strcpy(window->title, title);
  window->group_buttons = malloc_or_die(sizeof(Group));
  group_init(window->group_buttons, window->width, 100, 0, window->height - 100, 5);
  window->group_pictureframe = malloc_or_die(sizeof(Group));
  group_init(window->group_pictureframe, window->width, window->height - 100, 0, 0, 5);
}

void window_free(Window *window) {
  assert(window != NULL);
  free(window->title);
  group_free(window->group_buttons);
  group_free(window->group_pictureframe);
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

void window_create(Window *window) {
  assert(window != NULL);
  MLV_create_window(window->title, window->title, (unsigned int) window->width, (unsigned int) window->height);
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