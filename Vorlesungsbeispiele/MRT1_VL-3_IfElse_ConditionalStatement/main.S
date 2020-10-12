	.data
.balign 4
var_a: .word 0x00000000
var_b: .word 0x00000010
var_x: .word 0x00000010

.text
.balign 4
.global main
.func   main

main:
  stmfd sp!,{r4-r11,lr}
/**********************************/
// WENN ( A < B) DANN … SONST …
// Ergebniss aus Ausdruck A in r0
  ldr r0, =var_a  // load pointer to a
  ldr r0, [r0]    // load value of a
// Ergebniss aus Ausdruck B in r1
  ldr r1, =var_b  // load pointer to b
  ldr r1, [r1]    // load value of b

  cmp r0, r1      // compare a and b
  bge if_else     // skip IF section if b >= a
if_match:
  mov r0, #1      // IF section: load 1 into r0
  b if_done       // skip ELSE section unconditionally
if_else:
  mov r0, #0      // ELSE section: load 0 into r0

if_done:
  ldr r1, =var_x  // load pointer to x
  str r0, [r1]    // store r0 in x

