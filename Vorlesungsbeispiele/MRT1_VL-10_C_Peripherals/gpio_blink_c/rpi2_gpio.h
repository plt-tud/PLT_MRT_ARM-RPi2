#ifndef HAVE_RPI2_GPIO_H
#define HAVE_RPI2_GPIO_H

enum rpi2_peripheral_regnames {
  GPFSEL0=0, GPFSEL1, GPFSEL2, GPFSEL3, GPFSEL4, GPFSEL5,
  UNUSED_0,
  GPSET0, GPSET1,
  UNUSED_1,
  GPCLR0, GPCLR1,
  UNUSED_2,
  GPLEV0, GPLEV1,
  UNUSED_3,
  GPEDS0, GPEDS1,
  UNUSED_4,
  GPREN0, GPREN1,
  UNUSED_5,
  GPFEN0, GPFEN1,
  UNUSED_6,
  GPHEN0, GPHEN1,
  UNUSED_7,
  GPLEN0, GPLEN1,
  UNUSED_8,
  GPAREN0, GPAREN1,
  UNUSED_9,
  GPAFEN0, GPAFEN1,
  UNUSED_10,
  GPPUD, GPPUDCLK0, GPPUDCLK1
};

#define GPIO_REGISTER_LIST_SIZE 39

extern volatile unsigned int* GPIO_REGISTER_LIST[];
void gpio_registers_initRegList(volatile unsigned int *gpio_base_addr);

#endif