#ifndef PEDESTRIANLIGHT_H
#define PEDESTRIANLIGHT_H

#include "Light.h"
#include "setLight.h"
//#include "ThreadedSensor.h"


using namespace std;




class PedestrianLight : public Light{

    public:
        PedestrianLight( );
        ~PedestrianLight();

        void run( bool in_blocking );

        void compareStates();

        using Light::createStateRequest;
        using Light::setCurrentState;
        using Light::setNextState;

        void switchTo_RED();
        void switchTo_GREEN();
        void switchTo_RED_WITH_WAIT_LIGHT();

    protected:


    private:



};




#endif // PEDESTRIANLIGHT_H
