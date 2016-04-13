
#include <iostream>      //cout
#include <unistd.h>      //sleep
#include <stdio.h>       //getchar()
#include <thread>


#include "Light.h"
#include "TrafficLight.h"
#include "PedestrianLight.h"

using namespace std;

void wait(){
    int key = getchar();
    while( key != 110 ){     //'n' in ascii
        cout << "press 'n' and then 'return' to continue!" << endl;
        key = getchar();
    }

}




void test(Light* in_light){


    cout << "\n\n\ntest: switch to green!" << endl;
    wait();
    in_light->createStateRequest(GREEN_PHASE);


    cout << "\n\ntest: switch to red" << endl;
    wait();
    in_light->createStateRequest(RED_PHASE);

    cout << "\n\ntest: read triggerDetected" << endl;
    wait();
    cout << "test: read_triggerDetected(): " << in_light->read_triggerDetected() << endl;


    cout << "\n\ntest: set triggerDetected and read again" << endl;
    wait();
    in_light->set_TriggerDetected();
    cout << "test: read_triggerDetected(): " << in_light->read_triggerDetected() << endl;

    cout << "\n\ntest: pull trigger now!" << endl;
    wait();

    cout << "\n\ntest: now: read_triggerDectedted()" << endl;
    wait();
    cout << "test: read_triggerDetected(): " << in_light->read_triggerDetected() << endl;

    cout << "\n\ntest: now again: read_triggerDectedted()" << endl;
    wait();
    cout << "test: read_triggerDetected(): " << in_light->read_triggerDetected() << endl;



}








int main(){



    sleep(1);
	cout << "\nwhat kind of traffic lights do you want to simulate with this pi?";
	int key = -1;
	while( (key != 49) && (key != 50) ){    // 49 = '1', 50 = '2' in ascii
        cout << "\npress 1 for a 'standard/car/traffic'-light and 2 for a pedestrian light" << endl;
        key = getchar();
	}

	if( key == 49 ){        // standard lights

        cout << "simulating a traffic-light" << endl;

        TrafficLight* lights = new TrafficLight();
        lights->run( false );       //non-blocking

        test(lights);

        lights->shutdown();
        usleep(10000000);





	}else{                  // pedestrian lights

        cout << "simulating a pedestrian light" << endl;



        PedestrianLight* lights = new PedestrianLight();
        lights->run( false );

        test(lights);

        lights->createStateRequest( RED_WITH_WAIT_LIGHT );

        lights->shutdown();
        usleep(10000000);

	}



    cout << "leaving main" << endl;
    return 0;

}

