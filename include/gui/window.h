#ifndef UPEM_MORPHING_WINDOW
#define UPEM_MORPHING_WINDOW

/**
 * File: window.h
 */

typedef void (*ClickHandler)(int x_pos, int y_pos);

typedef struct {
  int width, height;
  ClickHandler click_handler;
} Component;

typedef struct {
  int width, height;
  Component *components;
} Window;

void window_init(Window *window, int width, int height, char *title);

void window_free(Window *window);

void window_add_component(Window *window, Component *component, int x_pos, int y_pos);

#endif
