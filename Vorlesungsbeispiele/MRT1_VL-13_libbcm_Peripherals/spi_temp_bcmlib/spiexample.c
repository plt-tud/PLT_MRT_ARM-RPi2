#include <stdlib.h>
#include <stdio.h>
#include "bcm2835.h"

#define SENSOR_VOLTAGE 3.3

typedef union tmp36_spi_package_t {
  struct {
      unsigned start  : 1;
      unsigned        : 7;
      
      unsigned        : 4;
      
      unsigned d0     : 1;
      unsigned d1     : 1;
      unsigned d2     : 1;
      unsigned single : 1;
      
      unsigned        : 8;
  };
  struct {
      unsigned         : 8;
      unsigned         : 4;
      unsigned channel : 3;
      unsigned         : 1;
      unsigned         : 8;
  };
  struct {
    char     control;
    uint16_t value; // Note: Not usable on Motorolla Byte Ordered systems (MCP3008 sends intel byte order)
  };
  char data[3];
} tmp36_spi_package;

void main() {
  bcm2835_init();

  //Setup SPI pins
  bcm2835_spi_begin();
  
  //Set CS pins polarity to low
  bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, 0);
  bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS1, 0);
  
  //Set SPI clock speed
  //  BCM2835_SPI_CLOCK_DIVIDER_65536 = 0,       ///< 65536 = 262.144us = 3.814697260kHz (total H+L clock period) 
  //  BCM2835_SPI_CLOCK_DIVIDER_32768 = 32768,   ///< 32768 = 131.072us = 7.629394531kHz
  //  BCM2835_SPI_CLOCK_DIVIDER_16384 = 16384,   ///< 16384 = 65.536us = 15.25878906kHz
  //  BCM2835_SPI_CLOCK_DIVIDER_8192  = 8192,    ///< 8192 = 32.768us = 30/51757813kHz
  //  BCM2835_SPI_CLOCK_DIVIDER_4096  = 4096,    ///< 4096 = 16.384us = 61.03515625kHz
  //  BCM2835_SPI_CLOCK_DIVIDER_2048  = 2048,    ///< 2048 = 8.192us = 122.0703125kHz
  //  BCM2835_SPI_CLOCK_DIVIDER_1024  = 1024,    ///< 1024 = 4.096us = 244.140625kHz
  //  BCM2835_SPI_CLOCK_DIVIDER_512   = 512,     ///< 512 = 2.048us = 488.28125kHz
  //  BCM2835_SPI_CLOCK_DIVIDER_256   = 256,     ///< 256 = 1.024us = 976.5625MHz
  //  BCM2835_SPI_CLOCK_DIVIDER_128   = 128,     ///< 128 = 512ns = = 1.953125MHz
  //  BCM2835_SPI_CLOCK_DIVIDER_64    = 64,      ///< 64 = 256ns = 3.90625MHz
  //  BCM2835_SPI_CLOCK_DIVIDER_32    = 32,      ///< 32 = 128ns = 7.8125MHz
  //  BCM2835_SPI_CLOCK_DIVIDER_16    = 16,      ///< 16 = 64ns = 15.625MHz
  //  BCM2835_SPI_CLOCK_DIVIDER_8     = 8,       ///< 8 = 32ns = 31.25MHz
  //  BCM2835_SPI_CLOCK_DIVIDER_4     = 4,       ///< 4 = 16ns = 62.5MHz
  //  BCM2835_SPI_CLOCK_DIVIDER_2     = 2,       ///< 2 = 8ns = 125MHz, fastest you can get
  //  BCM2835_SPI_CLOCK_DIVIDER_1     = 1,       ///< 1 = 262.144us = 3.814697260kHz, same as 0/65536
  bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_64);

  //Set SPI data mode
  //  BCM2835_SPI_MODE0 = 0,  // CPOL = 0, CPHA = 0, Clock idle low, data is clocked in on rising edge, output data (change) on falling edge
  //  BCM2835_SPI_MODE1 = 1,  // CPOL = 0, CPHA = 1, Clock idle low, data is clocked in on falling edge, output data (change) on rising edge
  //  BCM2835_SPI_MODE2 = 2,  // CPOL = 1, CPHA = 0, Clock idle high, data is clocked in on falling edge, output data (change) on rising edge
  //  BCM2835_SPI_MODE3 = 3,  // CPOL = 1, CPHA = 1, Clock idle high, data is clocked in on rising, edge output data (change) on falling edge
  bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);

  //Set with CS pin to use for next transfers
  bcm2835_spi_chipSelect(BCM2835_SPI_CS0);

  float t;
  tmp36_spi_package p;
  
  p.value   = 0;
  p.control = 0;  
  p.single  = 1;
  p.start   = 1;
  p.channel = 0;
  
  printf("TX:  %x,%x,%x\n", (char) p.data[0], (char) p.data[1], (char) p.data[2]);
  bcm2835_spi_transfern(&p.data[0], 3);     //data_buffer used for tx and rx
  printf("Got %i, %x,%x,%x\n", p.value, (char) p.data[0], (char) p.data[1], (char) p.data[2]);
  
  // TMP36 Analog devices sensor: 750mV@25C, 10mV/C; Note operating Voltage...
  t = p.data[2] + (p.data[1] << 8); // Note: Device sends intel byte order... don't cast to short on ARM
  t = t/1024.0 * SENSOR_VOLTAGE - 0.75;
  t = 25 + t/0.1;
  printf("%g C\n", t);
  
  bcm2835_spi_end();
  
  p.data[0] = 1;
  p.data[2] = 0;
  p.data[1] = (8+0) << 4;
  printf("TX:  %x,%x,%x\n", (char) p.data[0], (char) p.data[1], (char) p.data[2]);
  
  bcm2835_spi_end();
  return ;
}
