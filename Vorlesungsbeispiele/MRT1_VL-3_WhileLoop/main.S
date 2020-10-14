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
  // Ergebniss aus Ausdruck A in r0
  ldr r0, =var_a  // load pointer to a
  ldr r0, [r0]    // load value of a
  // Ergebniss aus Ausdruck B in r0
  ldr r1, =var_b  // load pointer to b
  ldr r1, [r1]    // load value of b

  cmp r0, r1      // compare a and b
  bge loop0_end   // skip IF section if b >= a

  /*Loop Body*/
  ldr r1, =var_a  // load pointer to a
  ldr r0, [r1]    // load value of a
  add r0, r0, #1
  str r0, [r1]

  /*Loop End*/
  b loop0_start
loop0_end:
  ldmfd sp!,{r4-r11,lr}
  bx lr
.endfunc
