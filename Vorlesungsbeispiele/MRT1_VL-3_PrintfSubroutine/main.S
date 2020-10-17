.global main, printf
.type main, %function

.data
fmt:	.asciz "asciz %s: a=%x, l=%d, c=%c, s=<%s>\n"
name:	.asciz "msg"
msg:	.asciz "Hallo MRT-1"

.set len, . - msg

.text
.align 4

main:
  //Calling printf
    stmfd sp!,{lr}	@ safe link register
    sub sp,sp,#4	    @ align to 8-byte boundary
@ Push arguments 5 and 6 on stack
	ldr r2, =msg	@ A3: load pointer to msg
	ldrb r0, [r2]	@ get first char of msg
	stmfd sp!,{r0} 	@ A5: push char
	stmfd sp!,{r2} 	@ A6: push pointer to msg
@ Store arguments 1 to 4 in registers r0 to r3
	ldr r0, =fmt	@ A1: load pointer to fmt
	ldr r1, =name	@ A2: load pointer to name
	ldr r3, =len	@ A3: load len of msg 
@ call function and clean up stack afterwards
	bl printf		@ call clib-function printf
	add sp,sp,#8	@ remove A5,A6 from stack
@ return from subroutine
	add sp,sp,#4	@ remove alignment
	ldr r0, =0	    @ return 0
	ldmfd sp!,{pc}
  bx lr
.endfunc
