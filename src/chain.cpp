// Copyright (c) 2009-2010 Satoshi Nakamoto
<<<<<<< HEAD
// Copyright (c) 2009-2014 The Bitcoin Core developers
=======
// Copyright (c) 2009-2014 The Bitcoin developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chain.h"

using namespace std;

/**
 * CChain implementation
 */
<<<<<<< HEAD
void CChain::SetTip(CBlockIndex *pindex) {
=======
void CChain::SetTip(CBlockIndex* pindex)
{
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    if (pindex == NULL) {
        vChain.clear();
        return;
    }
    vChain.resize(pindex->nHeight + 1);
    while (pindex && vChain[pindex->nHeight] != pindex) {
        vChain[pindex->nHeight] = pindex;
        pindex = pindex->pprev;
    }
}

<<<<<<< HEAD
CBlockLocator CChain::GetLocator(const CBlockIndex *pindex) const {
=======
CBlockLocator CChain::GetLocator(const CBlockIndex* pindex) const
{
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    int nStep = 1;
    std::vector<uint256> vHave;
    vHave.reserve(32);

    if (!pindex)
        pindex = Tip();
    while (pindex) {
        vHave.push_back(pindex->GetBlockHash());
        // Stop when we have added the genesis block.
        if (pindex->nHeight == 0)
            break;
        // Exponentially larger steps back, plus the genesis block.
        int nHeight = std::max(pindex->nHeight - nStep, 0);
        if (Contains(pindex)) {
            // Use O(1) CChain index if possible.
            pindex = (*this)[nHeight];
        } else {
            // Otherwise, use O(log n) skiplist.
            pindex = pindex->GetAncestor(nHeight);
        }
        if (vHave.size() > 10)
            nStep *= 2;
    }

    return CBlockLocator(vHave);
}

<<<<<<< HEAD
const CBlockIndex *CChain::FindFork(const CBlockIndex *pindex) const {
    if (pindex == NULL) {
        return NULL;
    }
=======
const CBlockIndex* CChain::FindFork(const CBlockIndex* pindex) const
{
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    if (pindex->nHeight > Height())
        pindex = pindex->GetAncestor(Height());
    while (pindex && !Contains(pindex))
        pindex = pindex->pprev;
    return pindex;
}

<<<<<<< HEAD
/** Turn the lowest '1' bit in the binary representation of a number into a '0'. */
int static inline InvertLowestOne(int n) { return n & (n - 1); }

/** Compute what height to jump back to with the CBlockIndex::pskip pointer. */
int static inline GetSkipHeight(int height) {
    if (height < 2)
        return 0;

    // Determine which height to jump back to. Any number strictly lower than height is acceptable,
    // but the following expression seems to perform well in simulations (max 110 steps to go back
    // up to 2**18 blocks).
    return (height & 1) ? InvertLowestOne(InvertLowestOne(height - 1)) + 1 : InvertLowestOne(height);
}

CBlockIndex* CBlockIndex::GetAncestor(int height)
{
    if (height > nHeight || height < 0)
        return NULL;

    CBlockIndex* pindexWalk = this;
    int heightWalk = nHeight;
    while (heightWalk > height) {
        int heightSkip = GetSkipHeight(heightWalk);
        int heightSkipPrev = GetSkipHeight(heightWalk - 1);
        if (pindexWalk->pskip != NULL &&
            (heightSkip == height ||
             (heightSkip > height && !(heightSkipPrev < heightSkip - 2 &&
                                       heightSkipPrev >= height)))) {
            // Only follow pskip if pprev->pskip isn't better than pskip->pprev.
            pindexWalk = pindexWalk->pskip;
            heightWalk = heightSkip;
        } else {
            assert(pindexWalk->pprev);
            pindexWalk = pindexWalk->pprev;
            heightWalk--;
        }
    }
    return pindexWalk;
}

const CBlockIndex* CBlockIndex::GetAncestor(int height) const
{
    return const_cast<CBlockIndex*>(this)->GetAncestor(height);
}

void CBlockIndex::BuildSkip()
{
    if (pprev)
        pskip = pprev->GetAncestor(GetSkipHeight(nHeight));
}
=======
uint256 CBlockIndex::GetBlockTrust() const
{
    uint256 bnTarget;
    bnTarget.SetCompact(nBits);
    if (bnTarget <= 0)
        return 0;

    if (IsProofOfStake()) {
        // Return trust score as usual
        return (uint256(1) << 256) / (bnTarget + 1);
    } else {
        // Calculate work amount for block
        uint256 bnPoWTrust = ((~uint256(0) >> 20) / (bnTarget + 1));
        return bnPoWTrust > 1 ? bnPoWTrust : 1;
    }
}
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
