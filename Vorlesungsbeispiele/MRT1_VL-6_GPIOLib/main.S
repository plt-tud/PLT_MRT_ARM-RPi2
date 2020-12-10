/*
 * Copyright (c) 2017 Chris Iatrou <chris_paul.iatrou@tu-dresden.de>
 * Copyright (c) 2018 Leon Urbas <leon.urbas@tu-dresden.de>
 * Copyright (c) 2019 Chris Iatrou <chris_paul.iatrou@tu-dresden.de>
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


/**
 *  @brief: GPIOLib demnonstriert die Nutzung der GPIO Bibliothek
 *
 *  Das Programm blinkt abwechselnd mit der gruenen/roten LED.
 *  Per Default werden die LEDs des Linker Kits benutzt, als
 *  Rueckfall-Loesung koennen die Status LEDs des Pis genutzt werden.
 */


.global main
.type main, %function

.include "BCM2836.h"
.include "SYSCALL.h"

/**
 * @param USE_BOARDLEDS Selects either external LEDs (nice, safe) or on-board LEDs for
 *                      this example
 */
.equ USE_BOARDLEDS,0

.if (USE_BOARDLEDS == 0)
  /* These LEDs can be connected to the LK Linker Kit
   */
  .equ GPIO_RED,    26
  .equ GPIO_GREEN,  22
  //.equ GPIO_YELLOW, 27 // unused in this application
.else
  /* The following two leds are the system LEDs at the rear of the Pi Board
   * using them might cause problems if the kernel led-class module is loaded.
   */
  .equ GPIO_RED,    35
  .equ GPIO_GREEN,  47
.endif

// Status-LEDs des Pis

.data
.balign 4
BCM2836_msg_err_open: .asciz "error initializing BCM2836"
.set BCM2836_mln_err_open, . - BCM2836_msg_err_open

.text
.balign 4

.func main
main:
  // EABI first
  mov   ip, sp
  stmfd sp!,{r4-r11,lr}
  mov   fp, ip

  bl BCM2836_GPIO_Open
  cmp r0,#0
  bne main_err_open

  mov r0,#GPIO_RED
  mov r1,#BCM2836_GPFSEL_OUTPUT
  bl BCM2836_GPIO_PinSelFun

  mov r0,#GPIO_GREEN
  mov r1,#BCM2836_GPFSEL_OUTPUT
  bl BCM2836_GPIO_PinSelFun


//loop init
	mov r10, #0
main_loop: // clear all lights
  // red for 1 seconds
  mov r0,#GPIO_RED
  bl BCM2836_GPIO_PinSet
  mov r0,#GPIO_GREEN
  bl BCM2836_GPIO_PinClr
  mov r0,#1
  bl sleep

  // red + green for 1 second
  mov r0,#GPIO_RED
  bl BCM2836_GPIO_PinSet
  mov r0,#GPIO_GREEN
  bl BCM2836_GPIO_PinSet
  mov r0,#1
  bl sleep

  // green for 1 seconds
  mov r0,#GPIO_RED
  bl BCM2836_GPIO_PinClr
  mov r0,#GPIO_GREEN
  bl BCM2836_GPIO_PinSet
  mov r0,#1
  bl sleep

//loop advance
  add r10, r10 ,#1
//loop test
  cmp r10, #3
  bgt main_loop_done
  bal main_loop	//Branch always

main_loop_done:
  mov r0,#GPIO_RED
  bl BCM2836_GPIO_PinClr
  mov r0,#GPIO_GREEN
  bl BCM2836_GPIO_PinClr
  bl BCM2836_GPIO_Close

  mov r0, #0
main_exit:
  ldmfd sp!,{r4-r10,r11,lr}
  bx lr

main_err_open:
  push {r0,r7}
  mov r0,#1  // stdout
  ldr r1,=BCM2836_msg_err_open
  mov  r2,#BCM2836_mln_err_open
  mov r7,#SYSCALL_WRITE
  swi #0

  ldmfd sp!,{r4-r10,r11,lr}
  bx lr
.endfunc
