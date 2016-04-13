#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "Light.h"
//#include "ThreadedSensor.h"

using namespace std;



class TrafficLight : public Light{


    public:
        TrafficLight();
        ~TrafficLight();

        void run( bool in_blocking );

        void compareStates();

        using Light::createStateRequest;
        using Light::setCurrentState;
        using Light::setNextState;

        void switchTo_RED();
        void switchTo_RED_YELLOW();
        void switchTo_GREEN();
        void switchTo_YELLOW();


    protected:


    private:


};




#endif // TRAFFICLIGHT_H
