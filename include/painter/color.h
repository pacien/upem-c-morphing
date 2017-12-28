#ifndef UPEM_MORPHING_COLOR
#define UPEM_MORPHING_COLOR

/**
 * File: color.h
 * > Coming, colors in the air! Oh, everywhere!
 * -- The Rolling Stones
 */

#include <MLV/MLV_color.h>
#include <stdbool.h>
#include "common/time.h"

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
    ColorComponent a, b, g, r;
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

/**
 * Function: color_blend
 * Blends two colors.
 *
 * Parameters:
 *   origin   - the first color
 *   target   - the second color
 *   distance - the distance from the first color
 *
 * Returns:
 *   The blended color
 */
Color color_blend(Color origin, Color target, TimeVector distance);

#endif
