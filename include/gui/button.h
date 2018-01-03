#ifndef UPEM_MORPHING_BUTTON
#define UPEM_MORPHING_BUTTON
/**
 * File: button.h
 * Buttons handling
 */

#include "component.h"

/**
 * Struct: Button
 * Component that can be triggered by click to execute a specific action.
 *
 * Fields:
 *   component - component that will acted as a button thanks to a rightful initialization
 *   *label - title on the button
 *   sizeInterligne - parameter that change padding of the button
 */
typedef struct {
  Component component;
  char *label;
  int sizeInterligne;
} Button;

/**
 * Function: button_create
 * Allocates and initializes the button.
 *
 * Parameters:
 *  text - label for the button
 *  sizeInterligne - parameter to initialize padding inside the button
 *  x_pos - position of the button on x axis
 *  y_pos - position of the button on y axis
 *  clickHandler - pointer of function that will be loaded inside our button to perform its purpose
 *
 * Returns:
 *  A pointer of Button
 */
Button *
button_create(const char *text, int sizeInterligne, int x_pos, int y_pos, ClickHandler clickHandler);

/**
 * Function: button_destroy
 * Frees the resources for the Button
 *
 * Parameters:
 *  *button - pointer to the button
 */
void button_destroy(Button *button);

/**
 * Function: button_click_add_constraint
 * Allows to add a constraint point in order on the first picture, then on the second.
 *
 * Parameters:
 *  x - position of the click on x axis
 *  y - position of the click on y axis
 *  *parameterSelf - pointer on the button that is clicked
 */
void button_click_add_constraint(int x, int y, Component *parameterSelf);

/**
 * Function: button_click_show_hide
 * Allows to show and hide the constraint points and triangles.
 *
 * Parameters:
 *  x - position of the click on x axis
 *  y - position of the click on y axis
 *  *parameterSelf - pointer on the button that is clicked
 */
void button_click_show_hide(int x, int y, Component *parameterSelf);

/**
 * Function: button_click_exit
 * Quit the program.
 *
 * Parameters:
 *  x - position of the click on x axis
 *  y - position of the click on y axis
 *  *parameterSelf - pointer on the button that is clicked.
 */
void button_click_exit(int x, int y, Component *parameterSelf);

/**
 * Function: button_click_none
 * Allows the button to do nothing on click.
 *
 * Parameters:
 *  x - position of the click on x axis
 *  y - position of the click on y axis
 *  *parameterSelf - pointer on the button that is clicked
 */
void button_click_none(int x, int y, Component *parameterSelf);


/**
 * Function: button_click_more_frame
 * Multiplies by two the number of frames to create when rendering.
 *
 * Parameters:
 *  x - position of the click on x axis
 *  y - position of the click on y axis
 *  *parameterSelf - pointer on the button that is clicked
 */
void button_click_more_frame(int x, int y, Component *parameterSelf);

/**
 * Function: button_click_less_frame
 * Divides by two the number of frames to create when rendering.
 *
 * Parameters:
 *  x - position of the click on x axis
 *  y - position of the click on y axis
 *  *parameterSelf - pointer on the button that is clicked
 */
void button_click_less_frame(int x, int y, Component *parameterSelf);

/**
 * Function: button_click_rendering
 * Launches the rendering of the morphing
 *
 * Parameters:
 *  x - position of the click on x axis
 *  y - position of the click on y axis
 *  *parameterSelf - pointer on the button that is clicked
 */
void button_click_rendering(int x, int y, Component *parameterSelf);


#endif
