#ifndef UPEM_MORPHING_COLOR
#define UPEM_MORPHING_COLOR

/**
 * File: color.h
 *
 * See also:
 *   A rainbow
 */

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
  ColorComponent r, g, b, a;
  MLV_Color mlv;
} Color;

#endif
