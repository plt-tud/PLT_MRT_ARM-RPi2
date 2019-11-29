/*
 * Copyright (c) 2018 Leon Urbas   <leon.urbas@tu-dresden.de>
 * Copyright (c) 2019 Chris Iatrou <chris_paul.iatrou@tu-dresden.de>
 *
 * Hiermit wird unentgeltlich jeder Person, die eine Kopie der
 * Software und der zugehörigen Dokumentationen (die "Software")
 * erhält, die Erlaubnis erteilt, sie uneingeschränkt zu nutzen,
 * inklusive und ohne Ausnahme mit dem Recht, sie zu verwenden,
 * zu kopieren, zu verändern, zusammenzufügen, zu veröffentlichen,
 * zu verbreiten, zu unterlizenzieren und/oder zu verkaufen, und
 * Personen, denen diese Software überlassen wird, diese Rechte
 * zu verschaffen, unter den folgenden Bedingungen:
 *
 * Der obige Urheberrechtsvermerk und dieser Erlaubnisvermerk
 * sind in allen Kopien oder Teilkopien der Software beizulegen.
 *
 * DIE SOFTWARE WIRD OHNE JEDE AUSDRÜCKLICHE ODER IMPLIZIERTE
 * GARANTIE BEREITGESTELLT, EINSCHLIEẞLICH DER GARANTIE ZUR
 * BENUTZUNG FÜR DEN VORGESEHENEN ODER EINEM BESTIMMTEN ZWECK
 * SOWIE JEGLICHER RECHTSVERLETZUNG, JEDOCH NICHT DARAUF
 * BESCHRÄNKT. IN KEINEM FALL SIND DIE AUTOREN ODER
 * COPYRIGHTINHABER FÜR JEGLICHEN SCHADEN ODER SONSTIGE
 * ANSPRÜCHE HAFTBAR ZU MACHEN, OB INFOLGE DER ERFÜLLUNG EINES
 * VERTRAGES, EINES DELIKTES ODER ANDERS IM ZUSAMMENHANG MIT
 * DER SOFTWARE ODER SONSTIGER VERWENDUNG DER SOFTWARE ENTSTANDEN.
 */

/**
 *  @brief: Recap zur Bedienung unserer Peripherie in C.
 *
 *  Schaltet wahlweise GPIO 47 (Boad Status LED) oder 27 (externe
 *  LED/Linker Kit) an/aus. Die LED kann mit der Definition
 *  USE_BOARDLED ausgewaehlt werden.
 */

//#define USE_BOARDLEDS
#ifndef USE_BOARDLEDS
  #define GPIO_LED 26
#else
  #define GPIO_LED 47
#endif

#include <stdio.h>
#include <stdint.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/mman.h>

#include <string.h>
#include <errno.h>

#include <unistd.h>

#define RPI2_PERI_BASE          0x3f000000
#define RPI2_GPIO_OFFSET        0x00200000
#define RPI2_GPIO_GPSEL2_OFFS   0x00000008
#define RPI2_GPIO_GPSEL3_OFFS   0x0000000C
#define RPI2_GPIO_GPSEL4_OFFS   0x00000010

#define RPI2_GPIO_GPSET0_OFFS   0x0000001C
#define RPI2_GPIO_GPSET1_OFFS   0x00000020
#define RPI2_GPIO_GPCLR0_OFFS   0x00000028
#define RPI2_GPIO_GPCLR1_OFFS   0x0000002C

int manual_example()
{
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

		#ifndef USE_BOARDLEDS
			volatile uint32_t *gpioFSEL2_ptr = (uint32_t *) &peripheral[RPI2_GPIO_GPSEL2_OFFS];
			volatile uint32_t *gpioSet1_ptr  = (uint32_t *) &peripheral[RPI2_GPIO_GPSET0_OFFS];
			volatile uint32_t *gpioClr1_ptr  = (uint32_t *) &peripheral[RPI2_GPIO_GPCLR0_OFFS];

			// Make GPIO26 an output
			unsigned int fsel = *gpioFSEL2_ptr;
			fsel             &= ~( ((unsigned int) 0x7) << (3*(26%10)) );
			fsel			 |=  ( ((unsigned int) 0x1) << (3*(26%10)) );
			*gpioFSEL2_ptr    = fsel;

			// Turn GPIO26 off
			*(gpioClr1_ptr) = (unsigned int) 1 << (26 %32);

			// Turn GPIO26 on
			*(gpioSet1_ptr) = (unsigned int) 1 << (26 %32);

			// Turn GPIO27 off
			*(gpioClr1_ptr) = (unsigned int) 1 << (26 %32);
		#else // Use Board LEDs: GPIO 47 is the green system LED
			volatile uint32_t *gpioFSEL4_ptr = (uint32_t *) &peripheral[RPI2_GPIO_GPSEL4_OFFS];
			volatile uint32_t *gpioSet2_ptr  = (uint32_t *) &peripheral[RPI2_GPIO_GPSET1_OFFS];
			volatile uint32_t *gpioClr2_ptr  = (uint32_t *) &peripheral[RPI2_GPIO_GPCLR1_OFFS];

			// Make GPIO47 an output
			uint32_t fsel    = *gpioFSEL4_ptr;
			fsel             &=  ~(  (unsigned int) 0x7 << (3* (47%10)) ) ;
			fsel 	         |=      (unsigned int) 0x1 << (3* (47%10))  ;
			*(gpioFSEL4_ptr) = fsel;

			// Turn GPIO47 off
			*(gpioClr2_ptr) = (unsigned int) 1 << (47 %32);

			// Turn GPIO47 on
			*(gpioSet2_ptr) = (unsigned int) 1 << (47 %32);

			// Turn GPIO47 off
			*(gpioClr2_ptr) = (unsigned int) 1 << (47 %32);
		#endif // USE_BOARDLEDS

		munmap(peripheral, 4096);
		close(devmem_h);

	return 0;
}

#include "BCM2836.h"
int library_example()
{
	if (! BCM2836_Open() ) {
		BCM2836_GPIO_PinSelFun(GPIO_LED, BCM2836_GPFSEL_OUTPUT);
		BCM2836_GPIO_PinClr(GPIO_LED);
		BCM2836_GPIO_PinSet(GPIO_LED);
		BCM2836_GPIO_PinClr(GPIO_LED);
	}

	BCM2836_Close();

	return 0;
}

int main(int argc, char **argv) {
	manual_example();
	library_example();
	return 0;
}
