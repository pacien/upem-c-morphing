#ifndef UPEM_MORPHING_BUTTON
#define UPEM_MORPHING_BUTTON

/**
 * File: button.h
 * Buttons handling
 */
#include "window.h"

/**
 * Struct: Button
 * Component that can be triggered by click to execute a specific action.
 *
 * Fields:
 *   component - component that will acted as a button thanks to a rightful initialization.
 */
typedef struct {
  Component component;
} Button;

/**
 * Function: button_init
 * Initializes the button.
 *
 * Parameters:
 *  *button - pointer to the input button
 *  text - label for the button
 */
void button_init(Button *button, char *text);


#endif
