.set DEBUG,0
.global main
.type main, %function

.equ GPIO_RED,		26
.equ GPIO_YELLOW,	27
.equ GPIO_GREEN, 	22

.include "BCM2536.h"
.set BCM2835_SPI0_CS_OFFSET, 0x00 @ SPI Master Control and Status
.set BCM2835_SPI0_FIFO_OFFSET, 0x04 @ SPI Master TX and RX FIFOs
.set BCM2835_SPI0_CLK_OFFSET, 0x08 @ SPI Master Clock Divider
.set BCM2835_SPI0_DLEN_OFFSET, 0x0c @ SPI Master Data Length
.set BCM2835_SPI0_LTOH_OFFSET, 0x10 @ SPI LOSSI mode TOH
.set BCM2835_SPI0_DC_OFFSET, 0x14 @ SPI DMA DREQ Controls

.set BCM2835_SPI0_CS_LEN_LONG, 0x02000000 /*!< Enable Long data word in Lossi mode if DMA_LEN is set */
.set BCM2835_SPI0_CS_DMA_LEN, 0x01000000 /*!< Enable DMA mode in Lossi mode */
.set BCM2835_SPI0_CS_CSPOL2, 0x00800000 /*!< Chip Select 2 Polarity */
.set BCM2835_SPI0_CS_CSPOL1, 0x00400000 /*!< Chip Select 1 Polarity */
.set BCM2835_SPI0_CS_CSPOL0, 0x00200000 /*!< Chip Select 0 Polarity */
.set BCM2835_SPI0_CS_RXF, 0x00100000 /*!< RXF - RX FIFO Full */
.set BCM2835_SPI0_CS_RXR, 0x00080000 /*!< RXR RX FIFO needs Reading (full) */
.set BCM2835_SPI0_CS_TXD, 0x00040000 /*!< TXD TX FIFO can accept Data */
.set BCM2835_SPI0_CS_RXD, 0x00020000 /*!< RXD RX FIFO contains Data */
.set BCM2835_SPI0_CS_DONE, 0x00010000 /*!< Done transfer Done */
.set BCM2835_SPI0_CS_TE_EN, 0x00008000 /*!< Unused */
.set BCM2835_SPI0_CS_LMONO, 0x00004000 /*!< Unused */
.set BCM2835_SPI0_CS_LEN, 0x00002000 /*!< LEN LoSSI enable */
.set BCM2835_SPI0_CS_REN, 0x00001000 /*!< REN Read Enable */
.set BCM2835_SPI0_CS_ADCS, 0x00000800 /*!< ADCS Automatically Deassert Chip Select */
.set BCM2835_SPI0_CS_INTR, 0x00000400 /*!< INTR Interrupt on RXR */
.set BCM2835_SPI0_CS_INTD, 0x00000200 /*!< INTD Interrupt on Done */
.set BCM2835_SPI0_CS_DMAEN, 0x00000100 /*!< DMAEN DMA Enable */
.set BCM2835_SPI0_CS_TA, 0x00000080 /*!< Transfer Active */
.set BCM2835_SPI0_CS_CSPOL, 0x00000040 /*!< Chip Select Polarity */
.set BCM2835_SPI0_CS_CLEAR, 0x00000030 /*!< Clear FIFO Clear RX and TX */
.set BCM2835_SPI0_CS_CLEAR_RX, 0x00000020 /*!< Clear FIFO Clear RX  */
.set BCM2835_SPI0_CS_CLEAR_TX, 0x00000010 /*!< Clear FIFO Clear TX  */
.set BCM2835_SPI0_CS_CPOL, 0x00000008 /*!< Clock Polarity */
.set BCM2835_SPI0_CS_CPHA, 0x00000004 /*!< Clock Phase */
.set BCM2835_SPI0_CS_CS, 0x00000003 /*!< Chip Select */

.include "SYSCALL.h"

.data
.align
bcm2536_msg_err_open: .asciz "error initializing bcm2536"
.set bcm2536_mln_err_open, . - bcm2536_msg_err_open
.align

bcm2536_brt:
.byte 0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0
.byte 0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0
.byte 0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8
.byte 0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8
.byte 0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4
.byte 0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4
.byte 0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec
.byte 0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc
.byte 0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2
.byte 0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2
.byte 0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea
.byte 0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa
.byte 0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6
.byte 0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6
.byte 0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee
.byte 0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe
.byte 0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1
.byte 0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1
.byte 0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9
.byte 0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9
.byte 0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5
.byte 0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5
.byte 0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed
.byte 0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd
.byte 0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3
.byte 0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3
.byte 0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb
.byte 0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb
.byte 0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7
.byte 0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7
.byte 0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef
.byte 0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff

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
