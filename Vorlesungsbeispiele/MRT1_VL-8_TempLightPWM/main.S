/*
 * Copyright (c) 2018 Leon Urbas <leon.urbas//tu-dresden.de>
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

/**
 *  @brief: ThermalLightPWM: Reacts to temperature changes by changing an LED output.
 *
 * ThermalLightPWM is a demo program using both SPI to sample an Analog Devices TMP35
 * Temperature sensor using anb MCP3008 ADC. The lowest value aquired is interpreted as
 * ambient temperature (compensates for starting the application with a warm sensor).
 *
 * The parameter DC_SENSE gives a range for PWM Modulation of the green LED.
 * As the Tcurrent-Tambient approaches 0, the green LED will become brighter
 */

/**
 * @param USE_BOARDLEDS Selects either external LEDs (nice, safe) or on-board LEDs for
 *                      this example
 */
.equ USE_BOARDLEDS,0

.if (USE_BOARDLEDS == 0)
  /* These LEDs can be connected to the LK Linker Kit
   */
  //.equ GPIO_RED,    26 //unsued in this application
  .equ GPIO_GREEN,  22
  //.equ GPIO_YELLOW, 27 // unused in this application
.else
  /* The following two leds are the system LEDs at the rear of the Pi Board
   * using them might cause problems if the kernel led-class module is loaded.
   */
  .equ GPIO_RED,    35
  .equ GPIO_GREEN,  47
.endif

/* From Analog Devices TMP35/36/37 Datasheet:
 * TMP36  V = 10 mV/°C
 *     --> v2c(v) = (v_V-0.5_V)/0.01_V
 *
 * From Microchip MCP3008 datasheet:
 * MCP3008:  D    = 1024 x V / V_ref (10-bit ADC)
 *     --> d2c(d) = v2c(d/1024 * 3.3_V)
 *
 *     10 discrete units ~= 3,22 °C
 */
.equ DC_SENSE, 30 // sensitivity, empirical value for warming up the sensor by hoding in hand

.global main

.include "BCM2836.h"
.include "SYSCALL.h"

.data
.align
spi_msg:   .byte 0x01, 0x80, 0x00
.align
spi_reply: .byte 0x00, 0x00, 0x00

.text
.align
.func main
main:
  // EABI first
  mov   ip, sp
  stmfd sp!,{r4-r11,lr}
  mov   fp, ip

  main_io_init:     // Template: Sektion
    bl BCM2836_Open
    cmp r0,#0
    bne main_exit

    mov r0,#GPIO_GREEN
    mov r1,#BCM2836_GPFSEL_OUTPUT
    bl BCM2836_GPIO_PinSelFun

    mov r0,#GPIO_GREEN
    bl BCM2836_GPIO_PinClr

    bl BCM2836_SPI0_Init
  main_io_init_done:

  mov r5, #1024  // r5:Ambienttemperature=0
  mov r6, #0     // r6:currentTemp
  mov r7, #0     // r7:pwmCount

  main_loop_forever: // Template: Endlossschleife
    // send()
    mov r0, #3
    ldr r1, =spi_msg
    ldr r2, =spi_reply
    bl BCM2836_SPI0_Send

    ldr r0, =spi_reply
    // RX Buffer will appear reversed:
    //   LSB is first byte received, which to the MCP3008 is an MSP
    //   to create a propper 10bit int, place in order #0,#0,[1],[2]
    ldrb r1, [r0, #1]
    lsl  r1, #8
    ldrb r0, [r0, #2]
    orr  r6, r0, r1 // currentTemp:r6 = r0

    // Update ambient temperate if it is drifting downwards
    // Template: Selektion
    main_loop_forever_updateAmbient:      // if (ambientTemp:r5 > currentTemp:r6) {
      cmp   r6, r5
      movlt r5, r6 //ambientTemp:r5 = r6:currentTemp
    main_loop_forever_updateAmbient_done: //}

    add   r7, r7,#1   // pwmCnt++

    // Template: Selektion
    main_loop_forever_resetPWMCount: // if (++r7:pwmCount > DC_SENSE)
      cmp   r7, #DC_SENSE
      movge r7, #0                   // r7 = 0;
    main_loop_forever_resetPWMCount_done:


    // Template: Selektion
    main_loop_forever_pwm_setGreen_test:
    // if (currentTemp-ambientTemp < pwmCnt)
    sub  r1, r6, r5
    cmp  r1, r7
    bge  main_loop_forever_pwm_setGreen_else
    main_loop_forever_pwm_setGreen_if:
      // then GPIO_GREEN On
      mov  r0, #GPIO_GREEN
      bl   BCM2836_GPIO_PinSet
      b    main_loop_forever_pwm_setGreen_done
    main_loop_forever_pwm_setGreen_else:
      // else GPIO_GREEN Off
      mov  r0,#GPIO_GREEN
      bl   BCM2836_GPIO_PinClr
    main_loop_forever_pwm_setGreen_done:
    b main_loop_forever
  main_loop_forever_done:

  main_exit:
  bl BCM2836_Close

  // EABI Last
  ldmfd sp!,{r4-r10,r11,lr}
  bx lr
.endfunc // main
