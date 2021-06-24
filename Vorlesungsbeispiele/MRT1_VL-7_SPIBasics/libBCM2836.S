@ Header
.globl BCM2836_GPIO_Open, BCM2836_GPIO_Close, BCM2836_GPIO_PinSelFun, BCM2836_GPIO_PinSet, BCM2836_GPIO_PinClr, BCM2836_GPIO_PinSelDump
.globl BCM2836_SPI0_GetBase, BCM2836_SPI0_Init, BCM2836_SPI0_Send

.include "BCM2836_constants.h"
.include "BCM2836_GPIO_constants.h"
.include "BCM2836_SPI_constants.h"
.include "SYSCALL.h"

.data
.balign 4
dev_mem_filename:     .asciz "/dev/mem"
.balign 4
BCM2836_msg_err_open: .asciz "error initializing BCM2836"
.balign 4
dev_mem_gpio_fd:         .word 0  @ holds fd to /dev/mem
dev_mem_gpio_base_addr:  .word 0

.equ BCM2836_strlen_err_open, . - BCM2836_msg_err_open

.text
.align 4

/*********************
 * GPIO Functions
 *********************/

.func BCM2836_GPIO_Open
BCM2836_GPIO_Open:
  // EABI first
  mov   ip, sp
  stmfd sp!,{r4-r11,lr}
  mov   fp, ip

  // open(const char *pathname, int flags, mode_t mode);
  // r9: dev_mem_gpio_fd = open(/dev/mem,  O_RDWR|O_SYNC, 0)
  ldr r0, =dev_mem_filename				// filepath is "/dev/mem"
  ldr r1, =OPEN_PARAMETER_SYNC_RDWR		// RDWD: open for read and write access
  										// SYNC: write operations will only return after writing has finsished
  mov r2, #0							// file modes are ignored since no file will be created
  mov r7, #SYSCALL_OPEN
  swi #0								// open returns a file descriptor that is used to refer to the opened file
  ldr r1,=dev_mem_gpio_fd  				// save file descriptor at =dev_mem_gpio_fd
  str r0,[r1]
  cmp r0,#0
  ble BCM2836_GPIO_Open_error

  // mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
  // dev_mem_gpio_base_addr = mmap(NULL, gpio_speicherbereich, PROT_READ|PROT_WRITE, MAP_SHARED)
  mov r4, r0							// file handle to "/dev/mem" from previous syscall open
  mov r0, #0							// we do not define an address of mapping, so it will be chosen by the kernel
  mov r1, #BCM2836_PERI_MAPSIZE			// mapping's length
  mov r2, #MMAP_PARAMETER_PROT_READ_WRITE	// mapped pages will be written and read
  mov r3, #MMAP_PARAMETER_MAP_SHARED		// updates to the mapping are visible to other processes
  ldr r5, =BCM2836_GPIO_BASE         	// offset must be multiple of 4k (page size), so we have to shift the address
  lsr r5, r5, #12                   	// shift address from the manual (0x3f200000) to 0x3f200 (divide by 2^12 = 4k)
  mov r7, #SYSCALL_MMAP2
  swi #0
  ldr r1,=dev_mem_gpio_base_addr  		// addr_base of memory mapping is returned to r0 and saved at dev_mem_gpio_base_addr
  str r0,[r1]
  cmp r0,#0
  movne r0,#0
BCM2836_GPIO_Open_exit:
  ldmfd sp!,{r4-r10,r11,lr}
  bx lr

BCM2836_GPIO_Open_error:
  push {r0,r7}
  mov r0,#1 // stdout
  ldr r1,=BCM2836_msg_err_open
  mov r2,#BCM2836_strlen_err_open
  mov r7,#SYSCALL_WRITE
  swi #0
  pop {r0,r7}
  bal BCM2836_GPIO_Open_exit
.endfunc
// BCM2836_GPIO_PinSelFun(pin_target, FunctionSelection)
.func BCM2836_GPIO_PinSelFun
BCM2836_GPIO_PinSelFun:
  // EABI first
  mov   ip, sp
  stmfd sp!,{r4-r11,lr}
  mov   fp, ip

  // GPIO function select registers can access a maximum of 10 pins (3 bit per pin and max size of 32 bit per
  // register). So we have to calculate the fsel register's index and the corresponding bit position.

  // r10: bitpos_target = (pin_target % 10) * 3
  // r9: index_register = pin_target / 3

  // We do not calculate bitpos_target and index_register using the formulas above but by using a loop.

  BCM2836_GPIO_PinSelFun_divloop_init:
  // while (r9: div=0, r0: mod=27); r0 = value --> value%10; r9=value/10
  mov r9, #0		// r9: index_fsel = 0
  BCM2836_GPIO_PinSelFun_divloop_test:
    // Subtrahiere, solange r0 positiv ist
    subs r0, r0, #10							// r0: pin_target = pin_target - 10
    bmi  BCM2836_GPIO_PinSelFun_divloop_done	// branch if pin_target is negative (bmi - "mi" = "minus")
    add  r9, r9, #1								// r9: index_fsel++
    b    BCM2836_GPIO_PinSelFun_divloop_test	// continue loop
  BCM2836_GPIO_PinSelFun_divloop_done:
  add r10, r0, #10 			// pin_target mistakenly became negative, so we correct that
  add r10, r10, r10, lsl #1 // r10: bitpos_target = pin_target + pin_target*2
  							//	   			      = pin_target * 3

  // r10: bitpos_target		- target bit position in gpfsel register
  // r9:  index_register	- fsel register's index

  /* Copy - ... */
  ldr r3,=dev_mem_gpio_base_addr 	// we have stored the base address from mmap at this address in GPIO_Open call
  ldr r3,[r3]   					// r3: addr_base = mem(dev_mem_gpio_base_addr)

  ldr r4,[r3,r9,LSL #2]   	// r4: content_gpfsel = mem(GPFSEL<index_register>)
  							// 					  = mem(addr_base + index_register * 4]

  /* ... - Modify - ...*/
  mov r5,#0b111				// generate bitmask for clearing fsel register at bitpos_target
  bic r4,r4,r5,LSL R10  	// r4: content_gpfsel = content_gpfsel NAND ( 0b111 << bitpos_target)
  orr r4,r4,r1,LSL R10 		// r4: content_gpfsel = content_gpfsel OR 	( 0b111 << bitpos_target)

  /* ... - Update*/
  str r4,[r3,r9,LSL #2] 	//   mem(addr_base + index_register * 4]
  							// = mem(GPFSEL<index_register>)		 = content_gpfsel

  ldmfd sp!,{r4-r10,r11,lr}
  bx lr
.endfunc

// void BCM2836_GPIO_PinSet(pin_target) r0=GPIO_Pin
.func BCM2836_GPIO_PinSet
BCM2836_GPIO_PinSet:
  // EABI first
  mov   ip, sp
  stmfd sp!,{r4-r11,lr}
  mov   fp, ip

  // There are two registers for setting GPIO values (GPSET0 and GPSET1). We first have to calculate the correct
  // register and then continue with setting the bit at the correct position to 1.

  mov r1,#BCM2836_GPSET_OFFSET	// r1: addr_gpset_offs
  cmp r0,#31      				// if (pin_target > 31)
  addgt r1,r1,#4  				//  then r1: addr_gpset_offs = addr_gpset_offs + 4 	(jump to register 2 which
  								//													 directly follows in memory)

  // r0: mask = 1 << (pin_target % 32)	- shift 1 to correct position
  and r0, r0, #0x1F	// r0: bitpos_set = pin_target % 32 	(get the correct bit positon in a 32 bit field)
  mov r3, #1
  lsl r0, r3, r0    // r0: gpset_content = 1 << bitpos_set	(create gpset by shifting 1 to the correct bit position)

  // r2 <- gpio_base_addr
  ldr r2,=dev_mem_gpio_base_addr	// r2: addr_gpio_base
  ldr r2,[r2]						// r2: mem(addr_gpio_base)

  // r0 -> [base + offset]
  str r0,[r2,r1] 				// mem(addr_gpio_base + addr_gpset_offs) = gpset_content

  ldmfd sp!,{r4-r10,r11,lr}
  bx lr
.endfunc

// void BCM2836_GPIO_PinClr(pin_target)
.func BCM2836_GPIO_PinClr
BCM2836_GPIO_PinClr:
  // EABI first
  mov   ip, sp
  stmfd sp!,{r4-r11,lr}
  mov   fp, ip

  // There are two registers for clearing GPIO values (GPCLR0 and GPCLR1). We first have to calculate the correct
  // register and then continue with setting the bit at the correct position to 1.

  // r0: mask = 1 << (pin_target % 32)	- shift 1 to correct position
  mov r1,#BCM2836_GPCLR_OFFSET	// r1: addr_gpclr_offs
  cmp r0,#31      				// if (pin_target > 31)
  addgt r1,r1,#4  				//  then r1: addr_gpclr_offs = addr_gpclr_offs + 4 	(jump to register 2 which
  								//													 directly follows in memory)

  // r0: mask = 1 << (pin_target % 32)	- shift 1 to correct position
  and r0, r0, #0x1F	 // r0: bitpos_clr = pin_target % 32 	(get the correct bit positon in a 32 bit field)
  mov r3, #1
  mov r0, r3, LSL r0 // r0: gpclr_content = 1 << bitpos_clr	(create gpclr by shifting 1 to the correct bit position)

  // r2 <- gpio_base_addr
  ldr r2,=dev_mem_gpio_base_addr	// r2: addr_gpio_base
  ldr r2,[r2]						// r2: mem(addr_gpio_base)

  // r0 -> [gpio_base_addr + offset]
  str r0,[r2,r1]					// mem(addr_gpio_base + addr_gpclr_offs) = gpclr_content

  ldmfd sp!,{r4-r10,r11,lr}
  bx lr
.endfunc

.func BCM2836_GPIO_Close
BCM2836_GPIO_Close:
  // EABI first
  mov   ip, sp
  stmfd sp!,{r4-r11,lr}
  mov   fp, ip

  // int munmap(void *addr, size_t length);
  // munmap(addr_base, gpio_speicherbereich)
  ldr r0,=dev_mem_gpio_base_addr	// base address for memory unmapping
  ldr r0,[r0]
  mov r1,#BCM2836_PERI_MAPSIZE		// length of memory block that is to be deleted
  mov r7,#SYSCALL_MUNMAP
  swi #0
  
  // int close(int fd);
  ldr r0,=dev_mem_gpio_fd			// file descriptor that has been returned by open()
  ldr r0,[r0]
  mov r7, #SYSCALL_CLOSE
  swi #0

  ldmfd sp!,{r4-r10,r11,lr}
  bx lr
.endfunc



/*********************
 * SPI Functions
 *
 * For documentation, see BCM2835 datasheet
 * chapter 10, page 148ff.
 *********************/

.func BCM2836_SPI0_GetBase
 /**
   * @brief: Returns the base address of the SPI0 registers in mapped memory
   *
   * Note that this function assumes you have initialized the peripheral.
   */
BCM2836_SPI0_GetBase:
  // EABI first
  mov   ip, sp
  stmfd sp!,{r4-r11,lr}
  mov   fp, ip

  ldr r0,=dev_mem_gpio_base_addr
  ldr r0,[r0]
  add r0,r0,#(BCM2836_SPI0_BASEOFFSET-BCM2836_GPIO_BASEOFFSET)

  ldmfd sp!,{r4-r10,r11,lr}
  bx lr
.endfunc
