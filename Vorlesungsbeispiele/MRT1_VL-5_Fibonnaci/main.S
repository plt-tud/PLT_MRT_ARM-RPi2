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
  push {r1-r11, lr}

  // Run tests
  BL test_fib_recursive_zero
  BL test_fib_recursive_one
  BL test_fib_recursive_two
  BL test_fib_recursive_4m

  BX  LR
.endfunc

.func test_fib_recursive_zero
test_fib_recursive_zero:
  // small test wrapper: Return 0 if fib(0)==0
  // We only use temporary regs, no need to save regs

  // Test
  mov r0, #0
  bl fib_recursive
  mov r1, #0 // should be 0

  cmp r1, r0
  moveq r0, #0
  movne r0, #1
  bx lr
.endfunc

.func test_fib_recursive_one
test_fib_recursive_one:
  // small test wrapper: Return 0 if fib(0)==0
  // We only use temporary regs, no need to save regs

  // Test
  mov r0, #1
  bl fib_recursive
  mov r1, #1 // should be 1

  cmp r1, r0
  moveq r0, #0
  movne r0, #1
  bx lr
.endfunc

.func test_fib_recursive_two
test_fib_recursive_two:
  // small test wrapper: Return 0 if fib(0)==0
  // We only use temporary regs, no need to save regs

  // Test
  mov r0, #2
  bl fib_recursive
  mov r1, #2 // should be 2

  cmp r1, r0
  moveq r0, #0
  movne r0, #1
  bx lr
.endfunc

.func test_fib_recursive_4m
test_fib_recursive_4m:
  // small test wrapper: Return 0 if fib(0)==0
  // We only use temporary regs, no need to save regs

  // Test
  mov r0, #0xFFFFFFFF
  bl fib_recursive
  mov r1, #0 // should be 0

  cmp r1, r0
  moveq r0, #0
  movne r0, #1
  bx lr
.endfunc


