<<<<<<< HEAD
// Copyright (c) 2014-2017 The GelCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "activemasternode.h"
#include "instantx.h"
#include "key.h"
#include "validation.h"
#include "masternode-sync.h"
#include "masternodeman.h"
#include "messagesigner.h"
#include "net.h"
#include "protocol.h"
#include "spork.h"
#include "sync.h"
#include "txmempool.h"
#include "util.h"
#include "consensus/validation.h"
#include "validationinterface.h"
#ifdef ENABLE_WALLET
#include "wallet/wallet.h"
#endif // ENABLE_WALLET

#include <boost/algorithm/string/replace.hpp>
#include <boost/thread.hpp>

#ifdef ENABLE_WALLET
extern CWallet* pwalletMain;
#endif // ENABLE_WALLET
extern CTxMemPool mempool;

bool fEnableInstantSend = true;
int nInstantSendDepth = DEFAULT_INSTANTSEND_DEPTH;
int nCompleteTXLocks;

CInstantSend instantsend;

// Transaction Locks
//
// step 1) Some node announces intention to lock transaction inputs via "txlreg" message
// step 2) Top COutPointLock::SIGNATURES_TOTAL masternodes per each spent outpoint push "txvote" message
// step 3) Once there are COutPointLock::SIGNATURES_REQUIRED valid "txvote" messages per each spent outpoint
//         for a corresponding "txlreg" message, all outpoints from that tx are treated as locked

//
// CInstantSend
//

void CInstantSend::ProcessMessage(CNode* pfrom, std::string& strCommand, CDataStream& vRecv, CConnman& connman)
{
    if(fLiteMode) return; // disable all GelCoin specific functionality
    if(!sporkManager.IsSporkActive(SPORK_2_INSTANTSEND_ENABLED)) return;

    // NOTE: NetMsgType::TXLOCKREQUEST is handled via ProcessMessage() in main.cpp

    if (strCommand == NetMsgType::TXLOCKVOTE) // InstantSend Transaction Lock Consensus Votes
    {
        if(pfrom->nVersion < MIN_INSTANTSEND_PROTO_VERSION) return;

        CTxLockVote vote;
        vRecv >> vote;


        uint256 nVoteHash = vote.GetHash();

        pfrom->setAskFor.erase(nVoteHash);

        // Ignore any InstantSend messages until masternode list is synced
        if(!masternodeSync.IsMasternodeListSynced()) return;

        LOCK(cs_main);
#ifdef ENABLE_WALLET
        if (pwalletMain)
            LOCK(pwalletMain->cs_wallet);
#endif
        LOCK(cs_instantsend);

        if(mapTxLockVotes.count(nVoteHash)) return;
        mapTxLockVotes.insert(std::make_pair(nVoteHash, vote));

        ProcessTxLockVote(pfrom, vote, connman);

        return;
    }
}

bool CInstantSend::ProcessTxLockRequest(const CTxLockRequest& txLockRequest, CConnman& connman)
{
    LOCK2(cs_main, cs_instantsend);

    uint256 txHash = txLockRequest.GetHash();

    // Check to see if we conflict with existing completed lock
    BOOST_FOREACH(const CTxIn& txin, txLockRequest.vin) {
        std::map<COutPoint, uint256>::iterator it = mapLockedOutpoints.find(txin.prevout);
        if(it != mapLockedOutpoints.end() && it->second != txLockRequest.GetHash()) {
            // Conflicting with complete lock, proceed to see if we should cancel them both
            LogPrintf("CInstantSend::ProcessTxLockRequest -- WARNING: Found conflicting completed Transaction Lock, txid=%s, completed lock txid=%s\n",
                    txLockRequest.GetHash().ToString(), it->second.ToString());
        }
    }

    // Check to see if there are votes for conflicting request,
    // if so - do not fail, just warn user
    BOOST_FOREACH(const CTxIn& txin, txLockRequest.vin) {
        std::map<COutPoint, std::set<uint256> >::iterator it = mapVotedOutpoints.find(txin.prevout);
        if(it != mapVotedOutpoints.end()) {
            BOOST_FOREACH(const uint256& hash, it->second) {
                if(hash != txLockRequest.GetHash()) {
                    LogPrint("instantsend", "CInstantSend::ProcessTxLockRequest -- Double spend attempt! %s\n", txin.prevout.ToStringShort());
                    // do not fail here, let it go and see which one will get the votes to be locked
                    // TODO: notify zmq+script
                }
            }
        }
    }

    if(!CreateTxLockCandidate(txLockRequest)) {
        // smth is not right
        LogPrintf("CInstantSend::ProcessTxLockRequest -- CreateTxLockCandidate failed, txid=%s\n", txHash.ToString());
        return false;
    }
    LogPrintf("CInstantSend::ProcessTxLockRequest -- accepted, txid=%s\n", txHash.ToString());

    // Masternodes will sometimes propagate votes before the transaction is known to the client.
    // If this just happened - lock inputs, resolve conflicting locks, update transaction status
    // forcing external script notification.
    std::map<uint256, CTxLockCandidate>::iterator itLockCandidate = mapTxLockCandidates.find(txHash);
    TryToFinalizeLockCandidate(itLockCandidate->second);

    return true;
}

bool CInstantSend::CreateTxLockCandidate(const CTxLockRequest& txLockRequest)
{
    if(!txLockRequest.IsValid()) return false;

    LOCK(cs_instantsend);

    uint256 txHash = txLockRequest.GetHash();

    std::map<uint256, CTxLockCandidate>::iterator itLockCandidate = mapTxLockCandidates.find(txHash);
    if(itLockCandidate == mapTxLockCandidates.end()) {
        LogPrintf("CInstantSend::CreateTxLockCandidate -- new, txid=%s\n", txHash.ToString());

        CTxLockCandidate txLockCandidate(txLockRequest);
        // all inputs should already be checked by txLockRequest.IsValid() above, just use them now
        BOOST_REVERSE_FOREACH(const CTxIn& txin, txLockRequest.vin) {
            txLockCandidate.AddOutPointLock(txin.prevout);
        }
        mapTxLockCandidates.insert(std::make_pair(txHash, txLockCandidate));
    } else if (!itLockCandidate->second.txLockRequest) {
        // i.e. empty Transaction Lock Candidate was created earlier, let's update it with actual data
        itLockCandidate->second.txLockRequest = txLockRequest;
        if (itLockCandidate->second.IsTimedOut()) {
            LogPrintf("CInstantSend::CreateTxLockCandidate -- timed out, txid=%s\n", txHash.ToString());
            return false;
        }
        LogPrintf("CInstantSend::CreateTxLockCandidate -- update empty, txid=%s\n", txHash.ToString());

        // all inputs should already be checked by txLockRequest.IsValid() above, just use them now
        BOOST_REVERSE_FOREACH(const CTxIn& txin, txLockRequest.vin) {
            itLockCandidate->second.AddOutPointLock(txin.prevout);
        }
    } else {
        LogPrint("instantsend", "CInstantSend::CreateTxLockCandidate -- seen, txid=%s\n", txHash.ToString());
    }

    return true;
}

void CInstantSend::CreateEmptyTxLockCandidate(const uint256& txHash)
{
    if (mapTxLockCandidates.find(txHash) != mapTxLockCandidates.end())
        return;
    LogPrintf("CInstantSend::CreateEmptyTxLockCandidate -- new, txid=%s\n", txHash.ToString());
    const CTxLockRequest txLockRequest = CTxLockRequest();
    mapTxLockCandidates.insert(std::make_pair(txHash, CTxLockCandidate(txLockRequest)));
}

void CInstantSend::Vote(const uint256& txHash, CConnman& connman)
{
    AssertLockHeld(cs_main);
    LOCK(cs_instantsend);

    std::map<uint256, CTxLockCandidate>::iterator itLockCandidate = mapTxLockCandidates.find(txHash);
    if (itLockCandidate == mapTxLockCandidates.end()) return;
    Vote(itLockCandidate->second, connman);
    // Let's see if our vote changed smth
    TryToFinalizeLockCandidate(itLockCandidate->second);
}

void CInstantSend::Vote(CTxLockCandidate& txLockCandidate, CConnman& connman)
{
    if(!fMasterNode) return;
    if(!sporkManager.IsSporkActive(SPORK_2_INSTANTSEND_ENABLED)) return;

    LOCK2(cs_main, cs_instantsend);

    uint256 txHash = txLockCandidate.GetHash();
    // We should never vote on a Transaction Lock Request that was not (yet) accepted by the mempool
    if(mapLockRequestAccepted.find(txHash) == mapLockRequestAccepted.end()) return;
    // check if we need to vote on this candidate's outpoints,
    // it's possible that we need to vote for several of them
    std::map<COutPoint, COutPointLock>::iterator itOutpointLock = txLockCandidate.mapOutPointLocks.begin();
    while(itOutpointLock != txLockCandidate.mapOutPointLocks.end()) {

        int nPrevoutHeight = GetUTXOHeight(itOutpointLock->first);
        if(nPrevoutHeight == -1) {
            LogPrint("instantsend", "CInstantSend::Vote -- Failed to find UTXO %s\n", itOutpointLock->first.ToStringShort());
            return;
        }

        int nLockInputHeight = nPrevoutHeight + 4;

        int nRank;
        if(!mnodeman.GetMasternodeRank(activeMasternode.outpoint, nRank, nLockInputHeight, MIN_INSTANTSEND_PROTO_VERSION)) {
            LogPrint("instantsend", "CInstantSend::Vote -- Can't calculate rank for masternode %s\n", activeMasternode.outpoint.ToStringShort());
            ++itOutpointLock;
            continue;
        }

        int nSignaturesTotal = COutPointLock::SIGNATURES_TOTAL;
        if(nRank > nSignaturesTotal) {
            LogPrint("instantsend", "CInstantSend::Vote -- Masternode not in the top %d (%d)\n", nSignaturesTotal, nRank);
            ++itOutpointLock;
            continue;
        }

        LogPrint("instantsend", "CInstantSend::Vote -- In the top %d (%d)\n", nSignaturesTotal, nRank);

        std::map<COutPoint, std::set<uint256> >::iterator itVoted = mapVotedOutpoints.find(itOutpointLock->first);

        // Check to see if we already voted for this outpoint,
        // refuse to vote twice or to include the same outpoint in another tx
        bool fAlreadyVoted = false;
        if(itVoted != mapVotedOutpoints.end()) {
            BOOST_FOREACH(const uint256& hash, itVoted->second) {
                std::map<uint256, CTxLockCandidate>::iterator it2 = mapTxLockCandidates.find(hash);
                if(it2->second.HasMasternodeVoted(itOutpointLock->first, activeMasternode.outpoint)) {
                    // we already voted for this outpoint to be included either in the same tx or in a competing one,
                    // skip it anyway
                    fAlreadyVoted = true;
                    LogPrintf("CInstantSend::Vote -- WARNING: We already voted for this outpoint, skipping: txHash=%s, outpoint=%s\n",
                            txHash.ToString(), itOutpointLock->first.ToStringShort());
                    break;
                }
            }
        }
        if(fAlreadyVoted) {
            ++itOutpointLock;
            continue; // skip to the next outpoint
        }

        // we haven't voted for this outpoint yet, let's try to do this now
        CTxLockVote vote(txHash, itOutpointLock->first, activeMasternode.outpoint);

        if(!vote.Sign()) {
            LogPrintf("CInstantSend::Vote -- Failed to sign consensus vote\n");
            return;
        }
        if(!vote.CheckSignature()) {
            LogPrintf("CInstantSend::Vote -- Signature invalid\n");
            return;
        }

        // vote constructed sucessfully, let's store and relay it
        uint256 nVoteHash = vote.GetHash();
        mapTxLockVotes.insert(std::make_pair(nVoteHash, vote));
        if(itOutpointLock->second.AddVote(vote)) {
            LogPrintf("CInstantSend::Vote -- Vote created successfully, relaying: txHash=%s, outpoint=%s, vote=%s\n",
                    txHash.ToString(), itOutpointLock->first.ToStringShort(), nVoteHash.ToString());

            if(itVoted == mapVotedOutpoints.end()) {
                std::set<uint256> setHashes;
                setHashes.insert(txHash);
                mapVotedOutpoints.insert(std::make_pair(itOutpointLock->first, setHashes));
            } else {
                mapVotedOutpoints[itOutpointLock->first].insert(txHash);
                if(mapVotedOutpoints[itOutpointLock->first].size() > 1) {
                    // it's ok to continue, just warn user
                    LogPrintf("CInstantSend::Vote -- WARNING: Vote conflicts with some existing votes: txHash=%s, outpoint=%s, vote=%s\n",
                            txHash.ToString(), itOutpointLock->first.ToStringShort(), nVoteHash.ToString());
                }
            }

            vote.Relay(connman);
        }

        ++itOutpointLock;
    }
}

//received a consensus vote
bool CInstantSend::ProcessTxLockVote(CNode* pfrom, CTxLockVote& vote, CConnman& connman)
{
    // cs_main, cs_wallet and cs_instantsend should be already locked
    AssertLockHeld(cs_main);
#ifdef ENABLE_WALLET
    if (pwalletMain)
        AssertLockHeld(pwalletMain->cs_wallet);
#endif
    AssertLockHeld(cs_instantsend);

    uint256 txHash = vote.GetTxHash();

    if(!vote.IsValid(pfrom, connman)) {
        // could be because of missing MN
        LogPrint("instantsend", "CInstantSend::ProcessTxLockVote -- Vote is invalid, txid=%s\n", txHash.ToString());
        return false;
    }

    // relay valid vote asap
    vote.Relay(connman);

    // Masternodes will sometimes propagate votes before the transaction is known to the client,
    // will actually process only after the lock request itself has arrived

    std::map<uint256, CTxLockCandidate>::iterator it = mapTxLockCandidates.find(txHash);
    if(it == mapTxLockCandidates.end() || !it->second.txLockRequest) {
        if(!mapTxLockVotesOrphan.count(vote.GetHash())) {
            // start timeout countdown after the very first vote
            CreateEmptyTxLockCandidate(txHash);
            mapTxLockVotesOrphan[vote.GetHash()] = vote;
            LogPrint("instantsend", "CInstantSend::ProcessTxLockVote -- Orphan vote: txid=%s  masternode=%s new\n",
                    txHash.ToString(), vote.GetMasternodeOutpoint().ToStringShort());
            bool fReprocess = true;
            std::map<uint256, CTxLockRequest>::iterator itLockRequest = mapLockRequestAccepted.find(txHash);
            if(itLockRequest == mapLockRequestAccepted.end()) {
                itLockRequest = mapLockRequestRejected.find(txHash);
                if(itLockRequest == mapLockRequestRejected.end()) {
                    // still too early, wait for tx lock request
                    fReprocess = false;
                }
            }
            if(fReprocess && IsEnoughOrphanVotesForTx(itLockRequest->second)) {
                // We have enough votes for corresponding lock to complete,
                // tx lock request should already be received at this stage.
                LogPrint("instantsend", "CInstantSend::ProcessTxLockVote -- Found enough orphan votes, reprocessing Transaction Lock Request: txid=%s\n", txHash.ToString());
                ProcessTxLockRequest(itLockRequest->second, connman);
                return true;
            }
        } else {
            LogPrint("instantsend", "CInstantSend::ProcessTxLockVote -- Orphan vote: txid=%s  masternode=%s seen\n",
                    txHash.ToString(), vote.GetMasternodeOutpoint().ToStringShort());
        }

        // This tracks those messages and allows only the same rate as of the rest of the network
        // TODO: make sure this works good enough for multi-quorum

        int nMasternodeOrphanExpireTime = GetTime() + 60*10; // keep time data for 10 minutes
        if(!mapMasternodeOrphanVotes.count(vote.GetMasternodeOutpoint())) {
            mapMasternodeOrphanVotes[vote.GetMasternodeOutpoint()] = nMasternodeOrphanExpireTime;
        } else {
            int64_t nPrevOrphanVote = mapMasternodeOrphanVotes[vote.GetMasternodeOutpoint()];
            if(nPrevOrphanVote > GetTime() && nPrevOrphanVote > GetAverageMasternodeOrphanVoteTime()) {
                LogPrint("instantsend", "CInstantSend::ProcessTxLockVote -- masternode is spamming orphan Transaction Lock Votes: txid=%s  masternode=%s\n",
                        txHash.ToString(), vote.GetMasternodeOutpoint().ToStringShort());
                // Misbehaving(pfrom->id, 1);
                return false;
            }
            // not spamming, refresh
            mapMasternodeOrphanVotes[vote.GetMasternodeOutpoint()] = nMasternodeOrphanExpireTime;
        }

        return true;
    }

    CTxLockCandidate& txLockCandidate = it->second;

    if (txLockCandidate.IsTimedOut()) {
        LogPrint("instantsend", "CInstantSend::ProcessTxLockVote -- too late, Transaction Lock timed out, txid=%s\n", txHash.ToString());
        return false;
    }

    LogPrint("instantsend", "CInstantSend::ProcessTxLockVote -- Transaction Lock Vote, txid=%s\n", txHash.ToString());

    std::map<COutPoint, std::set<uint256> >::iterator it1 = mapVotedOutpoints.find(vote.GetOutpoint());
    if(it1 != mapVotedOutpoints.end()) {
        BOOST_FOREACH(const uint256& hash, it1->second) {
            if(hash != txHash) {
                // same outpoint was already voted to be locked by another tx lock request,
                // let's see if it was the same masternode who voted on this outpoint
                // for another tx lock request
                std::map<uint256, CTxLockCandidate>::iterator it2 = mapTxLockCandidates.find(hash);
                if(it2 !=mapTxLockCandidates.end() && it2->second.HasMasternodeVoted(vote.GetOutpoint(), vote.GetMasternodeOutpoint())) {
                    // yes, it was the same masternode
                    LogPrintf("CInstantSend::ProcessTxLockVote -- masternode sent conflicting votes! %s\n", vote.GetMasternodeOutpoint().ToStringShort());
                    // mark both Lock Candidates as attacked, none of them should complete,
                    // or at least the new (current) one shouldn't even
                    // if the second one was already completed earlier
                    txLockCandidate.MarkOutpointAsAttacked(vote.GetOutpoint());
                    it2->second.MarkOutpointAsAttacked(vote.GetOutpoint());
                    // apply maximum PoSe ban score to this masternode i.e. PoSe-ban it instantly
                    mnodeman.PoSeBan(vote.GetMasternodeOutpoint());
                    // NOTE: This vote must be relayed further to let all other nodes know about such
                    // misbehaviour of this masternode. This way they should also be able to construct
                    // conflicting lock and PoSe-ban this masternode.
                }
            }
        }
        // store all votes, regardless of them being sent by malicious masternode or not
        it1->second.insert(txHash);
    } else {
        std::set<uint256> setHashes;
        setHashes.insert(txHash);
        mapVotedOutpoints.insert(std::make_pair(vote.GetOutpoint(), setHashes));
    }

    if(!txLockCandidate.AddVote(vote)) {
        // this should never happen
        return false;
    }

    int nSignatures = txLockCandidate.CountVotes();
    int nSignaturesMax = txLockCandidate.txLockRequest.GetMaxSignatures();
    LogPrint("instantsend", "CInstantSend::ProcessTxLockVote -- Transaction Lock signatures count: %d/%d, vote hash=%s\n",
            nSignatures, nSignaturesMax, vote.GetHash().ToString());

    TryToFinalizeLockCandidate(txLockCandidate);

    return true;
}

void CInstantSend::ProcessOrphanTxLockVotes(CConnman& connman)
{
    LOCK(cs_main);
#ifdef ENABLE_WALLET
    if (pwalletMain)
        LOCK(pwalletMain->cs_wallet);
#endif
    LOCK(cs_instantsend);

    std::map<uint256, CTxLockVote>::iterator it = mapTxLockVotesOrphan.begin();
    while(it != mapTxLockVotesOrphan.end()) {
        if(ProcessTxLockVote(NULL, it->second, connman)) {
            mapTxLockVotesOrphan.erase(it++);
        } else {
            ++it;
        }
    }
}

bool CInstantSend::IsEnoughOrphanVotesForTx(const CTxLockRequest& txLockRequest)
{
    // There could be a situation when we already have quite a lot of votes
    // but tx lock request still wasn't received. Let's scan through
    // orphan votes to check if this is the case.
    BOOST_FOREACH(const CTxIn& txin, txLockRequest.vin) {
        if(!IsEnoughOrphanVotesForTxAndOutPoint(txLockRequest.GetHash(), txin.prevout)) {
            return false;
        }
    }
    return true;
}

bool CInstantSend::IsEnoughOrphanVotesForTxAndOutPoint(const uint256& txHash, const COutPoint& outpoint)
{
    // Scan orphan votes to check if this outpoint has enough orphan votes to be locked in some tx.
    LOCK2(cs_main, cs_instantsend);
    int nCountVotes = 0;
    std::map<uint256, CTxLockVote>::iterator it = mapTxLockVotesOrphan.begin();
    while(it != mapTxLockVotesOrphan.end()) {
        if(it->second.GetTxHash() == txHash && it->second.GetOutpoint() == outpoint) {
            nCountVotes++;
            if(nCountVotes >= COutPointLock::SIGNATURES_REQUIRED) {
                return true;
            }
        }
        ++it;
    }
    return false;
}

void CInstantSend::TryToFinalizeLockCandidate(const CTxLockCandidate& txLockCandidate)
{
    if(!sporkManager.IsSporkActive(SPORK_2_INSTANTSEND_ENABLED)) return;

    LOCK(cs_main);
#ifdef ENABLE_WALLET
    if (pwalletMain)
        LOCK(pwalletMain->cs_wallet);
#endif
    LOCK(cs_instantsend);

    uint256 txHash = txLockCandidate.txLockRequest.GetHash();
    if(txLockCandidate.IsAllOutPointsReady() && !IsLockedInstantSendTransaction(txHash)) {
        // we have enough votes now
        LogPrint("instantsend", "CInstantSend::TryToFinalizeLockCandidate -- Transaction Lock is ready to complete, txid=%s\n", txHash.ToString());
        if(ResolveConflicts(txLockCandidate)) {
            LockTransactionInputs(txLockCandidate);
            UpdateLockedTransaction(txLockCandidate);
        }
    }
}

void CInstantSend::UpdateLockedTransaction(const CTxLockCandidate& txLockCandidate)
{
    // cs_wallet and cs_instantsend should be already locked
#ifdef ENABLE_WALLET
    if (pwalletMain)
        AssertLockHeld(pwalletMain->cs_wallet);
#endif
    AssertLockHeld(cs_instantsend);

    uint256 txHash = txLockCandidate.GetHash();

    if(!IsLockedInstantSendTransaction(txHash)) return; // not a locked tx, do not update/notify

#ifdef ENABLE_WALLET
    if(pwalletMain && pwalletMain->UpdatedTransaction(txHash)) {
        // bumping this to update UI
        nCompleteTXLocks++;
        // notify an external script once threshold is reached
        std::string strCmd = GetArg("-instantsendnotify", "");
        if(!strCmd.empty()) {
            boost::replace_all(strCmd, "%s", txHash.GetHex());
            boost::thread t(runCommand, strCmd); // thread runs free
        }
    }
#endif

    GetMainSignals().NotifyTransactionLock(txLockCandidate.txLockRequest);

    LogPrint("instantsend", "CInstantSend::UpdateLockedTransaction -- done, txid=%s\n", txHash.ToString());
}

void CInstantSend::LockTransactionInputs(const CTxLockCandidate& txLockCandidate)
{
    if(!sporkManager.IsSporkActive(SPORK_2_INSTANTSEND_ENABLED)) return;

    LOCK(cs_instantsend);

    uint256 txHash = txLockCandidate.GetHash();

    if(!txLockCandidate.IsAllOutPointsReady()) return;

    std::map<COutPoint, COutPointLock>::const_iterator it = txLockCandidate.mapOutPointLocks.begin();

    while(it != txLockCandidate.mapOutPointLocks.end()) {
        mapLockedOutpoints.insert(std::make_pair(it->first, txHash));
        ++it;
    }
    LogPrint("instantsend", "CInstantSend::LockTransactionInputs -- done, txid=%s\n", txHash.ToString());
}

bool CInstantSend::GetLockedOutPointTxHash(const COutPoint& outpoint, uint256& hashRet)
{
    LOCK(cs_instantsend);
    std::map<COutPoint, uint256>::iterator it = mapLockedOutpoints.find(outpoint);
    if(it == mapLockedOutpoints.end()) return false;
    hashRet = it->second;
    return true;
}

bool CInstantSend::ResolveConflicts(const CTxLockCandidate& txLockCandidate)
{
    LOCK2(cs_main, cs_instantsend);

    uint256 txHash = txLockCandidate.GetHash();

    // make sure the lock is ready
    if(!txLockCandidate.IsAllOutPointsReady()) return false;

    LOCK(mempool.cs); // protect mempool.mapNextTx

    BOOST_FOREACH(const CTxIn& txin, txLockCandidate.txLockRequest.vin) {
        uint256 hashConflicting;
        if(GetLockedOutPointTxHash(txin.prevout, hashConflicting) && txHash != hashConflicting) {
            // completed lock which conflicts with another completed one?
            // this means that majority of MNs in the quorum for this specific tx input are malicious!
            std::map<uint256, CTxLockCandidate>::iterator itLockCandidate = mapTxLockCandidates.find(txHash);
            std::map<uint256, CTxLockCandidate>::iterator itLockCandidateConflicting = mapTxLockCandidates.find(hashConflicting);
            if(itLockCandidate == mapTxLockCandidates.end() || itLockCandidateConflicting == mapTxLockCandidates.end()) {
                // safety check, should never really happen
                LogPrintf("CInstantSend::ResolveConflicts -- ERROR: Found conflicting completed Transaction Lock, but one of txLockCandidate-s is missing, txid=%s, conflicting txid=%s\n",
                        txHash.ToString(), hashConflicting.ToString());
                return false;
            }
            LogPrintf("CInstantSend::ResolveConflicts -- WARNING: Found conflicting completed Transaction Lock, dropping both, txid=%s, conflicting txid=%s\n",
                    txHash.ToString(), hashConflicting.ToString());
            CTxLockRequest txLockRequest = itLockCandidate->second.txLockRequest;
            CTxLockRequest txLockRequestConflicting = itLockCandidateConflicting->second.txLockRequest;
            itLockCandidate->second.SetConfirmedHeight(0); // expired
            itLockCandidateConflicting->second.SetConfirmedHeight(0); // expired
            CheckAndRemove(); // clean up
            // AlreadyHave should still return "true" for both of them
            mapLockRequestRejected.insert(make_pair(txHash, txLockRequest));
            mapLockRequestRejected.insert(make_pair(hashConflicting, txLockRequestConflicting));

            // TODO: clean up mapLockRequestRejected later somehow
            //       (not a big issue since we already PoSe ban malicious masternodes
            //        and they won't be able to spam)
            // TODO: ban all malicious masternodes permanently, do not accept anything from them, ever

            // TODO: notify zmq+script about this double-spend attempt
            //       and let merchant cancel/hold the order if it's not too late...

            // can't do anything else, fallback to regular txes
            return false;
        } else if (mempool.mapNextTx.count(txin.prevout)) {
            // check if it's in mempool
            hashConflicting = mempool.mapNextTx[txin.prevout].ptx->GetHash();
            if(txHash == hashConflicting) continue; // matches current, not a conflict, skip to next txin
            // conflicts with tx in mempool
            LogPrintf("CInstantSend::ResolveConflicts -- ERROR: Failed to complete Transaction Lock, conflicts with mempool, txid=%s\n", txHash.ToString());
            return false;
        }
    } // FOREACH
    // No conflicts were found so far, check to see if it was already included in block
    CTransaction txTmp;
    uint256 hashBlock;
    if(GetTransaction(txHash, txTmp, Params().GetConsensus(), hashBlock, true) && hashBlock != uint256()) {
        LogPrint("instantsend", "CInstantSend::ResolveConflicts -- Done, %s is included in block %s\n", txHash.ToString(), hashBlock.ToString());
        return true;
    }
    // Not in block yet, make sure all its inputs are still unspent
    BOOST_FOREACH(const CTxIn& txin, txLockCandidate.txLockRequest.vin) {
        Coin coin;
        if(!GetUTXOCoin(txin.prevout, coin)) {
            // Not in UTXO anymore? A conflicting tx was mined while we were waiting for votes.
            LogPrintf("CInstantSend::ResolveConflicts -- ERROR: Failed to find UTXO %s, can't complete Transaction Lock\n", txin.prevout.ToStringShort());
            return false;
        }
    }
    LogPrint("instantsend", "CInstantSend::ResolveConflicts -- Done, txid=%s\n", txHash.ToString());

    return true;
}

int64_t CInstantSend::GetAverageMasternodeOrphanVoteTime()
{
    LOCK(cs_instantsend);
    // NOTE: should never actually call this function when mapMasternodeOrphanVotes is empty
    if(mapMasternodeOrphanVotes.empty()) return 0;

    std::map<COutPoint, int64_t>::iterator it = mapMasternodeOrphanVotes.begin();
    int64_t total = 0;

    while(it != mapMasternodeOrphanVotes.end()) {
        total+= it->second;
        ++it;
    }

    return total / mapMasternodeOrphanVotes.size();
}

void CInstantSend::CheckAndRemove()
{
    if(!masternodeSync.IsMasternodeListSynced()) return;

    LOCK(cs_instantsend);

    std::map<uint256, CTxLockCandidate>::iterator itLockCandidate = mapTxLockCandidates.begin();

    // remove expired candidates
    while(itLockCandidate != mapTxLockCandidates.end()) {
        CTxLockCandidate &txLockCandidate = itLockCandidate->second;
        uint256 txHash = txLockCandidate.GetHash();
        if(txLockCandidate.IsExpired(nCachedBlockHeight)) {
            LogPrintf("CInstantSend::CheckAndRemove -- Removing expired Transaction Lock Candidate: txid=%s\n", txHash.ToString());
            std::map<COutPoint, COutPointLock>::iterator itOutpointLock = txLockCandidate.mapOutPointLocks.begin();
            while(itOutpointLock != txLockCandidate.mapOutPointLocks.end()) {
                mapLockedOutpoints.erase(itOutpointLock->first);
                mapVotedOutpoints.erase(itOutpointLock->first);
                ++itOutpointLock;
            }
            mapLockRequestAccepted.erase(txHash);
            mapLockRequestRejected.erase(txHash);
            mapTxLockCandidates.erase(itLockCandidate++);
        } else {
            ++itLockCandidate;
        }
    }

    // remove expired votes
    std::map<uint256, CTxLockVote>::iterator itVote = mapTxLockVotes.begin();
    while(itVote != mapTxLockVotes.end()) {
        if(itVote->second.IsExpired(nCachedBlockHeight)) {
            LogPrint("instantsend", "CInstantSend::CheckAndRemove -- Removing expired vote: txid=%s  masternode=%s\n",
                    itVote->second.GetTxHash().ToString(), itVote->second.GetMasternodeOutpoint().ToStringShort());
            mapTxLockVotes.erase(itVote++);
        } else {
            ++itVote;
        }
    }

    // remove timed out orphan votes
    std::map<uint256, CTxLockVote>::iterator itOrphanVote = mapTxLockVotesOrphan.begin();
    while(itOrphanVote != mapTxLockVotesOrphan.end()) {
        if(itOrphanVote->second.IsTimedOut()) {
            LogPrint("instantsend", "CInstantSend::CheckAndRemove -- Removing timed out orphan vote: txid=%s  masternode=%s\n",
                    itOrphanVote->second.GetTxHash().ToString(), itOrphanVote->second.GetMasternodeOutpoint().ToStringShort());
            mapTxLockVotes.erase(itOrphanVote->first);
            mapTxLockVotesOrphan.erase(itOrphanVote++);
        } else {
            ++itOrphanVote;
        }
    }

    // remove invalid votes and votes for failed lock attempts
    itVote = mapTxLockVotes.begin();
    while(itVote != mapTxLockVotes.end()) {
        if(itVote->second.IsFailed()) {
            LogPrint("instantsend", "CInstantSend::CheckAndRemove -- Removing vote for failed lock attempt: txid=%s  masternode=%s\n",
                    itVote->second.GetTxHash().ToString(), itVote->second.GetMasternodeOutpoint().ToStringShort());
            mapTxLockVotes.erase(itVote++);
        } else {
            ++itVote;
        }
    }

    // remove timed out masternode orphan votes (DOS protection)
    std::map<COutPoint, int64_t>::iterator itMasternodeOrphan = mapMasternodeOrphanVotes.begin();
    while(itMasternodeOrphan != mapMasternodeOrphanVotes.end()) {
        if(itMasternodeOrphan->second < GetTime()) {
            LogPrint("instantsend", "CInstantSend::CheckAndRemove -- Removing timed out orphan masternode vote: masternode=%s\n",
                    itMasternodeOrphan->first.ToStringShort());
            mapMasternodeOrphanVotes.erase(itMasternodeOrphan++);
        } else {
            ++itMasternodeOrphan;
        }
    }
    LogPrintf("CInstantSend::CheckAndRemove -- %s\n", ToString());
}

bool CInstantSend::AlreadyHave(const uint256& hash)
{
    LOCK(cs_instantsend);
    return mapLockRequestAccepted.count(hash) ||
            mapLockRequestRejected.count(hash) ||
            mapTxLockVotes.count(hash);
}

void CInstantSend::AcceptLockRequest(const CTxLockRequest& txLockRequest)
{
    LOCK(cs_instantsend);
    mapLockRequestAccepted.insert(make_pair(txLockRequest.GetHash(), txLockRequest));
}

void CInstantSend::RejectLockRequest(const CTxLockRequest& txLockRequest)
{
    LOCK(cs_instantsend);
    mapLockRequestRejected.insert(make_pair(txLockRequest.GetHash(), txLockRequest));
}

bool CInstantSend::HasTxLockRequest(const uint256& txHash)
{
    CTxLockRequest txLockRequestTmp;
    return GetTxLockRequest(txHash, txLockRequestTmp);
}

bool CInstantSend::GetTxLockRequest(const uint256& txHash, CTxLockRequest& txLockRequestRet)
{
    LOCK(cs_instantsend);

    std::map<uint256, CTxLockCandidate>::iterator it = mapTxLockCandidates.find(txHash);
    if(it == mapTxLockCandidates.end()) return false;
    txLockRequestRet = it->second.txLockRequest;

    return true;
}

bool CInstantSend::GetTxLockVote(const uint256& hash, CTxLockVote& txLockVoteRet)
{
    LOCK(cs_instantsend);

    std::map<uint256, CTxLockVote>::iterator it = mapTxLockVotes.find(hash);
    if(it == mapTxLockVotes.end()) return false;
    txLockVoteRet = it->second;

    return true;
}

bool CInstantSend::IsInstantSendReadyToLock(const uint256& txHash)
{
    if(!fEnableInstantSend || fLargeWorkForkFound || fLargeWorkInvalidChainFound ||
        !sporkManager.IsSporkActive(SPORK_2_INSTANTSEND_ENABLED)) return false;

    LOCK(cs_instantsend);
    // There must be a successfully verified lock request
    // and all outputs must be locked (i.e. have enough signatures)
    std::map<uint256, CTxLockCandidate>::iterator it = mapTxLockCandidates.find(txHash);
    return it != mapTxLockCandidates.end() && it->second.IsAllOutPointsReady();
}

bool CInstantSend::IsLockedInstantSendTransaction(const uint256& txHash)
{
    if(!fEnableInstantSend || fLargeWorkForkFound || fLargeWorkInvalidChainFound ||
        !sporkManager.IsSporkActive(SPORK_3_INSTANTSEND_BLOCK_FILTERING)) return false;

    LOCK(cs_instantsend);

    // there must be a lock candidate
    std::map<uint256, CTxLockCandidate>::iterator itLockCandidate = mapTxLockCandidates.find(txHash);
    if(itLockCandidate == mapTxLockCandidates.end()) return false;

    // which should have outpoints
    if(itLockCandidate->second.mapOutPointLocks.empty()) return false;

    // and all of these outputs must be included in mapLockedOutpoints with correct hash
    std::map<COutPoint, COutPointLock>::iterator itOutpointLock = itLockCandidate->second.mapOutPointLocks.begin();
    while(itOutpointLock != itLockCandidate->second.mapOutPointLocks.end()) {
        uint256 hashLocked;
        if(!GetLockedOutPointTxHash(itOutpointLock->first, hashLocked) || hashLocked != txHash) return false;
        ++itOutpointLock;
    }

    return true;
}

int CInstantSend::GetTransactionLockSignatures(const uint256& txHash)
{
    if(!fEnableInstantSend) return -1;
    if(fLargeWorkForkFound || fLargeWorkInvalidChainFound) return -2;
    if(!sporkManager.IsSporkActive(SPORK_2_INSTANTSEND_ENABLED)) return -3;

    LOCK(cs_instantsend);

    std::map<uint256, CTxLockCandidate>::iterator itLockCandidate = mapTxLockCandidates.find(txHash);
    if(itLockCandidate != mapTxLockCandidates.end()) {
        return itLockCandidate->second.CountVotes();
    }

    return -1;
}

int CInstantSend::GetConfirmations(const uint256 &nTXHash)
{
    return IsLockedInstantSendTransaction(nTXHash) ? nInstantSendDepth : 0;
}

bool CInstantSend::IsTxLockCandidateTimedOut(const uint256& txHash)
{
    if(!fEnableInstantSend) return false;

    LOCK(cs_instantsend);

    std::map<uint256, CTxLockCandidate>::iterator itLockCandidate = mapTxLockCandidates.find(txHash);
    if (itLockCandidate != mapTxLockCandidates.end()) {
        return !itLockCandidate->second.IsAllOutPointsReady() &&
                itLockCandidate->second.IsTimedOut();
    }

    return false;
}

void CInstantSend::Relay(const uint256& txHash, CConnman& connman)
{
    LOCK(cs_instantsend);

    std::map<uint256, CTxLockCandidate>::const_iterator itLockCandidate = mapTxLockCandidates.find(txHash);
    if (itLockCandidate != mapTxLockCandidates.end()) {
        itLockCandidate->second.Relay(connman);
    }
}

void CInstantSend::UpdatedBlockTip(const CBlockIndex *pindex)
{
    nCachedBlockHeight = pindex->nHeight;
}

void CInstantSend::SyncTransaction(const CTransaction& tx, const CBlock* pblock)
{
    // Update lock candidates and votes if corresponding tx confirmed
    // or went from confirmed to 0-confirmed or conflicted.

    if (tx.IsCoinBase()) return;

    LOCK2(cs_main, cs_instantsend);

    uint256 txHash = tx.GetHash();

    // When tx is 0-confirmed or conflicted, pblock is NULL and nHeightNew should be set to -1
    CBlockIndex* pblockindex = NULL;
    if(pblock) {
        uint256 blockHash = pblock->GetHash();
        BlockMap::iterator mi = mapBlockIndex.find(blockHash);
        if(mi == mapBlockIndex.end() || !mi->second) {
            // shouldn't happen
            LogPrint("instantsend", "CTxLockRequest::SyncTransaction -- Failed to find block %s\n", blockHash.ToString());
            return;
        }
        pblockindex = mi->second;
    }
    int nHeightNew = pblockindex ? pblockindex->nHeight : -1;

    LogPrint("instantsend", "CInstantSend::SyncTransaction -- txid=%s nHeightNew=%d\n", txHash.ToString(), nHeightNew);

    // Check lock candidates
    std::map<uint256, CTxLockCandidate>::iterator itLockCandidate = mapTxLockCandidates.find(txHash);
    if(itLockCandidate != mapTxLockCandidates.end()) {
        LogPrint("instantsend", "CInstantSend::SyncTransaction -- txid=%s nHeightNew=%d lock candidate updated\n",
                txHash.ToString(), nHeightNew);
        itLockCandidate->second.SetConfirmedHeight(nHeightNew);
        // Loop through outpoint locks
        std::map<COutPoint, COutPointLock>::iterator itOutpointLock = itLockCandidate->second.mapOutPointLocks.begin();
        while(itOutpointLock != itLockCandidate->second.mapOutPointLocks.end()) {
            // Check corresponding lock votes
            std::vector<CTxLockVote> vVotes = itOutpointLock->second.GetVotes();
            std::vector<CTxLockVote>::iterator itVote = vVotes.begin();
            std::map<uint256, CTxLockVote>::iterator it;
            while(itVote != vVotes.end()) {
                uint256 nVoteHash = itVote->GetHash();
                LogPrint("instantsend", "CInstantSend::SyncTransaction -- txid=%s nHeightNew=%d vote %s updated\n",
                        txHash.ToString(), nHeightNew, nVoteHash.ToString());
                it = mapTxLockVotes.find(nVoteHash);
                if(it != mapTxLockVotes.end()) {
                    it->second.SetConfirmedHeight(nHeightNew);
                }
                ++itVote;
            }
            ++itOutpointLock;
        }
    }

    // check orphan votes
    std::map<uint256, CTxLockVote>::iterator itOrphanVote = mapTxLockVotesOrphan.begin();
    while(itOrphanVote != mapTxLockVotesOrphan.end()) {
        if(itOrphanVote->second.GetTxHash() == txHash) {
            LogPrint("instantsend", "CInstantSend::SyncTransaction -- txid=%s nHeightNew=%d vote %s updated\n",
                    txHash.ToString(), nHeightNew, itOrphanVote->first.ToString());
            mapTxLockVotes[itOrphanVote->first].SetConfirmedHeight(nHeightNew);
        }
        ++itOrphanVote;
    }
}

std::string CInstantSend::ToString()
{
    LOCK(cs_instantsend);
    return strprintf("Lock Candidates: %llu, Votes %llu", mapTxLockCandidates.size(), mapTxLockVotes.size());
}

//
// CTxLockRequest
//

bool CTxLockRequest::IsValid() const
{
    if(vout.size() < 1) return false;

    if(vin.size() > WARN_MANY_INPUTS) {
        LogPrint("instantsend", "CTxLockRequest::IsValid -- WARNING: Too many inputs: tx=%s", ToString());
    }

    LOCK(cs_main);
    if(!CheckFinalTx(*this)) {
        LogPrint("instantsend", "CTxLockRequest::IsValid -- Transaction is not final: tx=%s", ToString());
        return false;
    }

    CAmount nValueIn = 0;

    BOOST_FOREACH(const CTxIn& txin, vin) {

        Coin coin;

        if(!GetUTXOCoin(txin.prevout, coin)) {
            LogPrint("instantsend", "CTxLockRequest::IsValid -- Failed to find UTXO %s\n", txin.prevout.ToStringShort());
            return false;
        }

        int nTxAge = chainActive.Height() - coin.nHeight + 1;
        // 1 less than the "send IX" gui requires, in case of a block propagating the network at the time
        int nConfirmationsRequired = INSTANTSEND_CONFIRMATIONS_REQUIRED - 1;

        if(nTxAge < nConfirmationsRequired) {
            LogPrint("instantsend", "CTxLockRequest::IsValid -- outpoint %s too new: nTxAge=%d, nConfirmationsRequired=%d, txid=%s\n",
                    txin.prevout.ToStringShort(), nTxAge, nConfirmationsRequired, GetHash().ToString());
            return false;
        }

        nValueIn += coin.out.nValue;
    }

    if(nValueIn > sporkManager.GetSporkValue(SPORK_5_INSTANTSEND_MAX_VALUE)*COIN) {
        LogPrint("instantsend", "CTxLockRequest::IsValid -- Transaction value too high: nValueIn=%d, tx=%s", nValueIn, ToString());
        return false;
    }

    CAmount nValueOut = GetValueOut();

    if(nValueIn - nValueOut < GetMinFee()) {
        LogPrint("instantsend", "CTxLockRequest::IsValid -- did not include enough fees in transaction: fees=%d, tx=%s", nValueOut - nValueIn, ToString());
        return false;
    }

    return true;
}

CAmount CTxLockRequest::GetMinFee() const
{
    CAmount nMinFee = MIN_FEE;
    return std::max(nMinFee, CAmount(vin.size() * nMinFee));
}

int CTxLockRequest::GetMaxSignatures() const
{
    return vin.size() * COutPointLock::SIGNATURES_TOTAL;
}

//
// CTxLockVote
//

bool CTxLockVote::IsValid(CNode* pnode, CConnman& connman) const
{
    if(!mnodeman.Has(outpointMasternode)) {
        LogPrint("instantsend", "CTxLockVote::IsValid -- Unknown masternode %s\n", outpointMasternode.ToStringShort());
        mnodeman.AskForMN(pnode, outpointMasternode, connman);
        return false;
    }

    Coin coin;
    if(!GetUTXOCoin(outpoint, coin)) {
        LogPrint("instantsend", "CTxLockVote::IsValid -- Failed to find UTXO %s\n", outpoint.ToStringShort());
        return false;
    }

    int nLockInputHeight = coin.nHeight + 4;

    int nRank;
    if(!mnodeman.GetMasternodeRank(outpointMasternode, nRank, nLockInputHeight, MIN_INSTANTSEND_PROTO_VERSION)) {
        //can be caused by past versions trying to vote with an invalid protocol
        LogPrint("instantsend", "CTxLockVote::IsValid -- Can't calculate rank for masternode %s\n", outpointMasternode.ToStringShort());
        return false;
    }
    LogPrint("instantsend", "CTxLockVote::IsValid -- Masternode %s, rank=%d\n", outpointMasternode.ToStringShort(), nRank);

    int nSignaturesTotal = COutPointLock::SIGNATURES_TOTAL;
    if(nRank > nSignaturesTotal) {
        LogPrint("instantsend", "CTxLockVote::IsValid -- Masternode %s is not in the top %d (%d), vote hash=%s\n",
                outpointMasternode.ToStringShort(), nSignaturesTotal, nRank, GetHash().ToString());
        return false;
    }

    if(!CheckSignature()) {
        LogPrintf("CTxLockVote::IsValid -- Signature invalid\n");
=======
#include "uint256.h"
#include "sync.h"
#include "net.h"
#include "key.h"
#include "util.h"
#include "base58.h"
#include "protocol.h"
#include "instantx.h"
#include "masternode.h"
#include "activemasternode.h"
#include "darksend.h"
#include "spork.h"
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

std::map<uint256, CTransaction> mapTxLockReq;
std::map<uint256, CTransaction> mapTxLockReqRejected;
std::map<uint256, CConsensusVote> mapTxLockVote;
std::map<uint256, CTransactionLock> mapTxLocks;
std::map<COutPoint, uint256> mapLockedInputs;
std::map<uint256, int64_t> mapUnknownVotes; //track votes with no tx for DOS
int nCompleteTXLocks;

//txlock - Locks transaction
//
//step 1.) Broadcast intention to lock transaction inputs, "txlreg", CTransaction
//step 2.) Top 10 masternodes, open connect to top 1 masternode. Send "txvote", CTransaction, Signature, Approve
//step 3.) Top 1 masternode, waits for 10 messages. Upon success, sends "txlock'

void ProcessInstantX(CNode* pfrom, const std::string& strCommand, CDataStream& vRecv, bool &isInstantXCommand)
{
    if(fLiteMode) return; //disable all darksend/masternode related functionality
    if(!IsSporkActive(SPORK_1_MASTERNODE_PAYMENTS_ENFORCEMENT)) return;

    if (strCommand == "txlreq") {
        isInstantXCommand = true;
        
        //LogPrintf("ProcessMessageInstantX::txlreq\n");
        CDataStream vMsg(vRecv);
        CTransaction tx;
        vRecv >> tx;

        CInv inv(MSG_TXLOCK_REQUEST, tx.GetHash());
        pfrom->AddInventoryKnown(inv);

        if(mapTxLockReq.count(tx.GetHash()) || mapTxLockReqRejected.count(tx.GetHash())){
            return;
        }

        if(!IsIXTXValid(tx)){
            return;
        }

        BOOST_FOREACH(const CTxOut o, tx.vout){
            if(!o.scriptPubKey.IsNormalPaymentScript()){
                printf ("ProcessMessageInstantX::txlreq - Invalid Script %s\n", tx.ToString().c_str());
                return;
            }
        }

        int nBlockHeight = CreateNewLock(tx);

        bool fMissingInputs = false;
        CValidationState state;


        if (AcceptToMemoryPool(mempool, state, tx, true, &fMissingInputs)) {
            vector<CInv> vInv;
            vInv.push_back(inv);
            LOCK(cs_vNodes);
            BOOST_FOREACH(CNode* pnode, vNodes)
                pnode->PushMessage("inv", vInv);

            DoConsensusVote(tx, nBlockHeight);

            mapTxLockReq.insert(make_pair(tx.GetHash(), tx));

            LogPrintf("ProcessMessageInstantX::txlreq - Transaction Lock Request: %s %s : accepted %s\n",
                pfrom->addr.ToString().c_str(), pfrom->cleanSubVer.c_str(),
                tx.GetHash().ToString().c_str()
            );

            return;

        } else {
            mapTxLockReqRejected.insert(make_pair(tx.GetHash(), tx));

            // can we get the conflicting transaction as proof?

            LogPrintf("ProcessMessageInstantX::txlreq - Transaction Lock Request: %s %s : rejected %s\n",
                pfrom->addr.ToString().c_str(), pfrom->cleanSubVer.c_str(),
                tx.GetHash().ToString().c_str()
            );

            BOOST_FOREACH(const CTxIn& in, tx.vin){
                if(!mapLockedInputs.count(in.prevout)){
                    mapLockedInputs.insert(make_pair(in.prevout, tx.GetHash()));
                }
            }

            // resolve conflicts
            std::map<uint256, CTransactionLock>::iterator i = mapTxLocks.find(tx.GetHash());
            if (i != mapTxLocks.end()){
                //we only care if we have a complete tx lock
                if((*i).second.CountSignatures() >= INSTANTX_SIGNATURES_REQUIRED){
                    if(!CheckForConflictingLocks(tx)){
                        LogPrintf("ProcessMessageInstantX::txlreq - Found Existing Complete IX Lock\n");

                        CValidationState state;
                        //DisconnectBlockAndInputs(state, tx);
                        mapTxLockReq.insert(make_pair(tx.GetHash(), tx));
                    }
                }
            }

            return;
        }
    }

    else if (strCommand == "txlvote") { //InstantX Lock Consensus Votes
        isInstantXCommand = true;
        
        CConsensusVote ctx;
        vRecv >> ctx;

        CInv inv(MSG_TXLOCK_VOTE, ctx.GetHash());
        pfrom->AddInventoryKnown(inv);

        if(mapTxLockVote.count(ctx.GetHash())){
            return;
        }

        mapTxLockVote.insert(make_pair(ctx.GetHash(), ctx));

        if(ProcessConsensusVote(ctx)){
            //Spam/Dos protection
            /*
                Masternodes will sometimes propagate votes before the transaction is known to the client.
                This tracks those messages and allows it at the same rate of the rest of the network, if
                a peer violates it, it will simply be ignored
            */
            if(!mapTxLockReq.count(ctx.txHash) && !mapTxLockReqRejected.count(ctx.txHash)){
                if(!mapUnknownVotes.count(ctx.vinMasternode.prevout.hash)){
                    mapUnknownVotes[ctx.vinMasternode.prevout.hash] = GetTime()+(60*10);
                }

                if(mapUnknownVotes[ctx.vinMasternode.prevout.hash] > GetTime() &&
                    mapUnknownVotes[ctx.vinMasternode.prevout.hash] - GetAverageVoteTime() > 60*10){
                        LogPrintf("ProcessMessageInstantX::txlreq - masternode is spamming transaction votes: %s %s\n",
                            ctx.vinMasternode.ToString().c_str(),
                            ctx.txHash.ToString().c_str()
                        );
                        return;
                } else {
                    mapUnknownVotes[ctx.vinMasternode.prevout.hash] = GetTime()+(60*10);
                }
            }
            vector<CInv> vInv;
            vInv.push_back(inv);
            LOCK(cs_vNodes);
            BOOST_FOREACH(CNode* pnode, vNodes)
                pnode->PushMessage("inv", vInv);

        }

        return;
    }
}

bool IsIXTXValid(const CTransaction& txCollateral){
    if(txCollateral.vout.size() < 1) return false;
    if(txCollateral.nLockTime != 0) return false;

    int64_t nValueIn = 0;
    int64_t nValueOut = 0;
    bool missingTx = false;

    BOOST_FOREACH(const CTxOut o, txCollateral.vout)
        nValueOut += o.nValue;

    BOOST_FOREACH(const CTxIn i, txCollateral.vin){
        CTransaction tx2;
        uint256 hash;
        //if(GetTransaction(i.prevout.hash, tx2, hash, true)){
	if(GetTransaction(i.prevout.hash, tx2, hash)){
            if(tx2.vout.size() > i.prevout.n) {
                nValueIn += tx2.vout[i.prevout.n].nValue;
            }
        } else{
            missingTx = true;
        }
    }

    if(nValueOut > GetSporkValue(SPORK_2_MAX_VALUE)*COIN){
        if(fDebug) LogPrintf ("IsIXTXValid - Transaction value too high - %s\n", txCollateral.ToString().c_str());
        return false;
    }

    if(missingTx){
        if(fDebug) LogPrintf ("IsIXTXValid - Unknown inputs in IX transaction - %s\n", txCollateral.ToString().c_str());
        /*
            This happens sometimes for an unknown reason, so we'll return that it's a valid transaction.
            If someone submits an invalid transaction it will be rejected by the network anyway and this isn't
            very common, but we don't want to block IX just because the client can't figure out the fee.
        */
        return true;
    }

    if(nValueIn-nValueOut < COIN*0.01) {
        if(fDebug) LogPrintf ("IsIXTXValid - did not include enough fees in transaction %d\n%s\n", nValueOut-nValueIn, txCollateral.ToString().c_str());
        return false;
    }

    return true;
}

int64_t CreateNewLock(CTransaction tx)
{

    int64_t nTxAge = 0;
    BOOST_REVERSE_FOREACH(CTxIn i, tx.vin){
        nTxAge = GetInputAge(i);
        if(nTxAge < 6)
        {
            LogPrintf("CreateNewLock - Transaction not found / too new: %d / %s\n", nTxAge, tx.GetHash().ToString().c_str());
            return 0;
        }
    }

    /*
        Use a blockheight newer than the input.
        This prevents attackers from using transaction mallibility to predict which masternodes
        they'll use.
    */
    int nBlockHeight = (chainActive.Tip()->nHeight - nTxAge)+4;

    if (!mapTxLocks.count(tx.GetHash())){
        LogPrintf("CreateNewLock - New Transaction Lock %s !\n", tx.GetHash().ToString().c_str());

        CTransactionLock newLock;
        newLock.nBlockHeight = nBlockHeight;
        newLock.nExpiration = GetTime()+(60*60); //locks expire after 15 minutes (6 confirmations)
        newLock.nTimeout = GetTime()+(60*5);
        newLock.txHash = tx.GetHash();
        mapTxLocks.insert(make_pair(tx.GetHash(), newLock));
    } else {
        mapTxLocks[tx.GetHash()].nBlockHeight = nBlockHeight;
        if(fDebug) LogPrintf("CreateNewLock - Transaction Lock Exists %s !\n", tx.GetHash().ToString().c_str());
    }

    return nBlockHeight;
}

// check if we need to vote on this transaction
void DoConsensusVote(CTransaction& tx, int64_t nBlockHeight)
{
    if(!fMasterNode) return;

    int n = GetMasternodeRank(activeMasternode.vin, nBlockHeight, MIN_INSTANTX_PROTO_VERSION);

    if(n == -1)
    {
        if(fDebug) LogPrintf("InstantX::DoConsensusVote - Unknown Masternode\n");
        return;
    }

    if(n > INSTANTX_SIGNATURES_TOTAL)
    {
        if(fDebug) LogPrintf("InstantX::DoConsensusVote - Masternode not in the top %d (%d)\n", INSTANTX_SIGNATURES_TOTAL, n);
        return;
    }
    /*
        nBlockHeight calculated from the transaction is the authoritive source
    */

    if(fDebug) LogPrintf("InstantX::DoConsensusVote - In the top %d (%d)\n", INSTANTX_SIGNATURES_TOTAL, n);

    CConsensusVote ctx;
    ctx.vinMasternode = activeMasternode.vin;
    ctx.txHash = tx.GetHash();
    ctx.nBlockHeight = nBlockHeight;
    if(!ctx.Sign()){
        LogPrintf("InstantX::DoConsensusVote - Failed to sign consensus vote\n");
        return;
    }
    if(!ctx.SignatureValid()) {
        LogPrintf("InstantX::DoConsensusVote - Signature invalid\n");
        return;
    }

    mapTxLockVote[ctx.GetHash()] = ctx;

    CInv inv(MSG_TXLOCK_VOTE, ctx.GetHash());

    vector<CInv> vInv;
    vInv.push_back(inv);
    LOCK(cs_vNodes);
    BOOST_FOREACH(CNode* pnode, vNodes){
        pnode->PushMessage("inv", vInv);
    }

}

//received a consensus vote
bool ProcessConsensusVote(CConsensusVote& ctx)
{
    int n = GetMasternodeRank(ctx.vinMasternode, ctx.nBlockHeight, MIN_INSTANTX_PROTO_VERSION);

    int x = GetMasternodeByVin(ctx.vinMasternode);
    if(x != -1){
        if(fDebug) LogPrintf("InstantX::ProcessConsensusVote - Masternode ADDR %s %d\n", vecMasternodes[x].addr.ToString().c_str(), n);
    }

    if(n == -1)
    {
        //can be caused by past versions trying to vote with an invalid protocol
        if(fDebug) LogPrintf("InstantX::ProcessConsensusVote - Unknown Masternode\n");
        return false;
    }

    if(n > INSTANTX_SIGNATURES_TOTAL)
    {
        if(fDebug) LogPrintf("InstantX::ProcessConsensusVote - Masternode not in the top %d (%d) - %s\n", INSTANTX_SIGNATURES_TOTAL, n, ctx.GetHash().ToString().c_str());
        return false;
    }

    if(!ctx.SignatureValid()) {
        LogPrintf("InstantX::ProcessConsensusVote - Signature invalid\n");
        //don't ban, it could just be a non-synced masternode
        return false;
    }

    if (!mapTxLocks.count(ctx.txHash)){
        LogPrintf("InstantX::ProcessConsensusVote - New Transaction Lock %s !\n", ctx.txHash.ToString().c_str());

        CTransactionLock newLock;
        newLock.nBlockHeight = 0;
        newLock.nExpiration = GetTime()+(60*60);
        newLock.nTimeout = GetTime()+(60*5);
        newLock.txHash = ctx.txHash;
        mapTxLocks.insert(make_pair(ctx.txHash, newLock));
    } else {
        if(fDebug) LogPrintf("InstantX::ProcessConsensusVote - Transaction Lock Exists %s !\n", ctx.txHash.ToString().c_str());
    }

    //compile consessus vote
    std::map<uint256, CTransactionLock>::iterator i = mapTxLocks.find(ctx.txHash);
    if (i != mapTxLocks.end()){
        (*i).second.AddSignature(ctx);

#ifdef ENABLE_WALLET
        if(pwalletMain){
            //when we get back signatures, we'll count them as requests. Otherwise the client will think it didn't propagate.
            if(pwalletMain->mapRequestCount.count(ctx.txHash))
                pwalletMain->mapRequestCount[ctx.txHash]++;
        }
#endif

        if(fDebug) LogPrintf("InstantX::ProcessConsensusVote - Transaction Lock Votes %d - %s !\n", (*i).second.CountSignatures(), ctx.GetHash().ToString().c_str());

        if((*i).second.CountSignatures() >= INSTANTX_SIGNATURES_REQUIRED){
            if(fDebug) LogPrintf("InstantX::ProcessConsensusVote - Transaction Lock Is Complete %s !\n", (*i).second.GetHash().ToString().c_str());

            CTransaction& tx = mapTxLockReq[ctx.txHash];
            if(!CheckForConflictingLocks(tx)){

#ifdef ENABLE_WALLET
                if(pwalletMain){
                    pwalletMain->UpdatedTransaction((*i).second.txHash);
                        nCompleteTXLocks++;
                    
                }
#endif

                if(mapTxLockReq.count(ctx.txHash)){
                    BOOST_FOREACH(const CTxIn& in, tx.vin){
                        if(!mapLockedInputs.count(in.prevout)){
                            mapLockedInputs.insert(make_pair(in.prevout, ctx.txHash));
                        }
                    }
                }

                // resolve conflicts

                //if this tx lock was rejected, we need to remove the conflicting blocks
                if(mapTxLockReqRejected.count((*i).second.txHash)){
                    CValidationState state;
                    //DisconnectBlockAndInputs(state, mapTxLockReqRejected[(*i).second.txHash]);
                }
            }
        }
        return true;
    }


    return false;
}

bool CheckForConflictingLocks(CTransaction& tx)
{
    /*
        It's possible (very unlikely though) to get 2 conflicting transaction locks approved by the network.
        In that case, they will cancel each other out.

        Blocks could have been rejected during this time, which is OK. After they cancel out, the client will
        rescan the blocks and find they're acceptable and then take the chain with the most work.
    */
    BOOST_FOREACH(const CTxIn& in, tx.vin){
        if(mapLockedInputs.count(in.prevout)){
            if(mapLockedInputs[in.prevout] != tx.GetHash()){
                LogPrintf("InstantX::CheckForConflictingLocks - found two complete conflicting locks - removing both. %s %s", tx.GetHash().ToString().c_str(), mapLockedInputs[in.prevout].ToString().c_str());
                if(mapTxLocks.count(tx.GetHash())) mapTxLocks[tx.GetHash()].nExpiration = GetTime();
                if(mapTxLocks.count(mapLockedInputs[in.prevout])) mapTxLocks[mapLockedInputs[in.prevout]].nExpiration = GetTime();
                return true;
            }
        }
    }

    return false;
}

int64_t GetAverageVoteTime()
{
    std::map<uint256, int64_t>::iterator it = mapUnknownVotes.begin();
    int64_t total = 0;
    int64_t count = 0;

    while(it != mapUnknownVotes.end()) {
        total+= it->second;
        count++;
        it++;
    }

    return total / count;
}

void CleanTransactionLocksList()
{
    if(chainActive.Tip() == NULL) return;

    std::map<uint256, CTransactionLock>::iterator it = mapTxLocks.begin();

    while(it != mapTxLocks.end()) {
        if(GetTime() > it->second.nExpiration){ //keep them for an hour
            LogPrintf("Removing old transaction lock %s\n", it->second.txHash.ToString().c_str());

            if(mapTxLockReq.count(it->second.txHash)){
                CTransaction& tx = mapTxLockReq[it->second.txHash];

                BOOST_FOREACH(const CTxIn& in, tx.vin)
                    mapLockedInputs.erase(in.prevout);

                mapTxLockReq.erase(it->second.txHash);
                mapTxLockReqRejected.erase(it->second.txHash);

                BOOST_FOREACH(CConsensusVote& v, it->second.vecConsensusVotes)
                    mapTxLockVote.erase(v.GetHash());
            }

            mapTxLocks.erase(it++);
        } else {
            it++;
        }
    }

}

uint256 CConsensusVote::GetHash() const
{
    return vinMasternode.prevout.hash + vinMasternode.prevout.n + txHash;
}


bool CConsensusVote::SignatureValid()
{
    std::string errorMessage;
    std::string strMessage = txHash.ToString().c_str() + boost::lexical_cast<std::string>(nBlockHeight);
    //LogPrintf("verify strMessage %s \n", strMessage.c_str());

    int n = GetMasternodeByVin(vinMasternode);

    if(n == -1)
    {
        LogPrintf("InstantX::CConsensusVote::SignatureValid() - Unknown Masternode\n");
        return false;
    }

    //LogPrintf("verify addr %s \n", vecMasternodes[0].addr.ToString().c_str());
    //LogPrintf("verify addr %s \n", vecMasternodes[1].addr.ToString().c_str());
    //LogPrintf("verify addr %d %s \n", n, vecMasternodes[n].addr.ToString().c_str());

    CScript pubkey;
    pubkey =GetScriptForDestination(vecMasternodes[n].pubkey2.GetID());
    CTxDestination address1;
    ExtractDestination(pubkey, address1);
    CBitcoinAddress address2(address1);
    //LogPrintf("verify pubkey2 %s \n", address2.ToString().c_str());

    if(!darkSendSigner.VerifyMessage(vecMasternodes[n].pubkey2, vchMasterNodeSignature, strMessage, errorMessage)) {
        LogPrintf("InstantX::CConsensusVote::SignatureValid() - Verify message failed\n");
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return false;
    }

    return true;
}

<<<<<<< HEAD
uint256 CTxLockVote::GetHash() const
{
    CHashWriter ss(SER_GETHASH, PROTOCOL_VERSION);
    ss << txHash;
    ss << outpoint;
    ss << outpointMasternode;
    return ss.GetHash();
}

bool CTxLockVote::CheckSignature() const
{
    std::string strError;
    std::string strMessage = txHash.ToString() + outpoint.ToStringShort();

    masternode_info_t infoMn;

    if(!mnodeman.GetMasternodeInfo(outpointMasternode, infoMn)) {
        LogPrintf("CTxLockVote::CheckSignature -- Unknown Masternode: masternode=%s\n", outpointMasternode.ToString());
        return false;
    }

    if(!CMessageSigner::VerifyMessage(infoMn.pubKeyMasternode, vchMasternodeSignature, strMessage, strError)) {
        LogPrintf("CTxLockVote::CheckSignature -- VerifyMessage() failed, error: %s\n", strError);
        return false;
    }

    return true;
}

bool CTxLockVote::Sign()
{
    std::string strError;
    std::string strMessage = txHash.ToString() + outpoint.ToStringShort();

    if(!CMessageSigner::SignMessage(strMessage, vchMasternodeSignature, activeMasternode.keyMasternode)) {
        LogPrintf("CTxLockVote::Sign -- SignMessage() failed\n");
        return false;
    }

    if(!CMessageSigner::VerifyMessage(activeMasternode.pubKeyMasternode, vchMasternodeSignature, strMessage, strError)) {
        LogPrintf("CTxLockVote::Sign -- VerifyMessage() failed, error: %s\n", strError);
=======
bool CConsensusVote::Sign()
{
    std::string errorMessage;

    CKey key2;
    CPubKey pubkey2;
    std::string strMessage = txHash.ToString().c_str() + boost::lexical_cast<std::string>(nBlockHeight);
    //LogPrintf("signing strMessage %s \n", strMessage.c_str());
    //LogPrintf("signing privkey %s \n", strMasterNodePrivKey.c_str());

    if(!darkSendSigner.SetKey(strMasterNodePrivKey, errorMessage, key2, pubkey2))
    {
        LogPrintf("CActiveMasternode::RegisterAsMasterNode() - ERROR: Invalid masternodeprivkey: '%s'\n", errorMessage.c_str());
        return false;
    }

    CScript pubkey;
    pubkey =GetScriptForDestination(pubkey2.GetID());
    CTxDestination address1;
    ExtractDestination(pubkey, address1);
    CBitcoinAddress address2(address1);
    //LogPrintf("signing pubkey2 %s \n", address2.ToString().c_str());

    if(!darkSendSigner.SignMessage(strMessage, errorMessage, vchMasterNodeSignature, key2)) {
        LogPrintf("CActiveMasternode::RegisterAsMasterNode() - Sign message failed");
        return false;
    }

    if(!darkSendSigner.VerifyMessage(pubkey2, vchMasterNodeSignature, strMessage, errorMessage)) {
        LogPrintf("CActiveMasternode::RegisterAsMasterNode() - Verify message failed");
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return false;
    }

    return true;
}

<<<<<<< HEAD
void CTxLockVote::Relay(CConnman& connman) const
{
    CInv inv(MSG_TXLOCK_VOTE, GetHash());
    connman.RelayInv(inv);
}

bool CTxLockVote::IsExpired(int nHeight) const
{
    // Locks and votes expire nInstantSendKeepLock blocks after the block corresponding tx was included into.
    return (nConfirmedHeight != -1) && (nHeight - nConfirmedHeight > Params().GetConsensus().nInstantSendKeepLock);
}

bool CTxLockVote::IsTimedOut() const
{
    return GetTime() - nTimeCreated > INSTANTSEND_LOCK_TIMEOUT_SECONDS;
}

bool CTxLockVote::IsFailed() const
{
    return (GetTime() - nTimeCreated > INSTANTSEND_FAILED_TIMEOUT_SECONDS) && !instantsend.IsLockedInstantSendTransaction(GetTxHash());
}

//
// COutPointLock
//

bool COutPointLock::AddVote(const CTxLockVote& vote)
{
    if(mapMasternodeVotes.count(vote.GetMasternodeOutpoint()))
        return false;
    mapMasternodeVotes.insert(std::make_pair(vote.GetMasternodeOutpoint(), vote));
    return true;
}

std::vector<CTxLockVote> COutPointLock::GetVotes() const
{
    std::vector<CTxLockVote> vRet;
    std::map<COutPoint, CTxLockVote>::const_iterator itVote = mapMasternodeVotes.begin();
    while(itVote != mapMasternodeVotes.end()) {
        vRet.push_back(itVote->second);
        ++itVote;
    }
    return vRet;
}

bool COutPointLock::HasMasternodeVoted(const COutPoint& outpointMasternodeIn) const
{
    return mapMasternodeVotes.count(outpointMasternodeIn);
}

void COutPointLock::Relay(CConnman& connman) const
{
    std::map<COutPoint, CTxLockVote>::const_iterator itVote = mapMasternodeVotes.begin();
    while(itVote != mapMasternodeVotes.end()) {
        itVote->second.Relay(connman);
        ++itVote;
    }
}

//
// CTxLockCandidate
//

void CTxLockCandidate::AddOutPointLock(const COutPoint& outpoint)
{
    mapOutPointLocks.insert(make_pair(outpoint, COutPointLock(outpoint)));
}

void CTxLockCandidate::MarkOutpointAsAttacked(const COutPoint& outpoint)
{
    std::map<COutPoint, COutPointLock>::iterator it = mapOutPointLocks.find(outpoint);
    if(it != mapOutPointLocks.end())
        it->second.MarkAsAttacked();
}

bool CTxLockCandidate::AddVote(const CTxLockVote& vote)
{
    std::map<COutPoint, COutPointLock>::iterator it = mapOutPointLocks.find(vote.GetOutpoint());
    if(it == mapOutPointLocks.end()) return false;
    return it->second.AddVote(vote);
}

bool CTxLockCandidate::IsAllOutPointsReady() const
{
    if(mapOutPointLocks.empty()) return false;

    std::map<COutPoint, COutPointLock>::const_iterator it = mapOutPointLocks.begin();
    while(it != mapOutPointLocks.end()) {
        if(!it->second.IsReady()) return false;
        ++it;
    }
    return true;
}

bool CTxLockCandidate::HasMasternodeVoted(const COutPoint& outpointIn, const COutPoint& outpointMasternodeIn)
{
    std::map<COutPoint, COutPointLock>::iterator it = mapOutPointLocks.find(outpointIn);
    return it !=mapOutPointLocks.end() && it->second.HasMasternodeVoted(outpointMasternodeIn);
}

int CTxLockCandidate::CountVotes() const
{
    // Note: do NOT use vote count to figure out if tx is locked, use IsAllOutPointsReady() instead
    int nCountVotes = 0;
    std::map<COutPoint, COutPointLock>::const_iterator it = mapOutPointLocks.begin();
    while(it != mapOutPointLocks.end()) {
        nCountVotes += it->second.CountVotes();
        ++it;
    }
    return nCountVotes;
}

bool CTxLockCandidate::IsExpired(int nHeight) const
{
    // Locks and votes expire nInstantSendKeepLock blocks after the block corresponding tx was included into.
    return (nConfirmedHeight != -1) && (nHeight - nConfirmedHeight > Params().GetConsensus().nInstantSendKeepLock);
}

bool CTxLockCandidate::IsTimedOut() const
{
    return GetTime() - nTimeCreated > INSTANTSEND_LOCK_TIMEOUT_SECONDS;
}

void CTxLockCandidate::Relay(CConnman& connman) const
{
    connman.RelayTransaction(txLockRequest);
    std::map<COutPoint, COutPointLock>::const_iterator itOutpointLock = mapOutPointLocks.begin();
    while(itOutpointLock != mapOutPointLocks.end()) {
        itOutpointLock->second.Relay(connman);
        ++itOutpointLock;
    }
=======

bool CTransactionLock::SignaturesValid()
{

    BOOST_FOREACH(CConsensusVote vote, vecConsensusVotes)
    {
        int n = GetMasternodeRank(vote.vinMasternode, vote.nBlockHeight, MIN_INSTANTX_PROTO_VERSION);

        if(n == -1)
        {
            LogPrintf("InstantX::DoConsensusVote - Unknown Masternode\n");
            return false;
        }

        if(n > INSTANTX_SIGNATURES_TOTAL)
        {
            LogPrintf("InstantX::DoConsensusVote - Masternode not in the top %s\n", INSTANTX_SIGNATURES_TOTAL);
            return false;
        }

        if(!vote.SignatureValid()){
            LogPrintf("InstantX::CTransactionLock::SignaturesValid - Signature not valid\n");
            return false;
        }
    }

    return true;
}

void CTransactionLock::AddSignature(CConsensusVote& cv)
{
    vecConsensusVotes.push_back(cv);
}

int CTransactionLock::CountSignatures()
{
    /*
        Only count signatures where the BlockHeight matches the transaction's blockheight.
        The votes have no proof it's the correct blockheight
    */

    if(nBlockHeight == 0) return -1;

    int n = 0;
    BOOST_FOREACH(CConsensusVote v, vecConsensusVotes){
        if(v.nBlockHeight == nBlockHeight){
            n++;
        }
    }
    return n;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}
