#ifndef UPEM_MORPHING_BUTTON
#define UPEM_MORPHING_BUTTON

/**
 * File: button.h
 */

typedef struct {
  Component component;
} Button;

void button_init(Button *button, char *text);

void button_free(Button *button);

#endif
