#ifndef UPEM_MORPHING_CANVAS
#define UPEM_MORPHING_CANVAS

/**
 * File: canvas.h
 *
 * See also:
 *   Freedom, according to Bob Ross
 */

#include <MLV_image.h>
#include "common/geom.h"
#include "color.h"

/**
 * Type: Canvas
 * Represents a fixed size RGBa pixel matrix.
 */
typedef struct {
  MLV_Image mlv;
} Canvas;

/**
 * Function: canvas_init
 * Initialises a canvas of the given size
 *
 * Parameters:
 *   *canvas - the canvas to initialise
 *   width   - the width in pixels
 *   height  - the height in pixels
 */
void canvas_init(Canvas *canvas, IntVector width, IntVector height);

/**
 * Function: canvas_free
 * Frees all memory allocated to a canvas.
 *
 * Parameters:
 *   *canvas - the canvas to destroy
 */
void canvas_free(Canvas *canvas);

/**
 * Function: canvas_set_pixel
 * Sets the pixel colour at the given coordinates.
 *
 * Parameters:
 *   *canvas  - the canvas to alter
 *   position - the cartesian coordinates of the pixel to set
 *   color    - the new colour to set
 */
void canvas_set_pixel(Canvas *canvas, CartesianVector position, Color color);

/**
 * Function: canvas_get_pixel
 * Returns the colour of the pixel at the given position.
 *
 * Parameters:
 *   *canvas - the base canvas
 *   position - the position in cartesian coordinates
 *
 * Returns:
 *   The colour of the requested pixel
 */
Color canvas_get_pixel(Canvas *canvas, CartesianVector position);

/**
 * Function: canvas_get_size
 * Returns the size (in pixels) of the given canvas.
 *
 * Parameters:
 *   *canvas - the canvas
 *
 * Returns:
 *   The size of the canvas
 */
CartesianVector canvas_get_size(Canvas *canvas);

#endif
