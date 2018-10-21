/* reverse(byte *left, byte *right) */
.global reverse
.type reverse, %function
reverse:
	stmfd sp!,{fp,lr}	@ will call myself, safe link register
	add fp,sp,#4		@ fp points to base of subroutine frame

	cmp r0,r1		@ ( if (left >= right ) ) return
	bge exit

	ldrb r2,[r0]	@ load byte at *left
	ldrb r3,[r1]	@ load byte at *right
	strb r3,[r0]	@ store in *left
	strb r2,[r1]	@ store in *right

	add r0,r0,#1	@ advance to next memory position
	sub r1,r1,#1	@ advance to prev memory position
	bl reverse		@ call myself
exit:
	ldmfd sp!,{fp,lr}	@ restore fp,lr
	mov pc,lr
