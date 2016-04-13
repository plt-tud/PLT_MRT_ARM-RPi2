#include <stdio.h>

#include "config.h"



#ifdef PI
#include "bcm2835.h"
#endif // PI



#include "setLight.h"




/**
 * @brief Sets GPIO (aka LED) to new value
 *
 * @param in_whichLED: Which LED should be changed?
 * @param in_newState: New Value
 */
int setLight( LED in_whichLED, int in_newState ){
    int success = 0;


    #ifdef PI
    if( in_newState == 1){
        bcm2835_gpio_set(in_whichLED);       //on
    }else{
        bcm2835_gpio_clr(in_whichLED);       //off
    }
    success = 1;
    #endif // PI




    #ifdef X86
    if( in_newState == 1 ){              //on
        if( in_whichLED == RED ){
            printf("\nturning RED-LED on\n");
        }else if(in_whichLED == YELLOW){
            printf("turning YELLOW-LED on\n");
        }else if(in_whichLED == GREEN){
            printf("truning GREEN-LED on\n");
        }else if(in_whichLED == WAIT){
            printf("truning WAIT-LED on\n");
        }
    }else{                                  //off
        if( in_whichLED == RED ){
            printf("\nturning RED-LED off\n");
        }else if(in_whichLED == YELLOW){
            printf("turning YELLOW-LED off\n");
        }else if(in_whichLED == GREEN){
            printf("truning GREEN-LED off\n");
        }else if(in_whichLED == WAIT){
            printf("truning WAIT-LED off\n");
        }
    }
    success = 1;
    #endif // X86

    return success;
}



/**
 * @brief initializes output
 */
int initOutput(){


    int success = 0;

    #ifdef PI
    // init bcm2835
	if( bcm2835_init() == 0 ){
		printf("bcm2835 init failed\n");
		return 1;
	}else{
		printf("bcm2835 init successfully\n");
	}
	// set GPIO's as output:
	bcm2835_gpio_fsel(RED, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(YELLOW, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(GREEN, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(WAIT, BCM2835_GPIO_FSEL_OUTP);

    printf("clear all GPIOs now!");
	int GPIOs[] = { 26, 22, 21, 20, 25, 21, 20, 19, 14, 13, 12, 5, 15, 14, 13, 6, 3, 2, 4, 5, 15, 16, 26, 27 };
	for( int i = 0; i < sizeof( GPIOs ); i++ ){
        bcm2835_gpio_clr(GPIOs[i]);
	}

	bcm2835_spi_begin();

    #endif // PI


    #ifdef X86
    printf("terminal output...");
    #endif // X86



    return success;


}









