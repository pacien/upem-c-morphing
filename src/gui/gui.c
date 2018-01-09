#include "gui/gui.h"
#include <MLV/MLV_all.h>
#include "common/mem.h"

/**
 * File: gui.c
 *
 * Author:
 *   Adam NAILI
 */

GUI *gui_create(const char *fpath1, const char *fpath2) {
  GUI *gui = malloc_or_die(sizeof(GUI));
  gui->window = window_create(500, 500, "Morphing");
  gui->canvasSrc = canvas_create_from_image(fpath1);
  gui->canvasTrg = canvas_create_from_image(fpath2);
  if (gui->canvasSrc->mlv == NULL || gui->canvasTrg->mlv == NULL) {
    canvas_destroy(gui->canvasSrc);
    canvas_destroy(gui->canvasTrg);
    window_destroy(gui->window);
    fprintf(stderr, "Impossible to create an image from the path given. Verify the two paths.\n");
    exit(-4);
  }
  int canvasSrcWidth;
  int canvasTrgWidth;
  int canvasSrcHeight;
  int canvasTrgHeight;

  MLV_get_image_size(gui->canvasSrc->mlv, &canvasSrcWidth, &canvasSrcHeight);
  MLV_get_image_size(gui->canvasTrg->mlv, &canvasTrgWidth, &canvasTrgHeight);

  if (canvasSrcWidth != canvasTrgWidth || canvasSrcHeight != canvasTrgHeight) {
    canvas_destroy(gui->canvasSrc);
    canvas_destroy(gui->canvasTrg);
    window_destroy(gui->window);
    fprintf(stderr, "The two pictures do not have the same size\n");
    exit(-5);
  }

  gui->window->width = 2 * canvasSrcWidth + 10;
  gui->window->height = canvasSrcHeight + 200;

  MLV_change_window_size((unsigned int) gui->window->width, (unsigned int) gui->window->height);

  gui->pictureFrame1 = malloc_or_die(sizeof(PictureFrame));
  gui->pictureFrame2 = malloc_or_die(sizeof(PictureFrame));

  gui->morphing = morphing_create(canvasSrcWidth, canvasSrcHeight);


  sprintf(labelFrame, "%03d frames", frame);
  gui->button1 = button_create("Add constraint point", 10, 0, 0, button_click_add_constraint);
  gui->button2 = button_create("Show/Hide", 10, 0, 0, button_click_show_hide);
  gui->button3 = button_create("Start rendering", 10, 0, 0, button_click_rendering);
  gui->button4 = button_create("<<<", 10, 0, 0, button_click_less_frame);
  gui->button5 = button_create(labelFrame, 10, 0, 0, button_click_none);
  gui->button6 = button_create(">>>", 10, 0, 0, button_click_more_frame);
  gui->button7 = button_create("Exit", 10, 0, 0, button_click_exit);

  gui->pictureFrame1 = pictureframe_create(canvasSrcWidth, canvasSrcHeight, 0, 0, pictureframe_origin_split,
                                           gui->morphing,
                                           gui->canvasSrc,
                                           pictureframe_click_handler_origin);
  gui->pictureFrame2 = pictureframe_create(canvasSrcWidth, canvasSrcHeight, 0, 0, pictureframe_target_split,
                                           gui->morphing,
                                           gui->canvasTrg,
                                           pictureframe_click_handler_target);

  window_add_pictureframe(gui->window, gui->pictureFrame1);
  window_add_pictureframe(gui->window, gui->pictureFrame2);

  window_add_button(gui->window, gui->button1);
  window_add_button(gui->window, gui->button2);
  window_add_button(gui->window, gui->button3);
  window_add_button(gui->window, gui->button4);
  window_add_button(gui->window, gui->button5);
  window_add_button(gui->window, gui->button6);
  window_add_button(gui->window, gui->button7);


  window_print_buttons(gui->window);
  window_print_pictureframes(gui->window);
  return gui;
}

void gui_handle_event(GUI *gui) {
  MLV_Keyboard_button keyboardButton;
  MLV_Keyboard_modifier keyboardModifier;
  int unicode;
  int mouse_x;
  int mouse_y;
  window_click_keyboard_handler(gui->window, &keyboardButton, &keyboardModifier, &unicode, &mouse_x,
                                &mouse_y);
  switch (mode) {
    case PRINTING:
      window_print_pictureframes(gui->window);
      mode = WAITING_BUTTON_SHOW;
      break;
    case WAITING_BUTTON_SHOW:
      window_print_pictureframes(gui->window);
      break;
    case WAITING_BUTTON_HIDE:
      window_print_pictureframes(gui->window);
      break;
    case PRINTING_BUTTONS:
      free(gui->button5->label);
      gui->button5->label = malloc_or_die(sizeof(char) * (strlen(labelFrame) + 1));
      strcpy(gui->button5->label, labelFrame);
      window_print_buttons(gui->window);
      mode = WAITING_BUTTON_SHOW;
      break;
    case RENDERING:
      window_rendering(gui->window, *(gui->pictureFrame1), gui->canvasSrc, gui->canvasTrg, gui->morphing);
      break;
    case INSERT_TARGET:
      if (keyboardButton == MLV_KEYBOARD_ESCAPE) {
        window_print_pictureframes(gui->window);
        mode = WAITING_BUTTON_SHOW;
      }
      break;
    default:
      break;
  }
}

void gui_destroy(GUI *gui) {
  window_destroy(gui->window);
  canvas_destroy(gui->canvasSrc);
  canvas_destroy(gui->canvasTrg);
  morphing_destroy(gui->morphing);

  button_destroy(gui->button1);
  button_destroy(gui->button2);
  button_destroy(gui->button3);
  button_destroy(gui->button4);
  button_destroy(gui->button5);
  button_destroy(gui->button6);
  button_destroy(gui->button7);

  pictureframe_destroy(gui->pictureFrame1);
  pictureframe_destroy(gui->pictureFrame2);
}
