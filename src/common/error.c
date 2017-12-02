#include "common/error.h"
#include <stdlib.h>
#include <stdio.h>

void rage_quit(const char *msg) {
  fprintf(stderr, "FATAL ERROR: %s\n", msg);
  exit(1);
}
