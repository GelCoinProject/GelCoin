/**********************************************************************
 * Copyright (c) 2013, 2014 Pieter Wuille                             *
 * Distributed under the MIT software license, see the accompanying   *
 * file COPYING or http://www.opensource.org/licenses/mit-license.php.*
 **********************************************************************/

#ifndef _SECP256K1_ECKEY_
#define _SECP256K1_ECKEY_

<<<<<<< HEAD
#include <stddef.h>

#include "group.h"
#include "scalar.h"
#include "ecmult.h"
#include "ecmult_gen.h"

static int secp256k1_eckey_pubkey_parse(secp256k1_ge *elem, const unsigned char *pub, size_t size);
static int secp256k1_eckey_pubkey_serialize(secp256k1_ge *elem, unsigned char *pub, size_t *size, int compressed);

static int secp256k1_eckey_privkey_tweak_add(secp256k1_scalar *key, const secp256k1_scalar *tweak);
static int secp256k1_eckey_pubkey_tweak_add(const secp256k1_ecmult_context *ctx, secp256k1_ge *key, const secp256k1_scalar *tweak);
static int secp256k1_eckey_privkey_tweak_mul(secp256k1_scalar *key, const secp256k1_scalar *tweak);
static int secp256k1_eckey_pubkey_tweak_mul(const secp256k1_ecmult_context *ctx, secp256k1_ge *key, const secp256k1_scalar *tweak);
=======
#include "group.h"
#include "scalar.h"

static int secp256k1_eckey_pubkey_parse(secp256k1_ge_t *elem, const unsigned char *pub, int size);
static int secp256k1_eckey_pubkey_serialize(secp256k1_ge_t *elem, unsigned char *pub, int *size, int compressed);

static int secp256k1_eckey_privkey_parse(secp256k1_scalar_t *key, const unsigned char *privkey, int privkeylen);
static int secp256k1_eckey_privkey_serialize(unsigned char *privkey, int *privkeylen, const secp256k1_scalar_t *key, int compressed);

static int secp256k1_eckey_privkey_tweak_add(secp256k1_scalar_t *key, const secp256k1_scalar_t *tweak);
static int secp256k1_eckey_pubkey_tweak_add(secp256k1_ge_t *key, const secp256k1_scalar_t *tweak);
static int secp256k1_eckey_privkey_tweak_mul(secp256k1_scalar_t *key, const secp256k1_scalar_t *tweak);
static int secp256k1_eckey_pubkey_tweak_mul(secp256k1_ge_t *key, const secp256k1_scalar_t *tweak);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

#endif
