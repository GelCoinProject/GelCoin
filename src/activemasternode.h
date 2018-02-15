<<<<<<< HEAD
// Copyright (c) 2014-2017 The GelCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ACTIVEMASTERNODE_H
#define ACTIVEMASTERNODE_H

#include "chainparams.h"
#include "key.h"
#include "net.h"
#include "primitives/transaction.h"

class CActiveMasternode;

static const int ACTIVE_MASTERNODE_INITIAL          = 0; // initial state
static const int ACTIVE_MASTERNODE_SYNC_IN_PROCESS  = 1;
static const int ACTIVE_MASTERNODE_INPUT_TOO_NEW    = 2;
static const int ACTIVE_MASTERNODE_NOT_CAPABLE      = 3;
static const int ACTIVE_MASTERNODE_STARTED          = 4;

extern CActiveMasternode activeMasternode;

// Responsible for activating the Masternode and pinging the network
class CActiveMasternode
{
public:
    enum masternode_type_enum_t {
        MASTERNODE_UNKNOWN = 0,
        MASTERNODE_REMOTE  = 1
    };

private:
    // critical section to protect the inner data structures
    mutable CCriticalSection cs;

    masternode_type_enum_t eType;

    bool fPingerEnabled;

    /// Ping Masternode
    bool SendMasternodePing(CConnman& connman);

    //  sentinel ping data
    int64_t nSentinelPingTime;
    uint32_t nSentinelVersion;

public:
    // Keys for the active Masternode
    CPubKey pubKeyMasternode;
    CKey keyMasternode;

    // Initialized while registering Masternode
    COutPoint outpoint;
    CService service;

    int nState; // should be one of ACTIVE_MASTERNODE_XXXX
    std::string strNotCapableReason;


    CActiveMasternode()
        : eType(MASTERNODE_UNKNOWN),
          fPingerEnabled(false),
          pubKeyMasternode(),
          keyMasternode(),
          outpoint(),
          service(),
          nState(ACTIVE_MASTERNODE_INITIAL)
    {}

    /// Manage state of active Masternode
    void ManageState(CConnman& connman);

    std::string GetStateString() const;
    std::string GetStatus() const;
    std::string GetTypeString() const;

    bool UpdateSentinelPing(int version);

private:
    void ManageStateInitial(CConnman& connman);
    void ManageStateRemote();
=======
// Copyright (c) 2009-2010 Satoshi Nakamoto             -*- c++ -*-
// Copyright (c) 2009-2012 The DarkCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef ACTIVEMASTERNODE_H
#define ACTIVEMASTERNODE_H

#include "uint256.h"
#include "sync.h"
#include "net.h"
#include "key.h"
//#include "primitives/transaction.h"
#include "main.h"
#include "init.h"
#include "wallet.h"
#include "darksend.h"

// Responsible for activating the masternode and pinging the network
class CActiveMasternode
{
public:
	// Initialized by init.cpp
	// Keys for the main masternode
	CPubKey pubKeyMasternode;

	// Initialized while registering masternode
	CTxIn vin;
    CService service;

    int status;
    std::string notCapableReason;

    CActiveMasternode()
    {        
        status = MASTERNODE_NOT_PROCESSED;
    }

    void ManageStatus(); // manage status of main masternode

    bool Dseep(std::string& errorMessage); // ping for main masternode
    bool Dseep(CTxIn vin, CService service, CKey key, CPubKey pubKey, std::string &retErrorMessage, bool stop); // ping for any masternode

    bool StopMasterNode(std::string& errorMessage); // stop main masternode
    bool StopMasterNode(std::string strService, std::string strKeyMasternode, std::string& errorMessage); // stop remote masternode
    bool StopMasterNode(CTxIn vin, CService service, CKey key, CPubKey pubKey, std::string& errorMessage); // stop any masternode

    bool Register(std::string strService, std::string strKey, std::string txHash, std::string strOutputIndex, std::string& errorMessage); // register remote masternode
    bool Register(CTxIn vin, CService service, CKey key, CPubKey pubKey, CKey keyMasternode, CPubKey pubKeyMasternode, std::string &retErrorMessage); // register any masternode
    bool RegisterByPubKey(std::string strService, std::string strKeyMasternode, std::string collateralAddress, std::string& errorMessage); // register for a specific collateral address

    // get 16120 Lux input that can be used for the masternode
    bool GetMasterNodeVin(CTxIn& vin, CPubKey& pubkey, CKey& secretKey);
    bool GetMasterNodeVin(CTxIn& vin, CPubKey& pubkey, CKey& secretKey, std::string strTxHash, std::string strOutputIndex);
    bool GetMasterNodeVinForPubKey(std::string collateralAddress, CTxIn& vin, CPubKey& pubkey, CKey& secretKey);
    bool GetMasterNodeVinForPubKey(std::string collateralAddress, CTxIn& vin, CPubKey& pubkey, CKey& secretKey, std::string strTxHash, std::string strOutputIndex);
    vector<COutput> SelectCoinsMasternode();
    vector<COutput> SelectCoinsMasternodeForPubKey(std::string collateralAddress);
    bool GetVinFromOutput(COutput out, CTxIn& vin, CPubKey& pubkey, CKey& secretKey);

    // enable hot wallet mode (run a masternode with no funds)
    bool EnableHotColdMasterNode(CTxIn& vin, CService& addr);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};

#endif
