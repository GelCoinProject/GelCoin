<<<<<<< HEAD
// Copyright (c) 2014-2017 The GelCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "activemasternode.h"
#include "base58.h"
#include "init.h"
#include "netbase.h"
#include "masternode.h"
#include "masternode-payments.h"
#include "masternode-sync.h"
#include "masternodeman.h"
#include "messagesigner.h"
#include "script/standard.h"
#include "util.h"
#ifdef ENABLE_WALLET
#include "wallet/wallet.h"
#endif // ENABLE_WALLET

#include <boost/lexical_cast.hpp>


CMasternode::CMasternode() :
    masternode_info_t{ MASTERNODE_ENABLED, PROTOCOL_VERSION, GetAdjustedTime()},
    fAllowMixingTx(true)
{}

CMasternode::CMasternode(CService addr, COutPoint outpoint, CPubKey pubKeyCollateralAddress, CPubKey pubKeyMasternode, int nProtocolVersionIn) :
    masternode_info_t{ MASTERNODE_ENABLED, nProtocolVersionIn, GetAdjustedTime(),
                       outpoint, addr, pubKeyCollateralAddress, pubKeyMasternode},
    fAllowMixingTx(true)
{}

CMasternode::CMasternode(const CMasternode& other) :
    masternode_info_t{other},
    lastPing(other.lastPing),
    vchSig(other.vchSig),
    nCollateralMinConfBlockHash(other.nCollateralMinConfBlockHash),
    nBlockLastPaid(other.nBlockLastPaid),
    nPoSeBanScore(other.nPoSeBanScore),
    nPoSeBanHeight(other.nPoSeBanHeight),
    fAllowMixingTx(other.fAllowMixingTx),
    fUnitTest(other.fUnitTest)
{}

CMasternode::CMasternode(const CMasternodeBroadcast& mnb) :
    masternode_info_t{ mnb.nActiveState, mnb.nProtocolVersion, mnb.sigTime,
                       mnb.vin.prevout, mnb.addr, mnb.pubKeyCollateralAddress, mnb.pubKeyMasternode,
                       mnb.sigTime /*nTimeLastWatchdogVote*/},
    lastPing(mnb.lastPing),
    vchSig(mnb.vchSig),
    fAllowMixingTx(true)
{}

//
// When a new masternode broadcast is sent, update our information
//
bool CMasternode::UpdateFromNewBroadcast(CMasternodeBroadcast& mnb, CConnman& connman)
{
    if(mnb.sigTime <= sigTime && !mnb.fRecovery) return false;

    pubKeyMasternode = mnb.pubKeyMasternode;
    sigTime = mnb.sigTime;
    vchSig = mnb.vchSig;
    nProtocolVersion = mnb.nProtocolVersion;
    addr = mnb.addr;
    nPoSeBanScore = 0;
    nPoSeBanHeight = 0;
    nTimeLastChecked = 0;
    int nDos = 0;
    if(mnb.lastPing == CMasternodePing() || (mnb.lastPing != CMasternodePing() && mnb.lastPing.CheckAndUpdate(this, true, nDos, connman))) {
        lastPing = mnb.lastPing;
        mnodeman.mapSeenMasternodePing.insert(std::make_pair(lastPing.GetHash(), lastPing));
    }
    // if it matches our Masternode privkey...
    if(fMasterNode && pubKeyMasternode == activeMasternode.pubKeyMasternode) {
        nPoSeBanScore = -MASTERNODE_POSE_BAN_MAX_SCORE;
        if(nProtocolVersion == PROTOCOL_VERSION) {
            // ... and PROTOCOL_VERSION, then we've been remotely activated ...
            activeMasternode.ManageState(connman);
        } else {
            // ... otherwise we need to reactivate our node, do not add it to the list and do not relay
            // but also do not ban the node we get this message from
            LogPrintf("CMasternode::UpdateFromNewBroadcast -- wrong PROTOCOL_VERSION, re-activate your MN: message nProtocolVersion=%d  PROTOCOL_VERSION=%d\n", nProtocolVersion, PROTOCOL_VERSION);
            return false;
        }
    }
    return true;
}

//
// Deterministically calculate a given "score" for a Masternode depending on how close it's hash is to
// the proof of work for that block. The further away they are the better, the furthest will win the election
// and get paid this block
//
arith_uint256 CMasternode::CalculateScore(const uint256& blockHash)
{
    // Deterministically calculate a "score" for a Masternode based on any given (block)hash
    CHashWriter ss(SER_GETHASH, PROTOCOL_VERSION);
    ss << vin.prevout << nCollateralMinConfBlockHash << blockHash;
    return UintToArith256(ss.GetHash());
}

CMasternode::CollateralStatus CMasternode::CheckCollateral(const COutPoint& outpoint)
{
    int nHeight;
    return CheckCollateral(outpoint, nHeight);
}

CMasternode::CollateralStatus CMasternode::CheckCollateral(const COutPoint& outpoint, int& nHeightRet)
{
    AssertLockHeld(cs_main);

    Coin coin;
    if(!GetUTXOCoin(outpoint, coin)) {
        return COLLATERAL_UTXO_NOT_FOUND;
    }

    if(coin.out.nValue != 1000 * COIN) {
        return COLLATERAL_INVALID_AMOUNT;
    }

    nHeightRet = coin.nHeight;
    return COLLATERAL_OK;
}

void CMasternode::Check(bool fForce)
{
    LOCK(cs);

    if(ShutdownRequested()) return;

    if(!fForce && (GetTime() - nTimeLastChecked < MASTERNODE_CHECK_SECONDS)) return;
    nTimeLastChecked = GetTime();

    LogPrint("masternode", "CMasternode::Check -- Masternode %s is in %s state\n", vin.prevout.ToStringShort(), GetStateString());

    //once spent, stop doing the checks
    if(IsOutpointSpent()) return;

    int nHeight = 0;
    if(!fUnitTest) {
        TRY_LOCK(cs_main, lockMain);
        if(!lockMain) return;

        CollateralStatus err = CheckCollateral(vin.prevout);
        if (err == COLLATERAL_UTXO_NOT_FOUND) {
            nActiveState = MASTERNODE_OUTPOINT_SPENT;
            LogPrint("masternode", "CMasternode::Check -- Failed to find Masternode UTXO, masternode=%s\n", vin.prevout.ToStringShort());
            return;
        }

        nHeight = chainActive.Height();
    }

    if(IsPoSeBanned()) {
        if(nHeight < nPoSeBanHeight) return; // too early?
        // Otherwise give it a chance to proceed further to do all the usual checks and to change its state.
        // Masternode still will be on the edge and can be banned back easily if it keeps ignoring mnverify
        // or connect attempts. Will require few mnverify messages to strengthen its position in mn list.
        LogPrintf("CMasternode::Check -- Masternode %s is unbanned and back in list now\n", vin.prevout.ToStringShort());
        DecreasePoSeBanScore();
    } else if(nPoSeBanScore >= MASTERNODE_POSE_BAN_MAX_SCORE) {
        nActiveState = MASTERNODE_POSE_BAN;
        // ban for the whole payment cycle
        nPoSeBanHeight = nHeight + mnodeman.size();
        LogPrintf("CMasternode::Check -- Masternode %s is banned till block %d now\n", vin.prevout.ToStringShort(), nPoSeBanHeight);
        return;
    }

    int nActiveStatePrev = nActiveState;
    bool fOurMasternode = fMasterNode && activeMasternode.pubKeyMasternode == pubKeyMasternode;

                   // masternode doesn't meet payment protocol requirements ...
    bool fRequireUpdate = nProtocolVersion < mnpayments.GetMinMasternodePaymentsProto() ||
                   // or it's our own node and we just updated it to the new protocol but we are still waiting for activation ...
                   (fOurMasternode && nProtocolVersion < PROTOCOL_VERSION);

    if(fRequireUpdate) {
        nActiveState = MASTERNODE_UPDATE_REQUIRED;
        if(nActiveStatePrev != nActiveState) {
            LogPrint("masternode", "CMasternode::Check -- Masternode %s is in %s state now\n", vin.prevout.ToStringShort(), GetStateString());
        }
        return;
    }

    // keep old masternodes on start, give them a chance to receive updates...
    bool fWaitForPing = !masternodeSync.IsMasternodeListSynced() && !IsPingedWithin(MASTERNODE_MIN_MNP_SECONDS);

    if(fWaitForPing && !fOurMasternode) {
        // ...but if it was already expired before the initial check - return right away
        if(IsExpired() || IsWatchdogExpired() || IsNewStartRequired()) {
            LogPrint("masternode", "CMasternode::Check -- Masternode %s is in %s state, waiting for ping\n", vin.prevout.ToStringShort(), GetStateString());
            return;
        }
    }

    // don't expire if we are still in "waiting for ping" mode unless it's our own masternode
    if(!fWaitForPing || fOurMasternode) {

        if(!IsPingedWithin(MASTERNODE_NEW_START_REQUIRED_SECONDS)) {
            nActiveState = MASTERNODE_NEW_START_REQUIRED;
            if(nActiveStatePrev != nActiveState) {
                LogPrint("masternode", "CMasternode::Check -- Masternode %s is in %s state now\n", vin.prevout.ToStringShort(), GetStateString());
            }
            return;
        }

        bool fWatchdogActive = masternodeSync.IsSynced() && mnodeman.IsWatchdogActive();
        bool fWatchdogExpired = (fWatchdogActive && ((GetAdjustedTime() - nTimeLastWatchdogVote) > MASTERNODE_WATCHDOG_MAX_SECONDS));

        LogPrint("masternode", "CMasternode::Check -- outpoint=%s, nTimeLastWatchdogVote=%d, GetAdjustedTime()=%d, fWatchdogExpired=%d\n",
                vin.prevout.ToStringShort(), nTimeLastWatchdogVote, GetAdjustedTime(), fWatchdogExpired);

        if(fWatchdogExpired) {
            nActiveState = MASTERNODE_WATCHDOG_EXPIRED;
            if(nActiveStatePrev != nActiveState) {
                LogPrint("masternode", "CMasternode::Check -- Masternode %s is in %s state now\n", vin.prevout.ToStringShort(), GetStateString());
            }
            return;
        }

        if(!IsPingedWithin(MASTERNODE_EXPIRATION_SECONDS)) {
            nActiveState = MASTERNODE_EXPIRED;
            if(nActiveStatePrev != nActiveState) {
                LogPrint("masternode", "CMasternode::Check -- Masternode %s is in %s state now\n", vin.prevout.ToStringShort(), GetStateString());
            }
            return;
        }
    }

    if(lastPing.sigTime - sigTime < MASTERNODE_MIN_MNP_SECONDS) {
        nActiveState = MASTERNODE_PRE_ENABLED;
        if(nActiveStatePrev != nActiveState) {
            LogPrint("masternode", "CMasternode::Check -- Masternode %s is in %s state now\n", vin.prevout.ToStringShort(), GetStateString());
        }
        return;
    }

    nActiveState = MASTERNODE_ENABLED; // OK
    if(nActiveStatePrev != nActiveState) {
        LogPrint("masternode", "CMasternode::Check -- Masternode %s is in %s state now\n", vin.prevout.ToStringShort(), GetStateString());
    }
}

bool CMasternode::IsInputAssociatedWithPubkey()
{
    CScript payee;
    payee = GetScriptForDestination(pubKeyCollateralAddress.GetID());

    CTransaction tx;
    uint256 hash;
    if(GetTransaction(vin.prevout.hash, tx, Params().GetConsensus(), hash, true)) {
        BOOST_FOREACH(CTxOut out, tx.vout)
            if(out.nValue == 1000*COIN && out.scriptPubKey == payee) return true;
    }

    return false;
}

bool CMasternode::IsValidNetAddr()
{
    return IsValidNetAddr(addr);
}

bool CMasternode::IsValidNetAddr(CService addrIn)
{
    // TODO: regtest is fine with any addresses for now,
    // should probably be a bit smarter if one day we start to implement tests for this
    return Params().NetworkIDString() == CBaseChainParams::REGTEST ||
            (addrIn.IsIPv4() && IsReachable(addrIn) && addrIn.IsRoutable());
}

masternode_info_t CMasternode::GetInfo()
{
    masternode_info_t info{*this};
    info.nTimeLastPing = lastPing.sigTime;
    info.fInfoValid = true;
    return info;
}

std::string CMasternode::StateToString(int nStateIn)
{
    switch(nStateIn) {
        case MASTERNODE_PRE_ENABLED:            return "PRE_ENABLED";
        case MASTERNODE_ENABLED:                return "ENABLED";
        case MASTERNODE_EXPIRED:                return "EXPIRED";
        case MASTERNODE_OUTPOINT_SPENT:         return "OUTPOINT_SPENT";
        case MASTERNODE_UPDATE_REQUIRED:        return "UPDATE_REQUIRED";
        case MASTERNODE_WATCHDOG_EXPIRED:       return "WATCHDOG_EXPIRED";
        case MASTERNODE_NEW_START_REQUIRED:     return "NEW_START_REQUIRED";
        case MASTERNODE_POSE_BAN:               return "POSE_BAN";
        default:                                return "UNKNOWN";
    }
}

std::string CMasternode::GetStateString() const
{
    return StateToString(nActiveState);
}

std::string CMasternode::GetStatus() const
{
    // TODO: return smth a bit more human readable here
    return GetStateString();
}

void CMasternode::UpdateLastPaid(const CBlockIndex *pindex, int nMaxBlocksToScanBack)
{
    if(!pindex) return;

    const CBlockIndex *BlockReading = pindex;

    CScript mnpayee = GetScriptForDestination(pubKeyCollateralAddress.GetID());
    // LogPrint("masternode", "CMasternode::UpdateLastPaidBlock -- searching for block with payment to %s\n", vin.prevout.ToStringShort());

    LOCK(cs_mapMasternodeBlocks);

    for (int i = 0; BlockReading && BlockReading->nHeight > nBlockLastPaid && i < nMaxBlocksToScanBack; i++) {
        if(mnpayments.mapMasternodeBlocks.count(BlockReading->nHeight) &&
            mnpayments.mapMasternodeBlocks[BlockReading->nHeight].HasPayeeWithVotes(mnpayee, 2))
        {
            CBlock block;
            if(!ReadBlockFromDisk(block, BlockReading, Params().GetConsensus())) // shouldn't really happen
                continue;

            CAmount nMasternodePayment = GetMasternodePayment(BlockReading->nHeight, block.vtx[0].GetValueOut());

            BOOST_FOREACH(CTxOut txout, block.vtx[0].vout)
                if(mnpayee == txout.scriptPubKey && nMasternodePayment == txout.nValue) {
                    nBlockLastPaid = BlockReading->nHeight;
                    nTimeLastPaid = BlockReading->nTime;
                    LogPrint("masternode", "CMasternode::UpdateLastPaidBlock -- searching for block with payment to %s -- found new %d\n", vin.prevout.ToStringShort(), nBlockLastPaid);
                    return;
                }
        }

        if (BlockReading->pprev == NULL) { assert(BlockReading); break; }
        BlockReading = BlockReading->pprev;
    }

    // Last payment for this masternode wasn't found in latest mnpayments blocks
    // or it was found in mnpayments blocks but wasn't found in the blockchain.
    // LogPrint("masternode", "CMasternode::UpdateLastPaidBlock -- searching for block with payment to %s -- keeping old %d\n", vin.prevout.ToStringShort(), nBlockLastPaid);
}

#ifdef ENABLE_WALLET
bool CMasternodeBroadcast::Create(std::string strService, std::string strKeyMasternode, std::string strTxHash, std::string strOutputIndex, std::string& strErrorRet, CMasternodeBroadcast &mnbRet, bool fOffline)
{
    COutPoint outpoint;
    CPubKey pubKeyCollateralAddressNew;
    CKey keyCollateralAddressNew;
    CPubKey pubKeyMasternodeNew;
    CKey keyMasternodeNew;

    auto Log = [&strErrorRet](std::string sErr)->bool
    {
        strErrorRet = sErr;
        LogPrintf("CMasternodeBroadcast::Create -- %s\n", strErrorRet);
        return false;
    };

    //need correct blocks to send ping
    if (!fOffline && !masternodeSync.IsBlockchainSynced())
        return Log("Sync in progress. Must wait until sync is complete to start Masternode");

    if (!CMessageSigner::GetKeysFromSecret(strKeyMasternode, keyMasternodeNew, pubKeyMasternodeNew))
        return Log(strprintf("Invalid masternode key %s", strKeyMasternode));

    if (!pwalletMain->GetMasternodeOutpointAndKeys(outpoint, pubKeyCollateralAddressNew, keyCollateralAddressNew, strTxHash, strOutputIndex))
        return Log(strprintf("Could not allocate outpoint %s:%s for masternode %s", strTxHash, strOutputIndex, strService));

    CService service;
    if (!Lookup(strService.c_str(), service, 0, false))
        return Log(strprintf("Invalid address %s for masternode.", strService));
    int mainnetDefaultPort = Params(CBaseChainParams::MAIN).GetDefaultPort();
    if (Params().NetworkIDString() == CBaseChainParams::MAIN) {
        if (service.GetPort() != mainnetDefaultPort)
            return Log(strprintf("Invalid port %u for masternode %s, only %d is supported on mainnet.", service.GetPort(), strService, mainnetDefaultPort));
    } else if (service.GetPort() == mainnetDefaultPort)
        return Log(strprintf("Invalid port %u for masternode %s, %d is the only supported on mainnet.", service.GetPort(), strService, mainnetDefaultPort));

    return Create(outpoint, service, keyCollateralAddressNew, pubKeyCollateralAddressNew, keyMasternodeNew, pubKeyMasternodeNew, strErrorRet, mnbRet);
}

bool CMasternodeBroadcast::Create(const COutPoint& outpoint, const CService& service, const CKey& keyCollateralAddressNew, const CPubKey& pubKeyCollateralAddressNew, const CKey& keyMasternodeNew, const CPubKey& pubKeyMasternodeNew, std::string &strErrorRet, CMasternodeBroadcast &mnbRet)
{
    // wait for reindex and/or import to finish
    if (fImporting || fReindex) return false;

    LogPrint("masternode", "CMasternodeBroadcast::Create -- pubKeyCollateralAddressNew = %s, pubKeyMasternodeNew.GetID() = %s\n",
             CBitcoinAddress(pubKeyCollateralAddressNew.GetID()).ToString(),
             pubKeyMasternodeNew.GetID().ToString());

    auto Log = [&strErrorRet,&mnbRet](std::string sErr)->bool
    {
        strErrorRet = sErr;
        LogPrintf("CMasternodeBroadcast::Create -- %s\n", strErrorRet);
        mnbRet = CMasternodeBroadcast();
        return false;
    };

    CMasternodePing mnp(outpoint);
    if (!mnp.Sign(keyMasternodeNew, pubKeyMasternodeNew))
        return Log(strprintf("Failed to sign ping, masternode=%s", outpoint.ToStringShort()));

    mnbRet = CMasternodeBroadcast(service, outpoint, pubKeyCollateralAddressNew, pubKeyMasternodeNew, PROTOCOL_VERSION);

    if (!mnbRet.IsValidNetAddr())
        return Log(strprintf("Invalid IP address, masternode=%s", outpoint.ToStringShort()));

    mnbRet.lastPing = mnp;
    if (!mnbRet.Sign(keyCollateralAddressNew))
        return Log(strprintf("Failed to sign broadcast, masternode=%s", outpoint.ToStringShort()));

    return true;
}
#endif // ENABLE_WALLET

bool CMasternodeBroadcast::SimpleCheck(int& nDos)
{
    nDos = 0;

    // make sure addr is valid
    if(!IsValidNetAddr()) {
        LogPrintf("CMasternodeBroadcast::SimpleCheck -- Invalid addr, rejected: masternode=%s  addr=%s\n",
                    vin.prevout.ToStringShort(), addr.ToString());
        return false;
    }

    // make sure signature isn't in the future (past is OK)
    if (sigTime > GetAdjustedTime() + 60 * 60) {
        LogPrintf("CMasternodeBroadcast::SimpleCheck -- Signature rejected, too far into the future: masternode=%s\n", vin.prevout.ToStringShort());
        nDos = 1;
        return false;
    }

    // empty ping or incorrect sigTime/unknown blockhash
    if(lastPing == CMasternodePing() || !lastPing.SimpleCheck(nDos)) {
        // one of us is probably forked or smth, just mark it as expired and check the rest of the rules
        nActiveState = MASTERNODE_EXPIRED;
    }

    if(nProtocolVersion < mnpayments.GetMinMasternodePaymentsProto()) {
        LogPrintf("CMasternodeBroadcast::SimpleCheck -- ignoring outdated Masternode: masternode=%s  nProtocolVersion=%d\n", vin.prevout.ToStringShort(), nProtocolVersion);
        return false;
    }

    CScript pubkeyScript;
    pubkeyScript = GetScriptForDestination(pubKeyCollateralAddress.GetID());

    if(pubkeyScript.size() != 25) {
        LogPrintf("CMasternodeBroadcast::SimpleCheck -- pubKeyCollateralAddress has the wrong size\n");
        nDos = 100;
        return false;
    }

    CScript pubkeyScript2;
    pubkeyScript2 = GetScriptForDestination(pubKeyMasternode.GetID());

    if(pubkeyScript2.size() != 25) {
        LogPrintf("CMasternodeBroadcast::SimpleCheck -- pubKeyMasternode has the wrong size\n");
        nDos = 100;
        return false;
    }

    if(!vin.scriptSig.empty()) {
        LogPrintf("CMasternodeBroadcast::SimpleCheck -- Ignore Not Empty ScriptSig %s\n",vin.ToString());
        nDos = 100;
        return false;
    }

    int mainnetDefaultPort = Params(CBaseChainParams::MAIN).GetDefaultPort();
    if(Params().NetworkIDString() == CBaseChainParams::MAIN) {
        if(addr.GetPort() != mainnetDefaultPort) return false;
    } else if(addr.GetPort() == mainnetDefaultPort) return false;

    return true;
}

bool CMasternodeBroadcast::Update(CMasternode* pmn, int& nDos, CConnman& connman)
{
    nDos = 0;

    if(pmn->sigTime == sigTime && !fRecovery) {
        // mapSeenMasternodeBroadcast in CMasternodeMan::CheckMnbAndUpdateMasternodeList should filter legit duplicates
        // but this still can happen if we just started, which is ok, just do nothing here.
        return false;
    }

    // this broadcast is older than the one that we already have - it's bad and should never happen
    // unless someone is doing something fishy
    if(pmn->sigTime > sigTime) {
        LogPrintf("CMasternodeBroadcast::Update -- Bad sigTime %d (existing broadcast is at %d) for Masternode %s %s\n",
                      sigTime, pmn->sigTime, vin.prevout.ToStringShort(), addr.ToString());
        return false;
    }

    pmn->Check();

    // masternode is banned by PoSe
    if(pmn->IsPoSeBanned()) {
        LogPrintf("CMasternodeBroadcast::Update -- Banned by PoSe, masternode=%s\n", vin.prevout.ToStringShort());
        return false;
    }

    // IsVnAssociatedWithPubkey is validated once in CheckOutpoint, after that they just need to match
    if(pmn->pubKeyCollateralAddress != pubKeyCollateralAddress) {
        LogPrintf("CMasternodeBroadcast::Update -- Got mismatched pubKeyCollateralAddress and vin\n");
        nDos = 33;
        return false;
    }

    if (!CheckSignature(nDos)) {
        LogPrintf("CMasternodeBroadcast::Update -- CheckSignature() failed, masternode=%s\n", vin.prevout.ToStringShort());
        return false;
    }

    // if ther was no masternode broadcast recently or if it matches our Masternode privkey...
    if(!pmn->IsBroadcastedWithin(MASTERNODE_MIN_MNB_SECONDS) || (fMasterNode && pubKeyMasternode == activeMasternode.pubKeyMasternode)) {
        // take the newest entry
        LogPrintf("CMasternodeBroadcast::Update -- Got UPDATED Masternode entry: addr=%s\n", addr.ToString());
        if(pmn->UpdateFromNewBroadcast(*this, connman)) {
            pmn->Check();
            Relay(connman);
        }
        masternodeSync.BumpAssetLastTime("CMasternodeBroadcast::Update");
    }

    return true;
}

bool CMasternodeBroadcast::CheckOutpoint(int& nDos)
{
    // we are a masternode with the same vin (i.e. already activated) and this mnb is ours (matches our Masternode privkey)
    // so nothing to do here for us
    if(fMasterNode && vin.prevout == activeMasternode.outpoint && pubKeyMasternode == activeMasternode.pubKeyMasternode) {
        return false;
    }

    if (!CheckSignature(nDos)) {
        LogPrintf("CMasternodeBroadcast::CheckOutpoint -- CheckSignature() failed, masternode=%s\n", vin.prevout.ToStringShort());
        return false;
    }

    {
        TRY_LOCK(cs_main, lockMain);
        if(!lockMain) {
            // not mnb fault, let it to be checked again later
            LogPrint("masternode", "CMasternodeBroadcast::CheckOutpoint -- Failed to aquire lock, addr=%s", addr.ToString());
            mnodeman.mapSeenMasternodeBroadcast.erase(GetHash());
            return false;
        }

        int nHeight;
        CollateralStatus err = CheckCollateral(vin.prevout, nHeight);
        if (err == COLLATERAL_UTXO_NOT_FOUND) {
            LogPrint("masternode", "CMasternodeBroadcast::CheckOutpoint -- Failed to find Masternode UTXO, masternode=%s\n", vin.prevout.ToStringShort());
            return false;
        }

        if (err == COLLATERAL_INVALID_AMOUNT) {
            LogPrint("masternode", "CMasternodeBroadcast::CheckOutpoint -- Masternode UTXO should have 1000 GEL, masternode=%s\n", vin.prevout.ToStringShort());
            return false;
        }

        if(chainActive.Height() - nHeight + 1 < Params().GetConsensus().nMasternodeMinimumConfirmations) {
            LogPrintf("CMasternodeBroadcast::CheckOutpoint -- Masternode UTXO must have at least %d confirmations, masternode=%s\n",
                    Params().GetConsensus().nMasternodeMinimumConfirmations, vin.prevout.ToStringShort());
            // maybe we miss few blocks, let this mnb to be checked again later
            mnodeman.mapSeenMasternodeBroadcast.erase(GetHash());
            return false;
        }
        // remember the hash of the block where masternode collateral had minimum required confirmations
        nCollateralMinConfBlockHash = chainActive[nHeight + Params().GetConsensus().nMasternodeMinimumConfirmations - 1]->GetBlockHash();
    }

    LogPrint("masternode", "CMasternodeBroadcast::CheckOutpoint -- Masternode UTXO verified\n");

    // make sure the input that was signed in masternode broadcast message is related to the transaction
    // that spawned the Masternode - this is expensive, so it's only done once per Masternode
    if(!IsInputAssociatedWithPubkey()) {
        LogPrintf("CMasternodeMan::CheckOutpoint -- Got mismatched pubKeyCollateralAddress and vin\n");
        nDos = 33;
        return false;
    }

    // verify that sig time is legit in past
    // should be at least not earlier than block when 1000 GEL tx got nMasternodeMinimumConfirmations
    uint256 hashBlock = uint256();
    CTransaction tx2;
    GetTransaction(vin.prevout.hash, tx2, Params().GetConsensus(), hashBlock, true);
    {
        LOCK(cs_main);
        BlockMap::iterator mi = mapBlockIndex.find(hashBlock);
        if (mi != mapBlockIndex.end() && (*mi).second) {
            CBlockIndex* pMNIndex = (*mi).second; // block for 1000 GEL tx -> 1 confirmation
            CBlockIndex* pConfIndex = chainActive[pMNIndex->nHeight + Params().GetConsensus().nMasternodeMinimumConfirmations - 1]; // block where tx got nMasternodeMinimumConfirmations
            if(pConfIndex->GetBlockTime() > sigTime) {
                LogPrintf("CMasternodeBroadcast::CheckOutpoint -- Bad sigTime %d (%d conf block is at %d) for Masternode %s %s\n",
                          sigTime, Params().GetConsensus().nMasternodeMinimumConfirmations, pConfIndex->GetBlockTime(), vin.prevout.ToStringShort(), addr.ToString());
                return false;
            }
        }
=======
#include "masternode.h"
#include "activemasternode.h"
#include "darksend.h"
#include "primitives/transaction.h"
#include "main.h"
#include "util.h"
#include "addrman.h"
#include <boost/lexical_cast.hpp>
//tt

int CMasterNode::minProtoVersion = MIN_MN_PROTO_VERSION;

CCriticalSection cs_masternodes;

/** The list of active masternodes */
std::vector<CMasterNode> vecMasternodes;
/** Object for who's going to get paid on which blocks */
CMasternodePayments masternodePayments;
// keep track of masternode votes I've seen
map<uint256, CMasternodePaymentWinner> mapSeenMasternodeVotes;
// keep track of the scanning errors I've seen
map<uint256, int> mapSeenMasternodeScanningErrors;
// who's asked for the masternode list and the last time
std::map<CNetAddr, int64_t> askedForMasternodeList;
// which masternodes we've asked for
std::map<COutPoint, int64_t> askedForMasternodeListEntry;
// cache block hashes as we calculate them
std::map<int64_t, uint256> mapCacheBlockHashes;

// manage the masternode connections
void ProcessMasternodeConnections(){
    LOCK(cs_vNodes);

    BOOST_FOREACH(CNode* pnode, vNodes)
                {
                    //if it's our masternode, let it be
                    if(darkSendPool.submittedToMasternode == pnode->addr) continue;

                    if(pnode->fDarkSendMaster){
                        LogPrintf("Closing masternode connection %s \n", pnode->addr.ToString().c_str());
                        pnode->CloseSocketDisconnect();
                    }
                }
}

void ProcessMasternode(CNode* pfrom, const std::string& strCommand, CDataStream& vRecv, bool &isMasternodeCommand)
{

    if (strCommand == "dsee") { //DarkSend Election Entry
        isMasternodeCommand = true;
        
        if(fLiteMode) return; //disable all darksend/masternode related functionality

        bool fIsInitialDownload = IsInitialBlockDownload();
        if(fIsInitialDownload) return;

        CTxIn vin;
        CService addr;
        CPubKey pubkey;
        CPubKey pubkey2;
        vector<unsigned char> vchSig;
        int64_t sigTime;
        int count;
        int current;
        int64_t lastUpdated;
        int protocolVersion;
        std::string strMessage;

        // 70047 and greater
        vRecv >> vin >> addr >> vchSig >> sigTime >> pubkey >> pubkey2 >> count >> current >> lastUpdated >> protocolVersion;

        // make sure signature isn't in the future (past is OK)
        if (sigTime > GetAdjustedTime() + 60 * 60) {
            LogPrintf("dsee - Signature rejected, too far into the future %s\n", vin.ToString().c_str());
            return;
        }

        bool isLocal = addr.IsRFC1918() || addr.IsLocal();
        //if(Params().MineBlocksOnDemand()) isLocal = false;

        std::string vchPubKey(pubkey.begin(), pubkey.end());
        std::string vchPubKey2(pubkey2.begin(), pubkey2.end());

        strMessage = addr.ToString() + boost::lexical_cast<std::string>(sigTime) + vchPubKey + vchPubKey2 + boost::lexical_cast<std::string>(protocolVersion);

        if(protocolVersion < MIN_MN_PROTO_VERSION) {
            LogPrintf("dsee - ignoring outdated masternode %s protocol version %d\n", vin.ToString().c_str(), protocolVersion);
            return;
        }

        CScript pubkeyScript;
        pubkeyScript =GetScriptForDestination(pubkey.GetID());

        if(pubkeyScript.size() != 25) {
            LogPrintf("dsee - pubkey the wrong size\n");
            Misbehaving(pfrom->GetId(), 100);
            return;
        }

        CScript pubkeyScript2;
        pubkeyScript2 =GetScriptForDestination(pubkey2.GetID());

        if(pubkeyScript2.size() != 25) {
            LogPrintf("dsee - pubkey2 the wrong size\n");
            Misbehaving(pfrom->GetId(), 100);
            return;
        }

        std::string errorMessage = "";
        if(!darkSendSigner.VerifyMessage(pubkey, vchSig, strMessage, errorMessage)){
            LogPrintf("dsee - Got bad masternode address signature\n");
            Misbehaving(pfrom->GetId(), 100);
            return;
        }



        //search existing masternode list, this is where we update existing masternodes with new dsee broadcasts
        LOCK(cs_masternodes);
        BOOST_FOREACH(CMasterNode& mn, vecMasternodes) {
                        if(mn.vin.prevout == vin.prevout) {
                            // count == -1 when it's a new entry
                            //   e.g. We don't want the entry relayed/time updated when we're syncing the list
                            // mn.pubkey = pubkey, IsVinAssociatedWithPubkey is validated once below,
                            //   after that they just need to match
                            if(count == -1 && mn.pubkey == pubkey && !mn.UpdatedWithin(MASTERNODE_MIN_DSEE_SECONDS)){
                                mn.UpdateLastSeen();

                                if(mn.now < sigTime){ //take the newest entry
                                    LogPrintf("dsee - Got updated entry for %s\n", addr.ToString().c_str());
                                    mn.pubkey2 = pubkey2;
                                    mn.now = sigTime;
                                    mn.sig = vchSig;
                                    mn.protocolVersion = protocolVersion;
                                    mn.addr = addr;

                                    RelayDarkSendElectionEntry(vin, addr, vchSig, sigTime, pubkey, pubkey2, count, current, lastUpdated, protocolVersion);
                                }
                            }

                            return;
                        }
                    }

        // make sure the vout that was signed is related to the transaction that spawned the masternode
        //  - this is expensive, so it's only done once per masternode
        if(!darkSendSigner.IsVinAssociatedWithPubkey(vin, pubkey)) {
            LogPrintf("dsee - Got mismatched pubkey and vin\n");
            Misbehaving(pfrom->GetId(), 100);
            return;
        }

        if(fDebug) LogPrintf("dsee - Got NEW masternode entry %s\n", addr.ToString().c_str());

        // make sure it's still unspent
        //  - this is checked later by .check() in many places and by ThreadCheckDarkSendPool()

        CValidationState state;
        CTransaction tx = CTransaction();
        CTxOut vout = CTxOut((GetMNCollateral(chainActive.Tip()->nHeight)-1)*COIN, darkSendPool.collateralPubKey);
        tx.vin.push_back(vin);
        tx.vout.push_back(vout);
        //if(AcceptableInputs(mempool, state, tx)){
        bool pfMissingInputs;
        if(AcceptableInputs(mempool, state, tx, false, &pfMissingInputs)){
            if(fDebug) LogPrintf("dsee - Accepted masternode entry %i %i\n", count, current);

            if(GetInputAge(vin) < MASTERNODE_MIN_CONFIRMATIONS){
                LogPrintf("dsee - Input must have least %d confirmations\n", MASTERNODE_MIN_CONFIRMATIONS);
                Misbehaving(pfrom->GetId(), 20);
                return;
            }

            // use this as a peer
            addrman.Add(CAddress(addr), pfrom->addr, 2*60*60);

            // add our masternode
            CMasterNode mn(addr, vin, pubkey, vchSig, sigTime, pubkey2, protocolVersion);
            mn.UpdateLastSeen(lastUpdated);
            vecMasternodes.push_back(mn);

            // if it matches our masternodeprivkey, then we've been remotely activated
            if(pubkey2 == activeMasternode.pubKeyMasternode && protocolVersion == PROTOCOL_VERSION){
                activeMasternode.EnableHotColdMasterNode(vin, addr);
            }

            if(count == -1 && !isLocal)
                RelayDarkSendElectionEntry(vin, addr, vchSig, sigTime, pubkey, pubkey2, count, current, lastUpdated, protocolVersion);

        } else {
            LogPrintf("dsee - Rejected masternode entry %s\n", addr.ToString().c_str());

            int nDoS = 0;
            if (state.IsInvalid(nDoS))
            {
                LogPrintf("dsee - %s from %s %s was not accepted into the memory pool\n", tx.GetHash().ToString().c_str(),
                          pfrom->addr.ToString().c_str(), pfrom->cleanSubVer.c_str());
                if (nDoS > 0)
                    Misbehaving(pfrom->GetId(), nDoS);
            }
        }
    }

    else if (strCommand == "dseep") { //DarkSend Election Entry Ping
        isMasternodeCommand = true;
        
        if(fLiteMode) return; //disable all darksend/masternode related functionality
        bool fIsInitialDownload = IsInitialBlockDownload();
        if(fIsInitialDownload) return;

        CTxIn vin;
        vector<unsigned char> vchSig;
        int64_t sigTime;
        bool stop;
        vRecv >> vin >> vchSig >> sigTime >> stop;

        //LogPrintf("dseep - Received: vin: %s sigTime: %lld stop: %s\n", vin.ToString().c_str(), sigTime, stop ? "true" : "false");

        if (sigTime > GetAdjustedTime() + 60 * 60) {
            LogPrintf("dseep - Signature rejected, too far into the future %s\n", vin.ToString().c_str());
            return;
        }

        if (sigTime <= GetAdjustedTime() - 60 * 60) {
            LogPrintf("dseep - Signature rejected, too far into the past %s - %d %d \n", vin.ToString().c_str(), sigTime, GetAdjustedTime());
            return;
        }

        // see if we have this masternode
        LOCK(cs_masternodes);
        BOOST_FOREACH(CMasterNode& mn, vecMasternodes) {
                        if(mn.vin.prevout == vin.prevout) {
                            // LogPrintf("dseep - Found corresponding mn for vin: %s\n", vin.ToString().c_str());
                            // take this only if it's newer
                            if(mn.lastDseep < sigTime){
                                std::string strMessage = mn.addr.ToString() + boost::lexical_cast<std::string>(sigTime) + boost::lexical_cast<std::string>(stop);

                                std::string errorMessage = "";
                                if(!darkSendSigner.VerifyMessage(mn.pubkey2, vchSig, strMessage, errorMessage)){
                                    LogPrintf("dseep - Got bad masternode address signature %s \n", vin.ToString().c_str());
                                    //Misbehaving(pfrom->GetId(), 100);
                                    return;
                                }

                                mn.lastDseep = sigTime;

                                if(!mn.UpdatedWithin(MASTERNODE_MIN_DSEEP_SECONDS)){
                                    mn.UpdateLastSeen();
                                    if(stop) {
                                        mn.Disable();
                                        mn.Check();
                                    }
                                    RelayDarkSendElectionEntryPing(vin, vchSig, sigTime, stop);
                                }
                            }
                            return;
                        }
                    }

        if(fDebug) LogPrintf("dseep - Couldn't find masternode entry %s\n", vin.ToString().c_str());

        std::map<COutPoint, int64_t>::iterator i = askedForMasternodeListEntry.find(vin.prevout);
        if (i != askedForMasternodeListEntry.end()){
            int64_t t = (*i).second;
            if (GetTime() < t) {
                // we've asked recently
                return;
            }
        }

        // ask for the dsee info once from the node that sent dseep

        LogPrintf("dseep - Asking source node for missing entry %s\n", vin.ToString().c_str());
        pfrom->PushMessage("dseg", vin);
        int64_t askAgain = GetTime()+(60*60*24);
        askedForMasternodeListEntry[vin.prevout] = askAgain;

    } 

    else if (strCommand == "dseg") { //Get masternode list or specific entry
        isMasternodeCommand = true;
        
        if(fLiteMode) return; //disable all darksend/masternode related functionality
        CTxIn vin;
        vRecv >> vin;

        if(vin == CTxIn()) { //only should ask for this once
            //local network
            //Note tor peers show up as local proxied addrs //if(!pfrom->addr.IsRFC1918())//&& !Params().MineBlocksOnDemand())
            //{
            std::map<CNetAddr, int64_t>::iterator i = askedForMasternodeList.find(pfrom->addr);
            if (i != askedForMasternodeList.end())
            {
                int64_t t = (*i).second;
                if (GetTime() < t) {
                    //Misbehaving(pfrom->GetId(), 34);
                    //LogPrintf("dseg - peer already asked me for the list\n");
                    //return;
                }
            }

            int64_t askAgain = GetTime()+(60*60*3);
            askedForMasternodeList[pfrom->addr] = askAgain;
            //}
        } //else, asking for a specific node which is ok

        LOCK(cs_masternodes);
        int count = vecMasternodes.size();
        int i = 0;

        BOOST_FOREACH(CMasterNode mn, vecMasternodes) {

                        if(mn.addr.IsRFC1918()) continue; //local network

                        if(vin == CTxIn()){
                            mn.Check();
                            if(mn.IsEnabled()) {
                                if(fDebug) LogPrintf("dseg - Sending masternode entry - %s \n", mn.addr.ToString().c_str());
                                pfrom->PushMessage("dsee", mn.vin, mn.addr, mn.sig, mn.now, mn.pubkey, mn.pubkey2, count, i, mn.lastTimeSeen, mn.protocolVersion);
                            }
                        } else if (vin == mn.vin) {
                            if(fDebug) LogPrintf("dseg - Sending masternode entry - %s \n", mn.addr.ToString().c_str());
                            pfrom->PushMessage("dsee", mn.vin, mn.addr, mn.sig, mn.now, mn.pubkey, mn.pubkey2, count, i, mn.lastTimeSeen, mn.protocolVersion);
                            LogPrintf("dseg - Sent 1 masternode entries to %s\n", pfrom->addr.ToString().c_str());
                            return;
                        }
                        i++;
                    }

        LogPrintf("dseg - Sent %d masternode entries to %s\n", count, pfrom->addr.ToString().c_str());
    }

    else if (strCommand == "mnget") { //Masternode Payments Request Sync
        isMasternodeCommand = true;
        
        if(fLiteMode) return; //disable all darksend/masternode related functionality

        /*if(pfrom->HasFulfilledRequest("mnget")) {
            LogPrintf("mnget - peer already asked me for the list\n");
            Misbehaving(pfrom->GetId(), 20);
            return;
        }*/

        pfrom->FulfilledRequest("mnget");
        masternodePayments.Sync(pfrom);
        LogPrintf("mnget - Sent masternode winners to %s\n", pfrom->addr.ToString().c_str());
    }


    else if (strCommand == "mnw") { //Masternode Payments Declare Winner
        isMasternodeCommand = true;
        
        //this is required in litemode
        CMasternodePaymentWinner winner;
        int a = 0;
        vRecv >> winner >> a;

        if(chainActive.Tip() == NULL) return;

        uint256 hash = winner.GetHash();
        if(mapSeenMasternodeVotes.count(hash)) {
            if(fDebug) LogPrintf("mnw - seen vote %s Height %d bestHeight %d\n", hash.ToString().c_str(), winner.nBlockHeight, chainActive.Tip()->nHeight);
            return;
        }

        if(winner.nBlockHeight < chainActive.Tip()->nHeight - 10 || winner.nBlockHeight > chainActive.Tip()->nHeight+20){
            LogPrintf("mnw - winner out of range %s Height %d bestHeight %d\n", winner.vin.ToString().c_str(), winner.nBlockHeight, chainActive.Tip()->nHeight);
            return;
        }

        if(winner.vin.nSequence != std::numeric_limits<unsigned int>::max()){
            LogPrintf("mnw - invalid nSequence\n");
            Misbehaving(pfrom->GetId(), 100);
            return;
        }

        LogPrintf("mnw - winning vote  %s Height %d bestHeight %d\n", winner.vin.ToString().c_str(), winner.nBlockHeight, chainActive.Tip()->nHeight);

        if(!masternodePayments.CheckSignature(winner)){
            LogPrintf("mnw - invalid signature\n");
            Misbehaving(pfrom->GetId(), 100);
            return;
        }

        mapSeenMasternodeVotes.insert(make_pair(hash, winner));

        if(masternodePayments.AddWinningMasternode(winner)){
            masternodePayments.Relay(winner);
        }
    }
}

struct CompareValueOnly
{
    bool operator()(const pair<int64_t, CTxIn>& t1,
                    const pair<int64_t, CTxIn>& t2) const
    {
        return t1.first < t2.first;
    }
};

struct CompareValueOnly2
{
    bool operator()(const pair<int64_t, int>& t1,
                    const pair<int64_t, int>& t2) const
    {
        return t1.first < t2.first;
    }
};

int CountMasternodesAboveProtocol(int protocolVersion)
{
    int i = 0;
    LOCK(cs_masternodes);
    BOOST_FOREACH(CMasterNode& mn, vecMasternodes) {
                    if(mn.protocolVersion < protocolVersion) continue;
                    i++;
                }

    return i;

}


int GetMasternodeByVin(CTxIn& vin)
{
    int i = 0;
    LOCK(cs_masternodes);
    BOOST_FOREACH(CMasterNode& mn, vecMasternodes) {
                    if (mn.vin == vin) return i;
                    i++;
                }

    return -1;
}

int GetCurrentMasterNode(int mod, int64_t nBlockHeight, int minProtocol)
{
    int i = 0;
    unsigned int score = 0;
    int winner = -1;
    LOCK(cs_masternodes);
    // scan for winner
    BOOST_FOREACH(CMasterNode mn, vecMasternodes) {
                    mn.Check();
                    if(mn.protocolVersion < minProtocol) continue;
                    if(!mn.IsEnabled()) {
                        i++;
                        continue;
                    }

                    // calculate the score for each masternode
                    uint256 n = mn.CalculateScore(mod, nBlockHeight);
                    unsigned int n2 = 0;
                    memcpy(&n2, &n, sizeof(n2));

                    // determine the winner
                    if(n2 > score){
                        score = n2;
                        winner = i;
                    }
                    i++;
                }

    return winner;
}

int GetMasternodeByRank(int findRank, int64_t nBlockHeight, int minProtocol)
{
    LOCK(cs_masternodes);
    int i = 0;

    std::vector<pair<unsigned int, int> > vecMasternodeScores;

    i = 0;
    BOOST_FOREACH(CMasterNode mn, vecMasternodes) {
                    mn.Check();
                    if(mn.protocolVersion < minProtocol) continue;
                    if(!mn.IsEnabled()) {
                        i++;
                        continue;
                    }

                    uint256 n = mn.CalculateScore(1, nBlockHeight);
                    unsigned int n2 = 0;
                    memcpy(&n2, &n, sizeof(n2));

                    vecMasternodeScores.push_back(make_pair(n2, i));
                    i++;
                }

    sort(vecMasternodeScores.rbegin(), vecMasternodeScores.rend(), CompareValueOnly2());

    int rank = 0;
    BOOST_FOREACH (PAIRTYPE(unsigned int, int)& s, vecMasternodeScores){
                    rank++;
                    if(rank == findRank) return s.second;
                }

    return -1;
}

int GetMasternodeRank(CTxIn& vin, int64_t nBlockHeight, int minProtocol)
{
    LOCK(cs_masternodes);
    std::vector<pair<unsigned int, CTxIn> > vecMasternodeScores;

    BOOST_FOREACH(CMasterNode& mn, vecMasternodes) {
                    mn.Check();

                    if(mn.protocolVersion < minProtocol) continue;
                    if(!mn.IsEnabled()) {
                        continue;
                    }

                    uint256 n = mn.CalculateScore(1, nBlockHeight);
                    unsigned int n2 = 0;
                    memcpy(&n2, &n, sizeof(n2));

                    vecMasternodeScores.push_back(make_pair(n2, mn.vin));
                }

    sort(vecMasternodeScores.rbegin(), vecMasternodeScores.rend(), CompareValueOnly());

    unsigned int rank = 0;
    BOOST_FOREACH (PAIRTYPE(unsigned int, CTxIn)& s, vecMasternodeScores){
                    rank++;
                    if(s.second == vin) {
                        return rank;
                    }
                }

    return -1;
}

//Get the last hash that matches the modulus given. Processed in reverse order
bool GetBlockHash(uint256& hash, int nBlockHeight)
{
    if (chainActive.Tip() == NULL) return false;

    if(nBlockHeight == 0)
        nBlockHeight = chainActive.Tip()->nHeight;

    if(mapCacheBlockHashes.count(nBlockHeight)){
        hash = mapCacheBlockHashes[nBlockHeight];
        return true;
    }

    const CBlockIndex *BlockLastSolved = chainActive.Tip();
    const CBlockIndex *BlockReading = chainActive.Tip();

    if (BlockLastSolved == NULL || BlockLastSolved->nHeight == 0 || chainActive.Tip()->nHeight+1 < nBlockHeight) return false;

    int nBlocksAgo = 0;
    if(nBlockHeight > 0) nBlocksAgo = (chainActive.Tip()->nHeight+1)-nBlockHeight;
    assert(nBlocksAgo >= 0);

    int n = 0;
    for (unsigned int i = 1; BlockReading && BlockReading->nHeight > 0; i++) {
        if(n >= nBlocksAgo){
            hash = BlockReading->GetBlockHash();
            mapCacheBlockHashes[nBlockHeight] = hash;
            return true;
        }
        n++;

        if (BlockReading->pprev == NULL) { assert(BlockReading); break; }
        BlockReading = BlockReading->pprev;
    }

    return false;
}

//
// Deterministically calculate a given "score" for a masternode depending on how close it's hash is to
// the proof of work for that block. The further away they are the better, the furthest will win the election
// and get paid this block
//
uint256 CMasterNode::CalculateScore(int mod, int64_t nBlockHeight)
{
    if(chainActive.Tip() == NULL) return 0;

    uint256 hash = 0;
    uint256 aux = vin.prevout.hash + vin.prevout.n;

    if(!GetBlockHash(hash, nBlockHeight)) return 0;

    uint256 hash2 = Hash(BEGIN(hash), END(hash));
    uint256 hash3 = Hash(BEGIN(hash), END(aux));

    uint256 r = (hash3 > hash2 ? hash3 - hash2 : hash2 - hash3);

    return r;
}

void CMasterNode::Check()
{
    //once spent, stop doing the checks
    if(enabled==3) return;


    if(!UpdatedWithin(MASTERNODE_REMOVAL_SECONDS)){
        enabled = 4;
        return;
    }

    if(!UpdatedWithin(MASTERNODE_EXPIRATION_SECONDS)){
        enabled = 2;
        return;
    }


    if(!unitTest){
        CValidationState state;
        CTransaction tx = CTransaction();
        CTxOut vout = CTxOut((GetMNCollateral(chainActive.Tip()->nHeight)-1)*COIN, darkSendPool.collateralPubKey);
        tx.vin.push_back(vin);
        tx.vout.push_back(vout);

        bool pfMissingInputs;
        if (!AcceptableInputs(mempool, state, tx, false, &pfMissingInputs)) {
            enabled = 3;
            return;
        }
    }

    enabled = 1; // OK
}

bool CMasternodePayments::CheckSignature(CMasternodePaymentWinner& winner)
{
    //note: need to investigate why this is failing
    std::string strMessage = winner.vin.ToString().c_str() + boost::lexical_cast<std::string>(winner.nBlockHeight) + winner.payee.ToString();
    std::string strPubKey = strMainPubKey ;
    CPubKey pubkey(ParseHex(strPubKey));

    std::string errorMessage = "";
    if(!darkSendSigner.VerifyMessage(pubkey, winner.vchSig, strMessage, errorMessage)){
        return false;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }

    return true;
}

<<<<<<< HEAD
bool CMasternodeBroadcast::Sign(const CKey& keyCollateralAddress)
{
    std::string strError;
    std::string strMessage;

    sigTime = GetAdjustedTime();

    strMessage = addr.ToString(false) + boost::lexical_cast<std::string>(sigTime) +
                    pubKeyCollateralAddress.GetID().ToString() + pubKeyMasternode.GetID().ToString() +
                    boost::lexical_cast<std::string>(nProtocolVersion);

    if(!CMessageSigner::SignMessage(strMessage, vchSig, keyCollateralAddress)) {
        LogPrintf("CMasternodeBroadcast::Sign -- SignMessage() failed\n");
        return false;
    }

    if(!CMessageSigner::VerifyMessage(pubKeyCollateralAddress, vchSig, strMessage, strError)) {
        LogPrintf("CMasternodeBroadcast::Sign -- VerifyMessage() failed, error: %s\n", strError);
=======
bool CMasternodePayments::Sign(CMasternodePaymentWinner& winner)
{
    std::string strMessage = winner.vin.ToString().c_str() + boost::lexical_cast<std::string>(winner.nBlockHeight) + winner.payee.ToString();

    CKey key2;
    CPubKey pubkey2;
    std::string errorMessage = "";

    if(!darkSendSigner.SetKey(strMasterPrivKey, errorMessage, key2, pubkey2))
    {
        LogPrintf("CMasternodePayments::Sign - ERROR: Invalid masternodeprivkey: '%s'\n", errorMessage.c_str());
        return false;
    }

    if(!darkSendSigner.SignMessage(strMessage, errorMessage, winner.vchSig, key2)) {
        LogPrintf("CMasternodePayments::Sign - Sign message failed");
        return false;
    }

    if(!darkSendSigner.VerifyMessage(pubkey2, winner.vchSig, strMessage, errorMessage)) {
        LogPrintf("CMasternodePayments::Sign - Verify message failed");
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return false;
    }

    return true;
}

<<<<<<< HEAD
bool CMasternodeBroadcast::CheckSignature(int& nDos)
{
    std::string strMessage;
    std::string strError = "";
    nDos = 0;

    strMessage = addr.ToString(false) + boost::lexical_cast<std::string>(sigTime) +
                    pubKeyCollateralAddress.GetID().ToString() + pubKeyMasternode.GetID().ToString() +
                    boost::lexical_cast<std::string>(nProtocolVersion);

    LogPrint("masternode", "CMasternodeBroadcast::CheckSignature -- strMessage: %s  pubKeyCollateralAddress address: %s  sig: %s\n", strMessage, CBitcoinAddress(pubKeyCollateralAddress.GetID()).ToString(), EncodeBase64(&vchSig[0], vchSig.size()));

    if(!CMessageSigner::VerifyMessage(pubKeyCollateralAddress, vchSig, strMessage, strError)){
        LogPrintf("CMasternodeBroadcast::CheckSignature -- Got bad Masternode announce signature, error: %s\n", strError);
        nDos = 100;
        return false;
    }

    return true;
}

void CMasternodeBroadcast::Relay(CConnman& connman)
{
    // Do not relay until fully synced
    if(!masternodeSync.IsSynced()) {
        LogPrint("masternode", "CMasternodeBroadcast::Relay -- won't relay until fully synced\n");
        return;
    }

    CInv inv(MSG_MASTERNODE_ANNOUNCE, GetHash());
    connman.RelayInv(inv);
}

CMasternodePing::CMasternodePing(const COutPoint& outpoint)
{
    LOCK(cs_main);
    if (!chainActive.Tip() || chainActive.Height() < 12) return;

    vin = CTxIn(outpoint);
    blockHash = chainActive[chainActive.Height() - 12]->GetBlockHash();
    sigTime = GetAdjustedTime();
}

bool CMasternodePing::Sign(const CKey& keyMasternode, const CPubKey& pubKeyMasternode)
{
    std::string strError;
    std::string strMasterNodeSignMessage;

    // TODO: add sentinel data
    sigTime = GetAdjustedTime();
    std::string strMessage = vin.ToString() + blockHash.ToString() + boost::lexical_cast<std::string>(sigTime);

    if(!CMessageSigner::SignMessage(strMessage, vchSig, keyMasternode)) {
        LogPrintf("CMasternodePing::Sign -- SignMessage() failed\n");
        return false;
    }

    if(!CMessageSigner::VerifyMessage(pubKeyMasternode, vchSig, strMessage, strError)) {
        LogPrintf("CMasternodePing::Sign -- VerifyMessage() failed, error: %s\n", strError);
        return false;
    }

    return true;
}

bool CMasternodePing::CheckSignature(CPubKey& pubKeyMasternode, int &nDos)
{
    // TODO: add sentinel data
    std::string strMessage = vin.ToString() + blockHash.ToString() + boost::lexical_cast<std::string>(sigTime);
    std::string strError = "";
    nDos = 0;

    if(!CMessageSigner::VerifyMessage(pubKeyMasternode, vchSig, strMessage, strError)) {
        LogPrintf("CMasternodePing::CheckSignature -- Got bad Masternode ping signature, masternode=%s, error: %s\n", vin.prevout.ToStringShort(), strError);
        nDos = 33;
        return false;
    }
    return true;
}

bool CMasternodePing::SimpleCheck(int& nDos)
{
    // don't ban by default
    nDos = 0;

    if (sigTime > GetAdjustedTime() + 60 * 60) {
        LogPrintf("CMasternodePing::SimpleCheck -- Signature rejected, too far into the future, masternode=%s\n", vin.prevout.ToStringShort());
        nDos = 1;
        return false;
    }

    {
        AssertLockHeld(cs_main);
        BlockMap::iterator mi = mapBlockIndex.find(blockHash);
        if (mi == mapBlockIndex.end()) {
            LogPrint("masternode", "CMasternodePing::SimpleCheck -- Masternode ping is invalid, unknown block hash: masternode=%s blockHash=%s\n", vin.prevout.ToStringShort(), blockHash.ToString());
            // maybe we stuck or forked so we shouldn't ban this node, just fail to accept this ping
            // TODO: or should we also request this block?
            return false;
        }
    }
    LogPrint("masternode", "CMasternodePing::SimpleCheck -- Masternode ping verified: masternode=%s  blockHash=%s  sigTime=%d\n", vin.prevout.ToStringShort(), blockHash.ToString(), sigTime);
    return true;
}

bool CMasternodePing::CheckAndUpdate(CMasternode* pmn, bool fFromNewBroadcast, int& nDos, CConnman& connman)
{
    // don't ban by default
    nDos = 0;

    if (!SimpleCheck(nDos)) {
        return false;
    }

    if (pmn == NULL) {
        LogPrint("masternode", "CMasternodePing::CheckAndUpdate -- Couldn't find Masternode entry, masternode=%s\n", vin.prevout.ToStringShort());
        return false;
    }

    if(!fFromNewBroadcast) {
        if (pmn->IsUpdateRequired()) {
            LogPrint("masternode", "CMasternodePing::CheckAndUpdate -- masternode protocol is outdated, masternode=%s\n", vin.prevout.ToStringShort());
            return false;
        }

        if (pmn->IsNewStartRequired()) {
            LogPrint("masternode", "CMasternodePing::CheckAndUpdate -- masternode is completely expired, new start is required, masternode=%s\n", vin.prevout.ToStringShort());
            return false;
        }
    }

    {
        LOCK(cs_main);
        BlockMap::iterator mi = mapBlockIndex.find(blockHash);
        if ((*mi).second && (*mi).second->nHeight < chainActive.Height() - 24) {
            LogPrintf("CMasternodePing::CheckAndUpdate -- Masternode ping is invalid, block hash is too old: masternode=%s  blockHash=%s\n", vin.prevout.ToStringShort(), blockHash.ToString());
            // nDos = 1;
            return false;
        }
    }

    LogPrint("masternode", "CMasternodePing::CheckAndUpdate -- New ping: masternode=%s  blockHash=%s  sigTime=%d\n", vin.prevout.ToStringShort(), blockHash.ToString(), sigTime);

    // LogPrintf("mnping - Found corresponding mn for vin: %s\n", vin.prevout.ToStringShort());
    // update only if there is no known ping for this masternode or
    // last ping was more then MASTERNODE_MIN_MNP_SECONDS-60 ago comparing to this one
    if (pmn->IsPingedWithin(MASTERNODE_MIN_MNP_SECONDS - 60, sigTime)) {
        LogPrint("masternode", "CMasternodePing::CheckAndUpdate -- Masternode ping arrived too early, masternode=%s\n", vin.prevout.ToStringShort());
        //nDos = 1; //disable, this is happening frequently and causing banned peers
        return false;
    }

    if (!CheckSignature(pmn->pubKeyMasternode, nDos)) return false;

    // so, ping seems to be ok

    // if we are still syncing and there was no known ping for this mn for quite a while
    // (NOTE: assuming that MASTERNODE_EXPIRATION_SECONDS/2 should be enough to finish mn list sync)
    if(!masternodeSync.IsMasternodeListSynced() && !pmn->IsPingedWithin(MASTERNODE_EXPIRATION_SECONDS/2)) {
        // let's bump sync timeout
        LogPrint("masternode", "CMasternodePing::CheckAndUpdate -- bumping sync timeout, masternode=%s\n", vin.prevout.ToStringShort());
        masternodeSync.BumpAssetLastTime("CMasternodePing::CheckAndUpdate");
    }

    // let's store this ping as the last one
    LogPrint("masternode", "CMasternodePing::CheckAndUpdate -- Masternode ping accepted, masternode=%s\n", vin.prevout.ToStringShort());
    pmn->lastPing = *this;

    // and update mnodeman.mapSeenMasternodeBroadcast.lastPing which is probably outdated
    CMasternodeBroadcast mnb(*pmn);
    uint256 hash = mnb.GetHash();
    if (mnodeman.mapSeenMasternodeBroadcast.count(hash)) {
        mnodeman.mapSeenMasternodeBroadcast[hash].second.lastPing = *this;
    }

    // force update, ignoring cache
    pmn->Check(true);
    // relay ping for nodes in ENABLED/EXPIRED/WATCHDOG_EXPIRED state only, skip everyone else
    if (!pmn->IsEnabled() && !pmn->IsExpired() && !pmn->IsWatchdogExpired()) return false;

    LogPrint("masternode", "CMasternodePing::CheckAndUpdate -- Masternode ping acceepted and relayed, masternode=%s\n", vin.prevout.ToStringShort());
    Relay(connman);

    return true;
}

void CMasternodePing::Relay(CConnman& connman)
{
    // Do not relay until fully synced
    if(!masternodeSync.IsSynced()) {
        LogPrint("masternode", "CMasternodePing::Relay -- won't relay until fully synced\n");
        return;
    }

    CInv inv(MSG_MASTERNODE_PING, GetHash());
    connman.RelayInv(inv);
}

void CMasternode::AddGovernanceVote(uint256 nGovernanceObjectHash)
{
    if(mapGovernanceObjectsVotedOn.count(nGovernanceObjectHash)) {
        mapGovernanceObjectsVotedOn[nGovernanceObjectHash]++;
    } else {
        mapGovernanceObjectsVotedOn.insert(std::make_pair(nGovernanceObjectHash, 1));
    }
}

void CMasternode::RemoveGovernanceObject(uint256 nGovernanceObjectHash)
{
    std::map<uint256, int>::iterator it = mapGovernanceObjectsVotedOn.find(nGovernanceObjectHash);
    if(it == mapGovernanceObjectsVotedOn.end()) {
        return;
    }
    mapGovernanceObjectsVotedOn.erase(it);
}

void CMasternode::UpdateWatchdogVoteTime(uint64_t nVoteTime)
{
    LOCK(cs);
    nTimeLastWatchdogVote = (nVoteTime == 0) ? GetAdjustedTime() : nVoteTime;
}

/**
*   FLAG GOVERNANCE ITEMS AS DIRTY
*
*   - When masternode come and go on the network, we must flag the items they voted on to recalc it's cached flags
*
*/
void CMasternode::FlagGovernanceItemsAsDirty()
{
    std::vector<uint256> vecDirty;
    {
        std::map<uint256, int>::iterator it = mapGovernanceObjectsVotedOn.begin();
        while(it != mapGovernanceObjectsVotedOn.end()) {
            vecDirty.push_back(it->first);
            ++it;
        }
    }
    for(size_t i = 0; i < vecDirty.size(); ++i) {
        mnodeman.AddDirtyGovernanceObjectHash(vecDirty[i]);
=======
uint64_t CMasternodePayments::CalculateScore(uint256 blockHash, CTxIn& vin)
{
    uint256 n1 = blockHash;
    uint256 n2 = Hash(BEGIN(n1), END(n1));
    uint256 n3 = Hash(BEGIN(vin.prevout.hash), END(vin.prevout.hash));
    uint256 n4 = n3 > n2 ? (n3 - n2) : (n2 - n3);

    LogPrintf(" -- CMasternodePayments CalculateScore() n2 = %d \n", n2.Get64());
    LogPrintf(" -- CMasternodePayments CalculateScore() n3 = %d \n", n3.Get64());
    LogPrintf(" -- CMasternodePayments CalculateScore() n4 = %d \n", n4.Get64());

    return n4.Get64();
}

bool CMasternodePayments::GetBlockPayee(int nBlockHeight, CScript& payee)
{
    BOOST_FOREACH(CMasternodePaymentWinner& winner, vWinning){
                    if(winner.nBlockHeight == nBlockHeight) {
                        payee = winner.payee;
                        return true;
                    }
                }

    return false;
}

bool CMasternodePayments::GetWinningMasternode(int nBlockHeight, CTxIn& vinOut)
{
    BOOST_FOREACH(CMasternodePaymentWinner& winner, vWinning){
                    if(winner.nBlockHeight == nBlockHeight) {
                        vinOut = winner.vin;
                        return true;
                    }
                }

    return false;
}

bool CMasternodePayments::AddWinningMasternode(CMasternodePaymentWinner& winnerIn)
{
    uint256 blockHash = 0;
    if(!GetBlockHash(blockHash, winnerIn.nBlockHeight-576)) {
        return false;
    }

    winnerIn.score = CalculateScore(blockHash, winnerIn.vin);

    bool foundBlock = false;
    BOOST_FOREACH(CMasternodePaymentWinner& winner, vWinning){
                    if(winner.nBlockHeight == winnerIn.nBlockHeight) {
                        foundBlock = true;
                        if(winner.score < winnerIn.score){
                            winner.score = winnerIn.score;
                            winner.vin = winnerIn.vin;
                            winner.payee = winnerIn.payee;
                            winner.vchSig = winnerIn.vchSig;

                            return true;
                        }
                    }
                }

    // if it's not in the vector
    if(!foundBlock){
        vWinning.push_back(winnerIn);
        mapSeenMasternodeVotes.insert(make_pair(winnerIn.GetHash(), winnerIn));

        return true;
    }

    return false;
}

void CMasternodePayments::CleanPaymentList()
{
    LOCK(cs_masternodes);
    if(chainActive.Tip() == NULL) return;

    int nLimit = std::max(((int)vecMasternodes.size())*2, 1000);

    vector<CMasternodePaymentWinner>::iterator it;
    for(it=vWinning.begin();it<vWinning.end();it++){
        if(chainActive.Tip()->nHeight - (*it).nBlockHeight > nLimit){
            if(fDebug) LogPrintf("CMasternodePayments::CleanPaymentList - Removing old masternode payment - block %d\n", (*it).nBlockHeight);
            vWinning.erase(it);
            break;
        }
    }
}

bool CMasternodePayments::ProcessBlock(int nBlockHeight)
{
    LOCK(cs_masternodes);
    if(!enabled) return false;
    CMasternodePaymentWinner winner;

    std::vector<CTxIn> vecLastPayments;
    int c = 0;
    BOOST_REVERSE_FOREACH(CMasternodePaymentWinner& winner, vWinning){
                    vecLastPayments.push_back(winner.vin);
                    //if we have one full payment cycle, break
                    if(++c > (int)vecMasternodes.size()) break;
                }

    std::random_shuffle ( vecMasternodes.begin(), vecMasternodes.end() );
    BOOST_FOREACH(CMasterNode& mn, vecMasternodes) {
                    bool found = false;
                    BOOST_FOREACH(CTxIn& vin, vecLastPayments)
                                    if(mn.vin == vin) found = true;

                    if(found) continue;

                    mn.Check();
                    if(!mn.IsEnabled()) {
                        continue;
                    }

                    winner.score = 0;
                    winner.nBlockHeight = nBlockHeight;
                    winner.vin = mn.vin;
                    winner.payee =GetScriptForDestination(mn.pubkey.GetID());

                    break;
                }

    //if we can't find someone to get paid, pick randomly
    if(winner.nBlockHeight == 0 && vecMasternodes.size() > 0) {
        winner.score = 0;
        winner.nBlockHeight = nBlockHeight;
        winner.vin = vecMasternodes[0].vin;
        winner.payee =GetScriptForDestination(vecMasternodes[0].pubkey.GetID());
    }

    if(Sign(winner)){
        if(AddWinningMasternode(winner)){
            Relay(winner);
            return true;
        }
    }

    return false;
}

void CMasternodePayments::Relay(CMasternodePaymentWinner& winner)
{
    CInv inv(MSG_MASTERNODE_WINNER, winner.GetHash());

    vector<CInv> vInv;
    vInv.push_back(inv);
    LOCK(cs_vNodes);
    BOOST_FOREACH(CNode* pnode, vNodes){
                    pnode->PushMessage("inv", vInv);
                }
}

void CMasternodePayments::Sync(CNode* node)
{
    int a = 0;
    BOOST_FOREACH(CMasternodePaymentWinner& winner, vWinning)
                    if(winner.nBlockHeight >= chainActive.Tip()->nHeight-10 && winner.nBlockHeight <= chainActive.Tip()->nHeight + 20)
                        node->PushMessage("mnw", winner, a);
}


bool CMasternodePayments::SetPrivKey(std::string strPrivKey)
{
    CMasternodePaymentWinner winner;

    // Test signing successful, proceed
    strMasterPrivKey = strPrivKey;

    Sign(winner);

    if(CheckSignature(winner)){
        LogPrintf("CMasternodePayments::SetPrivKey - Successfully initialized as masternode payments master\n");
        enabled = true;
        return true;
    } else {
        return false;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }
}
