	.data
.balign 4
var_a: .word 0x00000100
var_b: .word 0x00000010
var_x: .word 0x00000100
var_c: .word 0x00000011

.text
.balign 4
.global main
.func   main

main:
  stmfd sp!,{r4-r11,lr}
/**********************************/
// WENN ( A < B) DANN … SONST WENN ( A == C+1) … SONST …
	ldr r0, =a		@ load pointer to a
	ldr r0, [r0]		@ load value of a
	ldr r1, =b		@ load pointer to b
	ldr r1, [r1]		@ load value of b
	cmp r0, r1		@ compare a and b
	bge case_a_eq_b
case_a_lt_b:	mov r0, #1		@ IF section: load 1 into r0
	b case_done 		@ skip unconditionally
case_a_eq_cp: 	ldr r1, =c		@ load pointer to c
	ldr r1, [r1]		@ load value of c
	add r1,r1,#1 		@ C+1
	cmp r0, r1		@ compare a and b
	bne case_default
	mov r0, #2
	b case_done 	 	@ skip unconditionally
case_default:	mov r0, #0		@ Default section: load 0 into r0

case_done:	ldr r1, =x		@ load pointer to x
	str r0, [r1]		@ store r0 in x
