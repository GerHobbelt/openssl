/*
 * Generated by util/mkerr.pl DO NOT EDIT
 * Copyright 1995-2019 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#ifndef OPENSSL_KDFERR_H
# define OPENSSL_KDFERR_H
# pragma once

# define HEADER_KDFERR_H  /* deprecated in version 3.0 */

# include <openssl/opensslconf.h>
# include <openssl/symhacks.h>


# ifdef  __cplusplus
extern "C"
# endif
int ERR_load_KDF_strings(void);

/*
 * KDF function codes.
 */
# if !OPENSSL_API_3
#  define KDF_F_HKDF_EXTRACT                               0
#  define KDF_F_KDF_HKDF_DERIVE                            0
#  define KDF_F_KDF_HKDF_NEW                               0
#  define KDF_F_KDF_HKDF_SIZE                              0
#  define KDF_F_KDF_MD2CTRL                                0
#  define KDF_F_KDF_PBKDF2_CTRL                            0
#  define KDF_F_KDF_PBKDF2_CTRL_STR                        0
#  define KDF_F_KDF_PBKDF2_DERIVE                          0
#  define KDF_F_KDF_PBKDF2_NEW                             0
#  define KDF_F_KDF_SCRYPT_CTRL_STR                        0
#  define KDF_F_KDF_SCRYPT_CTRL_UINT32                     0
#  define KDF_F_KDF_SCRYPT_CTRL_UINT64                     0
#  define KDF_F_KDF_SCRYPT_DERIVE                          0
#  define KDF_F_KDF_SCRYPT_NEW                             0
#  define KDF_F_KDF_SSHKDF_CTRL                            0
#  define KDF_F_KDF_SSHKDF_CTRL_STR                        0
#  define KDF_F_KDF_SSHKDF_DERIVE                          0
#  define KDF_F_KDF_SSHKDF_NEW                             0
#  define KDF_F_KDF_TLS1_PRF_CTRL_STR                      0
#  define KDF_F_KDF_TLS1_PRF_DERIVE                        0
#  define KDF_F_KDF_TLS1_PRF_NEW                           0
#  define KDF_F_PBKDF2_DERIVE                              0
#  define KDF_F_PBKDF2_SET_MEMBUF                          0
#  define KDF_F_PKEY_HKDF_CTRL_STR                         0
#  define KDF_F_PKEY_HKDF_DERIVE                           0
#  define KDF_F_PKEY_HKDF_INIT                             0
#  define KDF_F_PKEY_SCRYPT_CTRL_STR                       0
#  define KDF_F_PKEY_SCRYPT_CTRL_UINT64                    0
#  define KDF_F_PKEY_SCRYPT_DERIVE                         0
#  define KDF_F_PKEY_SCRYPT_INIT                           0
#  define KDF_F_PKEY_SCRYPT_SET_MEMBUF                     0
#  define KDF_F_PKEY_TLS1_PRF_CTRL_STR                     0
#  define KDF_F_PKEY_TLS1_PRF_DERIVE                       0
#  define KDF_F_PKEY_TLS1_PRF_INIT                         0
#  define KDF_F_SCRYPT_SET_MEMBUF                          0
#  define KDF_F_SSKDF_CTRL_STR                             0
#  define KDF_F_SSKDF_DERIVE                               0
#  define KDF_F_SSKDF_MAC2CTRL                             0
#  define KDF_F_SSKDF_NEW                                  0
#  define KDF_F_SSKDF_SIZE                                 0
#  define KDF_F_TLS1_PRF_ALG                               0
#  define KDF_F_X942KDF_CTRL                               0
#  define KDF_F_X942KDF_DERIVE                             0
#  define KDF_F_X942KDF_HASH_KDM                           0
#  define KDF_F_X942KDF_NEW                                0
#  define KDF_F_X942KDF_SIZE                               0
#  define KDF_F_X963KDF_DERIVE                             0
# endif

/*
 * KDF reason codes.
 */
# define KDF_R_BAD_ENCODING                               122
# define KDF_R_BAD_LENGTH                                 123
# define KDF_R_INAVLID_UKM_LEN                            124
# define KDF_R_INVALID_DIGEST                             100
# define KDF_R_INVALID_ITERATION_COUNT                    119
# define KDF_R_INVALID_KEY_LEN                            120
# define KDF_R_INVALID_MAC_TYPE                           116
# define KDF_R_INVALID_SALT_LEN                           121
# define KDF_R_MISSING_CEK_ALG                            125
# define KDF_R_MISSING_ITERATION_COUNT                    109
# define KDF_R_MISSING_KEY                                104
# define KDF_R_MISSING_MESSAGE_DIGEST                     105
# define KDF_R_MISSING_PARAMETER                          101
# define KDF_R_MISSING_PASS                               110
# define KDF_R_MISSING_SALT                               111
# define KDF_R_MISSING_SECRET                             107
# define KDF_R_MISSING_SEED                               106
# define KDF_R_MISSING_SESSION_ID                         113
# define KDF_R_MISSING_TYPE                               114
# define KDF_R_MISSING_XCGHASH                            115
# define KDF_R_NOT_SUPPORTED                              118
# define KDF_R_UNKNOWN_PARAMETER_TYPE                     103
# define KDF_R_UNSUPPORTED_CEK_ALG                        126
# define KDF_R_UNSUPPORTED_MAC_TYPE                       117
# define KDF_R_VALUE_ERROR                                108
# define KDF_R_VALUE_MISSING                              102
# define KDF_R_WRONG_OUTPUT_BUFFER_SIZE                   112

#endif
