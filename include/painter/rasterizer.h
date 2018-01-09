#ifndef UPEM_MORPHING_RASTERIZER
#define UPEM_MORPHING_RASTERIZER

/**
 * File: rasterizer.h
 * > Everyday is a good day when you paint.
 * -- Bob Ross
 *
 * Author:
 *   Pacien TRAN-GIRARD
 */

#include "painter/canvas.h"
#include "morpher/morphing.h"

/**
 * Struct: RasterizationContext
 */
typedef struct {
  Canvas *result, *source, *target;
  TimeVector frame;
} RasterizationContext;

/**
 * Struct: TriangleContext
 */
typedef struct {
  Triangle current, source, target;
} TriangleContext;

/**
 * Function: rasterize
 * Rasterises a morphing from a source and a target image at the given time frame.
 *
 * Parameters:
 *   *source - source image canvas
 *   *target - target image canvas
 *   *m      - reference morphing
 *   frame   - time frame
 *
 * Returns:
 *   The drawn canvas, dynamically allocated
 */
Canvas *rasterize(Canvas *source, Canvas *target, Morphing *m, TimeVector frame);

#endif
