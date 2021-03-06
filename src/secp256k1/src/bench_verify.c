/**********************************************************************
 * Copyright (c) 2014 Pieter Wuille                                   *
 * Distributed under the MIT software license, see the accompanying   *
 * file COPYING or http://www.opensource.org/licenses/mit-license.php.*
 **********************************************************************/

#include <stdio.h>
#include <string.h>

#include "include/secp256k1.h"
#include "util.h"
<<<<<<< HEAD
#include "bench.h"

typedef struct {
    secp256k1_context *ctx;
    unsigned char msg[32];
    unsigned char key[32];
    unsigned char sig[72];
    size_t siglen;
    unsigned char pubkey[33];
    size_t pubkeylen;
} benchmark_verify_t;

static void benchmark_verify(void* arg) {
    int i;
    benchmark_verify_t* data = (benchmark_verify_t*)arg;

    for (i = 0; i < 20000; i++) {
        secp256k1_pubkey pubkey;
        secp256k1_ecdsa_signature sig;
        data->sig[data->siglen - 1] ^= (i & 0xFF);
        data->sig[data->siglen - 2] ^= ((i >> 8) & 0xFF);
        data->sig[data->siglen - 3] ^= ((i >> 16) & 0xFF);
        CHECK(secp256k1_ec_pubkey_parse(data->ctx, &pubkey, data->pubkey, data->pubkeylen) == 1);
        CHECK(secp256k1_ecdsa_signature_parse_der(data->ctx, &sig, data->sig, data->siglen) == 1);
        CHECK(secp256k1_ecdsa_verify(data->ctx, &sig, data->msg, &pubkey) == (i == 0));
        data->sig[data->siglen - 1] ^= (i & 0xFF);
        data->sig[data->siglen - 2] ^= ((i >> 8) & 0xFF);
        data->sig[data->siglen - 3] ^= ((i >> 16) & 0xFF);
    }
}

int main(void) {
    int i;
    secp256k1_pubkey pubkey;
    secp256k1_ecdsa_signature sig;
    benchmark_verify_t data;

    data.ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY);

    for (i = 0; i < 32; i++) {
        data.msg[i] = 1 + i;
    }
    for (i = 0; i < 32; i++) {
        data.key[i] = 33 + i;
    }
    data.siglen = 72;
    CHECK(secp256k1_ecdsa_sign(data.ctx, &sig, data.msg, data.key, NULL, NULL));
    CHECK(secp256k1_ecdsa_signature_serialize_der(data.ctx, data.sig, &data.siglen, &sig));
    CHECK(secp256k1_ec_pubkey_create(data.ctx, &pubkey, data.key));
    data.pubkeylen = 33;
    CHECK(secp256k1_ec_pubkey_serialize(data.ctx, data.pubkey, &data.pubkeylen, &pubkey, SECP256K1_EC_COMPRESSED) == 1);

    run_benchmark("ecdsa_verify", benchmark_verify, NULL, NULL, &data, 10, 20000);

    secp256k1_context_destroy(data.ctx);
=======

int main(void) {
    secp256k1_start(SECP256K1_START_VERIFY);

    unsigned char msg[32];
    unsigned char sig[64];

    for (int i = 0; i < 32; i++) msg[i] = 1 + i;
    for (int i = 0; i < 64; i++) sig[i] = 65 + i;

    unsigned char pubkey[33];
    for (int i=0; i<1000000; i++) {
        int pubkeylen = 33;
        CHECK(secp256k1_ecdsa_recover_compact(msg, 32, sig, pubkey, &pubkeylen, 1, i % 2));
        for (int j = 0; j < 32; j++) {
            sig[j + 32] = msg[j];    /* Move former message to S. */
            msg[j] = sig[j];         /* Move former R to message. */
            sig[j] = pubkey[j + 1];  /* Move recovered pubkey X coordinate to R (which must be a valid X coordinate). */
        }
    }

    static const unsigned char fini[33] = {
        0x02,
        0x52, 0x63, 0xae, 0x9a, 0x9d, 0x47, 0x1f, 0x1a,
        0xb2, 0x36, 0x65, 0x89, 0x11, 0xe7, 0xcc, 0x86,
        0xa3, 0xab, 0x97, 0xb6, 0xf1, 0xaf, 0xfd, 0x8f,
        0x9b, 0x38, 0xb6, 0x18, 0x55, 0xe5, 0xc2, 0x43
    };
    CHECK(memcmp(fini, pubkey, 33) == 0);

    secp256k1_stop();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    return 0;
}
