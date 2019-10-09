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

/* //brief: ThermalLightFlat: Reacts to temperature changes by changing an LED output.
 *
 * ThermalLightFlat is a demo program using both SPI to sample an Analog Devices TMP35
 * Temperature sensor using anb MCP3008 ADC. It first aquires an initial measurement.
 * 3 LEDs are assumed to be connected to GPIOs 26, 27 & 22.
 *
 * Red:26    - On during ambient temperature
 * Yellow:27 - On during T > ambient temperature + DC_SENSE
 * Green:22  - On during T > ambient temperature + 2*DC_SENSE
 */
.equ GPIO_RED,    26
.equ GPIO_YELLOW, 27
.equ GPIO_GREEN,  22


/* From Analog Devices TMP35/36/37 Datasheet:
 * TMP35  V = 10 mV/°C, 25°C=250 mV
 *
 * From Microchip MCP3008 datasheet:
 * MCP3008:  D    = 1024 x V / V_ref (10-bit ADC)
 *           10mV = 31 descrete units = 1 °C
 *           10 descrete units = 0,322 °C
 */
.equ DC_SENSE, 5 // sensitivity, empirical value for warming up the sensor by hoding in hand at ~23 C

.global main
.type main, %function

.set DEBUG,0


.include "BCM2536.h"
.include "SYSCALL.h"

.data
.align
bcm2536_msg_err_open: .asciz "error initializing bcm2536"
.set bcm2536_mln_err_open, . - bcm2536_msg_err_open

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

  mov r4, #0 // r4:MMapBase
  mov r5, #0 // r5:Ambienttemperature

	bl BCM2536_GPIO_Open
	cmp r0,#0
	bne err_open

	mov r0,#GPIO_RED
	mov r1,#BCM2536_GPFSEL_OUTPUT
	bl BCM2536_GPIO_PinSelFun

	mov r0,#GPIO_YELLOW
	mov r1,#BCM2536_GPFSEL_OUTPUT
	bl BCM2536_GPIO_PinSelFun

	mov r0,#GPIO_GREEN
	mov r1,#BCM2536_GPFSEL_OUTPUT
	bl BCM2536_GPIO_PinSelFun

	bl BCM2536_SPI0_Init

forever:
	// send()
	mov r0, #3
	ldr r1, =spi_msg
	ldr r2, =spi_reply
  bl BCM2536_SPI0_Send

	ldr r0, =spi_reply
	// RX Buffer will appear reversed:
	//   LSB is first byte received, which to the MCP3008 is an MSP
	//   to create a propper 10bit int, place in order #0,#0,[1],[2]
	ldrb r1, [r0, #1]
	lsl  r1, #8
	ldrb r0, [r0, #2]
  orr  r3, r0, r1

  mov r6, r0 // currentTemp:r6 = r0

  // if (ambientTemp:r5 == 0) {
  cmp   r5, #0
  moveq r5, r0 //r5 = r0:currentTemp
  //}

  //bl PrintHex
  //bl PrintNL

  // if (Tambient:r5 + 2*DC_SENSE > T)
  mov r0, r5
  add r0, r5, #DC_SENSE
  add r0, r0, #DC_SENSE
  cmp r6, r0
  bge light_green

  // else if (Tambient:r5 + 1*DC_SENSE > T)
  sub r0, r0, #DC_SENSE
  cmp r6, r0
  bge light_yellow

	//else
	bal light_red

  light_yellow:
    mov r0,#GPIO_GREEN
    bl BCM2536_GPIO_PinClr
    mov r0,#GPIO_YELLOW
    bl BCM2536_GPIO_PinSet
    mov r0,#GPIO_RED
    bl BCM2536_GPIO_PinClr
    b light_done
  light_green:
    mov r0,#GPIO_GREEN
    bl BCM2536_GPIO_PinSet
    mov r0,#GPIO_YELLOW
    bl BCM2536_GPIO_PinClr
    mov r0,#GPIO_RED
    bl BCM2536_GPIO_PinClr
    b light_done
  light_red:
    mov r0,#GPIO_GREEN
    bl BCM2536_GPIO_PinClr
    mov r0,#GPIO_YELLOW
    bl BCM2536_GPIO_PinClr
    mov r0,#GPIO_RED
    bl BCM2536_GPIO_PinSet
    b light_done

light_done:
	mov r0,#1
	bl sleep
	bal forever

exit:
	bl BCM2536_GPIO_Close
	pop {r4-r9,fp,pc} // restore & return

err_open:
	push {r0,r7}
	mov r0,#1	// stdout
	ldr r1,=bcm2536_msg_err_open
	mov	r2,#bcm2536_mln_err_open
	mov r7,#SYSCALL_WRITE
	swi #0
	pop {r0,r7}
	bal exit
