<<<<<<< HEAD
// Copyright (c) 2014-2017 The GelCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SPORK_H
#define SPORK_H

#include "hash.h"
#include "net.h"
#include "utilstrencodings.h"
=======
// Copyright (c) 2015 The Lux developers
// Copyright (c) 2009-2012 The Darkcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef SPORK_H
#define SPORK_H

//#include "bignum.h"
#include "sync.h"
#include "net.h"
#include "key.h"

#include "util.h"
#include "script/script.h"
#include "base58.h"
#include "main.h"

using namespace std;
using namespace boost;

// Don't ever reuse these IDs for other sporks
#define SPORK_1_MASTERNODE_PAYMENTS_ENFORCEMENT               10000
#define SPORK_2_MAX_VALUE                                     10002
#define SPORK_3_REPLAY_BLOCKS                                 10003
#define SPORK_4_NOTUSED                                       10004


#define SPORK_1_MASTERNODE_PAYMENTS_ENFORCEMENT_DEFAULT       2428537599  //2015-4-8 23:59:59 GMT
#define SPORK_2_MAX_VALUE_DEFAULT                             10000        //500 Lux 
#define SPORK_3_REPLAY_BLOCKS_DEFAULT                         0
#define SPORK_4_RECONVERGE_DEFAULT                            1420070400  //2047-1-1
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

class CSporkMessage;
class CSporkManager;

<<<<<<< HEAD
/*
    Don't ever reuse these IDs for other sporks
    - This would result in old clients getting confused about which spork is for what
*/
static const int SPORK_START                                            = 10001;
static const int SPORK_END                                              = 10013;

static const int SPORK_2_INSTANTSEND_ENABLED                            = 10001;
static const int SPORK_3_INSTANTSEND_BLOCK_FILTERING                    = 10002;
static const int SPORK_5_INSTANTSEND_MAX_VALUE                          = 10004;
static const int SPORK_8_MASTERNODE_PAYMENT_ENFORCEMENT                 = 10007;
static const int SPORK_9_SUPERBLOCKS_ENABLED                            = 10008;
static const int SPORK_10_MASTERNODE_PAY_UPDATED_NODES                  = 10009;
static const int SPORK_12_RECONSIDER_BLOCKS                             = 10011;
static const int SPORK_13_OLD_SUPERBLOCK_FLAG                           = 10012;
static const int SPORK_14_REQUIRE_SENTINEL_FLAG                         = 10013;

static const int64_t SPORK_2_INSTANTSEND_ENABLED_DEFAULT                = 0;            // ON
static const int64_t SPORK_3_INSTANTSEND_BLOCK_FILTERING_DEFAULT        = 0;            // ON
static const int64_t SPORK_5_INSTANTSEND_MAX_VALUE_DEFAULT              = 1000;         // 1000 GEL
static const int64_t SPORK_8_MASTERNODE_PAYMENT_ENFORCEMENT_DEFAULT     = 4070908800ULL;// OFF
static const int64_t SPORK_9_SUPERBLOCKS_ENABLED_DEFAULT                = 4070908800ULL;// OFF
static const int64_t SPORK_10_MASTERNODE_PAY_UPDATED_NODES_DEFAULT      = 4070908800ULL;// OFF
static const int64_t SPORK_12_RECONSIDER_BLOCKS_DEFAULT                 = 0;            // 0 BLOCKS
static const int64_t SPORK_13_OLD_SUPERBLOCK_FLAG_DEFAULT               = 4070908800ULL;// OFF
static const int64_t SPORK_14_REQUIRE_SENTINEL_FLAG_DEFAULT             = 4070908800ULL;// OFF

extern std::map<uint256, CSporkMessage> mapSporks;
extern CSporkManager sporkManager;

//
// Spork classes
// Keep track of all of the network spork settings
=======
//#include "bignum.h"
#include "net.h"
#include "key.h"
#include "util.h"
#include "protocol.h"
#include "darksend.h"
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

extern std::map<uint256, CSporkMessage> mapSporks;
extern std::map<int, CSporkMessage> mapSporksActive;
extern CSporkManager sporkManager;

void ProcessSpork(CNode* pfrom, const std::string& strCommand, CDataStream& vRecv, bool &isSporkCommand);
int GetSporkValue(int nSporkID);
bool IsSporkActive(int nSporkID);
void ExecuteSpork(int nSporkID, int nValue);

//
// Spork Class
// Keeps track of all of the network spork settings
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
//

class CSporkMessage
{
<<<<<<< HEAD
private:
    std::vector<unsigned char> vchSig;

public:
=======
public:
    std::vector<unsigned char> vchSig;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    int nSporkID;
    int64_t nValue;
    int64_t nTimeSigned;

<<<<<<< HEAD
    CSporkMessage(int nSporkID, int64_t nValue, int64_t nTimeSigned) :
        nSporkID(nSporkID),
        nValue(nValue),
        nTimeSigned(nTimeSigned)
        {}

    CSporkMessage() :
        nSporkID(0),
        nValue(0),
        nTimeSigned(0)
        {}

=======
    uint256 GetHash(){
        uint256 n = Hash(BEGIN(nSporkID), END(nTimeSigned));
        return n;
    }
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion) {
        READWRITE(nSporkID);
        READWRITE(nValue);
        READWRITE(nTimeSigned);
        READWRITE(vchSig);
    }
<<<<<<< HEAD

    uint256 GetHash() const
    {
        CHashWriter ss(SER_GETHASH, PROTOCOL_VERSION);
        ss << nSporkID;
        ss << nValue;
        ss << nTimeSigned;
        return ss.GetHash();
    }

    bool Sign(std::string strSignKey);
    bool CheckSignature();
    void Relay(CConnman& connman);
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};


class CSporkManager
{
private:
    std::vector<unsigned char> vchSig;
<<<<<<< HEAD
    std::string strMasterPrivKey;
    std::map<int, CSporkMessage> mapSporksActive;

public:

    CSporkManager() {}

    void ProcessSpork(CNode* pfrom, std::string& strCommand, CDataStream& vRecv, CConnman& connman);
    void ExecuteSpork(int nSporkID, int nValue);
    bool UpdateSpork(int nSporkID, int64_t nValue, CConnman& connman);

    bool IsSporkActive(int nSporkID);
    int64_t GetSporkValue(int nSporkID);
    int GetSporkIDByName(std::string strName);
    std::string GetSporkNameByID(int nSporkID);

    bool SetPrivKey(std::string strPrivKey);
=======

    std::string strMasterPrivKey;
    std::string strTestPubKey;
    std::string strMainPubKey;

public:

    CSporkManager() {
        strMainPubKey = "04a983220ea7a38a7106385003fef77896538a382a0dcc389cc45f3c98751d9af423a097789757556259351198a8aaa628a1fd644c3232678c5845384c744ff8d7";
        strTestPubKey = "04a983220ea7a38a7106385003fef77896538a382a0dcc389cc45f3c98751d9af423a097789757556259351198a8aaa628a1fd644c3232678c5845384c744ff8d7";
    }

    std::string GetSporkNameByID(int id);
    int GetSporkIDByName(std::string strName);
    bool UpdateSpork(int nSporkID, int64_t nValue);
    bool SetPrivKey(std::string strPrivKey);
    bool CheckSignature(CSporkMessage& spork);
    bool Sign(CSporkMessage& spork);
    void Relay(CSporkMessage& msg);

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};

#endif
