#include "common/mem.h"
#include <stdlib.h>
#include "common/error.h"

/**
 * File: error.c
 *
 * Author:
 *   Pacien TRAN-GIRARD
 */

void *malloc_or_die(size_t size) {
  void *ptr = malloc(size);

  if (ptr == NULL)
    rage_quit(OUT_OF_MEMORY_ERROR);

  return ptr;
}
