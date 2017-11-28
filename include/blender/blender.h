#ifndef UPEM_MORPHING_BLENDER
#define UPEM_MORPHING_BLENDER

/**
 * File: blender.h
 * Will it blend? That is the question.
 */

#include "common/time.h"
#include "blender/canvas.h"
#include "blender/color.h"
#include "morpher/morpher.h"

/**
 * Function: blender_blend_canvas
 * Blends two canvas by applying the given morphing at the requested time frame.
 *
 * Parameters:
 *   *canvas   - pointer to the canvas to paint
 *   *source   - source image
 *   *target   - target image
 *   *morphing - morphing transform to apply
 *   frame     - the interpolation distance from the origin canvas [0;1]
 */
void blender_blend_canvas(Canvas *canvas, Canvas *source, Canvas *target, Morphing *morphing, TimeVector frame);

/**
 * Function: blender_blend_colors
 * Properly blends two coloured pixels, interpolated at the given time frame.
 * (https://www.youtube.com/watch?v=LKnqECcg6Gw)
 *
 * Parameters:
 *   origin - the origin colour
 *   target - the target colour
 *   frame  - the interpolation distance from the origin colour [0;1]
 *
 * Returns:
 *   The blended coloured pixel
 */
Color blender_blend_colors(Color origin, Color target, TimeVector frame);

#endif
