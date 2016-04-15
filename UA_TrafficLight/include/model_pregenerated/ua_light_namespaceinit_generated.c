/* WARNING: This is a generated file.
 * Any manual changes will be overwritten.

 */
#include "ua_light_namespaceinit_generated.h"
UA_INLINE void ua_light_namespaceinit_generated(UA_Server *server) {

do {
// Referencing node found and declared as parent: i=29/Enumeration using i=45/HasSubtype
// Node: opcua_node_dataType_t(ns=1;i=3001), 1:TrafficLightRequestMode
UA_DataTypeAttributes attr;
UA_DataTypeAttributes_init(&attr);
attr.displayName = UA_LOCALIZEDTEXT("", "TrafficLightRequestMode");
attr.description = UA_LOCALIZEDTEXT("", "Request Mode for Traffic lights");
UA_NodeId nodeId = UA_NODEID_NUMERIC(1, 3001);
UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, 29);
UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, 45);
UA_QualifiedName nodeName = UA_QUALIFIEDNAME(1, "TrafficLightRequestMode");
UA_Server_addDataTypeNode(server, nodeId, parentNodeId, parentReferenceNodeId, nodeName
       , attr, NULL, NULL);
} while(0);

do {
// Referencing node found and declared as parent: ns=1;i=3001/1:TrafficLightRequestMode using i=46/HasProperty
// Node: opcua_node_variable_t(ns=1;i=6010), EnumStrings
UA_VariableAttributes attr;
UA_VariableAttributes_init(&attr);
attr.displayName = UA_LOCALIZEDTEXT("", "EnumStrings");
attr.description = UA_LOCALIZEDTEXT("", "");
UA_NodeId nodeId = UA_NODEID_NUMERIC(1, 6010);
UA_NodeId typeDefinition = UA_NODEID_NULL;
UA_NodeId parentNodeId = UA_NODEID_NUMERIC(1, 3001);
UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, 46);
UA_QualifiedName nodeName = UA_QUALIFIEDNAME(0, "EnumStrings");
UA_Server_addVariableNode(server, nodeId, parentNodeId, parentReferenceNodeId, nodeName
       , typeDefinition
       , attr, NULL, NULL);
// This node has the following references that can be created:
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6010), UA_NODEID_NUMERIC(0, 37), UA_EXPANDEDNODEID_NUMERIC(0, 78), true);
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6010), UA_NODEID_NUMERIC(0, 40), UA_EXPANDEDNODEID_NUMERIC(0, 68), true);
} while(0);

do {
// Referencing node found and declared as parent: i=58/BaseObjectType using i=45/HasSubtype
// Node: opcua_node_objectType_t(ns=1;i=1002), 1:BinarySensorType
UA_ObjectTypeAttributes attr;
UA_ObjectTypeAttributes_init(&attr);
attr.displayName = UA_LOCALIZEDTEXT("", "BinarySensorType");
attr.description = UA_LOCALIZEDTEXT("", "A Sensor returning 0 or one");
UA_NodeId nodeId = UA_NODEID_NUMERIC(1, 1002);
UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, 58);
UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, 45);
UA_QualifiedName nodeName = UA_QUALIFIEDNAME(1, "BinarySensorType");
UA_Server_addObjectTypeNode(server, nodeId, parentNodeId, parentReferenceNodeId, nodeName
       , attr, NULL, NULL);
} while(0);

do {
// Referencing node found and declared as parent: ns=1;i=1002/1:BinarySensorType using i=47/HasComponent
// Node: opcua_node_variable_t(ns=1;i=6012), 1:latchValue
UA_VariableAttributes attr;
UA_VariableAttributes_init(&attr);
attr.displayName = UA_LOCALIZEDTEXT("", "latchValue");
attr.description = UA_LOCALIZEDTEXT("", "");
UA_NodeId nodeId = UA_NODEID_NUMERIC(1, 6012);
UA_NodeId typeDefinition = UA_NODEID_NULL;
UA_NodeId parentNodeId = UA_NODEID_NUMERIC(1, 1002);
UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, 47);
UA_QualifiedName nodeName = UA_QUALIFIEDNAME(1, "latchValue");
UA_Server_addVariableNode(server, nodeId, parentNodeId, parentReferenceNodeId, nodeName
       , typeDefinition
       , attr, NULL, NULL);
// This node has the following references that can be created:
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6012), UA_NODEID_NUMERIC(0, 40), UA_EXPANDEDNODEID_NUMERIC(0, 63), true);
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6012), UA_NODEID_NUMERIC(0, 37), UA_EXPANDEDNODEID_NUMERIC(0, 78), true);
} while(0);

do {
// Referencing node found and declared as parent: ns=1;i=1002/1:BinarySensorType using i=47/HasComponent
// Node: opcua_node_variable_t(ns=1;i=6011), 1:senseValue
UA_VariableAttributes attr;
UA_VariableAttributes_init(&attr);
attr.displayName = UA_LOCALIZEDTEXT("", "senseValue");
attr.description = UA_LOCALIZEDTEXT("", "");
UA_NodeId nodeId = UA_NODEID_NUMERIC(1, 6011);
UA_NodeId typeDefinition = UA_NODEID_NULL;
UA_NodeId parentNodeId = UA_NODEID_NUMERIC(1, 1002);
UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, 47);
UA_QualifiedName nodeName = UA_QUALIFIEDNAME(1, "senseValue");
UA_Server_addVariableNode(server, nodeId, parentNodeId, parentReferenceNodeId, nodeName
       , typeDefinition
       , attr, NULL, NULL);
// This node has the following references that can be created:
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6011), UA_NODEID_NUMERIC(0, 40), UA_EXPANDEDNODEID_NUMERIC(0, 63), true);
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6011), UA_NODEID_NUMERIC(0, 37), UA_EXPANDEDNODEID_NUMERIC(0, 78), true);
} while(0);

do {
// Referencing node found and declared as parent: i=58/BaseObjectType using i=45/HasSubtype
// Node: opcua_node_objectType_t(ns=1;i=1003), 1:TrafficLightOutputFacility
UA_ObjectTypeAttributes attr;
UA_ObjectTypeAttributes_init(&attr);
attr.displayName = UA_LOCALIZEDTEXT("", "TrafficLightOutputFacility");
attr.description = UA_LOCALIZEDTEXT("", "");
UA_NodeId nodeId = UA_NODEID_NUMERIC(1, 1003);
UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, 58);
UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, 45);
UA_QualifiedName nodeName = UA_QUALIFIEDNAME(1, "TrafficLightOutputFacility");
UA_Server_addObjectTypeNode(server, nodeId, parentNodeId, parentReferenceNodeId, nodeName
       , attr, NULL, NULL);
} while(0);

do {
// Referencing node found and declared as parent: ns=1;i=1003/1:TrafficLightOutputFacility using i=47/HasComponent
// Node: opcua_node_variable_t(ns=1;i=6018), 1:hasSignal
UA_VariableAttributes attr;
UA_VariableAttributes_init(&attr);
attr.displayName = UA_LOCALIZEDTEXT("", "hasSignal");
attr.description = UA_LOCALIZEDTEXT("", "");
UA_NodeId nodeId = UA_NODEID_NUMERIC(1, 6018);
UA_NodeId typeDefinition = UA_NODEID_NULL;
UA_NodeId parentNodeId = UA_NODEID_NUMERIC(1, 1003);
UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, 47);
UA_QualifiedName nodeName = UA_QUALIFIEDNAME(1, "hasSignal");
UA_Server_addVariableNode(server, nodeId, parentNodeId, parentReferenceNodeId, nodeName
       , typeDefinition
       , attr, NULL, NULL);
// This node has the following references that can be created:
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6018), UA_NODEID_NUMERIC(0, 40), UA_EXPANDEDNODEID_NUMERIC(0, 63), true);
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6018), UA_NODEID_NUMERIC(0, 37), UA_EXPANDEDNODEID_NUMERIC(0, 78), true);
} while(0);

do {
// Referencing node found and declared as parent: ns=1;i=1003/1:TrafficLightOutputFacility using i=47/HasComponent
// Node: opcua_node_variable_t(ns=1;i=6017), 1:hasYellow
UA_VariableAttributes attr;
UA_VariableAttributes_init(&attr);
attr.displayName = UA_LOCALIZEDTEXT("", "hasYellow");
attr.description = UA_LOCALIZEDTEXT("", "");
UA_NodeId nodeId = UA_NODEID_NUMERIC(1, 6017);
UA_NodeId typeDefinition = UA_NODEID_NULL;
UA_NodeId parentNodeId = UA_NODEID_NUMERIC(1, 1003);
UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, 47);
UA_QualifiedName nodeName = UA_QUALIFIEDNAME(1, "hasYellow");
UA_Server_addVariableNode(server, nodeId, parentNodeId, parentReferenceNodeId, nodeName
       , typeDefinition
       , attr, NULL, NULL);
// This node has the following references that can be created:
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6017), UA_NODEID_NUMERIC(0, 40), UA_EXPANDEDNODEID_NUMERIC(0, 63), true);
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6017), UA_NODEID_NUMERIC(0, 37), UA_EXPANDEDNODEID_NUMERIC(0, 78), true);
} while(0);

do {
// Referencing node found and declared as parent: ns=1;i=1003/1:TrafficLightOutputFacility using i=47/HasComponent
// Node: opcua_node_variable_t(ns=1;i=6015), 1:statusGreen
UA_VariableAttributes attr;
UA_VariableAttributes_init(&attr);
attr.displayName = UA_LOCALIZEDTEXT("", "statusGreen");
attr.description = UA_LOCALIZEDTEXT("", "");
UA_NodeId nodeId = UA_NODEID_NUMERIC(1, 6015);
UA_NodeId typeDefinition = UA_NODEID_NULL;
UA_NodeId parentNodeId = UA_NODEID_NUMERIC(1, 1003);
UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, 47);
UA_QualifiedName nodeName = UA_QUALIFIEDNAME(1, "statusGreen");
UA_Server_addVariableNode(server, nodeId, parentNodeId, parentReferenceNodeId, nodeName
       , typeDefinition
       , attr, NULL, NULL);
// This node has the following references that can be created:
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6015), UA_NODEID_NUMERIC(0, 40), UA_EXPANDEDNODEID_NUMERIC(0, 63), true);
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6015), UA_NODEID_NUMERIC(0, 37), UA_EXPANDEDNODEID_NUMERIC(0, 78), true);
} while(0);

do {
// Referencing node found and declared as parent: ns=1;i=1003/1:TrafficLightOutputFacility using i=47/HasComponent
// Node: opcua_node_variable_t(ns=1;i=6013), 1:statusRed
UA_VariableAttributes attr;
UA_VariableAttributes_init(&attr);
attr.displayName = UA_LOCALIZEDTEXT("", "statusRed");
attr.description = UA_LOCALIZEDTEXT("", "");
UA_NodeId nodeId = UA_NODEID_NUMERIC(1, 6013);
UA_NodeId typeDefinition = UA_NODEID_NULL;
UA_NodeId parentNodeId = UA_NODEID_NUMERIC(1, 1003);
UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, 47);
UA_QualifiedName nodeName = UA_QUALIFIEDNAME(1, "statusRed");
UA_Server_addVariableNode(server, nodeId, parentNodeId, parentReferenceNodeId, nodeName
       , typeDefinition
       , attr, NULL, NULL);
// This node has the following references that can be created:
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6013), UA_NODEID_NUMERIC(0, 40), UA_EXPANDEDNODEID_NUMERIC(0, 63), true);
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6013), UA_NODEID_NUMERIC(0, 37), UA_EXPANDEDNODEID_NUMERIC(0, 78), true);
} while(0);

do {
// Referencing node found and declared as parent: ns=1;i=1003/1:TrafficLightOutputFacility using i=47/HasComponent
// Node: opcua_node_variable_t(ns=1;i=6016), 1:statusSignal
UA_VariableAttributes attr;
UA_VariableAttributes_init(&attr);
attr.displayName = UA_LOCALIZEDTEXT("", "statusSignal");
attr.description = UA_LOCALIZEDTEXT("", "");
UA_NodeId nodeId = UA_NODEID_NUMERIC(1, 6016);
UA_NodeId typeDefinition = UA_NODEID_NULL;
UA_NodeId parentNodeId = UA_NODEID_NUMERIC(1, 1003);
UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, 47);
UA_QualifiedName nodeName = UA_QUALIFIEDNAME(1, "statusSignal");
UA_Server_addVariableNode(server, nodeId, parentNodeId, parentReferenceNodeId, nodeName
       , typeDefinition
       , attr, NULL, NULL);
// This node has the following references that can be created:
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6016), UA_NODEID_NUMERIC(0, 40), UA_EXPANDEDNODEID_NUMERIC(0, 63), true);
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6016), UA_NODEID_NUMERIC(0, 37), UA_EXPANDEDNODEID_NUMERIC(0, 78), true);
} while(0);

do {
// Referencing node found and declared as parent: ns=1;i=1003/1:TrafficLightOutputFacility using i=47/HasComponent
// Node: opcua_node_variable_t(ns=1;i=6014), 1:statusYellow
UA_VariableAttributes attr;
UA_VariableAttributes_init(&attr);
attr.displayName = UA_LOCALIZEDTEXT("", "statusYellow");
attr.description = UA_LOCALIZEDTEXT("", "");
UA_NodeId nodeId = UA_NODEID_NUMERIC(1, 6014);
UA_NodeId typeDefinition = UA_NODEID_NULL;
UA_NodeId parentNodeId = UA_NODEID_NUMERIC(1, 1003);
UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, 47);
UA_QualifiedName nodeName = UA_QUALIFIEDNAME(1, "statusYellow");
UA_Server_addVariableNode(server, nodeId, parentNodeId, parentReferenceNodeId, nodeName
       , typeDefinition
       , attr, NULL, NULL);
// This node has the following references that can be created:
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6014), UA_NODEID_NUMERIC(0, 40), UA_EXPANDEDNODEID_NUMERIC(0, 63), true);
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6014), UA_NODEID_NUMERIC(0, 37), UA_EXPANDEDNODEID_NUMERIC(0, 78), true);
} while(0);

do {
// Referencing node found and declared as parent: i=58/BaseObjectType using i=45/HasSubtype
// Node: opcua_node_objectType_t(ns=1;i=1001), 1:TrafficLightType
UA_ObjectTypeAttributes attr;
UA_ObjectTypeAttributes_init(&attr);
attr.displayName = UA_LOCALIZEDTEXT("", "TrafficLightType");
attr.description = UA_LOCALIZEDTEXT("", "A Generic, configurable traffic light");
UA_NodeId nodeId = UA_NODEID_NUMERIC(1, 1001);
UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, 58);
UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, 45);
UA_QualifiedName nodeName = UA_QUALIFIEDNAME(1, "TrafficLightType");
UA_Server_addObjectTypeNode(server, nodeId, parentNodeId, parentReferenceNodeId, nodeName
       , attr, NULL, NULL);
} while(0);

do {
// Referencing node found and declared as parent: ns=1;i=1001/1:TrafficLightType using i=47/HasComponent
// Node: opcua_node_variable_t(ns=1;i=6004), 1:autonomous_greenPhase
UA_VariableAttributes attr;
UA_VariableAttributes_init(&attr);
attr.displayName = UA_LOCALIZEDTEXT("", "autonomous_greenPhase");
attr.description = UA_LOCALIZEDTEXT("", "");
UA_NodeId nodeId = UA_NODEID_NUMERIC(1, 6004);
UA_NodeId typeDefinition = UA_NODEID_NULL;
UA_NodeId parentNodeId = UA_NODEID_NUMERIC(1, 1001);
UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, 47);
UA_QualifiedName nodeName = UA_QUALIFIEDNAME(1, "autonomous_greenPhase");
UA_Server_addVariableNode(server, nodeId, parentNodeId, parentReferenceNodeId, nodeName
       , typeDefinition
       , attr, NULL, NULL);
// This node has the following references that can be created:
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6004), UA_NODEID_NUMERIC(0, 40), UA_EXPANDEDNODEID_NUMERIC(0, 63), true);
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6004), UA_NODEID_NUMERIC(0, 37), UA_EXPANDEDNODEID_NUMERIC(0, 78), true);
} while(0);

do {
// Referencing node found and declared as parent: ns=1;i=1001/1:TrafficLightType using i=47/HasComponent
// Node: opcua_node_variable_t(ns=1;i=6003), 1:autonomous_greenPhaseLength
UA_VariableAttributes attr;
UA_VariableAttributes_init(&attr);
attr.displayName = UA_LOCALIZEDTEXT("", "autonomous_greenPhaseLength");
attr.description = UA_LOCALIZEDTEXT("", "");
UA_NodeId nodeId = UA_NODEID_NUMERIC(1, 6003);
UA_NodeId typeDefinition = UA_NODEID_NULL;
UA_NodeId parentNodeId = UA_NODEID_NUMERIC(1, 1001);
UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, 47);
UA_QualifiedName nodeName = UA_QUALIFIEDNAME(1, "autonomous_greenPhaseLength");
UA_Server_addVariableNode(server, nodeId, parentNodeId, parentReferenceNodeId, nodeName
       , typeDefinition
       , attr, NULL, NULL);
// This node has the following references that can be created:
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6003), UA_NODEID_NUMERIC(0, 40), UA_EXPANDEDNODEID_NUMERIC(0, 63), true);
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6003), UA_NODEID_NUMERIC(0, 37), UA_EXPANDEDNODEID_NUMERIC(0, 78), true);
} while(0);

do {
// Referencing node found and declared as parent: ns=1;i=1001/1:TrafficLightType using i=47/HasComponent
// Node: opcua_node_variable_t(ns=1;i=6005), 1:autonomous_sensorAck
UA_VariableAttributes attr;
UA_VariableAttributes_init(&attr);
attr.displayName = UA_LOCALIZEDTEXT("", "autonomous_sensorAck");
attr.description = UA_LOCALIZEDTEXT("", "");
UA_NodeId nodeId = UA_NODEID_NUMERIC(1, 6005);
UA_NodeId typeDefinition = UA_NODEID_NULL;
UA_NodeId parentNodeId = UA_NODEID_NUMERIC(1, 1001);
UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, 47);
UA_QualifiedName nodeName = UA_QUALIFIEDNAME(1, "autonomous_sensorAck");
UA_Server_addVariableNode(server, nodeId, parentNodeId, parentReferenceNodeId, nodeName
       , typeDefinition
       , attr, NULL, NULL);
// This node has the following references that can be created:
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6005), UA_NODEID_NUMERIC(0, 40), UA_EXPANDEDNODEID_NUMERIC(0, 63), true);
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6005), UA_NODEID_NUMERIC(0, 37), UA_EXPANDEDNODEID_NUMERIC(0, 78), true);
} while(0);

do {
// Referencing node found and declared as parent: ns=1;i=1001/1:TrafficLightType using i=47/HasComponent
// Node: opcua_node_variable_t(ns=1;i=6002), 1:autonomous_yellowPhaseLength
UA_VariableAttributes attr;
UA_VariableAttributes_init(&attr);
attr.displayName = UA_LOCALIZEDTEXT("", "autonomous_yellowPhaseLength");
attr.description = UA_LOCALIZEDTEXT("", "");
UA_NodeId nodeId = UA_NODEID_NUMERIC(1, 6002);
UA_NodeId typeDefinition = UA_NODEID_NULL;
UA_NodeId parentNodeId = UA_NODEID_NUMERIC(1, 1001);
UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, 47);
UA_QualifiedName nodeName = UA_QUALIFIEDNAME(1, "autonomous_yellowPhaseLength");
UA_Server_addVariableNode(server, nodeId, parentNodeId, parentReferenceNodeId, nodeName
       , typeDefinition
       , attr, NULL, NULL);
// This node has the following references that can be created:
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6002), UA_NODEID_NUMERIC(0, 40), UA_EXPANDEDNODEID_NUMERIC(0, 63), true);
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6002), UA_NODEID_NUMERIC(0, 37), UA_EXPANDEDNODEID_NUMERIC(0, 78), true);
} while(0);

do {
// Referencing node found and declared as parent: ns=1;i=1001/1:TrafficLightType using i=47/HasComponent
// Node: opcua_node_variable_t(ns=1;i=6007), 1:hasController
UA_VariableAttributes attr;
UA_VariableAttributes_init(&attr);
attr.displayName = UA_LOCALIZEDTEXT("", "hasController");
attr.description = UA_LOCALIZEDTEXT("", "");
UA_NodeId nodeId = UA_NODEID_NUMERIC(1, 6007);
UA_NodeId typeDefinition = UA_NODEID_NULL;
UA_NodeId parentNodeId = UA_NODEID_NUMERIC(1, 1001);
UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, 47);
UA_QualifiedName nodeName = UA_QUALIFIEDNAME(1, "hasController");
UA_Server_addVariableNode(server, nodeId, parentNodeId, parentReferenceNodeId, nodeName
       , typeDefinition
       , attr, NULL, NULL);
// This node has the following references that can be created:
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6007), UA_NODEID_NUMERIC(0, 40), UA_EXPANDEDNODEID_NUMERIC(0, 63), true);
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6007), UA_NODEID_NUMERIC(0, 37), UA_EXPANDEDNODEID_NUMERIC(0, 78), true);
} while(0);

do {
// Referencing node found and declared as parent: ns=1;i=1001/1:TrafficLightType using i=47/HasComponent
// Node: opcua_node_variable_t(ns=1;i=6006), 1:needsController
UA_VariableAttributes attr;
UA_VariableAttributes_init(&attr);
attr.displayName = UA_LOCALIZEDTEXT("", "needsController");
attr.description = UA_LOCALIZEDTEXT("", "");
UA_NodeId nodeId = UA_NODEID_NUMERIC(1, 6006);
UA_NodeId typeDefinition = UA_NODEID_NULL;
UA_NodeId parentNodeId = UA_NODEID_NUMERIC(1, 1001);
UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, 47);
UA_QualifiedName nodeName = UA_QUALIFIEDNAME(1, "needsController");
UA_Server_addVariableNode(server, nodeId, parentNodeId, parentReferenceNodeId, nodeName
       , typeDefinition
       , attr, NULL, NULL);
// This node has the following references that can be created:
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6006), UA_NODEID_NUMERIC(0, 40), UA_EXPANDEDNODEID_NUMERIC(0, 63), true);
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6006), UA_NODEID_NUMERIC(0, 37), UA_EXPANDEDNODEID_NUMERIC(0, 78), true);
} while(0);

do {
// Referencing node found and declared as parent: ns=1;i=1001/1:TrafficLightType using i=47/HasComponent
// Node: opcua_node_variable_t(ns=1;i=6009), 1:requestState
UA_VariableAttributes attr;
UA_VariableAttributes_init(&attr);
attr.displayName = UA_LOCALIZEDTEXT("", "requestState");
attr.description = UA_LOCALIZEDTEXT("", "");
UA_NodeId nodeId = UA_NODEID_NUMERIC(1, 6009);
UA_NodeId typeDefinition = UA_NODEID_NULL;
UA_NodeId parentNodeId = UA_NODEID_NUMERIC(1, 1001);
UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, 47);
UA_QualifiedName nodeName = UA_QUALIFIEDNAME(1, "requestState");
UA_Server_addVariableNode(server, nodeId, parentNodeId, parentReferenceNodeId, nodeName
       , typeDefinition
       , attr, NULL, NULL);
// This node has the following references that can be created:
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6009), UA_NODEID_NUMERIC(0, 40), UA_EXPANDEDNODEID_NUMERIC(0, 63), true);
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6009), UA_NODEID_NUMERIC(0, 37), UA_EXPANDEDNODEID_NUMERIC(0, 78), true);
} while(0);

do {
// Referencing node found and declared as parent: ns=1;i=1001/1:TrafficLightType using i=47/HasComponent
// Node: opcua_node_variable_t(ns=1;i=6008), 1:sensorAck
UA_VariableAttributes attr;
UA_VariableAttributes_init(&attr);
attr.displayName = UA_LOCALIZEDTEXT("", "sensorAck");
attr.description = UA_LOCALIZEDTEXT("", "");
UA_NodeId nodeId = UA_NODEID_NUMERIC(1, 6008);
UA_NodeId typeDefinition = UA_NODEID_NULL;
UA_NodeId parentNodeId = UA_NODEID_NUMERIC(1, 1001);
UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, 47);
UA_QualifiedName nodeName = UA_QUALIFIEDNAME(1, "sensorAck");
UA_Server_addVariableNode(server, nodeId, parentNodeId, parentReferenceNodeId, nodeName
       , typeDefinition
       , attr, NULL, NULL);
// This node has the following references that can be created:
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6008), UA_NODEID_NUMERIC(0, 40), UA_EXPANDEDNODEID_NUMERIC(0, 63), true);
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6008), UA_NODEID_NUMERIC(0, 37), UA_EXPANDEDNODEID_NUMERIC(0, 78), true);
} while(0);

do {
// Referencing node found and declared as parent: ns=1;i=1001/1:TrafficLightType using i=47/HasComponent
// Node: opcua_node_variable_t(ns=1;i=6001), 1:warn_blinkInterval
UA_VariableAttributes attr;
UA_VariableAttributes_init(&attr);
attr.displayName = UA_LOCALIZEDTEXT("", "warn_blinkInterval");
attr.description = UA_LOCALIZEDTEXT("", "");
UA_NodeId nodeId = UA_NODEID_NUMERIC(1, 6001);
UA_NodeId typeDefinition = UA_NODEID_NULL;
UA_NodeId parentNodeId = UA_NODEID_NUMERIC(1, 1001);
UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, 47);
UA_QualifiedName nodeName = UA_QUALIFIEDNAME(1, "warn_blinkInterval");
UA_Server_addVariableNode(server, nodeId, parentNodeId, parentReferenceNodeId, nodeName
       , typeDefinition
       , attr, NULL, NULL);
// This node has the following references that can be created:
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6001), UA_NODEID_NUMERIC(0, 40), UA_EXPANDEDNODEID_NUMERIC(0, 63), true);
UA_Server_addReference(server, UA_NODEID_NUMERIC(1, 6001), UA_NODEID_NUMERIC(0, 37), UA_EXPANDEDNODEID_NUMERIC(0, 78), true);
} while(0);
}
