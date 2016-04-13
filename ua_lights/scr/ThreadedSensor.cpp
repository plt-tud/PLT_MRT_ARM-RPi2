#include <iostream>
#include <unistd.h>      //sleep
#include <thread>


#include "config.h"
#include "setLight.h"

//#ifdef PI
#include "bcm2835.h"
//#endif // PI

#include "ThreadedSensor.h"

#define TIME_BETWEEN_POLLING 1      //in seconds
#define ADC_CHANNEL 1


using namespace std;


/**
 * @brief ThreadedSensor-Construtor
 */
ThreadedSensor::ThreadedSensor(){
    cout << "ThreadedSensor::ThreadedSensor()" << endl;

    cout << "init output" << endl;
    initOutput();

    triggerDetected = false;

    /*!
    thread checkTrigger_Thread(&ThreadedSensor::checkTrigger, this);
    checkTrigger_Thread.detach();
    */


    cout << "leaving ThreadedSensor::ThreadedSensor()" << endl;
}


/**
 * @brief Periodically checks trigger (will be startet in own thread)
 *
 */
void ThreadedSensor::checkTrigger( bool* in_running ){
    cout << "entering ThreadedSensor::checkTrigger()" << endl;


    //char out[] = { 0b00000001, 0b00000000, 0b00000000 };  // for channel 0
    char out[] = { 0b00000001, 0b00010000, 0b00000000 };    // for channel 1
	char in[] = { 0x30, 0x30, 0x30 };

    #ifdef PI
    cout << "target: PI" << endl;
    int init_success = bcm2835_init();
    if( init_success == 1 ){
        cout << "bcm2835_init() successful" << endl;
    }else{
        cout << "bcm2835_init() not sucessful. Exit now!" << endl;
        exit(0);
    }

    bcm2835_spi_setClockDivider( BCM2835_SPI_CLOCK_DIVIDER_128 );
    #endif // PI



    #ifdef X86
    cout << "target: x86" << endl;
    #endif // X86


    while( *in_running ){

        usleep(TIME_BETWEEN_POLLING*1000000);           //waiting... usleep() takes time in µs

        if( triggerDetected == false ){                 //In case the sensor already returned 'true', there is no need to check again (state will be reset through reading the value)

            //cout << "checking triggerState" << endl;

            #ifdef PI
            bcm2835_spi_transfernb( out, in, 3);
            #endif // PI
            #ifdef X86
            in[2]=0;
            #endif // X86

            if( in[2] > 20 ){
                    cout << "triggerDetected = true" << endl;
                    triggerDetected = true;
            }

        }
    }
    cout << "leaving checkTrigger()" << endl;
}



/**
 * @brief Sets 'triggerDetected' to 'true'
 */
void ThreadedSensor::set_TriggerDetected(){
    triggerDetected = true;
}




/**
 * @brief Returns 'triggerDetected' and resets variable
 */
bool ThreadedSensor::read_triggerDetected(){      //read and reset
    bool output = false;

    if( triggerDetected == true ){
        triggerDetected = false;        //reset
        output = true;
    }

    return output;
}
