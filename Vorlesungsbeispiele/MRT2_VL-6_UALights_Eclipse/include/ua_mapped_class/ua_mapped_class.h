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

#ifndef UA_MAPPED_CLASS_H
#define UA_MAPPED_CLASS_H

extern "C" 
{
  #include "ua_server.h"
  #include "ua_client.h"
}

#include "ua_proxies.h"

class ua_mapped_class
{
protected:
  UA_Server *mappedServer;
  UA_Client *mappedClient;
  nodePairList ownedNodes;
  UA_NodeId baseNodeId;
  
public:
    ua_mapped_class(UA_Server *server, UA_NodeId *baseNodeId);
    ua_mapped_class(UA_Server *server, UA_NodeId baseNodeId);
    ua_mapped_class();
    ~ua_mapped_class();
    
    UA_StatusCode ua_setServer(UA_Server *server, UA_NodeId baseNodeId);
    UA_StatusCode ua_mapSelfToNamespace();
    UA_StatusCode ua_unmapSelfFromNamespace();
    UA_StatusCode ua_mapFunctions(void* srcClass, UA_FunctionCall_Map *map, UA_NodeId objectId);
    UA_StatusCode ua_mapDataSources(void* srcClass, UA_DataSource_Map* map);
};

#endif // UA_MAPPED_CLASS_H
