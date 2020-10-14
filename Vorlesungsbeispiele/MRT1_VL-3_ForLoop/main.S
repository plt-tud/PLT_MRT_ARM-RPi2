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
  mov r10, #1		//This is our counter

for_loop_test:
  mov r0, #3
  cmp r10, r0
  bgt for_loop_done // r10 > 3 or r10 <= 3

  ldr r1, =var_b
  ldr r0, [r1]
  add r0, r0, #1
  str r0, [r1]

for_loop_advance:
  add r10, r10, #1
  b for_loop_test

for_loop_done:
  ldmfd sp!,{r4-r11,lr}
  bx lr
.endfunc
