#ifndef UPEM_MORPHING_COLOR
#define UPEM_MORPHING_COLOR

/**
 * File: color.h
 *
 * See also:
 *   A rainbow
 */

#include <MLV/MLV_color.h>
#include <stdbool.h>

/**
 * Type: ColorComponent
 * Represents a single colour component of 32-bits RGBa tuple.
 */
typedef uint8_t ColorComponent;

/**
 * Type: ColorPixel
 * Represents a single RGBa coloured pixel.
 * Compatible with the libMLV representation.
 */
typedef union {
  struct {
    ColorComponent r, g, b, a;
  } rgba;

  MLV_Color mlv;
} Color;

/**
 * Function: color_equals
 * Compares the supplied colors.
 *
 * Parameters:
 *   c1 - the first color
 *   c2 - the second color
 *
 * Returns:
 *   T(c1 is the same color as c2)
 */
bool color_equals(Color c1, Color c2);

#endif
