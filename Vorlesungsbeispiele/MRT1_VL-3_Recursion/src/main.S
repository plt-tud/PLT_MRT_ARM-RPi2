.global main
.type main, %function

.data
src:					// Define string src = "PCS/PSE TUD MRT1". One character takes one byte of memory.
	.word 0x2F534350
	.word 0x20455350
	.word 0x20445554
	.word 0x3154524D   

.set len,.-src			// Get the string's length by subtracting the "src" label's address
						// from this line's address (".")
	.byte 0
.text
.align 4
main:	stmfd sp!,{fp,lr}
	add fp,sp,#4

	ldr r0,=src			// print src
	bl puts

	ldr r0,=src			// r0: address of first byte of string
	ldr r2,=len-1		// r2: string length
	
	add r1,r0,r2 		// r1: address of last byte of string
	bl reverse			// reverse(addr_first, addr_last)

	ldr r0,=src			// print src again, hopefully reversed
	bl puts

	mov r0,#0
	ldmfd sp!,{fp,pc}	// restore fp and return
