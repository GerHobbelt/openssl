/*
 * Copyright 2007-2019 The OpenSSL Project Authors. All Rights Reserved.
 * Copyright Nokia 2007-2018
 * Copyright Siemens AG 2015-2018
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 *
 * CMP implementation by Martin Peylo, Miikka Viljanen, and David von Oheimb.
 */

/* CMP functions for PKIHeader handling */

#include "cmp_int.h"

#include <openssl/rand.h>

/* explicit #includes not strictly needed since implied by the above: */
#include <openssl/asn1t.h>
#include <openssl/cmp.h>
#include <openssl/err.h>

int ossl_cmp_hdr_set_pvno(OSSL_CMP_PKIHEADER *hdr, int pvno)
{
    if (hdr == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return 0;
    }
    if (!ASN1_INTEGER_set(hdr->pvno, pvno)) {
        CMPerr(0, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    return 1;
}

int ossl_cmp_hdr_get_pvno(const OSSL_CMP_PKIHEADER *hdr)
{
    int64_t pvno;

    if (hdr == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return -1;
    }
    if (!ASN1_INTEGER_get_int64(&pvno, hdr->pvno) || pvno < 0 || pvno > INT_MAX)
        return -1;
    return (int)pvno;
}

ASN1_OCTET_STRING *OSSL_CMP_HDR_get0_transactionID(const OSSL_CMP_PKIHEADER *hdr)
{
    if (hdr == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return NULL;
    }
    return hdr->transactionID;
}

ASN1_OCTET_STRING *ossl_cmp_hdr_get0_senderNonce(const OSSL_CMP_PKIHEADER *hdr)
{
    if (hdr == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return NULL;
    }
    return hdr->senderNonce;
}

ASN1_OCTET_STRING *OSSL_CMP_HDR_get0_recipNonce(const OSSL_CMP_PKIHEADER *hdr)
{
    if (hdr == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return NULL;
    }
    return hdr->recipNonce;
}

static int set1_general_name(GENERAL_NAME **tgt, const X509_NAME *src)
{
    GENERAL_NAME *gen = NULL;

    if (tgt == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        goto err;
    }
    if ((gen = GENERAL_NAME_new()) == NULL) {
        CMPerr(0, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    gen->type = GEN_DIRNAME;

    if (src == NULL) { /* NULL DN */
        if ((gen->d.directoryName = X509_NAME_new()) == NULL) {
            CMPerr(0, ERR_R_MALLOC_FAILURE);
            goto err;
        }
    } else if (!X509_NAME_set(&gen->d.directoryName, src)) {
        CMPerr(0, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    GENERAL_NAME_free(*tgt);
    *tgt = gen;

    return 1;

 err:
    GENERAL_NAME_free(gen);
    return 0;
}

/*
 * Set the sender name in PKIHeader.
 * when nm is NULL, sender is set to an empty string
 * returns 1 on success, 0 on error
 */
int ossl_cmp_hdr_set1_sender(OSSL_CMP_PKIHEADER *hdr, const X509_NAME *nm)
{
    if (hdr == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return 0;
    }
    return set1_general_name(&hdr->sender, nm);
}

int ossl_cmp_hdr_set1_recipient(OSSL_CMP_PKIHEADER *hdr, const X509_NAME *nm)
{
    if (hdr == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return 0;
    }
    return set1_general_name(&hdr->recipient, nm);
}

int ossl_cmp_hdr_update_messageTime(OSSL_CMP_PKIHEADER *hdr)
{
    if (hdr == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return 0;
    }
    if (hdr->messageTime == NULL)
        if ((hdr->messageTime = ASN1_GENERALIZEDTIME_new()) == NULL) {
            CMPerr(0, ERR_R_MALLOC_FAILURE);
            return 0;
        }
    if (ASN1_GENERALIZEDTIME_set(hdr->messageTime, time(NULL)) == NULL) {
        CMPerr(0, ERR_R_INTERNAL_ERROR);
        return 0;
    }
    return 1;
}

static int set1_aostr_else_random(ASN1_OCTET_STRING **tgt,
                                  const ASN1_OCTET_STRING *src, size_t len)
{
    unsigned char *bytes = NULL;
    int res = 0;

    if (src == NULL) { /* generate a random value if src == NULL */
        if ((bytes = (unsigned char *)OPENSSL_malloc(len)) == NULL) {
            CMPerr(0, ERR_R_MALLOC_FAILURE);
            goto err;
        }
        if (RAND_bytes(bytes, len) <= 0) {
            CMPerr(0,CMP_R_FAILURE_OBTAINING_RANDOM);
            goto err;
        }
        res = ossl_cmp_asn1_octet_string_set1_bytes(tgt, bytes, len);
    } else {
        res = ossl_cmp_asn1_octet_string_set1(tgt, src);
    }

 err:
    OPENSSL_free(bytes);
    return res;
}

int ossl_cmp_hdr_set1_senderKID(OSSL_CMP_PKIHEADER *hdr,
                                const ASN1_OCTET_STRING *senderKID)
{
    if (hdr == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return 0;
    }
    return ossl_cmp_asn1_octet_string_set1(&hdr->senderKID, senderKID);
}

/*
 * CMP_PKIFREETEXT_push_str() pushes the given text string (unless it is NULL)
 * to the given PKIFREETEXT ft or to a newly allocated freeText if ft is NULL.
 * It returns the new/updated freeText. On error it frees ft and returns NULL.
 */
OSSL_CMP_PKIFREETEXT *ossl_cmp_pkifreetext_push_str(OSSL_CMP_PKIFREETEXT *ft,
                                                    const char *text)
{
    ASN1_UTF8STRING *utf8string = NULL;

    if (text == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return ft;
    }
    if (ft == NULL && (ft = sk_ASN1_UTF8STRING_new_null()) == NULL)
        goto oom;
    if ((utf8string = ASN1_UTF8STRING_new()) == NULL)
        goto oom;
    if (!ASN1_STRING_set(utf8string, text, (int)strlen(text)))
        goto oom;
    if (!sk_ASN1_UTF8STRING_push(ft, utf8string))
        goto oom;
    return ft;

 oom:
    CMPerr(0, ERR_R_MALLOC_FAILURE);
    sk_ASN1_UTF8STRING_pop_free(ft, ASN1_UTF8STRING_free);
    ASN1_UTF8STRING_free(utf8string);
    return NULL;
}

int ossl_cmp_hdr_push0_freeText(OSSL_CMP_PKIHEADER *hdr, ASN1_UTF8STRING *text)
{
    if (hdr == NULL || text == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return 0;
    }
    if (hdr->freeText == NULL)
        if ((hdr->freeText = sk_ASN1_UTF8STRING_new_null()) == NULL)
            goto err;

    if (!sk_ASN1_UTF8STRING_push(hdr->freeText, text))
        goto err;

    return 1;

 err:
    CMPerr(0, ERR_R_MALLOC_FAILURE);
    return 0;
}

int ossl_cmp_hdr_push1_freeText(OSSL_CMP_PKIHEADER *hdr, ASN1_UTF8STRING *text)
{
    if (hdr == NULL || text == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return 0;
    }

    hdr->freeText = ossl_cmp_pkifreetext_push_str(hdr->freeText,
                                                  (char *)text->data);
    return hdr->freeText != NULL;
}

int ossl_cmp_hdr_generalInfo_push0_item(OSSL_CMP_PKIHEADER *hdr,
                                        OSSL_CMP_ITAV *itav)
{
    if (hdr == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return 0;
    }
    if (!OSSL_CMP_ITAV_push0_stack_item(&hdr->generalInfo, itav)) {
        CMPerr(0, CMP_R_ERROR_PUSHING_GENERALINFO_ITEM);
        return 0;
    }
    return 1;
}

int ossl_cmp_hdr_generalInfo_push1_items(OSSL_CMP_PKIHEADER *hdr,
                                         STACK_OF(OSSL_CMP_ITAV) *itavs)
{
    int i;
    OSSL_CMP_ITAV *itav = NULL;

    if (hdr == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return 0;
    }
    for (i = 0; i < sk_OSSL_CMP_ITAV_num(itavs); i++) {
        itav = OSSL_CMP_ITAV_dup(sk_OSSL_CMP_ITAV_value(itavs, i));
        if (!ossl_cmp_hdr_generalInfo_push0_item(hdr, itav)) {
            OSSL_CMP_ITAV_free(itav);
            CMPerr(0, CMP_R_ERROR_PUSHING_GENERALINFO_ITEMS);
            return 0;
        }
    }
    return 1;
}

int ossl_cmp_hdr_set_implicitConfirm(OSSL_CMP_PKIHEADER *hdr)
{
    OSSL_CMP_ITAV *itav = NULL;

    if (hdr == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return 0;
    }
    if ((itav = OSSL_CMP_ITAV_create(OBJ_nid2obj(NID_id_it_implicitConfirm),
                                     (ASN1_TYPE *)ASN1_NULL_new())) == NULL)
        goto err;
    if (!ossl_cmp_hdr_generalInfo_push0_item(hdr, itav))
        goto err;
    return 1;

 err:
    OSSL_CMP_ITAV_free(itav);
    return 0;
}

/*
 * checks if implicitConfirm in the generalInfo field of the header is set
 * returns 1 if it is set, 0 if not
 */
int ossl_cmp_hdr_check_implicitConfirm(OSSL_CMP_PKIHEADER *hdr)
{
    int itavCount;
    int i;
    OSSL_CMP_ITAV *itav = NULL;

    if (hdr == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return 0;
    }

    itavCount = sk_OSSL_CMP_ITAV_num(hdr->generalInfo);

    for (i = 0; i < itavCount; i++) {
        itav = sk_OSSL_CMP_ITAV_value(hdr->generalInfo, i);
        if (OBJ_obj2nid(itav->infoType) == NID_id_it_implicitConfirm)
            return 1;
    }

    return 0;
}

int ossl_cmp_hdr_init(OSSL_CMP_CTX *ctx, OSSL_CMP_PKIHEADER *hdr)
{
    X509_NAME *sender;
    X509_NAME *rcp = NULL;

    if (ctx == NULL || hdr == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return 0;
    }

    /* set the CMP version */
    if (!ossl_cmp_hdr_set_pvno(hdr, OSSL_CMP_PVNO))
        return 0;

    /*
     * if neither client cert nor subject name given, sender name is not known
     * to the client and in that case set to NULL-DN
     */
    sender = ctx->clCert != NULL ?
        X509_get_subject_name(ctx->clCert) : ctx->subjectName;
    if (sender == NULL && ctx->referenceValue == NULL) {
        CMPerr(0, CMP_R_NO_SENDER_NO_REFERENCE);
        return 0;
    }
    if (!ossl_cmp_hdr_set1_sender(hdr, sender))
        return 0;

    /* determine recipient entry in PKIHeader */
    if (ctx->srvCert != NULL) {
        rcp = X509_get_subject_name(ctx->srvCert);
        /* set also as expected_sender of responses unless set explicitly */
        if (ctx->expected_sender == NULL && rcp != NULL
                && !OSSL_CMP_CTX_set1_expected_sender(ctx, rcp))
            return 0;
    } else if (ctx->recipient != NULL) {
        rcp = ctx->recipient;
    } else if (ctx->issuer != NULL) {
        rcp = ctx->issuer;
    } else if (ctx->oldCert != NULL) {
        rcp = X509_get_issuer_name(ctx->oldCert);
    } else if (ctx->clCert != NULL) {
        rcp = X509_get_issuer_name(ctx->clCert);
    }
    if (!ossl_cmp_hdr_set1_recipient(hdr, rcp))
        return 0;

    /* set current time as message time */
    if (!ossl_cmp_hdr_update_messageTime(hdr))
        return 0;

    if (ctx->recipNonce != NULL)
        if (!ossl_cmp_asn1_octet_string_set1(&hdr->recipNonce, ctx->recipNonce))
            return 0;

    /*
     * set ctx->transactionID in CMP header
     * if ctx->transactionID is NULL, a random one is created with 128 bit
     * according to section 5.1.1:
     *
     * It is RECOMMENDED that the clients fill the transactionID field with
     * 128 bits of (pseudo-) random data for the start of a transaction to
     * reduce the probability of having the transactionID in use at the server.
     */
    if (ctx->transactionID == NULL
            && !set1_aostr_else_random(&ctx->transactionID,NULL,
                                       OSSL_CMP_TRANSACTIONID_LENGTH))
        return 0;
    if (!ossl_cmp_asn1_octet_string_set1(&hdr->transactionID,
                                         ctx->transactionID))
        return 0;

    /*-
     * set random senderNonce
     * according to section 5.1.1:
     *
     * senderNonce                  present
     *         -- 128 (pseudo-)random bits
     * The senderNonce and recipNonce fields protect the PKIMessage against
     * replay attacks. The senderNonce will typically be 128 bits of
     * (pseudo-) random data generated by the sender, whereas the recipNonce
     * is copied from the senderNonce of the previous message in the
     * transaction.
     */
    if (!set1_aostr_else_random(&hdr->senderNonce, NULL,
                                OSSL_CMP_SENDERNONCE_LENGTH))
        return 0;

    /* store senderNonce - for cmp with recipNonce in next outgoing msg */
    OSSL_CMP_CTX_set1_senderNonce(ctx, hdr->senderNonce);

    /*-
     * freeText                [7] PKIFreeText OPTIONAL,
     * -- this may be used to indicate context-specific instructions
     * -- (this field is intended for human consumption)
     */
    if (ctx->freeText != NULL
            && !ossl_cmp_hdr_push1_freeText(hdr, ctx->freeText))
        return 0;

    return 1;
}