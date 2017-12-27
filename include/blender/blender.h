#ifndef UPEM_MORPHING_BLENDER
#define UPEM_MORPHING_BLENDER

/**
 * File: blender.h
 * Will it blend? That is the question.
 */

#include "common/time.h"
#include "blender/canvas.h"
#include "morpher/morphing.h"

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

#endif
