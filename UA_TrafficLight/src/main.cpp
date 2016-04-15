#include <iostream>
#include <unistd.h>

#include "TrafficLight.h"

#ifdef BUILD_RPI
#include "bcm2835.h"
#endif

TrafficLight *controlledTrafficLight;

static void SigHandler_Int(int sign) {
  controlledTrafficLight->doStop();
}


bool fakeSensor_trigger = false;
const bool readFakeSensor() {
#ifdef BUILD_RPI
  return (bcm2835_gpio_lev(RPI_GPIO_PB) == 1);
#else
  if (fakeSensor_trigger) {
    fakeSensor_trigger = false;
    return true;
  }
#endif
  return false;
}

const void setFakeOutput(bool red, bool yellow, bool green) {
  #ifdef BUILD_RPI
  if (red)    bcm2835_gpio_set(RPI_GPIO_RED);
  else        bcm2835_gpio_clr(RPI_GPIO_RED);
  
  if (yellow) bcm2835_gpio_set(RPI_GPIO_YELLOW);
  else        bcm2835_gpio_clr(RPI_GPIO_YELLOW);
  
  if (green)  bcm2835_gpio_set(RPI_GPIO_GREEN);
  else        bcm2835_gpio_clr(RPI_GPIO_GREEN);
  #endif
  return;
}

const void setFakeSignal(bool signal) {
  #ifdef BUILD_RPI
  if (signal)   bcm2835_gpio_set(RPI_GPIO_SIGNAL);
  else          bcm2835_gpio_clr(RPI_GPIO_SIGNAL);
  #endif
  return;
}

int main(int argc, char *argv[]){
  BinarySensor_config sc = (BinarySensor_config) {
    .readSensorFunction = readFakeSensor
  };
  TrafficLightOutputFacility_config oc = (TrafficLightOutputFacility_config ) {
    .hasSignal = true,
    .hasYellow = true,
    .extended_setOutput = setFakeOutput,
    .extended_setSignal = setFakeSignal
  };
  controlledTrafficLight = new TrafficLight(DEFAULT_TRAFFICLIGHT_TICK, &sc, &oc);
  //controlledTrafficLight->setNeedsController(false);
  
  #ifdef BUILD_RPI
  bcm2835_init();
  bcm2835_gpio_fsel(RPI_GPIO_RED,    BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(RPI_GPIO_YELLOW, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(RPI_GPIO_GREEN,  BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(RPI_GPIO_SIGNAL, BCM2835_GPIO_FSEL_OUTP);
  
  bcm2835_gpio_fsel(14,              BCM2835_GPIO_FSEL_INPT); // Cosmetic - GPIO14 is usually high after boot
  bcm2835_gpio_fsel(RPI_GPIO_PB,     BCM2835_GPIO_FSEL_INPT);
  bcm2835_gpio_set_pud(RPI_GPIO_PB,  BCM2835_GPIO_PUD_DOWN);
  #endif
  
  controlledTrafficLight->doRun();
  /* The following code would cause the traffic light to cycle once in supervised mode
  sleep(5);
  controlledTrafficLight->setHasController(true);
  controlledTrafficLight->setNeedsController(true);
  controlledTrafficLight->setAutonomousGreenPhase(false);
  controlledTrafficLight->setAutonomousSensorAcknowledge(false);
  sleep(2);
  fakeSensor_trigger = true;
  sleep(2);
  controlledTrafficLight->setControllerRequestedMode(RQM_GREEN);
  sleep(8);
  controlledTrafficLight->setControllerRequestedMode(RQM_RED);
  */
  while(controlledTrafficLight->isRunning()) {}

  #ifdef BUILD_RPI
  bcm2835_init();
  #endif  
  
  return 0;
}
