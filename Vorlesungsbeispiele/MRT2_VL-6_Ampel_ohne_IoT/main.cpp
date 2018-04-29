#include <iostream>
#include <unistd.h>
#include <csignal>

#include "Ampel.h"
#include "ampel_peripheral_x86.h"
#include "ampel_peripheral_rPi.h"

#define RPI_GPIO_GREEN  5
#define RPI_GPIO_YELLOW 4
#define RPI_GPIO_RED    2
#define RPI_GPIO_SIGNAL 27

bool runAmpel;

void signalHandler_exit(int signnum) {
  runAmpel = false;
}

int main(int argc, char **argv) {
    //Ampel a((struct timespec) {1,0});
    Ampel a;
    runAmpel = true;
    
    signal(SIGTERM, &signalHandler_exit);
    signal(SIGINT,  &signalHandler_exit);
    
    a.addPeripheral(new ampel_peripheral_x86());
    a.addPeripheral(new ampel_peripheral_rPi(RPI_GPIO_RED, RPI_GPIO_YELLOW, RPI_GPIO_GREEN, RPI_GPIO_SIGNAL));
    
    //a.setController(true);
    
    //a.start();
    while (runAmpel) {
        a.run();
        sleep(1);
        if ( a.getSensor()) {
            if (a.getPhaseCommand() == PHASE_GREEN)
                a.setPhaseCommand(PHASE_RED);
            else
                a.setPhaseCommand(PHASE_GREEN);
        }
    }
    //a.stop();
    
    return 0;
}
