#ifndef UPEM_MORPHING_WINDOW
#define UPEM_MORPHING_WINDOW

#include "MLV/MLV_keyboard.h"
#include "group.h"
#include "button.h"
#include "pictureframe.h"
/**
 * File: window.h
 * Windows and components handling.
 */

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
 * Function: window_create
 * Allocates and initializes a window.
 *
 * Parameters:
 *  width - width of the window to initialize
 *  height - height of the window to initialize
 *  *title - title of the actual window
 * Returns:
 *  A pointer to a Window
 */
Window *window_create(int width, int height, char *title);

/**
 * Function: window_destroy
 * Frees the resources supported by the window and the window itself.
 *
 * Parameters:
 *  *window - pointer to the input window
 */
void window_destroy(Window *window);

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

/**
 * Function: window_click_keyboard_handler
 * Handles click and keyboard.
 *
 * Parameters:
 *  *window - pointer to the current window
 *  *keyboardButton - code of the keyboard key that is pushed or released
 *  *keyboardModifier - mode of the keyboard when a key is push or released
 *  *unicode - character coded in unicode of the letter obtained by combining the code and the mode
 *  *mouse_x - coordinate on the X axis of the mouse
 *  *mouse_y - coordinate on the Y axis of the mouse
 */
void window_click_keyboard_handler(Window *window, MLV_Keyboard_button *keyboardButton,
                                   MLV_Keyboard_modifier *keyboardModifier,
                                   int *unicode, int *mouse_x, int *mouse_y);

/**
 * Function: window_rendering
 * Launches the rendering on the pictureframe origin.
 *
 * Parameters:
 *  *window - pointer to the current window
 *  *pictureFrame1 - pointer to the origin PictureFrame
 *  *canvasSrc - pointer to the source Canvas
 *  *canvasTarget - pointer to the target Canvas
 *  *morphing - pointer to the Morphing that will makes the transformation
 */
void window_rendering(Window *window, PictureFrame *pictureFrame1, Canvas *canvasSrc, Canvas *canvasTarget,
                      Morphing *morphing);

#endif
