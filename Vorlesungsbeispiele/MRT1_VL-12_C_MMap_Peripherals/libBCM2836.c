#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "BCM2836.h"

static volatile void *bcm2836_baseaddr_ptr = NULL;
static int 			  bcm2836_devmem_h=0;

int BCM2836_Open(void)
{
  if (bcm2836_devmem_h > 0) {
	  BCM2836_Close();
  }

  bcm2836_devmem_h = open("/dev/mem", O_RDWR | O_SYNC);
  if (bcm2836_devmem_h < 0) {
    printf("Failed to open /dev/mem\n");
    return -1;
  }

  bcm2836_baseaddr_ptr = mmap(NULL, BCM2836_PERI_MAPSIZE, PROT_READ|PROT_WRITE, MAP_SHARED,
		  	  	  	  	  	  bcm2836_devmem_h, BCM2836_PERI_BASE+BCM2836_GPIO_BASEOFFSET);
  if (bcm2836_baseaddr_ptr < 0) {
    printf("Failed to map /dev/mem: %s\n", strerror(errno));
    close(bcm2836_devmem_h);
    bcm2836_devmem_h = 0;
    return -1;
  }

  return 0;
}

void BCM2836_Close(void)
{

  if (bcm2836_baseaddr_ptr != NULL) {
    if (munmap(bcm2836_baseaddr_ptr, BCM2836_PERI_MAPSIZE) < 0) {
      return;
    }
    bcm2836_baseaddr_ptr = NULL;
  }

  if (bcm2836_devmem_h > 0) {
	close(bcm2836_devmem_h);
	bcm2836_devmem_h = 0;
  }

  return;
}

void BCM2836_GPIO_PinSelFun(unsigned int gpiono, gpfsel_function fun)
{
  if (gpiono > 53)
	  return;

  volatile uint32_t* fsel_reg_ptr = (uint32_t*) bcm2836_baseaddr_ptr;

  uint32_t fsel_copy = fsel_reg_ptr[gpiono/10];
  fsel_copy &= ~((0b111) << 3*(gpiono%10));
  fsel_copy |= (fun      << 3*(gpiono%10));
  fsel_reg_ptr[gpiono/10] = fsel_copy;

  return;
}

void BCM2836_GPIO_PinSet(unsigned int gpiono)
{
  if (gpiono > 53) {
	return;
  }

  volatile uint32_t* set_reg_ptr = (uint32_t*) (bcm2836_baseaddr_ptr + BCM2836_GPSET_OFFSET);
  if (gpiono > 31) {
	set_reg_ptr++;
  }

  *set_reg_ptr = 1 <<  gpiono % 32;
  return;
}

void BCM2836_GPIO_PinClr(unsigned int gpiono)
{
  if (gpiono > 53) {
	return;
  }

  volatile uint32_t* clr_reg_ptr = (uint32_t*) (bcm2836_baseaddr_ptr+BCM2836_GPCLR_OFFSET);
  if (gpiono > 31) {
	clr_reg_ptr++;
  }

  *clr_reg_ptr = 1 << gpiono % 32;
  return;
}

void BCM2836_SPI0_Init() {
  if (bcm2836_devmem_h < 0) {
  	BCM2836_Close();
  }

  volatile uint32_t* cs_reg_ptr  = (uint32_t*) (BCM2836_SPI_REGADDR(BCM2835_SPI0_CS_OFFSET));
  *cs_reg_ptr = 0;

  volatile uint32_t* clk_reg_ptr = (uint32_t*) (BCM2836_SPI_REGADDR(BCM2835_SPI0_CLK_OFFSET));

  BCM2836_GPIO_PinSelFun(SPI0_CE0_GPIONO,  BCM2836_GPFSEL_ALT0);
  BCM2836_GPIO_PinSelFun(SPI0_CE1_GPIONO,  BCM2836_GPFSEL_ALT0);
  BCM2836_GPIO_PinSelFun(SPI0_CLK_GPIONO,  BCM2836_GPFSEL_ALT0);
  BCM2836_GPIO_PinSelFun(SPI0_MOSI_GPIONO, BCM2836_GPFSEL_ALT0);
  BCM2836_GPIO_PinSelFun(SPI0_MISO_GPIONO, BCM2836_GPFSEL_ALT0);

  // Clear Fifos
  *cs_reg_ptr = BCM2835_SPI0_CS_CLEAR;

  // Mode settings for MCP3008: Clear these Bits
  *cs_reg_ptr &= ~BCM2835_SPI0_CS_CS
		       & ~BCM2835_SPI0_CS_CPOL
			   & ~BCM2835_SPI0_CS_CPHA
			   & ~BCM2835_SPI0_CS_CSPOL0
			   & ~BCM2835_SPI0_CS_CSPOL1 ;

  // Clock divider at 3.9Mhz for MCP3008
  *clk_reg_ptr = 64;

  return;
}

void BCM2836_SPI0_Send(size_t dataSz, uint8_t *txdata_ptr, uint8_t *rxdata_ptr) {
  volatile uint32_t* cs_reg_ptr   = (uint32_t*) (BCM2836_SPI_REGADDR(BCM2835_SPI0_CS_OFFSET));
  volatile uint32_t* fifo_reg_ptr = (uint32_t*) (BCM2836_SPI_REGADDR(BCM2835_SPI0_FIFO_OFFSET));

  size_t rxDataCount = 0;
  size_t txDataCount = 0;

  *cs_reg_ptr &= ~BCM2835_SPI0_CS_TA;
  *cs_reg_ptr |= BCM2835_SPI0_CS_CLEAR;
  *cs_reg_ptr |= BCM2835_SPI0_CS_TA;

  while(rxDataCount < dataSz) {
	  if (rxDataCount < dataSz && ((*cs_reg_ptr) & BCM2835_SPI0_CS_RXD)) {
		  uint32_t rxd  = *fifo_reg_ptr;
		  rxdata_ptr[rxDataCount++] = rxd;
	  }
	  if (txDataCount < dataSz && ((*cs_reg_ptr) & BCM2835_SPI0_CS_TXD)) {
		  uint32_t txd  = txdata_ptr[txDataCount++];
		  *fifo_reg_ptr = txd;
	  }
  }

  while( ((*cs_reg_ptr) & BCM2835_SPI0_CS_DONE) == 0) {}

  *cs_reg_ptr &= ~BCM2835_SPI0_CS_TA;
  return;
}
