#ifndef UPEM_MORPHING_GROUP
#define UPEM_MORPHING_GROUP

/**
 * File: group.h
 * Group of components
 */
#include "window.h"

/**
 * Struct: _GroupElement
 * Nod of the linked list that is involved in the Group behavior
 *
 * Parameters:
 *  *component - component
 *  *sub_component - sub component
 *  *next - link to the next nod
 */
typedef struct _GroupElement {
  Component *component;
  Component *sub_component;
  struct _GroupElement *next;
} GroupElement;

/**
 * Struct: Group
 * Group representation
 *
 * Parameters:
 *  component - Component used for the Group to catch clicks and handle print to delegate to the components contented in it
 *  *group_head - pointer to the head of the list that regroup all the components contained inside of the group
 */
typedef struct {
  Component component;
  GroupElement *group_head;
} Group;

void group_init(Group *group, int padding);

void group_free(Group *group);

void group_add_component(Group *group, Component *component);

#endif
