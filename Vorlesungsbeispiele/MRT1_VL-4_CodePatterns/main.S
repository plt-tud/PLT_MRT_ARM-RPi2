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

/**********************************/
// Annehmende Schleife
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

/**********************************/
// Abweisende Schleife
// do {A--} while ( a > 0)
loop1_start:
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


/**********************************/
// for-Schleife
// for (i=1; i<=10; i++) { b++ }
for_loop_init:
  mov r10, #1

for_loop_test:
  mov r0, #10
  cmp r10, r0 // r10 <= 10
  bgt for_loop_done

  ldr r1, =var_b
  ldr r0, [r1]
  add r0, r0, #1
  str r0, [r1]

for_loop_advance:
  add r10, r10, #1
  b for_loop_test

for_loop_done:

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
