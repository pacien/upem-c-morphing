#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <MLV/MLV_path.h>
#include "gui/gui.h"

int main(int argc, char **argv) {
  int opt = 0;
  int help = -1;
  static struct option long_options[] = {
   {"help", 0, 0, 'h'},
   {0,      0, 0, 0}
  };
  int long_index = 0;
  /*Option handling*/
  while ((opt = getopt_long_only(argc, argv, "h", long_options, &long_index)) != -1) {
    switch (opt) {
      case 'h':
        help = 0;
        break;
      default:
        exit(EXIT_FAILURE);
    }
  }
  if (help == 0) {
    printf(
     "--Morphing's Help--\nTo use the morphing, you need to put two correct paths to image files.\n\nCorrect image format :\nICO(Icon)/CUR(Cursor)/BMP, PNM (PPM/PGM/PBM), XPM, LBM(IFF ILBM), PCX, GIF, JPEG, PNG, TGA, TIFF, and XV.\n\nMorphing made by:\n Pacien TRAN-GIRARD and Adam NAILI\n");
  } else {
    int nbArg = argc - optind;
    if (nbArg < 2) {
      fprintf(stderr, "Not enough argument (2 correct pathfiles required)\n");
      exit(-1);
    }
    if (nbArg > 2) {
      fprintf(stderr, "Too much arguments (2 correct pathfiles required)\n");
      exit(-2);
    }
    if (!(MLV_path_is_a_file(argv[optind])) || !(MLV_path_is_a_file(argv[optind + 1]))) {
      fprintf(stderr, "One path is incorrect\n");
      exit(-3);
    };
    GUI *gui = gui_create(argv[optind], argv[optind + 1]);
    while (mode != EXITING) {
      gui_handle_event(gui);
    }
    gui_destroy(gui);
  }
  exit(EXIT_SUCCESS);
}
