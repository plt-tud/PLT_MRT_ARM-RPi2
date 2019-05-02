#include <iostream>
#include <unistd.h>
#include <csignal>

#include "Ampel_typeDefinitions.h"

bool runAmpel;

#include "RemoteAmpel.h"

void signalHandler_exit(int signnum) {
  runAmpel = false;
}

int main(int argc, char **argv) {
    /* Unsere lokale IoT Ampel, die sich per OPC UA
	   mit dem Pi verbinden wird:
	 */
	RemoteAmpel b("opc.tcp://192.168.0.240:4840");
    
    runAmpel = true;
    
    signal(SIGTERM, &signalHandler_exit);
    signal(SIGINT,  &signalHandler_exit);  
    
    b.start();
    
    // Wir setzen uns als Controller... diese Einstellung wird per OPC UA an das Pi übertragen
    b.setController(true);

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
            if (b.getPhaseCommand() == PHASE_GREEN) {
              b.setPhaseCommand(PHASE_RED);
              cout << "Rot!" << endl;
            }
            else {
              b.setPhaseCommand(PHASE_GREEN);
              cout << "Gruen!" << endl;
            }
          }
        }
        
        sleep(1);
    }
    
    b.setController(false);
    b.stop();
    
    return 0;
}
