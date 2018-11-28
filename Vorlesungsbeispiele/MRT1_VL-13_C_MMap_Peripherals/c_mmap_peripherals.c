#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/mman.h>

#include <string.h>
#include <errno.h>

#include <unistd.h>

#define RPI2_PERI_BASE          0x3f000000
#define RPI2_GPIO_OFFSET        0x00200000
#define RPI2_GPIO_GPSEL4_OFFS   0x00000010
#define RPI2_GPIO_GPSET1_OFFS   0x00000020
#define RPI2_GPIO_GPCLR1_OFFS   0x0000002C

int main(int argc, char **argv) {
    int devmem_h = open("/dev/mem", O_RDWR | O_SYNC);
    if (devmem_h < 0) {
        printf("Failed to open /dev/mem\n");
        return -1;
    }

    char *peripheral = (char *) mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED,
    							devmem_h, RPI2_PERI_BASE+RPI2_GPIO_OFFSET);
    if (peripheral < 0) {
        printf("Failed to map /dev/mem: %s\n", strerror(errno));
        return -1;
    }

    volatile unsigned int *gpioFSEL2_ptr = (unsigned int *) &peripheral[RPI2_GPIO_GPSEL4_OFFS];
    volatile unsigned int *gpioSet2_ptr  = (unsigned int *) &peripheral[RPI2_GPIO_GPSET1_OFFS];
    volatile unsigned int *gpioClr2_ptr  = (unsigned int *) &peripheral[RPI2_GPIO_GPCLR1_OFFS];

    // Make GPIO21 an output
    *(gpioFSEL2_ptr) &= ~(((unsigned int) 0x7) << 21);
    *(gpioFSEL2_ptr) |=   ((unsigned int) 0x1) << 21;

    // Turn GPIO47 on
    *(gpioSet2_ptr) = ((unsigned int) 1) << (47 %32);

    sleep(1);
    // Turn GPIO47 off
    *(gpioClr2_ptr) = ((unsigned int) 1) << (47 %32);

    munmap(peripheral, 4096);
    close(devmem_h);
    return 0;
}
