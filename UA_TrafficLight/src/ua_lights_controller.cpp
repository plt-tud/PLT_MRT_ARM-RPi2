#include <iostream>
#include <unistd.h>

#include <ua_remoteobject.h>
#include <server/ua_nodes.h>
using namespace std;

int main(int argc, char *argv[]){
  UA_NodeId myLight = ua_remoteObjectId_byPath("opc.tcp://10.0.53.112:16664", "/Objects/Traffic Light");
  ua_remoteObject remoteLight("opc.tcp://10.0.53.112:16664", myLight);
  sleep(2); // Wait for Trafficlight to connect and map...
  
  UA_Boolean *Sensor = UA_Boolean_new();
  *Sensor = UA_TRUE; // Misuse for setting the autonomous_sensorAck
  remoteLight.writeVar("autonomous_sensorAck", (void *) Sensor, &UA_TYPES[UA_TYPES_BOOLEAN]);
  
  *Sensor = UA_FALSE;
  while(Sensor != nullptr && *Sensor == UA_FALSE) {
    cout << "Waiting for sensor" << endl;
    Sensor = (UA_Boolean *) remoteLight.readVar("sensorAck", &UA_TYPES[UA_TYPES_BOOLEAN]);
    sleep(1);
  } 
  if (Sensor == nullptr)
    return -1; 
  
  UA_UInt32 rq = 2; // RQM_GREEN
  remoteLight.writeVar("requestState", (void *) &rq, &UA_TYPES[UA_TYPES_UINT32]);
  
  sleep(5); // Must wait until we are in green (green will reset the RQM to unspecified)
  rq=1; // RQM_RED
  remoteLight.writeVar("requestState", (void *) &rq, &UA_TYPES[UA_TYPES_UINT32]);
  
  return 0;
}