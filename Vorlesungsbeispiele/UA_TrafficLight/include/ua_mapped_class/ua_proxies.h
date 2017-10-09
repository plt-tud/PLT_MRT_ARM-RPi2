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

#ifndef HAVE_UA_PROXIES_H
#define HAVE_UA_PROXIES_H

#include "ua_types.h"
#include "ua_server.h"
#include <list>

#include "ua_proxies_typeconversion.h"
#include "ua_proxies_callback.h"

typedef struct UA_NodeId_pair_t {
  UA_NodeId sourceNodeId;
  UA_NodeId targetNodeId;
} UA_NodeId_pair;
typedef std::list<UA_NodeId_pair*> nodePairList; 

typedef struct UA_FunctionCall_InstanceLookupTable_Element_t {
  void              *classInstance;
  UA_NodeId         classObjectId;
} UA_FunctionCall_InstanceLookupTable_Element;
typedef std::list<UA_FunctionCall_InstanceLookupTable_Element*> UA_FunctionCall_InstanceLookUpTable; 

typedef struct UA_FunctionCall_Map_Element_t {
  UA_NodeId                             typeTemplateId;
  UA_FunctionCall_InstanceLookUpTable  *lookupTable;
  UA_MethodCallback                     callback;
} UA_FunctionCall_Map_Element;
typedef std::list<UA_FunctionCall_Map_Element> UA_FunctionCall_Map;

typedef struct UA_DataSource_Map_Element_t {
  UA_NodeId     typeTemplateId;
  UA_StatusCode (*read)(void *handle, const UA_NodeId nodeid, UA_Boolean includeSourceTimeStamp,const UA_NumericRange *range, UA_DataValue *value);
  UA_StatusCode (*write)(void *handle, const UA_NodeId nodeid, const UA_Variant *data, const UA_NumericRange *range);
} UA_DataSource_Map_Element;
typedef std::list<UA_DataSource_Map_Element> UA_DataSource_Map;


#define NODE_PAIR_PUSH(_p_listname, _p_srcId, _p_targetId) do {\
UA_NodeId_pair *tmp = new UA_NodeId_pair;\
UA_NodeId_copy(&_p_srcId, &tmp->sourceNodeId);\
UA_NodeId_copy(&_p_targetId, &tmp->targetNodeId);\
_p_listname.push_back(tmp); } while (0);

#define PUSH_OWNED_NODEID(_p_nodeid) do {\
UA_NodeId_pair * _p_nodeid##_tmp = new UA_NodeId_pair;\
UA_NodeId_copy(&UA_NODEID_NULL, & _p_nodeid##_tmp->sourceNodeId);\
UA_NodeId_copy(&_p_nodeid, & _p_nodeid##_tmp->targetNodeId);\
this->ownedNodes.push_back(_p_nodeid##_tmp); } while(0);

UA_NodeId *nodePairList_getTargetIdBySourceId(nodePairList pairList, UA_NodeId remoteId);
UA_NodeId *nodePairList_getSourceIdByTargetId(nodePairList pairList, UA_NodeId TargetId);

// Node function and proxy mapping
UA_StatusCode ua_mapInstantiatedNodes(UA_NodeId objectId, UA_NodeId definitionId, void *handle);

UA_StatusCode ua_callProxy_mapFunctions(UA_Server* server, UA_NodeId objectId, UA_FunctionCall_Map *map, void* srcClass, int recursive);
UA_StatusCode ua_callProxy_mapDataSources(UA_Server* server, nodePairList instantiatedNodesList, UA_DataSource_Map *map, void *srcClass);

/* Instatiation NodeId gatherer Macro (because it's always the same...) */
#define UA_INSTATIATIONCALLBACK(_p_lstName) \
UA_InstantiationCallback _p_lstName; \
_p_lstName.handle = (void *) &this->ownedNodes; \
_p_lstName.method = ua_mapInstantiatedNodes;


#endif // Header include

