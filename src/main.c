#include <stdlib.h>
#include <stdio.h>
#include <gui/gui.h>
#include <MLV/MLV_path.h>

int main(int argc, char **argv) {
  if (argc < 3) {
    fprintf(stderr, "Not enough argument (2 correct pathfiles required)\n");
    exit(-1);
  }
  if (argc > 3) {
    fprintf(stderr, "Too much arguments (2 correct pathfiles required)\n");
    exit(-2);
  }
  if (!(MLV_path_is_a_file(argv[1])) || !(MLV_path_is_a_file(argv[2]))) {
    fprintf(stderr, "One path is incorrect\n");
    exit(-3);
  };
  GUI *gui = gui_init(argv[1], argv[2]);
  while (mode != EXITING) {
    gui_handle_event(gui);
  }
  gui_free(gui);
  return 0;
}
