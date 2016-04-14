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

#ifndef HAVE_UA_PROXIES_CALLBACK_H
#define HAVE_UA_PROXIES_CALLBACK_H

#define C_MACRO_CONCAT_NOEXP(A,B) A ## B
#define C_MACRO_CONCAT(A,B) C_MACRO_CONCAT_NOEXP(A, B) // This causes macros to be expanded

/* Function call proxy generator
 * UA_CALLPROXY: Generate callback for the ua_stack. Calls CLASS_F in CLASS_P (this->) is implied.
 * UA_CALLPROXY_NAME Return the name of the call proxy
 */
// Generate Call-Through functions as stack callbacks
#define UA_CALLPROXY_NAME(_CLASS_P, _CLASS_F) ua_callproxy_##_CLASS_P##_##_CLASS_F
#define UA_CALLPROXY_TABLENAME(_CLASS_P, _CLASS_F) C_MACRO_CONCAT( UA_CALLPROXY_NAME(_CLASS_P,_CLASS_F) , _InstanceLookUpTable)
#define UA_CALLPROXY_TABLE(_CLASS_P, _CLASS_F) & UA_CALLPROXY_TABLENAME(_CLASS_P, _CLASS_F)

#define UA_CALLPROXY(_CLASS_P, _CLASS_F) \
UA_FunctionCall_InstanceLookUpTable UA_CALLPROXY_TABLENAME(_CLASS_P, _CLASS_F); \
UA_StatusCode UA_CALLPROXY_NAME(_CLASS_P,_CLASS_F)(void *methodHandle, const UA_NodeId objectId, size_t inputSize, const UA_Variant *input, size_t outputSize, UA_Variant *output){ \
  for (UA_FunctionCall_InstanceLookUpTable::iterator j=UA_CALLPROXY_TABLENAME(_CLASS_P, _CLASS_F).begin(); j != UA_CALLPROXY_TABLENAME(_CLASS_P, _CLASS_F).end(); j++) \
    if(UA_NodeId_equal(&(*(j))->classObjectId, &objectId)) { \
      _CLASS_P *theClass = static_cast<_CLASS_P *>( (*(j))->classInstance ); \
      return theClass->_CLASS_F(inputSize, input, outputSize, output); \
    } \
}

/* Generators for Valuesource read callbacks
 * Anyone who finds a way to do this using templates gets a cookie!
 * These callbacks are passed as functions to open62541 dataValue variables for read operations. 
 * They invoke the appropriate getXY() function of the object passed as handle.
 */

/* Prototype wrappers */

// Generate Proxy names
#define UA_RDPROXY_NAME(_p_class, _p_method) ua_readproxy_ ##_p_class## _ ##_p_method
#define UA_WRPROXY_NAME(_p_class, _p_method) ua_writeproxy_ ##_p_class## _ ##_p_method

// Generate Proxy tails (common function end)
#define UA_RDPROXY_TAIL() \
value->hasValue = UA_TRUE; \
if (includeSourceTimeStamp) { \
value->sourceTimestamp = UA_DateTime_now(); \
value->hasSourceTimestamp = UA_TRUE; } \
return UA_STATUSCODE_GOOD; } // Ends Fnct

#define UA_WRPROXY_TAIL(_p_method) \
return UA_STATUSCODE_GOOD; } // End Fnct

// Generate Proxy heads (common function starts)
#define UA_RDPROXY_HEAD(_p_class, _p_method) \
UA_StatusCode UA_RDPROXY_NAME(_p_class, _p_method) (void *handle, const UA_NodeId nodeid, UA_Boolean includeSourceTimeStamp, const UA_NumericRange *range, UA_DataValue *value) { \
_p_class *thisObj = static_cast<_p_class *> (handle); \
if (includeSourceTimeStamp) { \
value->serverTimestamp = UA_DateTime_now(); \
value->hasServerTimestamp = UA_TRUE; \
}

#define UA_WRPROXY_HEAD(_p_class, _p_method)  \
UA_StatusCode UA_WRPROXY_NAME(_p_class, _p_method) (void *handle, const UA_NodeId nodeid,const UA_Variant *data, const UA_NumericRange *range) {\
_p_class *theClass = static_cast<_p_class *> (handle);

// Generator for Simple Read bodies (type cast)
#define UA_RDPROXY_SIMPLEBODY(_p_method, _p_ctype, _p_uatype) \
_p_ctype ua_val = thisObj->_p_method(); \
UA_Variant_setScalarCopy(&value->value, &ua_val, &UA_TYPES[_p_uatype]); \

#define UA_WRPROXY_SIMPLEBODY(_p_method, _p_ctype) \
_p_ctype value = (_p_ctype) *((_p_ctype *) data->data); \
theClass->_p_method (value);

// Typed Function Protoypes with datatype specific stuff
// Readproxies:
#define UA_RDPROXY_STRING(_p_class, _p_method) \
UA_RDPROXY_HEAD(_p_class, _p_method) \
UA_String ua_val; \
CPPSTRING_TO_UASTRING(ua_val, thisObj->_p_method()); \
UA_Variant_setScalarCopy(&value->value, &ua_val, &UA_TYPES[UA_TYPES_STRING]); \
UA_String_deleteMembers(&ua_val); \
UA_RDPROXY_TAIL()

#define UA_RDPROXY_INT32(_p_class, _p_method) \
UA_RDPROXY_HEAD(_p_class, _p_method) \
UA_RDPROXY_SIMPLEBODY(_p_method, int32_t, UA_TYPES_INT32); \
UA_RDPROXY_TAIL()

#define UA_RDPROXY_UINT32(_p_class, _p_method) \
UA_RDPROXY_HEAD(_p_class, _p_method) \
UA_RDPROXY_SIMPLEBODY(_p_method, uint32_t, UA_TYPES_UINT32); \
UA_RDPROXY_TAIL()

#define UA_RDPROXY_INT16(_p_class, _p_method) \
UA_RDPROXY_HEAD(_p_class, _p_method) \
UA_RDPROXY_SIMPLEBODY(_p_method, int16_t, UA_TYPES_INT16); \
UA_RDPROXY_TAIL()

#define UA_RDPROXY_UINT16(_p_class, _p_method) \
UA_RDPROXY_HEAD(_p_class, _p_method) \
UA_RDPROXY_SIMPLEBODY(_p_method, uint16_t, UA_TYPES_UINT16); \
UA_RDPROXY_TAIL()

#define UA_RDPROXY_INT8(_p_class, _p_method) \
UA_RDPROXY_HEAD(_p_class, _p_method) \
UA_RDPROXY_SIMPLEBODY(_p_method, int8_t, UA_TYPES_INT8); \
UA_RDPROXY_TAIL()

#define UA_RDPROXY_UINT8(_p_class, _p_method) \
UA_RDPROXY_HEAD(_p_class, _p_method) \
UA_RDPROXY_SIMPLEBODY(_p_method, uint8_t, UA_TYPES_UINT8); \
UA_RDPROXY_TAIL()

#define UA_RDPROXY_BOOL(_p_class, _p_method) \
UA_RDPROXY_HEAD(_p_class, _p_method) \
UA_RDPROXY_SIMPLEBODY(_p_method, UA_Boolean, UA_TYPES_BOOLEAN); \
UA_RDPROXY_TAIL()

#define UA_RDPROXY_FLOAT(_p_class, _p_method) \
UA_RDPROXY_HEAD(_p_class, _p_method) \
UA_RDPROXY_SIMPLEBODY(_p_method, float); \
UA_RDPROXY_TAIL()

#define UA_RDPROXY_DOUBLE(_p_class, _p_method) \
UA_RDPROXY_HEAD(_p_class, _p_method) \
UA_RDPROXY_SIMPLEBODY(_p_method, double); \
UA_RDPROXY_TAIL()


// Writeproxies:

#define UA_WRPROXY_INT8(_p_class, _p_method) \
UA_WRPROXY_HEAD(_p_class, _p_method) \
UA_WRPROXY_SIMPLEBODY(_p_method, uint32_t); \
UA_WRPROXY_TAIL()

#define UA_WRPROXY_UINT8(_p_class, _p_method) \
UA_WRPROXY_HEAD(_p_class, _p_method) \
UA_WRPROXY_SIMPLEBODY(_p_method, uint32_t); \
UA_WRPROXY_TAIL()

#define UA_WRPROXY_INT16(_p_class, _p_method) \
UA_WRPROXY_HEAD(_p_class, _p_method) \
UA_WRPROXY_SIMPLEBODY(_p_method, uint32_t); \
UA_WRPROXY_TAIL()

#define UA_WRPROXY_UINT16(_p_class, _p_method) \
UA_WRPROXY_HEAD(_p_class, _p_method) \
UA_WRPROXY_SIMPLEBODY(_p_method, uint32_t); \
UA_WRPROXY_TAIL()

#define UA_WRPROXY_INT32(_p_class, _p_method) \
UA_WRPROXY_HEAD(_p_class, _p_method) \
UA_WRPROXY_SIMPLEBODY(_p_method, uint32_t); \
UA_WRPROXY_TAIL()

#define UA_WRPROXY_UINT32(_p_class, _p_method) \
UA_WRPROXY_HEAD(_p_class, _p_method) \
UA_WRPROXY_SIMPLEBODY(_p_method, uint32_t); \
UA_WRPROXY_TAIL()

#define UA_WRPROXY_BOOL(_p_class, _p_method) \
UA_WRPROXY_HEAD(_p_class, _p_method) \
UA_WRPROXY_SIMPLEBODY(_p_method, bool); \
UA_WRPROXY_TAIL()


#define UA_WRPROXY_FLOAT(_p_class, _p_method) \
UA_WRPROXY_HEAD(_p_class, _p_method) \
UA_WRPROXY_SIMPLEBODY(_p_method, float); \
UA_WRPROXY_TAIL()

#define UA_WRPROXY_DOUBLE(_p_class, _p_method) \
UA_WRPROXY_HEAD(_p_class, _p_method) \
UA_WRPROXY_SIMPLEBODY(_p_method, double); \
UA_WRPROXY_TAIL()

#endif //HAVE_UA_PROXIES_CALLBACK_H