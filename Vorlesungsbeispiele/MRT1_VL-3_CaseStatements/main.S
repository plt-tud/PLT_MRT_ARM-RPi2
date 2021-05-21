/**
 * Demonstrates multiple if clauses that act as case statements.
 */


.data
.balign 4

var_a: .word 0x00000011		// A = 17
var_b: .word 0x00000001		// B = 1
var_x: .word 0x00000100		// X = 256
var_c: .word 0x0000000F		// C = 15

.text
.balign 4
.global main
.func   main

main:
  stmfd sp!,{r0-r4,lr}
/**********************************/
/*
	IF ( A < B) THEN
		X = 1
	ELSE IF ( A == C+2)
		X = 2
	ELSE
		X = 0
*/
	ldr r0, =var_a				// load pointer to a
	ldr r0, [r0]				// load value of a

	ldr r1, =var_b				// load pointer to b
	ldr r1, [r1]				// load value of b

	cmp r0, r1					// compare a and b
	bge case_a_eq_cp			// if a >= b jump to case_a_eq_cp	(ge - greater than or equal)
case_a_lt_b:
	mov r0, #1					// load 1 into r0
	b case_done 				// skip unconditionally
case_a_eq_cp:
	ldr r1, =var_c				// load pointer to c
	ldr r1, [r1]				// load value of c

	add r1,r1,#2 				// c = c+2

	cmp r0, r1					// compare a and c+2
	bne case_default			// if a != b jump to case_default	(ne - not equal)

	mov r0, #2					// load 2 into r0

	b case_done 	 			// skip unconditionally
case_default:
	mov r0, #0					// load 0 into r0

case_done:
	ldr r1, =var_x				// load pointer to x
	str r0, [r1]				// store r0 in x

	ldmfd sp!,{r0-r4,lr}
  	bx lr
.endfunc

