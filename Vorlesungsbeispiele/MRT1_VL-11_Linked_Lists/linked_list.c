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

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "linked_list.h"
#include "linked_list_element.h"

linked_list*  linked_list_new()
{
	linked_list *n = (linked_list *) malloc(sizeof(linked_list)) ;
	linked_list_init(n);
	return n;
}

void linked_list_init(linked_list* el)
{
	if (el == NULL) return;
	el->head = NULL;
	el->tail = NULL;
	return;
}

void linked_list_deleteMembers(linked_list* l)
{
	if (l == NULL)  return;

	l->head = NULL;
	l->tail = NULL;

	return;
}

void linked_list_delete(linked_list* l)
{
	if (l == NULL)  return;

	linked_list_deleteMembers(l);
	free(l);
	l=NULL;

	return;
}


void linked_list_appendElement(linked_list_head *l, linked_list_element *el, void* payload)
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

void linked_list_deleteElement(linked_list_head *l, linked_list_element *el)
{
	if (l == NULL)  return;
	if (el == NULL) return;

	linked_list_element *it   = l->head;
	linked_list_element *prev = NULL;
	while (it != el && it != NULL) {
		prev = it;
		it = it->next;
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

	return;
}


void linked_list_clear(linked_list_head *l)
{
	linked_list_deleteMembers(l);
}
