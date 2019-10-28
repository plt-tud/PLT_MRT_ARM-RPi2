/*
 * Copyright (c) 2017 Chris Iatrou <chris_paul.iatrou//tu-dresden.de>
 * Copyright (c) 2019 Chris Iatrou <chris_paul.iatrou//tu-dresden.de>
 *
 * Hiermit wird unentgeltlich jeder Person, die eine Kopie der
 * Software und der zugehörigen Dokumentationen (die "Software")
 * erhält, die Erlaubnis erteilt, sie uneingeschränkt zu nutzen,
 * inklusive und ohne Ausnahme mit dem Recht, sie zu verwenden,
 * zu kopieren, zu verändern, zusammenzufügen, zu veröffentlichen,
 * zu verbreiten, zu unterlizenzieren und/oder zu verkaufen, und
 * Personen, denen diese Software überlassen wird, diese Rechte
 * zu verschaffen, unter den folgenden Bedingungen:
 *
 * Der obige Urheberrechtsvermerk und dieser Erlaubnisvermerk
 * sind in allen Kopien oder Teilkopien der Software beizulegen.
 *
 * DIE SOFTWARE WIRD OHNE JEDE AUSDRÜCKLICHE ODER IMPLIZIERTE
 * GARANTIE BEREITGESTELLT, EINSCHLIEẞLICH DER GARANTIE ZUR
 * BENUTZUNG FÜR DEN VORGESEHENEN ODER EINEM BESTIMMTEN ZWECK
 * SOWIE JEGLICHER RECHTSVERLETZUNG, JEDOCH NICHT DARAUF
 * BESCHRÄNKT. IN KEINEM FALL SIND DIE AUTOREN ODER
 * COPYRIGHTINHABER FÜR JEGLICHEN SCHADEN ODER SONSTIGE
 * ANSPRÜCHE HAFTBAR ZU MACHEN, OB INFOLGE DER ERFÜLLUNG EINES
 * VERTRAGES, EINES DELIKTES ODER ANDERS IM ZUSAMMENHANG MIT
 * DER SOFTWARE ODER SONSTIGER VERWENDUNG DER SOFTWARE ENTSTANDEN.
 */

.data


.text
.global fib_recursive, fib_iterative

.func fib_iterative
// uint32_t fib(uint32_t n)
fib_iterative:
  // EABI: Wir muessen die Register des Aufrufers sichern!
  mov   ip, sp      // Move our sp to scratch (parents FP still active)
  stmfd sp!,{r4-r11,lr} // r0-r4 duerfen veraendert werden
  mov   fp, ip      // Setup our own FP

  cmp   r0, #0 // if (n==0)
  moveq r0, #0 // ... optimierbar
  beq   fib_iterative_done

  cmp   r0, #1 // if (n==1)
  moveq r0, #1 // ... optimierbar
  beq   fib_iterative_done

  mov r1, #1 // r1 := temp_n-1; initial = fib(1) = 1
  mov r2, #0 // r2 := temp_n-2; initial = fib(0) = 0
  mov r3, #2 // r3 := k; iterator
  mov r4, r0 // r4 := n

fib_iterative_loop_test:
  cmp r4, r3              // while (k <= n)
  blt fib_iterative_done

fib_iterative_loop_do:
  add r0, r1, r2
  mov r2, r1
  mov r1, r0

fib_iterative_loop_increment:
  add r3, r3, #1           // k=k+1
  b fib_iterative_loop_test

fib_iterative_done:

  // R0=return value
  // EABI: Wir muessen die Register des Aufrufers wiederherstellen!
  ldmfd sp!,{r4-r10,r11,lr}
  bx lr
.endfunc

.func fib_recursive
// uint32_t fib(uint32_t n)
fib_recursive:
  // EABI: Wir muessen die Register des Aufrufers sichern!
  mov   ip, sp          // Move our sp to scratch (parents FP still active)
  stmfd sp!,{r4-r11,lr} // r0-r4 duerfen veraendert werden
  mov   fp, ip          // Setup our own FP

  // r0 = Parameter
  // if (n==0) { (optimierte Selektion)
  CMP   r0, #0
  MOVEQ r0, #0
  BEQ   fib_recursive_done
  //}

  // if (n==1) {  (optimierte Selektion)
  CMP   r0, #1
  MOVEQ r0, #1
  BEQ   fib_recursive_done
  //}

  SUB   R0, #1
  MOV   R4, R0     //  temp = n-1
  BL    fib_recursive
  MOV   R5, R0     // temp2=fib(n-1)

  SUB   R0, R4, #1 // r0=n-2
  BL    fib_recursive

  ADD   R0, R0, R5  // temp = temp + fib(n-2)

 fib_recursive_done:
  // R0=return value
  // EABI: Wir muessen die Register des Aufrufers wiederherstellen!
  ldmfd sp!,{r4-r11,lr}
  bx lr
.endfunc
