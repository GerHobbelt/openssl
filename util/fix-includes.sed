s|internal/([a-z0-9_]+)_int\.h|crypto/\1.h|g ;
s@internal/(__DECC_INCLUDE_EPILOGUE.H|__DECC_INCLUDE_PROLOGUE.H|aria.h|asn1_dsa.h|async.h|bn_conf.h|bn_dh.h|bn_srp.h|chacha.h|ciphermode_platform.h|ctype.h|dso_conf.h|engine.h|lhash.h|md32_common.h|objects.h|poly1305.h|sha.h|siphash.h|sm2.h|sm2err.h|sm4.h|sparse_array.h|store.h|foobar)@crypto/\1@g ;
s/constant_time_locl/constant_time/g ;
s/_lo?cl\.h/_local.h/g ;
s/_int\.h/_local.h/g ;
s|openssl/ossl_typ\.h|openssl/types.h|g ;
