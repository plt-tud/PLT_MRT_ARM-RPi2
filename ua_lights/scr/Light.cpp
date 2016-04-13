#include <thread>
#include <unistd.h>     //usleep()
#include <iostream>

#include "Light.h"

#include "setLight.h"

using namespace std;

/**
 * @brief 'Light'-Constructor
 */
Light::Light(){

    cout << "Light-constructor called" << endl;

    running = false;
}


/**
 * @brief 'Light'-Destructor
 */
Light::~Light(){

    cout << "Light-destructor called" << endl;

}




/**
 * @brief Returns current state
 */
Phase Light::getCurrentState(){
    return currentState.state;
}



void Light::createStateRequest( Phase in_requestedState ){
    //cout << "Light::createStateRequest(): in_requestedState: " << in_requestedState << endl;

    if( requestedState.state != in_requestedState ){
        this->requestedState.state = in_requestedState;
        this->requestedState.createTime = time(NULL);
    }
    //cout << "leaving Light::createStateRequest()" << endl;

}



void Light::setCurrentState( Phase in_currentState ){
    //cout << "entering Light::setCurrentState(): in_currentState: " << in_currentState << endl;

    if( currentState.state != in_currentState ){
        currentState.state = in_currentState;
        currentState.createTime = time(NULL);
    }
}


void Light::setNextState( Phase in_nextState ){
    //cout << "entering Light::setNextState(): in_nextState: " << in_nextState << endl;

    if( nextState.state != in_nextState ){
        nextState.state = in_nextState;
        nextState.createTime = time(NULL);
    }

}


void Light::shutdown(){
    cout << "shutting down lights" << endl;

    running = false;

}
