/* Intrusive circular doubly linked list. This is similar to the `list_head`
 * construct used in the Linux kernel, although very slimmed down for the sake
 * of simplicity. */
#pragma once

#include "prelude.h"

typedef struct List_Node List_Node;

struct List_Node {
	List_Node* next;
	List_Node* prev;
};

// Add list value after target
void list_add(List_Node* target, List_Node* new_node);

// Delete value from list by redirecting its neighbors
void list_add(List_Node* target, List_Node* new_node);

// Initialize node to be head of list
static inline
void list_init(List_Node* target){
	target->next = target;
	target->prev = target;
}

// Get pointer of structure containing the list
#define list_entry(Ptr, Type, Member) container_of(Ptr, Type, Member)

#define list_foreach(IterVar, ListHead) \
	for(List_Node* IterVar = ListHead.next; IterVar != &ListHead; IterVar = IterVar->next)

#define list_foreach_reversed(IterVar, ListHead) \
	for(List_Node* IterVar = ListHead.prev; IterVar != &ListHead; IterVar = IterVar->prev)

