#ifndef UPEM_MORPHING_WINDOW
#define UPEM_MORPHING_WINDOW

/**
 * File: window.h
 * Windows and components handling.
 *
 * See also:
 *  The famous OS
 */

typedef void (*ClickHandler)(int x_pos, int y_pos);
/**
 * Type: Component
 * Abstract component that handles clicks.
 */
typedef struct {
  int width, height;
  ClickHandler click_handler;
} Component;
/**
 * Type: Window
 * Supports and handles components.
 */
typedef struct {
  int width, height;
  Component *components;
} Window;
/**
 * Function: window_init
 * Initializes a window.
 *
 * Parameters:
 *  *window - pointer to the input window
 *  width - width of the window to initialize
 *  height - height of the window to initialize
 *  *title - title of the actual window
 */
void window_init(Window *window, int width, int height, char *title);
/**
 * Function: window_free
 * Frees the resources supported by the window and the window itself.
 *
 * Parameters:
 *  *window - pointer to the input window
 */
void window_free(Window *window);
/**
 * Function: window_add_component
 * Adds components to the current window at the position specified in x and y.
 *
 * Parameters:
 *  *window - pointer to the input window
 *  *component - pointer to the input component
 *  x_pos - coordinate on x axis to place the component
 *  y_pos - coordinate on y axis to place the component
 */
void window_add_component(Window *window, Component *component, int x_pos, int y_pos);

#endif
