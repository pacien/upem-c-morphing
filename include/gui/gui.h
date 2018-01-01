#ifndef UPEM_MORPHING_GUI
#define UPEM_MORPHING_GUI

#include <gui/window.h>
/**
 * File: gui.h
 */

typedef struct {
  Window *window;
  Button *button1;
  Button *button2;
  Button *button3;
  Button *button4;
  Button *button5;
  Button *button6;
  Button *button7;
  PictureFrame *pictureFrame1;
  PictureFrame *pictureFrame2;
  Canvas *canvasSrc;
  Canvas *canvasTrg;
  Morphing *morphing;
  MLV_Keyboard_button keyboardButton;
  MLV_Keyboard_modifier keyboardModifier;
  int unicode;
  int mouse_x;
  int mouse_y;
} GUI;


GUI *gui_init(const char *fpath1, const char *fpath2);
/**
 * Function: gui_handle_event
 * Builds and opens the graphical user interface.
 */
void gui_handle_event(GUI *gui);

void gui_free(GUI *gui);
#endif
