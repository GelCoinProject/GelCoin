<<<<<<< HEAD
// Copyright (c) 2009-2015 The Bitcoin Core developers
=======
// Copyright (c) 2009-2014 The Bitcoin developers               -*- c++ -*-
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CHECKPOINTS_H
#define BITCOIN_CHECKPOINTS_H

#include "uint256.h"

#include <map>

class CBlockIndex;
<<<<<<< HEAD
struct CCheckpointData;

/**
=======

/** 
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
 * Block-chain checkpoints are compiled-in sanity checks.
 * They are updated every release or three.
 */
namespace Checkpoints
{
<<<<<<< HEAD

//! Returns last CBlockIndex* in mapBlockIndex that is a checkpoint
CBlockIndex* GetLastCheckpoint(const CCheckpointData& data);

double GuessVerificationProgress(const CCheckpointData& data, CBlockIndex* pindex, bool fSigchecks = true);
=======
typedef std::map<int, uint256> MapCheckpoints;

struct CCheckpointData {
    const MapCheckpoints* mapCheckpoints;
    int64_t nTimeLastCheckpoint;
    int64_t nTransactionsLastCheckpoint;
    double fTransactionsPerDay;
};

//! Returns true if block passes checkpoint checks
bool CheckBlock(int nHeight, const uint256& hash);

//! Return conservative estimate of total number of blocks, 0 if unknown
int GetTotalBlocksEstimate();

//! Returns last CBlockIndex* in mapBlockIndex that is a checkpoint
CBlockIndex* GetLastCheckpoint();

double GuessVerificationProgress(CBlockIndex* pindex, bool fSigchecks = true);

extern bool fEnabled;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

} //namespace Checkpoints

#endif // BITCOIN_CHECKPOINTS_H
