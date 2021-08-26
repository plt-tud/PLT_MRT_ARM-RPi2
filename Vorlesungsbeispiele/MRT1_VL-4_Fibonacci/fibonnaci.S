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
  // EABI: Save caller's registers
  mov   ip, sp      	// Move our sp to scratch (parents FP still active)
  stmfd sp!,{r4-r11,lr} // r0-r4 can be used without saving
  mov   fp, ip      	// Setup our own FP

  cmp   r0, #0 			// if (n==0)
  moveq r0, #0 			// 	then r0 = 0
  beq   fib_iterative_done

  cmp   r0, #1 			// if (n==1)
  moveq r0, #1 			// 	then r0 = 1
  beq   fib_iterative_done

  mov r1, #1 			// r1 := x1 = temp_n-1; initial = fib(1) = 1
  mov r2, #0 			// r2 := x2 = temp_n-2; initial = fib(0) = 0
  mov r3, #2 			// r3 := k; iterator
  mov r4, r0 			// r4 := n

fib_iterative_loop_test:
  cmp r4, r3
  blt fib_iterative_done	 // while (k <= n) continue else jump to done

fib_iterative_loop_do:	// result = x1 + x2
  add r0, r1, r2
  mov r2, r1			// x2 = x1
  mov r1, r0			// x1 = result

fib_iterative_loop_increment:
  add r3, r3, #1        // k = k + 1
  b fib_iterative_loop_test

fib_iterative_done:

  // R0=return value
  // EABI: Restore caller's registers
  ldmfd sp!,{r4-r10,r11,lr}
  bx lr
.endfunc

.func fib_recursive
// uint32_t fib(uint32_t n)
fib_recursive:
  // EABI: Save caller's registers
  mov   ip, sp          // Move our sp to scratch (parents FP still active)
  stmfd sp!,{r4-r11,lr} // r0-r4 can be used without saving
  mov   fp, ip          // Setup our own FP

  /* fib_recursive calls itself to calculate the two fibonacci numbers fib(n-1) and fib(n-2) and then adds the
   * results up to calculate fib(n).
   * In case n is 0 or 1 the functions does not call itself and simply returns 0 or 1 respectively.
   */

  // r0 = n
  // check if n = 0
  CMP   r0, #0				// if (n == 0)
  MOVEQ r0, #0				//	then n = 0
  BEQ   fib_recursive_done	//  and break

  // check if n = 1
  CMP   r0, #1				// if (n == 1)
  MOVEQ r0, #1				// 	then n = 1
  BEQ   fib_recursive_done	//  and break

  SUB   R0, #1				// n--
  MOV   R4, R0     			// r4 = n - 1
  BL    fib_recursive		// call fib(n-1) recursively
  MOV   R5, R0     			// r5 = fib(n-1)

  SUB   R0, R4, #1 			// r0=n-2
  BL    fib_recursive		// call fib(n-1) recursively
  							// r0 = fib(n-2)

  ADD   R0, R0, R5  		// result = fib(n-2) + fib(n-1)

 fib_recursive_done:
  // r0: return value
  // EABI: Restore caller's registers
  ldmfd sp!,{r4-r11,lr}
  bx lr
.endfunc
