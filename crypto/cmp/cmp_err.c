/*
 * Generated by util/mkerr.pl DO NOT EDIT
 * Copyright 1995-2019 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <openssl/err.h>
#include <openssl/cmperr.h>

#ifndef OPENSSL_NO_ERR

static const ERR_STRING_DATA CMP_str_reasons[] = {
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ALGORITHM_NOT_SUPPORTED),
    "algorithm not supported"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_BAD_CHECKAFTER_IN_POLLREP),
    "bad checkafter in pollrep"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_BAD_REQUEST_ID), "bad request id"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_CERTID_NOT_FOUND), "certid not found"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_CERTIFICATE_NOT_ACCEPTED),
    "certificate not accepted"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_CERTIFICATE_NOT_FOUND),
    "certificate not found"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_CERTREQMSG_NOT_FOUND),
    "certreqmsg not found"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_CERTRESPONSE_NOT_FOUND),
    "certresponse not found"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_CERT_AND_KEY_DO_NOT_MATCH),
    "cert and key do not match"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_CONNECT_TIMEOUT), "connect timeout"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_CP_NOT_RECEIVED), "cp not received"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ENCOUNTERED_KEYUPDATEWARNING),
    "encountered keyupdatewarning"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ENCOUNTERED_UNSUPPORTED_PKISTATUS),
    "encountered unsupported pkistatus"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ENCOUNTERED_WAITING),
    "encountered waiting"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_CALCULATING_PROTECTION),
    "error calculating protection"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_CONNECTING), "error connecting"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_CREATING_CERTCONF),
    "error creating certconf"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_CREATING_CERTREP),
    "error creating certrep"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_CREATING_CR), "error creating cr"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_CREATING_ERROR),
    "error creating error"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_CREATING_GENM),
    "error creating genm"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_CREATING_GENP),
    "error creating genp"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_CREATING_IR), "error creating ir"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_CREATING_KUR), "error creating kur"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_CREATING_P10CR),
    "error creating p10cr"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_CREATING_PKICONF),
    "error creating pkiconf"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_CREATING_POLLREP),
    "error creating pollrep"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_CREATING_POLLREQ),
    "error creating pollreq"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_CREATING_RP), "error creating rp"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_CREATING_RR), "error creating rr"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_DECODING_MESSAGE),
    "error decoding message"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_PARSING_PKISTATUS),
    "error parsing pkistatus"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_PROCESSING_CERTREQ),
    "error processing certreq"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_PROCESSING_MSG),
    "error processing msg"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_PROTECTING_MESSAGE),
    "error protecting message"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_PUSHING_GENERALINFO_ITEM),
    "error pushing generalinfo item"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_PUSHING_GENERALINFO_ITEMS),
    "error pushing generalinfo items"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_SENDING_REQUEST),
    "error sending request"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_SETTING_CERTHASH),
    "error setting certhash"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_TRANSFERRING_IN),
    "error transferring in"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_TRANSFERRING_OUT),
    "error transferring out"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_ERROR_VALIDATING_PROTECTION),
    "error validating protection"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_FAILED_EXTRACTING_PUBKEY),
    "failed extracting pubkey"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_FAILED_TO_RECEIVE_PKIMESSAGE),
    "failed to receive pkimessage"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_FAILED_TO_SEND_REQUEST),
    "failed to send request"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_FAILURE_OBTAINING_RANDOM),
    "failure obtaining random"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_FAIL_INFO_OUT_OF_RANGE),
    "fail info out of range"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_GENP_NOT_RECEIVED), "genp not received"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_INVALID_ARGS), "invalid args"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_INVALID_PARAMETERS), "invalid parameters"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_IP_NOT_RECEIVED), "ip not received"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_KUP_NOT_RECEIVED), "kup not received"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_MISSING_KEY_INPUT_FOR_CREATING_PROTECTION),
    "missing key input for creating protection"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_MISSING_KEY_USAGE_DIGITALSIGNATURE),
    "missing key usage digitalsignature"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_MISSING_PRIVATE_KEY),
    "missing private key"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_MISSING_PROTECTION), "missing protection"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_MULTIPLE_RESPONSES_NOT_SUPPORTED),
    "multiple responses not supported"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_MULTIPLE_SAN_SOURCES),
    "multiple san sources"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_NO_SENDER_NO_REFERENCE),
    "no sender no reference"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_NO_STDIO), "no stdio"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_NO_SUITABLE_SERVER_CERT),
    "no suitable server cert"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_NO_VALID_SERVER_CERT_FOUND),
    "no valid server cert found"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_NULL_ARGUMENT), "null argument"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_PKIBODY_ERROR), "pkibody error"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_PKICONF_NOT_RECEIVED),
    "pkiconf not received"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_PKISTATUSINFO_NOT_FOUND),
    "pkistatusinfo not found"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_POLLREP_NOT_RECEIVED),
    "pollrep not received"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_POTENTIALLY_INVALID_CERTIFICATE),
    "potentially invalid certificate"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_READ_TIMEOUT), "read timeout"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_RECEIVED_ERROR), "received error"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_RECEIVED_NEGATIVE_CHECKAFTER_IN_POLLREP),
    "received negative checkafter in pollrep"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_RECIPNONCE_UNMATCHED),
    "recipnonce unmatched"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_REQUEST_NOT_ACCEPTED),
    "request not accepted"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_REQUEST_REJECTED_BY_CA),
    "request rejected by ca"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_RP_NOT_RECEIVED), "rp not received"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_SENDER_GENERALNAME_TYPE_NOT_SUPPORTED),
    "sender generalname type not supported"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_TLS_ERROR), "tls error"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_TOTAL_TIMEOUT), "total timeout"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_TRANSACTIONID_UNMATCHED),
    "transactionid unmatched"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_UNEXPECTED_PKIBODY), "unexpected pkibody"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_UNEXPECTED_PKISTATUS),
    "unexpected pkistatus"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_UNEXPECTED_PVNO), "unexpected pvno"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_UNEXPECTED_REQUEST_ID),
    "unexpected request id"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_UNEXPECTED_SENDER), "unexpected sender"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_UNKNOWN_ALGORITHM_ID),
    "unknown algorithm id"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_UNKNOWN_CERT_TYPE), "unknown cert type"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_UNKNOWN_PKISTATUS), "unknown pkistatus"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_UNSUPPORTED_ALGORITHM),
    "unsupported algorithm"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_UNSUPPORTED_KEY_TYPE),
    "unsupported key type"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_UNSUPPORTED_PROTECTION_ALG_DHBASEDMAC),
    "unsupported protection alg dhbasedmac"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_WRONG_ALGORITHM_OID),
    "wrong algorithm oid"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_WRONG_CERTID_IN_RP), "wrong certid in rp"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_WRONG_CERT_HASH), "wrong cert hash"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_WRONG_PBM_VALUE), "wrong pbm value"},
    {ERR_PACK(ERR_LIB_CMP, 0, CMP_R_WRONG_RP_COMPONENT_COUNT),
    "wrong rp component count"},
    {0, NULL}
};

#endif

int ERR_load_CMP_strings(void)
{
#ifndef OPENSSL_NO_ERR
    if (ERR_reason_error_string(CMP_str_reasons[0].error) == NULL)
        ERR_load_strings_const(CMP_str_reasons);
#endif
    return 1;
}
