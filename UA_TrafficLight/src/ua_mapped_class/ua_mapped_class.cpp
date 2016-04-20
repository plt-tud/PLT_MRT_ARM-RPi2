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

#include "ua_mapped_class.h"
#include <iostream>

using namespace std;

ua_mapped_class::ua_mapped_class()
{
  this->baseNodeId = UA_NODEID_NUMERIC(0,0);
  this->mappedServer = nullptr;
}

ua_mapped_class::ua_mapped_class(UA_Server *server, UA_NodeId *baseNodeId)
{ 
  UA_NodeId_copy(baseNodeId, &this->baseNodeId);
  this->mappedServer = server;
}

UA_StatusCode ua_mapped_class::ua_setServer(UA_Server *server, UA_NodeId baseNodeId) 
{
  if (this->mappedServer != nullptr)
    return UA_STATUSCODE_BADSERVERNOTCONNECTED;
  UA_NodeId_copy(&baseNodeId, &this->baseNodeId);
  this->mappedServer = server;
  return UA_STATUSCODE_GOOD;
}

ua_mapped_class::ua_mapped_class(UA_Server *server, UA_NodeId baseNodeId)
{
  UA_NodeId_copy(&baseNodeId, &this->baseNodeId);
  this->mappedServer = server;
}

ua_mapped_class::~ua_mapped_class()
{
  cout << "ua mapped class being destroyed...";
  this->ua_unmapSelfFromNamespace();
  this->mappedServer = nullptr;
  this->mappedClient = nullptr;
  cout << "unmapped" << endl;
}

UA_StatusCode ua_mapped_class::ua_mapSelfToNamespace()
{
  UA_StatusCode retval = UA_STATUSCODE_GOOD;
  UA_NodeId nullId = UA_NODEID_NULL;
  if (UA_NodeId_equal(&this->baseNodeId, &UA_NODEID_NULL))
    return -1;
  if (this->mappedServer == nullptr)
    return -2;
  
  return retval;
}

UA_StatusCode ua_mapped_class::ua_unmapSelfFromNamespace()
{
  for (nodePairList::reverse_iterator i = this->ownedNodes.rbegin(); i != this->ownedNodes.rend(); ++i) {
    UA_NodeId_pair *p = *(i);
    UA_StatusCode retval = UA_Server_deleteNode(this->mappedServer, p->targetNodeId, UA_FALSE);
    this->ownedNodes.remove(*(i));
  }
  return UA_STATUSCODE_GOOD;
}

UA_StatusCode ua_mapped_class::ua_mapFunctions(void* srcClass, UA_FunctionCall_Map* map, UA_NodeId objectId)
{
  return ua_callProxy_mapFunctions(this->mappedServer, objectId, map, srcClass, false);
}

UA_StatusCode ua_mapped_class::ua_mapDataSources(void* srcClass, UA_DataSource_Map *map) 
{
  return ua_callProxy_mapDataSources(this->mappedServer, this->ownedNodes, map, srcClass);
}