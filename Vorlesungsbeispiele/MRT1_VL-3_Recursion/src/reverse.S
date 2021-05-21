/* reverse(byte *addr_left, byte *addr_right) */
.global reverse
.type reverse, %function
reverse:
	stmfd sp!,{fp,lr}	// will call myself, save link register
	add fp,sp,#4		// fp points to base of subroutine frame

	cmp r0,r1		// ( if (addr_left >= addr_right ) ) return
	bge exit

	ldrb r2,[r0]	// load left byte at addr_left (r0)
	ldrb r3,[r1]	// load right byte at addr_right (r1)
	strb r3,[r0]	// store right byte at addr_left (r0)
	strb r2,[r1]	// store left byte at addr_right (r1)

	add r0,r0,#1	// advance to next character by incrementing addr_left
	sub r1,r1,#1	// advance to prev character by decrementing addr_right
	bl reverse		// call myself
exit:
	ldmfd sp!,{fp,lr}	// restore fp,lr
	mov pc,lr
