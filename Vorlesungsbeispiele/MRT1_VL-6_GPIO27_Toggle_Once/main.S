
@ Definitionen
// Aus Bootloader, Mapping v. physischem Speicher 0x7Exxxxx --> 0x3fxxxxxx
.equ BCM2836_PERI_BASE,         0x3f000000

// Aus BCM2836 Datenblatt, Abschnitt GPIOs
.equ BCM2836_GPIO_BASEOFFSET,   0x00200000
.equ BCM2836_GPIO_LASTADDRESS,  0x002000B4
.equ BCM2836_GPIO_MEMSIZE,      0x00001000 // Must be >=4k according to manual !
.equ BCM2836_GPIO_BASE, BCM2836_PERI_BASE + BCM2836_GPIO_BASEOFFSET

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
.balign 4
dev_mem_filename: .asciz        "/dev/mem"
.equ dev_mem_filename_strlen, . - dev_mem_filename

.text
.global main

.func main
main:
  // EABI first
  mov   ip, sp
  stmfd sp!,{r4-r11,lr}
  mov   fp, ip

  // r9 = open(/dev/mem,  O_RDWR|O_SYNC, 0)
  ldr r0, =dev_mem_filename
  ldr r1, =OPEN_PARAMETER_SYNC_RDWR
  mov r2, #0
  mov r7, #SYSCALL_OPEN
  swi #0
  mov r9, r0

  // mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
  // r8 = mmap(NULL, gpio_speicherbereich, PROT_READ|PROT_WRITE, MAP_SHARED)
  mov r0, #0
  mov r1, #BCM2836_GPIO_MEMSIZE
  mov r2, #MMAP_PARAMETER_PROT_READ_WRITE
  mov r3, #MMAP_PARAMETER_MAP_SHARED
  mov r4, r9						// file handle from open /dev/mem
  ldr r5, =BCM2836_GPIO_BASE        // mmap benutzt 4k bloecke und multipliziert unsere adresse intern; wir muessen etwas schieben
  lsr r5, r5, #12                   // aus 0x3f200000 sollte 0x3f200 werden...
  mov r7, #SYSCALL_MMAP2
  swi #0
  mov r8, r0                       // Von mmap bestimmte Basisadresse der Abbildung in unserem Speicher

  /* Ab hier:
     - r8 ist Basisadresse der GPIO register
     - Basisadresse in r8 wird dynamisch, zur Laufzeit, bestimmt! (durch mmap)
     - Offset ist zu GPIOs-Zugriffen aufzuaddieren
  */

  // ---- Anfang des GPIO-Codes

  // GPIO 21 als Output deklarieren
  // ldr r0, [r8, #8] // R0 <- GPIO-Register GPFSEL2
  // and r0, r0, #0b11111111111111111111111111000111
  // orr r0, r0, #0b00000000000000000000000000001000
  // str r0, [r8, #8] // R0 -> GPIO-Register GPFSEL1

  // GPIO 17 als Output deklarieren
  ldr r0, [r8, #4] // R0 <- GPIO-Register GPFSEL1
  and r0, r0, #0b11111111000111111111111111111111
  orr r0, r0, #0b00000000001000000000000000000000
  str r0, [r8, #4] // R0 -> GPIO-Register GPFSEL1

  // GPIO 21 setzen
  // mov r0, #0b00000000000100000000000000000000
  // str r0, [r8, #28] // R0 -> GPIO-Register GPSET0
  // GPIO 17 setzen
  mov r0,    #0b00000000000000100000000000000000
  str r0, [r8, #28] // R0 -> GPIO-Register GPSET0

  // GPIO 21 rücksetzen
  // mov r0, #0b00000000000100000000000000000000
  // str r0, [r8, #40] // R0 -> GPIO-Register GPCLR0
  // GPIO 17 rücksetzen
  mov r0, #0b00000000000000100000000000000000
  str r0, [r8, #40] // R0 -> GPIO-Register GPCLR0

  // ---- Ende des GPIO-Codes


  // munmap
  mov r0, r8
  mov r1, #BCM2836_GPIO_MEMSIZE
  mov r7, #SYSCALL_MUNMAP
  swi #0

  // close
  mov r0, r9
  mov r7, #SYSCALL_CLOSE
  swi #0

  mov r0, #0

  ldmfd sp!,{r4-r10,r11,lr}
  bx lr
.endfunc
