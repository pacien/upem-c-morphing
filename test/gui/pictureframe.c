#include <gui/group.h>
#include <gui/window.h>
#include "MLV/MLV_all.h"


static void test_pictureframe() {
  Window window;
  window_init(&window, 1000, 512, "Coucou");
  window_create(&window);

  PictureFrame pictureFrame1;
  PictureFrame pictureFrame2;

  Morphing *morphing = morphing_create(500,250);
  Canvas canvas;
  canvas_init(&canvas,500,250);

  pictureframe_init(&pictureFrame1,500,250,0,0,pictureframe_origin_split,morphing,&canvas);
  pictureframe_init(&pictureFrame2,500,250,0,0,pictureframe_target_split,morphing,&canvas);

  window_add_pictureframe(&window,&pictureFrame1);
  window_add_pictureframe(&window,&pictureFrame2);

  window_print_pictureframes(&window);
  int mouse_x;
  int mouse_y;
  while(1){
    if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) {
      MLV_get_mouse_position(&mouse_x, &mouse_y);
      group_click_handler(mouse_x,mouse_y,&(window.group_pictureframe->component));
    }
  }
  /*MLV_wait_seconds(15);
  window_free(&window);*/
}

int main() {
  test_pictureframe();
  return 0;
}