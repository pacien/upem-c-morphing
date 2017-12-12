#include <stdlib.h>
#include <gui/window.h>
#include <gui/group.h>
#include <gui/component.h>
#include "gui/window.h"
#include "common/mem.h"
#include "string.h"
#include "assert.h"
#include "MLV/MLV_window.h"

void window_init(Window *window, int width, int height, char *title) {
  assert(window != NULL);
  assert(width > 0);
  assert(height > 0);
  window->width = width;
  window->height = height;
  assert(title != NULL);
  window->title = malloc_or_die(sizeof(char) * (strlen(title) + 1));
  strcpy(window->title, title);
  window->group_buttons = malloc_or_die(sizeof(Group));
  group_init(window->group_buttons, window->width, 100, 0, window->height - 100, 5);
  window->group_pictureframe = malloc_or_die(sizeof(Group));
  group_init(window->group_pictureframe, window->width, window->height - 100, 0, 0, 5);
}

void window_free(Window *window) {
  free(window->title);
  group_free(window->group_buttons);
  group_free(window->group_pictureframe);
}

void window_add_button(Window *window, Component *component) {
  group_add_component(window->group_buttons, component);
}

void window_add_pictureframe(Window *window, Component *component) {
  group_add_component(window->group_pictureframe, component);
}

void window_create(Window *window) {
  MLV_create_window(window->title, window->title, (unsigned int) window->width, (unsigned int) window->height);
}