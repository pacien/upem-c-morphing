#include <stdlib.h>
#include <gui/group.h>

void group_init(Group *group, int width, int height, int x_pos, int y_pos, int padding) {
  group->component.width = width;
  group->component.height = height;
  group->component.x_pos = x_pos;
  group->component.y_pos = y_pos;
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

}