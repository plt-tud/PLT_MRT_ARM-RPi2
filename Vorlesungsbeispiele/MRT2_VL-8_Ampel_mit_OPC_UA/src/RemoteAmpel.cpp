/*
 * Copyright (c) 2018 Chris Iatrou <Chris_Paul.Iatrou@tu-dresden.de>
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

#include "RemoteAmpel.h"
#include "open62541.h"

void RemoteAmpel::init()
{
  client = UA_Client_new(UA_ClientConfig_default);
  UA_StatusCode retval = UA_Client_connect(client, serverURI.c_str() );
  if(retval != UA_STATUSCODE_GOOD) {
      UA_Client_delete(client);
      client = nullptr;
      return;
  }
}

void RemoteAmpel::run()
{
  // Always to nullptr-checks inside locked segments!
  
  // Auto-Reconnect if conncetion is down...
  clientMutex.lock();
  if (client != nullptr)
    if (UA_Client_getState(client) == UA_CLIENTSTATE_DISCONNECTED) {
      clientMutex.unlock();
      terminate();
      init();
      clientMutex.lock();
    };

  // Renew session once/second to keep our conncetion going
  if (client != nullptr)
    UA_Client_manuallyRenewSecureChannel(client);
  clientMutex.unlock();
}

void RemoteAmpel::terminate()
{
  clientMutex.lock();
  
  /* Clean up */
  if (client != nullptr) {
    UA_Client_delete(client); /* Disconnects the client internally */
    client = nullptr;
  }
  
  clientMutex.unlock();
}


/*
 * FIXME: Der Nachfolgende Abschnitt laesst sich extrem vereinfachen (ueber private setter/getter-Funktionen fuer UA oder
 *        durch Makros). Es veraendert sich nur die NodeId, bedingt der Typ. 
 *        
 *        Die Funktionen wurden zur Einfachheit bewusst "haesslich" implementiert, um einfacher nachvollziehbar zu sein.
 */

void RemoteAmpel::setRemoteBoolean(std::string StringNodeId, bool value)
{
  UA_Variant *val = UA_Variant_new();
  UA_Variant_setScalarCopy(val, &value, &UA_TYPES[UA_TYPES_BOOLEAN]);
  
  UA_NodeId n = UA_NODEID_STRING_ALLOC(1, StringNodeId.c_str());
  
  clientMutex.lock();
  if (client != nullptr && UA_Client_getState(client) != UA_CLIENTSTATE_DISCONNECTED) {
    UA_Client_writeValueAttribute(client, n, val);
  }
  clientMutex.unlock();
  
  UA_NodeId_deleteMembers(&n);
  UA_Variant_delete(val);
  return ;
}

bool RemoteAmpel::getRemoteBoolean(std::string StringNodeId)
{
  bool cval = false;
  UA_Variant *val = UA_Variant_new();
  UA_NodeId n = UA_NODEID_STRING_ALLOC(1, StringNodeId.c_str());
  
  clientMutex.lock();
  if (client != nullptr && UA_Client_getState(client) != UA_CLIENTSTATE_DISCONNECTED) {
    UA_StatusCode retval = UA_Client_readValueAttribute(client, n, val);
    if(retval == UA_STATUSCODE_GOOD && UA_Variant_isScalar(val) && val->type == &UA_TYPES[UA_TYPES_BOOLEAN]) {
      if(*(UA_Int32*)val->data == UA_TRUE) cval = true;
    }
  }
  clientMutex.unlock();
  
  UA_NodeId_deleteMembers(&n);
  UA_Variant_delete(val);
  return cval;
}

  
bool RemoteAmpel::getRedLight() 
{
  return getRemoteBoolean("redLight");
}

void RemoteAmpel::setRedLight(bool setLightOn)
{
   setRemoteBoolean("redLight", setLightOn);
}

bool RemoteAmpel::getYellowLight() 
{
  return getRemoteBoolean("yellowLight");
}

void RemoteAmpel::setYellowLight(bool setLightOn)
{
   setRemoteBoolean("yellowLight", setLightOn);
}

bool RemoteAmpel::getGreenLight() 
{
  return getRemoteBoolean("greenLight");
}

void RemoteAmpel::setGreenLight(bool setLightOn)
{
   setRemoteBoolean("greenLight", setLightOn);
}

bool RemoteAmpel::getSensor() 
{
  return getRemoteBoolean("sensor");
}

void RemoteAmpel::setSensor(bool setSensorTriggered)
{
   setRemoteBoolean("sensor", setSensorTriggered);
}

bool RemoteAmpel::hasController() 
{
  return getRemoteBoolean("sensor");
}

void RemoteAmpel::setController(bool present)
{
   setRemoteBoolean("hasController", present);
}


void RemoteAmpel::setPhaseCommand(ampel_phaseId value)
{
  UA_Variant *val = UA_Variant_new();
  UA_Variant_setScalarCopy(val, &value, &UA_TYPES[UA_TYPES_INT32]);
  
  clientMutex.lock();
  if (client != nullptr && UA_Client_getState(client) != UA_CLIENTSTATE_DISCONNECTED) {
    UA_Client_writeValueAttribute(client, UA_NODEID_STRING(1, "phaseCommand") , val);
  }
  clientMutex.unlock();
  
  UA_Variant_delete(val);
  return ;
}

ampel_phaseId RemoteAmpel::getPhaseCommand()
{
  ampel_phaseId cval = PHASE_RED;
  UA_Variant *val = UA_Variant_new();
  
  clientMutex.lock();
  if (client != nullptr && UA_Client_getState(client) != UA_CLIENTSTATE_DISCONNECTED) {
    UA_StatusCode retval = UA_Client_readValueAttribute(client, UA_NODEID_STRING(1, "phaseCommand"), val);
    if(retval == UA_STATUSCODE_GOOD && UA_Variant_isScalar(val) && val->type == &UA_TYPES[UA_TYPES_INT32]) {
      if(*(UA_Int32*)val->data != PHASE_RED) cval = PHASE_GREEN;
    }
  }
  clientMutex.unlock();
  
  UA_Variant_delete(val);
  return cval;
}
