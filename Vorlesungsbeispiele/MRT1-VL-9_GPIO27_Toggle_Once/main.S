.data

// Aus Bootloader, Mapping v. physischem Speicher 0x7Exxxxx --> 0x3fxxxxxx
.equ BCM2536_PERI_BASE,         0x3f000000

// Aus BCM2536 Datenblatt, Abschnitt GPIOs
.equ BCM2536_GPIO_BASEOFFSET,   0x00200000
.equ BCM2536_GPIO_LASTADDRESS,  0x002000B4 
.equ BCM2536_GPIO_MEMSIZE,      0x00001000 // Must be >=4k according to manual !
.set BCM2536_GPIO_BASE,         BCM2536_PERI_BASE + BCM2536_GPIO_BASEOFFSET

BCM2536_PERI_BASE_WORD: .word   BCM2536_PERI_BASE
OPEN_PARAMETER_SYNC_RDWR: .word 0x40100002

.balign 4

dev_mem_filename: .asciz        "/dev/mem"
dev_mem_filename_end:
.set dev_mem_filename_strlen, dev_mem_filename_end - dev_mem_filename

.text
.global main
.func main

main:
  // r11 = open(/dev/mem,  O_RDWR|O_SYNC, 0)
  ldr r0, dev_mem_filename_addr
  ldr r1, OPEN_PARAMETER_SYNC_RDWR_ADDR  // /usr/include/arm-linux-gnueabihf/bits/fcntl-linux.h:# define O_SYNC            04010000
                                         // /usr/include/arm-linux-gnueabihf/bits/fcntl-linux.h: #define O_RDWR                  02
  ldr r1, [r1]
  mov r2, #0
  mov r7, #5
  swi #0
  mov r11, r0
  
  // mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
  // mmap(NULL, gpio_speicherbereich, PROT_READ|PROT_WRITE, MAP_SHARED)
  mov r0, #0
  mov r1, #BCM2536_GPIO_MEMSIZE
  mov r2, #3                        // PROT_READ | PROT_WRITE
  mov r3, #1                        // /usr/include/arm-linux-gnueabihf/bits/mman-linux.h:#define MAP_SHARED   0x01
  mov r4, r11
  ldr r5, BCM2536_GPIO_BASE_ADDR    // mmap benutzt 4k bloecke und multipliziert unsere adresse intern; wir muessen etwas schieben
  lsr r5, r5, #12                   // aus 0x3f200000 sollte 0x3f200 werden...
  mov r7, #192                      // System Call #90 ist veraltet, supervisor call #192 wird empfohlen...
  swi #0
  mov r10, r0                       // Von mmap bestimmte Basisadresse der Abbildung in unserem Speicher
  
  /* Ab hier:
     - r10 ist Basisadresse der GPIO register
     - Basisadresse in r10 wird dynamisch, zur Laufzeit, bestimmt! (durch mmap)
     - Offset ist zu GPIOs-Zugriffen aufzuaddieren
  */
  
  // ---- Anfang des GPIO-Codes
  
  // GPIO 21 als Output deklarieren
  ldr r9, [r10, #8] // <- GPIO FSEL2
  and r9, r9, #0b11111111111111111111111111000111
  orr r9, r9, #0b00000000000000000000000000001000
  str r9, [r10, #8] // -> GPIO FSEL2
  
  ldr r9, [r10, #28] // GPIO GPSET0
  eor r9, r9, #0b00000000000100000000000000000000
  str r9, [r10, #28] // GPIO GPSET0
  
  ldr r9, [r10, #40] // GPIO GPCLR0
  eor r9, r9, #0b00000000000100000000000000000000
  str r9, [r10, #40] // GPIO GPSET0
  
  // ---- Ende des GPIO-Codes
  
  // munmap
  mov r0, r10
  mov r1, #BCM2536_GPIO_MEMSIZE
  mov r7, #91
  swi #0
  
  // close
  mov r0, r11
  mov r7, #6
  swi #0

  
  mov r0, #0
  bx  lr

BCM2536_GPIO_BASE_ADDR:        .word BCM2536_GPIO_BASE
OPEN_PARAMETER_SYNC_RDWR_ADDR: .word OPEN_PARAMETER_SYNC_RDWR
dev_mem_filename_addr:         .word dev_mem_filename

