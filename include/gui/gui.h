#ifndef UPEM_MORPHING_GUI
#define UPEM_MORPHING_GUI

#include "gui/window.h"

/**
 * File: gui.h
 */


/**
 * Struct: GUI
 * Supports all the parts of the GUI
 *
 * Fields:
 *  *window - pointer to the Window
 *  *button1 - pointer to the button 1
 *  *button2 - pointer to the button 2
 *  *button3 - pointer to the button 3
 *  *button4 - pointer to the button 4
 *  *button5 - pointer to the button 5
 *  *button6 - pointer to the button 6
 *  *button7 - pointer to the button 7
 *  *pictureFrame1 - pointer to the picture frame 1
 *  *pictureFrame2 - pointer to the picture frame 2
 *  *canvasSrc - pointer to the canvas 1
 *  *canvasTrg - pointer to the canvas 2
 *  *morphing - pointer to the current morphing
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
} GUI;

/**
 * Function: gui_create
 *
 *
 * Parameters:
 *  *fpath1 - path to the first picture
 *  *fpath2 - path to the second picture
 *
 * Returns:
 *  A pointer to a GUI structure
 */
GUI *gui_create(const char *fpath1, const char *fpath2);

/**
 * Function: gui_handle_event
 * Builds and opens the graphical user interface.
 *
 * Parameters:
 *  *gui - pointer to the current GUI structure
 */
void gui_handle_event(GUI *gui);

/**
 * Function: gui_destroy
 * Frees the resources allocated for the GUI
 * Parameters:
 *  *gui - pointer to the current GUI structure
 */
void gui_destroy(GUI *gui);

#endif
