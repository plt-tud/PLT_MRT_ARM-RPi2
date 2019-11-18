/*
 * Copyright (c) 2019 Chris Iatrou <chris_paul.iatrou@tu-dresden.de>
 *
 * Hiermit wird unentgeltlich jeder Person, die eine Kopie der
 * Software und der zugehörigen Dokumentationen (die "Software")
 * erhält, die Erlaubnis erteilt, sie uneingeschränkt zu nutzen,
 * inklusive und ohne Ausnahme mit dem Recht, sie zu verwenden,
 * zu kopieren, zu verändern, zusammenzufügen, zu veröffentlichen,
 * zu verbreiten, zu unterlizenzieren und/oder zu verkaufen, und
 * Personen, denen diese Software überlassen wird, diese Rechte
 * zu verschaffen, unter den folgenden Bedingungen:
 *
 * Der obige Urheberrechtsvermerk und dieser Erlaubnisvermerk
 * sind in allen Kopien oder Teilkopien der Software beizulegen.
 *
 * DIE SOFTWARE WIRD OHNE JEDE AUSDRÜCKLICHE ODER IMPLIZIERTE
 * GARANTIE BEREITGESTELLT, EINSCHLIEẞLICH DER GARANTIE ZUR
 * BENUTZUNG FÜR DEN VORGESEHENEN ODER EINEM BESTIMMTEN ZWECK
 * SOWIE JEGLICHER RECHTSVERLETZUNG, JEDOCH NICHT DARAUF
 * BESCHRÄNKT. IN KEINEM FALL SIND DIE AUTOREN ODER
 * COPYRIGHTINHABER FÜR JEGLICHEN SCHADEN ODER SONSTIGE
 * ANSPRÜCHE HAFTBAR ZU MACHEN, OB INFOLGE DER ERFÜLLUNG EINES
 * VERTRAGES, EINES DELIKTES ODER ANDERS IM ZUSAMMENHANG MIT
 * DER SOFTWARE ODER SONSTIGER VERWENDUNG DER SOFTWARE ENTSTANDEN.
 */

#include <stddef.h>
#include <stdlib.h>
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

void list_element_deleteMembers(list_element* el, _Bool freePayload)
{
	if (el == NULL) return;

	if (freePayload==true && el->payload != NULL ){
		free(el->payload );
	}

	el->payload = NULL;
	el->next    = NULL;

	return;
}

void list_element_delete(list_element* el, _Bool freePayload)
{
	if (el == NULL) return;

	list_element_deleteMembers(el, freePayload);
	free(el);
	el = NULL;

	return;
}


void listelement_append(list_header *l, list_element *el, void* payload)
{
	if (l == NULL)  return;
	if (el == NULL) return;

	el->payload = payload;

	if (l->tail != NULL)
		(l->tail)->next = el;
	l->tail = el;

	if (l->head == NULL) l->head = l->tail;
	return;
}

void listelement_delete(list_header *l, list_element *el, _Bool freePayload)
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


	if (it == l-> tail) {
		if (prev==NULL) {
			l->tail = NULL;
			l->head = NULL;
		}
		else {
			l->tail = prev;
			prev->next=NULL;
		}
	}
	else  if (it == l->head) {
		l->head = it->next;
	}
	else {
		prev->next = it->next;
	}

	list_element_deleteMembers(it, freePayload);

	return;
}


void list_clear(list_header *l)
{
	if (l == NULL)  return;
	while (l->head != NULL)
		listelement_delete(l, l->head, true);

	l->tail = NULL;

	return;
}
