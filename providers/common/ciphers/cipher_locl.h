/*
 * Copyright 2019 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <stdio.h>
#include <openssl/opensslconf.h>
#include <openssl/params.h>
#include <openssl/core_numbers.h>
#include <openssl/core_names.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include "internal/cryptlib.h"
#include "crypto/modes.h"
#include "internal/provider_algs.h"
#include "internal/providercommonerr.h"
#include "crypto/ciphermode_platform.h"

#define GENERIC_BLOCK_SIZE 16
#define IV_STATE_UNINITIALISED 0  /* initial state is not initialized */
#define IV_STATE_BUFFERED      1  /* iv has been copied to the iv buffer */
#define IV_STATE_COPIED        2  /* iv has been copied from the iv buffer */
#define IV_STATE_FINISHED      3  /* the iv has been used - so don't reuse it */

#define PROV_CIPHER_FUNC(type, name, args) typedef type (* OSSL_##name##_fn)args

typedef struct prov_cipher_hw_st PROV_CIPHER_HW;
typedef struct prov_cipher_ctx_st PROV_CIPHER_CTX;

typedef int (PROV_CIPHER_HW_FN)(PROV_CIPHER_CTX *dat, unsigned char *out,
                                const unsigned char *in, size_t len);

struct prov_cipher_ctx_st {
    block128_f block;
    union {
        cbc128_f cbc;
        ctr128_f ctr;
    } stream;

    /*
     * num contains the number of bytes of |iv| which are valid for modes that
     * manage partial blocks themselves.
     */
    size_t num;

    int mode;
    int enc;              /* Set to 1 for encrypt, or 0 otherwise */
    size_t bufsz;         /* Number of bytes in buf */
    size_t keylen;        /* key size (in bytes) */
    size_t blocksize;
    uint64_t flags;
    unsigned int pad : 1; /* Whether padding should be used or not */

    /* Buffer of partial blocks processed via update calls */
    unsigned char buf[GENERIC_BLOCK_SIZE];
    unsigned char iv[GENERIC_BLOCK_SIZE];
    const PROV_CIPHER_HW *hw; /* hardware specific functions */
    const void *ks; /* Pointer to algorithm specific key data */
};

struct prov_cipher_hw_st {
    int (*init)(PROV_CIPHER_CTX *dat, const uint8_t *key, size_t keylen);
    PROV_CIPHER_HW_FN *cipher;
};

OSSL_OP_cipher_encrypt_init_fn cipher_generic_einit;
OSSL_OP_cipher_decrypt_init_fn cipher_generic_dinit;
OSSL_OP_cipher_update_fn cipher_generic_block_update;
OSSL_OP_cipher_final_fn cipher_generic_block_final;
OSSL_OP_cipher_update_fn cipher_generic_stream_update;
OSSL_OP_cipher_final_fn cipher_generic_stream_final;
OSSL_OP_cipher_cipher_fn cipher_generic_cipher;
OSSL_OP_cipher_get_ctx_params_fn cipher_generic_get_ctx_params;
OSSL_OP_cipher_set_ctx_params_fn cipher_generic_set_ctx_params;
OSSL_OP_cipher_gettable_params_fn     cipher_default_gettable_params;
OSSL_OP_cipher_gettable_ctx_params_fn cipher_default_gettable_ctx_params;
OSSL_OP_cipher_settable_ctx_params_fn cipher_default_settable_ctx_params;
OSSL_OP_cipher_gettable_ctx_params_fn cipher_aead_gettable_ctx_params;
OSSL_OP_cipher_settable_ctx_params_fn cipher_aead_settable_ctx_params;
int cipher_default_get_params(OSSL_PARAM params[], int md, unsigned long flags,
                              int kbits, int blkbits, int ivbits);
void cipher_generic_initkey(void *vctx, int kbits, int blkbits, int mode,
                            const PROV_CIPHER_HW *ciph);

size_t fillblock(unsigned char *buf, size_t *buflen, size_t blocksize,
                 const unsigned char **in, size_t *inlen);
int trailingdata(unsigned char *buf, size_t *buflen, size_t blocksize,
                 const unsigned char **in, size_t *inlen);
void padblock(unsigned char *buf, size_t *buflen, size_t blocksize);
int unpadblock(unsigned char *buf, size_t *buflen, size_t blocksize);

#include "cipher_aes.h"
#include "cipher_aria.h"
#include "cipher_camellia.h"
#include "cipher_gcm.h"
#include "cipher_ccm.h"

#define IMPLEMENT_generic_cipher(alg, UCALG, lcmode, UCMODE, flags, kbits,     \
                                 blkbits, ivbits, typ)                         \
static OSSL_OP_cipher_get_params_fn alg##_##kbits##_##lcmode##_get_params;     \
static int alg##_##kbits##_##lcmode##_get_params(OSSL_PARAM params[])          \
{                                                                              \
    return cipher_default_get_params(params, EVP_CIPH_##UCMODE##_MODE, flags,  \
                                     kbits, blkbits, ivbits);                  \
}                                                                              \
static OSSL_OP_cipher_newctx_fn alg##_##kbits##_##lcmode##_newctx;             \
static void * alg##_##kbits##_##lcmode##_newctx(void *provctx)                 \
{                                                                              \
     PROV_##UCALG##_CTX *ctx = OPENSSL_zalloc(sizeof(*ctx));                   \
     if (ctx != NULL) {                                                        \
         cipher_generic_initkey(ctx, kbits, blkbits, EVP_CIPH_##UCMODE##_MODE, \
                                PROV_CIPHER_HW_##alg##_##lcmode(kbits));       \
     }                                                                         \
     return ctx;                                                               \
}                                                                              \
const OSSL_DISPATCH alg##kbits##lcmode##_functions[] = {                       \
    { OSSL_FUNC_CIPHER_NEWCTX,                                                 \
      (void (*)(void)) alg##_##kbits##_##lcmode##_newctx },                    \
    { OSSL_FUNC_CIPHER_FREECTX, (void (*)(void)) alg##_freectx },              \
    { OSSL_FUNC_CIPHER_DUPCTX, (void (*)(void)) alg##_dupctx },                \
    { OSSL_FUNC_CIPHER_ENCRYPT_INIT, (void (*)(void))cipher_generic_einit },   \
    { OSSL_FUNC_CIPHER_DECRYPT_INIT, (void (*)(void))cipher_generic_dinit },   \
    { OSSL_FUNC_CIPHER_UPDATE, (void (*)(void))cipher_generic_##typ##_update },\
    { OSSL_FUNC_CIPHER_FINAL, (void (*)(void))cipher_generic_##typ##_final },  \
    { OSSL_FUNC_CIPHER_CIPHER, (void (*)(void))cipher_generic_cipher },        \
    { OSSL_FUNC_CIPHER_GET_PARAMS,                                             \
      (void (*)(void)) alg##_##kbits##_##lcmode##_get_params },                \
    { OSSL_FUNC_CIPHER_GET_CTX_PARAMS,                                         \
      (void (*)(void))cipher_generic_get_ctx_params },                         \
    { OSSL_FUNC_CIPHER_SET_CTX_PARAMS,                                         \
      (void (*)(void))cipher_generic_set_ctx_params },                         \
    { OSSL_FUNC_CIPHER_GETTABLE_PARAMS,                                        \
      (void (*)(void))cipher_default_gettable_params },                        \
    { OSSL_FUNC_CIPHER_GETTABLE_CTX_PARAMS,                                    \
      (void (*)(void))cipher_default_gettable_ctx_params },                    \
    { OSSL_FUNC_CIPHER_SETTABLE_CTX_PARAMS,                                    \
     (void (*)(void))cipher_default_settable_ctx_params },                     \
    { 0, NULL }                                                                \
};

#define IMPLEMENT_aead_cipher(alg, lc, UCMODE, flags, kbits, blkbits, ivbits)  \
static OSSL_OP_cipher_get_params_fn alg##_##kbits##_##lc##_get_params;         \
static int alg##_##kbits##_##lc##_get_params(OSSL_PARAM params[])              \
{                                                                              \
    return cipher_default_get_params(params, EVP_CIPH_##UCMODE##_MODE,         \
                                     flags, kbits, blkbits, ivbits);           \
}                                                                              \
static OSSL_OP_cipher_newctx_fn alg##kbits##lc##_newctx;                       \
static void * alg##kbits##lc##_newctx(void *provctx)                           \
{                                                                              \
    return alg##_##lc##_newctx(provctx, kbits);                                \
}                                                                              \
const OSSL_DISPATCH alg##kbits##lc##_functions[] = {                           \
    { OSSL_FUNC_CIPHER_NEWCTX, (void (*)(void))alg##kbits##lc##_newctx },      \
    { OSSL_FUNC_CIPHER_FREECTX, (void (*)(void))alg##_##lc##_freectx },        \
    { OSSL_FUNC_CIPHER_ENCRYPT_INIT, (void (*)(void)) lc##_einit },            \
    { OSSL_FUNC_CIPHER_DECRYPT_INIT, (void (*)(void)) lc##_dinit },            \
    { OSSL_FUNC_CIPHER_UPDATE, (void (*)(void)) lc##_stream_update },          \
    { OSSL_FUNC_CIPHER_FINAL, (void (*)(void)) lc##_stream_final },            \
    { OSSL_FUNC_CIPHER_CIPHER, (void (*)(void)) lc##_cipher },                 \
    { OSSL_FUNC_CIPHER_GET_PARAMS,                                             \
      (void (*)(void)) alg##_##kbits##_##lc##_get_params },                    \
    { OSSL_FUNC_CIPHER_GET_CTX_PARAMS,                                         \
      (void (*)(void)) lc##_get_ctx_params },                                  \
    { OSSL_FUNC_CIPHER_SET_CTX_PARAMS,                                         \
      (void (*)(void)) lc##_set_ctx_params },                                  \
    { OSSL_FUNC_CIPHER_GETTABLE_PARAMS,                                        \
      (void (*)(void))cipher_default_gettable_params },                        \
    { OSSL_FUNC_CIPHER_GETTABLE_CTX_PARAMS,                                    \
      (void (*)(void))cipher_aead_gettable_ctx_params },                       \
    { OSSL_FUNC_CIPHER_SETTABLE_CTX_PARAMS,                                    \
      (void (*)(void))cipher_aead_settable_ctx_params },                       \
    { 0, NULL }                                                                \
}

PROV_CIPHER_HW_FN cipher_hw_generic_cbc;
PROV_CIPHER_HW_FN cipher_hw_generic_ecb;
PROV_CIPHER_HW_FN cipher_hw_generic_ofb128;
PROV_CIPHER_HW_FN cipher_hw_generic_cfb128;
PROV_CIPHER_HW_FN cipher_hw_generic_cfb8;
PROV_CIPHER_HW_FN cipher_hw_generic_cfb1;
PROV_CIPHER_HW_FN cipher_hw_generic_ctr;
PROV_CIPHER_HW_FN cipher_hw_chunked_cbc;
PROV_CIPHER_HW_FN cipher_hw_chunked_cfb8;
PROV_CIPHER_HW_FN cipher_hw_chunked_cfb128;
PROV_CIPHER_HW_FN cipher_hw_chunked_ofb128;
#define cipher_hw_chunked_ecb  cipher_hw_generic_ecb
#define cipher_hw_chunked_ctr  cipher_hw_generic_ctr
#define cipher_hw_chunked_cfb1 cipher_hw_generic_cfb1