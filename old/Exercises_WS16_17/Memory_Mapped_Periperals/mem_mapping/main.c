/*
 ============================================================================
 Name        : RPi_MemMapping.c
 Author      : Chris Iatrou (TUD/PLT)
 Version     :
 Copyright   : MIT/X11 Licence
 Description : Rapid primitive GPIO21 Blinker using mmap'ed peripherals
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define GPIO_BASE 0x3F200000
#define GPIO_LAST 0x3F2000B0



int main(void) {
	int memf = open("/dev/mem", O_RDWR | O_SYNC);
	if (memf < 0) {
		printf("Failed to open /dev/mem\n");
		return -1;
	}

	unsigned char *peripheral = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, memf, GPIO_BASE);
	if (peripheral == -1) {
		printf("Failed to map /dev/mem: %s\n", strerror(errno));
		return -1;
	}

	printf("Memory mapped @%x\n", (unsigned int) peripheral);

	volatile unsigned int *gpioFsel2 = peripheral + 0x08;
	// Make GPIO21 an output
	*(gpioFsel2) &= ~(((unsigned int) 0x3) << 3);
	*(gpioFsel2) |= ((unsigned int) 0x1) << 3;

	while(1) {
		// Set
		volatile unsigned int *gpio0set = peripheral + 0x1C;
		*(gpio0set) = ((unsigned int) 1) << 21;

		printf("On\n");
		unsigned int i=0;
		for(i=0; i<4000000; i++);

		printf("Off\n");
		// Clear
		volatile unsigned int *gpio0clr = peripheral + 0x28;
		*(gpio0clr) = ((unsigned int) 1) << 21;
		for(i=0; i<4000000; i++);
	}

	munmap(peripheral, GPIO_LAST-GPIO_BASE);
	close(memf);
	return 0;
}
