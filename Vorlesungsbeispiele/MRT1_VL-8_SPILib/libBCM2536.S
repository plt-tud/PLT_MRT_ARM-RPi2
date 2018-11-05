@ Header
.globl BCM2536_GPIO_Open, BCM2536_GPIO_Close, BCM2536_GPIO_PinSelFun, BCM2536_GPIO_PinSet, BCM2536_GPIO_PinClr, BCM2536_GPIO_PinSelDump
.type BCM2536_GPIO_Init,%function
.type BCM2536_GPIO_Close,%function
.type BCM2536_GPIO_PinSelFun,%function
.type BCM2536_GPIO_PinSet,%function
.type BCM2536_GPIO_PinClr,%function
.type BCM2536_GPIO_PinSelDump,%function

@ Definitionen
// Aus Bootloader, Mapping v. physischem Speicher 0x7Exxxxx --> 0x3fxxxxxx
.equ BCM2536_PERI_BASE,         0x3f000000

// Aus BCM2536 Datenblatt, Abschnitt GPIOs
.equ BCM2536_GPIO_BASEOFFSET,   0x200000
.equ BCM2536_GPIO_LASTADDRESS,  0x2000B4
.equ BCM2536_GPIO_MEMSIZE,      0x4100 // Must be >=4k according to manual !
.equ BCM2536_GPIO_BASE, BCM2536_PERI_BASE + BCM2536_GPIO_BASEOFFSET

.equ BCM2536_GPFSEL_OFFSET, 0
.equ BCM2536_GPSET_OFFSET, 0x1C
.equ BCM2536_GPCLR_OFFSET, 0x28

.equ BCM2536_SPI0_BASEOFFSET, 0x204000

.set BCM2835_SPI0_CS_OFFSET, 0x00 @ SPI Master Control and Status
.set BCM2835_SPI0_FIFO_OFFSET, 0x04 @ SPI Master TX and RX FIFOs
.set BCM2835_SPI0_CLK_OFFSET, 0x08 @ SPI Master Clock Divider
.set BCM2835_SPI0_DLEN_OFFSET, 0x0c @ SPI Master Data Length
.set BCM2835_SPI0_LTOH_OFFSET, 0x10 @ SPI LOSSI mode TOH
.set BCM2835_SPI0_DC_OFFSET, 0x14 @ SPI DMA DREQ Controls

.set BCM2835_SPI0_CS_LEN_LONG_MSK, 0x02000000 /*!< Enable Long data word in Lossi mode if DMA_LEN is set */
.set BCM2835_SPI0_CS_DMA_LEN_MSK, 0x01000000 /*!< Enable DMA mode in Lossi mode */
.set BCM2835_SPI0_CS_CSPOL2_MSK, 0x00800000 /*!< Chip Select 2 Polarity */
.set BCM2835_SPI0_CS_CSPOL1_MSK, 0x00400000 /*!< Chip Select 1 Polarity */
.set BCM2835_SPI0_CS_CSPOL0_MSK, 0x00200000 /*!< Chip Select 0 Polarity */
.set BCM2835_SPI0_CS_RXF_MSK, 0x00100000 /*!< RXF - RX FIFO Full */
.set BCM2835_SPI0_CS_RXR_MSK, 0x00080000 /*!< RXR RX FIFO needs Reading (full) */
.set BCM2835_SPI0_CS_TXD_MSK, 0x00040000 /*!< TXD TX FIFO can accept Data */
.set BCM2835_SPI0_CS_RXD_MSK, 0x00020000 /*!< RXD RX FIFO contains Data */
.set BCM2835_SPI0_CS_DONE_MSK, 0x00010000 /*!< Done transfer Done */
.set BCM2835_SPI0_CS_TE_EN_MSK, 0x00008000 /*!< Unused */
.set BCM2835_SPI0_CS_LMONO_MSK, 0x00004000 /*!< Unused */
.set BCM2835_SPI0_CS_LEN_MSK, 0x00002000 /*!< LEN LoSSI enable */
.set BCM2835_SPI0_CS_REN_MSK, 0x00001000 /*!< REN Read Enable */
.set BCM2835_SPI0_CS_ADCS_MSK, 0x00000800 /*!< ADCS Automatically Deassert Chip Select */
.set BCM2835_SPI0_CS_INTR_MSK, 0x00000400 /*!< INTR Interrupt on RXR */
.set BCM2835_SPI0_CS_INTD_MSK, 0x00000200 /*!< INTD Interrupt on Done */
.set BCM2835_SPI0_CS_DMAEN_MSK, 0x00000100 /*!< DMAEN DMA Enable */
.set BCM2835_SPI0_CS_TA_MSK, 0x00000080 /*!< Transfer Active */
.set BCM2835_SPI0_CS_CSPOL_MSK, 0x00000040 /*!< Chip Select Polarity */
.set BCM2835_SPI0_CS_CLEAR_MSK, 0x00000030 /*!< Clear FIFO Clear RX and TX */
.set BCM2835_SPI0_CS_CLEAR_RX_MSK, 0x00000020 /*!< Clear FIFO Clear RX  */
.set BCM2835_SPI0_CS_CLEAR_TX_MSK, 0x00000010 /*!< Clear FIFO Clear TX  */
.set BCM2835_SPI0_CS_CPOL_MSK, 0x00000008 /*!< Clock Polarity */
.set BCM2835_SPI0_CS_CPHA_MSK, 0x00000004 /*!< Clock Phase */
.set BCM2835_SPI0_CS_CS_MSK, 0x00000003 /*!< Chip Select */


.equ BCM2536_SPI1_BASEOFFSET, 0x215000
.equ BCM2536_SPI2_BASEOFFSET, 0x215080

.include "SYSCALL.h"

.data
.balign 4
dev_mem_filename: 	.asciz "/dev/mem"
.balign 4
dev_mem_gpio_fd: 	.word 0	@ holds fd to /dev/mem
dev_mem_gpio_base_addr:	.word 0

.text
.align 4

BCM2536_GPIO_Open:
  push {r4-r7,fp,lr}	// safe relevant registers (6)
  add fp,sp,#((6-1)*4)	// set frame pointer to lr at bottom of local stack

  // dev_mem_gpio_fd = open(/dev/mem,  O_RDWR|O_SYNC, 0)
  ldr r0, =dev_mem_filename
  ldr r1, =OPEN_PARAMETER_SYNC_RDWR
  mov r2, #0
  mov r7, #SYSCALL_OPEN
  swi #0
  ldr r1,=dev_mem_gpio_fd	@ save file-handle at =dev_mem_gpio_fd
  str r0,[r1]
  cmp r0,#0
  ble exit

  // mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
  // dev_mem_gpio_base_addr = mmap(NULL, gpio_speicherbereich, PROT_READ|PROT_WRITE, MAP_SHARED)
  mov r4, r0
  mov r0, #0
  mov r1, #BCM2536_GPIO_MEMSIZE
  mov r2, #MMAP_PARAMETER_PROT_READ_WRITE
  mov r3, #MMAP_PARAMETER_MAP_SHARED
  ldr r5, =BCM2536_GPIO_BASE        // mmap benutzt 4k bloecke und multipliziert unsere adresse intern; wir muessen etwas schieben
  lsr r5, r5, #12                   // aus 0x3f200000 sollte 0x3f200 werden...
  mov r7, #SYSCALL_MMAP2
  swi #0
  ldr r1,=dev_mem_gpio_base_addr	// save address at =dev_mem_gpio_addr
  str r0,[r1]
  cmp r0,#0
  movne r0,#0
exit:
  pop {r4-r7,fp,pc}					// restore saved registers

@ BCM2536_GPIO_PinSelFun(GPIO-Pin, FunctionSelection)
BCM2536_GPIO_PinSelFun:
	push {r4,r5,fp,lr} // safe 4 registers
	add fp,sp,#((4-1)*4)

	// r2 <- Index of GPFSELn register; r0 <- 10⁰ remainder of pin number
	mov r2,#0
loop:
	cmp r0,#10			// while ( r0 < 10)
	blt done			// {
	add r2,r2,#1		//   r2 <- r2 + 1
	sub r0,r0,#10		//   r0 <- r0 - 10
	bal loop			// }

done: add r0,r0,r0,lsl #1	// R0 <- R0 * 3

	ldr r3,=dev_mem_gpio_base_addr
	ldr r3,[r3]		// R3 <- address of gpio_base

	ldr r4,[r3,r2,LSL #2] 	// R4 <- [ GPFSEL<r2> ]

	mov r5,#0b111
	bic r4,r4,r5,LSL R0	// R4 <- R4 AND NOT ( 0b111 << R0)
	orr r4,r4,r1,LSL R0 // R4 <- R4 ORR R1

	str r4,[r3,r2,LSL #2]	// R4 -> [ GPFSEL<r2> ]

	pop {r4,r5,fp,pc}	// restore and return

@ void BCM2536_GPIO_PinSet(GPIO_Pin)
BCM2536_GPIO_PinSet:
	push {fp,lr}
	add fp,sp,#4

	// r1 <- Offset to GPSET0 or GPSET1
	mov r1,#BCM2536_GPSET_OFFSET
	cmp r0,#31		@ if (R0 > 31)
	addgt r1,r1,#4	@	R1 <- R1 + 4

	// r0 <- 1 << ( pin % 32)
	and r0, r0, #0x1F	@ pin % 32
	mov r3, #1
	lsl r0, r3, r0		@ 1 << ( pin % 32)

	// r2 <- gpio_base_addr
	ldr r2,=dev_mem_gpio_base_addr
	ldr r2,[r2]

	// r0 -> [base + offset]
	str r0,[r2,r1]

	pop {fp,pc} // restore saved registers and return

@ void BCM2536_GPIO_PinClr(GPIO_Pin)
BCM2536_GPIO_PinClr:
	push {fp,lr}		// safe registers
	add fp,sp,#((2-1)*4)	// set frame pointer to lr at bottom of stack

	// r1 <- Offset to GPCLR0 or GPCLR1
	mov r1,#BCM2536_GPCLR_OFFSET
	cmp r0,#31		@ if (R0 > 31)
	addgt r1,r1,#4	@	R1 <- R1 + 4

	// r0 <- ( b1 << ( PIN % 32 ))
	and r0, r0, #0x1F
	mov r3, #1
	mov r0, r3, LSL r0

	// r2 <- gpio_base_addr
	ldr r2,=dev_mem_gpio_base_addr
	ldr r2,[r2]

	// r0 -> [gpio_base_addr + offset]
	str r0,[r2,r1]

	pop {fp,pc} // restore & return
  
BCM2536_GPIO_Close:
	push {r4,r7,fp,lr}	// safe relevant registers (4)
	add fp,sp,#((4-1)*4)// set frame pointer to lr at bottom of stack

  	// munmap
	ldr r0,=dev_mem_gpio_base_addr
	ldr r0,[r0]
	mov r1,#BCM2536_GPIO_MEMSIZE
	mov r7,#SYSCALL_MUNMAP
	swi #0
  
	// close
	ldr r0,=dev_mem_gpio_fd
	ldr r0,[r0]
	mov r7, #SYSCALL_CLOSE
	swi #0

	pop {r4,r7,fp,pc} // restore & return

BCM2536_GPIO_PinSelDump:
	push {r4,r5,fp,lr} // safe 6 registers
	add fp,sp,#((4-1)*4)

	ldr r5,=dev_mem_gpio_base_addr 	// R5 <- address of gpio_base
	ldr r5,[r5]

	mov r4,#0	@ for (r4 <- 0;r4 < 6; r4 <- ++) {
l_reg: cmp r4,#6
	bge e_reg

	ldr r0,[r5,r4,LSL #2]	@ r0 <- [ GPFSEL<r4> ]
	bl PrintOct

	mov r0,#10
	bl PrintChar
	add r4,r4,#1
	bal l_reg

e_reg:	mov r0,#10
	bl PrintChar
	pop {r4,r5,fp,pc}	// restore and return

.globl BCM2536_GPIO_GetBase
.type BCM2536_GPIO_GetBase,%function
BCM2536_GPIO_GetBase:
  	ldr r0,=dev_mem_gpio_base_addr
  	ldr r0,[r0]
	mov pc,lr

.globl BCM2536_SPI0_GetBase
.type BCM2536_SPI0_GetBase,%function
BCM2536_SPI0_GetBase:
  	ldr r0,=dev_mem_gpio_base_addr
  	ldr r0,[r0]
  	add r0,r0,#(BCM2536_SPI0_BASEOFFSET-BCM2536_GPIO_BASEOFFSET)
	mov pc,lr
