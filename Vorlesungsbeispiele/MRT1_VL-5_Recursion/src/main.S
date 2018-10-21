.global main
.type main, %function

.data
src:	.word 0x2F534350,0x20455350,0x20445554,0x3154524D
.set len,.-src
	.byte 0
.text
.align 4
main:	stmfd sp!,{fp,lr}
	add fp,sp,#4

	ldr r0,=src	@ print src
	bl puts

	ldr r0,=src	@ adress of first byte of string
	ldr r2,=len-1
	add r1,r0,r2 @ adress of last byte of string
	bl reverse	@ reverse(first,last)

	ldr r0,=src	@ print src again, hopefully reversed
	bl puts

	mov r0,#0
	ldmfd sp!,{fp,pc}	@ restore fp and return
