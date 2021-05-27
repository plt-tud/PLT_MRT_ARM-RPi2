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
 *  @brief: SPIBasics: Auslesen des Kanals 0 des ADCs via SPI
 */

.global main
.include "BCM2836.h"

.data
.balign 4
spi_msg:   .byte 0x01, 0x80, 0x00
.balign 4
spi_reply: .byte 0x00, 0x00, 0x00

.text
.align
.func main
main:
	push {r4-r9,fp,lr} // safe 8 regs
	add fp,sp,#(8-1)*4 // fp <- lr // stack

	bl BCM2836_GPIO_Open
	cmp r0,#0
	bne main_err_open

  // Template: Section
  main_spi_init:
   bl BCM2836_SPI0_GetBase
    mov r4, r0 // r4 = SPI Base

    // set functions of pins 7-11 to alternate 0 mode, which enables SPI mode (see BCM2835 datasheet page 102)
    mov r0,#7 					// pin 7: CE1 - chip enable 1
    mov r1,#BCM2836_GPFSEL_ALT0
    bl BCM2836_GPIO_PinSelFun

    mov r0,#8 					// pin 8: CE0 - chip enable 0
    mov r1,#BCM2836_GPFSEL_ALT0
    bl BCM2836_GPIO_PinSelFun

    mov r0,#9 					// pin 9: MISO - Master In Slave Out
    mov r1,#BCM2836_GPFSEL_ALT0
    bl BCM2836_GPIO_PinSelFun

    mov r0,#10 					// pin 10: MOSI - Master Out Slave In
    mov r1,#BCM2836_GPFSEL_ALT0
    bl BCM2836_GPIO_PinSelFun

    mov r0,#11 					// pin 11: CLK - Clock
    mov r1,#BCM2836_GPFSEL_ALT0
    bl BCM2836_GPIO_PinSelFun

    // initialize CS
    mov r0, #0
    str r0,[r4,#BCM2836_SPI0_CS_OFFSET]

	// clear fifos
    mov r0,    #BCM2836_SPI0_CS_CLEAR		// bits 5-4 = 11:	clear rx and tx fifos
    str r0,[r4,#BCM2836_SPI0_CS_OFFSET]

	// set CS-Polarity of cspol0 to 0
    ldr r0,[r4,#BCM2836_SPI0_CS_OFFSET]
    bic r0,r0, #BCM2836_SPI0_CS_CSPOL0		// bit 21 = 0:		set chip select 0 to active low
    str r0,[r4,#BCM2836_SPI0_CS_OFFSET]

    // set data mode to mode 0 (cpol=0, cpha=0) and select CS0 (CS=0)
    ldr r0,[r4,#BCM2836_SPI0_CS_OFFSET]
    bic r0,r0,#BCM2836_SPI0_CS_CPOL			// bit 3 = 0:		rest state of clock is LOW
    bic r0,r0,#BCM2836_SPI0_CS_CPHA			// bit 2 = 0:		first CLK transition is in middle of data bit
    bic r0,r0,#BCM2836_SPI0_CS_CS			// bit 0-1 = 00:	use chip select 0
    str r0,[r4,#BCM2836_SPI0_CS_OFFSET]

    // set clock divider
    mov r0,#128 							// 1.9 MhZ on RPi2
    str r0,[r4,#BCM2836_SPI0_CLK_OFFSET]
  main_spi_init_done:

	mov r5,#3	          // send 3 byte
	ldr r6,=spi_msg     // message

  /* start our RX/RX Algorithm */

  main_forever:
    // clear fifos and set TA
    // CS = CS | (CLEAR|TA)
    ldr r0,[r4,#BCM2836_SPI0_CS_OFFSET]
    orr r0,r0, #BCM2836_SPI0_CS_CLEAR		// bit 4-5 = 11:	clear rx and tx FIFO
    orr r0,r0, #BCM2836_SPI0_CS_TA			// bit 7 = 1:		transfer is now active
    str r0,[r4,#BCM2836_SPI0_CS_OFFSET]

    mov r7, #3  			// dataSz; 				Message is 3 bytes long
    ldr r8, =spi_msg  		// r8 = *txdata_ptr; 	Message begins at =spi_msg
    ldr r9, =spi_reply  	// r9 = *rxdata_ptr;	Pointer to memory location where received date is stored

    // r4 = SPI Base
    mov r5, #0  // r5: rxDataCount = 0
    mov r6, #0  // r6: txDataCount = 0

    main_SPI0_Send_rxtxloop_start:
      // while (rxdata:r5 < dataSz:r7) ...
      cmp r5, r7						// if (rxdata >= dataSz)
      bge main_SPI0_Send_rxtxloop_end	// 	then jump to main_SPI0_Send_rxtxloop_end

      main_SPI0_Send_rxtxloop_rx:
        // if (rxBuffer != Empty) {
        ldr r0,[r4,#BCM2836_SPI0_CS_OFFSET]
        tst r0, #BCM2836_SPI0_CS_RXD_FIFO_NOTEMPTY	// Check if RXD (bit 17) is set (tst - test if bits are set).
        beq main_SPI0_Send_rxtxloop_rx_end			// "eq" condition tests for Z == 1, so if bit 17 is set, then
        											// tst returns 1, which is not 0, which means that RX FIFO is
        											// not empty.

        // copy(SPI RX Buffer to rxdata[rxData++])
        ldr r0,[r4,#BCM2836_SPI0_FIFO_OFFSET] 		// read FIFO register
        and r0,r0,#0xFF								// discard everything except the first byte
        strb r0,[r9, r5]							// store read byte at rxdata_ptr
        add r5, r5, #1 // rxData++					// increment rxdata_ptr
      main_SPI0_Send_rxtxloop_rx_end: // }

      // Template Selektion
      main_SPI0_Send_rxtxloop_tx:
        // if (txdata:r6 < dataSz:r7 ...
        cmp r6, r7									// if (txDataCount >= dataSz)
        bge main_SPI0_Send_rxtxloop_tx_end			// 	then jump to main_SPI0_Send_rxtxloop_tx_end
        //  && txBuffer != Full ....
        ldr r0,[r4,#BCM2836_SPI0_CS_OFFSET]			// load CS register
        tst r0, #BCM2836_SPI0_CS_TXD_FIFO_FULL		// Test if TXD (bit 18) is set to 0 (= FIFO full) and jump to
        beq main_SPI0_Send_rxtxloop_tx_end			// main_SPI0_Send_rxtxloop_tx_end if that is the case.
        // ... ) {

        // copy(txdata[txData++] to SPI TX Buffer);
        ldrb r0, [r8, r6]							// load byte from mem(txData_ptr + txDataCount)
        str  r0, [r4, #BCM2836_SPI0_FIFO_OFFSET]	// store byte onto FIFO
        add  r6, r6, #1  // txData++				// intcrement txData_ptr
      main_SPI0_Send_rxtxloop_tx_end: //}

      b main_SPI0_Send_rxtxloop_start
    main_SPI0_Send_rxtxloop_end:

    // while (!DONE) { wait }
    main_SPI0_Send_wait_for_done:					// wait for done
    ldr r0,[r4,#BCM2836_SPI0_CS_OFFSET]				// load CS register
    tst r0,#BCM2836_SPI0_CS_DONE					// Test if DONE (bit 16) is not yet set to 1 and
    beq main_SPI0_Send_wait_for_done				// continue waiting when Z is 1 (-> DONE is 0).

    ldr r0,[r4,#BCM2836_SPI0_CS_OFFSET]
    bic r0,r0,#BCM2836_SPI0_CS_TA					// bit 7 = 0:	transfer is complete and not active anymore
    str r0,[r4,#BCM2836_SPI0_CS_OFFSET]

    // FIXME: EABI: SP muss an 8-Byte-Grenze ausgerichtet sein! (externe Schnittstelle)
    mov r0,#1 // EABI: first parameter (r0) is 1
    bl sleep  // call function "sleep" from libc to let the program wait for 1 second

    b main_forever
  main_forever_done:

main_exit:
	bl BCM2836_GPIO_Close

  ldmfd sp!,{r4-r10,r11,lr}
  bx lr

main_err_open:
  mov r0, #1
  b   exit
.endfunc
