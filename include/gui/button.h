#ifndef UPEM_MORPHING_BUTTON
#define UPEM_MORPHING_BUTTON

#include "window.h"
/**
 * File: button.h
 * Buttons handling
 */

/**
 * Type: Button
 * Component that can be triggered by click to execute a specific action.
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

/**
 * Function: button_free
 * Frees the resources for the button.
 *
 * Parameters:
 *  *button - pointer to the input button
 */
void button_free(Button *button);

#endif
