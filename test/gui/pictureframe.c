#include "gui/component.h"
#include <gui/group.h>
#include <gui/window.h>
#include "MLV/MLV_all.h"

extern Mode mode;

static void test_pictureframe() {
  Window window;
  window_init(&window, 1005, 512, "Coucou");
  window_create(&window);

  Button button1;

  PictureFrame pictureFrame1;
  PictureFrame pictureFrame2;

  Morphing *morphing = morphing_create(500, 250);
  Canvas *canvas1 = canvas_create_from_image("/home/adam/Images/goku.png");
  Canvas *canvas2 = canvas_create_from_image("/home/adam/Images/marty.jpg");

  button_init(&button1, "Add constraint point", 10, 0, 0, button_click_add_constraint);

  pictureframe_init(&pictureFrame1, 500, 250, 0, 0, pictureframe_origin_split, morphing, canvas1,
                    pictureframe_click_handler_origin);
  pictureframe_init(&pictureFrame2, 500, 250, 0, 0, pictureframe_target_split, morphing, canvas2,
                    pictureframe_click_handler_target);

  window_add_pictureframe(&window, &pictureFrame1);
  window_add_pictureframe(&window, &pictureFrame2);

  window_add_button(&window, &button1);
  window_print_buttons(&window);
  window_print_pictureframes(&window);
  int mouse_x;
  int mouse_y;
  while (1) {
    if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) {
      MLV_get_mouse_position(&mouse_x, &mouse_y);
      group_click_handler(mouse_x, mouse_y, &(window.group_buttons->component));
      group_click_handler(mouse_x, mouse_y, &(window.group_pictureframe->component));
    if(mode == PRINTING){
      window_print_pictureframes(&window);
      mode = WAITING_BUTTON;
    }
    }
  }
  /*MLV_wait_seconds(15);
  window_free(&window);*/
}

int main() {
  test_pictureframe();
  return 0;
}