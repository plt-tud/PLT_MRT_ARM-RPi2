/*
 * Copyright (c) 2018 Chris Paul Iatrou <Chris_Paul.Iatrou@tu-dresden.de>
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

#include "ampel_iot_opcua.h"
#include "ampel_iot_callbacks.h"

#include <iostream>

/* Yes, we know we're creating char* strings in the "deprecated style", 
 * disable the compiler warning. */
#pragma GCC diagnostic ignored "-Wwrite-strings"

Ampel* ampel_iot_opcua::getAmpel()
{
    return a;
}

void ampel_iot_opcua::init()
{
    if (server != nullptr) return;
    
    serverConfig = UA_ServerConfig_new_default();
    server       = UA_Server_new(serverConfig);
    
    /* Konstruktion des nachfolgenden Models in OPC UA:
     * 
     * Objects 
     *  +- Ampel
     *      +- bool hasController
     *      +- bool redLight
     *      +- bool yellowLight
     *      +- bool greenLight
     *      +- bool sensor
     *      +- int  currentPhase
     */
    UA_StatusCode retval;
    UA_NodeId ampelObjectNodeId;
    UA_ObjectAttributes attr = UA_ObjectAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT("de_DE", "Ampel");
    attr.description = UA_LOCALIZEDTEXT("de_DE", "Ampel mit 3 Lichtern");
    retval = UA_Server_addObjectNode( 
                            server, UA_NODEID_NULL, // Unser Instanz-Server, NodeId ist egal
                             UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), // Parent
                             UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),     // Reference Parent --> Ampel
                             UA_QUALIFIEDNAME(1, "Ampel"),                 // browseName
                             UA_NODEID_NUMERIC(0, UA_NS0ID_FOLDERTYPE),    // In Abwesenheit eines Ampeltypenn... nur als Ordner angegeben
                             attr,
                             nullptr,                                      // Ohne Kontext (handle)
                             &ampelObjectNodeId                            // Erstellte NodeId hier speichern
    );
    
    if (retval != UA_STATUSCODE_GOOD)
        return;
    
    /* Durchleitung der OPC UA Read/Write-Anfragen an unsere Klasseninstanz
     * 
     */
    UA_VariableAttributes vattr = UA_VariableAttributes_default;
    vattr.displayName           = UA_LOCALIZEDTEXT("de_DE", "redLight");
    
    // WARNING: You might want to reconsider WRITE-Access to individual signals for a "production environment"...
    vattr.accessLevel           = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    UA_DataSource redLightDataSource, greenLightDataSource, yellowLightDataSource, sensorDataSource, hasControllerDataSource, phaseCommandDataSource;
    redLightDataSource.read     = readRedLight;
    redLightDataSource.write    = writeRedLight;
    yellowLightDataSource.read  = readYellowLight;
    yellowLightDataSource.write = writeYellowLight;
    greenLightDataSource.read   = readGreenLight;
    greenLightDataSource.write  = writeGreenLight;
    
    sensorDataSource.read       = readSensor;
    sensorDataSource.write      = writeSensor;
    
    phaseCommandDataSource.read  = readPhaseCommand;
    phaseCommandDataSource.write = writePhaseCommand;
    
    hasControllerDataSource.read  = readHasController;
    hasControllerDataSource.write = writeHasController;
    
    retval = UA_Server_addDataSourceVariableNode(
                server, UA_NODEID_STRING(1, "redLight"), 
                ampelObjectNodeId, 
                UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT), 
                UA_QUALIFIEDNAME(1, "redLight"),
                UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), // BaseType, da wir keinen Licht-Typen haben 
                vattr, redLightDataSource, 
                (void*) this->a,                                        // Handle: Diese Klasseninstanz (wie beim Automaton)
                NULL);
    
    vattr.displayName           = UA_LOCALIZEDTEXT("de_DE", "yellowLight");
    retval = UA_Server_addDataSourceVariableNode(
                server, UA_NODEID_STRING(1, "yellowLight"), 
                ampelObjectNodeId, 
                UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT), 
                UA_QUALIFIEDNAME(1, "yellowLight"),
                UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), // BaseType, da wir keinen Licht-Typen haben 
                vattr, yellowLightDataSource, 
                (void*) this->a,                                        // Handle: Diese Klasseninstanz (wie beim Automaton)
                NULL);
    
    vattr.displayName           = UA_LOCALIZEDTEXT("de_DE", "greenLight");
    retval = UA_Server_addDataSourceVariableNode(
                server, UA_NODEID_STRING(1, "greenLight"), 
                ampelObjectNodeId, 
                UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT), 
                UA_QUALIFIEDNAME(1, "greenLight"),
                UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), // BaseType, da wir keinen Licht-Typen haben 
                vattr, greenLightDataSource, 
                (void*) this->a,                                        // Handle: Diese Klasseninstanz (wie beim Automaton)
                NULL);

    vattr.displayName           = UA_LOCALIZEDTEXT("de_DE", "sensor");
    retval = UA_Server_addDataSourceVariableNode(
                server, UA_NODEID_STRING(1, "sensor"), 
                ampelObjectNodeId, 
                UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT), 
                UA_QUALIFIEDNAME(1, "sensor"),
                UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), // BaseType, da wir keinen Licht-Typen haben 
                vattr, sensorDataSource, 
                (void*) this->a,                                        // Handle: Diese Klasseninstanz (wie beim Automaton)
                NULL);
    
    vattr.displayName           = UA_LOCALIZEDTEXT("de_DE", "hasController");
    retval = UA_Server_addDataSourceVariableNode(
                server, UA_NODEID_STRING(1, "hasController"), 
                ampelObjectNodeId, 
                UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT), 
                UA_QUALIFIEDNAME(1, "hasController"),
                UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), // BaseType, da wir keinen Licht-Typen haben 
                vattr, hasControllerDataSource, 
                (void*) this->a,                                        // Handle: Diese Klasseninstanz (wie beim Automaton)
                NULL);
    
    // Only one definetely getting write access...
    vattr.accessLevel           = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    vattr.displayName           = UA_LOCALIZEDTEXT("de_DE", "phaseCommand");
    retval = UA_Server_addDataSourceVariableNode(
                server, UA_NODEID_STRING(1, "phaseCommand"), 
                ampelObjectNodeId, 
                UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT), 
                UA_QUALIFIEDNAME(1, "phaseCommand"),
                UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), // BaseType, da wir keinen Licht-Typen haben 
                vattr, phaseCommandDataSource, 
                (void*) this->a,                                        // Handle: Diese Klasseninstanz (wie beim Automaton)
                NULL);
}

void ampel_iot_opcua::run()
{
    if (server)
        UA_Server_run(server, &runThread); // Kein Problem: Boolean-Typ in C++ auch 32 bit, gleiche Kodierung wie UA_Boolean
}

void ampel_iot_opcua::terminate()
{
    if (server != nullptr) return;
    
    UA_Server_delete(server);
    UA_ServerConfig_delete(serverConfig);
    server = nullptr;
}
