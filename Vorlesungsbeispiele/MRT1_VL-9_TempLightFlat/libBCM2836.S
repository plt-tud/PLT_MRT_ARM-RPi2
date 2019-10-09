@ Header
.globl BCM2836_GPIO_GetBase, BCM2836_GPIO_Open, BCM2836_GPIO_Close, BCM2836_GPIO_PinSelFun, BCM2836_GPIO_PinSet, BCM2836_GPIO_PinClr, BCM2836_GPIO_PinSelDump

.type  BCM2836_GPIO_Init,%function
.type  BCM2836_GPIO_Close,%function
.type  BCM2836_GPIO_PinSelFun,%function
.type  BCM2836_GPIO_PinSet,%function
.type  BCM2836_GPIO_PinClr,%function
.type  BCM2836_GPIO_PinSelDump,%function
.type  BCM2836_GPIO_GetBase,%function

.globl BCM2836_SPI0_GetBase,BCM2836_SPI0_Init,BCM2836_SPI0_Send
.type  BCM2836_SPI0_GetBase,%function
.type  BCM2836_SPI0_Init,%function
.type  BCM2836_SPI0_Send,%function

.include "SYSCALL.h"
// We share these constants with non-library sources
.include "BCM2836_constants.h"
.include "BCM2836_GPIO_constants.h"
.include "BCM2836_SPI_constants.h"

/*********** Data ***********/
.data
.balign 4
dev_mem_filename: 	.asciz "/dev/mem"
.balign 4
dev_mem_gpio_fd: 	      .word 0	@ holds fd to /dev/mem
dev_mem_gpio_base_addr:	.word 0


/********** Text ************/
.text
.align 4

/*********************
 * GPIO Functions
 *********************/

BCM2836_GPIO_GetBase:
  ldr r0, =dev_mem_gpio_base_addr
  ldr r0, [r0]
  mov pc, lr

BCM2836_GPIO_Open:
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
  mov r1, #BCM2836_GPIO_MEMSIZE
  mov r2, #MMAP_PARAMETER_PROT_READ_WRITE
  mov r3, #MMAP_PARAMETER_MAP_SHARED
  ldr r5, =BCM2836_GPIO_BASE        // mmap benutzt 4k bloecke und multipliziert unsere adresse intern; wir muessen etwas schieben
  lsr r5, r5, #12                   // aus 0x3f200000 sollte 0x3f200 werden...
  mov r7, #SYSCALL_MMAP2
  swi #0
  ldr r1,=dev_mem_gpio_base_addr	// save address at =dev_mem_gpio_addr
  str r0,[r1]
  cmp r0,#0
  movne r0,#0
exit:
  pop {r4-r7,fp,pc}					// restore saved registers

@ BCM2836_GPIO_PinSelFun(GPIO-Pin, FunctionSelection)
BCM2836_GPIO_PinSelFun:
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

@ void BCM2836_GPIO_PinSet(GPIO_Pin)
BCM2836_GPIO_PinSet:
	push {fp,lr}
	add fp,sp,#4

	// r1 <- Offset to GPSET0 or GPSET1
	mov r1,#BCM2836_GPSET_OFFSET
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

@ void BCM2836_GPIO_PinClr(GPIO_Pin)
BCM2836_GPIO_PinClr:
	push {fp,lr}		// safe registers
	add fp,sp,#((2-1)*4)	// set frame pointer to lr at bottom of stack

	// r1 <- Offset to GPCLR0 or GPCLR1
	mov r1,#BCM2836_GPCLR_OFFSET
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
  
BCM2836_GPIO_Close:
	push {r4,r7,fp,lr}	// safe relevant registers (4)
	add fp,sp,#((4-1)*4)// set frame pointer to lr at bottom of stack

  	// munmap
	ldr r0,=dev_mem_gpio_base_addr
	ldr r0,[r0]
	mov r1,#BCM2836_GPIO_MEMSIZE
	mov r7,#SYSCALL_MUNMAP
	swi #0
  
	// close
	ldr r0,=dev_mem_gpio_fd
	ldr r0,[r0]
	mov r7, #SYSCALL_CLOSE
	swi #0

	pop {r4,r7,fp,pc} // restore & return

BCM2836_GPIO_PinSelDump:
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


/*********************
 * SPI Functions
 *
 * For documentation, see BCM2835 datasheet
 * chapter 10, page 148ff.
 *********************/

BCM2836_SPI0_GetBase:
	ldr r0,=dev_mem_gpio_base_addr
	ldr r0,[r0]
	add r0,r0,#(BCM2836_SPI0_BASEOFFSET-BCM2836_GPIO_BASEOFFSET)
	mov pc,lr

// void bcm2836_spi_init(void)
BCM2836_SPI0_Init:
  push {r4-r10,fp,lr} // Note: FP/R11 is not part of ARM EABI

  // FIXME: This bluntly assumes that GPIO_Init has been called!
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
  str r0,[r4,#BCM2835_SPI0_CS_OFFSET]
  // clear fifos
  mov r0, #BCM2835_SPI0_CS_CLEAR
  str r0,[r4,#BCM2835_SPI0_CS_OFFSET]
  // set CS-Polarity of cs0 and cs1 to 0
  ldr r0,[r4,#BCM2835_SPI0_CS_OFFSET]
  bic r0,r0,#BCM2835_SPI0_CS_CSPOL0
  bic r0,r0,#BCM2835_SPI0_CS_CSPOL1
  str r0,[r4,#BCM2835_SPI0_CS_OFFSET]
  // set clock divider
  mov r0,#64 // 3.9 MhZ on RPi2
  str r0,[r4,#BCM2835_SPI0_CLK_OFFSET]
  // set data mode to mode 0 (cpol=0, cpha=0) and select CS0 (CS=0)
  ldr r0,[r4,#BCM2835_SPI0_CS_OFFSET]
  bic r0,r0,#BCM2835_SPI0_CS_CPOL
  bic r0,r0,#BCM2835_SPI0_CS_CPHA
  bic r0,r0,#BCM2835_SPI0_CS_CS
  str r0,[r4,#BCM2835_SPI0_CS_OFFSET]

  pop {r4-r10,fp,pc}

 // size_t bcm2836_spi0_send(size_t dataSz, void* txdata, void *rxdata)
 BCM2836_SPI0_Send:
 /**
  * @brief: Send and receive dataSz bytes over SPI
  *
  * Assume *data points to dataSz bytes of data. proceed as follows:
  *
  * Clear RX/TX FiFos;
  * rxData = 0;
  * txData = 0;
  * while (rxData < dataSz) {
  *   if (txBuffer != Full && txData < dataSz)
  *     copy(txdata[txData++] to SPI TX Buffer);
  *   if (rxBuffer != Empty)
  *     copy(SPI RX Buffer to rxdata[rxData++])
  * }
  */
  push {r4-r10,fp,lr} // Note: FP/R11 is not part of ARM EABI; but we save it anyway
  // FIXME: This function simply assumes SPI_Init and GPIO_Init where called...

  mov r7, r0  // dataSz:r7 = r0:dataSz
  bl BCM2836_SPI0_GetBase
  mov r4, r0  // r4 = BCM2836_SPI0_GetBase()
  mov r5, #0  // rxData:r5 = 0
  mov r6, #0  // txData:r6 = r0:dataSz
  mov r8, r1  // r8 = *txdata_ptr
  mov r9, r2  // r9 = *rxdata_ptr

  // clear fifos and set TA
  // CS = CS | (CLEAR|TA)
  ldr r0,[r4,#BCM2835_SPI0_CS_OFFSET]
  orr r0,r0, #BCM2835_SPI0_CS_CLEAR
  orr r0,r0, #BCM2835_SPI0_CS_TA
  str r0,[r4,#BCM2835_SPI0_CS_OFFSET]

  BCM2836_SPI0_Send_rxtxloop_start:
    // while (rxdata:r5 < dataSz:r7) ...
    cmp r5, r7
    bge BCM2836_SPI0_Send_rxtxloop_end

    BCM2836_SPI0_Send_rxtxloop_rx:
    // if (rxBuffer != Empty) {
    ldr r0,[r4,#BCM2835_SPI0_CS_OFFSET]
    tst r0, #BCM2835_SPI0_CS_RXD_FIFO_NOTEMPTY
    beq BCM2836_SPI0_Send_rxtxloop_rx_end

    // copy(SPI RX Buffer to rxdata[rxData++])
    ldr r0,[r4,#BCM2835_SPI0_FIFO_OFFSET] // read
    and r0,r0,#0xFF
    strb r0,[r9, r5]
    add r5, r5, #1 // rxData++
    BCM2836_SPI0_Send_rxtxloop_rx_end: // }

    BCM2836_SPI0_Send_rxtxloop_tx:
    // if (txdata:r6 < dataSz:r7 ...
    cmp r6, r7
    bge BCM2836_SPI0_Send_rxtxloop_tx_end
    //  && txBuffer != Full ....
    ldr r0,[r4,#BCM2835_SPI0_CS_OFFSET]
    tst r0, #BCM2835_SPI0_CS_TXD_FIFO_FULL
    beq BCM2836_SPI0_Send_rxtxloop_tx_end
    // ... ) {

    // copy(txdata[txData++] to SPI TX Buffer);
    ldrb r0, [r8, r6]
    str  r0, [r4, #BCM2835_SPI0_FIFO_OFFSET]
    add  r6, r6, #1  // txData++
    BCM2836_SPI0_Send_rxtxloop_tx_end: //}

    b BCM2836_SPI0_Send_rxtxloop_start
  BCM2836_SPI0_Send_rxtxloop_end:

  BCM2836_SPI0_Send_wait_for_done:

  ldr r0,[r4,#BCM2835_SPI0_CS_OFFSET] // wait for done
  tst r0,#BCM2835_SPI0_CS_DONE
  beq BCM2836_SPI0_Send_wait_for_done

  ldr r0,[r4,#BCM2835_SPI0_CS_OFFSET]
  bic r0,r0,#BCM2835_SPI0_CS_TA
  str r0,[r4,#BCM2835_SPI0_CS_OFFSET]

  pop {r4-r10,fp,pc}
