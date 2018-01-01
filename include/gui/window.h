#ifndef UPEM_MORPHING_WINDOW
#define UPEM_MORPHING_WINDOW

/**
 * File: window.h
 * Windows and components handling.
 *
 * See also:
 *  The famous OS
 */

#include <MLV/MLV_keyboard.h>
#include "group.h"
#include "component.h"
#include "button.h"
#include "pictureframe.h"

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
 *  *button - pointer to the input button
 */
void window_add_button(Window *window, Button *button);

/**
 * Function: window_add_pictureframe
 * Adds PictureFrame component to the group of picture frames of the current window.
 *
 * Parameters:
 *  *window - pointer to the input window
 *  *pictureFrame - pointer to the input picture frame
 */
void window_add_pictureframe(Window *window, PictureFrame *pictureFrame);

/**
 * Function: window_create
 * Initializes the resources to create a window.
 *
 * Parameters:
 *  *window - pointer to the input window
 */
void window_create(Window *window);

/**
 * Function: window_print_buttons
 * Prints all the buttons to the screen
 *
 * Parameters:
 *  *window - pointer to the input window
 */
void window_print_buttons(Window *window);

/**
 * Function: window_print_pictureframes
 * Prints all the picture frames to the screen
 *
 * Parameters:
 *  *window - pointer to the input window
 */
void window_print_pictureframes(Window *window);

void window_click_keyboard_handler(Window *window, MLV_Keyboard_button *keyboardButton,
                                   MLV_Keyboard_modifier *keyboardModifier,
                                   int *unicode, int *mouse_x, int *mouse_y);
void window_rendering(Window *window,PictureFrame *pictureFrame1,Canvas *canvasSrc, Canvas *canvasTarget, Morphing *morphing);

#endif
