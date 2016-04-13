#ifndef THREADEDSENSOR_H_INCLUDED
#define THREADEDSENSOR_H_INCLUDED

class ThreadedSensor{
    public:

        ThreadedSensor();

        void checkTrigger( bool* in_running );

        void set_TriggerDetected();                         //overwrite Sensor (for testing)

        bool read_triggerDetected();


    protected:
        bool triggerDetected/* = false*/;

    private:


};














#endif // THREADEDSENSOR_H_INCLUDED
