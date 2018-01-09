#ifndef UPEM_MORPHING_COMPONENT
#define UPEM_MORPHING_COMPONENT

/**
 * File: component.h
 *
 * Author:
 *   Adam NAILI
 */

/**
 * Enum: Mode
 *
 * WAITING_BUTTON_SHOW - Waits a click on buttons to perform actions and paints the constraint points on the GUI
 * WAITING_BUTTON_HIDE - Waits a click on buttons to perform actions and does not print the constraint points on the GUI
 * INSERT_ORIGIN - Waits a click on the origin pictureframe and lock other components
 * INSERT_TARGET - Waits a click on the target pictureframe and lock other components
 * PRINTING - Force the application to paint the pictureframes
 * EXITING - Exits the programme
 * PRINTING_BUTTONS - paints the buttons
 * RENDERING - launches the rendering mode
 */
typedef enum {
  WAITING_BUTTON_SHOW, WAITING_BUTTON_HIDE, INSERT_ORIGIN, INSERT_TARGET, PRINTING, EXITING, PRINTING_BUTTONS, RENDERING
} Mode;

extern Mode mode;
extern int frame;
extern char labelFrame[20];
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
