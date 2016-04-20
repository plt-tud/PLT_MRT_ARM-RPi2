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

#include "ua_remoteobject.h"
#include "unistd.h"

#include "ua_proxies_typeconversion.h"

#include <iostream>
using namespace std;

extern "C" {
  #include "ua_client_highlevel.h"
  #include "networklayer_tcp.h"
  #include "logger_stdout.h"
}

// Recursive browse function that also tracks the list iterator for the /Brwose/Path/Parts/seperated/by/slashes 
// (each listentry is one path element)
static UA_StatusCode
ua_iterator_followPath(UA_NodeId childId, UA_Boolean isInverse, UA_NodeId referenceTypeId, void *handle) 
{  
  typedef struct {
    std::list<string>::iterator i;
    std::list<string> hops;
    UA_Client *client;
    UA_NodeId nodeId;
  } hopInfo_t;
  hopInfo_t *hopInfo = (hopInfo_t *) handle;
  
  UA_NodeId hasComponent = UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT);
  UA_NodeId hasProperty  = UA_NODEID_NUMERIC(0, UA_NS0ID_HASPROPERTY);
  UA_NodeId organizes    = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
  if (UA_NodeId_equal(&referenceTypeId, &hasComponent) == UA_FALSE &&
      UA_NodeId_equal(&referenceTypeId, &hasProperty) == UA_FALSE  &&
      UA_NodeId_equal(&referenceTypeId, &organizes) == UA_FALSE ) 
    return UA_STATUSCODE_GOOD; // Only these refTypes are allowed
  
  if(isInverse == UA_TRUE)
    return UA_STATUSCODE_GOOD; // Don't go invers
  
  if (UA_NodeId_equal(&UA_NODEID_NULL, &hopInfo->nodeId) == UA_FALSE)
    return UA_STATUSCODE_GOOD; // Someone found the last node
  
  // Get Node's browseName
  UA_QualifiedName name;
  if(UA_Client_readBrowseNameAttribute(hopInfo->client, childId, &name) != UA_STATUSCODE_GOOD) 
    return UA_STATUSCODE_GOOD;
  
  std::string cppname;
  UA_STRING_TO_CPPSTRING_COPY(&name.name, &cppname);
  
  if (cppname == *(hopInfo->i)) {
    hopInfo->i++;
    if (hopInfo->i == hopInfo->hops.end()) {
      UA_NodeId_copy(&childId, &hopInfo->nodeId);
    }
    else {
      UA_Client *client = hopInfo->client;
      UA_Client_forEachChildNodeCall(client, childId, ua_iterator_followPath, handle);
    }
  }
  return UA_STATUSCODE_GOOD;
}

UA_NodeId ua_remoteObjectId_byPath(std::string serverURI, std::string objectBrowsePath)
{
  UA_Client *client = UA_Client_new(UA_ClientConfig_standard, Logger_Stdout);
  if(UA_Client_connect(client, UA_ClientConnectionTCP, (const char*) serverURI.c_str()) != UA_STATUSCODE_GOOD) {
    UA_Client_delete(client);
    return UA_NODEID_NULL;
  }
  
  int p;
  while((p=objectBrowsePath.find("//")) != string::npos)
    objectBrowsePath.replace(p,2,"/");
  while((p=objectBrowsePath.find("\\\\")) != string::npos)
    objectBrowsePath.replace(p,2,"\\");
  
  if (objectBrowsePath[0] == '\\' || objectBrowsePath[0]=='/')
    objectBrowsePath.replace(0,1,"");
  if (objectBrowsePath[objectBrowsePath.length()-1] != '\\' || objectBrowsePath[objectBrowsePath.length()-1]!='/')
    objectBrowsePath.append("/");
  
  int pp = 0;
  p = 0;
  struct {
    std::list<string>::iterator i;
    std::list<string> hops;
    UA_Client *client;
    UA_NodeId nodeId;
  } hopInfo;
  hopInfo.client = client;
  hopInfo.nodeId = UA_NODEID_NULL;
  for(char& c : objectBrowsePath) {
    p++;
    if(c == '/' || c == '\\') {
      hopInfo.hops.push_back(objectBrowsePath.substr(pp, p-pp-1));
      pp=p;
    }
  }
  hopInfo.i = hopInfo.hops.begin();
  UA_Client_forEachChildNodeCall(client, UA_NODEID_NUMERIC(0, 84), ua_iterator_followPath, (void *) &hopInfo);
  // UA_TranslateBrowsePathsToNodeIdsRequest_deleteMembers(&tReq);
  
  UA_Client_disconnect(client);
  UA_Client_delete(client);
  
  return hopInfo.nodeId;
}

ua_remoteObject::ua_remoteObject(std::string serverURI, UA_NodeId baseNodeId) : serverURI(serverURI), mappedClient(nullptr)
{
  UA_NodeId_copy(&baseNodeId, &this->baseNodeId);
  
  this->initClient();
}

void ua_remoteObject::initClient() 
{
  this->thr_run = true;
  this->thr_alive = false;
  this->thr_client = new std::thread(&ua_remoteObject::lifeCycleThread, this);
}

bool ua_remoteObject::mapRemoteNodes(UA_NodeId objectBaseId) {
  //WARNING: Only call when locked by lifeCycleThread; does not lock mutex by itself
  
  UA_NodeId hasComponent = UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT);
  UA_NodeId hasProperty  = UA_NODEID_NUMERIC(0, UA_NS0ID_HASPROPERTY);
  UA_NodeId organizes    = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
  
  UA_BrowseRequest bReq;
  UA_BrowseRequest_init(&bReq);
  bReq.requestedMaxReferencesPerNode = 0;
  bReq.nodesToBrowse = UA_BrowseDescription_new();
  bReq.nodesToBrowseSize = 1;
  UA_NodeId_copy(&objectBaseId, &bReq.nodesToBrowse[0].nodeId); //browse objects folder
  bReq.nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_BROWSENAME | UA_BROWSERESULTMASK_ISFORWARD | UA_BROWSERESULTMASK_REFERENCETYPEID;
  
  UA_BrowseResponse bResp = UA_Client_Service_browse(this->mappedClient, bReq);
  if (bResp.responseHeader.serviceResult == UA_STATUSCODE_GOOD &&
      bResp.resultsSize > 0 && bResp.results[0].statusCode == UA_STATUSCODE_GOOD) 
  {
    UA_BrowseResult br = bResp.results[0];
    for (int i = 0; i < br.referencesSize; i++) {
      UA_ReferenceDescription rd = br.references[i];
      if (!UA_NodeId_equal(&rd.referenceTypeId, &hasComponent) &&
          !UA_NodeId_equal(&rd.referenceTypeId, &hasProperty) &&
          !UA_NodeId_equal(&rd.referenceTypeId, &organizes))
        continue;
      
      std::string name;
      UA_STRING_TO_CPPSTRING_COPY(&br.references[i].browseName.name, &name);
      remote_nodeNameMapEntry *n = new remote_nodeNameMapEntry;
      UA_NodeId_copy(&br.references[i].nodeId.nodeId, &n->nodeId);
      UA_QualifiedName_copy(&br.references[i].browseName, &n->browseName);
      n->nodeClass = br.references[i].nodeClass; // This fails on occasion and return UNSPECIFIED...
      this->remoteNodes.push_back(n); 
    }
    UA_BrowseResponse_deleteMembers(&bResp);
  }
  else {
    UA_BrowseRequest_deleteMembers(&bReq);  
    return false;
  }
  UA_BrowseRequest_deleteMembers(&bReq);
  return true;
}

bool ua_remoteObject::writeVar(std::string attributeName, void* value, const UA_DataType *dataType) {
  if(value == nullptr)
    return false;
  
  if(this->getClientState() != STATE_IDLE)
    return false;
  
  remote_nodeNameMapEntry *e  = nullptr;
  for(remote_NodeMap_t::iterator j = this->remoteNodes.begin(); j != this->remoteNodes.end(); j++) {
    std::string cname;
    UA_STRING_TO_CPPSTRING_COPY(&((*(j))->browseName.name), &cname);
    if (cname == attributeName) {
      e = *(j);
      break;
    }
  }
  if (e == nullptr)
    return false;
  
  UA_Variant *v = UA_Variant_new();
  UA_Variant_setScalarCopy(v, value, dataType);
  this->mtx_clientAccess.lock();
  UA_Client_writeValueAttribute(this->mappedClient, e->nodeId, v);
  this->mtx_clientAccess.unlock();
  return true;
}

void *ua_remoteObject::readVar(string attributeName, const UA_DataType* expectType) {
  if(this->getClientState() != STATE_IDLE)
    return nullptr;
  
  remote_nodeNameMapEntry *e = nullptr;
  for(remote_NodeMap_t::iterator j = this->remoteNodes.begin(); j != this->remoteNodes.end(); j++) {
    std::string cname;
    UA_STRING_TO_CPPSTRING_COPY(&((*(j))->browseName.name), &cname);
    if (cname == attributeName) {
      e = *(j);
      break;
    }
  }
  if (e == nullptr)
    return nullptr;
  
  UA_Variant *v = UA_Variant_new();
  this->mtx_clientAccess.lock();
  void *val = nullptr;
  if (UA_Client_readValueAttribute(this->mappedClient, e->nodeId, v) == UA_STATUSCODE_GOOD) {
    this->mtx_clientAccess.unlock();
    if ( v->type == expectType) {
      val = UA_new(expectType);
      UA_copy(v->data, val, expectType);
    }
    UA_Variant_delete(v);
  }
  else
    this->mtx_clientAccess.unlock();
  return val;
}

void ua_remoteObject::lifeCycleThread() 
{
  UA_StatusCode retval;
  
  this->mappedClient = UA_Client_new(UA_ClientConfig_standard, Logger_Stdout);
  this->thr_alive = true;
  while(this->thr_run) {
    this->mtx_clientAccess.lock();
    switch(this->mappedClientState) {
      case STATE_DISCONNECTED:
        if((retval = UA_Client_connect(this->mappedClient, UA_ClientConnectionTCP, (const char*) this->serverURI.c_str())) == UA_STATUSCODE_GOOD) {
          this->mappedClientState = STATE_CONNECTED;
          cout << "connected to client" << endl;
        }
        break;;
      case STATE_CONNECTED:
        this->mapRemoteNodes(this->baseNodeId);
        this->mappedClientState = STATE_IDLE;
        break;;
      case STATE_IDLE:
        if(UA_Client_manuallyRenewSecureChannel(this->mappedClient) != UA_STATUSCODE_GOOD) 
          this->mappedClientState = STATE_FAULTED;
        break;;
      case STATE_FAULTED:
        cout << "reinitializing client" << endl;
        UA_Client_disconnect(this->mappedClient);
        UA_Client_delete(this->mappedClient);
        // Destroy our nodemap... may be invalid if the server crashed/restarted for some reason
        this->remoteNodes.clear();
        // Create new client
        this->mappedClient = UA_Client_new(UA_ClientConfig_standard, Logger_Stdout);
        this->mappedClientState = STATE_DISCONNECTED;
        break;;
      default:
        this->mappedClientState = STATE_DISCONNECTED;
    }
    this->mtx_clientAccess.unlock();
    usleep(100000); // FIXME: This should be configurable...
  }
  this->thr_alive = false;
  if (this->mappedClientState == STATE_CONNECTED)
    UA_Client_disconnect(this->mappedClient);
  UA_Client_delete(this->mappedClient);
  this->mappedClient = nullptr;
  cout << "Client terminated" << endl;
  return;
}

ua_remoteObject::~ua_remoteObject()
{
  this->thr_run = false;
  
  if (this->thr_client->joinable())
    this->thr_client->join();
}

mappedClientState_t ua_remoteObject::getClientState() {
  this->mtx_clientAccess.lock();
  mappedClientState_t s = this->mappedClientState;
  this->mtx_clientAccess.unlock();
  return s;
}
