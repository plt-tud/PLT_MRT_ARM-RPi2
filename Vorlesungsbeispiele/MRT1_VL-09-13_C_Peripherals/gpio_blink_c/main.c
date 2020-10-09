#include <stdio.h>

#include "rpi2_memory_mapping.h"
#include "rpi2_gpio.h"

int main() {
    int debug;
    
    /* Map GPIO Mem. Area from /dev/mem into applications address space */
    volatile unsigned int *periBase = map_peripheral();
    if (periBase == NULL) 
      return 1; // Error is already displayed by map_peripheral function
    
    
    /* Leave calculating offsets to our register List */
    gpio_registers_initRegList(periBase);
    
    *(GPIO_REGISTER_LIST[GPFSEL2]) &= 0xFFFFFFC7;
    *(GPIO_REGISTER_LIST[GPFSEL2]) |= 0x00000008;
    
    *(GPIO_REGISTER_LIST[GPSET0]) |= (1 << 21);
    sleep(1);
    
    *(GPIO_REGISTER_LIST[GPCLR0]) |= (1 << 21);
    sleep(1);
    
    unmap_peripheral();
    return 0;
}
