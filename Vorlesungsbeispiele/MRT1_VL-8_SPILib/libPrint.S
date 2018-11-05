.globl PrintHex, PrintChar, PrintOct, PrintNL
.type PrintHex, %function
.type PrintChar, %function
.type PrintOct, %function
.type PrintNL, %function

.include "SYSCALL.h"

.text
.balign 4
@ void PrintOct(int nr)
PrintOct:
	push {r4,r5,fp,lr}
	add fp,sp,#(3-1)*4

	mov r5,r0
	mov r4,#30 @ for { shift=28;shift<=0;shift-=3) {
o_loop: cmp r4,#0
	blt o_done

	lsr r0,r5,r4 @ 3bit = ( nr >> shift ) & 0x7
	and r0,r0,#0x07
	add r0,r0,#'0'	@  r0 <- r0 + '0'
	bl PrintChar

	sub r4,r4,#3
	bal o_loop
o_done:
	pop {r4,r5,fp,pc}

@ void PrintHex(int nr)
PrintHex:
	push {r4,r5,fp,lr}
	add fp,sp,#(3-1)*4

	mov r5,r0
	mov r4,#28 @ for { shift=28;shift<=0;shift-=4) {
h_loop: cmp r4,#0
	blt h_done

	lsr r0,r5,r4 @ 4bit = ( nr >> shift ) & 0xF
	and r0,r0,#0x0F
	cmp r0,#10	@ if ( r0 < 10) {
	addlt r0,r0,#'0'	@  r0 <- r0 + '0'
	addge r0,r0,#('A'-10)	@ } else { r0 <- r0 - 10 + 'A' }
	bl PrintChar

	sub r4,r4,#4
	bal h_loop
h_done:
	pop {r4,r5,fp,pc}

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

@ void PrintNL()
PrintNL:
	push {fp,lr}
	add fp,sp,#(2-1)*4
	mov r0,#10
	bl PrintChar
	pop {fp,pc}
