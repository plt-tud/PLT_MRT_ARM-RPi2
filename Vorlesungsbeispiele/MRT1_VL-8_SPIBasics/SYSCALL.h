// /usr/arm-linux-gnueabihf/include/asm/unistd.h: #define __NR_write (__NR_SYSCALL_BASE+4)
.equ SYSCALL_WRITE, 4

// /usr/arm-linux-gnueabihf/include/asm/unistd.h: #define __NR_open (__NR_SYSCALL_BASE+5)
.equ SYSCALL_OPEN, 5
// /usr/include/arm-linux-gnueabihf/bits/fcntl-linux.h:# define O_SYNC            04010000
// /usr/include/arm-linux-gnueabihf/bits/fcntl-linux.h: #define O_RDWR                  02
.equ OPEN_PARAMETER_SYNC, 04010000
.equ OPEN_PARAMETER_RDWR, 00000002
.equ OPEN_PARAMETER_SYNC_RDWR, OPEN_PARAMETER_RDWR + OPEN_PARAMETER_SYNC

// /usr/arm-linux-gnueabihf/include/asm/unistd.h: #define __NR_close (__NR_SYSCALL_BASE+6)
.equ SYSCALL_CLOSE, 6

// /usr/arm-linux-gnueabihf/include/asm/unistd.h: #define __NR_mmap2 (__NR_SYSCALL_BASE+192)

.equ SYSCALL_MMAP2, 192
// /usr/include/arm-linux-gnueabihf/bits/mman-linux.h:#define MAP_SHARED   0x01
.equ MMAP_PARAMETER_MAP_SHARED, 0x01
// /usr/include/arm-linux-gnueabihf/bits/mman-linux.h:#define PROT_READ   0x01
// /usr/include/arm-linux-gnueabihf/bits/mman-linux.h:#define PROT_WRITE  0x2
.equ MMAP_PARAMETER_PROT_READ, 0x01
.equ MMAP_PARAMETER_PROT_WRITE, 0x02
.equ MMAP_PARAMETER_PROT_READ_WRITE, MMAP_PARAMETER_PROT_READ + MMAP_PARAMETER_PROT_WRITE

// /usr/arm-linux-gnueabihf/include/asm/unistd.h: #define __NR_munmap (__NR_SYSCALL_BASE+91)
.equ SYSCALL_MUNMAP, 91

