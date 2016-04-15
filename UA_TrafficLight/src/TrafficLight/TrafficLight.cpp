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

#include "TrafficLightBehavior.h"
#include "TrafficLight.h"
#include "Behavior.h"
#include "BinarySensor.h"
#include <unistd.h>
#include <iostream>

#include "ua_proxies.h"
extern "C" 
{
  // open62541
  #include "ua_server.h"
  #include "logger_stdout.h"
  #include "networklayer_tcp.h"
  
  // Generated namespace init
  #include "ua_light_namespaceinit_generated.h"
}


TrafficLight::TrafficLight(time_t tick_interval, BinarySensor_config *sc, TrafficLightOutputFacility_config *oc) 
: ua_mapped_class(nullptr, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER))
{ 
  this->stateMachine = constructStateMachine();
  
  this->thread_run    = false;
  this->thread_alive  = false;
  
  this->thr_automaton = nullptr;
  this->thr_uaserver  = nullptr;
  
  this->tick_interval = tick_interval;
  
  this->warn_blinkInt                = 1;
  this->yellowPhaseLength            = 2;
  this->autonomous_greenPhaseLength  = 5;
  this->autonomous_sensorAcknowledge = false;
  this->autonomous_greenPhase        = false;
  
  this->updateLastTransitionTimestamp();
  
  this->needsController         = true;
  this->hasController           = false;
  this->controllerRequestedMode = RQM_UNSPECIFIED;
  
  this->construct_uaserver();
  
  // Create Sensor and Output according to configuration *after* the ua server has been initialized (so the classes can map themselves)
  if (sc == nullptr)
    this->sensor = nullptr;
  else {
    this->sensor = new BinarySensor(*sc, this->mappedServer, this->instanceBaseId);
  }
  
  if (oc == nullptr)
    this->output = nullptr;
  else {
    this->output = new TrafficLightOutputFacility(*oc, this->mappedServer, this->instanceBaseId);
  }
}

void TrafficLight::construct_uaserver()
{
  this->server_config = UA_ServerConfig_standard;
  this->server_nl = UA_ServerNetworkLayerTCP(UA_ConnectionConfig_standard, 16664);
  this->server_config.logger = Logger_Stdout;
  this->server_config.networkLayers = &this->server_nl;
  this->server_config.networkLayersSize = 1;
  
  this->mappedServer = UA_Server_new(this->server_config);
  this->baseNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
  
  ua_light_namespaceinit_generated(this->mappedServer);
  this->ua_mapSelfToNamespace();
}


/*
 * State machine definition
 */
Automaton *TrafficLight::constructStateMachine() {
  /* State map:                             Id             enter             stay             exit             handle
   ********************************************************************************************************************/
  this->states["red"]          = new State("red",          bh_rd,             bh_sensorUpdate, bh_sensClrLatch, this);
  this->states["red_yellow"]   = new State("red_yellow",   bh_rd_yl,          defaultBehavior, defaultBehavior, this);
  this->states["green"]        = new State("green",        bh_gr,             defaultBehavior, defaultBehavior, this);
  this->states["green_yellow"] = new State("green_yellow", bh_gr_yl,          defaultBehavior, defaultBehavior, this); 
  this->states["yellow_warn"]  = new State("yellow_warn",  bh_problemDetect,  bh_warnProblem,  defaultBehavior, this);
  
  /* Transition List:                           Source                          Target                          Guard             Emit                           handle
   **********************************************************************************************************************************************************************/
  this->transitions.push_back( new Transition(*(this->states["red"]),          *(this->states["red_yellow"]),   gd_rdyl,          emt_updateTransitionTimestamp, this));
  this->transitions.push_back( new Transition(*(this->states["red_yellow"]),   *(this->states["green"]),        gd_yl,            emt_updateTransitionTimestamp, this));
  this->transitions.push_back( new Transition(*(this->states["green"]),        *(this->states["green_yellow"]), gd_gryl,          emt_updateTransitionTimestamp, this));
  this->transitions.push_back( new Transition(*(this->states["green_yellow"]), *(this->states["red"]),          gd_yl,            emt_updateTransitionTimestamp, this));
  this->transitions.push_back( new Transition(*(this->states["red"]),          *(this->states["yellow_warn"]),  gd_warn,          emt_updateTransitionTimestamp, this));
  this->transitions.push_back( new Transition(*(this->states["red_yellow"]),   *(this->states["yellow_warn"]),  gd_warn,          emt_updateTransitionTimestamp, this));
  this->transitions.push_back( new Transition(*(this->states["green"]),        *(this->states["yellow_warn"]),  gd_warn,          emt_updateTransitionTimestamp, this));
  this->transitions.push_back( new Transition(*(this->states["green_yellow"]), *(this->states["yellow_warn"]),  gd_warn,          emt_updateTransitionTimestamp, this));
  this->transitions.push_back( new Transition(*(this->states["yellow_warn"]),  *(this->states["red"]),          gd_standdownWarn, emt_updateTransitionTimestamp, this));
  
  return new Automaton(*(this->states["red"]), this->transitions);
}

/*
 * Thread execution and thread management
 */

bool TrafficLight::doRun() {
  if (this->thread_alive)
    return true;
  
  if (!thread_run) {
    thread_run = true;
    this->thr_automaton = new std::thread(&TrafficLight::workerThread, this);
    this->thr_uaserver  = new std::thread(UA_Server_run, this->mappedServer, &this->thread_run);
    while (!this->thread_alive) if (!this->thread_run) break;
  }
  
  return true;
}

bool TrafficLight::doStop() {
  this->thread_run = false;
  
  if (! this->thread_alive || this->thr_automaton == nullptr) {
    this->thread_alive = false;
    return true;
  }
  
  if (this->thr_uaserver->joinable())
    this->thr_uaserver->join();
  
  if (this->thr_automaton->joinable())
    this->thr_automaton->join();
  
  return true;
}

bool TrafficLight::isRunning() {
  if (this->thread_alive)
    return true;
  return false;
}

void TrafficLight::workerThread() {
  this->thread_alive = true;
  
  while(thread_run) {
    this->stateMachine->run();
    usleep(this->tick_interval);
  }
  
  this->thread_alive = false;
  this->thread_run = false;
  return;
}

/*
 * Class getter and setter functions
 */

UA_RDPROXY_BOOL(TrafficLight, getNeedsController);
bool TrafficLight::getNeedsController()             { return this->needsController; }
UA_WRPROXY_BOOL(TrafficLight, setNeedsController);
void TrafficLight::setNeedsController(bool b)       { this->needsController = b; }

UA_RDPROXY_BOOL(TrafficLight, getHasController);
bool TrafficLight::getHasController()               { return this->hasController;   }
UA_WRPROXY_BOOL(TrafficLight, setHasController);
void TrafficLight::setHasController(bool b)         { this->hasController   = b; }

UA_RDPROXY_BOOL(TrafficLight, getAutonomousGreenPhase);
bool TrafficLight::getAutonomousGreenPhase()              { return this->autonomous_greenPhase; }
UA_WRPROXY_BOOL(TrafficLight, setAutonomousGreenPhase);
void TrafficLight::setAutonomousGreenPhase(bool b)        { this->autonomous_greenPhase = b; }

UA_RDPROXY_BOOL(TrafficLight, getAutonomousSensorAcknowledge);
bool TrafficLight::getAutonomousSensorAcknowledge()       { return this->autonomous_sensorAcknowledge; }
UA_WRPROXY_BOOL(TrafficLight, setAutonomousSensorAcknowledge);
void TrafficLight::setAutonomousSensorAcknowledge(bool b) { this->autonomous_sensorAcknowledge = b;}

UA_RDPROXY_UINT32(TrafficLight, getYellowPhaseLength);
time_t TrafficLight::getYellowPhaseLength()         { return this->yellowPhaseLength; }
UA_WRPROXY_UINT32(TrafficLight, setYellowPhaseLength);
void   TrafficLight::setYellowPhaseLength(time_t t) { this->yellowPhaseLength = t; }

UA_RDPROXY_UINT32(TrafficLight, getAutonomousGreenPhaseLength);
time_t TrafficLight::getAutonomousGreenPhaseLength(){ return this->autonomous_greenPhaseLength; }
UA_WRPROXY_UINT32(TrafficLight, setAutonomousGreenPhaseLength);
void   TrafficLight::setAutonomousGreenPhaseLength(time_t  t){ this->autonomous_greenPhaseLength = t; }

UA_RDPROXY_UINT32(TrafficLight, getWarnBlinkInterval);
time_t TrafficLight::getWarnBlinkInterval()         { return this->warn_blinkInt; }
UA_WRPROXY_UINT32(TrafficLight, setWarnBlinkInterval);
void   TrafficLight::setWarnBlinkInterval(time_t t) {this->warn_blinkInt = t; }

void TrafficLight::updateLastTransitionTimestamp()  { this->last_transition_timestamp = time(nullptr); }
time_t TrafficLight::getLastTransitionTimestamp()   { return this->last_transition_timestamp; }

UA_RDPROXY_UINT32(TrafficLight, getControllerRequestedMode);
requestedMode_t TrafficLight::getControllerRequestedMode()                  {return this->controllerRequestedMode;}
UA_WRPROXY_UINT32(TrafficLight, setControllerRequestedMode);
void            TrafficLight::setControllerRequestedMode(requestedMode_t m) {this->controllerRequestedMode = m;}

bool TrafficLight::readSensor()
{ 
  if (this->sensor == nullptr)
    return false;
  return this->sensor->readValue();
}

/*
 * OPC UA Namespace construction
 */
UA_StatusCode TrafficLight::ua_mapSelfToNamespace() {
  UA_StatusCode retval = UA_STATUSCODE_GOOD;
  UA_NodeId createdNodeId = UA_NODEID_NULL;
  
  if (UA_NodeId_equal(&this->baseNodeId, &createdNodeId) == UA_TRUE) 
    return 0;
  
  // Create "our" base nodeId
  UA_ObjectAttributes oAttr;
  oAttr.displayName = UA_LOCALIZEDTEXT("en_US", "Traffic Light");
  oAttr.description = UA_LOCALIZEDTEXT("en_US", "An UA-interactive, configurable traffic light instance");
  
  UA_INSTATIATIONCALLBACK(icb);
  UA_Server_addObjectNode(this->mappedServer, UA_NODEID_NUMERIC(1,0),
                          UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                          UA_QUALIFIEDNAME(1, "Traffic Light"), UA_NODEID_NUMERIC(1, UA_NS1ID_TRAFFICLIGHTTYPE), oAttr, &icb, &createdNodeId);
  PUSH_OWNED_NODEID(createdNodeId);
  
  // The created node is the baseNodeId of any sensors or output facilities... so we need to remember it
  UA_NodeId_copy(&createdNodeId, &this->instanceBaseId);
  
  // Map getter and setter functions
  UA_DataSource_Map mapDs;
  mapDs.push_back((UA_DataSource_Map_Element) { .typeTemplateId = UA_NODEID_NUMERIC(1, 6006), .read=UA_RDPROXY_NAME(TrafficLight, getNeedsController),             .write=UA_WRPROXY_NAME(TrafficLight, setNeedsController) });
  mapDs.push_back((UA_DataSource_Map_Element) { .typeTemplateId = UA_NODEID_NUMERIC(1, 6007), .read=UA_RDPROXY_NAME(TrafficLight, getHasController),               .write=UA_WRPROXY_NAME(TrafficLight, setHasController) });
  mapDs.push_back((UA_DataSource_Map_Element) { .typeTemplateId = UA_NODEID_NUMERIC(1, 6004), .read=UA_RDPROXY_NAME(TrafficLight, getAutonomousGreenPhase),        .write=UA_WRPROXY_NAME(TrafficLight, setAutonomousGreenPhase) });
  mapDs.push_back((UA_DataSource_Map_Element) { .typeTemplateId = UA_NODEID_NUMERIC(1, 6005), .read=UA_RDPROXY_NAME(TrafficLight, getAutonomousSensorAcknowledge), .write=UA_WRPROXY_NAME(TrafficLight, setAutonomousSensorAcknowledge) });
  mapDs.push_back((UA_DataSource_Map_Element) { .typeTemplateId = UA_NODEID_NUMERIC(1, 6002), .read=UA_RDPROXY_NAME(TrafficLight, getYellowPhaseLength),           .write=UA_WRPROXY_NAME(TrafficLight, setYellowPhaseLength) });
  mapDs.push_back((UA_DataSource_Map_Element) { .typeTemplateId = UA_NODEID_NUMERIC(1, 6003), .read=UA_RDPROXY_NAME(TrafficLight, getAutonomousGreenPhaseLength),  .write=UA_WRPROXY_NAME(TrafficLight, setAutonomousGreenPhaseLength)});
  mapDs.push_back((UA_DataSource_Map_Element) { .typeTemplateId = UA_NODEID_NUMERIC(1, 6001), .read=UA_RDPROXY_NAME(TrafficLight, getWarnBlinkInterval),           .write=UA_WRPROXY_NAME(TrafficLight, setWarnBlinkInterval)});
  mapDs.push_back((UA_DataSource_Map_Element) { .typeTemplateId = UA_NODEID_NUMERIC(1, 6009), .read=UA_RDPROXY_NAME(TrafficLight, getControllerRequestedMode),     .write=UA_WRPROXY_NAME(TrafficLight, setControllerRequestedMode)});
  
  ua_callProxy_mapDataSources(this->mappedServer, this->ownedNodes, &mapDs, (void *) this);
  
  return UA_STATUSCODE_GOOD;
}