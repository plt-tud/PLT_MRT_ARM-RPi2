/*
 * Copyright (c) 2018 <copyright holder> <email>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef AMPEL_H
#define AMPEL_H

#include <list>
#include <map>

using namespace std;

#include "task.h"
#include "ampel_capabilities.h"
#include "Automaton.h"

typedef enum {PHASE_IDLE, PHASE_RED, PHASE_GREEN} ampel_phaseId;

class Ampel : public ampel_capabilities, public task
{
private:
    
protected:
    bool            controllerPresent;
    ampel_phaseId   phaseCommand;
    
    list<ampel_capabilities*>  p;
    
    list<Transition*>   t;
    map<string, State*> s;
     
    Automaton *  a;
    
public:
    Ampel(timespec tick_inteval);
    Ampel() :  Ampel((const timespec) {1,0}) {}; // Construct with default value (braucht C++11)
    ~Ampel();
    

    void addPeripheral(ampel_capabilities* p);
    void setController(bool present);
    bool hasController();
    
    void setPhaseCommand(ampel_phaseId command);
    ampel_phaseId getPhaseCommand();
    
    // Teil der Schnittstelle Peripheral...
    bool getSensor();
    
    void setRedLight(bool setLightOn);
    void setYellowLight(bool setLightOn);
    void setGreenLight(bool setLightOn);
    
    // Teil der Task-Schnittstelle
    void init();
    void run();
    void terminate();
};

#endif // AMPEL_H
