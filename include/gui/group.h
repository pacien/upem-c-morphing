#ifndef UPEM_MORPHING_GROUP
#define UPEM_MORPHING_GROUP

#include "window.h"

/**
 * File: group.h
 */

typedef struct _GroupElement {
  Component *c;
  struct _GroupElement *next;
} GroupElement;

typedef struct {
  Component component;
  GroupElement *group_head;
} Group;

void group_init(Group *group, int padding);

void group_free(Group *group);

void group_add_component(Group *group, Component *component);

#endif
