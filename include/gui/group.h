#ifndef UPEM_MORPHING_GROUP
#define UPEM_MORPHING_GROUP

/**
 * File: group.h
 * Group of components
 */
#include "component.h"

/**
 * Struct: _GroupElement
 * Node of the linked list that is involved in the Group behavior
 *
 * Parameters:
 *  *component - component
 *  *sub_component - sub component
 *  *next - link to the next node
 */
typedef struct _GroupElement {
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
 *  margin - margin for all components
 */
typedef struct {
  Component component;
  GroupElement *group_head;
  int margin;
} Group;

/**
 * Function: group_print
 * Print method for a group that will print all components contained in.
 *
 * Parameters:
 *  *parameterSelf - pointer that will be casted into a Group to print
 */
void group_print(Component *parameterSelf);

/**
 * Function: group_click_handler
 * Delegates the click handling to the component contained inside.
 *
 * Parameters:
 *  x_pos - position of the mouse on x axis
 *  y_pos - position of the mouse on y axis
 *  *parameterSelf - pointer that will be casted into a Group to print
 */
void group_click_handler(int x_pos, int y_pos, Component *parameterSelf);

/**
 * Function: group_init
 * Initializes fields of a Group that must be allocated before.
 *
 * Parameters:
 *  *group - group that must be initialized
 *  width - width of the current group
 *  height - height of the current group
 *  x_pos - position on the x axis from the upper left corner
 *  y_pos - position on the y axis from the upper left corner
 *  margin - space between each components
 */
void group_init(Group *group, int width, int height, int x_pos, int y_pos, int margin);

/**
 * Function: group_free
 * Frees the resources held by the group like the linked list.
 *
 * Parameters:
 *  *group - group that must be freed
 */
void group_free(Group *group);

/**
 * Function: group_add_component
 * Adds the component at the end of the chained list held by group_head.
 *
 * Parameters:
 *  *group - group in which we add the component
 *  *component - component which is added to the group
 */
void group_add_component(Group *group, Component *component);


#endif
