@ Header
.globl BCM2836_GPIO_Open, BCM2836_GPIO_Close, BCM2836_GPIO_PinSelFun, BCM2836_GPIO_PinSet, BCM2836_GPIO_PinClr, BCM2836_GPIO_PinSelDump

.include "BCM2836_constants.h"
.include "BCM2836_GPIO_constants.h"
.include "SYSCALL.h"

.data
.balign 4
dev_mem_filename:   .asciz "/dev/mem"
.balign 4
dev_mem_gpio_fd:   .word 0  @ holds fd to /dev/mem
dev_mem_gpio_base_addr:  .word 0

.text
.align 4

.func BCM2836_GPIO_Open
BCM2836_GPIO_Open:
  // EABI first
  mov   ip, sp
  stmfd sp!,{r4-r11,lr}
  mov   fp, ip

  // dev_mem_gpio_fd = open(/dev/mem,  O_RDWR|O_SYNC, 0)
  ldr r0, =dev_mem_filename
  ldr r1, =OPEN_PARAMETER_SYNC_RDWR
  mov r2, #0
  mov r7, #SYSCALL_OPEN
  swi #0
  ldr r1,=dev_mem_gpio_fd  @ save file-handle at =dev_mem_gpio_fd
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
  ldr r1,=dev_mem_gpio_base_addr  // save address at =dev_mem_gpio_addr
  str r0,[r1]
  cmp r0,#0
  movne r0,#0
BCM2836_GPIO_Open_exit:
  ldmfd sp!,{r4-r10,r11,lr}
  bx lr
.endfunc

@ BCM2836_GPIO_PinSelFun(GPIO-Pin, FunctionSelection)
.func BCM2836_GPIO_PinSelFun
BCM2836_GPIO_PinSelFun:
  // EABI first
  mov   ip, sp
  stmfd sp!,{r4-r11,lr}
  mov   fp, ip

  // r2 <- Index of GPFSELn register; r0 <- 10⁰ remainder of pin number
  mov r2,#0
BCM2836_GPIO_PinSelFun_loop:
  cmp r0,#10                           // while ( r0 < 10)
  blt BCM2836_GPIO_PinSelFun_done      // {
  add r2,r2,#1                         //   r2 <- r2 + 1
  sub r0,r0,#10                        //   r0 <- r0 - 10
  bal BCM2836_GPIO_PinSelFun_loop      // }

BCM2836_GPIO_PinSelFun_done: add r0,r0,r0,lsl #1  // R0 <- R0 * 3

  ldr r3,=dev_mem_gpio_base_addr
  ldr r3,[r3]    // R3 <- address of gpio_base

  ldr r4,[r3,r2,LSL #2]   // R4 <- [ GPFSEL<r2> ]

  mov r5,#0b111
  bic r4,r4,r5,LSL R0  // R4 <- R4 AND NOT ( 0b111 << R0)
  orr r4,r4,r1,LSL R0 // R4 <- R4 ORR R1

  str r4,[r3,r2,LSL #2]  // R4 -> [ GPFSEL<r2> ]

  ldmfd sp!,{r4-r10,r11,lr}
  bx lr
.endfunc

@ void BCM2836_GPIO_PinSet(GPIO_Pin)
.func BCM2836_GPIO_PinSet
BCM2836_GPIO_PinSet:
  // EABI first
  mov   ip, sp
  stmfd sp!,{r4-r11,lr}
  mov   fp, ip

  // r1 <- Offset to GPSET0 or GPSET1
  mov r1,#BCM2836_GPSET_OFFSET
  cmp r0,#31    @ if (R0 > 31)
  addgt r1,r1,#4  @  R1 <- R1 + 4

  // r0 <- 1 << ( pin % 32)
  and r0, r0, #0x1F  @ pin % 32
  mov r3, #1
  lsl r0, r3, r0    @ 1 << ( pin % 32)

  // r2 <- gpio_base_addr
  ldr r2,=dev_mem_gpio_base_addr
  ldr r2,[r2]

  // r0 -> [base + offset]
  str r0,[r2,r1]

  ldmfd sp!,{r4-r10,r11,lr}
  bx lr
.endfunc

@ void BCM2836_GPIO_PinClr(GPIO_Pin)
.func BCM2836_GPIO_PinClr
BCM2836_GPIO_PinClr:
  // EABI first
  mov   ip, sp
  stmfd sp!,{r4-r11,lr}
  mov   fp, ip

  // r1 <- Offset to GPCLR0 or GPCLR1
  mov r1,#BCM2836_GPCLR_OFFSET
  cmp r0,#31    @ if (R0 > 31)
  addgt r1,r1,#4  @  R1 <- R1 + 4

  // r0 <- ( b1 << ( PIN % 32 ))
  and r0, r0, #0x1F
  mov r3, #1
  mov r0, r3, LSL r0

  // r2 <- gpio_base_addr
  ldr r2,=dev_mem_gpio_base_addr
  ldr r2,[r2]

  // r0 -> [gpio_base_addr + offset]
  str r0,[r2,r1]

  ldmfd sp!,{r4-r10,r11,lr}
  bx lr
.endfunc

.func BCM2836_GPIO_Close
BCM2836_GPIO_Close:
  // EABI first
  mov   ip, sp
  stmfd sp!,{r4-r11,lr}
  mov   fp, ip

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

  ldmfd sp!,{r4-r10,r11,lr}
  bx lr
.endfunc
