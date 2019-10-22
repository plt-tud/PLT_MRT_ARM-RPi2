/*
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
 *  @brief: Kleines Vorlesungsbeispiel zur Demonstration der VL-Inhalte:
 *          - MOV, LDR, STR
 *          - Konditionale ausfuehrung und branch
 *          - Abschnitte einer Assembler-datei
 *          - labels
 */
		.data
		.balign 4
countD: .word 0x000010

		.text
		.func main
		.globl main
		.balign 4		    // instructions must be word-alignd
main:
		stmfd sp!,{lr}  	@ safe return address (as prepared by linux)
main_loop_start:
		mov r0, #0
		ldr r1, countD_addr // load our repetition count; this is a single-step form of
		ldr r10, [r1]     	@   what ldr r10,=countD would do
		sub r10, r10, #1    // decrement our counter variable
		cmp r0, r10
		str r10, [r1] 	    // persist our repetition count
		beq main_loop_end
		/* Hier koennte Ihr Code stehe */
		b   main_loop_start
main_loop_end:
		ldmfd sp!,{pc} 		@ pop return address to pc
		.endfunc

countD_addr: .word countD
