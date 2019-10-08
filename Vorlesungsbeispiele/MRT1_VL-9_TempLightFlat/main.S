/*
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

/* @brief: ThermalBlinker: Reacts to temperature changes by changing an LED output.
 *
 * ThermalBlinker is a demo program using both SPI to sample an Analog Devices TMP35
 * Temperature sensor using anb MCP3008 ADC. The green system LED on GPIO 47 is
 * "extinguished" if the temperature rises more than a preconfigured amount.
 */

.global main
.type main, %function

.set DEBUG,0

.equ GPIO_RED,		26
.equ GPIO_YELLOW,	27
.equ GPIO_GREEN, 	22

.include "BCM2536.h"
.include "SYSCALL.h"

.data
.align
bcm2536_msg_err_open: .asciz "error initializing bcm2536"
.set bcm2536_mln_err_open, . - bcm2536_msg_err_open

.align
spi_msg: .byte 0x01, 0x80, 0x00

.text
.align
main:
	push {r4-r9,fp,lr} @ safe 8 regs
	add fp,sp,#(8-1)*4 // fp <- lr @ stack

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

.if DEBUG>0
	bl BCM2536_GPIO_GetBase
	bl PrintHex
	bl PrintNL
.endif

	bl BCM2536_SPI0_GetBase
	mov r4, r0
.if DEBUG>0
	bl PrintHex
	bl PrintNL
.endif

	@ set pin functions
	mov r0,#7	@ CE1
	mov r1,#BCM2536_GPFSEL_ALT0
	bl BCM2536_GPIO_PinSelFun

	mov r0,#8	@ CE0
	mov r1,#BCM2536_GPFSEL_ALT0
	bl BCM2536_GPIO_PinSelFun

	mov r0,#9	@ MISO
	mov r1,#BCM2536_GPFSEL_ALT0
	bl BCM2536_GPIO_PinSelFun

	mov r0,#10 @ MOSI
	mov r1,#BCM2536_GPFSEL_ALT0
	bl BCM2536_GPIO_PinSelFun

	mov r0,#11 @ CLK
	mov r1,#BCM2536_GPFSEL_ALT0
	bl BCM2536_GPIO_PinSelFun

.if DEBUG>0
	bl BCM2536_GPIO_PinSelDump
.endif

	@ initialize CS
	mov r0, #0
	str r0,[r4,#BCM2835_SPI0_CS_OFFSET]
	@ clear fifos
	mov r0, #BCM2835_SPI0_CS_CLEAR
	str r0,[r4,#BCM2835_SPI0_CS_OFFSET]
	@ set CS-Polarity of cs0 and cs1 to 0
	ldr r0,[r4,#BCM2835_SPI0_CS_OFFSET]
	bic r0,r0,#BCM2835_SPI0_CS_CSPOL0
	bic r0,r0,#BCM2835_SPI0_CS_CSPOL1
	str r0,[r4,#BCM2835_SPI0_CS_OFFSET]
	@ set clock divider
	mov r0,#64 @ 3.9 MhZ on RPi2
	str r0,[r4,#BCM2835_SPI0_CLK_OFFSET]
	@ set data mode to mode 0 (cpol=0, cpha=0) and select CS0 (CS=0)
	ldr r0,[r4,#BCM2835_SPI0_CS_OFFSET]
	bic r0,r0,#BCM2835_SPI0_CS_CPOL
	bic r0,r0,#BCM2835_SPI0_CS_CPHA
	bic r0,r0,#BCM2835_SPI0_CS_CS
	str r0,[r4,#BCM2835_SPI0_CS_OFFSET]

	mov r5,#3	@ send 3 byte
	ldr r6,=spi_msg @ message

forever:
	@ clear fifos and set TA
	ldr r0,[r4,#BCM2835_SPI0_CS_OFFSET]
	orr r0,r0,#BCM2835_SPI0_CS_CLEAR
	orr r0,r0,#BCM2835_SPI0_CS_TA
	str r0,[r4,#BCM2835_SPI0_CS_OFFSET]

	mov r2,#0   @ r2=txcnt
	mov r3,#0   @ r3=rxcnt
	mov r8,#0   @ r8=result
poll: @ while (txcnt < len || rxcnt < len) {
	cmp r2,r5
	blt send
	cmp r3,r5
	bge wait_for_done

send: @ while (TXD & txcnt < len) {
	ldr r0,[r4,#BCM2835_SPI0_CS_OFFSET]
	tst r0, #BCM2835_SPI0_CS_TXD
	beq rcv  // fifo full -> TXD=0 -> Z=1, read
	cmp r2,r5
	bge rcv

	ldrb r0,[r6,r2]
	@ ldrb r0,[r7,r0] @ invert
	str r0,[r4,#BCM2835_SPI0_FIFO_OFFSET] @ send
.if DEBUG>0
	push {r0-r3}
	bl PrintHex
	mov r0,#'>'
	bl PrintChar
	pop {r0-r3}
.endif
	add r2,r2,#1 @ advance txcnt
	bal send @ }
rcv: @ while (RXD & rxcnt < len) {
	ldr r0,[r4,#BCM2835_SPI0_CS_OFFSET]
	tst r0, #BCM2835_SPI0_CS_RXD
	beq e_rcv // Z=1, nothing received
	cmp r3,r5
	bge e_rcv

	ldr r0,[r4,#BCM2835_SPI0_FIFO_OFFSET] @ read
.if DEBUG>0
	push {r0-r3}
	bl PrintHex
	mov r0,#'<'
	bl PrintChar
	pop {r0-r3}
.endif
	and r0,r0,#0xFF
	@ ldrb r0,[r7,r0] @ invert
	orr r8,r0,r8,lsl #8 @ store in r8

	add r3,r3,#1 @ advance rxcnt
	bal rcv @ }
e_rcv:
	bal poll @ }

wait_for_done:
	ldr r0,[r4,#BCM2835_SPI0_CS_OFFSET] @ wait for done
	tst r0,#BCM2835_SPI0_CS_DONE
	beq wait_for_done

	ldr r0,[r4,#BCM2835_SPI0_CS_OFFSET]
	bic r0,r0,#BCM2835_SPI0_CS_TA
	str r0,[r4,#BCM2835_SPI0_CS_OFFSET]

	mov r0,r8
	bl PrintHex
	bl PrintNL

	@ TMP35 	V = 10 mV/°C, 0°C=0 mV
	@ MCP3008:  D = 1024 x V / V_ref
.equ DC_1, 2
.equ DC_5, 10
.equ DC_10, 20
.equ DC_REF,0xB0 @ = 18 °C
	cmp r8,#DC_REF+DC_1
	movlt r9,#GPIO_GREEN
	blt light
	cmp r8,#DC_REF+DC_5
	movlt r9,#GPIO_YELLOW
	blt light
	mov r9,#GPIO_RED
light:
	mov r0,#GPIO_GREEN
	bl BCM2536_GPIO_PinClr
	mov r0,#GPIO_YELLOW
	bl BCM2536_GPIO_PinClr
	mov r0,#GPIO_RED
	bl BCM2536_GPIO_PinClr
	mov r0,r9
	bl BCM2536_GPIO_PinSet

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
