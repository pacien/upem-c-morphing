#ifndef UPEM_MORPHING_PITUREFRAME
#define UPEM_MORPHING_PITUREFRAME

#include <blender/canvas.h>

/**
 * File: pictureframe.h
 */

typedef struct {
  Component component;
} PictureFrame;

void pictureframe_init(PictureFrame *pictureFrame, int length);

void pictureframe_free(PictureFrame *pictureFrame);

void pictureframe_draw_canvas(PictureFrame *pictureFrame, Canvas *canvas);

void pictureframe_draw_triangulation(PictureFrame *pictureFrame, void *triangulation);

void pictureframe_draw_point(PictureFrame *pictureFrame, int x_pos, int y_pos);

#endif
