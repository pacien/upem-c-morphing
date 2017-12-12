#include <gui/group.h>
#include <gui/window.h>
#include "MLV/MLV_all.h"


static void test_group() {
  Window window;
  window_init(&window, 1000, 512, "Coucou");
  window_create(&window);
  window.group_buttons->component.print_method(window.group_pictureframe);
  MLV_wait_seconds(5);
  window_free(&window);
}

int main() {
  test_group();
  return 0;
}