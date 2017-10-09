/* Generated from Custom.Opc.Ua.Transport.bsd with script /home/ichrispa/work/svn/working_copies/open62541/tools/generate_datatypes.py
 * on host adriana by user ichrispa at 2016-04-14 07:26:16 */
 
#include "ua_types_encoding_binary.h"
#include "ua_transport_generated.h"

/* UA_MessageTypeAndFinal */
static UA_INLINE UA_StatusCode UA_MessageTypeAndFinal_encodeBinary(const UA_MessageTypeAndFinal *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TRANSPORT[UA_TRANSPORT_MESSAGETYPEANDFINAL], dst, offset); }
static UA_INLINE UA_StatusCode UA_MessageTypeAndFinal_decodeBinary(const UA_ByteString *src, size_t *offset, UA_MessageTypeAndFinal *dst) { return UA_decodeBinary(src, offset, dst, &UA_TRANSPORT[UA_TRANSPORT_MESSAGETYPEANDFINAL]); }

/* UA_TcpMessageHeader */
static UA_INLINE UA_StatusCode UA_TcpMessageHeader_encodeBinary(const UA_TcpMessageHeader *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TRANSPORT[UA_TRANSPORT_TCPMESSAGEHEADER], dst, offset); }
static UA_INLINE UA_StatusCode UA_TcpMessageHeader_decodeBinary(const UA_ByteString *src, size_t *offset, UA_TcpMessageHeader *dst) { return UA_decodeBinary(src, offset, dst, &UA_TRANSPORT[UA_TRANSPORT_TCPMESSAGEHEADER]); }

/* UA_TcpHelloMessage */
static UA_INLINE UA_StatusCode UA_TcpHelloMessage_encodeBinary(const UA_TcpHelloMessage *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TRANSPORT[UA_TRANSPORT_TCPHELLOMESSAGE], dst, offset); }
static UA_INLINE UA_StatusCode UA_TcpHelloMessage_decodeBinary(const UA_ByteString *src, size_t *offset, UA_TcpHelloMessage *dst) { return UA_decodeBinary(src, offset, dst, &UA_TRANSPORT[UA_TRANSPORT_TCPHELLOMESSAGE]); }

/* UA_TcpAcknowledgeMessage */
static UA_INLINE UA_StatusCode UA_TcpAcknowledgeMessage_encodeBinary(const UA_TcpAcknowledgeMessage *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TRANSPORT[UA_TRANSPORT_TCPACKNOWLEDGEMESSAGE], dst, offset); }
static UA_INLINE UA_StatusCode UA_TcpAcknowledgeMessage_decodeBinary(const UA_ByteString *src, size_t *offset, UA_TcpAcknowledgeMessage *dst) { return UA_decodeBinary(src, offset, dst, &UA_TRANSPORT[UA_TRANSPORT_TCPACKNOWLEDGEMESSAGE]); }

/* UA_SecureConversationMessageHeader */
static UA_INLINE UA_StatusCode UA_SecureConversationMessageHeader_encodeBinary(const UA_SecureConversationMessageHeader *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TRANSPORT[UA_TRANSPORT_SECURECONVERSATIONMESSAGEHEADER], dst, offset); }
static UA_INLINE UA_StatusCode UA_SecureConversationMessageHeader_decodeBinary(const UA_ByteString *src, size_t *offset, UA_SecureConversationMessageHeader *dst) { return UA_decodeBinary(src, offset, dst, &UA_TRANSPORT[UA_TRANSPORT_SECURECONVERSATIONMESSAGEHEADER]); }

/* UA_AsymmetricAlgorithmSecurityHeader */
static UA_INLINE UA_StatusCode UA_AsymmetricAlgorithmSecurityHeader_encodeBinary(const UA_AsymmetricAlgorithmSecurityHeader *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TRANSPORT[UA_TRANSPORT_ASYMMETRICALGORITHMSECURITYHEADER], dst, offset); }
static UA_INLINE UA_StatusCode UA_AsymmetricAlgorithmSecurityHeader_decodeBinary(const UA_ByteString *src, size_t *offset, UA_AsymmetricAlgorithmSecurityHeader *dst) { return UA_decodeBinary(src, offset, dst, &UA_TRANSPORT[UA_TRANSPORT_ASYMMETRICALGORITHMSECURITYHEADER]); }

/* UA_SymmetricAlgorithmSecurityHeader */
static UA_INLINE UA_StatusCode UA_SymmetricAlgorithmSecurityHeader_encodeBinary(const UA_SymmetricAlgorithmSecurityHeader *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TRANSPORT[UA_TRANSPORT_SYMMETRICALGORITHMSECURITYHEADER], dst, offset); }
static UA_INLINE UA_StatusCode UA_SymmetricAlgorithmSecurityHeader_decodeBinary(const UA_ByteString *src, size_t *offset, UA_SymmetricAlgorithmSecurityHeader *dst) { return UA_decodeBinary(src, offset, dst, &UA_TRANSPORT[UA_TRANSPORT_SYMMETRICALGORITHMSECURITYHEADER]); }

/* UA_SequenceHeader */
static UA_INLINE UA_StatusCode UA_SequenceHeader_encodeBinary(const UA_SequenceHeader *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TRANSPORT[UA_TRANSPORT_SEQUENCEHEADER], dst, offset); }
static UA_INLINE UA_StatusCode UA_SequenceHeader_decodeBinary(const UA_ByteString *src, size_t *offset, UA_SequenceHeader *dst) { return UA_decodeBinary(src, offset, dst, &UA_TRANSPORT[UA_TRANSPORT_SEQUENCEHEADER]); }

/* UA_SecureConversationMessageFooter */
static UA_INLINE UA_StatusCode UA_SecureConversationMessageFooter_encodeBinary(const UA_SecureConversationMessageFooter *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TRANSPORT[UA_TRANSPORT_SECURECONVERSATIONMESSAGEFOOTER], dst, offset); }
static UA_INLINE UA_StatusCode UA_SecureConversationMessageFooter_decodeBinary(const UA_ByteString *src, size_t *offset, UA_SecureConversationMessageFooter *dst) { return UA_decodeBinary(src, offset, dst, &UA_TRANSPORT[UA_TRANSPORT_SECURECONVERSATIONMESSAGEFOOTER]); }

/* UA_SecureConversationMessageAbortBody */
static UA_INLINE UA_StatusCode UA_SecureConversationMessageAbortBody_encodeBinary(const UA_SecureConversationMessageAbortBody *src, UA_ByteString *dst, size_t *offset) { return UA_encodeBinary(src, &UA_TRANSPORT[UA_TRANSPORT_SECURECONVERSATIONMESSAGEABORTBODY], dst, offset); }
static UA_INLINE UA_StatusCode UA_SecureConversationMessageAbortBody_decodeBinary(const UA_ByteString *src, size_t *offset, UA_SecureConversationMessageAbortBody *dst) { return UA_decodeBinary(src, offset, dst, &UA_TRANSPORT[UA_TRANSPORT_SECURECONVERSATIONMESSAGEABORTBODY]); }
