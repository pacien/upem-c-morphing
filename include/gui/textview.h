#ifndef UPEM_MORPHING_TEXTVIEW
#define UPEM_MORPHING_TEXTVIEW

/**
 * File: textview.h
 */

typedef struct {
  Component component;
  int length;
  char *text;
} TextView;

void textview_init(TextView *textview, int length);

void textview_free(TextView *textview);

void textview_set_text(TextView *textView, char *text);

#endif
