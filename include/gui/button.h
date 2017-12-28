#ifndef UPEM_MORPHING_BUTTON
#define UPEM_MORPHING_BUTTON
/**
 * File: button.h
 * Buttons handling
 */

#include <stdbool.h>
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
 * Function: button_init
 * Initializes the button.
 *
 * Parameters:
 *  *button - pointer to the input button
 *  text - label for the button
 *  sizeInterligne - parameter to initialize padding inside the button
 *  x_pos - position of the button on x axis
 *  y_pos - position of the button on y axis
 *  clickHandler - pointer of function that will be loaded inside our button to perform its purpose
 */
void button_init(Button *button, const char *text, int sizeInterligne, int x_pos, int y_pos, ClickHandler clickHandler);

/**
 * Function: button_print
 * Prints the button.
 *
 * Parameters:
 *  *parameterSelf - pointer to the button
 */
void button_print(Component *parameterSelf);

/**
 * Function: button_click_test
 * Debug function to test if the click is working on the current button.
 *
 * Parameters:
 *  x - position of the click on x axis
 *  y - position of the click on y axis
 *  *parameterSelf - pointer on the button that is clicked
 */
void button_click_test(int x, int y, Component *parameterSelf);

void button_click_add_constraint(int x, int y, Component *parameterSelf);
/**
 * Function: button_is_selected
 * Checks if the button is selected or not.
 *
 * Parameters:
 *  x - position in x for the check
 *  y - position in y for the check
 *  *button - pointer to the current button
 *
 * Returns:
 *  A bool from stdbool
 */

bool button_is_selected(int x, int y, Button *button);

#endif
