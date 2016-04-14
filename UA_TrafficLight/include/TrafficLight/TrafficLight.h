/*
 * Copyright (c) 2016 Chris Iatrou <Chris_Paul.Iatrou@tu-dresden.de>
 * Chair for Process Systems Engineering
 * Technical University of Dresden
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

#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "Automaton.h"
#include <map>
#include <list>
#include <thread>
#include <time.h>

#include "config_global.h"
#include "BinarySensor.h"
#include "TrafficLightOutputFacility.h"
#include "ua_mapped_class.h"

typedef enum {
  RQM_UNSPECIFIED,
  RQM_RED,
  RQM_GREEN
} requestedMode_t;

class TrafficLight : ua_mapped_class
{
private:
  UA_ServerConfig       server_config;
  UA_ServerNetworkLayer server_nl;
  UA_Logger             logger;
  
  UA_NodeId instanceBaseId;
  
  Automaton  *stateMachine;
  std::list<Transition*> transitions;
  std::map<std::string, State*> states;
  
  bool thread_run;
  bool thread_alive;
  std::thread *thr_automaton;
  std::thread *thr_uaserver;
  
  time_t warn_blinkInt;
  time_t yellowPhaseLength;
  time_t autonomous_greenPhaseLength;
  bool   autonomous_greenPhase;
  bool   autonomous_sensorAcknowledge;
  
  Automaton* constructStateMachine();
  void construct_uaserver();
  UA_StatusCode ua_mapSelfToNamespace();
protected:
  bool   hasController;
  bool   needsController;
  time_t last_transition_timestamp;
  requestedMode_t controllerRequestedMode;

public:
  time_t tick_interval;
  BinarySensor               *sensor;
  TrafficLightOutputFacility *output;
  
  TrafficLight(time_t tick_interval = DEFAULT_TRAFFICLIGHT_TICK, BinarySensor_config *sc=nullptr, TrafficLightOutputFacility_config *oc=nullptr);
  bool doRun();
  bool doStop();
  bool isRunning();
  void workerThread();
  
  bool readSensor();
  
  void updateLastTransitionTimestamp();
  time_t getLastTransitionTimestamp();
  
  bool getHasController();
  bool getNeedsController();
  void setHasController(bool b);
  void setNeedsController(bool b);
  time_t getYellowPhaseLength();
  void   setYellowPhaseLength(time_t t);
  time_t getAutonomousGreenPhaseLength();
  void   setAutonomousGreenPhaseLength(time_t t);
  time_t getWarnBlinkInterval();
  void   setWarnBlinkInterval(time_t t);
  
  bool getAutonomousGreenPhase();
  void setAutonomousGreenPhase(bool b);
  bool getAutonomousSensorAcknowledge();
  void setAutonomousSensorAcknowledge(bool b);
  
  requestedMode_t getControllerRequestedMode();
  void            setControllerRequestedMode(requestedMode_t m);
};

#endif // TRAFFICLIGHT_H
