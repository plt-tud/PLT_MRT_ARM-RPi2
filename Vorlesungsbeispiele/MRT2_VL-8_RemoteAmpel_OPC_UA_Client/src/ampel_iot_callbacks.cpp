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

#include "ampel_iot_callbacks.h"

UA_StatusCode
readRedLight(UA_Server *server,
             const UA_NodeId *sessionId, void *sessionContext,
             const UA_NodeId *nodeId, void *nodeContext,
             UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
             UA_DataValue *dataValue) {
    Ampel* instance = static_cast<Ampel *>(nodeContext);

    UA_Boolean light = UA_FALSE;
    if(instance->getRedLight()) light = UA_TRUE; 
    
    UA_Variant_setScalarCopy(&dataValue->value, &light, &UA_TYPES[UA_TYPES_BOOLEAN]);
    dataValue->hasValue = true;
    return UA_STATUSCODE_GOOD;
}

UA_StatusCode
writeRedLight(UA_Server *server,
                 const UA_NodeId *sessionId, void *sessionContext,
                 const UA_NodeId *nodeId, void *nodeContext,
                 const UA_NumericRange *range, const UA_DataValue *data) {
    Ampel* instance = static_cast<Ampel *>(nodeContext);
    if (data->hasValue == UA_TRUE && data->value.type == &UA_TYPES[UA_TYPES_BOOLEAN] )  {
        UA_Boolean *set = (UA_Boolean*) data->value.data;
        if (*set == UA_TRUE)         instance->setRedLight(true);
        else                         instance->setRedLight(false);
    }
    return UA_STATUSCODE_GOOD;
}

UA_StatusCode
readYellowLight(UA_Server *server,
             const UA_NodeId *sessionId, void *sessionContext,
             const UA_NodeId *nodeId, void *nodeContext,
             UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
             UA_DataValue *dataValue) {
    Ampel* instance = static_cast<Ampel *>(nodeContext);

    UA_Boolean light = UA_FALSE;
    if(instance->getYellowLight()) light = UA_TRUE; 
    
    UA_Variant_setScalarCopy(&dataValue->value, &light, &UA_TYPES[UA_TYPES_BOOLEAN]);
    dataValue->hasValue = true;
    return UA_STATUSCODE_GOOD;
}

UA_StatusCode
writeYellowLight(UA_Server *server,
                 const UA_NodeId *sessionId, void *sessionContext,
                 const UA_NodeId *nodeId, void *nodeContext,
                 const UA_NumericRange *range, const UA_DataValue *data) {
    Ampel* instance = static_cast<Ampel *>(nodeContext);
    if (data->hasValue == UA_TRUE && data->value.type == &UA_TYPES[UA_TYPES_BOOLEAN] )  {
        UA_Boolean *set = (UA_Boolean*) data->value.data;
        if (*set == UA_TRUE)         instance->setYellowLight(true);
        else                         instance->setYellowLight(false);
    }
    return UA_STATUSCODE_GOOD;
}

UA_StatusCode
readGreenLight(UA_Server *server,
             const UA_NodeId *sessionId, void *sessionContext,
             const UA_NodeId *nodeId, void *nodeContext,
             UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
             UA_DataValue *dataValue) {
    Ampel* instance = static_cast<Ampel *>(nodeContext);

    UA_Boolean light = UA_FALSE;
    if(instance->getGreenLight()) light = UA_TRUE; 
    
    UA_Variant_setScalarCopy(&dataValue->value, &light, &UA_TYPES[UA_TYPES_BOOLEAN]);
    dataValue->hasValue = true;
    return UA_STATUSCODE_GOOD;
}

UA_StatusCode
writeGreenLight(UA_Server *server,
                 const UA_NodeId *sessionId, void *sessionContext,
                 const UA_NodeId *nodeId, void *nodeContext,
                 const UA_NumericRange *range, const UA_DataValue *data) {
    Ampel* instance = static_cast<Ampel *>(nodeContext);
    if (data->hasValue == UA_TRUE && data->value.type == &UA_TYPES[UA_TYPES_BOOLEAN] )  {
        UA_Boolean *set = (UA_Boolean*) data->value.data;
        if (*set == UA_TRUE)         instance->setGreenLight(true);
        else                         instance->setGreenLight(false);
    }
    return UA_STATUSCODE_GOOD;
}

UA_StatusCode
readSensor(UA_Server *server,
             const UA_NodeId *sessionId, void *sessionContext,
             const UA_NodeId *nodeId, void *nodeContext,
             UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
             UA_DataValue *dataValue) {
    Ampel* instance = static_cast<Ampel *>(nodeContext);

    UA_Boolean light = UA_FALSE;
    if(instance->getSensor()) light = UA_TRUE; 
    
    UA_Variant_setScalarCopy(&dataValue->value, &light, &UA_TYPES[UA_TYPES_BOOLEAN]);
    dataValue->hasValue = true;
    return UA_STATUSCODE_GOOD;
}

UA_StatusCode
writeSensor(UA_Server *server,
                 const UA_NodeId *sessionId, void *sessionContext,
                 const UA_NodeId *nodeId, void *nodeContext,
                 const UA_NumericRange *range, const UA_DataValue *data) {
    Ampel* instance = static_cast<Ampel *>(nodeContext);
    if (data->hasValue == UA_TRUE  && data->value.type == &UA_TYPES[UA_TYPES_BOOLEAN] )  {
        UA_Boolean *set = (UA_Boolean*) data->value.data;
        if (*set == UA_TRUE)         instance->setSensor(true);
        else                         instance->setSensor(false);
    }
    return UA_STATUSCODE_GOOD;
}

UA_StatusCode
readHasController(UA_Server *server,
             const UA_NodeId *sessionId, void *sessionContext,
             const UA_NodeId *nodeId, void *nodeContext,
             UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
             UA_DataValue *dataValue) {
    Ampel* instance = static_cast<Ampel *>(nodeContext);

    UA_Boolean light = UA_FALSE;
    if(instance->hasController()) light = UA_TRUE; 
    
    UA_Variant_setScalarCopy(&dataValue->value, &light, &UA_TYPES[UA_TYPES_BOOLEAN]);
    dataValue->hasValue = true;
    return UA_STATUSCODE_GOOD;
}

UA_StatusCode
writeHasController(UA_Server *server,
                 const UA_NodeId *sessionId, void *sessionContext,
                 const UA_NodeId *nodeId, void *nodeContext,
                 const UA_NumericRange *range, const UA_DataValue *data) {
    Ampel* instance = static_cast<Ampel *>(nodeContext);
    if (data->hasValue == UA_TRUE && data->value.type == &UA_TYPES[UA_TYPES_BOOLEAN] )  {
        UA_Boolean *set = (UA_Boolean*) data->value.data;
        if (*set == UA_TRUE)         instance->setController(true);
        else                         instance->setController(false);
    }
    return UA_STATUSCODE_GOOD;
}

UA_StatusCode
readPhaseCommand(UA_Server *server,
             const UA_NodeId *sessionId, void *sessionContext,
             const UA_NodeId *nodeId, void *nodeContext,
             UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
             UA_DataValue *dataValue) {
    Ampel* instance = static_cast<Ampel *>(nodeContext);

    UA_Int32 command = instance->getPhaseCommand();
    
    UA_Variant_setScalarCopy(&dataValue->value, &command, &UA_TYPES[UA_TYPES_INT32]);
    dataValue->hasValue = true;
    return UA_STATUSCODE_GOOD;
}

UA_StatusCode
writePhaseCommand(UA_Server *server,
                 const UA_NodeId *sessionId, void *sessionContext,
                 const UA_NodeId *nodeId, void *nodeContext,
                 const UA_NumericRange *range, const UA_DataValue *data) {
    Ampel* instance = static_cast<Ampel *>(nodeContext);
    if (data->hasValue == UA_TRUE && data->value.type == &UA_TYPES[UA_TYPES_INT32] )  {
        UA_Int32 *set = (UA_Int32*) data->value.data;
        instance->setPhaseCommand((ampel_phaseId) *set);
    }
    return UA_STATUSCODE_GOOD;
}
