#include "gui/component.h"
#include "gui/window.h"
#include "common/mem.h"

extern Mode mode;

static void test_pictureframe() {
  Window *window = window_create(1005, 512, "Coucou");

  sprintf(labelFrame, "%03d frames", frame);
  Button *button1 = button_create("Add constraint point", 10, 0, 0, button_click_add_constraint);
  Button *button2 = button_create("Show/Hide", 10, 0, 0, button_click_show_hide);
  Button *button3 = button_create("Start rendering", 10, 0, 0, button_click_rendering);
  Button *button4 = button_create("<<<", 10, 0, 0, button_click_less_frame);
  Button *button5 = button_create(labelFrame, 10, 0, 0, button_click_none);
  Button *button6 = button_create(">>>", 10, 0, 0, button_click_more_frame);
  Button *button7 = button_create("Exit", 10, 0, 0, button_click_exit);


  Morphing *morphing = morphing_create(500, 250);
  Canvas *canvasSrc = canvas_create_from_image("/home/adam/Images/goku.png");
  Canvas *canvasTarget = canvas_create_from_image("/home/adam/Images/marty.jpg");

  PictureFrame *pictureFrame1 = pictureframe_create(500, 250, 0, 0, pictureframe_origin_split, morphing, canvasSrc,
                                                    pictureframe_click_handler_origin);
  PictureFrame *pictureFrame2 = pictureframe_create(500, 250, 0, 0, pictureframe_target_split, morphing, canvasTarget,
                                                    pictureframe_click_handler_target);

  window_add_pictureframe(window, pictureFrame1);
  window_add_pictureframe(window, pictureFrame2);

  window_add_button(window, button1);
  window_add_button(window, button2);
  window_add_button(window, button3);
  window_add_button(window, button4);
  window_add_button(window, button5);
  window_add_button(window, button6);
  window_add_button(window, button7);


  window_print_buttons(window);
  window_print_pictureframes(window);

  MLV_Keyboard_button keyboardButton;
  MLV_Keyboard_modifier keyboardModifier;
  int unicode;
  int mouse_x;
  int mouse_y;

  while (mode != EXITING) {
    window_click_keyboard_handler(window, &keyboardButton, &keyboardModifier, &unicode, &mouse_x, &mouse_y);
    switch (mode) {
      case PRINTING:
        window_print_pictureframes(window);
        mode = WAITING_BUTTON_SHOW;
        break;
      case WAITING_BUTTON_SHOW:
        window_print_pictureframes(window);
        break;
      case WAITING_BUTTON_HIDE:
        window_print_pictureframes(window);
        break;
      case PRINTING_BUTTONS:
        free(button5->label);
        button5->label = malloc_or_die(sizeof(char) * (strlen(labelFrame) + 1));
        strcpy(button5->label, labelFrame);
        window_print_buttons(window);
        mode = WAITING_BUTTON_SHOW;
        break;
      case RENDERING:
        window_rendering(window, pictureFrame1, canvasSrc, canvasTarget, morphing);
        break;
      case INSERT_TARGET:
        if (keyboardButton == MLV_KEYBOARD_ESCAPE) {
          window_print_pictureframes(window);
          mode = WAITING_BUTTON_SHOW;
        }
        break;
      default:
        break;
    }
  }

  button_destroy(button1);
  button_destroy(button2);
  button_destroy(button3);
  button_destroy(button4);
  button_destroy(button5);
  button_destroy(button6);
  button_destroy(button7);

  pictureframe_destroy(pictureFrame1);
  pictureframe_destroy(pictureFrame2);

  canvas_destroy(canvasSrc);
  canvas_destroy(canvasTarget);
  morphing_destroy(morphing);

  window_destroy(window);
}

int main() {
  test_pictureframe();
  return 0;
}