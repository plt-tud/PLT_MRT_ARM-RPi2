.global main

.text
.balign 4

.func   main

main:
  stmfd sp!,{r4-r11,lr}
/**********************************/
// Function Calls

  // call r0 = sum2(1, 11)
  // all parameters fit into registers
  mov r0, #1
  mov r1, #11
  bl sum2			// call sum2	(bl - branch and link)

  // call r0 = sum7(1, 2, 3, 4, 5, 6, 7)
  // parameters 5, 6 and 7 are passe by using the stack
  mov r0, #5
  mov r1, #6
  mov r2, #7
  stmfd sp!, {r0-r2}	// pushes parameters 5, 6 and 7 to the stack

  // parameters 1 to 4 fit into registers r0 to r3
  mov r0, #1
  mov r1, #2
  mov r2, #3
  mov r3, #4

  bl sum7			// call sum7	(bl - branch and link)


  // remove parameters 5, 6, 7 from the stack by moving the stack pointer
  // we do not have to clear the values since they will be overwritten anyway
  add sp, sp, #12	// move stack pointer by 3 * 4 bytes because we clear values

  ldmfd sp!,{r4-r11,lr}
  bx lr
.endfunc

.func sum2			// int sum2(int a, int b)
sum2:
  // EABI convention requires us to save the caller's registers to stack so we can restore
  // them after finishing the function.
  mov   ip, sp			// Move our sp to ipc-scratch (parents FP still active)
  stmfd sp!,{r4-r11,lr} // r0-r4 can be changed according do EABI convention
  mov   fp, ip			// Setup our own FP

  // int a = r0, int b = r1
  add r0, r0, r1 	// r0 = a + b
  					// r0=return value

  // EABI requires us to restore the registers
  ldmfd sp!,{r4-r11,lr}
  bx lr
.endfunc

.func sum7
// int sum7(int a, int b, int c, int d, int e, int f, int g)
//              a...d sind r0..r3, der rest liegt auf dem stack
sum7:
  // EABI convention requires us to save the caller's registers
  mov   ip, sp			// Move our sp to ipc-scratch (parents FP still active)
  stmfd sp!,{r4-r11,lr} // r0-r4 can be changed according do EABI convention
  mov   fp, ip			// Setup our own FP

  // int a = r0, int b = r1
  add r0, r0, r1 // r = a + b
  add r0, r0, r2 // r0 += c
  add r0, r0, r3 // r0 += d

  // The parameters d to g are on the stack.
  // The stacks base address is stored in fp
  ldr r1, [fp, #0] // r0 += e
  add r0, r1
  ldr r1, [fp, #4] // r0 += f
  add r0, r1
  ldr r1, [fp, #8] // r0 += g
  add r0, r1

  // r0=return value
  // EABI requires us to restore the registers
  ldmfd sp!,{r4-r10,r11,lr}
  bx lr
.endfunc
