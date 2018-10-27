@ Header
.globl BCM2536_GPIO_Open, BCM2536_GPIO_Close, BCM2536_GPIO_PinSelFun, BCM2536_GPIO_PinSet, BCM2536_GPIO_PinClr
.type BCM2536_GPIO_Init,%function
.type BCM2536_GPIO_Close,%function
.type BCM2536_GPIO_PinSelFun,%function
.type BCM2536_GPIO_PinSet,%function
.type BCM2536_GPIO_PinClr,%function

@ Definitionen
// Aus Bootloader, Mapping v. physischem Speicher 0x7Exxxxx --> 0x3fxxxxxx
.equ BCM2536_PERI_BASE,         0x3f000000

// Aus BCM2536 Datenblatt, Abschnitt GPIOs
.equ BCM2536_GPIO_BASEOFFSET,   0x00200000
.equ BCM2536_GPIO_LASTADDRESS,  0x002000B4 
.equ BCM2536_GPIO_MEMSIZE,      0x00001000 // Must be >=4k according to manual !
.equ BCM2536_GPIO_BASE, BCM2536_PERI_BASE + BCM2536_GPIO_BASEOFFSET

.equ BCM2536_GPFSEL_OFFSET, 0
.equ BCM2536_GPSET_OFFSET, 0x1C
.equ BCM2536_GPCLR_OFFSET, 0x28

// /usr/include/arm-linux-gnueabihf/bits/fcntl-linux.h:# define O_SYNC            04010000
// /usr/include/arm-linux-gnueabihf/bits/fcntl-linux.h: #define O_RDWR                  02
.equ OPEN_PARAMETER_SYNC_RDWR, 0x40100002

// /usr/include/arm-linux-gnueabihf/bits/mman-linux.h:#define MAP_SHARED   0x01
.equ MMAP_PARAMETER_MAP_SHARED, 0x01
// /usr/include/arm-linux-gnueabihf/bits/mman-linux.h:#define PROT_READ   0x01
// /usr/include/arm-linux-gnueabihf/bits/mman-linux.h:#define PROT_WRITE  0x2
.equ MMAP_PARAMETER_PROT_READ_WRITE, 0x03


// /usr/arm-linux-gnueabihf/include/asm/unistd.h: #define __NR_open (__NR_SYSCALL_BASE+5)
.equ SYSCALL_OPEN, 5
// /usr/arm-linux-gnueabihf/include/asm/unistd.h: #define __NR_close (__NR_SYSCALL_BASE+6)
.equ SYSCALL_CLOSE, 6
// /usr/arm-linux-gnueabihf/include/asm/unistd.h: #define __NR_mmap2 (__NR_SYSCALL_BASE+192)
.equ SYSCALL_MMAP2, 192
// /usr/arm-linux-gnueabihf/include/asm/unistd.h: #define __NR_munmap (__NR_SYSCALL_BASE+91)
.equ SYSCALL_MUNMAP, 91

.data
.align 4
dev_mem_filename: 	.asciz "/dev/mem"
.align 4
dev_mem_gpio_fd: 	.word 0	@ holds
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

  pop {r4-r7,fp,lr}	// restore saved registers
  bx lr

@ BCM2536_GPIO_PinSelFun(GPIO-Pin, FunctionSelection)
BCM2536_GPIO_PinSelFun:
	push {r4,r5,fp,lr} // safe 4 registers
	add fp,sp,#((4-1)*4)

	// Calcuate Offset into GPFSEL-Register in r2 and hold remainder in r0
	mov r2,#0
loop:
	cmp r0,#10
	blt done
	add r2,r2,#4
	sub r0,r0,#10
	bal loop
done:
	add r0,r0,r0,lsl #1	// R0 <- R0 * 3

	ldr r3,=dev_mem_gpio_base_addr
	ldr r3,[r3]		// R3 <- address of gpio_base
	ldr r4,[r3,r2] 	// R4 <- GPFSELn
	mov r5,#0b111
	bic r4,r4,r5,LSL R0	// R4 <- R4 AND NOT ( 0b111 << R0)
	orr r4,r4,r1,LSL R0
	str r4,[r3,r2]

	pop {r4,r5,fp,pc}	// restore saved registers and return

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

	// r1 <- Offset to GPSET0 or GPSET1
	mov r1,#BCM2536_GPSET_OFFSET
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
