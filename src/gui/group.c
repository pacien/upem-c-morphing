#include <stdlib.h>
#include <gui/group.h>
#include <common/mem.h>
#include <assert.h>
#include <gui/component.h>
#include "MLV/MLV_shape.h"
#include "MLV/MLV_window.h"

void group_print(Component *parameterSelf) {
  assert(parameterSelf != NULL);
  Group *self = (Group *) parameterSelf;
  if (self->group_head != NULL) {
    GroupElement *p = self->group_head;
    while (p != NULL) {
      p->sub_component->print_method(p->sub_component);
      p = p->next;
    }
  }
}

void group_click_handler(int x_pos, int y_pos, Component *parameterSelf) {
  assert(parameterSelf != NULL);
  Group *self = (Group *) parameterSelf;
  if (self->group_head != NULL) {
    GroupElement *p = self->group_head;
    while (p != NULL) {
      p->sub_component->click_handler(x_pos, y_pos, p->sub_component);
      p = p->next;
    }
  }
}

void group_init(Group *group, int width, int height, int x_pos, int y_pos, int margin) {
  assert(group != NULL);
  assert(width > 0);
  assert(height > 0);
  assert(x_pos >= 0);
  assert(y_pos >= 0);
  assert(margin >= 0);
  group->component.width = width;
  group->component.height = height;
  group->component.x_pos = x_pos;
  group->component.y_pos = y_pos;
  group->component.print_method = group_print;
  group->component.click_handler = group_click_handler;
  group->margin = margin;
}

void group_free(Group *group) {
  assert(group != NULL);
  if (group->group_head != NULL) {
    GroupElement *p = group->group_head;
    while (p != NULL) {
      GroupElement *tmp = p;
      p = p->next;
      free(tmp);
    }
    group->group_head = NULL;
  }
}

void group_add_component(Group *group, Component *component) {
  assert(group != NULL);
  assert(component != NULL);
  /*Initialize the new node*/
  GroupElement *tmp = malloc_or_die(sizeof(GroupElement));
  tmp->sub_component = component;
  tmp->next = NULL;
  if (group->group_head != NULL) {
    GroupElement *p = group->group_head;
    /*Browsing*/
    while (p->next != NULL) {
      p = p->next;
    }
    p->next = tmp;
    /*Modifying for margin*/
    tmp->sub_component->y_pos = p->sub_component->y_pos;
    tmp->sub_component->x_pos = p->sub_component->x_pos + p->sub_component->width + group->margin;
  } else {
    tmp->sub_component->y_pos = group->component.y_pos;
    tmp->sub_component->x_pos = group->component.x_pos;
    group->group_head = tmp;

  }
}

