#ifndef UPEM_MORPHING_GROUP
#define UPEM_MORPHING_GROUP

/**
 * File: group.h
 */

typedef struct {
  Component component;
  Component *sub_components;
} Group;

void group_init(Group *group, int padding);

void group_free(Group *group);

void group_add_component(Group *group, Component *component);

#endif
