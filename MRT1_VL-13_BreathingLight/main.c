#include <stdio.h>
#include "BCM2836.h"

//#define USE_BOARDLEDS

#ifndef USE_BOARDLEDS
#define GPIO_GREEN  27
#else
#define GPIO_GREEN  47
#endif

#if (GPIO_GREEN > 53)
#error "That is not a valid LED!"
#endif

#define DC_SENSE 100

#define ITERATIONS_PER_SECOND 10000000
#define ITERATIONS_UP (3 * ITERATIONS_PER_SECOND)
#define ITERATIONS_DOWN (1 * ITERATIONS_PER_SECOND)

int main(void) {
	BCM2836_Open();
	BCM2836_GPIO_PinSelFun(GPIO_GREEN, BCM2836_GPFSEL_OUTPUT);
	BCM2836_SPI0_Init();

	unsigned int pwmcount = 0;
	while (1) {

		long i;

		printf("Up...\n");
		// Up
		for (i = 0; i < ITERATIONS_UP; i++) {
			pwmcount++;
			if (pwmcount > DC_SENSE) {
				pwmcount = 0;
			}

			const unsigned int level = (i * DC_SENSE) / ITERATIONS_UP;

			if (level < pwmcount) {
				BCM2836_GPIO_PinClr(GPIO_GREEN);
			} else {
				BCM2836_GPIO_PinSet(GPIO_GREEN);
			}

		}

		printf("Down...\n");
		// Down
		for (i = ITERATIONS_DOWN - 1; i >= 0; i--) { // unsigned long would not work here!
			pwmcount++;
			if (pwmcount > DC_SENSE) {
				pwmcount = 0;
			}

			const unsigned int level = (i * DC_SENSE) / ITERATIONS_DOWN;

			if (level < pwmcount) {
				BCM2836_GPIO_PinClr(GPIO_GREEN);
			} else {
				BCM2836_GPIO_PinSet(GPIO_GREEN);
			}

		}

	}
	BCM2836_Close();
	return 0;
}
