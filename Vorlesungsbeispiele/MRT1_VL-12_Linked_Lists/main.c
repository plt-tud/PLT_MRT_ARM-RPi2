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


/**
 *  @brief: Fuellt lineare Listen mit integern und lehrt die Liste wieder.
 *
 *  linkedListExample_static:
 *  Dient als Beispiel fuer den Umgang mit Zeigern und Datenstrukturen
 *
 *  linkedListExample_dynamic:
 *  Dient als Beispiel fuer den Umgang mit dynamischen Datenstrukturen
 *
 */

#include <stddef.h>
#include <stdlib.h>
#include "linked_lists.h"

static void linkedListExample_static()
{
	list_header listhead = {NULL, NULL};

	// 100 statische elemente... wir wissen noch nicht, wie das dynamisch geht...
	list_element elements[100] = {{NULL, NULL}};

	// ein Paar statische Datentypen als Payload
	int payloadData[] = {0,1,2,3,4,5,6,7,8,9};

	// Statische Werte einfuegen ...
	for (int i=0; i<10; i++) {
		listelement_append(&listhead, &elements[i], &payloadData[i]);
	}

	// ... und wieder loeschen.
	while(listhead.head != NULL) {
		listelement_delete(&listhead, listhead.head, false);
	}
	return;
}

static void linkedListExample_dynamic()
{
	list_header listhead = {NULL, NULL};

	// Statische Werte einfuegen ...
	for (int i=0; i<10; i++) {
		int *payloadInt = (int *) malloc(sizeof(int));
		*payloadInt = i;
		listelement_append(&listhead,
							list_element_new(),
							payloadInt);
		printf("Added %i to list\n", *payloadInt);
	}

	list_clear(&listhead);
	return;
}

int  main(int argc, char **argv)
{
	linkedListExample_static();
	linkedListExample_dynamic();
	return 0;
}
