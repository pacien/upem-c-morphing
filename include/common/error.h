#ifndef UPEM_MORPHING_ERROR
#define UPEM_MORPHING_ERROR

/**
 * File: error.h
 */

/**
 * Constants: Common errors
 *
 * OUT_OF_MEMORY_ERROR - when memory cannot be allocated for the program
 */
#define OUT_OF_MEMORY_ERROR "Out of memory"

/**
 * Function: rage_quit
 * Logs the supplied error message to stderr before exiting the program with an error status code.
 *
 * Parameters:
 *   *msg - error message to log
 */
void rage_quit(const char *msg);

#endif
