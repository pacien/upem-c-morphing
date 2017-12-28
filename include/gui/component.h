#ifndef UPEM_C_COMPONENT_H
#define UPEM_C_COMPONENT_H
typedef enum {
  WAITING_BUTTON, INSERT_ORIGIN, INSERT_TARGET,PRINTING
} Mode;

extern Mode mode;
/**
 * File: component.h
 * Windows and components handling.
 *
 * See also:
 *  The famous OS
 */
struct Component;

/**
 * Type: ClickHandler
 * Type of functions that handle mouse's clicks.
 */
typedef void (*ClickHandler)(int x_pos, int y_pos, struct Component *parameter);

/**
 * Type: PrintMethod
 * Type of functions that will be used to print our component. This must be initialized by the initialization function of the component.
 */
typedef void (*PrintMethod)(struct Component *);

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
typedef struct Component {
  int width, height;
  int x_pos, y_pos;
  ClickHandler click_handler;
  PrintMethod print_method;
} Component;

#endif //UPEM_C_COMPONENT_H
