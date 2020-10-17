.global main, printf
.type main, %function

.data
fmt:	.asciz "asciz %s: a=%x, l=%d, c=%c, s=<%s>\n"
name:	.asciz "msg"
msg:	.asciz "Hallo MRT-1"

.set len, . - msg
 
.text
.balign 4

.func   main

main:
  stmfd sp!,{r4-r11,lr}
/**********************************/
// Function Calls

  // rufe r0 = sum2(1, 11) auf
  // alle Paramter passen in die register
  mov r0, #1
  mov r1, #11
  bl sum2

  // rufe r0 = sum7(1, 2, 3, 4, 5, 6, 7) auf
  //5,6 und 7 uebergeben wir auf dem Stack; wir nutzen
  mov r0, #5
  mov r1, #6
  mov r2, #7
  stmfd sp!, {r0-r2}

  // 1..4 passen in die Register 0..2
  mov r0, #1
  mov r1, #2
  mov r2, #3
  mov r3, #4

  bl sum7
  // Aufrauemn von 5, 6, 7 auf dem stack
  // es reicht, wenn wir den stack point "bewegen",
  // die paramter-werte sind uns egal
  add sp, sp, #12

  //Calling printf
    stmfd sp!,{lr}	@ safe link register
    sub sp,sp,#4	    @ align to 8-byte boundary
@ Push arguments 5 and 6 on stack
	ldr r2, =msg	@ A3: load pointer to msg
	ldrb r0, [r2]	@ get first char of msg
	stmfd sp!,{r0} 	@ A5: push char
	stmfd sp!,{r2} 	@ A6: push pointer to msg
 
@ Store arguments 1 to 4 in registers r0 to r3
	ldr r0, =fmt	@ A1: load pointer to fmt
	ldr r1, =name	@ A2: load pointer to name
	ldr r3, =len	@ A3: load len of msg
 
@ call function and clean up stack afterwards
	bl printf		@ call clib-function printf
	add sp,sp,#8	@ remove A5,A6 from stack
 
@ return from subroutine
	add sp,sp,#4	@ remove alignment
	ldr r0, =0	    @ return 0
	ldmfd sp!,{pc}

  ldmfd sp!,{r4-r11,lr}
  bx lr
.endfunc

.func sum2
// int sum2(int a, int b)
sum2:
  // EABI: Wir muessen die Register des Aufrufers sichern!
  mov   ip, sp			// Move our sp to ipc-scratch (parents FP still active)
  stmfd sp!,{r4-r11,lr} // r0-r4 duerfen von sum2 veraendert werden
  mov   fp, ip			// Setup our own FP

  // int a = r0, int b = r1
  add r0, r0, r1 // R0=A+B

  // R0=return value
  // EABI: Wir muessen die Register des Aufrufers wiederherstellen!
  ldmfd sp!,{r4-r11,lr}
  bx lr
.endfunc

.func sum7
// int sum7(int a, int b, int c, int d, int e, int f, int g)
//              a...d sind r0..r3, der rest liegt auf dem stack
sum7:
  // EABI: Wir muessen die Register des Aufrufers sichern!
  mov   ip, sp			// Move our sp to scratch (parents FP still active)
  stmfd sp!,{r4-r11,lr} // r0-r4 duerfen von sum2 veraendert werden
  mov   fp, ip			// Setup our own FP

  // int a = r0, int b = r1
  add r0, r0, r1 // R0=A+B
  add r0, r0, r2 // R0+=C
  add r0, r0, r3 // R0+=D

  // Die Argumente d...g liegen auf dem Stack
  // fp zeigt auf die Adresse direkt nach dem
  ldr r1, [fp, #0] // R0+=E
  add r0, r1
  ldr r1, [fp, #4] // R0+=F
  add r0, r1
  ldr r1, [fp, #8] // R0+=G
  add r0, r1

  // R0=return value
  // EABI: Wir muessen die Register des Aufrufers wiederherstellen!
  ldmfd sp!,{r4-r10,r11,lr}
  bx lr
.endfunc
