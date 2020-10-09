#include <stdlib.h>
#include <stdio.h>
#include "bcm2835.h"

#define GPIO 21

void main() {
  bcm2835_init();
  
  // Set RPI pin P1-15 to be an input
  bcm2835_gpio_fsel(GPIO, BCM2835_GPIO_FSEL_OUTP);
  
  // Blunk 10 times!
  for( int i = 0; i<10; i++ ){
    bcm2835_gpio_set(GPIO);
    sleep(1);
    bcm2835_gpio_clr(GPIO);
    sleep(1);
  }
  
  bcm2835_close();
  return;
}
