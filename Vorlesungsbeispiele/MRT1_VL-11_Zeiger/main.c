/*
 * main.c
 *
 *  Created on: 18.11.2019
 *      Author: mrt
 */

#include <stddef.h>

int global_var;

int callstack(int data_A)
{
	int a;

	a=global_var+data_A;

	return a;
}

void strukturen(void)
{
	struct bauteil {
	 	long number;
	 	char type;
	 	double value;
	};

	struct bauteil bt1 = { 1, 'R', 100 };

	struct bauteil bt[4] = {{1,'R',100}, {2,'C',90}, {3,'C',0.9 }, {4,'R',1000}};
	bt[3].number = 5;
	bt[3].type = 'R' ;
	bt[3].value = 200 ;

	bt1 = bt[2];

	struct bauteil *bt_ptr;

	(*bt_ptr).type = 'V';
	bt_ptr->type = 'V';

	return;
}

void bitfelder(void)
{
	struct einRegister {
		unsigned an         : 1;
		unsigned fifo_full  : 1;
		unsigned fifo_empty : 1;
		unsigned reserved   : 5;
	} reg;

	reg.an 		 = 1;
	reg.reserved = 0;

	return;
}

void enums(void)
{
	enum wochentag {MO, DI, MI, DO, FR, SA, SO=0};

	enum wochentag heute = 0;
	heute = MO;

	if (heute == MO || heute == MI) {
		// Mikrorechentechnik…
	}

	return;
}

void pointerBasics(void)
{
	int a = 42;
	int b = 21;

	int *a_ptr = NULL;
	*a_ptr = 42;

	a_ptr = &b;
	*(a_ptr) /= 2;

	return;

}

void zeigerAufFelder(void)
{

	return;
}

void stringsStuff(void)
{
	char *s    = "ABCD";    // String als Pointer auf 0-terminierte Ascii-Folge
	char s1[7] = "ABCD"; // OK, Compiler versteht die Absicht
	char s2[]  = "hallo"; // OK, Compiler legt Feldlänge fest
	char *s3   = NULL;    // unintialisierter Pointer!!

	s3 = s;           // Pointer darf zugewiesen werden
	s3 = &s1[0];	  // Auch OK
	s3 = s1; 	      // Auch OK
	s3 = "neu";	      //  Fehler ! Speicher für Strings nicht dynamisch alloziierbar!
	s3[3] = 'c';	  // Veränderung eines Feldelements, entspricht *(& s1[3] ) = 99

	return;
}

#include "linked_lists.h"
void linkedListExample()
{
	list_header listhead = {NULL, NULL};

	// 100 statische elemente... wir wissen noch nicht, wie das dynamisch geht...
	list_element elements[100] = {{NULL, NULL}};

	// ein Paar statische Datentypen als Payload
	int payloadData[] = {0,1,2,3,4,5,6,7,8,9};

	for (int i=0; i<10; i++) {
		listelement_append(&listhead, &elements[i], &payloadData[i]);
	}

	while(listhead.head != NULL) listelement_delete(&listhead, listhead.head);
	return;
}

int  main(int argc, char **argv)
{
	int retval = callstack(42);

	for(int argn=0; argn<argc && argv[argn]!=NULL; argn++)
	{
		// Process arf
	}

	linkedListExample();

	return 0;
}
