#include "gui/component.h"
#include <gui/group.h>
#include <gui/window.h>
#include <gui/button.h>
#include <gui/pictureframe.h>
#include <painter/rasterizer.h>
#include "MLV/MLV_all.h"

extern Mode mode;

static void test_pictureframe() {
  Window window;
  window_init(&window, 1005, 512, "Coucou");
  window_create(&window);

  Button button1;
  Button button2;
  Button button3;
  Button button4;
  Button button5;
  Button button6;
  Button button7;

  PictureFrame pictureFrame1;
  PictureFrame pictureFrame2;

  Morphing *morphing = morphing_create(500, 250);
  Canvas *canvasSrc = canvas_create_from_image("/home/adam/Images/goku.png");
  Canvas *canvasTarget = canvas_create_from_image("/home/adam/Images/marty.jpg");

  int i;

  sprintf(labelFrame, "%03d frames", frame);
  button_init(&button1, "Add constraint point", 10, 0, 0, button_click_add_constraint);
  button_init(&button2, "Show/Hide", 10, 0, 0, button_click_show_hide);
  button_init(&button3, "Start rendering", 10, 0, 0, button_click_rendering);
  button_init(&button4, "<<<", 10, 0, 0, button_click_less_frame);
  button_init(&button5, labelFrame, 10, 0, 0, button_click_none);
  button_init(&button6, ">>>", 10, 0, 0, button_click_more_frame);
  button_init(&button7, "Exit", 10, 0, 0, button_click_exit);


  pictureframe_init(&pictureFrame1, 500, 250, 0, 0, pictureframe_origin_split, morphing, canvasSrc,
                    pictureframe_click_handler_origin);
  pictureframe_init(&pictureFrame2, 500, 250, 0, 0, pictureframe_target_split, morphing, canvasTarget,
                    pictureframe_click_handler_target);

  window_add_pictureframe(&window, &pictureFrame1);
  window_add_pictureframe(&window, &pictureFrame2);

  window_add_button(&window, &button1);
  window_add_button(&window, &button2);
  window_add_button(&window, &button3);
  window_add_button(&window, &button4);
  window_add_button(&window, &button5);
  window_add_button(&window, &button6);
  window_add_button(&window, &button7);


  window_print_buttons(&window);
  window_print_pictureframes(&window);
  int mouse_x;
  int mouse_y;
  while (mode != EXITING) {
    MLV_wait_mouse(&mouse_x, &mouse_y);
    group_click_handler(mouse_x, mouse_y, &(window.group_buttons->component));
    group_click_handler(mouse_x, mouse_y, &(window.group_pictureframe->component));

    switch (mode) {
      case PRINTING:
        window_print_pictureframes(&window);
        mode = WAITING_BUTTON_SHOW;
        break;
      case WAITING_BUTTON_SHOW:
        window_print_pictureframes(&window);
        break;
      case WAITING_BUTTON_HIDE:
        window_print_pictureframes(&window);
        break;
      case PRINTING_BUTTONS:
        button_init(&button5, labelFrame, 10, button5.component.x_pos, button5.component.y_pos, button_click_none);
        window_print_buttons(&window);
        mode = WAITING_BUTTON_SHOW;
        break;
      case RENDERING:
        for (i = 1; i <= frame ; ++i) {
          pictureFrame1.canvas = rasterize(canvasSrc,canvasTarget,morphing,(TimeVector)(i/(float)frame));
          pictureframe_draw_canvas(&pictureFrame1);
          MLV_actualise_window();
          MLV_wait_seconds(1);
        }
        mode = EXITING;
        MLV_wait_seconds(15);
        break;
      default:
        break;
    }
  }
  canvas_destroy(canvasSrc);
  canvas_destroy(canvasTarget);

  morphing_destroy(morphing);

  window_free(&window);
}

int main() {
  test_pictureframe();
  return 0;
}