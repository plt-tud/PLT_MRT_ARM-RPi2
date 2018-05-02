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
    //RemoteAmpel b("opc.tcp://127.0.0.1:4840");
    RemoteAmpel b("opc.tcp://192.168.0.240:4840");
    
    runAmpel = true;
    
    signal(SIGTERM, &signalHandler_exit);
    signal(SIGINT,  &signalHandler_exit);  
    
    b.start();
    
    b.setController(true);
    cout << "Now Controlling our traffic light" << endl;

    bool sensorLatch = false;
    bool sense  = false;
    while (runAmpel) {
        sense = b.getSensor() ;
        
        if (sense && sensorLatch) {
          // Ein Sensor muss losgelassen werden, um als "neues druecken" zu gelten...
        }
        else {
          sensorLatch = sense;
          if(sensorLatch) {
            if (b.getPhaseCommand() == PHASE_GREEN)
              b.setPhaseCommand(PHASE_RED);
            else
              b.setPhaseCommand(PHASE_GREEN);
          }
        }
        
        sleep(1);
    }
    cout << "Ampel now stopping" << endl;
    
    b.setController(false);   
    b.stop();
    
    return 0;
}
