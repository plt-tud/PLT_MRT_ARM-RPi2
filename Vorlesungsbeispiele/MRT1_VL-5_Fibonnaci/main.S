/*
 * Copyright (c) 2017 Chris Iatrou <chris_paul.iatrou//tu-dresden.de>
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
.global main
.balign 4

.func main
main:
  stmfd sp!,{r4-r11,lr}
  // Test Pass/Fail
  mov r4, #0

  /* Wir benutzen eine Reihe sehr einfacher Wrapper zum
   * testen spezifischer Rueckgabewerte von fib. D.h. wir
   * testen alle kritischen Werte bei jeder Veraenderung unserer
   * Funktionen.
   *
   * Die Test-Wrapper koennten generischer sein (assertions)
   *  bool assert_fib(value, expect)
   */
  // Run tests: fib(0) = 0
  BL  test_fib_zero
  ORR r4, r4, r0

  // Run tests: fib(1) = 1
  BL test_fib_one
  ORR r4, r4, r0

  // Run tests: fib(2) = 1
  BL test_fib_two
  ORR r4, r4, r0

  // Run tests: fib(10) = 55
  BL test_fib_ten
  ORR r4, r4, r0

  mov r0, r4

  ldmfd sp!,{r4-r11,lr}
  bx  LR
.endfunc

.func test_fib_zero
test_fib_zero:
  /* bool test_fib_zero
   *
   * Teste wie folgt:
   *  r4 = fib_recursive(0)
   *  r0 = fib_iterative(0)
   * falls r4 != r0: fail: return 1
   * falls r4 != 0:  fail: return 1
   * return 0
   */
  // small test wrapper: Return 0 if fib(0)==0
  stmfd sp!,{r4-r11,lr}

  // r4 = fib(0)
  mov r0, #0
  bl fib_recursive
  mov r4, r0

  // r0 = fib(0)
  mov r0, #0
  bl fib_iterative

  // fib_iterative != fib_recursive return fail;
  cmp   r4, r0
  movne r0, #1
  bne   test_fib_one_done

  // if fib_recursive != 0 return fail;
  cmp   r4, #0
  moveq r0, #0
  movne r0, #1

test_fib_zero_done:
  ldmfd sp!,{r4-r10,r11,lr}
  bx lr
.endfunc

.func test_fib_one
test_fib_one:
  // small test wrapper: Return 0 if fib(0)==0
  stmfd sp!,{r4-r11,lr}

  // r4 = fib(1)
  mov r0, #1
  bl fib_recursive
  mov r4, r0

  // r0 = fib(1)
  mov r0, #1
  bl fib_iterative

  // fib_iterative != fib_recursive return fail;
  cmp   r4, r0
  movne r0, #1
  bne   test_fib_one_done

  // if fib_recursive != 1 return fail;
  cmp   r4, #1
  moveq r0, #0
  movne r0, #1

test_fib_one_done:
  ldmfd sp!,{r4-r10,r11,lr}
  bx lr
.endfunc

.func test_fib_two
test_fib_two:
  // small test wrapper: Return 0 if fib(0)==0
  stmfd sp!,{r4-r11,lr}

  // r4 = fib(2)
  mov r0, #2
  bl fib_recursive
  mov r4, r0

  // r0 = fib(2)
  mov r0, #2
  bl fib_iterative

  // fib_iterative != fib_recursive return fail;
  cmp   r4, r0
  movne r0, #1
  bne   test_fib_one_done

  // if fib_recursive != 1 return fail;
  cmp   r4, #1
  moveq r0, #0
  movne r0, #1

test_fib_two_done:
  ldmfd sp!,{r4-r10,r11,lr}
  bx lr
.endfunc

.func test_fib_ten
test_fib_ten:
  // small test wrapper: Return 0 if fib(0)==0
  stmfd sp!,{r4-r11,lr}

  // r4 = fib(10)
  mov r0, #10
  bl fib_recursive
  mov r4, r0

  // r0 = fib(10)
  mov r0, #10
  bl fib_iterative

  // fib_iterative != fib_recursive return fail;
  cmp   r4, r0
  movne r0, #1
  bne   test_fib_ten_done

  // if fib_recursive != 55 return fail;
  cmp   r4, #55
  moveq r0, #0
  movne r0, #1

test_fib_ten_done:
  ldmfd sp!,{r4-r10,r11,lr}
  bx lr
.endfunc

