#ifndef UPEM_MORPHING_MEM
#define UPEM_MORPHING_MEM

/**
 * File: mem.h
 */

#include <stddef.h>

/**
 * Function: malloc_or_die
 * Allocates a memory chunk of the requested size.
 * Interrupts the execution of the program in case of an error.
 *
 * Parameters:
 *   size - size of the chunk to allocate
 *
 * Returns:
 *   A non-NULL pointer to the allocated chunk
 */
void *malloc_or_die(size_t size);

#endif
