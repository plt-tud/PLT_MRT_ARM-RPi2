.global main

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
