/*
* Demonstrates a for-loop.
*/

.data
.balign 4
var_b: .word 0x00000004

.text
.balign 4
.global main
.func   main


main:
  stmfd sp!,{r4-r11,lr}
/**********************************/
// for-Schleife
// for (i=1; i<=3; i++) { b++ }
for_loop_init:
  mov r10, #1			// i = 1

for_loop_test:
  mov r0, #3			// r0 = 3

  cmp r10, r0
  bgt for_loop_done 	// if i > 3 then jump to for_loop_done	(gt - greater than)
						// if i<= 3 then continue

  ldr r1, =var_b		// load address of b
  ldr r0, [r1]			// load value of b to r0
  add r0, r0, #1		// b++
  str r0, [r1]			// store value of b at address of b

for_loop_advance:
  add r10, r10, #1		// i++
  b for_loop_test		// continue for-loop

for_loop_done:
  ldmfd sp!,{r4-r11,lr}
  bx lr
.endfunc
