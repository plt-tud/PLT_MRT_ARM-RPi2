/*
 * Copyright (c) 2017 Chris Iatrou <chris_paul.iatrou@tu-dresden.de>
 * Copyright (c) 2018 Leon Urbas <leon.urbas@tu-dresden.de>
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
 *  @brief: Kopiere einen Block aus 8 32bit Datenwerten aus einem .data-wert in einen anderen
 *
 * Das Program demonstriert die Nutzung von Load/Store-multiple sowie die Nutzung des Stacks
 */

//
// Toolchain Setting:
//	Cross GCC Assembler: -adhlns="$//.lst"

.data			        	 	// directive .data tells the assembler to open a Data Section
.balign 4 		     			// data shall be word aligned (makes it faster)

source:            				// This label defines the name of the variable
	.word 0x2F534350 			// directive .word reserves 4 bytes (i.e. a word) and initializes it to some value
	.word 0x20455350			// all subsequently reserved bytes are stored subsequently in memory
	.word 0x20445554
	.word 0x3154524D
	.word 0x32303220
	.word 0x52412030
	.word 0x2037564D
	.word 0x004D5341
dest:			      			// a new variable begins
	.skip 32	   			 	// reserves 32 bytes of free space without explicitly defined content

.text			      			// directive .text tells the assembler to begin the Code Section
.balign 4		    			// instructions must be word-alignd

.global main	  				// directive .global exports the symbol for the linker

.func main		  				// directive .func helps the debugger
main:
	stmfd sp!,{r0-r9,lr} 		// save r0-r9,lr on the stack
								// stmfd will store data at current stack pointer, which is stored in sp
								// sp will be decremented before each data transfer (fd - full descending stack)
								// suffix ! will write back the final memory address to sp

	ldr r8,=source	  	 		// r8 <- adresse von source
	ldr r9,=dest     	   		// r9 <- adresse von ziel

	ldmia r8,{r0-r7} 	   		// copy data from memory starting at address in r8 to registers r0 to r7
								// ldmia increments address after each tranfser (ia - increment after)
	stmia r9,{r0-r7} 	   		// copy data from registers r0 to r7 to memory starting at address in r8
								// stmia increments address after each tranfser (ia - increment after)

	ldmfd sp!,{r0-r9,lr} 		// restore r0-r9 from the stack

	ldr r0, =0					// r0 <- #0
	bx lr				    	// return from subroutine
.endfunc		      			// directive .endfunc helps debugger
