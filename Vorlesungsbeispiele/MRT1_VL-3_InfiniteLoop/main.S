/*
 * main.S
 *
 *  Created on: Oct 14, 2020
 *      Author: zohra
 */

	.data
.balign 4
msg: .asciz "Hello, MRT"

.text
.balign 4
.global main
.func   main

main:

  ldr r0, =msg		// load pointer to string
loop:	bl puts		// put string at address r0 to console
	b loop			// repeat loop unconditionally

.endfunc
