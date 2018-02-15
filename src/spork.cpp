<<<<<<< HEAD
// Copyright (c) 2014-2017 The GelCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "validation.h"
#include "messagesigner.h"
#include "net_processing.h"
#include "spork.h"

#include <boost/lexical_cast.hpp>

class CSporkMessage;
class CSporkManager;

CSporkManager sporkManager;

std::map<uint256, CSporkMessage> mapSporks;

void CSporkManager::ProcessSpork(CNode* pfrom, std::string& strCommand, CDataStream& vRecv, CConnman& connman)
{
    if(fLiteMode) return; // disable all GelCoin specific functionality

    if (strCommand == NetMsgType::SPORK) {

        CSporkMessage spork;
        vRecv >> spork;

        uint256 hash = spork.GetHash();

        std::string strLogMsg;
        {
            LOCK(cs_main);
            pfrom->setAskFor.erase(hash);
            if(!chainActive.Tip()) return;
            strLogMsg = strprintf("SPORK -- hash: %s id: %d value: %10d bestHeight: %d peer=%d", hash.ToString(), spork.nSporkID, spork.nValue, chainActive.Height(), pfrom->id);
        }

        if(mapSporksActive.count(spork.nSporkID)) {
            if (mapSporksActive[spork.nSporkID].nTimeSigned >= spork.nTimeSigned) {
                LogPrint("spork", "%s seen\n", strLogMsg);
                return;
            } else {
                LogPrintf("%s updated\n", strLogMsg);
            }
        } else {
            LogPrintf("%s new\n", strLogMsg);
        }

        if(!spork.CheckSignature()) {
            LogPrintf("CSporkManager::ProcessSpork -- invalid signature\n");
=======
// Copyright (c) 2015 The Lux developers
// Copyright (c) 2009-2012 The Darkcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


//#include "bignum.h"
#include "sync.h"
#include "net.h"
#include "key.h"
#include "util.h"
#include "script/script.h"
#include "base58.h"
#include "protocol.h"
#include "spork.h"
#include "main.h"
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

class CSporkMessage;
class CSporkManager;

std::map<uint256, CSporkMessage> mapSporks;
std::map<int, CSporkMessage> mapSporksActive;
CSporkManager sporkManager;

void ProcessSpork(CNode* pfrom, const std::string& strCommand, CDataStream& vRecv, bool &isSporkCommand)
{
    if(fLiteMode) return; //disable all darksend/masternode related functionality

    if (strCommand == "spork") {
        isSporkCommand = true;
        
        //LogPrintf("ProcessSpork::spork\n");
        CDataStream vMsg(vRecv);
        CSporkMessage spork;
        vRecv >> spork;

        if (chainActive.Tip() == nullptr) return;

        uint256 hash = spork.GetHash();
        if(mapSporks.count(hash) && mapSporksActive.count(spork.nSporkID)) {
            if(mapSporksActive[spork.nSporkID].nTimeSigned >= spork.nTimeSigned){
                if(fDebug) LogPrintf("spork - seen %s block %d \n", hash.ToString().c_str(), chainActive.Tip()->nHeight);
                return;
            } else {
                if(fDebug) LogPrintf("spork - got updated spork %s block %d \n", hash.ToString().c_str(), chainActive.Tip()->nHeight);
            }
        }

        LogPrintf("spork - new %s ID %d Time %d bestHeight %d\n", hash.ToString().c_str(), spork.nSporkID, spork.nValue, chainActive.Tip()->nHeight);

        if(!sporkManager.CheckSignature(spork)){
            LogPrintf("spork - invalid signature\n");
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            Misbehaving(pfrom->GetId(), 100);
            return;
        }

        mapSporks[hash] = spork;
        mapSporksActive[spork.nSporkID] = spork;
<<<<<<< HEAD
        spork.Relay(connman);

        //does a task if needed
        ExecuteSpork(spork.nSporkID, spork.nValue);

    } else if (strCommand == NetMsgType::GETSPORKS) {

        std::map<int, CSporkMessage>::iterator it = mapSporksActive.begin();

        while(it != mapSporksActive.end()) {
            connman.PushMessage(pfrom, NetMsgType::SPORK, it->second);
            it++;
        }
    }

}

void CSporkManager::ExecuteSpork(int nSporkID, int nValue)
{
    //correct fork via spork technology
    if(nSporkID == SPORK_12_RECONSIDER_BLOCKS && nValue > 0) {
        // allow to reprocess 24h of blocks max, which should be enough to resolve any issues
        int64_t nMaxBlocks = 576;
        // this potentially can be a heavy operation, so only allow this to be executed once per 10 minutes
        int64_t nTimeout = 10 * 60;

        static int64_t nTimeExecuted = 0; // i.e. it was never executed before

        if(GetTime() - nTimeExecuted < nTimeout) {
            LogPrint("spork", "CSporkManager::ExecuteSpork -- ERROR: Trying to reconsider blocks, too soon - %d/%d\n", GetTime() - nTimeExecuted, nTimeout);
            return;
        }

        if(nValue > nMaxBlocks) {
            LogPrintf("CSporkManager::ExecuteSpork -- ERROR: Trying to reconsider too many blocks %d/%d\n", nValue, nMaxBlocks);
            return;
        }


        LogPrintf("CSporkManager::ExecuteSpork -- Reconsider Last %d Blocks\n", nValue);

        ReprocessBlocks(nValue);
        nTimeExecuted = GetTime();
    }
}

bool CSporkManager::UpdateSpork(int nSporkID, int64_t nValue, CConnman& connman)
{

    CSporkMessage spork = CSporkMessage(nSporkID, nValue, GetAdjustedTime());

    if(spork.Sign(strMasterPrivKey)) {
        spork.Relay(connman);
        mapSporks[spork.GetHash()] = spork;
        mapSporksActive[nSporkID] = spork;
        return true;
    }

    return false;
}

// grab the spork, otherwise say it's off
bool CSporkManager::IsSporkActive(int nSporkID)
{
    int64_t r = -1;
=======
        sporkManager.Relay(spork);

        //does a task if needed
        ExecuteSpork(spork.nSporkID, spork.nValue);
    }

    else if (strCommand == "getsporks") {
        isSporkCommand = true;

        std::map<int, CSporkMessage>::iterator it = mapSporksActive.begin();
        while (it != mapSporksActive.end()) {
            pfrom->PushMessage("spork", it->second);
            it++;
        }
    }
}

// grab the spork, otherwise say it's off
bool IsSporkActive(int nSporkID)
{
    int64_t r = 0;

    if(mapSporksActive.count(nSporkID)){
        r = mapSporksActive[nSporkID].nValue;
    } else {
        if(nSporkID == SPORK_1_MASTERNODE_PAYMENTS_ENFORCEMENT) r = SPORK_1_MASTERNODE_PAYMENTS_ENFORCEMENT_DEFAULT;
        if(nSporkID == SPORK_2_MAX_VALUE) r = SPORK_2_MAX_VALUE_DEFAULT;
        if(nSporkID == SPORK_3_REPLAY_BLOCKS) r = SPORK_3_REPLAY_BLOCKS_DEFAULT;

        if(r == 0 && fDebug) LogPrintf("GetSpork::Unknown Spork %d\n", nSporkID);
    }
    if(r == 0) r = 4070908800; //return 2099-1-1 by default

    return r < GetTime();
}

// grab the value of the spork on the network, or the default
int GetSporkValue(int nSporkID)
{
    int r = 0;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    if(mapSporksActive.count(nSporkID)){
        r = mapSporksActive[nSporkID].nValue;
    } else {
<<<<<<< HEAD
        switch (nSporkID) {
            case SPORK_2_INSTANTSEND_ENABLED:               r = SPORK_2_INSTANTSEND_ENABLED_DEFAULT; break;
            case SPORK_3_INSTANTSEND_BLOCK_FILTERING:       r = SPORK_3_INSTANTSEND_BLOCK_FILTERING_DEFAULT; break;
            case SPORK_5_INSTANTSEND_MAX_VALUE:             r = SPORK_5_INSTANTSEND_MAX_VALUE_DEFAULT; break;
            case SPORK_8_MASTERNODE_PAYMENT_ENFORCEMENT:    r = SPORK_8_MASTERNODE_PAYMENT_ENFORCEMENT_DEFAULT; break;
            case SPORK_9_SUPERBLOCKS_ENABLED:               r = SPORK_9_SUPERBLOCKS_ENABLED_DEFAULT; break;
            case SPORK_10_MASTERNODE_PAY_UPDATED_NODES:     r = SPORK_10_MASTERNODE_PAY_UPDATED_NODES_DEFAULT; break;
            case SPORK_12_RECONSIDER_BLOCKS:                r = SPORK_12_RECONSIDER_BLOCKS_DEFAULT; break;
            case SPORK_13_OLD_SUPERBLOCK_FLAG:              r = SPORK_13_OLD_SUPERBLOCK_FLAG_DEFAULT; break;
            case SPORK_14_REQUIRE_SENTINEL_FLAG:            r = SPORK_14_REQUIRE_SENTINEL_FLAG_DEFAULT; break;
            default:
                LogPrint("spork", "CSporkManager::IsSporkActive -- Unknown Spork ID %d\n", nSporkID);
                r = 4070908800ULL; // 2099-1-1 i.e. off by default
                break;
        }
    }

    return r < GetAdjustedTime();
}

// grab the value of the spork on the network, or the default
int64_t CSporkManager::GetSporkValue(int nSporkID)
{
    if (mapSporksActive.count(nSporkID))
        return mapSporksActive[nSporkID].nValue;

    switch (nSporkID) {
        case SPORK_2_INSTANTSEND_ENABLED:               return SPORK_2_INSTANTSEND_ENABLED_DEFAULT;
        case SPORK_3_INSTANTSEND_BLOCK_FILTERING:       return SPORK_3_INSTANTSEND_BLOCK_FILTERING_DEFAULT;
        case SPORK_5_INSTANTSEND_MAX_VALUE:             return SPORK_5_INSTANTSEND_MAX_VALUE_DEFAULT;
        case SPORK_8_MASTERNODE_PAYMENT_ENFORCEMENT:    return SPORK_8_MASTERNODE_PAYMENT_ENFORCEMENT_DEFAULT;
        case SPORK_9_SUPERBLOCKS_ENABLED:               return SPORK_9_SUPERBLOCKS_ENABLED_DEFAULT;
        case SPORK_10_MASTERNODE_PAY_UPDATED_NODES:     return SPORK_10_MASTERNODE_PAY_UPDATED_NODES_DEFAULT;
        case SPORK_12_RECONSIDER_BLOCKS:                return SPORK_12_RECONSIDER_BLOCKS_DEFAULT;
        case SPORK_13_OLD_SUPERBLOCK_FLAG:              return SPORK_13_OLD_SUPERBLOCK_FLAG_DEFAULT;
        case SPORK_14_REQUIRE_SENTINEL_FLAG:            return SPORK_14_REQUIRE_SENTINEL_FLAG_DEFAULT;
        default:
            LogPrint("spork", "CSporkManager::GetSporkValue -- Unknown Spork ID %d\n", nSporkID);
            return -1;
    }

}

int CSporkManager::GetSporkIDByName(std::string strName)
{
    if (strName == "SPORK_2_INSTANTSEND_ENABLED")               return SPORK_2_INSTANTSEND_ENABLED;
    if (strName == "SPORK_3_INSTANTSEND_BLOCK_FILTERING")       return SPORK_3_INSTANTSEND_BLOCK_FILTERING;
    if (strName == "SPORK_5_INSTANTSEND_MAX_VALUE")             return SPORK_5_INSTANTSEND_MAX_VALUE;
    if (strName == "SPORK_8_MASTERNODE_PAYMENT_ENFORCEMENT")    return SPORK_8_MASTERNODE_PAYMENT_ENFORCEMENT;
    if (strName == "SPORK_9_SUPERBLOCKS_ENABLED")               return SPORK_9_SUPERBLOCKS_ENABLED;
    if (strName == "SPORK_10_MASTERNODE_PAY_UPDATED_NODES")     return SPORK_10_MASTERNODE_PAY_UPDATED_NODES;
    if (strName == "SPORK_12_RECONSIDER_BLOCKS")                return SPORK_12_RECONSIDER_BLOCKS;
    if (strName == "SPORK_13_OLD_SUPERBLOCK_FLAG")              return SPORK_13_OLD_SUPERBLOCK_FLAG;
    if (strName == "SPORK_14_REQUIRE_SENTINEL_FLAG")            return SPORK_14_REQUIRE_SENTINEL_FLAG;

    LogPrint("spork", "CSporkManager::GetSporkIDByName -- Unknown Spork name '%s'\n", strName);
    return -1;
}

std::string CSporkManager::GetSporkNameByID(int nSporkID)
{
    switch (nSporkID) {
        case SPORK_2_INSTANTSEND_ENABLED:               return "SPORK_2_INSTANTSEND_ENABLED";
        case SPORK_3_INSTANTSEND_BLOCK_FILTERING:       return "SPORK_3_INSTANTSEND_BLOCK_FILTERING";
        case SPORK_5_INSTANTSEND_MAX_VALUE:             return "SPORK_5_INSTANTSEND_MAX_VALUE";
        case SPORK_8_MASTERNODE_PAYMENT_ENFORCEMENT:    return "SPORK_8_MASTERNODE_PAYMENT_ENFORCEMENT";
        case SPORK_9_SUPERBLOCKS_ENABLED:               return "SPORK_9_SUPERBLOCKS_ENABLED";
        case SPORK_10_MASTERNODE_PAY_UPDATED_NODES:     return "SPORK_10_MASTERNODE_PAY_UPDATED_NODES";
        case SPORK_12_RECONSIDER_BLOCKS:                return "SPORK_12_RECONSIDER_BLOCKS";
        case SPORK_13_OLD_SUPERBLOCK_FLAG:              return "SPORK_13_OLD_SUPERBLOCK_FLAG";
        case SPORK_14_REQUIRE_SENTINEL_FLAG:            return "SPORK_14_REQUIRE_SENTINEL_FLAG";
        default:
            LogPrint("spork", "CSporkManager::GetSporkNameByID -- Unknown Spork ID %d\n", nSporkID);
            return "Unknown";
    }
}

bool CSporkManager::SetPrivKey(std::string strPrivKey)
{
    CSporkMessage spork;

    spork.Sign(strPrivKey);

    if(spork.CheckSignature()){
        // Test signing successful, proceed
        LogPrintf("CSporkManager::SetPrivKey -- Successfully initialized as spork signer\n");
        strMasterPrivKey = strPrivKey;
        return true;
    } else {
        return false;
    }
}

bool CSporkMessage::Sign(std::string strSignKey)
{
    CKey key;
    CPubKey pubkey;
    std::string strError = "";
    std::string strMessage = boost::lexical_cast<std::string>(nSporkID) + boost::lexical_cast<std::string>(nValue) + boost::lexical_cast<std::string>(nTimeSigned);

    if(!CMessageSigner::GetKeysFromSecret(strSignKey, key, pubkey)) {
        LogPrintf("CSporkMessage::Sign -- GetKeysFromSecret() failed, invalid spork key %s\n", strSignKey);
        return false;
    }

    if(!CMessageSigner::SignMessage(strMessage, vchSig, key)) {
        LogPrintf("CSporkMessage::Sign -- SignMessage() failed\n");
        return false;
    }

    if(!CMessageSigner::VerifyMessage(pubkey, vchSig, strMessage, strError)) {
        LogPrintf("CSporkMessage::Sign -- VerifyMessage() failed, error: %s\n", strError);
=======
        if(nSporkID == SPORK_1_MASTERNODE_PAYMENTS_ENFORCEMENT) r = SPORK_1_MASTERNODE_PAYMENTS_ENFORCEMENT_DEFAULT;
        if(nSporkID == SPORK_2_MAX_VALUE) r = SPORK_2_MAX_VALUE_DEFAULT;
        if(nSporkID == SPORK_3_REPLAY_BLOCKS) r = SPORK_3_REPLAY_BLOCKS_DEFAULT;

        if(r == 0 && fDebug) LogPrintf("GetSpork::Unknown Spork %d\n", nSporkID);
    }

    return r;
}

void ExecuteSpork(int nSporkID, int nValue)
{
    //replay and process blocks (to sync to the longest chain after disabling sporks)
    //if(nSporkID == SPORK_3_REPLAY_BLOCKS){
        //DisconnectBlocksAndReprocess(nValue);
    //}
}


bool CSporkManager::CheckSignature(CSporkMessage& spork)
{
    //note: need to investigate why this is failing
    std::string strMessage = boost::lexical_cast<std::string>(spork.nSporkID) + boost::lexical_cast<std::string>(spork.nValue) + boost::lexical_cast<std::string>(spork.nTimeSigned);
    std::string strPubKey = strMainPubKey;
    CPubKey pubkey(ParseHex(strPubKey));

    std::string errorMessage = "";
    if(!darkSendSigner.VerifyMessage(pubkey, spork.vchSig, strMessage, errorMessage)){
        return false;
    }

    return true;
}

bool CSporkManager::Sign(CSporkMessage& spork)
{
    std::string strMessage = boost::lexical_cast<std::string>(spork.nSporkID) + boost::lexical_cast<std::string>(spork.nValue) + boost::lexical_cast<std::string>(spork.nTimeSigned);

    CKey key2;
    CPubKey pubkey2;
    std::string errorMessage = "";

    if(!darkSendSigner.SetKey(strMasterPrivKey, errorMessage, key2, pubkey2))
    {
        LogPrintf("CMasternodePayments::Sign - ERROR: Invalid masternodeprivkey: '%s'\n", errorMessage.c_str());
        return false;
    }

    if(!darkSendSigner.SignMessage(strMessage, errorMessage, spork.vchSig, key2)) {
        LogPrintf("CMasternodePayments::Sign - Sign message failed");
        return false;
    }

    if(!darkSendSigner.VerifyMessage(pubkey2, spork.vchSig, strMessage, errorMessage)) {
        LogPrintf("CMasternodePayments::Sign - Verify message failed");
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return false;
    }

    return true;
}

<<<<<<< HEAD
bool CSporkMessage::CheckSignature()
{
    //note: need to investigate why this is failing
    std::string strError = "";
    std::string strMessage = boost::lexical_cast<std::string>(nSporkID) + boost::lexical_cast<std::string>(nValue) + boost::lexical_cast<std::string>(nTimeSigned);
    CPubKey pubkey(ParseHex(Params().SporkPubKey()));

    if(!CMessageSigner::VerifyMessage(pubkey, vchSig, strMessage, strError)) {
        LogPrintf("CSporkMessage::CheckSignature -- VerifyMessage() failed, error: %s\n", strError);
        return false;
    }

    return true;
}

void CSporkMessage::Relay(CConnman& connman)
{
    CInv inv(MSG_SPORK, GetHash());
    connman.RelayInv(inv);
=======
bool CSporkManager::UpdateSpork(int nSporkID, int64_t nValue)
{

    CSporkMessage msg;
    msg.nSporkID = nSporkID;
    msg.nValue = nValue;
    msg.nTimeSigned = GetTime();

    if(Sign(msg)){
        Relay(msg);
        mapSporks[msg.GetHash()] = msg;
        mapSporksActive[nSporkID] = msg;
        return true;
    }

    return false;
}

void CSporkManager::Relay(CSporkMessage& msg)
{
    CInv inv(MSG_SPORK, msg.GetHash());

    vector<CInv> vInv;
    vInv.push_back(inv);
    LOCK(cs_vNodes);
    BOOST_FOREACH(CNode* pnode, vNodes){
        pnode->PushMessage("inv", vInv);
    }
}

bool CSporkManager::SetPrivKey(std::string strPrivKey)
{
    CSporkMessage msg;

    // Test signing successful, proceed
    strMasterPrivKey = strPrivKey;

    Sign(msg);

    if(CheckSignature(msg)){
        LogPrintf("CSporkManager::SetPrivKey - Successfully initialized as spork signer\n");
        return true;
    } else {
        return false;
    }
}

int CSporkManager::GetSporkIDByName(std::string strName)
{
    if(strName == "SPORK_1_MASTERNODE_PAYMENTS_ENFORCEMENT") return SPORK_1_MASTERNODE_PAYMENTS_ENFORCEMENT;
    if(strName == "SPORK_2_MAX_VALUE") return SPORK_2_MAX_VALUE;
    if(strName == "SPORK_3_REPLAY_BLOCKS") return SPORK_3_REPLAY_BLOCKS;

    return -1;
}

std::string CSporkManager::GetSporkNameByID(int id)
{
    if(id == SPORK_1_MASTERNODE_PAYMENTS_ENFORCEMENT) return "SPORK_1_MASTERNODE_PAYMENTS_ENFORCEMENT";
    if(id == SPORK_2_MAX_VALUE) return "SPORK_2_MAX_VALUE";
    if(id == SPORK_3_REPLAY_BLOCKS) return "SPORK_3_REPLAY_BLOCKS";

    return "Unknown";
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}
