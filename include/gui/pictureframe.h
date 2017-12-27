#ifndef UPEM_MORPHING_PITUREFRAME
#define UPEM_MORPHING_PITUREFRAME

#include <blender/canvas.h>
#include <morpher/morphing.h>

/**
 * File: pictureframe.h
 */
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

void pictureframe_init(PictureFrame *pictureFrame, int width, int height, int x_pos, int y_pos, CartesianMappingDivision cartesianMappingDivision);

void pictureframe_free(PictureFrame *pictureFrame);

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
 * Function: pictureframe_click_handler
 * Adds a point on the coordinate of the picture that the mouse is pointing.
 *
 * Parameters:
 *  x_pos - coordinate on x axis of the mouse
 *  y_pos - coordinate on y axis of the mouse
 *  *parameterSelf - pointer that will be casted into a PictureFrame
 */
void pictureframe_click_handler(int x_pos, int y_pos, Component *parameterSelf);


#endif
