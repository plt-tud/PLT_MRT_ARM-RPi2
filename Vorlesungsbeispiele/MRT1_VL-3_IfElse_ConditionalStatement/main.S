/**
 * Compares to variables from memory and stores the comparsion result in var_x.
 */


.data
.balign 4

var_a: .word 0x00000000		// var_a = 0x0;
var_b: .word 0x00000010		// var_b = 0x10;
var_x: .word 0x00000010		// var_x = 0x10;

.text
.balign 4
.global main
.func   main

main:
  stmfd sp!,{r4-r11,lr}

// IF ( var_a < var_b) THEN … ELSE …

if_start:
  ldr r0, =var_a  // load address of var_a to r0
  ldr r0, [r0]    // load value of var_a by loading data from address in r0

  ldr r1, =var_b  // load address of var_b to r1
  ldr r1, [r1]    // load value of var_b

  cmp r0, r1      // compare var_a and var_b, the comparison result is placed into the condition flags N, Z, C, V
  bge if_else     // jump to label if_else when var_a >= var_b (bge - branch if greater or equal)
  				  // bge accesses the comparison results by accessing the condition flags

if_match:
  mov r0, #1      // MATCH section: load return value 1 (true) into r0
  b if_done       // skip if_else and jump to if_done
if_else:
  mov r0, #0      // ELSE section: load return value 0 (false) into r0

if_done:
  ldr r1, =var_x  // load address of var_x
  str r0, [r1]    // store content of r0 at address of var_x

  ldmfd sp!,{r4-r11,lr}
  bx lr
.endfunc
