#ifndef UPEM_MORPHING_PITUREFRAME
#define UPEM_MORPHING_PITUREFRAME

#include <morpher/morphing.h>
#include <painter/canvas.h>
#include "component.h"
/**
 * File: pictureframe.h
 */

CartesianVector savedPoint;
/**
 * Type: CartesianMappingDivision
 * Type of functions needed to split CartesianMapping and keep only the CartesianVector needed, related to the type of PictureFrame involved
 */
typedef CartesianVector (*CartesianMappingDivision)(const CartesianMapping *cartesianMapping);

/**
 * Struct: PictureFrame
 * Represents a component to print pictures.
 *
 * Fields:
 *  component - inherent component management of the PictureFrame
 *  morphing - abstract coordinate transform
 *  canvas - image that will be printed
 *  cartesianMappingDivision - pointer of function that gives the role of the current PictureFrame to retrieve the right CartesianVector related to its usage
 */
typedef struct {
  Component component;
  Morphing *morphing;
  Canvas *canvas;
  CartesianMappingDivision cartesianMappingDivision;
} PictureFrame;

/**
 * Function: pictureframe_origin_split
 * Splits the CartesianMapping to get the CartesianVector related to the origin PictureFrame.
 *
 * Parameters:
 *  *cartesianMapping - CartesianMapping that contains the origin and target CartesianVector needed to be split
 */
CartesianVector pictureframe_origin_split(const CartesianMapping *cartesianMapping);

/**
 * Function: pictureframe_target_split
 * Splits the CartesianMapping to get the CartesianVector related to the target PictureFrame.
 *
 * Parameters:
 *  *cartesianMapping - CartesianMapping that contains the origin and target CartesianVector needed to be split
 */
CartesianVector pictureframe_target_split(const CartesianMapping *cartesianMapping);

bool pictureframe_is_selected(int x, int y, PictureFrame *pictureFrame);

/**
 * Function: pictureframe_conversion_to_origin
 * Returns the relative coordinate on the picture corresponding to the input values
 *
 * Parameters:
 *  x - value on x axis from the origin of the window to convert
 *  y - value on y axis from the origin of the window to convert
 *  *pictureFrame - pointer to the reference pictureframe that will give his relative coordinates
 */
CartesianVector pictureframe_conversion_to_pic(int x, int y, PictureFrame *pictureFrame);

CartesianVector pictureframe_conversion_to_origin(int x, int y, PictureFrame *pictureFrame);

void pictureframe_init(PictureFrame *pictureFrame, int width, int height, int x_pos, int y_pos,
                       CartesianMappingDivision cartesianMappingDivision, Morphing *morphing, Canvas *canvas,
                       ClickHandler clickHandler);

/**
 * Function: pictureframe_draw_canvas
 * Draws the contained Canvas of the PictureFrame.
 *
 * Parameters:
 *  *pictureFrame - current PictureFrame containing the Canvas to print.
 */
void pictureframe_draw_canvas(PictureFrame *pictureFrame);

/**
 * Function: pictureframe_print
 * Prints the PictureFrame (The Canvas involved, plus the triangles and points of the Morphing)
 *
 * Parameters:
 *  *parameterSelf - pointer that will be casted into a PictureFrame to be printed
 */
void pictureframe_print(Component *parameterSelf);

/**
 * Function: pictureframe_click_handler_origin
 * Adds a point on the coordinate of the picture that the mouse is pointing.
 *
 * Parameters:
 *  x_pos - coordinate on x axis of the mouse
 *  y_pos - coordinate on y axis of the mouse
 *  *parameterSelf - pointer that will be casted into a PictureFrame
 */
void pictureframe_click_handler_origin(int x_pos, int y_pos, Component *parameterSelf);

/**
 * Function: pictureframe_click_handler_target
 * Adds a point on the coordinate of the picture that the mouse is pointing.
 *
 * Parameters:
 *  x_pos - coordinate on x axis of the mouse
 *  y_pos - coordinate on y axis of the mouse
 *  *parameterSelf - pointer that will be casted into a PictureFrame
 */
void pictureframe_click_handler_target(int x_pos, int y_pos, Component *parameterSelf);


#endif
