/**********************************************************************
 * Copyright (c) 2013, 2014 Pieter Wuille                             *
 * Distributed under the MIT software license, see the accompanying   *
 * file COPYING or http://www.opensource.org/licenses/mit-license.php.*
 **********************************************************************/

#ifndef _SECP256K1_ECDSA_
#define _SECP256K1_ECDSA_

<<<<<<< HEAD
#include <stddef.h>

#include "scalar.h"
#include "group.h"
#include "ecmult.h"

static int secp256k1_ecdsa_sig_parse(secp256k1_scalar *r, secp256k1_scalar *s, const unsigned char *sig, size_t size);
static int secp256k1_ecdsa_sig_serialize(unsigned char *sig, size_t *size, const secp256k1_scalar *r, const secp256k1_scalar *s);
static int secp256k1_ecdsa_sig_verify(const secp256k1_ecmult_context *ctx, const secp256k1_scalar* r, const secp256k1_scalar* s, const secp256k1_ge *pubkey, const secp256k1_scalar *message);
static int secp256k1_ecdsa_sig_sign(const secp256k1_ecmult_gen_context *ctx, secp256k1_scalar* r, secp256k1_scalar* s, const secp256k1_scalar *seckey, const secp256k1_scalar *message, const secp256k1_scalar *nonce, int *recid);
=======
#include "scalar.h"
#include "group.h"

static void secp256k1_ecsda_start(void);
static void secp256k1_ecdsa_stop(void);

typedef struct {
    secp256k1_scalar_t r, s;
} secp256k1_ecdsa_sig_t;

static int secp256k1_ecdsa_sig_parse(secp256k1_ecdsa_sig_t *r, const unsigned char *sig, int size);
static int secp256k1_ecdsa_sig_serialize(unsigned char *sig, int *size, const secp256k1_ecdsa_sig_t *a);
static int secp256k1_ecdsa_sig_verify(const secp256k1_ecdsa_sig_t *sig, const secp256k1_ge_t *pubkey, const secp256k1_scalar_t *message);
static int secp256k1_ecdsa_sig_sign(secp256k1_ecdsa_sig_t *sig, const secp256k1_scalar_t *seckey, const secp256k1_scalar_t *message, const secp256k1_scalar_t *nonce, int *recid);
static int secp256k1_ecdsa_sig_recover(const secp256k1_ecdsa_sig_t *sig, secp256k1_ge_t *pubkey, const secp256k1_scalar_t *message, int recid);
static void secp256k1_ecdsa_sig_set_rs(secp256k1_ecdsa_sig_t *sig, const secp256k1_scalar_t *r, const secp256k1_scalar_t *s);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

#endif
