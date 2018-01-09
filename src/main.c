#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <MLV/MLV_path.h>
#include "gui/gui.h"

/**
 * File: main.c
 *
 * Author:
 *   Adam NAILI
 */

static inline void print_help() {
  printf("Usage: morph [--help] <path to base image> <path to end image>\n\n"
          "To use the morphing, you need to put two correct paths to image files.\n\n"
          "Accepted input imaege formats are: ICO, CUR, BMP, PNM, XPM, LBM, PCX, GIF, JPEG, PNG, TGA, TIFF, and XV.\n\n"
          "Project made by: Pacien TRAN-GIRARD and Adam NAILI\n");
}

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
    print_help();
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
