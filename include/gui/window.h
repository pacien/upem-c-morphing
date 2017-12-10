#ifndef UPEM_MORPHING_WINDOW
#define UPEM_MORPHING_WINDOW

/**
 * File: window.h
 * Windows and components handling.
 *
 * See also:
 *  The famous OS
 */

#include "group.h"

/**
 * Type: ClickHandler
 * Type of functions that handle mouse's clicks.
 */
typedef void (*ClickHandler)(int x_pos, int y_pos);

/**
 * Type: PrintMethod
 * Type of functions that will be used to print our component. This must be initialized by the initialization function of the component.
 */
typedef void (*PrintMethod)(void);

/**
 * Struct: Component
 * Represents an abstract module handling clicks and a way to be print on the screen.
 *
 * Fields:
 *  width - width of the component
 *  height - height of the component
 *  x_pos - position on the x axis from the origin meant to be placed in top left
 *  y_pos - position on the y axis from the origin meant to be placed in top left
 *  click_handler - pointer of function that is called on mouse click
 *  print_method - pointer of function that handle the component's print
 */
typedef struct {
  int width, height;
  int x_pos, y_pos;
  ClickHandler click_handler;
  PrintMethod print_method;
} Component;
/**
 * Struct: Window
 * Supports and handles components.
 *
 * Fields:
 *   width - width of the window
 *   height - height of the window
 *   *title - string printed as name for the window
 *   *group_buttons - group that handles the buttons added to the window
 *   *group_pictureframe - group that handles the picture frames added to the window
 */
typedef struct {
  int width, height;
  char *title;
  Group *group_buttons;
  Group *group_pictureframe;
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
 * Function: window_add_button
 * Adds Button component to the group of buttons of the current window.
 *
 * Parameters:
 *  *window - pointer to the input window
 *  *component - pointer to the input component
 */
void window_add_button(Window *window, Component *component);

/**
 * Function: window_add_pictureframe
 * Adds PictureFrame component to the group of picture frames of the current window.
 *
 * Parameters:
 *  *window - pointer to the input window
 *  *component - pointer to the input component
 */
void window_add_pictureframe(Window *window, Component *component);


#endif
