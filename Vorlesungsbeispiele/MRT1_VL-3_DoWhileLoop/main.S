.data
.balign 4
var_a: .word 0x00000004


.text
.balign 4
.global main
.func   main


main:
  stmfd sp!,{r4-r11,lr}
/**********************************/
// do {A--} while ( a > 0)
loop_start:
  /*Loop Body*/
  ldr r1, =var_a  // load pointer to a
  ldr r0, [r1]    // load value of a
  sub r0, r0, #1  // a--
  str r0, [r1]    // store value of a

  /*Setup & Test loop expression*/
  ldr r0, =var_a  // load pointer to a
  ldr r0, [r0]    // load value of a
  mov r1, #0
  cmp r0, r1      // compare a and 0

  /*Loop End*/
  bgt loop1_start // skip IF section if 0 <= a
loop_end:
  ldmfd sp!,{r4-r11,lr}
  bx lr
.endfunc
