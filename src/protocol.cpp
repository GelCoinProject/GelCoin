// Copyright (c) 2009-2010 Satoshi Nakamoto
<<<<<<< HEAD
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "protocol.h"

<<<<<<< HEAD
=======
#include "chainparams.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include "util.h"
#include "utilstrencodings.h"

#ifndef WIN32
<<<<<<< HEAD
# include <arpa/inet.h>
#endif

namespace NetMsgType {
const char *VERSION="version";
const char *VERACK="verack";
const char *ADDR="addr";
const char *INV="inv";
const char *GETDATA="getdata";
const char *MERKLEBLOCK="merkleblock";
const char *GETBLOCKS="getblocks";
const char *GETHEADERS="getheaders";
const char *TX="tx";
const char *HEADERS="headers";
const char *BLOCK="block";
const char *GETADDR="getaddr";
const char *MEMPOOL="mempool";
const char *PING="ping";
const char *PONG="pong";
const char *ALERT="alert";
const char *NOTFOUND="notfound";
const char *FILTERLOAD="filterload";
const char *FILTERADD="filteradd";
const char *FILTERCLEAR="filterclear";
const char *REJECT="reject";
const char *SENDHEADERS="sendheaders";
// GelCoin message types
const char *TXLOCKREQUEST="ix";
const char *TXLOCKVOTE="txlvote";
const char *SPORK="spork";
const char *GETSPORKS="getsporks";
const char *MASTERNODEPAYMENTVOTE="mnw";
const char *MASTERNODEPAYMENTBLOCK="mnwb";
const char *MASTERNODEPAYMENTSYNC="mnget";
const char *MNBUDGETSYNC="mnvs"; // depreciated since 12.1
const char *MNBUDGETVOTE="mvote"; // depreciated since 12.1
const char *MNBUDGETPROPOSAL="mprop"; // depreciated since 12.1
const char *MNBUDGETFINAL="fbs"; // depreciated since 12.1
const char *MNBUDGETFINALVOTE="fbvote"; // depreciated since 12.1
const char *MNQUORUM="mn quorum"; // not implemented
const char *MNANNOUNCE="mnb";
const char *MNPING="mnp";
const char *DSACCEPT="dsa";
const char *DSVIN="dsi";
const char *DSFINALTX="dsf";
const char *DSSIGNFINALTX="dss";
const char *DSCOMPLETE="dsc";
const char *DSSTATUSUPDATE="dssu";
const char *DSTX="dstx";
const char *DSQUEUE="dsq";
const char *DSEG="dseg";
const char *SYNCSTATUSCOUNT="ssc";
const char *MNGOVERNANCESYNC="govsync";
const char *MNGOVERNANCEOBJECT="govobj";
const char *MNGOVERNANCEOBJECTVOTE="govobjvote";
const char *MNVERIFY="mnv";
};

static const char* ppszTypeName[] =
{
    "ERROR", // Should never occur
    NetMsgType::TX,
    NetMsgType::BLOCK,
    "filtered block", // Should never occur
    // GelCoin message types
    // NOTE: include non-implmented here, we must keep this list in sync with enum in protocol.h
    NetMsgType::TXLOCKREQUEST,
    NetMsgType::TXLOCKVOTE,
    NetMsgType::SPORK,
    NetMsgType::MASTERNODEPAYMENTVOTE,
    NetMsgType::MASTERNODEPAYMENTBLOCK, // reusing, was MNSCANERROR previousely, was NOT used in 12.0, we need this for inv
    NetMsgType::MNBUDGETVOTE, // depreciated since 12.1
    NetMsgType::MNBUDGETPROPOSAL, // depreciated since 12.1
    NetMsgType::MNBUDGETFINAL, // depreciated since 12.1
    NetMsgType::MNBUDGETFINALVOTE, // depreciated since 12.1
    NetMsgType::MNQUORUM, // not implemented
    NetMsgType::MNANNOUNCE,
    NetMsgType::MNPING,
    NetMsgType::DSTX,
    NetMsgType::MNGOVERNANCEOBJECT,
    NetMsgType::MNGOVERNANCEOBJECTVOTE,
    NetMsgType::MNVERIFY,
};

/** All known message types. Keep this in the same order as the list of
 * messages above and in protocol.h.
 */
const static std::string allNetMessageTypes[] = {
    NetMsgType::VERSION,
    NetMsgType::VERACK,
    NetMsgType::ADDR,
    NetMsgType::INV,
    NetMsgType::GETDATA,
    NetMsgType::MERKLEBLOCK,
    NetMsgType::GETBLOCKS,
    NetMsgType::GETHEADERS,
    NetMsgType::TX,
    NetMsgType::HEADERS,
    NetMsgType::BLOCK,
    NetMsgType::GETADDR,
    NetMsgType::MEMPOOL,
    NetMsgType::PING,
    NetMsgType::PONG,
    NetMsgType::ALERT,
    NetMsgType::NOTFOUND,
    NetMsgType::FILTERLOAD,
    NetMsgType::FILTERADD,
    NetMsgType::FILTERCLEAR,
    NetMsgType::REJECT,
    NetMsgType::SENDHEADERS,
    // GelCoin message types
    // NOTE: do NOT include non-implmented here, we want them to be "Unknown command" in ProcessMessage()
    NetMsgType::TXLOCKREQUEST,
    NetMsgType::TXLOCKVOTE,
    NetMsgType::SPORK,
    NetMsgType::GETSPORKS,
    NetMsgType::MASTERNODEPAYMENTVOTE,
    // NetMsgType::MASTERNODEPAYMENTBLOCK, // there is no message for this, only inventory
    NetMsgType::MASTERNODEPAYMENTSYNC,
    NetMsgType::MNANNOUNCE,
    NetMsgType::MNPING,
    NetMsgType::DSACCEPT,
    NetMsgType::DSVIN,
    NetMsgType::DSFINALTX,
    NetMsgType::DSSIGNFINALTX,
    NetMsgType::DSCOMPLETE,
    NetMsgType::DSSTATUSUPDATE,
    NetMsgType::DSTX,
    NetMsgType::DSQUEUE,
    NetMsgType::DSEG,
    NetMsgType::SYNCSTATUSCOUNT,
    NetMsgType::MNGOVERNANCESYNC,
    NetMsgType::MNGOVERNANCEOBJECT,
    NetMsgType::MNGOVERNANCEOBJECTVOTE,
    NetMsgType::MNVERIFY,
};
const static std::vector<std::string> allNetMessageTypesVec(allNetMessageTypes, allNetMessageTypes+ARRAYLEN(allNetMessageTypes));

CMessageHeader::CMessageHeader(const MessageStartChars& pchMessageStartIn)
{
    memcpy(pchMessageStart, pchMessageStartIn, MESSAGE_START_SIZE);
    memset(pchCommand, 0, sizeof(pchCommand));
    nMessageSize = -1;
    memset(pchChecksum, 0, CHECKSUM_SIZE);
}

CMessageHeader::CMessageHeader(const MessageStartChars& pchMessageStartIn, const char* pszCommand, unsigned int nMessageSizeIn)
{
    memcpy(pchMessageStart, pchMessageStartIn, MESSAGE_START_SIZE);
    memset(pchCommand, 0, sizeof(pchCommand));
    strncpy(pchCommand, pszCommand, COMMAND_SIZE);
    nMessageSize = nMessageSizeIn;
    memset(pchChecksum, 0, CHECKSUM_SIZE);
=======
#include <arpa/inet.h>
#endif

static const char* ppszTypeName[] =
    {
        "ERROR",
        "tx",
        "block",
        "filtered block",
        "tx lock request",
        "tx lock vote",
        "spork",
        "mn winner",
        "mn scan error",
        "mn budget vote",
        "mn budget proposal",
        "mn budget finalized",
        "mn budget finalized vote",
        "mn quorum",
        "mn announce",
        "mn ping",
        "dstx"};

CMessageHeader::CMessageHeader()
{
    memcpy(pchMessageStart, Params().MessageStart(), MESSAGE_START_SIZE);
    memset(pchCommand, 0, sizeof(pchCommand));
    nMessageSize = -1;
    nChecksum = 0;
}

CMessageHeader::CMessageHeader(const char* pszCommand, unsigned int nMessageSizeIn)
{
    memcpy(pchMessageStart, Params().MessageStart(), MESSAGE_START_SIZE);
    memset(pchCommand, 0, sizeof(pchCommand));
    strncpy(pchCommand, pszCommand, COMMAND_SIZE);
    nMessageSize = nMessageSizeIn;
    nChecksum = 0;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

std::string CMessageHeader::GetCommand() const
{
<<<<<<< HEAD
    return std::string(pchCommand, pchCommand + strnlen(pchCommand, COMMAND_SIZE));
}

bool CMessageHeader::IsValid(const MessageStartChars& pchMessageStartIn) const
{
    // Check start string
    if (memcmp(pchMessageStart, pchMessageStartIn, MESSAGE_START_SIZE) != 0)
        return false;

    // Check the command string for errors
    for (const char* p1 = pchCommand; p1 < pchCommand + COMMAND_SIZE; p1++)
    {
        if (*p1 == 0)
        {
=======
    return std::string(pchCommand, pchCommand + strnlen_int(pchCommand, COMMAND_SIZE));
}

bool CMessageHeader::IsValid() const
{
    // Check start string
    if (memcmp(pchMessageStart, Params().MessageStart(), MESSAGE_START_SIZE) != 0)
        return false;

    // Check the command string for errors
    for (const char* p1 = pchCommand; p1 < pchCommand + COMMAND_SIZE; p1++) {
        if (*p1 == 0) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            // Must be all zeros after the first zero
            for (; p1 < pchCommand + COMMAND_SIZE; p1++)
                if (*p1 != 0)
                    return false;
<<<<<<< HEAD
        }
        else if (*p1 < ' ' || *p1 > 0x7E)
=======
        } else if (*p1 < ' ' || *p1 > 0x7E)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            return false;
    }

    // Message size
<<<<<<< HEAD
    if (nMessageSize > MAX_SIZE)
    {
        LogPrintf("CMessageHeader::IsValid(): (%s, %u bytes) nMessageSize > MAX_SIZE\n", GetCommand(), nMessageSize);
=======
    if (nMessageSize > MAX_SIZE) {
        LogPrintf("CMessageHeader::IsValid() : (%s, %u bytes) nMessageSize > MAX_SIZE\n", GetCommand(), nMessageSize);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return false;
    }

    return true;
}


<<<<<<< HEAD

=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
CAddress::CAddress() : CService()
{
    Init();
}

<<<<<<< HEAD
CAddress::CAddress(CService ipIn, ServiceFlags nServicesIn) : CService(ipIn)
=======
CAddress::CAddress(CService ipIn, uint64_t nServicesIn) : CService(ipIn)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    Init();
    nServices = nServicesIn;
}

void CAddress::Init()
{
<<<<<<< HEAD
    nServices = NODE_NONE;
    nTime = 100000000;
=======
    nServices = NODE_NETWORK;
    nTime = 100000000;
    nLastTry = 0;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

CInv::CInv()
{
    type = 0;
<<<<<<< HEAD
    hash.SetNull();
=======
    hash = 0;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

CInv::CInv(int typeIn, const uint256& hashIn)
{
    type = typeIn;
    hash = hashIn;
}

CInv::CInv(const std::string& strType, const uint256& hashIn)
{
    unsigned int i;
<<<<<<< HEAD
    for (i = 1; i < ARRAYLEN(ppszTypeName); i++)
    {
        if (strType == ppszTypeName[i])
        {
=======
    for (i = 1; i < ARRAYLEN(ppszTypeName); i++) {
        if (strType == ppszTypeName[i]) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            type = i;
            break;
        }
    }
    if (i == ARRAYLEN(ppszTypeName))
<<<<<<< HEAD
        throw std::out_of_range(strprintf("CInv::CInv(string, uint256): unknown type '%s'", strType));
=======
        LogPrint("net", "CInv::CInv(string, uint256) : unknown type '%s'", strType);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    hash = hashIn;
}

bool operator<(const CInv& a, const CInv& b)
{
    return (a.type < b.type || (a.type == b.type && a.hash < b.hash));
}

bool CInv::IsKnownType() const
{
    return (type >= 1 && type < (int)ARRAYLEN(ppszTypeName));
}

const char* CInv::GetCommand() const
{
    if (!IsKnownType())
<<<<<<< HEAD
        throw std::out_of_range(strprintf("CInv::GetCommand(): type=%d unknown type", type));
=======
        LogPrint("net", "CInv::GetCommand() : type=%d unknown type", type);

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    return ppszTypeName[type];
}

std::string CInv::ToString() const
{
<<<<<<< HEAD
    try {
        return strprintf("%s %s", GetCommand(), hash.ToString());
    } catch(const std::out_of_range &) {
        return strprintf("0x%08x %s", type, hash.ToString());
    }
}

const std::vector<std::string> &getAllNetMessageTypes()
{
    return allNetMessageTypesVec;
=======
    return strprintf("%s %s", GetCommand(), hash.ToString());
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}
