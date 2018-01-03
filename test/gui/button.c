#include <gui/group.h>
#include <gui/window.h>
#include <gui/button.h>
#include <gui/component.h>
#include "MLV/MLV_all.h"


static void test_button() {
 /* Window window;
  window_init(&window, 1000, 512, "Coucou");
  window_create(&window);
  Button button1;
  button_init(&button1, "OK", 10, 500, 256, button_click_test);
  button1.component.print_method(&button1);
  int mouse_x;
  int mouse_y;
  while (1) {
    if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) {
      MLV_get_mouse_position(&mouse_x, &mouse_y);
      button1.component.click_handler(mouse_x, mouse_y, &(button1.component));
    }
  }*/
  /*MLV_wait_seconds(10);
  window_destroy(&window);*/
}

int main() {
  test_button();
  return 0;
}