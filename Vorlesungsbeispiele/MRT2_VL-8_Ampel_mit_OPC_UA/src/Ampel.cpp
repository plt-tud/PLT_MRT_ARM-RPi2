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

#include "Ampel.h"
#include <iostream>

#include "Ampel_Behaviors.h"

Ampel::Ampel(timespec tick_inteval) : task(tick_inteval)
{
    // Konstruktion unseres Ampel-Automaten
    s["offline_check"] = new State("offline_check",  behavior_offline_check, defaultBehavior, defaultBehavior, (void*) this);
    s["offline"]       = new State("offline",        behavior_offline,       defaultBehavior, defaultBehavior, (void*) this);
    s["red"]           = new State("red",            behavior_red,           defaultBehavior, defaultBehavior, (void*) this);
    s["redToGreen"]    = new State("redToGreen",     behavior_redtogreen,    defaultBehavior, defaultBehavior, (void*) this);
    s["green"]         = new State("green",          behavior_green,         defaultBehavior, defaultBehavior, (void*) this);
    s["greenToRed"]    = new State("greenToRed",     behavior_greentored,    defaultBehavior, defaultBehavior, (void*) this);
     
    t.push_back(new Transition(*s["offline_check"],*s["offline"],       guard_hasNoController, defaultBehavior, (void*) this));
    t.push_back(new Transition(*s["offline_check"],*s["red"],           guard_hasController, defaultBehavior, (void*) this));
    t.push_back(new Transition(*s["red"],          *s["offline_check"], guard_hasNoController, defaultBehavior, (void*) this));
    t.push_back(new Transition(*s["green"]        ,*s["offline_check"], guard_hasNoController, defaultBehavior, (void*) this));
    t.push_back(new Transition(*s["red"],          *s["redToGreen"],    guard_greenPhaseRequested, defaultBehavior, (void*) this));
    t.push_back(new Transition(*s["redToGreen"],   *s["green"],         defaultGuard, defaultBehavior, (void*) this));
    t.push_back(new Transition(*s["green"],        *s["greenToRed"],    guard_redPhaseRequested, defaultBehavior, (void*) this));
    t.push_back(new Transition(*s["greenToRed"],   *s["red"],           defaultGuard, defaultBehavior, (void*) this));
    t.push_back(new Transition(*s["offline"],      *s["offline_check"], defaultGuard, defaultBehavior, (void*) this));
    
    a = new Automaton(*s["red"], t);
    
    // We have no controller...
    controllerPresent = false;
    
    // Our inital command is always RED
    phaseCommand = PHASE_RED;
    
    iot_server = new ampel_iot_opcua(this); // Pass ourselves as parent to be accessed by IoT-Callbacks
    
    return;
}

Ampel::~Ampel()
{
    // FIXME:
    // Normaler Stop-Code fuer eine Ampel? Alle Lichter ausschalten?
    
    return;
}

void Ampel::addPeripheral(ampel_capabilities* p)
{
    this->p.push_back(p);
}

void Ampel::setGreenLight(bool setLightOn)
{
    greenLight    = setLightOn;
    for(auto& p_p : this->p) {
        if (p_p)
            p_p->setGreenLight(setLightOn);
    }
}

void Ampel::setYellowLight(bool setLightOn)
{
    yellowLight    = setLightOn;
    for(auto& p_p : this->p) {
        if (p_p)
            p_p->setYellowLight(setLightOn);
    }
}


void Ampel::setRedLight(bool setLightOn)
{
    redLight    = setLightOn;
    for(auto& p_p : this->p) {
        if (p_p)
            p_p->setRedLight(setLightOn);
    }
}

bool Ampel::getSensor()
{
    // Wenn ein Sensor ausgeloest wurde, dann WAHR
    for(auto& p_p : this->p) {
        if (p_p)
            if (p_p->getSensor()) return true;
    }
    
    // Allow using our own capability-sensor boolean as overwrite.
    // This value is set from main or from IoT.
    if (sensor) {
        sensor = false;
        return true;
    }
    return false;
}

void Ampel::setController(bool present)
{
    // If we are registering a new controller and previously had none, make sure we have command RED again
    if (!controllerPresent && present) 
        phaseCommand = PHASE_RED;
    
    controllerPresent = present;
}

bool Ampel::hasController()
{
    return controllerPresent;
}

void Ampel::init()
{
    // Wir starten unsere Threads
    iot_server->start();
}

void Ampel::terminate()
{
    // Wir stoppen unsere Threads
    iot_server->stop();
    
    // FIXME:
    // Normaler Stop-Code fuer eine Ampel? Alle Lichter ausschalten?
}

void Ampel::run()
{
    // Update our Automaton
    //   Der Automat ist kein Task und implementiert nur ein Subset unserer Task-Schnittstelle (nur run())
    //   er kann daher nicht als thread gestartet werden
    a->run();
    
    return;
}

ampel_phaseId Ampel::getPhaseCommand()
{
    return this->phaseCommand;
}

void Ampel::setPhaseCommand(ampel_phaseId command)
{
    // Check that the command given (possibly as INT over IoT) is valid
    if (command == PHASE_RED || command == PHASE_GREEN)
        phaseCommand = command;
}
