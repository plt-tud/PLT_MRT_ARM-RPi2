.text
.globl f
.func f
f:
	MOV R3, #200		// a = 200
	MOV R2, #0			// i = 0
	f_loop_0:
	LSR R4, R3, #1		// division by 2
	CMP R2, R4			// compare
	BLT f_loop_0_body	// if lower then, jump to f_loop_0_body
	MOV R0, R3			// else: move R3 to R0
	BX lr				// return to main-funciton (lr = link-register = R14)
	f_loop_0_body:
	SUB R3, R3, #1		// decrement a
	ADD R2, #1			// increment i
	B f_loop_0			// go to f_loop_0
