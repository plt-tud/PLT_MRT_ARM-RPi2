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

#ifndef UA_REMOTEOBJECT_H
#define UA_REMOTEOBJECT_H

extern "C" 
{
  #include "ua_server.h"
  #include "ua_client.h"
}
#include <string>
#include <thread>
#include <mutex>
#include <list>

typedef enum { 
  STATE_DISCONNECTED,
  STATE_CONNECTED,
  STATE_IDLE,
  STATE_FAULTED
} mappedClientState_t;

typedef struct remote_nodeNameMapEntry_t {
  UA_QualifiedName browseName;
  UA_NodeId        nodeId;
  UA_NodeClass     nodeClass;
} remote_nodeNameMapEntry;

typedef std::list<remote_nodeNameMapEntry *> remote_NodeMap_t;

class ua_remoteObject
{
private:
  UA_Client   *mappedClient;
  std::string  serverURI;
  UA_NodeId    baseNodeId;
  
  std::thread *thr_client;
  bool         thr_run;
  bool         thr_alive;
  std::mutex   mtx_clientAccess;
  
  mappedClientState_t mappedClientState;
  
  remote_NodeMap_t remoteNodes;
  void initClient();
  void lifeCycleThread();
protected:
  bool mapRemoteNodes(UA_NodeId objectBaseId);
  mappedClientState_t getClientState();
  
public:
  ua_remoteObject(std::string serverURI, UA_NodeId baseNodeId);
  ~ua_remoteObject();
  
  bool writeVar(std::string attributeName, void* value, const UA_DataType* dataType);
  
  void* readVar(std::string attributeName, const UA_DataType *expectType);
};

UA_NodeId ua_remoteObjectId_byPath(std::string serverURI, std::string objectBrowsePath);
#endif // UA_REMOTEOBJECT_H
