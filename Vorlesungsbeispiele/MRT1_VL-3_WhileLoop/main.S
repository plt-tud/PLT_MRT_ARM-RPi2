.data
.balign 4
var_a: .word 0x00000000
var_b: .word 0x00000004

.text
.balign 4
.global main
.func   main


main:
  stmfd sp!,{r4-r11,lr}
/**********************************/
// WHILE ( A < B) {A++}
loop0_start:
  /*Setup & Test loop expression*/
  ldr r0, =var_a  // load pointer to a
  ldr r0, [r0]    // load value of a

  ldr r1, =var_b  // load pointer to b
  ldr r1, [r1]    // load value of b

  cmp r0, r1      // compare a and b
  bge loop0_end   // if a >= b then jump to loop0_end

  /*Loop Body*/
  ldr r1, =var_a  // load pointer to a
  ldr r0, [r1]    // load value of a

  add r0, r0, #1  // a++
  str r0, [r1]

  /*Loop End*/
  b loop0_start   // unconditional jump to loop0_start
loop0_end:
  ldmfd sp!,{r4-r11,lr}
  bx lr
.endfunc
