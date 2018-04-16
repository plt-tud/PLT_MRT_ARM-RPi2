/* Generated from Opc.Ua.Types.bsd with script /home/ichrispa/work/svn/working_copies/open62541/tools/generate_datatypes.py
 * on host adriana by user ichrispa at 2016-04-14 07:26:15 */
 
#include "ua_types_encoding_binary.h"
#include "ua_types_generated.h"

/* UA_Boolean */
static UA_INLINE UA_StatusCode UA_Boolean_encodeBinary(const UA_Boolean *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_BOOLEAN], dst, offset); }
static UA_INLINE UA_StatusCode UA_Boolean_decodeBinary(const UA_ByteString *src, size_t *offset, UA_Boolean *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_BOOLEAN]); }

/* UA_SByte */
static UA_INLINE UA_StatusCode UA_SByte_encodeBinary(const UA_SByte *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_SBYTE], dst, offset); }
static UA_INLINE UA_StatusCode UA_SByte_decodeBinary(const UA_ByteString *src, size_t *offset, UA_SByte *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_SBYTE]); }

/* UA_Byte */
static UA_INLINE UA_StatusCode UA_Byte_encodeBinary(const UA_Byte *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_BYTE], dst, offset); }
static UA_INLINE UA_StatusCode UA_Byte_decodeBinary(const UA_ByteString *src, size_t *offset, UA_Byte *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_BYTE]); }

/* UA_Int16 */
static UA_INLINE UA_StatusCode UA_Int16_encodeBinary(const UA_Int16 *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_INT16], dst, offset); }
static UA_INLINE UA_StatusCode UA_Int16_decodeBinary(const UA_ByteString *src, size_t *offset, UA_Int16 *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_INT16]); }

/* UA_UInt16 */
static UA_INLINE UA_StatusCode UA_UInt16_encodeBinary(const UA_UInt16 *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_UINT16], dst, offset); }
static UA_INLINE UA_StatusCode UA_UInt16_decodeBinary(const UA_ByteString *src, size_t *offset, UA_UInt16 *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_UINT16]); }

/* UA_Int32 */
static UA_INLINE UA_StatusCode UA_Int32_encodeBinary(const UA_Int32 *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_INT32], dst, offset); }
static UA_INLINE UA_StatusCode UA_Int32_decodeBinary(const UA_ByteString *src, size_t *offset, UA_Int32 *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_INT32]); }

/* UA_UInt32 */
static UA_INLINE UA_StatusCode UA_UInt32_encodeBinary(const UA_UInt32 *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_UINT32], dst, offset); }
static UA_INLINE UA_StatusCode UA_UInt32_decodeBinary(const UA_ByteString *src, size_t *offset, UA_UInt32 *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_UINT32]); }

/* UA_Int64 */
static UA_INLINE UA_StatusCode UA_Int64_encodeBinary(const UA_Int64 *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_INT64], dst, offset); }
static UA_INLINE UA_StatusCode UA_Int64_decodeBinary(const UA_ByteString *src, size_t *offset, UA_Int64 *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_INT64]); }

/* UA_UInt64 */
static UA_INLINE UA_StatusCode UA_UInt64_encodeBinary(const UA_UInt64 *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_UINT64], dst, offset); }
static UA_INLINE UA_StatusCode UA_UInt64_decodeBinary(const UA_ByteString *src, size_t *offset, UA_UInt64 *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_UINT64]); }

/* UA_Float */
static UA_INLINE UA_StatusCode UA_Float_encodeBinary(const UA_Float *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_FLOAT], dst, offset); }
static UA_INLINE UA_StatusCode UA_Float_decodeBinary(const UA_ByteString *src, size_t *offset, UA_Float *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_FLOAT]); }

/* UA_Double */
static UA_INLINE UA_StatusCode UA_Double_encodeBinary(const UA_Double *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_DOUBLE], dst, offset); }
static UA_INLINE UA_StatusCode UA_Double_decodeBinary(const UA_ByteString *src, size_t *offset, UA_Double *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_DOUBLE]); }

/* UA_String */
static UA_INLINE UA_StatusCode UA_String_encodeBinary(const UA_String *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_STRING], dst, offset); }
static UA_INLINE UA_StatusCode UA_String_decodeBinary(const UA_ByteString *src, size_t *offset, UA_String *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_STRING]); }

/* UA_DateTime */
static UA_INLINE UA_StatusCode UA_DateTime_encodeBinary(const UA_DateTime *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_DATETIME], dst, offset); }
static UA_INLINE UA_StatusCode UA_DateTime_decodeBinary(const UA_ByteString *src, size_t *offset, UA_DateTime *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_DATETIME]); }

/* UA_Guid */
static UA_INLINE UA_StatusCode UA_Guid_encodeBinary(const UA_Guid *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_GUID], dst, offset); }
static UA_INLINE UA_StatusCode UA_Guid_decodeBinary(const UA_ByteString *src, size_t *offset, UA_Guid *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_GUID]); }

/* UA_ByteString */
static UA_INLINE UA_StatusCode UA_ByteString_encodeBinary(const UA_ByteString *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_BYTESTRING], dst, offset); }
static UA_INLINE UA_StatusCode UA_ByteString_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ByteString *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_BYTESTRING]); }

/* UA_XmlElement */
static UA_INLINE UA_StatusCode UA_XmlElement_encodeBinary(const UA_XmlElement *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_XMLELEMENT], dst, offset); }
static UA_INLINE UA_StatusCode UA_XmlElement_decodeBinary(const UA_ByteString *src, size_t *offset, UA_XmlElement *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_XMLELEMENT]); }

/* UA_NodeId */
static UA_INLINE UA_StatusCode UA_NodeId_encodeBinary(const UA_NodeId *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_NODEID], dst, offset); }
static UA_INLINE UA_StatusCode UA_NodeId_decodeBinary(const UA_ByteString *src, size_t *offset, UA_NodeId *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_NODEID]); }

/* UA_ExpandedNodeId */
static UA_INLINE UA_StatusCode UA_ExpandedNodeId_encodeBinary(const UA_ExpandedNodeId *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_EXPANDEDNODEID], dst, offset); }
static UA_INLINE UA_StatusCode UA_ExpandedNodeId_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ExpandedNodeId *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_EXPANDEDNODEID]); }

/* UA_StatusCode */
static UA_INLINE UA_StatusCode UA_StatusCode_encodeBinary(const UA_StatusCode *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_STATUSCODE], dst, offset); }
static UA_INLINE UA_StatusCode UA_StatusCode_decodeBinary(const UA_ByteString *src, size_t *offset, UA_StatusCode *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_STATUSCODE]); }

/* UA_QualifiedName */
static UA_INLINE UA_StatusCode UA_QualifiedName_encodeBinary(const UA_QualifiedName *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_QUALIFIEDNAME], dst, offset); }
static UA_INLINE UA_StatusCode UA_QualifiedName_decodeBinary(const UA_ByteString *src, size_t *offset, UA_QualifiedName *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_QUALIFIEDNAME]); }

/* UA_LocalizedText */
static UA_INLINE UA_StatusCode UA_LocalizedText_encodeBinary(const UA_LocalizedText *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_LOCALIZEDTEXT], dst, offset); }
static UA_INLINE UA_StatusCode UA_LocalizedText_decodeBinary(const UA_ByteString *src, size_t *offset, UA_LocalizedText *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_LOCALIZEDTEXT]); }

/* UA_ExtensionObject */
static UA_INLINE UA_StatusCode UA_ExtensionObject_encodeBinary(const UA_ExtensionObject *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_EXTENSIONOBJECT], dst, offset); }
static UA_INLINE UA_StatusCode UA_ExtensionObject_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ExtensionObject *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_EXTENSIONOBJECT]); }

/* UA_DataValue */
static UA_INLINE UA_StatusCode UA_DataValue_encodeBinary(const UA_DataValue *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_DATAVALUE], dst, offset); }
static UA_INLINE UA_StatusCode UA_DataValue_decodeBinary(const UA_ByteString *src, size_t *offset, UA_DataValue *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_DATAVALUE]); }

/* UA_Variant */
static UA_INLINE UA_StatusCode UA_Variant_encodeBinary(const UA_Variant *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_VARIANT], dst, offset); }
static UA_INLINE UA_StatusCode UA_Variant_decodeBinary(const UA_ByteString *src, size_t *offset, UA_Variant *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_VARIANT]); }

/* UA_DiagnosticInfo */
static UA_INLINE UA_StatusCode UA_DiagnosticInfo_encodeBinary(const UA_DiagnosticInfo *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_DIAGNOSTICINFO], dst, offset); }
static UA_INLINE UA_StatusCode UA_DiagnosticInfo_decodeBinary(const UA_ByteString *src, size_t *offset, UA_DiagnosticInfo *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_DIAGNOSTICINFO]); }

/* UA_IdType */
static UA_INLINE UA_StatusCode UA_IdType_encodeBinary(const UA_IdType *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_IDTYPE], dst, offset); }
static UA_INLINE UA_StatusCode UA_IdType_decodeBinary(const UA_ByteString *src, size_t *offset, UA_IdType *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_IDTYPE]); }

/* UA_NodeClass */
static UA_INLINE UA_StatusCode UA_NodeClass_encodeBinary(const UA_NodeClass *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_NODECLASS], dst, offset); }
static UA_INLINE UA_StatusCode UA_NodeClass_decodeBinary(const UA_ByteString *src, size_t *offset, UA_NodeClass *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_NODECLASS]); }

/* UA_ReferenceNode */
static UA_INLINE UA_StatusCode UA_ReferenceNode_encodeBinary(const UA_ReferenceNode *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_REFERENCENODE], dst, offset); }
static UA_INLINE UA_StatusCode UA_ReferenceNode_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ReferenceNode *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_REFERENCENODE]); }

/* UA_Argument */
static UA_INLINE UA_StatusCode UA_Argument_encodeBinary(const UA_Argument *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_ARGUMENT], dst, offset); }
static UA_INLINE UA_StatusCode UA_Argument_decodeBinary(const UA_ByteString *src, size_t *offset, UA_Argument *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_ARGUMENT]); }

/* UA_ApplicationType */
static UA_INLINE UA_StatusCode UA_ApplicationType_encodeBinary(const UA_ApplicationType *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_APPLICATIONTYPE], dst, offset); }
static UA_INLINE UA_StatusCode UA_ApplicationType_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ApplicationType *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_APPLICATIONTYPE]); }

/* UA_ApplicationDescription */
static UA_INLINE UA_StatusCode UA_ApplicationDescription_encodeBinary(const UA_ApplicationDescription *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_APPLICATIONDESCRIPTION], dst, offset); }
static UA_INLINE UA_StatusCode UA_ApplicationDescription_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ApplicationDescription *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_APPLICATIONDESCRIPTION]); }

/* UA_RequestHeader */
static UA_INLINE UA_StatusCode UA_RequestHeader_encodeBinary(const UA_RequestHeader *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_REQUESTHEADER], dst, offset); }
static UA_INLINE UA_StatusCode UA_RequestHeader_decodeBinary(const UA_ByteString *src, size_t *offset, UA_RequestHeader *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_REQUESTHEADER]); }

/* UA_ResponseHeader */
static UA_INLINE UA_StatusCode UA_ResponseHeader_encodeBinary(const UA_ResponseHeader *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_RESPONSEHEADER], dst, offset); }
static UA_INLINE UA_StatusCode UA_ResponseHeader_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ResponseHeader *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_RESPONSEHEADER]); }

/* UA_ServiceFault */
static UA_INLINE UA_StatusCode UA_ServiceFault_encodeBinary(const UA_ServiceFault *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_SERVICEFAULT], dst, offset); }
static UA_INLINE UA_StatusCode UA_ServiceFault_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ServiceFault *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_SERVICEFAULT]); }

/* UA_FindServersRequest */
static UA_INLINE UA_StatusCode UA_FindServersRequest_encodeBinary(const UA_FindServersRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_FINDSERVERSREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_FindServersRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_FindServersRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_FINDSERVERSREQUEST]); }

/* UA_FindServersResponse */
static UA_INLINE UA_StatusCode UA_FindServersResponse_encodeBinary(const UA_FindServersResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_FINDSERVERSRESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_FindServersResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_FindServersResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_FINDSERVERSRESPONSE]); }

/* UA_MessageSecurityMode */
static UA_INLINE UA_StatusCode UA_MessageSecurityMode_encodeBinary(const UA_MessageSecurityMode *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_MESSAGESECURITYMODE], dst, offset); }
static UA_INLINE UA_StatusCode UA_MessageSecurityMode_decodeBinary(const UA_ByteString *src, size_t *offset, UA_MessageSecurityMode *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_MESSAGESECURITYMODE]); }

/* UA_UserTokenType */
static UA_INLINE UA_StatusCode UA_UserTokenType_encodeBinary(const UA_UserTokenType *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_USERTOKENTYPE], dst, offset); }
static UA_INLINE UA_StatusCode UA_UserTokenType_decodeBinary(const UA_ByteString *src, size_t *offset, UA_UserTokenType *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_USERTOKENTYPE]); }

/* UA_UserTokenPolicy */
static UA_INLINE UA_StatusCode UA_UserTokenPolicy_encodeBinary(const UA_UserTokenPolicy *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_USERTOKENPOLICY], dst, offset); }
static UA_INLINE UA_StatusCode UA_UserTokenPolicy_decodeBinary(const UA_ByteString *src, size_t *offset, UA_UserTokenPolicy *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_USERTOKENPOLICY]); }

/* UA_EndpointDescription */
static UA_INLINE UA_StatusCode UA_EndpointDescription_encodeBinary(const UA_EndpointDescription *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_ENDPOINTDESCRIPTION], dst, offset); }
static UA_INLINE UA_StatusCode UA_EndpointDescription_decodeBinary(const UA_ByteString *src, size_t *offset, UA_EndpointDescription *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_ENDPOINTDESCRIPTION]); }

/* UA_GetEndpointsRequest */
static UA_INLINE UA_StatusCode UA_GetEndpointsRequest_encodeBinary(const UA_GetEndpointsRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_GETENDPOINTSREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_GetEndpointsRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_GetEndpointsRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_GETENDPOINTSREQUEST]); }

/* UA_GetEndpointsResponse */
static UA_INLINE UA_StatusCode UA_GetEndpointsResponse_encodeBinary(const UA_GetEndpointsResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_GETENDPOINTSRESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_GetEndpointsResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_GetEndpointsResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_GETENDPOINTSRESPONSE]); }

/* UA_SecurityTokenRequestType */
static UA_INLINE UA_StatusCode UA_SecurityTokenRequestType_encodeBinary(const UA_SecurityTokenRequestType *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_SECURITYTOKENREQUESTTYPE], dst, offset); }
static UA_INLINE UA_StatusCode UA_SecurityTokenRequestType_decodeBinary(const UA_ByteString *src, size_t *offset, UA_SecurityTokenRequestType *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_SECURITYTOKENREQUESTTYPE]); }

/* UA_ChannelSecurityToken */
static UA_INLINE UA_StatusCode UA_ChannelSecurityToken_encodeBinary(const UA_ChannelSecurityToken *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_CHANNELSECURITYTOKEN], dst, offset); }
static UA_INLINE UA_StatusCode UA_ChannelSecurityToken_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ChannelSecurityToken *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_CHANNELSECURITYTOKEN]); }

/* UA_OpenSecureChannelRequest */
static UA_INLINE UA_StatusCode UA_OpenSecureChannelRequest_encodeBinary(const UA_OpenSecureChannelRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_OPENSECURECHANNELREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_OpenSecureChannelRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_OpenSecureChannelRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_OPENSECURECHANNELREQUEST]); }

/* UA_OpenSecureChannelResponse */
static UA_INLINE UA_StatusCode UA_OpenSecureChannelResponse_encodeBinary(const UA_OpenSecureChannelResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_OPENSECURECHANNELRESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_OpenSecureChannelResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_OpenSecureChannelResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_OPENSECURECHANNELRESPONSE]); }

/* UA_CloseSecureChannelRequest */
static UA_INLINE UA_StatusCode UA_CloseSecureChannelRequest_encodeBinary(const UA_CloseSecureChannelRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_CLOSESECURECHANNELREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_CloseSecureChannelRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_CloseSecureChannelRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_CLOSESECURECHANNELREQUEST]); }

/* UA_CloseSecureChannelResponse */
static UA_INLINE UA_StatusCode UA_CloseSecureChannelResponse_encodeBinary(const UA_CloseSecureChannelResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_CLOSESECURECHANNELRESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_CloseSecureChannelResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_CloseSecureChannelResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_CLOSESECURECHANNELRESPONSE]); }

/* UA_SignedSoftwareCertificate */
static UA_INLINE UA_StatusCode UA_SignedSoftwareCertificate_encodeBinary(const UA_SignedSoftwareCertificate *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_SIGNEDSOFTWARECERTIFICATE], dst, offset); }
static UA_INLINE UA_StatusCode UA_SignedSoftwareCertificate_decodeBinary(const UA_ByteString *src, size_t *offset, UA_SignedSoftwareCertificate *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_SIGNEDSOFTWARECERTIFICATE]); }

/* UA_SignatureData */
static UA_INLINE UA_StatusCode UA_SignatureData_encodeBinary(const UA_SignatureData *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_SIGNATUREDATA], dst, offset); }
static UA_INLINE UA_StatusCode UA_SignatureData_decodeBinary(const UA_ByteString *src, size_t *offset, UA_SignatureData *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_SIGNATUREDATA]); }

/* UA_CreateSessionRequest */
static UA_INLINE UA_StatusCode UA_CreateSessionRequest_encodeBinary(const UA_CreateSessionRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_CREATESESSIONREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_CreateSessionRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_CreateSessionRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_CREATESESSIONREQUEST]); }

/* UA_CreateSessionResponse */
static UA_INLINE UA_StatusCode UA_CreateSessionResponse_encodeBinary(const UA_CreateSessionResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_CREATESESSIONRESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_CreateSessionResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_CreateSessionResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_CREATESESSIONRESPONSE]); }

/* UA_UserIdentityToken */
static UA_INLINE UA_StatusCode UA_UserIdentityToken_encodeBinary(const UA_UserIdentityToken *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_USERIDENTITYTOKEN], dst, offset); }
static UA_INLINE UA_StatusCode UA_UserIdentityToken_decodeBinary(const UA_ByteString *src, size_t *offset, UA_UserIdentityToken *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_USERIDENTITYTOKEN]); }

/* UA_AnonymousIdentityToken */
static UA_INLINE UA_StatusCode UA_AnonymousIdentityToken_encodeBinary(const UA_AnonymousIdentityToken *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_ANONYMOUSIDENTITYTOKEN], dst, offset); }
static UA_INLINE UA_StatusCode UA_AnonymousIdentityToken_decodeBinary(const UA_ByteString *src, size_t *offset, UA_AnonymousIdentityToken *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_ANONYMOUSIDENTITYTOKEN]); }

/* UA_UserNameIdentityToken */
static UA_INLINE UA_StatusCode UA_UserNameIdentityToken_encodeBinary(const UA_UserNameIdentityToken *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_USERNAMEIDENTITYTOKEN], dst, offset); }
static UA_INLINE UA_StatusCode UA_UserNameIdentityToken_decodeBinary(const UA_ByteString *src, size_t *offset, UA_UserNameIdentityToken *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_USERNAMEIDENTITYTOKEN]); }

/* UA_ActivateSessionRequest */
static UA_INLINE UA_StatusCode UA_ActivateSessionRequest_encodeBinary(const UA_ActivateSessionRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_ACTIVATESESSIONREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_ActivateSessionRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ActivateSessionRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_ACTIVATESESSIONREQUEST]); }

/* UA_ActivateSessionResponse */
static UA_INLINE UA_StatusCode UA_ActivateSessionResponse_encodeBinary(const UA_ActivateSessionResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_ACTIVATESESSIONRESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_ActivateSessionResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ActivateSessionResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_ACTIVATESESSIONRESPONSE]); }

/* UA_CloseSessionRequest */
static UA_INLINE UA_StatusCode UA_CloseSessionRequest_encodeBinary(const UA_CloseSessionRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_CLOSESESSIONREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_CloseSessionRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_CloseSessionRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_CLOSESESSIONREQUEST]); }

/* UA_CloseSessionResponse */
static UA_INLINE UA_StatusCode UA_CloseSessionResponse_encodeBinary(const UA_CloseSessionResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_CLOSESESSIONRESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_CloseSessionResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_CloseSessionResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_CLOSESESSIONRESPONSE]); }

/* UA_NodeAttributesMask */
static UA_INLINE UA_StatusCode UA_NodeAttributesMask_encodeBinary(const UA_NodeAttributesMask *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_NODEATTRIBUTESMASK], dst, offset); }
static UA_INLINE UA_StatusCode UA_NodeAttributesMask_decodeBinary(const UA_ByteString *src, size_t *offset, UA_NodeAttributesMask *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_NODEATTRIBUTESMASK]); }

/* UA_NodeAttributes */
static UA_INLINE UA_StatusCode UA_NodeAttributes_encodeBinary(const UA_NodeAttributes *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_NODEATTRIBUTES], dst, offset); }
static UA_INLINE UA_StatusCode UA_NodeAttributes_decodeBinary(const UA_ByteString *src, size_t *offset, UA_NodeAttributes *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_NODEATTRIBUTES]); }

/* UA_ObjectAttributes */
static UA_INLINE UA_StatusCode UA_ObjectAttributes_encodeBinary(const UA_ObjectAttributes *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_OBJECTATTRIBUTES], dst, offset); }
static UA_INLINE UA_StatusCode UA_ObjectAttributes_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ObjectAttributes *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_OBJECTATTRIBUTES]); }

/* UA_VariableAttributes */
static UA_INLINE UA_StatusCode UA_VariableAttributes_encodeBinary(const UA_VariableAttributes *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_VARIABLEATTRIBUTES], dst, offset); }
static UA_INLINE UA_StatusCode UA_VariableAttributes_decodeBinary(const UA_ByteString *src, size_t *offset, UA_VariableAttributes *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_VARIABLEATTRIBUTES]); }

/* UA_MethodAttributes */
static UA_INLINE UA_StatusCode UA_MethodAttributes_encodeBinary(const UA_MethodAttributes *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_METHODATTRIBUTES], dst, offset); }
static UA_INLINE UA_StatusCode UA_MethodAttributes_decodeBinary(const UA_ByteString *src, size_t *offset, UA_MethodAttributes *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_METHODATTRIBUTES]); }

/* UA_ObjectTypeAttributes */
static UA_INLINE UA_StatusCode UA_ObjectTypeAttributes_encodeBinary(const UA_ObjectTypeAttributes *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_OBJECTTYPEATTRIBUTES], dst, offset); }
static UA_INLINE UA_StatusCode UA_ObjectTypeAttributes_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ObjectTypeAttributes *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_OBJECTTYPEATTRIBUTES]); }

/* UA_VariableTypeAttributes */
static UA_INLINE UA_StatusCode UA_VariableTypeAttributes_encodeBinary(const UA_VariableTypeAttributes *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_VARIABLETYPEATTRIBUTES], dst, offset); }
static UA_INLINE UA_StatusCode UA_VariableTypeAttributes_decodeBinary(const UA_ByteString *src, size_t *offset, UA_VariableTypeAttributes *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_VARIABLETYPEATTRIBUTES]); }

/* UA_ReferenceTypeAttributes */
static UA_INLINE UA_StatusCode UA_ReferenceTypeAttributes_encodeBinary(const UA_ReferenceTypeAttributes *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_REFERENCETYPEATTRIBUTES], dst, offset); }
static UA_INLINE UA_StatusCode UA_ReferenceTypeAttributes_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ReferenceTypeAttributes *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_REFERENCETYPEATTRIBUTES]); }

/* UA_DataTypeAttributes */
static UA_INLINE UA_StatusCode UA_DataTypeAttributes_encodeBinary(const UA_DataTypeAttributes *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_DATATYPEATTRIBUTES], dst, offset); }
static UA_INLINE UA_StatusCode UA_DataTypeAttributes_decodeBinary(const UA_ByteString *src, size_t *offset, UA_DataTypeAttributes *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_DATATYPEATTRIBUTES]); }

/* UA_ViewAttributes */
static UA_INLINE UA_StatusCode UA_ViewAttributes_encodeBinary(const UA_ViewAttributes *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_VIEWATTRIBUTES], dst, offset); }
static UA_INLINE UA_StatusCode UA_ViewAttributes_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ViewAttributes *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_VIEWATTRIBUTES]); }

/* UA_AddNodesItem */
static UA_INLINE UA_StatusCode UA_AddNodesItem_encodeBinary(const UA_AddNodesItem *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_ADDNODESITEM], dst, offset); }
static UA_INLINE UA_StatusCode UA_AddNodesItem_decodeBinary(const UA_ByteString *src, size_t *offset, UA_AddNodesItem *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_ADDNODESITEM]); }

/* UA_AddNodesResult */
static UA_INLINE UA_StatusCode UA_AddNodesResult_encodeBinary(const UA_AddNodesResult *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_ADDNODESRESULT], dst, offset); }
static UA_INLINE UA_StatusCode UA_AddNodesResult_decodeBinary(const UA_ByteString *src, size_t *offset, UA_AddNodesResult *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_ADDNODESRESULT]); }

/* UA_AddNodesRequest */
static UA_INLINE UA_StatusCode UA_AddNodesRequest_encodeBinary(const UA_AddNodesRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_ADDNODESREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_AddNodesRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_AddNodesRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_ADDNODESREQUEST]); }

/* UA_AddNodesResponse */
static UA_INLINE UA_StatusCode UA_AddNodesResponse_encodeBinary(const UA_AddNodesResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_ADDNODESRESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_AddNodesResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_AddNodesResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_ADDNODESRESPONSE]); }

/* UA_AddReferencesItem */
static UA_INLINE UA_StatusCode UA_AddReferencesItem_encodeBinary(const UA_AddReferencesItem *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_ADDREFERENCESITEM], dst, offset); }
static UA_INLINE UA_StatusCode UA_AddReferencesItem_decodeBinary(const UA_ByteString *src, size_t *offset, UA_AddReferencesItem *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_ADDREFERENCESITEM]); }

/* UA_AddReferencesRequest */
static UA_INLINE UA_StatusCode UA_AddReferencesRequest_encodeBinary(const UA_AddReferencesRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_ADDREFERENCESREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_AddReferencesRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_AddReferencesRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_ADDREFERENCESREQUEST]); }

/* UA_AddReferencesResponse */
static UA_INLINE UA_StatusCode UA_AddReferencesResponse_encodeBinary(const UA_AddReferencesResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_ADDREFERENCESRESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_AddReferencesResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_AddReferencesResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_ADDREFERENCESRESPONSE]); }

/* UA_DeleteNodesItem */
static UA_INLINE UA_StatusCode UA_DeleteNodesItem_encodeBinary(const UA_DeleteNodesItem *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_DELETENODESITEM], dst, offset); }
static UA_INLINE UA_StatusCode UA_DeleteNodesItem_decodeBinary(const UA_ByteString *src, size_t *offset, UA_DeleteNodesItem *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_DELETENODESITEM]); }

/* UA_DeleteNodesRequest */
static UA_INLINE UA_StatusCode UA_DeleteNodesRequest_encodeBinary(const UA_DeleteNodesRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_DELETENODESREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_DeleteNodesRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_DeleteNodesRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_DELETENODESREQUEST]); }

/* UA_DeleteNodesResponse */
static UA_INLINE UA_StatusCode UA_DeleteNodesResponse_encodeBinary(const UA_DeleteNodesResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_DELETENODESRESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_DeleteNodesResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_DeleteNodesResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_DELETENODESRESPONSE]); }

/* UA_DeleteReferencesItem */
static UA_INLINE UA_StatusCode UA_DeleteReferencesItem_encodeBinary(const UA_DeleteReferencesItem *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_DELETEREFERENCESITEM], dst, offset); }
static UA_INLINE UA_StatusCode UA_DeleteReferencesItem_decodeBinary(const UA_ByteString *src, size_t *offset, UA_DeleteReferencesItem *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_DELETEREFERENCESITEM]); }

/* UA_DeleteReferencesRequest */
static UA_INLINE UA_StatusCode UA_DeleteReferencesRequest_encodeBinary(const UA_DeleteReferencesRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_DELETEREFERENCESREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_DeleteReferencesRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_DeleteReferencesRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_DELETEREFERENCESREQUEST]); }

/* UA_DeleteReferencesResponse */
static UA_INLINE UA_StatusCode UA_DeleteReferencesResponse_encodeBinary(const UA_DeleteReferencesResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_DELETEREFERENCESRESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_DeleteReferencesResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_DeleteReferencesResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_DELETEREFERENCESRESPONSE]); }

/* UA_BrowseDirection */
static UA_INLINE UA_StatusCode UA_BrowseDirection_encodeBinary(const UA_BrowseDirection *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_BROWSEDIRECTION], dst, offset); }
static UA_INLINE UA_StatusCode UA_BrowseDirection_decodeBinary(const UA_ByteString *src, size_t *offset, UA_BrowseDirection *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_BROWSEDIRECTION]); }

/* UA_ViewDescription */
static UA_INLINE UA_StatusCode UA_ViewDescription_encodeBinary(const UA_ViewDescription *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_VIEWDESCRIPTION], dst, offset); }
static UA_INLINE UA_StatusCode UA_ViewDescription_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ViewDescription *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_VIEWDESCRIPTION]); }

/* UA_BrowseDescription */
static UA_INLINE UA_StatusCode UA_BrowseDescription_encodeBinary(const UA_BrowseDescription *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_BROWSEDESCRIPTION], dst, offset); }
static UA_INLINE UA_StatusCode UA_BrowseDescription_decodeBinary(const UA_ByteString *src, size_t *offset, UA_BrowseDescription *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_BROWSEDESCRIPTION]); }

/* UA_BrowseResultMask */
static UA_INLINE UA_StatusCode UA_BrowseResultMask_encodeBinary(const UA_BrowseResultMask *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_BROWSERESULTMASK], dst, offset); }
static UA_INLINE UA_StatusCode UA_BrowseResultMask_decodeBinary(const UA_ByteString *src, size_t *offset, UA_BrowseResultMask *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_BROWSERESULTMASK]); }

/* UA_ReferenceDescription */
static UA_INLINE UA_StatusCode UA_ReferenceDescription_encodeBinary(const UA_ReferenceDescription *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_REFERENCEDESCRIPTION], dst, offset); }
static UA_INLINE UA_StatusCode UA_ReferenceDescription_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ReferenceDescription *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_REFERENCEDESCRIPTION]); }

/* UA_BrowseResult */
static UA_INLINE UA_StatusCode UA_BrowseResult_encodeBinary(const UA_BrowseResult *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_BROWSERESULT], dst, offset); }
static UA_INLINE UA_StatusCode UA_BrowseResult_decodeBinary(const UA_ByteString *src, size_t *offset, UA_BrowseResult *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_BROWSERESULT]); }

/* UA_BrowseRequest */
static UA_INLINE UA_StatusCode UA_BrowseRequest_encodeBinary(const UA_BrowseRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_BROWSEREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_BrowseRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_BrowseRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_BROWSEREQUEST]); }

/* UA_BrowseResponse */
static UA_INLINE UA_StatusCode UA_BrowseResponse_encodeBinary(const UA_BrowseResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_BROWSERESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_BrowseResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_BrowseResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_BROWSERESPONSE]); }

/* UA_BrowseNextRequest */
static UA_INLINE UA_StatusCode UA_BrowseNextRequest_encodeBinary(const UA_BrowseNextRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_BROWSENEXTREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_BrowseNextRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_BrowseNextRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_BROWSENEXTREQUEST]); }

/* UA_BrowseNextResponse */
static UA_INLINE UA_StatusCode UA_BrowseNextResponse_encodeBinary(const UA_BrowseNextResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_BROWSENEXTRESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_BrowseNextResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_BrowseNextResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_BROWSENEXTRESPONSE]); }

/* UA_RelativePathElement */
static UA_INLINE UA_StatusCode UA_RelativePathElement_encodeBinary(const UA_RelativePathElement *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_RELATIVEPATHELEMENT], dst, offset); }
static UA_INLINE UA_StatusCode UA_RelativePathElement_decodeBinary(const UA_ByteString *src, size_t *offset, UA_RelativePathElement *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_RELATIVEPATHELEMENT]); }

/* UA_RelativePath */
static UA_INLINE UA_StatusCode UA_RelativePath_encodeBinary(const UA_RelativePath *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_RELATIVEPATH], dst, offset); }
static UA_INLINE UA_StatusCode UA_RelativePath_decodeBinary(const UA_ByteString *src, size_t *offset, UA_RelativePath *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_RELATIVEPATH]); }

/* UA_BrowsePath */
static UA_INLINE UA_StatusCode UA_BrowsePath_encodeBinary(const UA_BrowsePath *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_BROWSEPATH], dst, offset); }
static UA_INLINE UA_StatusCode UA_BrowsePath_decodeBinary(const UA_ByteString *src, size_t *offset, UA_BrowsePath *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_BROWSEPATH]); }

/* UA_BrowsePathTarget */
static UA_INLINE UA_StatusCode UA_BrowsePathTarget_encodeBinary(const UA_BrowsePathTarget *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_BROWSEPATHTARGET], dst, offset); }
static UA_INLINE UA_StatusCode UA_BrowsePathTarget_decodeBinary(const UA_ByteString *src, size_t *offset, UA_BrowsePathTarget *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_BROWSEPATHTARGET]); }

/* UA_BrowsePathResult */
static UA_INLINE UA_StatusCode UA_BrowsePathResult_encodeBinary(const UA_BrowsePathResult *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_BROWSEPATHRESULT], dst, offset); }
static UA_INLINE UA_StatusCode UA_BrowsePathResult_decodeBinary(const UA_ByteString *src, size_t *offset, UA_BrowsePathResult *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_BROWSEPATHRESULT]); }

/* UA_TranslateBrowsePathsToNodeIdsRequest */
static UA_INLINE UA_StatusCode UA_TranslateBrowsePathsToNodeIdsRequest_encodeBinary(const UA_TranslateBrowsePathsToNodeIdsRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_TRANSLATEBROWSEPATHSTONODEIDSREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_TranslateBrowsePathsToNodeIdsRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_TranslateBrowsePathsToNodeIdsRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_TRANSLATEBROWSEPATHSTONODEIDSREQUEST]); }

/* UA_TranslateBrowsePathsToNodeIdsResponse */
static UA_INLINE UA_StatusCode UA_TranslateBrowsePathsToNodeIdsResponse_encodeBinary(const UA_TranslateBrowsePathsToNodeIdsResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_TRANSLATEBROWSEPATHSTONODEIDSRESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_TranslateBrowsePathsToNodeIdsResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_TranslateBrowsePathsToNodeIdsResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_TRANSLATEBROWSEPATHSTONODEIDSRESPONSE]); }

/* UA_RegisterNodesRequest */
static UA_INLINE UA_StatusCode UA_RegisterNodesRequest_encodeBinary(const UA_RegisterNodesRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_REGISTERNODESREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_RegisterNodesRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_RegisterNodesRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_REGISTERNODESREQUEST]); }

/* UA_RegisterNodesResponse */
static UA_INLINE UA_StatusCode UA_RegisterNodesResponse_encodeBinary(const UA_RegisterNodesResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_REGISTERNODESRESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_RegisterNodesResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_RegisterNodesResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_REGISTERNODESRESPONSE]); }

/* UA_UnregisterNodesRequest */
static UA_INLINE UA_StatusCode UA_UnregisterNodesRequest_encodeBinary(const UA_UnregisterNodesRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_UNREGISTERNODESREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_UnregisterNodesRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_UnregisterNodesRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_UNREGISTERNODESREQUEST]); }

/* UA_UnregisterNodesResponse */
static UA_INLINE UA_StatusCode UA_UnregisterNodesResponse_encodeBinary(const UA_UnregisterNodesResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_UNREGISTERNODESRESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_UnregisterNodesResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_UnregisterNodesResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_UNREGISTERNODESRESPONSE]); }

/* UA_QueryDataDescription */
static UA_INLINE UA_StatusCode UA_QueryDataDescription_encodeBinary(const UA_QueryDataDescription *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_QUERYDATADESCRIPTION], dst, offset); }
static UA_INLINE UA_StatusCode UA_QueryDataDescription_decodeBinary(const UA_ByteString *src, size_t *offset, UA_QueryDataDescription *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_QUERYDATADESCRIPTION]); }

/* UA_NodeTypeDescription */
static UA_INLINE UA_StatusCode UA_NodeTypeDescription_encodeBinary(const UA_NodeTypeDescription *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_NODETYPEDESCRIPTION], dst, offset); }
static UA_INLINE UA_StatusCode UA_NodeTypeDescription_decodeBinary(const UA_ByteString *src, size_t *offset, UA_NodeTypeDescription *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_NODETYPEDESCRIPTION]); }

/* UA_FilterOperator */
static UA_INLINE UA_StatusCode UA_FilterOperator_encodeBinary(const UA_FilterOperator *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_FILTEROPERATOR], dst, offset); }
static UA_INLINE UA_StatusCode UA_FilterOperator_decodeBinary(const UA_ByteString *src, size_t *offset, UA_FilterOperator *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_FILTEROPERATOR]); }

/* UA_QueryDataSet */
static UA_INLINE UA_StatusCode UA_QueryDataSet_encodeBinary(const UA_QueryDataSet *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_QUERYDATASET], dst, offset); }
static UA_INLINE UA_StatusCode UA_QueryDataSet_decodeBinary(const UA_ByteString *src, size_t *offset, UA_QueryDataSet *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_QUERYDATASET]); }

/* UA_ContentFilterElement */
static UA_INLINE UA_StatusCode UA_ContentFilterElement_encodeBinary(const UA_ContentFilterElement *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_CONTENTFILTERELEMENT], dst, offset); }
static UA_INLINE UA_StatusCode UA_ContentFilterElement_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ContentFilterElement *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_CONTENTFILTERELEMENT]); }

/* UA_ContentFilter */
static UA_INLINE UA_StatusCode UA_ContentFilter_encodeBinary(const UA_ContentFilter *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_CONTENTFILTER], dst, offset); }
static UA_INLINE UA_StatusCode UA_ContentFilter_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ContentFilter *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_CONTENTFILTER]); }

/* UA_ContentFilterElementResult */
static UA_INLINE UA_StatusCode UA_ContentFilterElementResult_encodeBinary(const UA_ContentFilterElementResult *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_CONTENTFILTERELEMENTRESULT], dst, offset); }
static UA_INLINE UA_StatusCode UA_ContentFilterElementResult_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ContentFilterElementResult *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_CONTENTFILTERELEMENTRESULT]); }

/* UA_ContentFilterResult */
static UA_INLINE UA_StatusCode UA_ContentFilterResult_encodeBinary(const UA_ContentFilterResult *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_CONTENTFILTERRESULT], dst, offset); }
static UA_INLINE UA_StatusCode UA_ContentFilterResult_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ContentFilterResult *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_CONTENTFILTERRESULT]); }

/* UA_ParsingResult */
static UA_INLINE UA_StatusCode UA_ParsingResult_encodeBinary(const UA_ParsingResult *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_PARSINGRESULT], dst, offset); }
static UA_INLINE UA_StatusCode UA_ParsingResult_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ParsingResult *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_PARSINGRESULT]); }

/* UA_QueryFirstRequest */
static UA_INLINE UA_StatusCode UA_QueryFirstRequest_encodeBinary(const UA_QueryFirstRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_QUERYFIRSTREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_QueryFirstRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_QueryFirstRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_QUERYFIRSTREQUEST]); }

/* UA_QueryFirstResponse */
static UA_INLINE UA_StatusCode UA_QueryFirstResponse_encodeBinary(const UA_QueryFirstResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_QUERYFIRSTRESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_QueryFirstResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_QueryFirstResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_QUERYFIRSTRESPONSE]); }

/* UA_QueryNextRequest */
static UA_INLINE UA_StatusCode UA_QueryNextRequest_encodeBinary(const UA_QueryNextRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_QUERYNEXTREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_QueryNextRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_QueryNextRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_QUERYNEXTREQUEST]); }

/* UA_QueryNextResponse */
static UA_INLINE UA_StatusCode UA_QueryNextResponse_encodeBinary(const UA_QueryNextResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_QUERYNEXTRESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_QueryNextResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_QueryNextResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_QUERYNEXTRESPONSE]); }

/* UA_TimestampsToReturn */
static UA_INLINE UA_StatusCode UA_TimestampsToReturn_encodeBinary(const UA_TimestampsToReturn *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_TIMESTAMPSTORETURN], dst, offset); }
static UA_INLINE UA_StatusCode UA_TimestampsToReturn_decodeBinary(const UA_ByteString *src, size_t *offset, UA_TimestampsToReturn *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_TIMESTAMPSTORETURN]); }

/* UA_ReadValueId */
static UA_INLINE UA_StatusCode UA_ReadValueId_encodeBinary(const UA_ReadValueId *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_READVALUEID], dst, offset); }
static UA_INLINE UA_StatusCode UA_ReadValueId_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ReadValueId *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_READVALUEID]); }

/* UA_ReadRequest */
static UA_INLINE UA_StatusCode UA_ReadRequest_encodeBinary(const UA_ReadRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_READREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_ReadRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ReadRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_READREQUEST]); }

/* UA_ReadResponse */
static UA_INLINE UA_StatusCode UA_ReadResponse_encodeBinary(const UA_ReadResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_READRESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_ReadResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ReadResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_READRESPONSE]); }

/* UA_WriteValue */
static UA_INLINE UA_StatusCode UA_WriteValue_encodeBinary(const UA_WriteValue *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_WRITEVALUE], dst, offset); }
static UA_INLINE UA_StatusCode UA_WriteValue_decodeBinary(const UA_ByteString *src, size_t *offset, UA_WriteValue *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_WRITEVALUE]); }

/* UA_WriteRequest */
static UA_INLINE UA_StatusCode UA_WriteRequest_encodeBinary(const UA_WriteRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_WRITEREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_WriteRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_WriteRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_WRITEREQUEST]); }

/* UA_WriteResponse */
static UA_INLINE UA_StatusCode UA_WriteResponse_encodeBinary(const UA_WriteResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_WRITERESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_WriteResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_WriteResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_WRITERESPONSE]); }

/* UA_CallMethodRequest */
static UA_INLINE UA_StatusCode UA_CallMethodRequest_encodeBinary(const UA_CallMethodRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_CALLMETHODREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_CallMethodRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_CallMethodRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_CALLMETHODREQUEST]); }

/* UA_CallMethodResult */
static UA_INLINE UA_StatusCode UA_CallMethodResult_encodeBinary(const UA_CallMethodResult *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_CALLMETHODRESULT], dst, offset); }
static UA_INLINE UA_StatusCode UA_CallMethodResult_decodeBinary(const UA_ByteString *src, size_t *offset, UA_CallMethodResult *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_CALLMETHODRESULT]); }

/* UA_CallRequest */
static UA_INLINE UA_StatusCode UA_CallRequest_encodeBinary(const UA_CallRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_CALLREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_CallRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_CallRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_CALLREQUEST]); }

/* UA_CallResponse */
static UA_INLINE UA_StatusCode UA_CallResponse_encodeBinary(const UA_CallResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_CALLRESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_CallResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_CallResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_CALLRESPONSE]); }

/* UA_MonitoringMode */
static UA_INLINE UA_StatusCode UA_MonitoringMode_encodeBinary(const UA_MonitoringMode *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_MONITORINGMODE], dst, offset); }
static UA_INLINE UA_StatusCode UA_MonitoringMode_decodeBinary(const UA_ByteString *src, size_t *offset, UA_MonitoringMode *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_MONITORINGMODE]); }

/* UA_MonitoringParameters */
static UA_INLINE UA_StatusCode UA_MonitoringParameters_encodeBinary(const UA_MonitoringParameters *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_MONITORINGPARAMETERS], dst, offset); }
static UA_INLINE UA_StatusCode UA_MonitoringParameters_decodeBinary(const UA_ByteString *src, size_t *offset, UA_MonitoringParameters *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_MONITORINGPARAMETERS]); }

/* UA_MonitoredItemCreateRequest */
static UA_INLINE UA_StatusCode UA_MonitoredItemCreateRequest_encodeBinary(const UA_MonitoredItemCreateRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_MONITOREDITEMCREATEREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_MonitoredItemCreateRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_MonitoredItemCreateRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_MONITOREDITEMCREATEREQUEST]); }

/* UA_MonitoredItemCreateResult */
static UA_INLINE UA_StatusCode UA_MonitoredItemCreateResult_encodeBinary(const UA_MonitoredItemCreateResult *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_MONITOREDITEMCREATERESULT], dst, offset); }
static UA_INLINE UA_StatusCode UA_MonitoredItemCreateResult_decodeBinary(const UA_ByteString *src, size_t *offset, UA_MonitoredItemCreateResult *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_MONITOREDITEMCREATERESULT]); }

/* UA_CreateMonitoredItemsRequest */
static UA_INLINE UA_StatusCode UA_CreateMonitoredItemsRequest_encodeBinary(const UA_CreateMonitoredItemsRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_CREATEMONITOREDITEMSREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_CreateMonitoredItemsRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_CreateMonitoredItemsRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_CREATEMONITOREDITEMSREQUEST]); }

/* UA_CreateMonitoredItemsResponse */
static UA_INLINE UA_StatusCode UA_CreateMonitoredItemsResponse_encodeBinary(const UA_CreateMonitoredItemsResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_CREATEMONITOREDITEMSRESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_CreateMonitoredItemsResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_CreateMonitoredItemsResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_CREATEMONITOREDITEMSRESPONSE]); }

/* UA_DeleteMonitoredItemsRequest */
static UA_INLINE UA_StatusCode UA_DeleteMonitoredItemsRequest_encodeBinary(const UA_DeleteMonitoredItemsRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_DELETEMONITOREDITEMSREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_DeleteMonitoredItemsRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_DeleteMonitoredItemsRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_DELETEMONITOREDITEMSREQUEST]); }

/* UA_DeleteMonitoredItemsResponse */
static UA_INLINE UA_StatusCode UA_DeleteMonitoredItemsResponse_encodeBinary(const UA_DeleteMonitoredItemsResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_DELETEMONITOREDITEMSRESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_DeleteMonitoredItemsResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_DeleteMonitoredItemsResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_DELETEMONITOREDITEMSRESPONSE]); }

/* UA_CreateSubscriptionRequest */
static UA_INLINE UA_StatusCode UA_CreateSubscriptionRequest_encodeBinary(const UA_CreateSubscriptionRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_CREATESUBSCRIPTIONREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_CreateSubscriptionRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_CreateSubscriptionRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_CREATESUBSCRIPTIONREQUEST]); }

/* UA_CreateSubscriptionResponse */
static UA_INLINE UA_StatusCode UA_CreateSubscriptionResponse_encodeBinary(const UA_CreateSubscriptionResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_CREATESUBSCRIPTIONRESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_CreateSubscriptionResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_CreateSubscriptionResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_CREATESUBSCRIPTIONRESPONSE]); }

/* UA_ModifySubscriptionRequest */
static UA_INLINE UA_StatusCode UA_ModifySubscriptionRequest_encodeBinary(const UA_ModifySubscriptionRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_MODIFYSUBSCRIPTIONREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_ModifySubscriptionRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ModifySubscriptionRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_MODIFYSUBSCRIPTIONREQUEST]); }

/* UA_ModifySubscriptionResponse */
static UA_INLINE UA_StatusCode UA_ModifySubscriptionResponse_encodeBinary(const UA_ModifySubscriptionResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_MODIFYSUBSCRIPTIONRESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_ModifySubscriptionResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ModifySubscriptionResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_MODIFYSUBSCRIPTIONRESPONSE]); }

/* UA_SetPublishingModeRequest */
static UA_INLINE UA_StatusCode UA_SetPublishingModeRequest_encodeBinary(const UA_SetPublishingModeRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_SETPUBLISHINGMODEREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_SetPublishingModeRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_SetPublishingModeRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_SETPUBLISHINGMODEREQUEST]); }

/* UA_SetPublishingModeResponse */
static UA_INLINE UA_StatusCode UA_SetPublishingModeResponse_encodeBinary(const UA_SetPublishingModeResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_SETPUBLISHINGMODERESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_SetPublishingModeResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_SetPublishingModeResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_SETPUBLISHINGMODERESPONSE]); }

/* UA_NotificationMessage */
static UA_INLINE UA_StatusCode UA_NotificationMessage_encodeBinary(const UA_NotificationMessage *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_NOTIFICATIONMESSAGE], dst, offset); }
static UA_INLINE UA_StatusCode UA_NotificationMessage_decodeBinary(const UA_ByteString *src, size_t *offset, UA_NotificationMessage *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_NOTIFICATIONMESSAGE]); }

/* UA_MonitoredItemNotification */
static UA_INLINE UA_StatusCode UA_MonitoredItemNotification_encodeBinary(const UA_MonitoredItemNotification *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_MONITOREDITEMNOTIFICATION], dst, offset); }
static UA_INLINE UA_StatusCode UA_MonitoredItemNotification_decodeBinary(const UA_ByteString *src, size_t *offset, UA_MonitoredItemNotification *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_MONITOREDITEMNOTIFICATION]); }

/* UA_SubscriptionAcknowledgement */
static UA_INLINE UA_StatusCode UA_SubscriptionAcknowledgement_encodeBinary(const UA_SubscriptionAcknowledgement *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_SUBSCRIPTIONACKNOWLEDGEMENT], dst, offset); }
static UA_INLINE UA_StatusCode UA_SubscriptionAcknowledgement_decodeBinary(const UA_ByteString *src, size_t *offset, UA_SubscriptionAcknowledgement *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_SUBSCRIPTIONACKNOWLEDGEMENT]); }

/* UA_PublishRequest */
static UA_INLINE UA_StatusCode UA_PublishRequest_encodeBinary(const UA_PublishRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_PUBLISHREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_PublishRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_PublishRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_PUBLISHREQUEST]); }

/* UA_PublishResponse */
static UA_INLINE UA_StatusCode UA_PublishResponse_encodeBinary(const UA_PublishResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_PUBLISHRESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_PublishResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_PublishResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_PUBLISHRESPONSE]); }

/* UA_RepublishRequest */
static UA_INLINE UA_StatusCode UA_RepublishRequest_encodeBinary(const UA_RepublishRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_REPUBLISHREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_RepublishRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_RepublishRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_REPUBLISHREQUEST]); }

/* UA_RepublishResponse */
static UA_INLINE UA_StatusCode UA_RepublishResponse_encodeBinary(const UA_RepublishResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_REPUBLISHRESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_RepublishResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_RepublishResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_REPUBLISHRESPONSE]); }

/* UA_DeleteSubscriptionsRequest */
static UA_INLINE UA_StatusCode UA_DeleteSubscriptionsRequest_encodeBinary(const UA_DeleteSubscriptionsRequest *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_DELETESUBSCRIPTIONSREQUEST], dst, offset); }
static UA_INLINE UA_StatusCode UA_DeleteSubscriptionsRequest_decodeBinary(const UA_ByteString *src, size_t *offset, UA_DeleteSubscriptionsRequest *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_DELETESUBSCRIPTIONSREQUEST]); }

/* UA_DeleteSubscriptionsResponse */
static UA_INLINE UA_StatusCode UA_DeleteSubscriptionsResponse_encodeBinary(const UA_DeleteSubscriptionsResponse *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_DELETESUBSCRIPTIONSRESPONSE], dst, offset); }
static UA_INLINE UA_StatusCode UA_DeleteSubscriptionsResponse_decodeBinary(const UA_ByteString *src, size_t *offset, UA_DeleteSubscriptionsResponse *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_DELETESUBSCRIPTIONSRESPONSE]); }

/* UA_BuildInfo */
static UA_INLINE UA_StatusCode UA_BuildInfo_encodeBinary(const UA_BuildInfo *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_BUILDINFO], dst, offset); }
static UA_INLINE UA_StatusCode UA_BuildInfo_decodeBinary(const UA_ByteString *src, size_t *offset, UA_BuildInfo *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_BUILDINFO]); }

/* UA_ServerState */
static UA_INLINE UA_StatusCode UA_ServerState_encodeBinary(const UA_ServerState *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_SERVERSTATE], dst, offset); }
static UA_INLINE UA_StatusCode UA_ServerState_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ServerState *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_SERVERSTATE]); }

/* UA_ServerStatusDataType */
static UA_INLINE UA_StatusCode UA_ServerStatusDataType_encodeBinary(const UA_ServerStatusDataType *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_SERVERSTATUSDATATYPE], dst, offset); }
static UA_INLINE UA_StatusCode UA_ServerStatusDataType_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ServerStatusDataType *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_SERVERSTATUSDATATYPE]); }

/* UA_DataChangeNotification */
static UA_INLINE UA_StatusCode UA_DataChangeNotification_encodeBinary(const UA_DataChangeNotification *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TYPES[UA_TYPES_DATACHANGENOTIFICATION], dst, offset); }
static UA_INLINE UA_StatusCode UA_DataChangeNotification_decodeBinary(const UA_ByteString *src, size_t *offset, UA_DataChangeNotification *dst) { return UA_decodeBinary(src, offset, dst, &UA_TYPES[UA_TYPES_DATACHANGENOTIFICATION]); }
