#include <iostream>
#include <unistd.h>
#include <csignal>

#include "Ampel.h"
#include "ampel_peripheral_x86.h"
#include "ampel_peripheral_rPi.h"

/* Grouped conveniently on LK-Linker-Kit Board */
#define RPI_GPIO_GREEN  5   // LK D5
#define RPI_GPIO_YELLOW 4   // LK D4
#define RPI_GPIO_RED    2   // LK D2
#define RPI_GPIO_SIGNAL 12	// LK D12


/* Alternative: Grouped conveniently on Pi Header
#define RPI_GPIO_SIGNAL 24 // Pin 18
#define RPI_GPIO_GREEN  17 // Pin 11
#define RPI_GPIO_YELLOW 27 // Pin 13
#define RPI_GPIO_RED    22 // Pin 15
*/

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
        sleep(1);
    }
    cout << "Ampel now stopping" << endl;
    
    b.stop();
    a.stop();
    
    return 0;
}
