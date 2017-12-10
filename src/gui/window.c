#include <stdlib.h>
#include <gui/window.h>
#include <common/mem.h>
#include "string.h"
#include "assert.h"

void window_init(Window *window, int width, int height, char *title) {
  window = malloc_or_die(sizeof(window));
  assert(width > 0);
  assert(height > 0);
  window->width = width;
  window->height = height;
  assert(title != NULL);
  strcpy(window->title,title);
  window->group_buttons = malloc_or_die(sizeof(Group));
  window->group_pictureframe = malloc_or_die(sizeof(Group));
}

void window_free(Window *window) {
  group_free(window->group_buttons);
  group_free(window->group_pictureframe);
}

void window_add_button(Window *window, Component *component){
  group_add_component(window->group_buttons,component);
}

void window_add_pictureframe(Window *window, Component *component){
  group_add_component(window->group_pictureframe,component);
}