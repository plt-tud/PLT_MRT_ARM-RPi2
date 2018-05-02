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

#include "RemoteAmpel.h"

void signalHandler_exit(int signnum) {
  runAmpel = false;
}

int main(int argc, char **argv) {
    Ampel a;
    RemoteAmpel b("opc.tcp://127.0.0.1:4840");
    
    runAmpel = true;
    
    signal(SIGTERM, &signalHandler_exit);
    signal(SIGINT,  &signalHandler_exit);  
    
    a.addPeripheral(new ampel_peripheral_x86());
    a.addPeripheral(new ampel_peripheral_rPi(RPI_GPIO_RED, RPI_GPIO_YELLOW, RPI_GPIO_GREEN, RPI_GPIO_SIGNAL));
    
    a.start();
    b.start();
    
    while (runAmpel) {
        if(b.getPhaseCommand() == PHASE_GREEN)
          cout << "Gruen!" << endl;

        sleep(1);
    }
    cout << "Ampel now stopping" << endl;
    
    b.stop();
    a.stop();
    
    return 0;
}
