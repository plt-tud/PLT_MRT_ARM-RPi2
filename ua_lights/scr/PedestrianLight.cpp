#include <iostream>
#include <thread>
#include <unistd.h>      //sleep

#include "PedestrianLight.h"
#include "setLight.h"

using namespace std;


/**
 * @brief Constructor of 'PedestrianLight'
 */
PedestrianLight::PedestrianLight(){
    cout << "PedestrianLight-Constructor called" << endl;

    //createStateRequest(RED_PHASE);
    //setNextState(RED_PHASE);
    //setCurrentState(RED_PHASE);

    requestedState.state = RED_PHASE;
    currentState.state = RED_PHASE;
    nextState.state = RED_PHASE;

    requestedState.createTime = 0;      //to make valgrind happy
    nextState.createTime = 0;
    currentState.createTime = 0;

    cout << "leaving PedestrianLight::PedestrianLight()" << endl;

}



/**
 * @brief Destructor of 'PedestrianLight'
 */
PedestrianLight::~PedestrianLight(){

    cout << "PedestrianLight-Destructor called" << endl;

}


void PedestrianLight::run( bool in_blocking ){

    running = true;

    thread opc_ua_Thread( &Opc_ua::run_Opc_ua, this, &running );
    if( in_blocking == false ){
        opc_ua_Thread.detach();
    }

    thread checkTrigger_Thread(&ThreadedSensor::checkTrigger, this, &running);

    if( in_blocking == false ){
        checkTrigger_Thread.detach();
    }


    thread compareStates_Thread(&PedestrianLight::compareStates, this);

    if( in_blocking == false ){
        compareStates_Thread.detach();
    }

    if( in_blocking ){
        opc_ua_Thread.join();
        checkTrigger_Thread.join();
        compareStates_Thread.join();
    }
}



void PedestrianLight::compareStates(){
    cout << "entering PedestrianLight::compareStates()" << endl;

    while( running ){
        usleep(500000);    //0.5 s

        if( currentState.state != requestedState.state ){

            if( currentState.state == RED_PHASE ){
                if( requestedState.state == GREEN_PHASE ){
                    setNextState( GREEN_PHASE );
                }else if( requestedState.state == RED_WITH_WAIT_LIGHT ){
                    setNextState( RED_WITH_WAIT_LIGHT );
                }else{
                    cout << "invalid state-request (currentState.state == RED_PHASE)" << endl;
                }
            }else if( currentState.state == GREEN_PHASE ){
                if( requestedState.state == RED_PHASE ){
                    setNextState( RED_PHASE );
                }else{
                    cout << "invalid state-request (currentState.state == GREEN_PHASE)" << endl;
                }
            }else if( currentState.state == RED_WITH_WAIT_LIGHT ){
                if( requestedState.state == GREEN_PHASE ){
                    setNextState( GREEN_PHASE );
                }else{
                    cout << "invalid state-request (currentState.state == RED_WITH_WAIT_LIGHT)" << endl;
                }
            }



            if( nextState.state == RED_PHASE ){
                switchTo_RED();
            }else if( nextState.state == GREEN_PHASE ){
                switchTo_GREEN();
            }else if( nextState.state == RED_WITH_WAIT_LIGHT ){
                switchTo_RED_WITH_WAIT_LIGHT();
            }else{
                cout << "whut?" << endl;
            }

        }


    }


    cout << "leaving PedestrianLight::compareStates()" << endl;


}


void PedestrianLight::switchTo_RED(){
    //cout << "entering PedestrianLight::switchTo_RED()" << endl;

    if( difftime( time(NULL), nextState.createTime ) > TIME_TO_RED ){

        setLight(WAIT, false);
        setLight(RED, true);
        setLight(GREEN, false);

        cout << "         |-------| " << endl,
        cout << "         |       | " << endl;
        cout << "Wait:    |       | " << endl;
        cout << "         |-------| " << endl;
        cout << "           |---|   " << endl;
        cout << "Red:       | X |   " << endl;
        cout << "           |---|   " << endl;
        cout << "Green:     |   |   " << endl;
        cout << "           |---|   " << endl;

        setCurrentState(RED_PHASE);
    }else{
        //cout << "not time to change state" << endl;
    }

}


void PedestrianLight::switchTo_GREEN(){
    //cout << "entering PedestrianLight::switchTo_GREEN()" << endl;

    if( difftime( time(NULL), nextState.createTime ) > TIME_TO_GREEN ){
        setLight(WAIT, false);
        setLight(RED, false);
        setLight(GREEN, true);

        cout << "         |-------| " << endl,
        cout << "         |       | " << endl;
        cout << "Wait:    |       | " << endl;
        cout << "         |-------| " << endl;
        cout << "           |---|   " << endl;
        cout << "Red:       |   |   " << endl;
        cout << "           |---|   " << endl;
        cout << "Green:     | X |   " << endl;
        cout << "           |---|   " << endl;

        setCurrentState(GREEN_PHASE);
    }else{
        //cout << "not time to change state" << endl;
    }

}


void PedestrianLight::switchTo_RED_WITH_WAIT_LIGHT(){
    //cout << "PedestrianLight::switchTo_RED_WITH_WAIT_LIGHT()" << endl;

    if( difftime( time(NULL), nextState.createTime ) > TIME_TO_RED_WITH_WAIT_LIGHT ){
        setLight(WAIT, true);
        setLight(RED, true);
        setLight(GREEN, false);

        cout << "         |-------| " << endl,
        cout << "         | Sign. | " << endl;
        cout << "Wait:    |comming| " << endl;
        cout << "         |-------| " << endl;
        cout << "           |---|   " << endl;
        cout << "Red:       | X |   " << endl;
        cout << "           |---|   " << endl;
        cout << "Green:     |   |   " << endl;
        cout << "           |---|   " << endl;

        setCurrentState(RED_WITH_WAIT_LIGHT);
    }else{
        //cout << "not time to change state" << endl;
    }

}
