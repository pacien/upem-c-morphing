#include <gui/window.h>
#include <gui/gui.h>
#include <common/mem.h>
#include <MLV/MLV_all.h>
#include <gui/button.h>


GUI *gui_init(const char *fpath1, const char *fpath2) {
  GUI *gui = malloc_or_die(sizeof(GUI));

  gui->window = malloc_or_die(sizeof(Window));
  window_init(gui->window, 500, 500, "Morphing");
  window_create(gui->window);
  gui->canvasSrc = canvas_create_from_image(fpath1);
  gui->canvasTrg = canvas_create_from_image(fpath2);
  if (gui->canvasSrc->mlv == NULL || gui->canvasTrg->mlv == NULL) {
    canvas_destroy(gui->canvasSrc);
    canvas_destroy(gui->canvasTrg);
    /*window_free(gui->window);*/
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
    window_free(gui->window);
    fprintf(stderr, "The two pictures do not have the same size\n");
    exit(-5);
  }

  gui->window->width = 2 * canvasSrcWidth + 10;
  gui->window->height = canvasSrcHeight + 200;

  MLV_change_window_size((unsigned int) gui->window->width, (unsigned int) gui->window->height);

  gui->button1 = malloc_or_die(sizeof(Button));
  gui->button2 = malloc_or_die(sizeof(Button));
  gui->button3 = malloc_or_die(sizeof(Button));
  gui->button4 = malloc_or_die(sizeof(Button));
  gui->button5 = malloc_or_die(sizeof(Button));
  gui->button6 = malloc_or_die(sizeof(Button));
  gui->button7 = malloc_or_die(sizeof(Button));

  gui->pictureFrame1 = malloc_or_die(sizeof(PictureFrame));
  gui->pictureFrame2 = malloc_or_die(sizeof(PictureFrame));

  gui->morphing = morphing_create(canvasSrcWidth, canvasSrcHeight);


  sprintf(labelFrame, "%03d frames", frame);
  button_init(gui->button1, "Add constraint point", 10, 0, 0, button_click_add_constraint);
  button_init(gui->button2, "Show/Hide", 10, 0, 0, button_click_show_hide);
  button_init(gui->button3, "Start rendering", 10, 0, 0, button_click_rendering);
  button_init(gui->button4, "<<<", 10, 0, 0, button_click_less_frame);
  button_init(gui->button5, labelFrame, 10, 0, 0, button_click_none);
  button_init(gui->button6, ">>>", 10, 0, 0, button_click_more_frame);
  button_init(gui->button7, "Exit", 10, 0, 0, button_click_exit);

  pictureframe_init(gui->pictureFrame1, canvasSrcWidth, canvasSrcHeight, 0, 0, pictureframe_origin_split, gui->morphing,
                    gui->canvasSrc,
                    pictureframe_click_handler_origin);
  pictureframe_init(gui->pictureFrame2, canvasSrcWidth, canvasSrcHeight, 0, 0, pictureframe_target_split, gui->morphing,
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
  window_click_keyboard_handler(gui->window, &gui->keyboardButton, &gui->keyboardModifier, &gui->unicode, &gui->mouse_x,
                                &gui->mouse_y);
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
      button_init(gui->button5, labelFrame, 10, gui->button5->component.x_pos, gui->button5->component.y_pos,
                  button_click_none);
      window_print_buttons(gui->window);
      mode = WAITING_BUTTON_SHOW;
      break;
    case RENDERING:
      window_rendering(gui->window, gui->pictureFrame1, gui->canvasSrc, gui->canvasTrg, gui->morphing);
      break;
    case INSERT_TARGET:
      if (gui->keyboardButton == MLV_KEYBOARD_ESCAPE) {
        window_print_pictureframes(gui->window);
        mode = WAITING_BUTTON_SHOW;
      }
      break;
    default:
      break;
  }
}

void gui_free(GUI *gui) {
  window_free(gui->window);
  canvas_destroy(gui->canvasSrc);
  canvas_destroy(gui->canvasTrg);
  morphing_destroy(gui->morphing);

  free(gui->button1);
  free(gui->button2);
  free(gui->button3);
  free(gui->button4);
  free(gui->button5);
  free(gui->button6);
  free(gui->button7);
  free(gui->pictureFrame1);
  free(gui->pictureFrame2);
}