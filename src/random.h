<<<<<<< HEAD
// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2009-2010 Satoshi Nakamoto             -*- c++ -*-
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_RANDOM_H
#define BITCOIN_RANDOM_H

#include "uint256.h"

#include <stdint.h>

/**
 * Seed OpenSSL PRNG with additional entropy data
 */
void RandAddSeed();
void RandAddSeedPerfmon();

/**
 * Functions to gather random data via the OpenSSL PRNG
 */
void GetRandBytes(unsigned char* buf, int num);
uint64_t GetRand(uint64_t nMax);
int GetRandInt(int nMax);
uint256 GetRandHash();

/**
 * Seed insecure_rand using the random pool.
 * @param Deterministic Use a deterministic seed
 */
void seed_insecure_rand(bool fDeterministic = false);

/**
 * MWC RNG of George Marsaglia
 * This is intended to be fast. It has a period of 2^59.3, though the
 * least significant 16 bits only have a period of about 2^30.1.
 *
 * @return random value
 */
extern uint32_t insecure_rand_Rz;
extern uint32_t insecure_rand_Rw;
static inline uint32_t insecure_rand(void)
{
    insecure_rand_Rz = 36969 * (insecure_rand_Rz & 65535) + (insecure_rand_Rz >> 16);
    insecure_rand_Rw = 18000 * (insecure_rand_Rw & 65535) + (insecure_rand_Rw >> 16);
    return (insecure_rand_Rw << 16) + insecure_rand_Rz;
}

<<<<<<< HEAD
/**
 * PRNG initialized from secure entropy based RNG
 */
class InsecureRand
{
private:
    uint32_t nRz;
    uint32_t nRw;
    bool fDeterministic;

public:
    InsecureRand(bool _fDeterministic = false);

   /**
    * MWC RNG of George Marsaglia
    * This is intended to be fast. It has a period of 2^59.3, though the
    * least significant 16 bits only have a period of about 2^30.1.
    *
    * @return random value < nMax
    */
    int64_t operator()(int64_t nMax)
    {
        nRz = 36969 * (nRz & 65535) + (nRz >> 16);
        nRw = 18000 * (nRw & 65535) + (nRw >> 16);
        return ((nRw << 16) + nRz) % nMax;
    }
};

=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#endif // BITCOIN_RANDOM_H
