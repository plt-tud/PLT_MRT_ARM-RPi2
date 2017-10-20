.global main
.func main

main:
BL f					// Branch and Link (Call) f()
BX lr					// Return

f:
	MOV R3, #200		// a=200
	MOV R2, #0			// for (i=0
f_loop_0:
	LSR R4, R3, #1		// a/2
	CMP R2, R4      	// i<a/2
	BLT f_loop_0_body	// for(...) {
	MOV R3, R0
	BX lr				// return
f_loop_0_body:
	SUB R3, R3, #1		// a-=1
	ADD R2, #1			// i++
	B f_loop_0          // for...}
