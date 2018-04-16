/*
 * Copyright (c) 2016 Chris Iatrou <Chris_Paul.Iatrou@tu-dresden.de>
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

#include "TrafficLightOutputFacility.h"
#include <iostream>
extern "C" 
{
  // open62541
  #include "ua_server.h"
  
  // Generated namespace init
  #include "ua_light_namespaceinit_generated.h"
}

using namespace std;

TrafficLightOutputFacility::TrafficLightOutputFacility(TrafficLightOutputFacility_config config)
: ua_mapped_class(nullptr, UA_NODEID_NULL), hasYellow(config.hasYellow), hasSignal(config.hasSignal), signal(false), red(false), green(false), yellow(false) 
{
  this->extended_setOutput = config.extended_setOutput;
  this->extended_setSignal = config.extended_setSignal;
}

TrafficLightOutputFacility::TrafficLightOutputFacility(TrafficLightOutputFacility_config config, UA_Server *server, UA_NodeId baseNodeId)
: ua_mapped_class(server, baseNodeId), hasYellow(config.hasYellow), hasSignal(config.hasSignal), signal(false), red(false), green(false), yellow(false) 
{
  this->extended_setOutput = config.extended_setOutput;
  this->extended_setSignal = config.extended_setSignal;
  
  this->ua_mapSelfToNamespace();
}

void TrafficLightOutputFacility::setSignal(bool signal) 
{
  this->signal = signal;
  if(this->extended_setSignal != nullptr)
    this->extended_setSignal(signal);
}

UA_RDPROXY_BOOL(TrafficLightOutputFacility, getSignal)
bool TrafficLightOutputFacility::getSignal() { return this->signal; }

void TrafficLightOutputFacility::setOutput(bool red, bool yellow, bool green) 
{
  this->red    = red;
  this->yellow = yellow;
  this->green  = green;
  if (this->extended_setOutput != nullptr)
    this->extended_setOutput(red, yellow, green);
}

void TrafficLightOutputFacility::toggleWarnIndicator() 
{
  if(this->hasYellow) {
    this->yellow = !this->yellow ;
    if (this->extended_setOutput != nullptr)
      this->extended_setOutput(false, this->yellow, false);
  }
  else {
    this->red = this->green;
    this->red   = !this->red;
    this->green = !this->green ;
    if (this->extended_setOutput != nullptr)
      this->extended_setOutput(this->red, false, this->green);
  }
}

UA_RDPROXY_BOOL(TrafficLightOutputFacility, getRedStatus)
bool TrafficLightOutputFacility::getRedStatus() {return this->red;}
UA_RDPROXY_BOOL(TrafficLightOutputFacility, getYellowStatus)
bool TrafficLightOutputFacility::getYellowStatus() {return this->yellow;}
UA_RDPROXY_BOOL(TrafficLightOutputFacility, getGreenStatus)
bool TrafficLightOutputFacility::getGreenStatus() {return this->green;}
UA_RDPROXY_BOOL(TrafficLightOutputFacility, getHasSignal)
bool TrafficLightOutputFacility::getHasSignal() {return this->hasSignal;}
UA_RDPROXY_BOOL(TrafficLightOutputFacility, getHasYellow)
bool TrafficLightOutputFacility::getHasYellow() {return this->hasYellow;}

UA_StatusCode TrafficLightOutputFacility::ua_mapSelfToNamespace() {
  UA_StatusCode retval = UA_STATUSCODE_GOOD;
  UA_NodeId createdNodeId = UA_NODEID_NULL;
  
  if (UA_NodeId_equal(&this->baseNodeId, &createdNodeId) == UA_TRUE) 
    return 0;
  
  // Create "our" base nodeId
  UA_ObjectAttributes oAttr;
  oAttr.displayName = UA_LOCALIZEDTEXT("en_US", "TrafficLightOutput ");
  oAttr.description = UA_LOCALIZEDTEXT("en_US", "Representation of the traffic lights lights");
  
  UA_INSTATIATIONCALLBACK(icb);
  UA_Server_addObjectNode(this->mappedServer, UA_NODEID_NUMERIC(1,0),
                          this->baseNodeId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                          UA_QUALIFIEDNAME(1, "TrafficLightOutputFacility"), UA_NODEID_NUMERIC(1, UA_NS1ID_TRAFFICLIGHTOUTPUTFACILITY), oAttr, &icb, &createdNodeId);
  PUSH_OWNED_NODEID(createdNodeId);
  
  UA_DataSource_Map mapDs;
  mapDs.push_back((UA_DataSource_Map_Element) { .typeTemplateId = UA_NODEID_NUMERIC(1, 6013), .read=UA_RDPROXY_NAME(TrafficLightOutputFacility, getRedStatus),    .write=nullptr });
  mapDs.push_back((UA_DataSource_Map_Element) { .typeTemplateId = UA_NODEID_NUMERIC(1, 6014), .read=UA_RDPROXY_NAME(TrafficLightOutputFacility, getYellowStatus), .write=nullptr });
  mapDs.push_back((UA_DataSource_Map_Element) { .typeTemplateId = UA_NODEID_NUMERIC(1, 6015), .read=UA_RDPROXY_NAME(TrafficLightOutputFacility, getGreenStatus),  .write=nullptr });
  mapDs.push_back((UA_DataSource_Map_Element) { .typeTemplateId = UA_NODEID_NUMERIC(1, 6016), .read=UA_RDPROXY_NAME(TrafficLightOutputFacility, getSignal),       .write=nullptr });
  mapDs.push_back((UA_DataSource_Map_Element) { .typeTemplateId = UA_NODEID_NUMERIC(1, 6018), .read=UA_RDPROXY_NAME(TrafficLightOutputFacility, getHasSignal),    .write=nullptr });
  mapDs.push_back((UA_DataSource_Map_Element) { .typeTemplateId = UA_NODEID_NUMERIC(1, 6017), .read=UA_RDPROXY_NAME(TrafficLightOutputFacility, getHasYellow),    .write=nullptr });
  ua_callProxy_mapDataSources(this->mappedServer, this->ownedNodes, &mapDs, (void *) this);
  
  return retval;
}

void TrafficLightOutputFacility::printState() 
{
  cout << "\x1B[2J\x1B[H"; // ANSI Console only... clear screen, move cursor to first position
  if(this->hasSignal) {
    cout << "+-+" << endl;
    cout << "|"; 
    if (this->signal) cout << "X"; else cout << " ";
    cout << "|" << endl;
    cout << "+-+" << endl;
  }
  cout << "+-+" << endl;
  cout << "|"; 
  if (this->red) cout << "O"; else cout << " ";
  cout << "|" << endl;
  cout << "+-+" << endl;
  
  if(this->hasYellow) {
    cout << "|"; 
    if (this->yellow) cout << "O"; else cout << " ";
    cout << "|" << endl;
    cout << "+-+" << endl;
  }
  cout << "|"; 
  if (this->green) cout << "O"; else cout << " ";
  cout << "|" << endl;
  cout << "+-+" << endl << endl;

}