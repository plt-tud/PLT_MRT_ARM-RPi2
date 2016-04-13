#include <iostream>
#include <unistd.h>      //sleep
#include <time.h>
#include <thread>


#include "TrafficLight.h"
#include "setLight.h"

using namespace std;




/**
 * @brief Constructor of TrafficLight
 */
TrafficLight::TrafficLight( ){
    cout << "TrafficLight-Constructor called" << endl;


    //createStateRequest(RED_PHASE);
    //setNextState(RED_PHASE);
    //setCurrentState(RED_PHASE);

    requestedState.state = RED_PHASE;
    currentState.state = RED_PHASE;
    nextState.state = RED_PHASE;

    requestedState.createTime = 0;      //to make valgrind happy
    nextState.createTime = 0;
    currentState.createTime = 0;

    cout << "leaving TrafficLight::TrafficLight()" << endl;

}



/**
 * @brief Destructor of TrafficLight
 */
TrafficLight::~TrafficLight(){

    cout << "TrafficLight-Destructor called" << endl;

}



void TrafficLight::run( bool in_blocking ){

    running = true;

    thread opc_ua_Thread( &Opc_ua::run_Opc_ua, this, &running );
    if( in_blocking == false ){
        opc_ua_Thread.detach();
    }

    thread checkTrigger_Thread(&ThreadedSensor::checkTrigger, this, &running);

    if( in_blocking == false ){
        checkTrigger_Thread.detach();
    }


    thread compareStates_Thread(&TrafficLight::compareStates, this);

    if( in_blocking == false ){
        compareStates_Thread.detach();
    }

    if( in_blocking ){
        opc_ua_Thread.join();
        checkTrigger_Thread.join();
        compareStates_Thread.join();
    }


}




void TrafficLight::compareStates(){
    cout << "entering TrafficLight::compareStates()" << endl;

    while( running ){

        usleep(500000);      //0.5 s

        if( currentState.state != requestedState.state ){
            //cout << "currentState.state != requestedState.state" << endl;

            if( currentState.state == RED_PHASE ){
                if( requestedState.state == GREEN_PHASE ){
                    setNextState( RED_YELLOW_PHASE );
                }else{
                    cout << "invalid state-request (currentState.state == RED_PHASE)" << endl;
                }
            }else if( currentState.state == RED_YELLOW_PHASE ){
                if( requestedState.state == GREEN_PHASE ){
                    setNextState( GREEN_PHASE );
                }else{
                    cout << "invalid state-request (currentState.state == RED_YELLOW_PHASE)" << endl;
                }

            }else if( currentState.state == GREEN_PHASE ){
                if( requestedState.state == RED_PHASE ){
                    setNextState( YELLOW_PHASE );
                }else{
                    cout << "invalid state-request (currentState.state == GREEN_PHASE)" << endl;
                }
            }else if( currentState.state == YELLOW_PHASE ){
                if( requestedState.state == RED_PHASE ){
                    setNextState( RED_PHASE );
                }else{
                    cout << "invalid state-request (currentState.state == YELLOW_PHASE)" << endl;
                }
            }else{
                cout << "unknown state" << endl;
            }

            if( nextState.state == RED_PHASE ){
                switchTo_RED();
            }else if( nextState.state == RED_YELLOW_PHASE ){
                switchTo_RED_YELLOW();
            }else if( nextState.state == GREEN_PHASE ){
                switchTo_GREEN();
            }else if( nextState.state == YELLOW_PHASE ){
                switchTo_YELLOW();
            }else{
                cout << "whut?" << endl;
            }

        }else{
            //cout << "currentState == requestedState" << endl;
        }

    }

    cout << "leaving TrafficLight::compareStates()" << endl;

}

void TrafficLight::switchTo_RED(){
    //cout << "entering TrafficLight::switchTo_RED()" << endl;

    //double diffTime = difftime( time(NULL), nextState.createTime );
    //double currentTime = time(NULL);

    if( difftime( time(NULL), nextState.createTime ) > TIME_TO_RED ){

        setLight(RED, true);
        setLight(YELLOW, false);
        setLight(GREEN, false);

        cout << "           |---|   " << endl;
        cout << "Red:       | X |   " << endl;
        cout << "           |---|   " << endl;
        cout << "Yellow:    |   |   " << endl;
        cout << "           |---|   " << endl;
        cout << "Green:     |   |   " << endl;
        cout << "           |---|   " << endl;

        setCurrentState(RED_PHASE);
    }else{
        //cout << "TrafficLight::switchTo_RED(): not time to change state" << endl;
    }

}


void TrafficLight::switchTo_RED_YELLOW(){

    //double diffTime = difftime( time(NULL), nextState.createTime );
    //double currentTime = time(NULL);
    //cout << "diffTime: " << diffTime << endl;

    if( difftime( time(NULL), nextState.createTime ) > TIME_TO_RED_YELLOW ){

        setLight(RED, true);
        setLight(YELLOW, true);
        setLight(GREEN, false);

        cout << "           |---|   " << endl;
        cout << "Red:       | X |   " << endl;
        cout << "           |---|   " << endl;
        cout << "Yellow:    | X |   " << endl;
        cout << "           |---|   " << endl;
        cout << "Green:     |   |   " << endl;
        cout << "           |---|   " << endl;

        setCurrentState(RED_YELLOW_PHASE);
    }else{
        //cout << "TrafficLight::switchTo_RED_YELLOW(): not time to change state" << endl;
    }

}

void TrafficLight::switchTo_GREEN(){

    //double diffTime = difftime( time(NULL), nextState.createTime );
    //double currentTime = time(NULL);

    if( difftime( time(NULL), nextState.createTime ) > TIME_TO_GREEN ){

        setLight(RED, false);
        setLight(YELLOW, false);
        setLight(GREEN, true);

        cout << "           |---|   " << endl;
        cout << "Red:       |   |   " << endl;
        cout << "           |---|   " << endl;
        cout << "Yellow:    |   |   " << endl;
        cout << "           |---|   " << endl;
        cout << "Green:     | X |   " << endl;
        cout << "           |---|   " << endl;

        setCurrentState(GREEN_PHASE);
    }else{
        //cout << "TrafficLight::switchTo_GREEN(): not time to change state" << endl;
    }

}

void TrafficLight::switchTo_YELLOW(){

    if( difftime( time(NULL), nextState.createTime ) > TIME_TO_YELLOW ){

        setLight(RED, false);
        setLight(YELLOW, true);
        setLight(GREEN, false);

        cout << "           |---|   " << endl;
        cout << "Red:       |   |   " << endl;
        cout << "           |---|   " << endl;
        cout << "Yellow:    | X |   " << endl;
        cout << "           |---|   " << endl;
        cout << "Green:     |   |   " << endl;
        cout << "           |---|   " << endl;

        setCurrentState(YELLOW_PHASE);
    }else{
        //cout << "not time to change state" << endl;
    }

}

