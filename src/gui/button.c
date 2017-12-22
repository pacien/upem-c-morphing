#include <gui/button.h>
#include <stdlib.h>
#include <assert.h>
#include <common/mem.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include <gui/component.h>


bool button_is_selected(int x, int y, Button *button) {
  assert(x >= 0);
  assert(y >= 0);
  assert(button != NULL);
  int x1 = button->component.x_pos;
  int y1 = button->component.y_pos;
  int x2 = button->component.x_pos + button->component.width;
  int y2 = button->component.y_pos + button->component.height;
  if (x >= x1 && x <= x2 && y >= y1 && y <= y2) {
    return true;
  }
  return false;
}

void button_print(Component *parameterSelf) {
  assert(parameterSelf != NULL);
  Button *self = (Button *) parameterSelf;
  MLV_draw_adapted_text_box(self->component.x_pos, self->component.y_pos, self->label, self->sizeInterligne,
                            MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_DARK_GREY, MLV_TEXT_CENTER);
}

void button_click_test(int x, int y, Component *parameterSelf) {
  assert(x >= 0);
  assert(y >= 0);
  assert(parameterSelf != NULL);
  Button *self = (Button *) parameterSelf;
  if (button_is_selected(x, y, self)) {
    printf("OK\n");
  }
}

void
button_init(Button *button, const char *text, int sizeInterligne, int x_pos, int y_pos, ClickHandler clickHandler) {
  assert(button != NULL);
  assert(text != NULL);
  assert(sizeInterligne >= 0);
  assert(x_pos >= 0);
  assert(y_pos >= 0);
  button->label = malloc_or_die(sizeof(char) * (strlen(text) + 1));
  strcpy(button->label, text);
  button->sizeInterligne = sizeInterligne;
  MLV_get_size_of_adapted_text_box(text, sizeInterligne, &button->component.width, &button->component.height);
  button->component.x_pos = x_pos;
  button->component.y_pos = y_pos;
  button->component.print_method = button_print;
  button->component.click_handler = clickHandler;
}
