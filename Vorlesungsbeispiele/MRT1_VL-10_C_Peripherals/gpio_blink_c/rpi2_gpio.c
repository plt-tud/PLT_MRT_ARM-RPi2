#include "rpi2_gpio.h"

volatile unsigned int* GPIO_REGISTER_LIST[39];

void gpio_registers_initRegList(volatile unsigned int  *gpio_base_addr) {
  for(int i=0; i<GPIO_REGISTER_LIST_SIZE; i++)
    GPIO_REGISTER_LIST[i] = gpio_base_addr+i;

  return;
}
