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
 *  @brief: ThermalLightFlat: Reacts to temperature changes by changing an LED output.
 *
 * ThermalLightFlat is a demo program using both SPI to sample an Analog Devices TMP35
 * Temperature sensor using anb MCP3008 ADC. The lowest value aquired is interpreted as
 * ambient temperature (compensates for starting the application with a warm sensor).
 *
 * The parameter DC_SENSE gives a range for PWM Modulation of the green and red led.
 * As the Tcurrent-Tambient approaches 0, the green LED will become darker and the
 * red LED brighter.
 */

/**
 * @param DEBUG Setting Debug to anything but 0 will cause the main loop to delay 1s between
 *              updates and print the hex ADC Value to the shell.
 */
.equ DEBUG,0

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

/* From Analog Devices TMP35/36/37 Datasheet:
 * TMP36  V = 10 mV/°C, 25°C=750 mV
 *     --> v2c(v) = (v_V-0.75_V)/0.01_V + 25°C
 *
 * From Microchip MCP3008 datasheet:
 * MCP3008:  D    = 1024 x V / V_ref (10-bit ADC)
 *     --> d2c(d) = v3c(d/1024 * 3.3_V)
 *
 *     10 discrete units ~= 3,22 °C
 */
.equ DC_SENSE, 10 // sensitivity, empirical value for warming up the sensor by hoding in hand at ~23 C

.global main
.type main, %function


.include "BCM2836.h"
.include "SYSCALL.h"

.data
.align
bcm2836_msg_err_open: .asciz "error initializing bcm2836"
.set bcm2836_mln_err_open, . - bcm2836_msg_err_open

.align
// See MCP3008 Datasheet, Figure 6-1, MCU Transmitted Data
spi_msg:   .byte 0x01, 0x80, 0x00, 0x00
.align
spi_reply: .byte 0x00, 0x00, 0x00, 0x00

.text
.align
main:
	push {r4-r9,fp,lr} // safe 8 regs
	add fp,sp,#(8-1)*4 // fp <- lr // stack

  mov r4, #0    // r4:MMapBase
  mov r5, #1024    // r5:Ambienttemperature=0
  mov r6, #0    // r6:currentTemp
  mov r7, #0    // r7:pwmCount

	bl BCM2836_GPIO_Open
	cmp r0,#0
	bne err_open

	mov r0,#GPIO_RED
	mov r1,#BCM2836_GPFSEL_OUTPUT
	bl BCM2836_GPIO_PinSelFun

	mov r0,#GPIO_GREEN
	mov r1,#BCM2836_GPFSEL_OUTPUT
	bl BCM2836_GPIO_PinSelFun

	bl BCM2836_SPI0_Init

forever:
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

  .if DEBUG==1
    mov r0, r6
    bl PrintHex
    bl PrintNL
  .endif

  // Update ambient temperate if it is drifting downwards
  // if (ambientTemp:r5 == 0) {
  cmp   r6, r5
  movlt r5, r6 //ambientTemp:r5 = r6:currentTemp
  //}

  // if (++r7:pwmCount > DC_SENSE) r7 = 0;
  add   r7, r7,#1   // pwmCnt++
  cmp   r7, #DC_SENSE
  movge r7, #0

  // if (currentTemp-ambientTemp > pwmCnt) greenLED=Off
  sub  r1, r6, r5
  cmp  r1, r7
  blgt light_pwm_greenOff
  // else: greenLED=on
  mov  r0,#GPIO_GREEN
  bl   BCM2836_GPIO_PinSet
  mov  r0, #GPIO_RED
  bl   BCM2836_GPIO_PinClr
  bal  light_pwm_done

  light_pwm_greenOff:
  mov  r0,#GPIO_GREEN
  bl   BCM2836_GPIO_PinClr
  mov  r0, #GPIO_RED
  bl   BCM2836_GPIO_PinSet
  bal  light_pwm_done

  light_pwm_done:
  .if DEBUG==1
    // sleep(1)
    mov r0, #1
    bl sleep
  .endif
	bal forever

exit:
	bl BCM2836_GPIO_Close
	pop {r4-r9,fp,pc} // restore & return

err_open:
	push {r0,r7}
	mov r0,#1	// stdout
	ldr r1,=bcm2836_msg_err_open
	mov	r2,#bcm2836_mln_err_open
	mov r7,#SYSCALL_WRITE
	swi #0
	pop {r0,r7}
	bal exit
