#include <stdlib.h>
#include <gui/group.h>
#include <common/mem.h>
#include <assert.h>
#include "MLV/MLV_shape.h"
#include "MLV/MLV_window.h"

void group_print(void *parameter) {
  Group *group = (Group *) parameter;
  /*DEBUG*/
  MLV_draw_filled_rectangle(group->component.x_pos, group->component.y_pos, group->component.width,
                            group->component.height, MLV_COLOR_AQUAMARINE);
  /**/
  MLV_actualise_window();
}

void group_init(Group *group, int width, int height, int x_pos, int y_pos, int padding) {
  assert(group != NULL);
  assert(width > 0);
  assert(height > 0);
  assert(x_pos >= 0);
  assert(y_pos >= 0);
  assert(padding >= 0);
  group->component.width = width;
  group->component.height = height;
  group->component.x_pos = x_pos;
  group->component.y_pos = y_pos;
  group->component.print_method = group_print;
  group->padding = padding;
}

void group_free(Group *group) {
  if (group->group_head != NULL) {
    GroupElement *p = group->group_head;
    while (p->next != NULL) {
      GroupElement *tmp = group->group_head;
      p = p->next;
      free(tmp);
    }
    group->group_head = NULL;
  }
}

void group_add_component(Group *group, Component *component) {
  if (group->group_head != NULL) {
    /*Initialize the new node*/
    GroupElement *tmp = malloc_or_die(sizeof(GroupElement));
    tmp->sub_component = component;
    tmp->next = NULL;
    GroupElement *p = group->group_head;
    /*Browsing*/
    while (p->next != NULL) {
      p = p->next;
    }
    p->next = tmp;
  } else {
    group->group_head = malloc_or_die(sizeof(GroupElement));
    group->group_head->sub_component = component;
    group->group_head->next = NULL;
  }
}