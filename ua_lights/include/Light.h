#ifndef LIGHT_H
#define LIGHT_H

#include <time.h>

#include "setLight.h"
#include "ThreadedSensor.h"
#include "Opc_ua.h"

#define TIME_TO_RED 1
#define TIME_TO_RED_YELLOW 2
#define TIME_TO_GREEN 3
#define TIME_TO_YELLOW 3
#define TIME_TO_RED_WITH_WAIT_LIGHT 1


using namespace std;

/*

Traffic-Light:

                |---|                       |---|                       |---|                       |---|                       |---|
        Red:    | X |                       | X |                       |   |                       |   |                       | X |
                |---|                       |---|                       |---|                       |---|                       |---|
        Yellow: |   |           ->          | X |           ->          |   |           ->          | X |           ->          |   |
                |---|                       |---|                       |---|                       |---|                       |---|
        Green:  |   |                       |   |                       | X |                       |   |                       |   |
                |---|                       |---|                       |---|                       |---|                       |---|

    State:      RED_PHASE,                  RED_YELLOW_PHASE,           GREEN_PHASE,                YELLOW_PHASE,               RED_PHASE






Pedestrian-Light:

              |-------|                   |-------|                   |-------|                   |-------|                                   |-------|
              |       |                   |       |                   |       |                   |       |                                   |       |
              |       |                   |       |                   |       |                   |       |                                   |       |
              |-------|                   |-------|                   |-------|                   |-------|                                   |-------|
                |---|                       |---|                       |---|                       |---|                                       |---|
        Red:    | X |           ->          | X |           ->          |   |           ->          |   |                           ->          | X |
                |---|                       |---|                       |---|                       |---|                                       |---|
        Green:  |   |                       |   |                       | X |                       | X |                                       |   |
                |---|                       |---|                       |---|                       |---|                                       |---|

    State:      RED_PHASE                   FROM_RED_TO_GREEN,          GREEN_PHASE,                FROM_GREEN_TO_RED,                          RED_PHASE


                                          |-------|                   |-------|                   |-------|                   |-------|
                                          |       |                   | Sign. |                   | Sign. |                   |       |
                                          |       |                   |comming|                   |comming|                   |       |
                                    |     |-------|                   |-------|                   |-------|                   |-------|     ^
                                    |       |---|                       |---|                       |---|                       |---|       |
        Red:                        ->      | X |           ->          | X |           ->          | X |           ->          |   |      _|
                                            |---|                       |---|                       |---|                       |---|
        Green:                              |   |                       |   |                       |   |                       | X |
                                            |---|                       |---|                       |---|                       |---|

    State:                          FROM_RED_TO_RED_WITH_WAIT_LIGHT,    RED_PHASE_WITH_WAIT_LIGHT,  GREEN_PHASE,                FROM_RED_WITH_WAIT_LIGHT_TO_GREEN


*/




typedef enum{
                IDYL = 0,   //not used yet

                /*
                RED_PHASE,
                GREEN_PHASE,
                FROM_GREEN_TO_RED,
                FROM_RED_TO_GREEN,
                */

                RED_PHASE = 1,
                RED_YELLOW_PHASE = 2,
                GREEN_PHASE = 3,
                YELLOW_PHASE = 4,



                //for PedestrianLight only
                /*
                FROM_RED_TO_RED_WITH_WAIT_LIGHT = 5,
                FROM_RED_WITH_WAIT_LIGHT_TO_GREEN = 6,
                RED_PHASE_WITH_WAIT_LIGHT = 7,
                */
                RED_WITH_WAIT_LIGHT = 5,

            }Phase;



typedef struct{

                Phase state;            //what state has been requested
                time_t createTime;            //create-time

                }State_t;



class Light : public ThreadedSensor, public Opc_ua{



    public:
        Light();
        ~Light();


        using ThreadedSensor::read_triggerDetected;
        using ThreadedSensor::set_TriggerDetected;

        Phase getCurrentState();

        void createStateRequest( Phase in_requestedState );
        void setCurrentState( Phase in_requestedState );
        void setNextState( Phase in_nextState );

        void shutdown();

    protected:

        bool running;
        State_t currentState;
        State_t requestedState;
        State_t nextState;

    private:



};

#endif // LIGHT_H
