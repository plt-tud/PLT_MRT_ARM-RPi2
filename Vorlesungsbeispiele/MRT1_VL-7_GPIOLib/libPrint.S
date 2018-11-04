.globl PrintHex, PrintChar
.type PrintHex, %function
.type PrintChar, %function

.include "SYSCALL.h"

.text
.balign 4
@ void PrintHex(int digit)
PrintHex:
	push {fp,lr}
	add fp,sp,#(2-1)*4

	cmp r0,#10	@ if ( r0 < 10) {
	addlt r0,r0,#'0'	@  r0 <- r0 + '0'
	addge r0,r0,#'A'	@ } else { r0 <- r0 + 'A' }
	bl PrintChar
	pop {fp,pc}

@ void PrintChar(int char)
PrintChar:
	push {r0,r7,fp,lr}
	add fp,sp,#(4-1)*4

	mov r0,#1			// r0 <- stdout
	mov r1,sp			// r1 <- sp, address of r0
	mov	r2,#1			// r2 <- 1, length
	mov r7,#SYSCALL_WRITE
	swi #0

	pop {r0,r7,fp,pc}
