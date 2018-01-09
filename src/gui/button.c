#include "gui/button.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <MLV/MLV_all.h>
#include "common/mem.h"

static bool button_is_selected(int x, int y, Button *button) {
  assert(button != NULL);
  int x1 = button->component.x_pos;
  int y1 = button->component.y_pos;
  int x2 = button->component.x_pos + button->component.width;
  int y2 = button->component.y_pos + button->component.height;
  return x >= x1 && x <= x2 && y >= y1 && y <= y2;
}

static void button_print(Component *parameterSelf) {
  assert(parameterSelf != NULL);
  Button *self = (Button *) parameterSelf;
  MLV_draw_adapted_text_box(self->component.x_pos, self->component.y_pos, self->label, self->sizeInterligne,
                            MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_DARK_GREY, MLV_TEXT_CENTER);
}

void button_click_add_constraint(int x, int y, Component *parameterSelf) {
  assert(parameterSelf != NULL);
  Button *self = (Button *) parameterSelf;
  if (button_is_selected(x, y, self) && (mode == WAITING_BUTTON_SHOW || mode == WAITING_BUTTON_HIDE)) {
    mode = INSERT_ORIGIN;
  }
}

void button_click_show_hide(int x, int y, Component *parameterSelf) {
  assert(parameterSelf != NULL);
  Button *self = (Button *) parameterSelf;
  if (button_is_selected(x, y, self)) {
    if (mode == WAITING_BUTTON_SHOW) {
      mode = WAITING_BUTTON_HIDE;
    } else if (mode == WAITING_BUTTON_HIDE) {
      mode = WAITING_BUTTON_SHOW;
    }
  }
}

void button_click_exit(int x, int y, Component *parameterSelf) {
  assert(parameterSelf != NULL);
  Button *self = (Button *) parameterSelf;
  if (button_is_selected(x, y, self) && (mode == WAITING_BUTTON_SHOW || mode == WAITING_BUTTON_HIDE)) {
    mode = EXITING;
  }
}

void button_click_less_frame(int x, int y, Component *parameterSelf) {
  assert(parameterSelf != NULL);
  Button *self = (Button *) parameterSelf;
  if (button_is_selected(x, y, self) && (mode == WAITING_BUTTON_SHOW || mode == WAITING_BUTTON_HIDE)) {
    if (frame > 2) {
      frame = frame / 2;
      sprintf(labelFrame, "%03d frames", frame);
      mode = PRINTING_BUTTONS;
    }
  }
}

void button_click_more_frame(int x, int y, Component *parameterSelf) {
  assert(parameterSelf != NULL);
  Button *self = (Button *) parameterSelf;
  if (button_is_selected(x, y, self) && (mode == WAITING_BUTTON_SHOW || mode == WAITING_BUTTON_HIDE)) {
    if (frame < 256) {
      frame = frame * 2;
      sprintf(labelFrame, "%03d frames", frame);
      mode = PRINTING_BUTTONS;
    }
  }
}

void button_click_rendering(int x, int y, Component *parameterSelf) {
  assert(parameterSelf != NULL);
  Button *self = (Button *) parameterSelf;
  if (button_is_selected(x, y, self) && (mode == WAITING_BUTTON_SHOW || mode == WAITING_BUTTON_HIDE)) {
    mode = RENDERING;
  }
}

void button_click_none(int x, int y, Component *parameterSelf) {
  assert(parameterSelf != NULL);
}

Button *button_create(const char *text, int sizeInterligne, int x_pos, int y_pos, ClickHandler clickHandler) {
  assert(text != NULL);
  assert(sizeInterligne >= 0);
  assert(x_pos >= 0);
  assert(y_pos >= 0);
  Button *button = malloc_or_die(sizeof(Button));
  button->label = malloc_or_die(sizeof(char) * (strlen(text) + 1));
  strcpy(button->label, text);
  button->sizeInterligne = sizeInterligne;
  MLV_get_size_of_adapted_text_box(text, sizeInterligne, &button->component.width, &button->component.height);
  button->component.x_pos = x_pos;
  button->component.y_pos = y_pos;
  button->component.print_method = button_print;
  button->component.click_handler = clickHandler;
  return button;
}

void button_destroy(Button *button) {
  assert(button != NULL);
  free(button->label);
  free(button);
}
