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

#ifndef HAVE_LINKED_LIST_H
#define HAVE_LINKED_LIST_H

#include <stdbool.h>
#include "linked_list_element.h"

typedef struct liste_t {
	linked_list_element *head; // Kopf der Liste
	linked_list_element *tail; // Ende der Liste
} linked_list_head;

typedef linked_list_head linked_list;

// Konstruktoren und Destruktoren fuer Dynamische Datenstrukturfunktionen
linked_list*  linked_list_new();
void          linked_list_init(linked_list* el);
void          linked_list_deleteMembers(linked_list* el);
void          linked_list_delete(linked_list* el);

// Bedien-Funktionen
void linked_list_appendElement(linked_list *l, linked_list_element *el, void* payload);
void linked_list_deleteElement(linked_list *l, linked_list_element *el);
void linked_list_clear(linked_list_head *l);

#endif /* HAVE_LINKED_LIST_H */
