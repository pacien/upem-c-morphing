#ifndef UPEM_MORPHING_CANVAS
#define UPEM_MORPHING_CANVAS

/**
 * File: canvas.h
 */

#include <MLV/MLV_image.h>
#include "common/geom.h"
#include "painter/color.h"

/**
 * Type: Canvas
 * Represents a fixed size RGBa pixel matrix.
 */
typedef struct {
  MLV_Image *mlv;
} Canvas;

/**
 * Function: canvas_create
 * Initialises a canvas of the given size
 *
 * Parameters:
 *   width  - the width in pixels
 *   height - the height in pixels
 *
 * Returns:
 *   The initialised canvas, dynamically allocated
 */
Canvas *canvas_create(IntVector width, IntVector height);

/**
 * Function: canvas_create_from_image
 * Initialises a canvas with an image loaded from the given path.
 *
 * Parameters:
 *   *fpath - path to the base image file
 *
 * Returns:
 *   The initialised canvas, dynamically allocated
 */
Canvas *canvas_create_from_image(const char *fpath);

/**
 * Function: canvas_destroy
 * Frees all memory allocated to a canvas.
 *
 * Parameters:
 *   *c - the canvas to destroy
 */
void canvas_destroy(Canvas *c);

/**
 * Function: canvas_set_pixel
 * Sets the pixel colour at the given coordinates.
 *
 * Parameters:
 *   *c    - the canvas to alter
 *   pos   - the coordinate of the pixel to set
 *   color - the new colour to set
 */
void canvas_set_pixel(Canvas *c, CartesianVector pos, Color color);

/**
 * Function: canvas_get_pixel
 * Returns the colour of the pixel at the given position.
 *
 * Parameters:
 *   *c  - the base canvas
 *   pos - the coordinate of the pixel to get
 *
 * Returns:
 *   The colour of the requested pixel
 */
Color canvas_get_pixel(Canvas *c, CartesianVector pos);

/**
 * Function: canvas_get_dim
 * Returns the size (in pixels) of the given canvas.
 *
 * Parameters:
 *   *c - the canvas
 *
 * Returns:
 *   The size of the canvas
 */
CartesianVector canvas_get_dim(Canvas *c);

#endif
