#include <gui/group.h>
#include <gui/window.h>
#include "MLV/MLV_all.h"


static void test_group() {
  /*Window window;
  window_init(&window, 1000, 512, "Coucou");
  window_create(&window);

  Button button1;
  Button button2;
  Button button3;

  button_init(&button1, "OK", 10, 500, 256, button_click_test);
  button_init(&button2,"Bouton magique",10, 500,290, button_click_test);
  button_init(&button3,"Très lonnggggg boooouttttooooon",10,0,0,button_click_test);

  window_add_button(&window,&button1);
  window_add_button(&window,&button2);
  window_add_button(&window,&button3);

  window_print_buttons(&window);
  int mouse_x;
  int mouse_y;
  while(1){
    if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) {
      MLV_get_mouse_position(&mouse_x, &mouse_y);
      group_click_handler(mouse_x,mouse_y,&(window.group_buttons->component));
    }
  }
  MLV_wait_seconds(15);
  window_destroy(&window);*/
}

int main() {
  test_group();
  return 0;
}