/*
 * Copyright 1995-2018 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#ifndef OPENSSL_DSA_H
# define OPENSSL_DSA_H
# pragma once

# include <openssl/macros.h>
# ifndef OPENSSL_NO_DEPRECATED_3_0
#  define HEADER_DSA_H
# endif

# include <openssl/opensslconf.h>

# ifndef OPENSSL_NO_DSA
#  ifdef  __cplusplus
extern "C" {
#  endif
#  include <openssl/e_os2.h>
#  include <openssl/asn1.h>
#  include <openssl/bio.h>
#  include <openssl/crypto.h>
#  include <openssl/types.h>
#  include <openssl/bn.h>
#  ifndef OPENSSL_NO_DEPRECATED_1_1_0
#   include <openssl/dh.h>
#  endif
#  include <openssl/dsaerr.h>

#  ifndef OPENSSL_DSA_MAX_MODULUS_BITS
#   define OPENSSL_DSA_MAX_MODULUS_BITS   10000
#  endif

#  define OPENSSL_DSA_FIPS_MIN_MODULUS_BITS 1024

#  ifndef OPENSSL_NO_DEPRECATED_1_1_0
/*
 * Does nothing. Previously this switched off constant time behaviour.
 */
#   define DSA_FLAG_NO_EXP_CONSTTIME       0x00
#  endif

#  ifndef OPENSSL_NO_DEPRECATED_3_0
#   define DSA_FLAG_CACHE_MONT_P   0x01

/*
 * If this flag is set the DSA method is FIPS compliant and can be used in
 * FIPS mode. This is set in the validated module method. If an application
 * sets this flag in its own methods it is its responsibility to ensure the
 * result is compliant.
 */

#   define DSA_FLAG_FIPS_METHOD                    0x0400

/*
 * If this flag is set the operations normally disabled in FIPS mode are
 * permitted it is then the applications responsibility to ensure that the
 * usage is compliant.
 */

#   define DSA_FLAG_NON_FIPS_ALLOW                 0x0400
#   define DSA_FLAG_FIPS_CHECKED                   0x0800
#  endif    /* OPENSSL_NO_DEPRECATED_3_0 */

/* Already defined in ossl_typ.h */
/* typedef struct dsa_st DSA; */
/* typedef struct dsa_method DSA_METHOD; */

typedef struct DSA_SIG_st DSA_SIG;

/*
 * TODO(3.0): consider removing the ASN.1 encoding and decoding when
 * deserialisation is completed elsewhere.
 */
#  define d2i_DSAparams_fp(fp, x) \
        (DSA *)ASN1_d2i_fp((char *(*)())DSA_new, \
                           (char *(*)())d2i_DSAparams, (fp), \
                           (unsigned char **)(x))
#  define i2d_DSAparams_fp(fp, x) \
        ASN1_i2d_fp(i2d_DSAparams, (fp), (unsigned char *)(x))
#  define d2i_DSAparams_bio(bp, x) \
        ASN1_d2i_bio_of(DSA, DSA_new, d2i_DSAparams, bp, x)
#  define i2d_DSAparams_bio(bp, x) \
        ASN1_i2d_bio_of(DSA, i2d_DSAparams, bp, x)

DECLARE_ASN1_DUP_FUNCTION_name(DSA, DSAparams)
DSA_SIG *DSA_SIG_new(void);
void DSA_SIG_free(DSA_SIG *a);
DECLARE_ASN1_ENCODE_FUNCTIONS_only(DSA_SIG, DSA_SIG)
void DSA_SIG_get0(const DSA_SIG *sig, const BIGNUM **pr, const BIGNUM **ps);
int DSA_SIG_set0(DSA_SIG *sig, BIGNUM *r, BIGNUM *s);

DEPRECATEDIN_3_0(DSA_SIG *DSA_do_sign(const unsigned char *dgst, int dlen,
                                      DSA *dsa))
DEPRECATEDIN_3_0(int DSA_do_verify(const unsigned char *dgst, int dgst_len,
                                   DSA_SIG *sig, DSA *dsa))

DEPRECATEDIN_3_0(const DSA_METHOD *DSA_OpenSSL(void))

DEPRECATEDIN_3_0(void DSA_set_default_method(const DSA_METHOD *))
DEPRECATEDIN_3_0(const DSA_METHOD *DSA_get_default_method(void))
DEPRECATEDIN_3_0(int DSA_set_method(DSA *dsa, const DSA_METHOD *))
DEPRECATEDIN_3_0(const DSA_METHOD *DSA_get_method(DSA *d))

DSA *DSA_new(void);
DEPRECATEDIN_3_0(DSA *DSA_new_method(ENGINE *engine))
void DSA_free(DSA *r);
/* "up" the DSA object's reference count */
int DSA_up_ref(DSA *r);
DEPRECATEDIN_3_0(int DSA_size(const DSA *))
DEPRECATEDIN_3_0(int DSA_bits(const DSA *d))
DEPRECATEDIN_3_0(int DSA_security_bits(const DSA *d))
        /* next 4 return -1 on error */
DEPRECATEDIN_3_0(int DSA_sign_setup(DSA *dsa, BN_CTX *ctx_in, BIGNUM **kinvp,
                                    BIGNUM **rp))
DEPRECATEDIN_3_0(int DSA_sign(int type, const unsigned char *dgst, int dlen,
                              unsigned char *sig, unsigned int *siglen,
                              DSA *dsa))
DEPRECATEDIN_3_0(int DSA_verify(int type, const unsigned char *dgst,
                                int dgst_len, const unsigned char *sigbuf,
                                int siglen, DSA *dsa))
#  ifndef OPENSSL_NO_DEPRECATED_3_0
#   define DSA_get_ex_new_index(l, p, newf, dupf, freef) \
        CRYPTO_get_ex_new_index(CRYPTO_EX_INDEX_DSA, l, p, newf, dupf, freef)
#  endif
DEPRECATEDIN_3_0(int DSA_set_ex_data(DSA *d, int idx, void *arg))
DEPRECATEDIN_3_0(void *DSA_get_ex_data(const DSA *d, int idx))

DECLARE_ASN1_ENCODE_FUNCTIONS_only(DSA, DSAPublicKey)
DECLARE_ASN1_ENCODE_FUNCTIONS_only(DSA, DSAPrivateKey)
DECLARE_ASN1_ENCODE_FUNCTIONS_only(DSA, DSAparams)

/* Deprecated version */
DEPRECATEDIN_0_9_8(DSA *DSA_generate_parameters(int bits,
                                                unsigned char *seed,
                                                int seed_len,
                                                int *counter_ret,
                                                unsigned long *h_ret, void
                                                 (*callback) (int, int,
                                                              void *),
                                                void *cb_arg))

/* New version */
DEPRECATEDIN_3_0(int DSA_generate_parameters_ex(DSA *dsa, int bits,
                                                const unsigned char *seed,
                                                int seed_len, int *counter_ret,
                                                unsigned long *h_ret,
                                                BN_GENCB *cb))

DEPRECATEDIN_3_0(int DSA_generate_key(DSA *a))

DEPRECATEDIN_3_0(int DSAparams_print(BIO *bp, const DSA *x))
DEPRECATEDIN_3_0(int DSA_print(BIO *bp, const DSA *x, int off))
#  ifndef OPENSSL_NO_STDIO
DEPRECATEDIN_3_0(int DSAparams_print_fp(FILE *fp, const DSA *x))
DEPRECATEDIN_3_0(int DSA_print_fp(FILE *bp, const DSA *x, int off))
#  endif

#  ifndef OPENSSL_NO_DEPRECATED_3_0
#   define DSS_prime_checks 64
/*
 * Primality test according to FIPS PUB 186-4, Appendix C.3. Since we only
 * have one value here we set the number of checks to 64 which is the 128 bit
 * security level that is the highest level and valid for creating a 3072 bit
 * DSA key.
 */
#   define DSA_is_prime(n, callback, cb_arg) \
            BN_is_prime(n, DSS_prime_checks, callback, NULL, cb_arg)
#  endif

#  ifndef OPENSSL_NO_DH
/*
 * Convert DSA structure (key or just parameters) into DH structure (be
 * careful to avoid small subgroup attacks when using this!)
 */
DEPRECATEDIN_3_0(DH *DSA_dup_DH(const DSA *r))
#  endif

#  define EVP_PKEY_CTX_set_dsa_paramgen_bits(ctx, nbits) \
         EVP_PKEY_CTX_ctrl(ctx, EVP_PKEY_DSA, EVP_PKEY_OP_PARAMGEN, \
                           EVP_PKEY_CTRL_DSA_PARAMGEN_BITS, nbits, NULL)
#  define EVP_PKEY_CTX_set_dsa_paramgen_q_bits(ctx, qbits) \
         EVP_PKEY_CTX_ctrl(ctx, EVP_PKEY_DSA, EVP_PKEY_OP_PARAMGEN, \
                           EVP_PKEY_CTRL_DSA_PARAMGEN_Q_BITS, qbits, NULL)
#  define EVP_PKEY_CTX_set_dsa_paramgen_md(ctx, md) \
         EVP_PKEY_CTX_ctrl(ctx, EVP_PKEY_DSA, EVP_PKEY_OP_PARAMGEN, \
                           EVP_PKEY_CTRL_DSA_PARAMGEN_MD, 0, (void *)(md))

#  define EVP_PKEY_CTRL_DSA_PARAMGEN_BITS         (EVP_PKEY_ALG_CTRL + 1)
#  define EVP_PKEY_CTRL_DSA_PARAMGEN_Q_BITS       (EVP_PKEY_ALG_CTRL + 2)
#  define EVP_PKEY_CTRL_DSA_PARAMGEN_MD           (EVP_PKEY_ALG_CTRL + 3)

void DSA_get0_pqg(const DSA *d,
                  const BIGNUM **p, const BIGNUM **q, const BIGNUM **g);
int DSA_set0_pqg(DSA *d, BIGNUM *p, BIGNUM *q, BIGNUM *g);
void DSA_get0_key(const DSA *d,
                  const BIGNUM **pub_key, const BIGNUM **priv_key);
int DSA_set0_key(DSA *d, BIGNUM *pub_key, BIGNUM *priv_key);
const BIGNUM *DSA_get0_p(const DSA *d);
const BIGNUM *DSA_get0_q(const DSA *d);
const BIGNUM *DSA_get0_g(const DSA *d);
const BIGNUM *DSA_get0_pub_key(const DSA *d);
const BIGNUM *DSA_get0_priv_key(const DSA *d);
void DSA_clear_flags(DSA *d, int flags);
int DSA_test_flags(const DSA *d, int flags);
void DSA_set_flags(DSA *d, int flags);
DEPRECATEDIN_3_0(ENGINE *DSA_get0_engine(DSA *d))

DEPRECATEDIN_3_0(DSA_METHOD *DSA_meth_new(const char *name, int flags))
DEPRECATEDIN_3_0(void DSA_meth_free(DSA_METHOD *dsam))
DEPRECATEDIN_3_0(DSA_METHOD *DSA_meth_dup(const DSA_METHOD *dsam))
DEPRECATEDIN_3_0(const char *DSA_meth_get0_name(const DSA_METHOD *dsam))
DEPRECATEDIN_3_0(int DSA_meth_set1_name(DSA_METHOD *dsam, const char *name))
DEPRECATEDIN_3_0(int DSA_meth_get_flags(const DSA_METHOD *dsam))
DEPRECATEDIN_3_0(int DSA_meth_set_flags(DSA_METHOD *dsam, int flags))
DEPRECATEDIN_3_0(void *DSA_meth_get0_app_data(const DSA_METHOD *dsam))
DEPRECATEDIN_3_0(int DSA_meth_set0_app_data(DSA_METHOD *dsam, void *app_data))
DEPRECATEDIN_3_0(DSA_SIG *(*DSA_meth_get_sign(const DSA_METHOD *dsam))
        (const unsigned char *, int, DSA *))
DEPRECATEDIN_3_0(int DSA_meth_set_sign(DSA_METHOD *dsam,
                       DSA_SIG *(*sign) (const unsigned char *, int, DSA *)))
DEPRECATEDIN_3_0(int (*DSA_meth_get_sign_setup(const DSA_METHOD *dsam))
        (DSA *, BN_CTX *, BIGNUM **, BIGNUM **))
DEPRECATEDIN_3_0(int DSA_meth_set_sign_setup(DSA_METHOD *dsam,
        int (*sign_setup) (DSA *, BN_CTX *, BIGNUM **, BIGNUM **)))
DEPRECATEDIN_3_0(int (*DSA_meth_get_verify(const DSA_METHOD *dsam))
        (const unsigned char *, int, DSA_SIG *, DSA *))
DEPRECATEDIN_3_0(int DSA_meth_set_verify(DSA_METHOD *dsam,
    int (*verify) (const unsigned char *, int, DSA_SIG *, DSA *)))
DEPRECATEDIN_3_0(int (*DSA_meth_get_mod_exp(const DSA_METHOD *dsam))
        (DSA *, BIGNUM *, const BIGNUM *, const BIGNUM *, const BIGNUM *,
         const BIGNUM *, const BIGNUM *, BN_CTX *, BN_MONT_CTX *))
DEPRECATEDIN_3_0(int DSA_meth_set_mod_exp(DSA_METHOD *dsam,
    int (*mod_exp) (DSA *, BIGNUM *, const BIGNUM *, const BIGNUM *,
                    const BIGNUM *, const BIGNUM *, const BIGNUM *, BN_CTX *,
                    BN_MONT_CTX *)))
DEPRECATEDIN_3_0(int (*DSA_meth_get_bn_mod_exp(const DSA_METHOD *dsam))
    (DSA *, BIGNUM *, const BIGNUM *, const BIGNUM *, const BIGNUM *,
     BN_CTX *, BN_MONT_CTX *))
DEPRECATEDIN_3_0(int DSA_meth_set_bn_mod_exp(DSA_METHOD *dsam,
    int (*bn_mod_exp) (DSA *, BIGNUM *, const BIGNUM *, const BIGNUM *,
                       const BIGNUM *, BN_CTX *, BN_MONT_CTX *)))
DEPRECATEDIN_3_0(int (*DSA_meth_get_init(const DSA_METHOD *dsam))(DSA *))
DEPRECATEDIN_3_0(int DSA_meth_set_init(DSA_METHOD *dsam, int (*init)(DSA *)))
DEPRECATEDIN_3_0(int (*DSA_meth_get_finish(const DSA_METHOD *dsam)) (DSA *))
DEPRECATEDIN_3_0(int DSA_meth_set_finish(DSA_METHOD *dsam, int (*finish) (DSA *)))
DEPRECATEDIN_3_0(int (*DSA_meth_get_paramgen(const DSA_METHOD *dsam))
        (DSA *, int, const unsigned char *, int, int *, unsigned long *,
         BN_GENCB *))
DEPRECATEDIN_3_0(int DSA_meth_set_paramgen(DSA_METHOD *dsam,
        int (*paramgen) (DSA *, int, const unsigned char *, int, int *,
                         unsigned long *, BN_GENCB *)))
DEPRECATEDIN_3_0(int (*DSA_meth_get_keygen(const DSA_METHOD *dsam)) (DSA *))
DEPRECATEDIN_3_0(int DSA_meth_set_keygen(DSA_METHOD *dsam, int (*keygen) (DSA *)))

#  ifdef  __cplusplus
}
#  endif
# endif
#endif
