/*
 * linked_lists.h
 *
 *  Created on: 18.11.2019
 *      Author: mrt
 */

#ifndef LINKED_LISTS_H_
#define LINKED_LISTS_H_

typedef struct list_el_t {
	struct list_el_t *next; // nächstes Element
	void *payload;
} list_element;

typedef struct liste_t {
	list_element *head; // Kopf der Liste
	list_element *tail; // Ende der Liste
} list_header;

// Dynamische Datenstrukturfunktionen
list_element* list_element_new();
void          list_element_init(list_element* el);
void          list_element_deleteMembers(list_element* el);
void          list_element_delet(list_element* el);


void listelement_append(list_header *l, list_element *el, void* payload);
void listelement_delete(list_header *l, list_element *el);


#endif /* LINKED_LISTS_H_ */
