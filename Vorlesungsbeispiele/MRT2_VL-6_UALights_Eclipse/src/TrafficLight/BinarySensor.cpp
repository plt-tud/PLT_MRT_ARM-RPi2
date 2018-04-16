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

#include "BinarySensor.h"

extern "C" 
{
  // open62541
  #include "ua_server.h"
  
  // Generated namespace init
  #include "ua_light_namespaceinit_generated.h"
}

BinarySensor::BinarySensor(BinarySensor_config sc) : value_latch(false), read(sc.readSensorFunction), ua_mapped_class()
{}

BinarySensor::BinarySensor(BinarySensor_config sc, UA_Server *server, UA_NodeId baseNodeId) : value_latch(false), read(sc.readSensorFunction), ua_mapped_class(server, baseNodeId)
{
  this->ua_mapSelfToNamespace();
}

bool BinarySensor::readValue() 
{
  if (read != nullptr)
    this->value_latch |= read();
  return value_latch;
}

void BinarySensor::clearLatch() 
{
  value_latch = false;
  return;
}

UA_RDPROXY_BOOL(BinarySensor, getValue)
bool BinarySensor::getValue() {return this->read();}

UA_RDPROXY_BOOL(BinarySensor, getLatch)
bool BinarySensor::getLatch() {return this->value_latch;}
UA_WRPROXY_BOOL(BinarySensor, setLatch)
void BinarySensor::setLatch(bool b) {this->value_latch = b;}

UA_StatusCode BinarySensor::ua_mapSelfToNamespace() {
  UA_StatusCode retval = UA_STATUSCODE_GOOD;
  UA_NodeId createdNodeId = UA_NODEID_NULL;
  
  if (UA_NodeId_equal(&this->baseNodeId, &createdNodeId) == UA_TRUE) 
    return 0;
  
  // Create "our" base nodeId
  UA_ObjectAttributes oAttr;
  oAttr.displayName = UA_LOCALIZEDTEXT("en_US", "BinarySensor");
  oAttr.description = UA_LOCALIZEDTEXT("en_US", "Representation of the traffic lights sensor (induction coil or push button)");
  
  UA_INSTATIATIONCALLBACK(icb);
  UA_Server_addObjectNode(this->mappedServer, UA_NODEID_NUMERIC(1,0),
                          this->baseNodeId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                          UA_QUALIFIEDNAME(1, "BinarySensor"), UA_NODEID_NUMERIC(1, UA_NS1ID_BINARYSENSORTYPE), oAttr, &icb, &createdNodeId);
  PUSH_OWNED_NODEID(createdNodeId);
  
  UA_DataSource_Map mapDs;
  mapDs.push_back((UA_DataSource_Map_Element) { .typeTemplateId = UA_NODEID_NUMERIC(1, 6012), .read=UA_RDPROXY_NAME(BinarySensor, getLatch), .write=UA_WRPROXY_NAME(BinarySensor, setLatch) });
  mapDs.push_back((UA_DataSource_Map_Element) { .typeTemplateId = UA_NODEID_NUMERIC(1, 6011), .read=UA_RDPROXY_NAME(BinarySensor, getValue), .write=nullptr });
  ua_callProxy_mapDataSources(this->mappedServer, this->ownedNodes, &mapDs, (void *) this);
  
  return retval;
}