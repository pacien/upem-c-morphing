#include "common/error.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * File: error.c
 *
 * Author:
 *   Pacien TRAN-GIRARD
 */

void rage_quit(const char *msg) {
  fprintf(stderr, "FATAL ERROR: %s\n", msg);
  exit(1);
}
