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

    // set pin functions to alternate0
    mov r0,#7 // CE1
    mov r1,#BCM2836_GPFSEL_ALT0
    bl BCM2836_GPIO_PinSelFun

    mov r0,#8 // CE0
    mov r1,#BCM2836_GPFSEL_ALT0
    bl BCM2836_GPIO_PinSelFun

    mov r0,#9 // MISO
    mov r1,#BCM2836_GPFSEL_ALT0
    bl BCM2836_GPIO_PinSelFun

    mov r0,#10 // MOSI
    mov r1,#BCM2836_GPFSEL_ALT0
    bl BCM2836_GPIO_PinSelFun

    mov r0,#11 // CLK
    mov r1,#BCM2836_GPFSEL_ALT0
    bl BCM2836_GPIO_PinSelFun

    // initialize CS
    mov r0, #0
    str r0,[r4,#BCM2836_SPI0_CS_OFFSET]

    // clear fifos
    mov r0,    #BCM2836_SPI0_CS_CLEAR
    str r0,[r4,#BCM2836_SPI0_CS_OFFSET]

    // set CS-Polarity of cs0 and cs1 to 0
    ldr r0,[r4,#BCM2836_SPI0_CS_OFFSET]
    bic r0,r0, #BCM2836_SPI0_CS_CSPOL0
    str r0,[r4,#BCM2836_SPI0_CS_OFFSET]

    // set data mode to mode 0 (cpol=0, cpha=0) and select CS0 (CS=0)
    ldr r0,[r4,#BCM2836_SPI0_CS_OFFSET]
    bic r0,r0,#BCM2836_SPI0_CS_CPOL
    bic r0,r0,#BCM2836_SPI0_CS_CPHA
    bic r0,r0,#BCM2836_SPI0_CS_CS
    str r0,[r4,#BCM2836_SPI0_CS_OFFSET]

    // set clock divider
    mov r0,#128 // 1.9 MhZ on RPi2
    str r0,[r4,#BCM2836_SPI0_CLK_OFFSET]
  main_spi_init_done:

	mov r5,#3	          // send 3 byte
	ldr r6,=spi_msg     // message

  /* start our RX/RX Algorithm */

  main_forever:
    // clear fifos and set TA
    // CS = CS | (CLEAR|TA)
    ldr r0,[r4,#BCM2836_SPI0_CS_OFFSET]
    orr r0,r0, #BCM2836_SPI0_CS_CLEAR
    orr r0,r0, #BCM2836_SPI0_CS_TA
    str r0,[r4,#BCM2836_SPI0_CS_OFFSET]

    mov r7, #3  // dataSz; Unsere Nachricht ist 3 Byte gross
    ldr r8, =spi_msg  // r8 = *txdata_ptr; Und beginnt hier
    ldr r9, =spi_reply  // r9 = *rxdata_ptr

    // r4: Ist schon unsere SPI BASADDR
    mov r5, #0  // rxDataCount:r5 = 0
    mov r6, #0  // rxDataCount:r6 = 0
    // Template: Ablehnende Schleife
    main_SPI0_Send_rxtxloop_start:
      // while (rxdata:r5 < dataSz:r7) ...
      cmp r5, r7
      bge main_SPI0_Send_rxtxloop_end

      // Template Selektion
      main_SPI0_Send_rxtxloop_rx:
        // if (rxBuffer != Empty) {
        ldr r0,[r4,#BCM2836_SPI0_CS_OFFSET]
        tst r0, #BCM2836_SPI0_CS_RXD_FIFO_NOTEMPTY
        beq main_SPI0_Send_rxtxloop_rx_end

        // copy(SPI RX Buffer to rxdata[rxData++])
        ldr r0,[r4,#BCM2836_SPI0_FIFO_OFFSET] // read
        and r0,r0,#0xFF
        strb r0,[r9, r5]
        add r5, r5, #1 // rxData++
      main_SPI0_Send_rxtxloop_rx_end: // }

      // Template Selektion
      main_SPI0_Send_rxtxloop_tx:
        // if (txdata:r6 < dataSz:r7 ...
        cmp r6, r7
        bge main_SPI0_Send_rxtxloop_tx_end
        //  && txBuffer != Full ....
        ldr r0,[r4,#BCM2836_SPI0_CS_OFFSET]
        tst r0, #BCM2836_SPI0_CS_TXD_FIFO_FULL
        beq main_SPI0_Send_rxtxloop_tx_end
        // ... ) {

        // copy(txdata[txData++] to SPI TX Buffer);
        ldrb r0, [r8, r6]
        str  r0, [r4, #BCM2836_SPI0_FIFO_OFFSET]
        add  r6, r6, #1  // txData++
      main_SPI0_Send_rxtxloop_tx_end: //}

      b main_SPI0_Send_rxtxloop_start
    main_SPI0_Send_rxtxloop_end:

    // while (!DONE) { wait }
    main_SPI0_Send_wait_for_done:
    ldr r0,[r4,#BCM2836_SPI0_CS_OFFSET] // wait for done
    tst r0,#BCM2836_SPI0_CS_DONE
    beq main_SPI0_Send_wait_for_done

    ldr r0,[r4,#BCM2836_SPI0_CS_OFFSET]
    bic r0,r0,#BCM2836_SPI0_CS_TA
    str r0,[r4,#BCM2836_SPI0_CS_OFFSET]

    // FIXME: EABI: SP muss an 8-Byte-Grenze ausgerichtet sein! (externe Schnittstelle)
    mov r0,#1 // EABI-konforme Übergabe des 0ten Parameters
    bl sleep  // Funktion der standard C-Bibliothek (clib)

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
