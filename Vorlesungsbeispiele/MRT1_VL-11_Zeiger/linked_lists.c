/*
 * linked_lists.c
 *
 *  Created on: 18.11.2019
 *      Author: mrt
 */

#include <stddef.h>
#include "linked_lists.h"

list_element* list_element_new()
{
	list_element* new = (list_element*) malloc(sizeof(list_element));
	list_element_init(new);
	return new;
}

void list_element_init(list_element* el)
{
	if (el == NULL) return;

	el->next    = NULL;
	el->payload = NULL;

	return;
}

void list_element_deleteMembers(list_element* el)
{
	if (el == NULL) return;

	el->next    = NULL;
	el->payload = NULL;

	return;
}

void list_element_delete(list_element* el)
{
	if (el == NULL) return;

	list_element_deleteMembers(el);
	free(el);
	el = NULL;

	return;
}


void listelement_append(list_header *l, list_element *el, void* payload)
{
	if (l == NULL)  return;
	if (el == NULL) return;

	el->payload = payload;

	(l->tail)->next = el;
	l->tail = el;

	if (l->head == NULL) l->head = l->tail;
	return;
}

void listelement_delete(list_header *l, list_element *el)
{
	if (l == NULL)  return;
	if (el == NULL) return;

	list_element *it   = l->head;
	list_element *prev = NULL;
	while (it != el && it != NULL) {
		prev = el;
		el = el->next;
	}
	if (it == NULL) return; // el not found

	if (it == l->head) {
		l->head = it->next;
	}
	else if (it == l-> tail) {
		if (prev==NULL) {
			l->tail = NULL;
			l->head = NULL;
		}
		else {
			l->tail = prev;
			prev->next=NULL;
		}
	}
	else {
		prev->next = it->next;
	}
	list_element_deleteMembers(it);

	return;
}
