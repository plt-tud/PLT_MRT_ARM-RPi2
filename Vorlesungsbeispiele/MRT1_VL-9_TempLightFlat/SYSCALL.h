/*
 * Die nachfolgenden Definitionen werden fuer SysCalls benoetigt. Sie wurden
 * diversen Standard-Headern entnommen und hier zusammengefuehrt. Die Kommentare
 * geben an, in welchen Headern die Konstanten eigentlich stehen.
 */

// aus: /usr/arm-linux-gnueabihf/include/asm/unistd.h: #define __NR_write (__NR_SYSCALL_BASE+4)
.equ SYSCALL_WRITE, 4

// aus:  /usr/arm-linux-gnueabihf/include/asm/unistd.h: #define __NR_open (__NR_SYSCALL_BASE+5)
.equ SYSCALL_OPEN, 5
// aus:  /usr/include/arm-linux-gnueabihf/bits/fcntl-linux.h:# define O_SYNC            04010000
// aus:  /usr/include/arm-linux-gnueabihf/bits/fcntl-linux.h: #define O_RDWR                  02
.equ OPEN_PARAMETER_SYNC, 0x40100000
.equ OPEN_PARAMETER_RDWR, 0x00000002
.equ OPEN_PARAMETER_SYNC_RDWR, OPEN_PARAMETER_RDWR + OPEN_PARAMETER_SYNC

// aus:  /usr/arm-linux-gnueabihf/include/asm/unistd.h: #define __NR_close (__NR_SYSCALL_BASE+6)
.equ SYSCALL_CLOSE, 6

// aus:  /usr/arm-linux-gnueabihf/include/asm/unistd.h: #define __NR_mmap2 (__NR_SYSCALL_BASE+192)

.equ SYSCALL_MMAP2, 192
// aus:  /usr/include/arm-linux-gnueabihf/bits/mman-linux.h:#define MAP_SHARED   0x01
.equ MMAP_PARAMETER_MAP_SHARED, 0x01
// aus:  /usr/include/arm-linux-gnueabihf/bits/mman-linux.h:#define PROT_READ   0x01
// aus:  /usr/include/arm-linux-gnueabihf/bits/mman-linux.h:#define PROT_WRITE  0x2
.equ MMAP_PARAMETER_PROT_READ, 0x01
.equ MMAP_PARAMETER_PROT_WRITE, 0x02
.equ MMAP_PARAMETER_PROT_READ_WRITE, MMAP_PARAMETER_PROT_READ + MMAP_PARAMETER_PROT_WRITE

// aus:  /usr/arm-linux-gnueabihf/include/asm/unistd.h: #define __NR_munmap (__NR_SYSCALL_BASE+91)
.equ SYSCALL_MUNMAP, 91

