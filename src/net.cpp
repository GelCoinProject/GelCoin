// Copyright (c) 2009-2010 Satoshi Nakamoto
<<<<<<< HEAD
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Copyright (c) 2014-2017 The GelCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#if defined(HAVE_CONFIG_H)
#include "config/gelcoin-config.h"
=======
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The LUX developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#if defined(HAVE_CONFIG_H)
#include "config/lux-config.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#endif

#include "net.h"

#include "addrman.h"
#include "chainparams.h"
#include "clientversion.h"
<<<<<<< HEAD
#include "consensus/consensus.h"
#include "crypto/common.h"
#include "hash.h"
#include "primitives/transaction.h"
#include "netbase.h"
#include "scheduler.h"
#include "ui_interface.h"
#include "utilstrencodings.h"

#include "instantx.h"
#include "masternode-sync.h"
#include "masternodeman.h"
#include "privatesend.h"
=======
#include "miner.h"
#include "darksend.h"
#include "primitives/transaction.h"
#include "ui_interface.h"
#include "wallet.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

#ifdef WIN32
#include <string.h>
#else
#include <fcntl.h>
#endif

#ifdef USE_UPNP
#include <miniupnpc/miniupnpc.h>
#include <miniupnpc/miniwget.h>
#include <miniupnpc/upnpcommands.h>
#include <miniupnpc/upnperrors.h>
#endif

<<<<<<< HEAD

#include <math.h>

// Dump addresses to peers.dat and banlist.dat every 15 minutes (900s)
#define DUMP_ADDRESSES_INTERVAL 900

// We add a random period time (0 to 1 seconds) to feeler connections to prevent synchronization.
#define FEELER_SLEEP_WINDOW 1

=======
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>

// Dump addresses to peers.dat every 15 minutes (900s)
#define DUMP_ADDRESSES_INTERVAL 900

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#if !defined(HAVE_MSG_NOSIGNAL) && !defined(MSG_NOSIGNAL)
#define MSG_NOSIGNAL 0
#endif

// Fix for ancient MinGW versions, that don't have defined these in ws2tcpip.h.
// Todo: Can be removed when our pull-tester is upgraded to a modern MinGW version.
#ifdef WIN32
#ifndef PROTECTION_LEVEL_UNRESTRICTED
#define PROTECTION_LEVEL_UNRESTRICTED 10
#endif
#ifndef IPV6_PROTECTION_LEVEL
#define IPV6_PROTECTION_LEVEL 23
#endif
#endif

<<<<<<< HEAD
const static std::string NET_MESSAGE_COMMAND_OTHER = "*other*";

constexpr const CConnman::CFullyConnectedOnly CConnman::FullyConnectedOnly;
constexpr const CConnman::CAllNodes CConnman::AllNodes;
=======
using namespace boost;
using namespace std;

namespace
{
const int MAX_OUTBOUND_CONNECTIONS = 16;

struct ListenSocket {
    SOCKET socket;
    bool whitelisted;

    ListenSocket(SOCKET socket, bool whitelisted) : socket(socket), whitelisted(whitelisted) {}
};
}
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

//
// Global state variables
//
bool fDiscover = true;
bool fListen = true;
<<<<<<< HEAD
bool fRelayTxes = true;
CCriticalSection cs_mapLocalHost;
std::map<CNetAddr, LocalServiceInfo> mapLocalHost;
static bool vfLimited[NET_MAX] = {};
static CNode* pnodeLocalHost = NULL;
std::string strSubVersion;

std::map<CInv, CDataStream> mapRelay;
std::deque<pair<int64_t, CInv> > vRelayExpiration;
CCriticalSection cs_mapRelay;
limitedmap<uint256, int64_t> mapAlreadyAskedFor(MAX_INV_SZ);
=======
uint64_t nLocalServices = NODE_NETWORK;
CCriticalSection cs_mapLocalHost;
map<CNetAddr, LocalServiceInfo> mapLocalHost;
static bool vfReachable[NET_MAX] = {};
static bool vfLimited[NET_MAX] = {};
static CNode* pnodeLocalHost = NULL;
uint64_t nLocalHostNonce = 0;
static std::vector<ListenSocket> vhListenSocket;
CAddrMan addrman;
int nMaxConnections = 125;
bool fAddressesInitialized = false;

vector<CNode*> vNodes;
CCriticalSection cs_vNodes;
map<CInv, CDataStream> mapRelay;
deque<pair<int64_t, CInv> > vRelayExpiration;
CCriticalSection cs_mapRelay;
limitedmap<CInv, int64_t> mapAlreadyAskedFor(MAX_INV_SZ);

static deque<string> vOneShots;
CCriticalSection cs_vOneShots;

set<CNetAddr> setservAddNodeAddresses;
CCriticalSection cs_setservAddNodeAddresses;

vector<std::string> vAddedNodes;
CCriticalSection cs_vAddedNodes;

NodeId nLastNodeId = 0;
CCriticalSection cs_nLastNodeId;

static CSemaphore* semOutbound = NULL;
boost::condition_variable messageHandlerCondition;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

// Signals for message handling
static CNodeSignals g_signals;
CNodeSignals& GetNodeSignals() { return g_signals; }

<<<<<<< HEAD
void CConnman::AddOneShot(const std::string& strDest)
=======
void AddOneShot(string strDest)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    LOCK(cs_vOneShots);
    vOneShots.push_back(strDest);
}

unsigned short GetListenPort()
{
    return (unsigned short)(GetArg("-port", Params().GetDefaultPort()));
}

// find 'best' local address for a particular peer
<<<<<<< HEAD
bool GetLocal(CService& addr, const CNetAddr *paddrPeer)
=======
bool GetLocal(CService& addr, const CNetAddr* paddrPeer)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    if (!fListen)
        return false;

    int nBestScore = -1;
    int nBestReachability = -1;
    {
        LOCK(cs_mapLocalHost);
<<<<<<< HEAD
        for (std::map<CNetAddr, LocalServiceInfo>::iterator it = mapLocalHost.begin(); it != mapLocalHost.end(); it++)
        {
            int nScore = (*it).second.nScore;
            int nReachability = (*it).first.GetReachabilityFrom(paddrPeer);
            if (nReachability > nBestReachability || (nReachability == nBestReachability && nScore > nBestScore))
            {
=======
        for (map<CNetAddr, LocalServiceInfo>::iterator it = mapLocalHost.begin(); it != mapLocalHost.end(); it++) {
            int nScore = (*it).second.nScore;
            int nReachability = (*it).first.GetReachabilityFrom(paddrPeer);
            if (nReachability > nBestReachability || (nReachability == nBestReachability && nScore > nBestScore)) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                addr = CService((*it).first, (*it).second.nPort);
                nBestReachability = nReachability;
                nBestScore = nScore;
            }
        }
    }
    return nBestScore >= 0;
}

<<<<<<< HEAD
//! Convert the pnSeeds6 array into usable address objects.
static std::vector<CAddress> convertSeed6(const std::vector<SeedSpec6> &vSeedsIn)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    std::vector<CAddress> vSeedsOut;
    vSeedsOut.reserve(vSeedsIn.size());
    for (std::vector<SeedSpec6>::const_iterator i(vSeedsIn.begin()); i != vSeedsIn.end(); ++i)
    {
        struct in6_addr ip;
        memcpy(&ip, i->addr, sizeof(ip));
        CAddress addr(CService(ip, i->port), NODE_NETWORK);
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
    return vSeedsOut;
}

=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// get best local address for a particular peer as a CAddress
// Otherwise, return the unroutable 0.0.0.0 but filled in with
// the normal parameters, since the IP may be changed to a useful
// one by discovery.
<<<<<<< HEAD
CAddress GetLocalAddress(const CNetAddr *paddrPeer, ServiceFlags nLocalServices)
{
    CAddress ret(CService(CNetAddr(),GetListenPort()), NODE_NONE);
    CService addr;
    if (GetLocal(addr, paddrPeer))
    {
        ret = CAddress(addr, nLocalServices);
    }
=======
CAddress GetLocalAddress(const CNetAddr* paddrPeer)
{
    CAddress ret(CService("0.0.0.0", GetListenPort()), 0);
    CService addr;
    if (GetLocal(addr, paddrPeer)) {
        ret = CAddress(addr);
    }
    ret.nServices = nLocalServices;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    ret.nTime = GetAdjustedTime();
    return ret;
}

<<<<<<< HEAD
=======
bool RecvLine(SOCKET hSocket, string& strLine)
{
    strLine = "";
    while (true) {
        char c;
        int nBytes = recv(hSocket, &c, 1, 0);
        if (nBytes > 0) {
            if (c == '\n')
                continue;
            if (c == '\r')
                return true;
            strLine += c;
            if (strLine.size() >= 9000)
                return true;
        } else if (nBytes <= 0) {
            boost::this_thread::interruption_point();
            if (nBytes < 0) {
                int nErr = WSAGetLastError();
                if (nErr == WSAEMSGSIZE)
                    continue;
                if (nErr == WSAEWOULDBLOCK || nErr == WSAEINTR || nErr == WSAEINPROGRESS) {
                    MilliSleep(10);
                    continue;
                }
            }
            if (!strLine.empty())
                return true;
            if (nBytes == 0) {
                // socket closed
                LogPrint("net", "socket closed\n");
                return false;
            } else {
                // socket error
                int nErr = WSAGetLastError();
                LogPrint("net", "recv failed: %s\n", NetworkErrorString(nErr));
                return false;
            }
        }
    }
}

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
int GetnScore(const CService& addr)
{
    LOCK(cs_mapLocalHost);
    if (mapLocalHost.count(addr) == LOCAL_NONE)
        return 0;
    return mapLocalHost[addr].nScore;
}

// Is our peer's addrLocal potentially useful as an external IP source?
<<<<<<< HEAD
bool IsPeerAddrLocalGood(CNode *pnode)
=======
bool IsPeerAddrLocalGood(CNode* pnode)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    return fDiscover && pnode->addr.IsRoutable() && pnode->addrLocal.IsRoutable() &&
           !IsLimited(pnode->addrLocal.GetNetwork());
}

// pushes our own address to a peer
<<<<<<< HEAD
void AdvertiseLocal(CNode *pnode)
{
    if (fListen && pnode->fSuccessfullyConnected)
    {
        CAddress addrLocal = GetLocalAddress(&pnode->addr, pnode->GetLocalServices());
=======
void AdvertizeLocal(CNode* pnode)
{
    if (fListen && pnode->fSuccessfullyConnected) {
        CAddress addrLocal = GetLocalAddress(&pnode->addr);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        // If discovery is enabled, sometimes give our peer the address it
        // tells us that it sees us as in case it has a better idea of our
        // address than we do.
        if (IsPeerAddrLocalGood(pnode) && (!addrLocal.IsRoutable() ||
<<<<<<< HEAD
             GetRand((GetnScore(addrLocal) > LOCAL_MANUAL) ? 8:2) == 0))
        {
            addrLocal.SetIP(pnode->addrLocal);
        }
        if (addrLocal.IsRoutable())
        {
            LogPrintf("AdvertiseLocal: advertising address %s\n", addrLocal.ToString());
=======
                                              GetRand((GetnScore(addrLocal) > LOCAL_MANUAL) ? 8 : 2) == 0)) {
            addrLocal.SetIP(pnode->addrLocal);
        }
        if (addrLocal.IsRoutable()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            pnode->PushAddress(addrLocal);
        }
    }
}

<<<<<<< HEAD
=======
void SetReachable(enum Network net, bool fFlag)
{
    LOCK(cs_mapLocalHost);
    vfReachable[net] = fFlag;
    if (net == NET_IPV6 && fFlag)
        vfReachable[NET_IPV4] = true;
}

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// learn a new local address
bool AddLocal(const CService& addr, int nScore)
{
    if (!addr.IsRoutable())
        return false;

    if (!fDiscover && nScore < LOCAL_MANUAL)
        return false;

    if (IsLimited(addr))
        return false;

    LogPrintf("AddLocal(%s,%i)\n", addr.ToString(), nScore);

    {
        LOCK(cs_mapLocalHost);
        bool fAlready = mapLocalHost.count(addr) > 0;
<<<<<<< HEAD
        LocalServiceInfo &info = mapLocalHost[addr];
=======
        LocalServiceInfo& info = mapLocalHost[addr];
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        if (!fAlready || nScore >= info.nScore) {
            info.nScore = nScore + (fAlready ? 1 : 0);
            info.nPort = addr.GetPort();
        }
<<<<<<< HEAD
=======
        SetReachable(addr.GetNetwork());
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }

    return true;
}

<<<<<<< HEAD
bool AddLocal(const CNetAddr &addr, int nScore)
=======
bool AddLocal(const CNetAddr& addr, int nScore)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    return AddLocal(CService(addr, GetListenPort()), nScore);
}

<<<<<<< HEAD
bool RemoveLocal(const CService& addr)
{
    LOCK(cs_mapLocalHost);
    LogPrintf("RemoveLocal(%s)\n", addr.ToString());
    mapLocalHost.erase(addr);
    return true;
}

=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
/** Make a particular network entirely off-limits (no automatic connects to it) */
void SetLimited(enum Network net, bool fLimited)
{
    if (net == NET_UNROUTABLE)
        return;
    LOCK(cs_mapLocalHost);
    vfLimited[net] = fLimited;
}

bool IsLimited(enum Network net)
{
    LOCK(cs_mapLocalHost);
    return vfLimited[net];
}

<<<<<<< HEAD
bool IsLimited(const CNetAddr &addr)
=======
bool IsLimited(const CNetAddr& addr)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    return IsLimited(addr.GetNetwork());
}

/** vote for a local address */
bool SeenLocal(const CService& addr)
{
    {
        LOCK(cs_mapLocalHost);
        if (mapLocalHost.count(addr) == 0)
            return false;
        mapLocalHost[addr].nScore++;
    }
    return true;
}


/** check whether a given address is potentially local */
bool IsLocal(const CService& addr)
{
    LOCK(cs_mapLocalHost);
    return mapLocalHost.count(addr) > 0;
}

/** check whether a given network is one we can probably connect to */
bool IsReachable(enum Network net)
{
    LOCK(cs_mapLocalHost);
<<<<<<< HEAD
    return !vfLimited[net];
=======
    return vfReachable[net] && !vfLimited[net];
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

/** check whether a given address is in a network we can probably connect to */
bool IsReachable(const CNetAddr& addr)
{
    enum Network net = addr.GetNetwork();
    return IsReachable(net);
}

<<<<<<< HEAD

std::vector<unsigned char> CNode::vchSecretKey;

CNode* CConnman::FindNode(const CNetAddr& ip)
{
    LOCK(cs_vNodes);
    BOOST_FOREACH(CNode* pnode, vNodes)
        if ((CNetAddr)pnode->addr == ip)
            return (pnode);
    return NULL;
}

CNode* CConnman::FindNode(const CSubNet& subNet)
{
    LOCK(cs_vNodes);
    BOOST_FOREACH(CNode* pnode, vNodes)
    if (subNet.Match((CNetAddr)pnode->addr))
        return (pnode);
    return NULL;
}

CNode* CConnman::FindNode(const std::string& addrName)
{
    LOCK(cs_vNodes);
    BOOST_FOREACH(CNode* pnode, vNodes)
        if (pnode->addrName == addrName)
=======
void AddressCurrentlyConnected(const CService& addr)
{
    addrman.Connected(addr);
}


uint64_t CNode::nTotalBytesRecv = 0;
uint64_t CNode::nTotalBytesSent = 0;
CCriticalSection CNode::cs_totalBytesRecv;
CCriticalSection CNode::cs_totalBytesSent;

CNode* FindNode(const CNetAddr& ip)
{
    LOCK(cs_vNodes);
    BOOST_FOREACH (CNode* pnode, vNodes)
        if ((CNetAddr)pnode->addr == ip)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            return (pnode);
    return NULL;
}

<<<<<<< HEAD
CNode* CConnman::FindNode(const CService& addr)
{
    LOCK(cs_vNodes);
    BOOST_FOREACH(CNode* pnode, vNodes)
        if((CService)pnode->addr == addr)
=======
CNode* FindNode(const std::string& addrName)
{
    LOCK(cs_vNodes);
    BOOST_FOREACH (CNode* pnode, vNodes)
        if (pnode->addrName == addrName)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            return (pnode);
    return NULL;
}

<<<<<<< HEAD
bool CConnman::CheckIncomingNonce(uint64_t nonce)
{
    LOCK(cs_vNodes);
    BOOST_FOREACH(CNode* pnode, vNodes) {
        if (!pnode->fSuccessfullyConnected && !pnode->fInbound && pnode->GetLocalNonce() == nonce)
            return false;
    }
    return true;
}

CNode* CConnman::ConnectNode(CAddress addrConnect, const char *pszDest, bool fConnectToMasternode)
{
    // TODO: This is different from what we have in Bitcoin which only calls ConnectNode from OpenNetworkConnection
    //       If we ever switch to using OpenNetworkConnection for MNs as well, this can be removed
    if (!fNetworkActive) {
        return NULL;
    }

    if (pszDest == NULL) {
        // we clean masternode connections in CMasternodeMan::ProcessMasternodeConnections()
        // so should be safe to skip this and connect to local Hot MN on CActiveMasternode::ManageState()
        if (IsLocal(addrConnect) && !fConnectToMasternode)
            return NULL;

        LOCK(cs_vNodes);
        // Look for an existing connection
        CNode* pnode = FindNode((CService)addrConnect);
        if (pnode)
        {
            // we have existing connection to this node but it was not a connection to masternode,
            // change flag and add reference so that we can correctly clear it later
            if(fConnectToMasternode && !pnode->fMasternode) {
                pnode->AddRef();
                pnode->fMasternode = true;
            }
=======
CNode* FindNode(const CService& addr)
{
    LOCK(cs_vNodes);
    BOOST_FOREACH (CNode* pnode, vNodes) {
        if (Params().NetworkID() == CBaseChainParams::REGTEST) {
            //if using regtest, just check the IP
            if ((CNetAddr)pnode->addr == (CNetAddr)addr)
                return (pnode);
        } else {
            if (pnode->addr == addr)
                return (pnode);
        }
    }
    return NULL;
}

CNode* ConnectNode(CAddress addrConnect, const char* pszDest, bool darkSendMaster)
{
    if (pszDest == NULL) {
        // we clean masternode connections in CMasternodeMan::ProcessMasternodeConnections()
        // so should be safe to skip this and connect to local Hot MN on CActiveMasternode::ManageStatus()
        if (IsLocal(addrConnect) && !darkSendMaster)
            return NULL;

        // Look for an existing connection
        CNode* pnode = FindNode((CService)addrConnect);
        if (pnode) {
            pnode->fDarkSendMaster = darkSendMaster;

            pnode->AddRef();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            return pnode;
        }
    }

    /// debug print
    LogPrint("net", "trying connection %s lastseen=%.1fhrs\n",
        pszDest ? pszDest : addrConnect.ToString(),
<<<<<<< HEAD
        pszDest ? 0.0 : (double)(GetAdjustedTime() - addrConnect.nTime)/3600.0);
=======
        pszDest ? 0.0 : (double)(GetAdjustedTime() - addrConnect.nTime) / 3600.0);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    // Connect
    SOCKET hSocket;
    bool proxyConnectionFailed = false;
    if (pszDest ? ConnectSocketByName(addrConnect, hSocket, pszDest, Params().GetDefaultPort(), nConnectTimeout, &proxyConnectionFailed) :
<<<<<<< HEAD
                  ConnectSocket(addrConnect, hSocket, nConnectTimeout, &proxyConnectionFailed))
    {
=======
                  ConnectSocket(addrConnect, hSocket, nConnectTimeout, &proxyConnectionFailed)) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        if (!IsSelectableSocket(hSocket)) {
            LogPrintf("Cannot create connection: non-selectable socket created (fd >= FD_SETSIZE ?)\n");
            CloseSocket(hSocket);
            return NULL;
        }

<<<<<<< HEAD
        if (pszDest && addrConnect.IsValid()) {
            // It is possible that we already have a connection to the IP/port pszDest resolved to.
            // In that case, drop the connection that was just created, and return the existing CNode instead.
            // Also store the name we used to connect in that CNode, so that future FindNode() calls to that
            // name catch this early.
            LOCK(cs_vNodes);
            CNode* pnode = FindNode((CService)addrConnect);
            if (pnode)
            {
                // we have existing connection to this node but it was not a connection to masternode,
                // change flag and add reference so that we can correctly clear it later
                if(fConnectToMasternode && !pnode->fMasternode) {
                    pnode->AddRef();
                    pnode->fMasternode = true;
                }
                if (pnode->addrName.empty()) {
                    pnode->addrName = std::string(pszDest);
                }
                CloseSocket(hSocket);
                return pnode;
            }
        }

        addrman.Attempt(addrConnect);

        // Add node
        CNode* pnode = new CNode(GetNewNodeId(), nLocalServices, GetBestHeight(), hSocket, addrConnect, pszDest ? pszDest : "", false, true);

        pnode->nServicesExpected = ServiceFlags(addrConnect.nServices & nRelevantServices);
        pnode->nTimeConnected = GetSystemTimeInSeconds();
        if(fConnectToMasternode) {
            pnode->AddRef();
            pnode->fMasternode = true;
        }

        GetNodeSignals().InitializeNode(pnode, *this);
        LOCK(cs_vNodes);
        vNodes.push_back(pnode);
=======
        addrman.Attempt(addrConnect);

        // Add node
        CNode* pnode = new CNode(hSocket, addrConnect, pszDest ? pszDest : "", false);
        pnode->AddRef();

        {
            LOCK(cs_vNodes);
            vNodes.push_back(pnode);
        }

        pnode->nTimeConnected = GetTime();
        if (darkSendMaster) pnode->fDarkSendMaster = true;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

        return pnode;
    } else if (!proxyConnectionFailed) {
        // If connecting to the node failed, and failure is not caused by a problem connecting to
        // the proxy, mark this as an attempt.
        addrman.Attempt(addrConnect);
    }

    return NULL;
}

<<<<<<< HEAD
void CConnman::DumpBanlist()
{
    SweepBanned(); // clean unused entries (if bantime has expired)

    if (!BannedSetIsDirty())
        return;

    int64_t nStart = GetTimeMillis();

    CBanDB bandb;
    banmap_t banmap;
    SetBannedSetDirty(false);
    GetBanned(banmap);
    if (!bandb.Write(banmap))
        SetBannedSetDirty(true);

    LogPrint("net", "Flushed %d banned node ips/subnets to banlist.dat  %dms\n",
        banmap.size(), GetTimeMillis() - nStart);
}

void CNode::CloseSocketDisconnect()
{
    fDisconnect = true;
    if (hSocket != INVALID_SOCKET)
    {
        LogPrint("net", "disconnecting peer=%d\n", id);
        CloseSocket(hSocket);
    }
}

void CConnman::ClearBanned()
{
    {
        LOCK(cs_setBanned);
        setBanned.clear();
        setBannedIsDirty = true;
    }
    DumpBanlist(); //store banlist to disk
    if(clientInterface)
        clientInterface->BannedListChanged();
}

bool CConnman::IsBanned(CNetAddr ip)
{
    bool fResult = false;
    {
        LOCK(cs_setBanned);
        for (banmap_t::iterator it = setBanned.begin(); it != setBanned.end(); it++)
        {
            CSubNet subNet = (*it).first;
            CBanEntry banEntry = (*it).second;

            if(subNet.Match(ip) && GetTime() < banEntry.nBanUntil)
                fResult = true;
        }
    }
    return fResult;
}

bool CConnman::IsBanned(CSubNet subnet)
=======
void CNode::CloseSocketDisconnect()
{
    fDisconnect = true;
    if (hSocket != INVALID_SOCKET) {
        LogPrint("net", "disconnecting peer=%d\n", id);
        CloseSocket(hSocket);
    }

    // in case this fails, we'll empty the recv buffer when the CNode is deleted
    TRY_LOCK(cs_vRecvMsg, lockRecv);
    if (lockRecv)
        vRecvMsg.clear();
}

void CNode::PushVersion()
{
    int nBestHeight = g_signals.GetHeight().get_value_or(0);

    /// when NTP implemented, change to just nTime = GetAdjustedTime()
    int64_t nTime = (fInbound ? GetAdjustedTime() : GetTime());
    CAddress addrYou = (addr.IsRoutable() && !IsProxy(addr) ? addr : CAddress(CService("0.0.0.0", 0)));
    CAddress addrMe = GetLocalAddress(&addr);
    GetRandBytes((unsigned char*)&nLocalHostNonce, sizeof(nLocalHostNonce));
    if (fLogIPs)
        LogPrint("net", "send version message: version %d, blocks=%d, us=%s, them=%s, peer=%d\n", PROTOCOL_VERSION, nBestHeight, addrMe.ToString(), addrYou.ToString(), id);
    else
        LogPrint("net", "send version message: version %d, blocks=%d, us=%s, peer=%d\n", PROTOCOL_VERSION, nBestHeight, addrMe.ToString(), id);
    PushMessage("version", PROTOCOL_VERSION, nLocalServices, nTime, addrYou, addrMe,
        nLocalHostNonce, FormatSubVersion(CLIENT_NAME, CLIENT_VERSION, std::vector<string>()), nBestHeight, true);
}


std::map<CNetAddr, int64_t> CNode::setBanned;
CCriticalSection CNode::cs_setBanned;

void CNode::ClearBanned()
{
    setBanned.clear();
}

bool CNode::IsBanned(CNetAddr ip)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    bool fResult = false;
    {
        LOCK(cs_setBanned);
<<<<<<< HEAD
        banmap_t::iterator i = setBanned.find(subnet);
        if (i != setBanned.end())
        {
            CBanEntry banEntry = (*i).second;
            if (GetTime() < banEntry.nBanUntil)
=======
        std::map<CNetAddr, int64_t>::iterator i = setBanned.find(ip);
        if (i != setBanned.end()) {
            int64_t t = (*i).second;
            if (GetTime() < t)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                fResult = true;
        }
    }
    return fResult;
}

<<<<<<< HEAD
void CConnman::Ban(const CNetAddr& addr, const BanReason &banReason, int64_t bantimeoffset, bool sinceUnixEpoch) {
    CSubNet subNet(addr);
    Ban(subNet, banReason, bantimeoffset, sinceUnixEpoch);
}

void CConnman::Ban(const CSubNet& subNet, const BanReason &banReason, int64_t bantimeoffset, bool sinceUnixEpoch) {
    CBanEntry banEntry(GetTime());
    banEntry.banReason = banReason;
    if (bantimeoffset <= 0)
    {
        bantimeoffset = GetArg("-bantime", DEFAULT_MISBEHAVING_BANTIME);
        sinceUnixEpoch = false;
    }
    banEntry.nBanUntil = (sinceUnixEpoch ? 0 : GetTime() )+bantimeoffset;

    {
        LOCK(cs_setBanned);
        if (setBanned[subNet].nBanUntil < banEntry.nBanUntil) {
            setBanned[subNet] = banEntry;
            setBannedIsDirty = true;
        }
        else
            return;
    }
    if(clientInterface)
        clientInterface->BannedListChanged();
    {
        LOCK(cs_vNodes);
        BOOST_FOREACH(CNode* pnode, vNodes) {
            if (subNet.Match((CNetAddr)pnode->addr))
                pnode->fDisconnect = true;
        }
    }
    if(banReason == BanReasonManuallyAdded)
        DumpBanlist(); //store banlist to disk immediately if user requested ban
}

bool CConnman::Unban(const CNetAddr &addr) {
    CSubNet subNet(addr);
    return Unban(subNet);
}

bool CConnman::Unban(const CSubNet &subNet) {
    {
        LOCK(cs_setBanned);
        if (!setBanned.erase(subNet))
            return false;
        setBannedIsDirty = true;
    }
    if(clientInterface)
        clientInterface->BannedListChanged();
    DumpBanlist(); //store banlist to disk immediately
    return true;
}

void CConnman::GetBanned(banmap_t &banMap)
{
    LOCK(cs_setBanned);
    banMap = setBanned; //create a thread safe copy
}

void CConnman::SetBanned(const banmap_t &banMap)
{
    LOCK(cs_setBanned);
    setBanned = banMap;
    setBannedIsDirty = true;
}

void CConnman::SweepBanned()
{
    int64_t now = GetTime();

    LOCK(cs_setBanned);
    banmap_t::iterator it = setBanned.begin();
    while(it != setBanned.end())
    {
        CSubNet subNet = (*it).first;
        CBanEntry banEntry = (*it).second;
        if(now > banEntry.nBanUntil)
        {
            setBanned.erase(it++);
            setBannedIsDirty = true;
            LogPrint("net", "%s: Removed banned node ip/subnet from banlist.dat: %s\n", __func__, subNet.ToString());
        }
        else
            ++it;
    }
}

bool CConnman::BannedSetIsDirty()
{
    LOCK(cs_setBanned);
    return setBannedIsDirty;
}

void CConnman::SetBannedSetDirty(bool dirty)
{
    LOCK(cs_setBanned); //reuse setBanned lock for the isDirty flag
    setBannedIsDirty = dirty;
}


bool CConnman::IsWhitelistedRange(const CNetAddr &addr) {
    LOCK(cs_vWhitelistedRange);
    BOOST_FOREACH(const CSubNet& subnet, vWhitelistedRange) {
=======
bool CNode::Ban(const CNetAddr& addr)
{
    int64_t banTime = GetTime() + GetArg("-bantime", 60 * 60 * 24); // Default 24-hour ban
    {
        LOCK(cs_setBanned);
        if (setBanned[addr] < banTime)
            setBanned[addr] = banTime;
    }
    return true;
}


std::vector<CSubNet> CNode::vWhitelistedRange;
CCriticalSection CNode::cs_vWhitelistedRange;

bool CNode::IsWhitelistedRange(const CNetAddr& addr)
{
    LOCK(cs_vWhitelistedRange);
    BOOST_FOREACH (const CSubNet& subnet, vWhitelistedRange) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        if (subnet.Match(addr))
            return true;
    }
    return false;
}

<<<<<<< HEAD
void CConnman::AddWhitelistedRange(const CSubNet &subnet) {
=======
void CNode::AddWhitelistedRange(const CSubNet& subnet)
{
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    LOCK(cs_vWhitelistedRange);
    vWhitelistedRange.push_back(subnet);
}

#undef X
#define X(name) stats.name = name
<<<<<<< HEAD
void CNode::copyStats(CNodeStats &stats)
{
    stats.nodeid = this->GetId();
    X(nServices);
    X(addr);
    X(fRelayTxes);
    X(nLastSend);
    X(nLastRecv);
    X(nTimeConnected);
    X(nTimeOffset);
=======
void CNode::copyStats(CNodeStats& stats)
{
    stats.nodeid = this->GetId();
    X(nServices);
    X(nLastSend);
    X(nLastRecv);
    X(nTimeConnected);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    X(addrName);
    X(nVersion);
    X(cleanSubVer);
    X(fInbound);
    X(nStartingHeight);
    X(nSendBytes);
<<<<<<< HEAD
    X(mapSendBytesPerMsgCmd);
    X(nRecvBytes);
    X(mapRecvBytesPerMsgCmd);
=======
    X(nRecvBytes);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    X(fWhitelisted);

    // It is common for nodes with good ping times to suddenly become lagged,
    // due to a new block arriving or other large transfer.
    // Merely reporting pingtime might fool the caller into thinking the node was still responsive,
    // since pingtime does not update until the ping is complete, which might take a while.
    // So, if a ping is taking an unusually long time in flight,
    // the caller can immediately detect that this is happening.
    int64_t nPingUsecWait = 0;
    if ((0 != nPingNonceSent) && (0 != nPingUsecStart)) {
        nPingUsecWait = GetTimeMicros() - nPingUsecStart;
    }

<<<<<<< HEAD
    // Raw ping time is in microseconds, but show it to user as whole seconds (GelCoin users should be well used to small numbers with many decimal places by now :)
    stats.dPingTime = (((double)nPingUsecTime) / 1e6);
    stats.dMinPing  = (((double)nMinPingUsecTime) / 1e6);
=======
    // Raw ping time is in microseconds, but show it to user as whole seconds (LUX users should be well used to small numbers with many decimal places by now :)
    stats.dPingTime = (((double)nPingUsecTime) / 1e6);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    stats.dPingWait = (((double)nPingUsecWait) / 1e6);

    // Leave string empty if addrLocal invalid (not filled in yet)
    stats.addrLocal = addrLocal.IsValid() ? addrLocal.ToString() : "";
}
#undef X

<<<<<<< HEAD
bool CNode::ReceiveMsgBytes(const char *pch, unsigned int nBytes, bool& complete)
{
    complete = false;
    int64_t nTimeMicros = GetTimeMicros();
    nLastRecv = nTimeMicros / 1000000;
    nRecvBytes += nBytes;
    while (nBytes > 0) {

        // get current incomplete message, or create a new one
        if (vRecvMsg.empty() ||
            vRecvMsg.back().complete())
            vRecvMsg.push_back(CNetMessage(Params().MessageStart(), SER_NETWORK, INIT_PROTO_VERSION));
=======
// requires LOCK(cs_vRecvMsg)
bool CNode::ReceiveMsgBytes(const char* pch, unsigned int nBytes)
{
    while (nBytes > 0) {
        // get current incomplete message, or create a new one
        if (vRecvMsg.empty() ||
            vRecvMsg.back().complete())
            vRecvMsg.push_back(CNetMessage(SER_NETWORK, nRecvVersion));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

        CNetMessage& msg = vRecvMsg.back();

        // absorb network data
        int handled;
        if (!msg.in_data)
            handled = msg.readHeader(pch, nBytes);
        else
            handled = msg.readData(pch, nBytes);

        if (handled < 0)
<<<<<<< HEAD
                return false;

        if (msg.in_data && msg.hdr.nMessageSize > MAX_PROTOCOL_MESSAGE_LENGTH) {
            LogPrint("net", "Oversized message from peer=%i, disconnecting\n", GetId());
=======
            return false;

        if (msg.in_data && msg.hdr.nMessageSize > MAX_PROTOCOL_MESSAGE_LENGTH) {
            LogPrint("net", "Oversized message from peer=%i, disconnecting", GetId());
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            return false;
        }

        pch += handled;
        nBytes -= handled;

        if (msg.complete()) {
<<<<<<< HEAD

            //store received bytes per message command
            //to prevent a memory DOS, only allow valid commands
            mapMsgCmdSize::iterator i = mapRecvBytesPerMsgCmd.find(msg.hdr.pchCommand);
            if (i == mapRecvBytesPerMsgCmd.end())
                i = mapRecvBytesPerMsgCmd.find(NET_MESSAGE_COMMAND_OTHER);
            assert(i != mapRecvBytesPerMsgCmd.end());
            i->second += msg.hdr.nMessageSize + CMessageHeader::HEADER_SIZE;

            msg.nTime = nTimeMicros;
            complete = true;
=======
            msg.nTime = GetTimeMicros();
            messageHandlerCondition.notify_one();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        }
    }

    return true;
}

<<<<<<< HEAD
void CNode::SetSendVersion(int nVersionIn)
{
    // Send version may only be changed in the version message, and
    // only one version message is allowed per session. We can therefore
    // treat this value as const and even atomic as long as it's only used
    // once a version message has been successfully processed. Any attempt to
    // set this twice is an error.
    if (nSendVersion != 0) {
        error("Send version already set for node: %i. Refusing to change from %i to %i", id, nSendVersion, nVersionIn);
    } else {
        nSendVersion = nVersionIn;
    }
}

int CNode::GetSendVersion() const
{
    // The send version should always be explicitly set to
    // INIT_PROTO_VERSION rather than using this value until SetSendVersion
    // has been called.
    if (nSendVersion == 0) {
        error("Requesting unset send version for node: %i. Using %i", id, INIT_PROTO_VERSION);
        return INIT_PROTO_VERSION;
    }
    return nSendVersion;
}


int CNetMessage::readHeader(const char *pch, unsigned int nBytes)
=======
int CNetMessage::readHeader(const char* pch, unsigned int nBytes)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    // copy data to temporary parsing buffer
    unsigned int nRemaining = 24 - nHdrPos;
    unsigned int nCopy = std::min(nRemaining, nBytes);

    memcpy(&hdrbuf[nHdrPos], pch, nCopy);
    nHdrPos += nCopy;

    // if header incomplete, exit
    if (nHdrPos < 24)
        return nCopy;

    // deserialize to CMessageHeader
    try {
        hdrbuf >> hdr;
<<<<<<< HEAD
    }
    catch (const std::exception&) {
=======
    } catch (const std::exception&) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return -1;
    }

    // reject messages larger than MAX_SIZE
    if (hdr.nMessageSize > MAX_SIZE)
<<<<<<< HEAD
            return -1;
=======
        return -1;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    // switch state to reading message data
    in_data = true;

    return nCopy;
}

<<<<<<< HEAD
int CNetMessage::readData(const char *pch, unsigned int nBytes)
=======
int CNetMessage::readData(const char* pch, unsigned int nBytes)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    unsigned int nRemaining = hdr.nMessageSize - nDataPos;
    unsigned int nCopy = std::min(nRemaining, nBytes);

    if (vRecv.size() < nDataPos + nCopy) {
        // Allocate up to 256 KiB ahead, but never more than the total message size.
        vRecv.resize(std::min(hdr.nMessageSize, nDataPos + nCopy + 256 * 1024));
    }

    memcpy(&vRecv[nDataPos], pch, nCopy);
    nDataPos += nCopy;

    return nCopy;
}


<<<<<<< HEAD







// requires LOCK(cs_vSend)
size_t CConnman::SocketSendData(CNode *pnode)
{
    std::deque<CSerializeData>::iterator it = pnode->vSendMsg.begin();
    size_t nSentSize = 0;

    while (it != pnode->vSendMsg.end()) {
        const CSerializeData &data = *it;
        assert(data.size() > pnode->nSendOffset);
        int nBytes = send(pnode->hSocket, &data[pnode->nSendOffset], data.size() - pnode->nSendOffset, MSG_NOSIGNAL | MSG_DONTWAIT);
        if (nBytes > 0) {
            pnode->nLastSend = GetSystemTimeInSeconds();
            pnode->nSendBytes += nBytes;
            pnode->nSendOffset += nBytes;
            nSentSize += nBytes;
            if (pnode->nSendOffset == data.size()) {
                pnode->nSendOffset = 0;
                pnode->nSendSize -= data.size();
                pnode->fPauseSend = pnode->nSendSize > nSendBufferMaxSize;
=======
// requires LOCK(cs_vSend)
void SocketSendData(CNode* pnode)
{
    std::deque<CSerializeData>::iterator it = pnode->vSendMsg.begin();

    while (it != pnode->vSendMsg.end()) {
        const CSerializeData& data = *it;
        assert(data.size() > pnode->nSendOffset);
        int nBytes = send(pnode->hSocket, &data[pnode->nSendOffset], data.size() - pnode->nSendOffset, MSG_NOSIGNAL | MSG_DONTWAIT);
        if (nBytes > 0) {
            pnode->nLastSend = GetTime();
            pnode->nSendBytes += nBytes;
            pnode->nSendOffset += nBytes;
            pnode->RecordBytesSent(nBytes);
            if (pnode->nSendOffset == data.size()) {
                pnode->nSendOffset = 0;
                pnode->nSendSize -= data.size();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                it++;
            } else {
                // could not send full message; stop sending more
                break;
            }
        } else {
            if (nBytes < 0) {
                // error
                int nErr = WSAGetLastError();
<<<<<<< HEAD
                if (nErr != WSAEWOULDBLOCK && nErr != WSAEMSGSIZE && nErr != WSAEINTR && nErr != WSAEINPROGRESS)
                {
                    LogPrintf("socket send error %s\n", NetworkErrorString(nErr));
                    pnode->fDisconnect = true;
=======
                if (nErr != WSAEWOULDBLOCK && nErr != WSAEMSGSIZE && nErr != WSAEINTR && nErr != WSAEINPROGRESS) {
                    LogPrintf("socket send error %s\n", NetworkErrorString(nErr));
                    pnode->CloseSocketDisconnect();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                }
            }
            // couldn't send anything at all
            break;
        }
    }

    if (it == pnode->vSendMsg.end()) {
        assert(pnode->nSendOffset == 0);
        assert(pnode->nSendSize == 0);
    }
    pnode->vSendMsg.erase(pnode->vSendMsg.begin(), it);
<<<<<<< HEAD
    return nSentSize;
}

struct NodeEvictionCandidate
{
    NodeEvictionCandidate(CNode* pnode)
        : id(pnode->id),
          nTimeConnected(pnode->nTimeConnected),
          nMinPingUsecTime(pnode->nMinPingUsecTime),
          nLastBlockTime(pnode->nLastBlockTime),
          nLastTXTime(pnode->nLastTXTime),
          fNetworkNode(pnode->fNetworkNode),
          fRelayTxes(pnode->fRelayTxes),
          fBloomFilter(pnode->pfilter != NULL),
          vchNetGroup(pnode->addr.GetGroup()),
          vchKeyedNetGroup(pnode->vchKeyedNetGroup)
        {}

    int id;
    int64_t nTimeConnected;
    int64_t nMinPingUsecTime;
    int64_t nLastBlockTime;
    int64_t nLastTXTime;
    bool fNetworkNode;
    bool fRelayTxes;
    bool fBloomFilter;
    std::vector<unsigned char> vchNetGroup;
    std::vector<unsigned char> vchKeyedNetGroup;
};

static bool ReverseCompareNodeMinPingTime(const NodeEvictionCandidate& a, const NodeEvictionCandidate& b)
{
    return a.nMinPingUsecTime > b.nMinPingUsecTime;
}

static bool ReverseCompareNodeTimeConnected(const NodeEvictionCandidate& a, const NodeEvictionCandidate& b)
{
    return a.nTimeConnected > b.nTimeConnected;
}

static bool CompareKeyedNetGroup(const NodeEvictionCandidate& a, const NodeEvictionCandidate& b)
{
    return a.vchKeyedNetGroup < b.vchKeyedNetGroup;
}

static bool CompareNodeBlockTime(const NodeEvictionCandidate &a, const NodeEvictionCandidate &b)
{
    // There is a fall-through here because it is common for a node to have many peers which have not yet relayed a block.
    if (a.nLastBlockTime != b.nLastBlockTime) return a.nLastBlockTime < b.nLastBlockTime;
    if (a.fNetworkNode != b.fNetworkNode) return b.fNetworkNode;
    return a.nTimeConnected > b.nTimeConnected;
}

static bool CompareNodeTXTime(const NodeEvictionCandidate &a, const NodeEvictionCandidate &b)
{
    // There is a fall-through here because it is common for a node to have more than a few peers that have not yet relayed txn.
    if (a.nLastTXTime != b.nLastTXTime) return a.nLastTXTime < b.nLastTXTime;
    if (a.fRelayTxes != b.fRelayTxes) return b.fRelayTxes;
    if (a.fBloomFilter != b.fBloomFilter) return a.fBloomFilter;
    return a.nTimeConnected > b.nTimeConnected;
}

/** Try to find a connection to evict when the node is full.
 *  Extreme care must be taken to avoid opening the node to attacker
 *   triggered network partitioning.
 *  The strategy used here is to protect a small number of peers
 *   for each of several distinct characteristics which are difficult
 *   to forge.  In order to partition a node the attacker must be
 *   simultaneously better at all of them than honest peers.
 */
bool CConnman::AttemptToEvictConnection()
{
    std::vector<NodeEvictionCandidate> vEvictionCandidates;
    {
        LOCK(cs_vNodes);

        for(size_t i = 0; i < vNodes.size(); ++i) {
            CNode* pnode = vNodes[i];
            if (pnode->fWhitelisted)
                continue;
            if (!pnode->fInbound)
                continue;
            if (pnode->fDisconnect)
                continue;
            vEvictionCandidates.push_back(NodeEvictionCandidate(pnode));
        }
    }

    if (vEvictionCandidates.empty()) return false;

    // Protect connections with certain characteristics

    // Deterministically select 4 peers to protect by netgroup.
    // An attacker cannot predict which netgroups will be protected.
    std::sort(vEvictionCandidates.begin(), vEvictionCandidates.end(), CompareKeyedNetGroup);
    vEvictionCandidates.erase(vEvictionCandidates.end() - std::min(4, static_cast<int>(vEvictionCandidates.size())), vEvictionCandidates.end());

    if (vEvictionCandidates.empty()) return false;

    // Protect the 8 nodes with the best ping times.
    // An attacker cannot manipulate this metric without physically moving nodes closer to the target.
    std::sort(vEvictionCandidates.begin(), vEvictionCandidates.end(), ReverseCompareNodeMinPingTime);
    vEvictionCandidates.erase(vEvictionCandidates.end() - std::min(8, static_cast<int>(vEvictionCandidates.size())), vEvictionCandidates.end());

    if (vEvictionCandidates.empty()) return false;

    // Protect 4 nodes that most recently sent us transactions.
    // An attacker cannot manipulate this metric without performing useful work.
    std::sort(vEvictionCandidates.begin(), vEvictionCandidates.end(), CompareNodeTXTime);
    vEvictionCandidates.erase(vEvictionCandidates.end() - std::min(4, static_cast<int>(vEvictionCandidates.size())), vEvictionCandidates.end());

    if (vEvictionCandidates.empty()) return false;

    // Protect 4 nodes that most recently sent us blocks.
    // An attacker cannot manipulate this metric without performing useful work.
    std::sort(vEvictionCandidates.begin(), vEvictionCandidates.end(), CompareNodeBlockTime);
    vEvictionCandidates.erase(vEvictionCandidates.end() - std::min(4, static_cast<int>(vEvictionCandidates.size())), vEvictionCandidates.end());

    if (vEvictionCandidates.empty()) return false;

    // Protect the half of the remaining nodes which have been connected the longest.
    // This replicates the existing implicit behavior.
    std::sort(vEvictionCandidates.begin(), vEvictionCandidates.end(), ReverseCompareNodeTimeConnected);
    vEvictionCandidates.erase(vEvictionCandidates.end() - static_cast<int>(vEvictionCandidates.size() / 2), vEvictionCandidates.end());

    if (vEvictionCandidates.empty()) return false;

    // Identify the network group with the most connections and youngest member.
    // (vEvictionCandidates is already sorted by reverse connect time)
    std::vector<unsigned char> naMostConnections;
    unsigned int nMostConnections = 0;
    int64_t nMostConnectionsTime = 0;
    std::map<std::vector<unsigned char>, std::vector<NodeEvictionCandidate> > mapAddrCounts;
    for(size_t i = 0; i < vEvictionCandidates.size(); ++i) {
        const NodeEvictionCandidate& candidate = vEvictionCandidates[i];
        mapAddrCounts[candidate.vchNetGroup].push_back(candidate);
        int64_t grouptime = mapAddrCounts[candidate.vchNetGroup][0].nTimeConnected;
        size_t groupsize = mapAddrCounts[candidate.vchNetGroup].size();

        if (groupsize > nMostConnections || (groupsize == nMostConnections && grouptime > nMostConnectionsTime)) {
            nMostConnections = groupsize;
            nMostConnectionsTime = grouptime;
            naMostConnections = candidate.vchNetGroup;
        }
    }

    // Reduce to the network group with the most connections
    std::vector<NodeEvictionCandidate> vEvictionNodes = mapAddrCounts[naMostConnections];

    if(vEvictionNodes.empty()) {
        return false;
    }

    // Disconnect from the network group with the most connections
    int nEvictionId = vEvictionNodes[0].id;
    {
        LOCK(cs_vNodes);
        for(size_t i = 0; i < vNodes.size(); ++i) {
            CNode* pnode = vNodes[i];
            if(pnode->id == nEvictionId) {
                pnode->fDisconnect = true;
                return true;
            }
        }
    }

    return false;
}

void CConnman::AcceptConnection(const ListenSocket& hListenSocket) {
    struct sockaddr_storage sockaddr;
    socklen_t len = sizeof(sockaddr);
    SOCKET hSocket = accept(hListenSocket.socket, (struct sockaddr*)&sockaddr, &len);
    CAddress addr;
    int nInbound = 0;
    int nMaxInbound = nMaxConnections - (nMaxOutbound + nMaxFeeler);

    if (hSocket != INVALID_SOCKET)
        if (!addr.SetSockAddr((const struct sockaddr*)&sockaddr))
            LogPrintf("Warning: Unknown socket family\n");

    bool whitelisted = hListenSocket.whitelisted || IsWhitelistedRange(addr);
    {
        LOCK(cs_vNodes);
        BOOST_FOREACH(CNode* pnode, vNodes)
            if (pnode->fInbound)
                nInbound++;
    }

    if (hSocket == INVALID_SOCKET)
    {
        int nErr = WSAGetLastError();
        if (nErr != WSAEWOULDBLOCK)
            LogPrintf("socket error accept failed: %s\n", NetworkErrorString(nErr));
        return;
    }

    if (!fNetworkActive) {
        LogPrintf("connection from %s dropped: not accepting new connections\n", addr.ToString());
        CloseSocket(hSocket);
        return;
    }

    if (!IsSelectableSocket(hSocket))
    {
        LogPrintf("connection from %s dropped: non-selectable socket\n", addr.ToString());
        CloseSocket(hSocket);
        return;
    }

    // According to the internet TCP_NODELAY is not carried into accepted sockets
    // on all platforms.  Set it again here just to be sure.
    int set = 1;
#ifdef WIN32
    setsockopt(hSocket, IPPROTO_TCP, TCP_NODELAY, (const char*)&set, sizeof(int));
#else
    setsockopt(hSocket, IPPROTO_TCP, TCP_NODELAY, (void*)&set, sizeof(int));
#endif

    if (IsBanned(addr) && !whitelisted)
    {
        LogPrintf("connection from %s dropped (banned)\n", addr.ToString());
        CloseSocket(hSocket);
        return;
    }

    if (nInbound >= nMaxInbound)
    {
        if (!AttemptToEvictConnection()) {
            // No connection to evict, disconnect the new connection
            LogPrint("net", "failed to find an eviction candidate - connection dropped (full)\n");
            CloseSocket(hSocket);
            return;
        }
    }

    // don't accept incoming connections until fully synced
    if(fMasterNode && !masternodeSync.IsSynced()) {
        LogPrintf("AcceptConnection -- masternode is not synced yet, skipping inbound connection attempt\n");
        CloseSocket(hSocket);
        return;
    }

    CNode* pnode = new CNode(GetNewNodeId(), nLocalServices, GetBestHeight(), hSocket, addr, "", true);
    pnode->fWhitelisted = whitelisted;
    GetNodeSignals().InitializeNode(pnode, *this);

    LogPrint("net", "connection from %s accepted\n", addr.ToString());

    {
        LOCK(cs_vNodes);
        vNodes.push_back(pnode);
    }
}

void CConnman::ThreadSocketHandler()
{
    unsigned int nPrevNodeCount = 0;
    while (!interruptNet)
    {
        //
        // Disconnect nodes
        //
        {
            LOCK(cs_vNodes);
            // Disconnect unused nodes
            std::vector<CNode*> vNodesCopy = vNodes;
            BOOST_FOREACH(CNode* pnode, vNodesCopy)
            {
                if (pnode->fDisconnect)
                {
                    LogPrintf("ThreadSocketHandler -- removing node: peer=%d addr=%s nRefCount=%d fNetworkNode=%d fInbound=%d fMasternode=%d\n",
                              pnode->id, pnode->addr.ToString(), pnode->GetRefCount(), pnode->fNetworkNode, pnode->fInbound, pnode->fMasternode);

                    // remove from vNodes
                    vNodes.erase(remove(vNodes.begin(), vNodes.end(), pnode), vNodes.end());

                    // release outbound grant (if any)
                    pnode->grantOutbound.Release();
                    pnode->grantMasternodeOutbound.Release();

                    // close socket and cleanup
                    pnode->CloseSocketDisconnect();

                    // hold in disconnected pool until all refs are released
                    if (pnode->fNetworkNode || pnode->fInbound)
                        pnode->Release();
                    if (pnode->fMasternode)
                        pnode->Release();
                    vNodesDisconnected.push_back(pnode);
                }
            }
        }
        {
            // Delete disconnected nodes
            std::list<CNode*> vNodesDisconnectedCopy = vNodesDisconnected;
            BOOST_FOREACH(CNode* pnode, vNodesDisconnectedCopy)
            {
                // wait until threads are done using it
                if (pnode->GetRefCount() <= 0)
                {
                    bool fDelete = false;
                    {
                        TRY_LOCK(pnode->cs_vSend, lockSend);
                        if (lockSend)
                        {
                                TRY_LOCK(pnode->cs_inventory, lockInv);
                                if (lockInv)
                                    fDelete = true;
                        }
                    }
                    if (fDelete)
                    {
                        vNodesDisconnected.remove(pnode);
                        DeleteNode(pnode);
                    }
                }
            }
        }
        size_t vNodesSize;
        {
            LOCK(cs_vNodes);
            vNodesSize = vNodes.size();
        }
        if(vNodesSize != nPrevNodeCount) {
            nPrevNodeCount = vNodesSize;
            if(clientInterface)
                clientInterface->NotifyNumConnectionsChanged(nPrevNodeCount);
        }

        //
        // Find which sockets have data to receive
        //
        struct timeval timeout;
        timeout.tv_sec  = 0;
        timeout.tv_usec = 50000; // frequency to poll pnode->vSend
=======
}

static list<CNode*> vNodesDisconnected;

void ThreadSocketHandler()
{
    unsigned int nPrevNodeCount = 0;
    while (true) {
        //
        // Disconnect nodes
        //
        {
            LOCK(cs_vNodes);
            // Disconnect unused nodes
            vector<CNode*> vNodesCopy = vNodes;
            BOOST_FOREACH (CNode* pnode, vNodesCopy) {
                if (pnode->fDisconnect ||
                    (pnode->GetRefCount() <= 0 && pnode->vRecvMsg.empty() && pnode->nSendSize == 0 && pnode->ssSend.empty())) {
                    // remove from vNodes
                    vNodes.erase(remove(vNodes.begin(), vNodes.end(), pnode), vNodes.end());

                    // release outbound grant (if any)
                    pnode->grantOutbound.Release();

                    // close socket and cleanup
                    pnode->CloseSocketDisconnect();

                    // hold in disconnected pool until all refs are released
                    if (pnode->fNetworkNode || pnode->fInbound)
                        pnode->Release();
                    vNodesDisconnected.push_back(pnode);
                }
            }
        }
        {
            // Delete disconnected nodes
            list<CNode*> vNodesDisconnectedCopy = vNodesDisconnected;
            BOOST_FOREACH (CNode* pnode, vNodesDisconnectedCopy) {
                // wait until threads are done using it
                if (pnode->GetRefCount() <= 0) {
                    bool fDelete = false;
                    {
                        TRY_LOCK(pnode->cs_vSend, lockSend);
                        if (lockSend) {
                            TRY_LOCK(pnode->cs_vRecvMsg, lockRecv);
                            if (lockRecv) {
                                TRY_LOCK(pnode->cs_inventory, lockInv);
                                if (lockInv)
                                    fDelete = true;
                            }
                        }
                    }
                    if (fDelete) {
                        vNodesDisconnected.remove(pnode);
                        delete pnode;
                    }
                }
            }
        }
        if (vNodes.size() != nPrevNodeCount) {
            nPrevNodeCount = vNodes.size();
            uiInterface.NotifyNumConnectionsChanged(nPrevNodeCount);
        }

        //
        // Find which sockets have data to receive
        //
        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 50000; // frequency to poll pnode->vSend
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

        fd_set fdsetRecv;
        fd_set fdsetSend;
        fd_set fdsetError;
        FD_ZERO(&fdsetRecv);
        FD_ZERO(&fdsetSend);
        FD_ZERO(&fdsetError);
        SOCKET hSocketMax = 0;
        bool have_fds = false;

<<<<<<< HEAD
        BOOST_FOREACH(const ListenSocket& hListenSocket, vhListenSocket) {
            FD_SET(hListenSocket.socket, &fdsetRecv);
            hSocketMax = std::max(hSocketMax, hListenSocket.socket);
=======
        BOOST_FOREACH (const ListenSocket& hListenSocket, vhListenSocket) {
            FD_SET(hListenSocket.socket, &fdsetRecv);
            hSocketMax = max(hSocketMax, hListenSocket.socket);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            have_fds = true;
        }

        {
            LOCK(cs_vNodes);
<<<<<<< HEAD
            BOOST_FOREACH(CNode* pnode, vNodes)
            {
                if (pnode->hSocket == INVALID_SOCKET)
                    continue;
                FD_SET(pnode->hSocket, &fdsetError);
                hSocketMax = std::max(hSocketMax, pnode->hSocket);
=======
            BOOST_FOREACH (CNode* pnode, vNodes) {
                if (pnode->hSocket == INVALID_SOCKET)
                    continue;
                FD_SET(pnode->hSocket, &fdsetError);
                hSocketMax = max(hSocketMax, pnode->hSocket);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                have_fds = true;

                // Implement the following logic:
                // * If there is data to send, select() for sending data. As this only
                //   happens when optimistic write failed, we choose to first drain the
                //   write buffer in this case before receiving more. This avoids
                //   needlessly queueing received data, if the remote peer is not themselves
                //   receiving data. This means properly utilizing TCP flow control signalling.
<<<<<<< HEAD
                // * Otherwise, if there is space left in the receive buffer, select() for
                //   receiving data.
                // * Hand off all complete messages to the processor, to be handled without
                //   blocking here.
                {
                    TRY_LOCK(pnode->cs_vSend, lockSend);
                    if (lockSend) {
                        if (!pnode->vSendMsg.empty()) {
                            FD_SET(pnode->hSocket, &fdsetSend);
                            continue;
                        }
                    }
                }
                {
                    if (!pnode->fPauseRecv)
=======
                // * Otherwise, if there is no (complete) message in the receive buffer,
                //   or there is space left in the buffer, select() for receiving data.
                // * (if neither of the above applies, there is certainly one message
                //   in the receiver buffer ready to be processed).
                // Together, that means that at least one of the following is always possible,
                // so we don't deadlock:
                // * We send some data.
                // * We wait for data to be received (and disconnect after timeout).
                // * We process a message in the buffer (message handler thread).
                {
                    TRY_LOCK(pnode->cs_vSend, lockSend);
                    if (lockSend && !pnode->vSendMsg.empty()) {
                        FD_SET(pnode->hSocket, &fdsetSend);
                        continue;
                    }
                }
                {
                    TRY_LOCK(pnode->cs_vRecvMsg, lockRecv);
                    if (lockRecv && (pnode->vRecvMsg.empty() || !pnode->vRecvMsg.front().complete() ||
                                        pnode->GetTotalRecvSize() <= ReceiveFloodSize()))
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                        FD_SET(pnode->hSocket, &fdsetRecv);
                }
            }
        }

        int nSelect = select(have_fds ? hSocketMax + 1 : 0,
<<<<<<< HEAD
                             &fdsetRecv, &fdsetSend, &fdsetError, &timeout);
        if (interruptNet)
            return;

        if (nSelect == SOCKET_ERROR)
        {
            if (have_fds)
            {
=======
            &fdsetRecv, &fdsetSend, &fdsetError, &timeout);
        boost::this_thread::interruption_point();

        if (nSelect == SOCKET_ERROR) {
            if (have_fds) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                int nErr = WSAGetLastError();
                LogPrintf("socket select error %s\n", NetworkErrorString(nErr));
                for (unsigned int i = 0; i <= hSocketMax; i++)
                    FD_SET(i, &fdsetRecv);
            }
            FD_ZERO(&fdsetSend);
            FD_ZERO(&fdsetError);
<<<<<<< HEAD
            if (!interruptNet.sleep_for(std::chrono::milliseconds(timeout.tv_usec/1000)))
                return;
=======
            MilliSleep(timeout.tv_usec / 1000);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        }

        //
        // Accept new connections
        //
<<<<<<< HEAD
        BOOST_FOREACH(const ListenSocket& hListenSocket, vhListenSocket)
        {
            if (hListenSocket.socket != INVALID_SOCKET && FD_ISSET(hListenSocket.socket, &fdsetRecv))
            {
                AcceptConnection(hListenSocket);
=======
        BOOST_FOREACH (const ListenSocket& hListenSocket, vhListenSocket) {
            if (hListenSocket.socket != INVALID_SOCKET && FD_ISSET(hListenSocket.socket, &fdsetRecv)) {
                struct sockaddr_storage sockaddr;
                socklen_t len = sizeof(sockaddr);
                SOCKET hSocket = accept(hListenSocket.socket, (struct sockaddr*)&sockaddr, &len);
                CAddress addr;
                int nInbound = 0;

                if (hSocket != INVALID_SOCKET)
                    if (!addr.SetSockAddr((const struct sockaddr*)&sockaddr))
                        LogPrintf("Warning: Unknown socket family\n");

                bool whitelisted = hListenSocket.whitelisted || CNode::IsWhitelistedRange(addr);
                {
                    LOCK(cs_vNodes);
                    BOOST_FOREACH (CNode* pnode, vNodes)
                        if (pnode->fInbound)
                            nInbound++;
                }

                if (hSocket == INVALID_SOCKET) {
                    int nErr = WSAGetLastError();
                    if (nErr != WSAEWOULDBLOCK)
                        LogPrintf("socket error accept failed: %s\n", NetworkErrorString(nErr));
                } else if (!IsSelectableSocket(hSocket)) {
                    LogPrintf("connection from %s dropped: non-selectable socket\n", addr.ToString());
                    CloseSocket(hSocket);
                } else if (nInbound >= nMaxConnections - MAX_OUTBOUND_CONNECTIONS) {
                    LogPrint("net", "connection from %s dropped (full)\n", addr.ToString());
                    CloseSocket(hSocket);
                } else if (CNode::IsBanned(addr) && !whitelisted) {
                    LogPrintf("connection from %s dropped (banned)\n", addr.ToString());
                    CloseSocket(hSocket);
                } else {
                    CNode* pnode = new CNode(hSocket, addr, "", true);
                    pnode->AddRef();
                    pnode->fWhitelisted = whitelisted;

                    {
                        LOCK(cs_vNodes);
                        vNodes.push_back(pnode);
                    }
                }
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            }
        }

        //
        // Service each socket
        //
<<<<<<< HEAD
        std::vector<CNode*> vNodesCopy = CopyNodeVector();
        BOOST_FOREACH(CNode* pnode, vNodesCopy)
        {
            if (interruptNet)
                return;
=======
        vector<CNode*> vNodesCopy;
        {
            LOCK(cs_vNodes);
            vNodesCopy = vNodes;
            BOOST_FOREACH (CNode* pnode, vNodesCopy)
                pnode->AddRef();
        }
        BOOST_FOREACH (CNode* pnode, vNodesCopy) {
            boost::this_thread::interruption_point();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

            //
            // Receive
            //
            if (pnode->hSocket == INVALID_SOCKET)
                continue;
<<<<<<< HEAD
            if (FD_ISSET(pnode->hSocket, &fdsetRecv) || FD_ISSET(pnode->hSocket, &fdsetError))
            {
                {
=======
            if (FD_ISSET(pnode->hSocket, &fdsetRecv) || FD_ISSET(pnode->hSocket, &fdsetError)) {
                TRY_LOCK(pnode->cs_vRecvMsg, lockRecv);
                if (lockRecv) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                    {
                        // typical socket buffer is 8K-64K
                        char pchBuf[0x10000];
                        int nBytes = recv(pnode->hSocket, pchBuf, sizeof(pchBuf), MSG_DONTWAIT);
<<<<<<< HEAD
                        if (nBytes > 0)
                        {
                            bool notify = false;
                            if (!pnode->ReceiveMsgBytes(pchBuf, nBytes, notify))
                                pnode->CloseSocketDisconnect();
                            RecordBytesRecv(nBytes);
                            if (notify) {
                                size_t nSizeAdded = 0;
                                auto it(pnode->vRecvMsg.begin());
                                for (; it != pnode->vRecvMsg.end(); ++it) {
                                    if (!it->complete())
                                        break;
                                    nSizeAdded += it->vRecv.size() + CMessageHeader::HEADER_SIZE;
                                }
                                {
                                    LOCK(pnode->cs_vProcessMsg);
                                    pnode->vProcessMsg.splice(pnode->vProcessMsg.end(), pnode->vRecvMsg, pnode->vRecvMsg.begin(), it);
                                    pnode->nProcessQueueSize += nSizeAdded;
                                    pnode->fPauseRecv = pnode->nProcessQueueSize > nReceiveFloodSize;
                                }
                                WakeMessageHandler();
                            }
                        }
                        else if (nBytes == 0)
                        {
=======
                        if (nBytes > 0) {
                            if (!pnode->ReceiveMsgBytes(pchBuf, nBytes))
                                pnode->CloseSocketDisconnect();
                            pnode->nLastRecv = GetTime();
                            pnode->nRecvBytes += nBytes;
                            pnode->RecordBytesRecv(nBytes);
                        } else if (nBytes == 0) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                            // socket closed gracefully
                            if (!pnode->fDisconnect)
                                LogPrint("net", "socket closed\n");
                            pnode->CloseSocketDisconnect();
<<<<<<< HEAD
                        }
                        else if (nBytes < 0)
                        {
                            // error
                            int nErr = WSAGetLastError();
                            if (nErr != WSAEWOULDBLOCK && nErr != WSAEMSGSIZE && nErr != WSAEINTR && nErr != WSAEINPROGRESS)
                            {
=======
                        } else if (nBytes < 0) {
                            // error
                            int nErr = WSAGetLastError();
                            if (nErr != WSAEWOULDBLOCK && nErr != WSAEMSGSIZE && nErr != WSAEINTR && nErr != WSAEINPROGRESS) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                                if (!pnode->fDisconnect)
                                    LogPrintf("socket recv error %s\n", NetworkErrorString(nErr));
                                pnode->CloseSocketDisconnect();
                            }
                        }
                    }
                }
            }

            //
            // Send
            //
            if (pnode->hSocket == INVALID_SOCKET)
                continue;
<<<<<<< HEAD
            if (FD_ISSET(pnode->hSocket, &fdsetSend))
            {
                TRY_LOCK(pnode->cs_vSend, lockSend);
                if (lockSend) {
                    size_t nBytes = SocketSendData(pnode);
                    if (nBytes) {
                        RecordBytesSent(nBytes);
                    }
                }
=======
            if (FD_ISSET(pnode->hSocket, &fdsetSend)) {
                TRY_LOCK(pnode->cs_vSend, lockSend);
                if (lockSend)
                    SocketSendData(pnode);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            }

            //
            // Inactivity checking
            //
<<<<<<< HEAD
            int64_t nTime = GetSystemTimeInSeconds();
            if (nTime - pnode->nTimeConnected > 60)
            {
                if (pnode->nLastRecv == 0 || pnode->nLastSend == 0)
                {
                    LogPrint("net", "socket no message in first 60 seconds, %d %d from %d\n", pnode->nLastRecv != 0, pnode->nLastSend != 0, pnode->id);
                    pnode->fDisconnect = true;
                }
                else if (nTime - pnode->nLastSend > TIMEOUT_INTERVAL)
                {
                    LogPrintf("socket sending timeout: %is\n", nTime - pnode->nLastSend);
                    pnode->fDisconnect = true;
                }
                else if (nTime - pnode->nLastRecv > (pnode->nVersion > BIP0031_VERSION ? TIMEOUT_INTERVAL : 90*60))
                {
                    LogPrintf("socket receive timeout: %is\n", nTime - pnode->nLastRecv);
                    pnode->fDisconnect = true;
                }
                else if (pnode->nPingNonceSent && pnode->nPingUsecStart + TIMEOUT_INTERVAL * 1000000 < GetTimeMicros())
                {
=======
            int64_t nTime = GetTime();
            if (nTime - pnode->nTimeConnected > 60) {
                if (pnode->nLastRecv == 0 || pnode->nLastSend == 0) {
                    LogPrint("net", "socket no message in first 60 seconds, %d %d from %d\n", pnode->nLastRecv != 0, pnode->nLastSend != 0, pnode->id);
                    pnode->fDisconnect = true;
                } else if (nTime - pnode->nLastSend > TIMEOUT_INTERVAL) {
                    LogPrintf("socket sending timeout: %is\n", nTime - pnode->nLastSend);
                    pnode->fDisconnect = true;
                } else if (nTime - pnode->nLastRecv > (pnode->nVersion > BIP0031_VERSION ? TIMEOUT_INTERVAL : 90 * 60)) {
                    LogPrintf("socket receive timeout: %is\n", nTime - pnode->nLastRecv);
                    pnode->fDisconnect = true;
                } else if (pnode->nPingNonceSent && pnode->nPingUsecStart + TIMEOUT_INTERVAL * 1000000 < GetTimeMicros()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                    LogPrintf("ping timeout: %fs\n", 0.000001 * (GetTimeMicros() - pnode->nPingUsecStart));
                    pnode->fDisconnect = true;
                }
            }
        }
<<<<<<< HEAD
        ReleaseNodeVector(vNodesCopy);
    }
}

void CConnman::WakeMessageHandler()
{
    {
        std::lock_guard<std::mutex> lock(mutexMsgProc);
        fMsgProcWake = true;
    }
    condMsgProc.notify_one();
}






=======
        {
            LOCK(cs_vNodes);
            BOOST_FOREACH (CNode* pnode, vNodesCopy)
                pnode->Release();
        }
    }
}


>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#ifdef USE_UPNP
void ThreadMapPort()
{
    std::string port = strprintf("%u", GetListenPort());
<<<<<<< HEAD
    const char * multicastif = 0;
    const char * minissdpdpath = 0;
    struct UPNPDev * devlist = 0;
=======
    const char* multicastif = 0;
    const char* minissdpdpath = 0;
    struct UPNPDev* devlist = 0;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    char lanaddr[64];

#ifndef UPNPDISCOVER_SUCCESS
    /* miniupnpc 1.5 */
    devlist = upnpDiscover(2000, multicastif, minissdpdpath, 0);
#elif MINIUPNPC_API_VERSION < 14
    /* miniupnpc 1.6 */
    int error = 0;
    devlist = upnpDiscover(2000, multicastif, minissdpdpath, 0, 0, &error);
#else
    /* miniupnpc 1.9.20150730 */
    int error = 0;
    devlist = upnpDiscover(2000, multicastif, minissdpdpath, 0, 0, 2, &error);
#endif

    struct UPNPUrls urls;
    struct IGDdatas data;
    int r;

    r = UPNP_GetValidIGD(devlist, &urls, &data, lanaddr, sizeof(lanaddr));
<<<<<<< HEAD
    if (r == 1)
    {
        if (fDiscover) {
            char externalIPAddress[40];
            r = UPNP_GetExternalIPAddress(urls.controlURL, data.first.servicetype, externalIPAddress);
            if(r != UPNPCOMMAND_SUCCESS)
                LogPrintf("UPnP: GetExternalIPAddress() returned %d\n", r);
            else
            {
                if(externalIPAddress[0])
                {
                    CNetAddr resolved;
                    if(LookupHost(externalIPAddress, resolved, false)) {
                        LogPrintf("UPnP: ExternalIPAddress = %s\n", resolved.ToString().c_str());
                        AddLocal(resolved, LOCAL_UPNP);
                    }
                }
                else
=======
    if (r == 1) {
        if (fDiscover) {
            char externalIPAddress[40];
            r = UPNP_GetExternalIPAddress(urls.controlURL, data.first.servicetype, externalIPAddress);
            if (r != UPNPCOMMAND_SUCCESS)
                LogPrintf("UPnP: GetExternalIPAddress() returned %d\n", r);
            else {
                if (externalIPAddress[0]) {
                    LogPrintf("UPnP: ExternalIPAddress = %s\n", externalIPAddress);
                    AddLocal(CNetAddr(externalIPAddress), LOCAL_UPNP);
                } else
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                    LogPrintf("UPnP: GetExternalIPAddress failed.\n");
            }
        }

<<<<<<< HEAD
        std::string strDesc = "GelCoin " + FormatFullVersion();
=======
        string strDesc = "LUX " + FormatFullVersion();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

        try {
            while (true) {
#ifndef UPNPDISCOVER_SUCCESS
                /* miniupnpc 1.5 */
                r = UPNP_AddPortMapping(urls.controlURL, data.first.servicetype,
<<<<<<< HEAD
                                    port.c_str(), port.c_str(), lanaddr, strDesc.c_str(), "TCP", 0);
#else
                /* miniupnpc 1.6 */
                r = UPNP_AddPortMapping(urls.controlURL, data.first.servicetype,
                                    port.c_str(), port.c_str(), lanaddr, strDesc.c_str(), "TCP", 0, "0");
#endif

                if(r!=UPNPCOMMAND_SUCCESS)
=======
                    port.c_str(), port.c_str(), lanaddr, strDesc.c_str(), "TCP", 0);
#else
                /* miniupnpc 1.6 */
                r = UPNP_AddPortMapping(urls.controlURL, data.first.servicetype,
                    port.c_str(), port.c_str(), lanaddr, strDesc.c_str(), "TCP", 0, "0");
#endif

                if (r != UPNPCOMMAND_SUCCESS)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                    LogPrintf("AddPortMapping(%s, %s, %s) failed with code %d (%s)\n",
                        port, port, lanaddr, r, strupnperror(r));
                else
                    LogPrintf("UPnP Port Mapping successful.\n");
<<<<<<< HEAD

                MilliSleep(20*60*1000); // Refresh every 20 minutes
            }
        }
        catch (const boost::thread_interrupted&)
        {
            r = UPNP_DeletePortMapping(urls.controlURL, data.first.servicetype, port.c_str(), "TCP", 0);
            LogPrintf("UPNP_DeletePortMapping() returned: %d\n", r);
            freeUPNPDevlist(devlist); devlist = 0;
=======
                ;

                MilliSleep(20 * 60 * 1000); // Refresh every 20 minutes
            }
        } catch (boost::thread_interrupted) {
            r = UPNP_DeletePortMapping(urls.controlURL, data.first.servicetype, port.c_str(), "TCP", 0);
            LogPrintf("UPNP_DeletePortMapping() returned : %d\n", r);
            freeUPNPDevlist(devlist);
            devlist = 0;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            FreeUPNPUrls(&urls);
            throw;
        }
    } else {
        LogPrintf("No valid UPnP IGDs found\n");
<<<<<<< HEAD
        freeUPNPDevlist(devlist); devlist = 0;
=======
        freeUPNPDevlist(devlist);
        devlist = 0;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        if (r != 0)
            FreeUPNPUrls(&urls);
    }
}

void MapPort(bool fUseUPnP)
{
    static boost::thread* upnp_thread = NULL;

<<<<<<< HEAD
    if (fUseUPnP)
    {
=======
    if (fUseUPnP) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        if (upnp_thread) {
            upnp_thread->interrupt();
            upnp_thread->join();
            delete upnp_thread;
        }
        upnp_thread = new boost::thread(boost::bind(&TraceThread<void (*)()>, "upnp", &ThreadMapPort));
<<<<<<< HEAD
    }
    else if (upnp_thread) {
=======
    } else if (upnp_thread) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        upnp_thread->interrupt();
        upnp_thread->join();
        delete upnp_thread;
        upnp_thread = NULL;
    }
}

#else
void MapPort(bool)
{
    // Intentionally left blank.
}
#endif


<<<<<<< HEAD




void CConnman::ThreadDNSAddressSeed()
{
    // goal: only query DNS seeds if address need is acute
    if ((addrman.size() > 0) &&
        (!GetBoolArg("-forcednsseed", DEFAULT_FORCEDNSSEED))) {
        if (!interruptNet.sleep_for(std::chrono::seconds(11)))
            return;
=======
void ThreadDNSAddressSeed()
{
    // goal: only query DNS seeds if address need is acute
    if ((addrman.size() > 0) &&
        (!GetBoolArg("-forcednsseed", false))) {
        MilliSleep(11 * 1000);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

        LOCK(cs_vNodes);
        if (vNodes.size() >= 2) {
            LogPrintf("P2P peers available. Skipped DNS seeding.\n");
            return;
        }
    }

<<<<<<< HEAD
    const std::vector<CDNSSeedData> &vSeeds = Params().DNSSeeds();
=======
    const vector<CDNSSeedData>& vSeeds = Params().DNSSeeds();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    int found = 0;

    LogPrintf("Loading addresses from DNS seeds (could take a while)\n");

<<<<<<< HEAD
    BOOST_FOREACH(const CDNSSeedData &seed, vSeeds) {
        if (HaveNameProxy()) {
            AddOneShot(seed.host);
        } else {
            std::vector<CNetAddr> vIPs;
            std::vector<CAddress> vAdd;
            if (LookupHost(seed.host.c_str(), vIPs, 0, true))
            {
                BOOST_FOREACH(const CNetAddr& ip, vIPs)
                {
                    int nOneDay = 24*3600;
                    CAddress addr = CAddress(CService(ip, Params().GetDefaultPort()), NODE_NETWORK);
                    addr.nTime = GetTime() - 3*nOneDay - GetRand(4*nOneDay); // use a random age between 3 and 7 days old
=======
    BOOST_FOREACH (const CDNSSeedData& seed, vSeeds) {
        if (HaveNameProxy()) {
            AddOneShot(seed.host);
        } else {
            vector<CNetAddr> vIPs;
            vector<CAddress> vAdd;
            if (LookupHost(seed.host.c_str(), vIPs)) {
                BOOST_FOREACH (CNetAddr& ip, vIPs) {
                    int nOneDay = 24 * 3600;
                    CAddress addr = CAddress(CService(ip, Params().GetDefaultPort()));
                    addr.nTime = GetTime() - 3 * nOneDay - GetRand(4 * nOneDay); // use a random age between 3 and 7 days old
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                    vAdd.push_back(addr);
                    found++;
                }
            }
<<<<<<< HEAD
            // TODO: The seed name resolve may fail, yielding an IP of [::], which results in
            // addrman assigning the same source to results from different seeds.
            // This should switch to a hard-coded stable dummy IP for each seed name, so that the
            // resolve is not required at all.
            if (!vIPs.empty()) {
                CService seedSource;
                Lookup(seed.name.c_str(), seedSource, 0, true);
                addrman.Add(vAdd, seedSource);
            }
=======
            addrman.Add(vAdd, CNetAddr(seed.name, true));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        }
    }

    LogPrintf("%d addresses found from DNS seeds\n", found);
}


<<<<<<< HEAD










void CConnman::DumpAddresses()
=======
void DumpAddresses()
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    int64_t nStart = GetTimeMillis();

    CAddrDB adb;
    adb.Write(addrman);

    LogPrint("net", "Flushed %d addresses to peers.dat  %dms\n",
<<<<<<< HEAD
           addrman.size(), GetTimeMillis() - nStart);
}

void CConnman::DumpData()
{
    DumpAddresses();
    DumpBanlist();
}

void CConnman::ProcessOneShot()
{
    std::string strDest;
=======
        addrman.size(), GetTimeMillis() - nStart);
}

void static ProcessOneShot()
{
    string strDest;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    {
        LOCK(cs_vOneShots);
        if (vOneShots.empty())
            return;
        strDest = vOneShots.front();
        vOneShots.pop_front();
    }
    CAddress addr;
    CSemaphoreGrant grant(*semOutbound, true);
    if (grant) {
        if (!OpenNetworkConnection(addr, &grant, strDest.c_str(), true))
            AddOneShot(strDest);
    }
}

<<<<<<< HEAD
void CConnman::ThreadOpenConnections()
{
    // Connect to specific addresses
    if (mapArgs.count("-connect") && mapMultiArgs["-connect"].size() > 0)
    {
        for (int64_t nLoop = 0;; nLoop++)
        {
            ProcessOneShot();
            BOOST_FOREACH(const std::string& strAddr, mapMultiArgs["-connect"])
            {
                CAddress addr(CService(), NODE_NONE);
                OpenNetworkConnection(addr, NULL, strAddr.c_str());
                for (int i = 0; i < 10 && i < nLoop; i++)
                {
                    if (!interruptNet.sleep_for(std::chrono::milliseconds(500)))
                        return;
                }
            }
            if (!interruptNet.sleep_for(std::chrono::milliseconds(500)))
                return;
=======
void ThreadOpenConnections()
{
    // Connect to specific addresses
    if (mapArgs.count("-connect") && mapMultiArgs["-connect"].size() > 0) {
        for (int64_t nLoop = 0;; nLoop++) {
            ProcessOneShot();
            BOOST_FOREACH (string strAddr, mapMultiArgs["-connect"]) {
                CAddress addr;
                OpenNetworkConnection(addr, NULL, strAddr.c_str());
                for (int i = 0; i < 10 && i < nLoop; i++) {
                    MilliSleep(500);
                }
            }
            MilliSleep(500);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        }
    }

    // Initiate network connections
    int64_t nStart = GetTime();
<<<<<<< HEAD

    // Minimum time before next feeler connection (in microseconds).
    int64_t nNextFeeler = PoissonNextSend(nStart*1000*1000, FEELER_INTERVAL);
    while (!interruptNet)
    {
        ProcessOneShot();

        if (!interruptNet.sleep_for(std::chrono::milliseconds(500)))
            return;

        CSemaphoreGrant grant(*semOutbound);
        if (interruptNet)
            return;
=======
    while (true) {
        ProcessOneShot();

        MilliSleep(500);

        CSemaphoreGrant grant(*semOutbound);
        boost::this_thread::interruption_point();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

        // Add seed nodes if DNS seeds are all down (an infrastructure attack?).
        if (addrman.size() == 0 && (GetTime() - nStart > 60)) {
            static bool done = false;
            if (!done) {
                LogPrintf("Adding fixed seed nodes as DNS doesn't seem to be available.\n");
<<<<<<< HEAD
                CNetAddr local;
                LookupHost("127.0.0.1", local, false);
                addrman.Add(convertSeed6(Params().FixedSeeds()), local);
=======
                addrman.Add(Params().FixedSeeds(), CNetAddr("127.0.0.1"));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                done = true;
            }
        }

        //
        // Choose an address to connect to based on most recently seen
        //
        CAddress addrConnect;

        // Only connect out to one peer per network group (/16 for IPv4).
        // Do this here so we don't have to critsect vNodes inside mapAddresses critsect.
        int nOutbound = 0;
<<<<<<< HEAD
        std::set<std::vector<unsigned char> > setConnected;
        {
            LOCK(cs_vNodes);
            BOOST_FOREACH(CNode* pnode, vNodes) {
                if (!pnode->fInbound && !pnode->fMasternode) {
=======
        set<vector<unsigned char> > setConnected;
        {
            LOCK(cs_vNodes);
            BOOST_FOREACH (CNode* pnode, vNodes) {
                if (!pnode->fInbound) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                    setConnected.insert(pnode->addr.GetGroup());
                    nOutbound++;
                }
            }
        }

<<<<<<< HEAD
        // Feeler Connections
        //
        // Design goals:
        //  * Increase the number of connectable addresses in the tried table.
        //
        // Method:
        //  * Choose a random address from new and attempt to connect to it if we can connect 
        //    successfully it is added to tried.
        //  * Start attempting feeler connections only after node finishes making outbound 
        //    connections.
        //  * Only make a feeler connection once every few minutes.
        //
        bool fFeeler = false;
        if (nOutbound >= nMaxOutbound) {
            int64_t nTime = GetTimeMicros(); // The current time right now (in microseconds).
            if (nTime > nNextFeeler) {
                nNextFeeler = PoissonNextSend(nTime, FEELER_INTERVAL);
                fFeeler = true;
            } else {
                continue;
            }
        }

        int64_t nANow = GetAdjustedTime();
        int nTries = 0;
        while (!interruptNet)
        {
            CAddrInfo addr = addrman.Select(fFeeler);
=======
        int64_t nANow = GetAdjustedTime();

        int nTries = 0;
        while (true) {
            CAddress addr = addrman.Select();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

            // if we selected an invalid address, restart
            if (!addr.IsValid() || setConnected.count(addr.GetGroup()) || IsLocal(addr))
                break;

            // If we didn't find an appropriate destination after trying 100 addresses fetched from addrman,
            // stop this loop, and let the outer loop run again (which sleeps, adds seed nodes, recalculates
            // already-connected network ranges, ...) before trying new addrman addresses.
            nTries++;
            if (nTries > 100)
                break;

            if (IsLimited(addr))
                continue;

<<<<<<< HEAD
            // only connect to full nodes
            if ((addr.nServices & REQUIRED_SERVICES) != REQUIRED_SERVICES)
                continue;

=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            // only consider very recently tried nodes after 30 failed attempts
            if (nANow - addr.nLastTry < 600 && nTries < 30)
                continue;

            // do not allow non-default ports, unless after 50 invalid addresses selected already
            if (addr.GetPort() != Params().GetDefaultPort() && nTries < 50)
                continue;

            addrConnect = addr;
            break;
        }

<<<<<<< HEAD
        if (addrConnect.IsValid()) {

            if (fFeeler) {
                // Add small amount of random noise before connection to avoid synchronization.
                int randsleep = GetRandInt(FEELER_SLEEP_WINDOW * 1000);
                if (!interruptNet.sleep_for(std::chrono::milliseconds(randsleep)))
                    return;
                LogPrint("net", "Making feeler connection to %s\n", addrConnect.ToString());
            }

            OpenNetworkConnection(addrConnect, &grant, NULL, false, fFeeler);
        }
    }
}

std::vector<AddedNodeInfo> CConnman::GetAddedNodeInfo()
{
    std::vector<AddedNodeInfo> ret;

    std::list<std::string> lAddresses(0);
    {
        LOCK(cs_vAddedNodes);
        ret.reserve(vAddedNodes.size());
        BOOST_FOREACH(const std::string& strAddNode, vAddedNodes)
            lAddresses.push_back(strAddNode);
    }


    // Build a map of all already connected addresses (by IP:port and by name) to inbound/outbound and resolved CService
    std::map<CService, bool> mapConnected;
    std::map<std::string, std::pair<bool, CService>> mapConnectedByName;
    {
        LOCK(cs_vNodes);
        for (const CNode* pnode : vNodes) {
            if (pnode->addr.IsValid()) {
                mapConnected[pnode->addr] = pnode->fInbound;
            }
            if (!pnode->addrName.empty()) {
                mapConnectedByName[pnode->addrName] = std::make_pair(pnode->fInbound, static_cast<const CService&>(pnode->addr));
            }
        }
    }

    BOOST_FOREACH(const std::string& strAddNode, lAddresses) {
        CService service(LookupNumeric(strAddNode.c_str(), Params().GetDefaultPort()));
        if (service.IsValid()) {
            // strAddNode is an IP:port
            auto it = mapConnected.find(service);
            if (it != mapConnected.end()) {
                ret.push_back(AddedNodeInfo{strAddNode, service, true, it->second});
            } else {
                ret.push_back(AddedNodeInfo{strAddNode, CService(), false, false});
            }
        } else {
            // strAddNode is a name
            auto it = mapConnectedByName.find(strAddNode);
            if (it != mapConnectedByName.end()) {
                ret.push_back(AddedNodeInfo{strAddNode, it->second.second, true, it->second.first});
            } else {
                ret.push_back(AddedNodeInfo{strAddNode, CService(), false, false});
            }
        }
    }

    return ret;
}

void CConnman::ThreadOpenAddedConnections()
{
    {
        LOCK(cs_vAddedNodes);
        vAddedNodes = mapMultiArgs["-addnode"];
    }

    for (unsigned int i = 0; true; i++)
    {
        std::vector<AddedNodeInfo> vInfo = GetAddedNodeInfo();
        for (const AddedNodeInfo& info : vInfo) {
            if (!info.fConnected) {
                CSemaphoreGrant grant(*semOutbound);
                // If strAddedNode is an IP/port, decode it immediately, so
                // OpenNetworkConnection can detect existing connections to that IP/port.
                CService service(LookupNumeric(info.strAddedNode.c_str(), Params().GetDefaultPort()));
                OpenNetworkConnection(CAddress(service, NODE_NONE), &grant, info.strAddedNode.c_str(), false);
                if (!interruptNet.sleep_for(std::chrono::milliseconds(500)))
                    return;
            }
        }
        if (!interruptNet.sleep_for(std::chrono::minutes(2)))
            return;
    }
}

void CConnman::ThreadMnbRequestConnections()
{
    // Connecting to specific addresses, no masternode connections available
    if (mapArgs.count("-connect") && mapMultiArgs["-connect"].size() > 0)
        return;

    while (!interruptNet)
    {
        if (!interruptNet.sleep_for(std::chrono::milliseconds(1000)))
            return;

        CSemaphoreGrant grant(*semMasternodeOutbound);
        if (interruptNet)
            return;

        std::pair<CService, std::set<uint256> > p = mnodeman.PopScheduledMnbRequestConnection();
        if(p.first == CService() || p.second.empty()) continue;

        ConnectNode(CAddress(p.first, NODE_NETWORK), NULL, true);

        LOCK(cs_vNodes);

        CNode *pnode = FindNode(p.first);
        if(!pnode || pnode->fDisconnect) continue;

        grant.MoveTo(pnode->grantMasternodeOutbound);

        // compile request vector
        std::vector<CInv> vToFetch;
        std::set<uint256>::iterator it = p.second.begin();
        while(it != p.second.end()) {
            if(*it != uint256()) {
                vToFetch.push_back(CInv(MSG_MASTERNODE_ANNOUNCE, *it));
                LogPrint("masternode", "ThreadMnbRequestConnections -- asking for mnb %s from addr=%s\n", it->ToString(), p.first.ToString());
            }
            ++it;
        }

        // ask for data
        PushMessage(pnode, NetMsgType::GETDATA, vToFetch);
=======
        if (addrConnect.IsValid())
            OpenNetworkConnection(addrConnect, &grant);
    }
}

void ThreadOpenAddedConnections()
{
    {
        LOCK(cs_vAddedNodes);
        vAddedNodes = mapMultiArgs["-addnode"];
    }

    if (HaveNameProxy()) {
        while (true) {
            list<string> lAddresses(0);
            {
                LOCK(cs_vAddedNodes);
                BOOST_FOREACH (string& strAddNode, vAddedNodes)
                    lAddresses.push_back(strAddNode);
            }
            BOOST_FOREACH (string& strAddNode, lAddresses) {
                CAddress addr;
                CSemaphoreGrant grant(*semOutbound);
                OpenNetworkConnection(addr, &grant, strAddNode.c_str());
                MilliSleep(500);
            }
            MilliSleep(120000); // Retry every 2 minutes
        }
    }

    for (unsigned int i = 0; true; i++) {
        list<string> lAddresses(0);
        {
            LOCK(cs_vAddedNodes);
            BOOST_FOREACH (string& strAddNode, vAddedNodes)
                lAddresses.push_back(strAddNode);
        }

        list<vector<CService> > lservAddressesToAdd(0);
        BOOST_FOREACH (string& strAddNode, lAddresses) {
            vector<CService> vservNode(0);
            if (Lookup(strAddNode.c_str(), vservNode, Params().GetDefaultPort(), fNameLookup, 0)) {
                lservAddressesToAdd.push_back(vservNode);
                {
                    LOCK(cs_setservAddNodeAddresses);
                    BOOST_FOREACH (CService& serv, vservNode)
                        setservAddNodeAddresses.insert(serv);
                }
            }
        }
        // Attempt to connect to each IP for each addnode entry until at least one is successful per addnode entry
        // (keeping in mind that addnode entries can have many IPs if fNameLookup)
        {
            LOCK(cs_vNodes);
            BOOST_FOREACH (CNode* pnode, vNodes)
                for (list<vector<CService> >::iterator it = lservAddressesToAdd.begin(); it != lservAddressesToAdd.end(); it++)
                    BOOST_FOREACH (CService& addrNode, *(it))
                        if (pnode->addr == addrNode) {
                            it = lservAddressesToAdd.erase(it);
                            it--;
                            break;
                        }
        }
        BOOST_FOREACH (vector<CService>& vserv, lservAddressesToAdd) {
            CSemaphoreGrant grant(*semOutbound);
            OpenNetworkConnection(CAddress(vserv[i % vserv.size()]), &grant);
            MilliSleep(500);
        }
        MilliSleep(120000); // Retry every 2 minutes
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }
}

// if successful, this moves the passed grant to the constructed node
<<<<<<< HEAD
bool CConnman::OpenNetworkConnection(const CAddress& addrConnect, CSemaphoreGrant *grantOutbound, const char *pszDest, bool fOneShot, bool fFeeler)
=======
bool OpenNetworkConnection(const CAddress& addrConnect, CSemaphoreGrant* grantOutbound, const char* pszDest, bool fOneShot)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    //
    // Initiate outbound network connection
    //
<<<<<<< HEAD
    if (interruptNet) {
        return false;
    }
    if (!fNetworkActive) {
        return false;
    }	
    if (!pszDest) {
        if (IsLocal(addrConnect) ||
            FindNode((CNetAddr)addrConnect) || IsBanned(addrConnect) ||
            FindNode(addrConnect.ToStringIPPort()))
            return false;
    } else if (FindNode(std::string(pszDest)))
        return false;

    CNode* pnode = ConnectNode(addrConnect, pszDest);
=======
    boost::this_thread::interruption_point();
    if (!pszDest) {
        if (IsLocal(addrConnect) ||
            FindNode((CNetAddr)addrConnect) || CNode::IsBanned(addrConnect) ||
            FindNode(addrConnect.ToStringIPPort()))
            return false;
    } else if (FindNode(pszDest))
        return false;

    CNode* pnode = ConnectNode(addrConnect, pszDest);
    boost::this_thread::interruption_point();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    if (!pnode)
        return false;
    if (grantOutbound)
        grantOutbound->MoveTo(pnode->grantOutbound);
<<<<<<< HEAD
    if (fOneShot)
        pnode->fOneShot = true;
    if (fFeeler)
        pnode->fFeeler = true;
=======
    pnode->fNetworkNode = true;
    if (fOneShot)
        pnode->fOneShot = true;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    return true;
}

<<<<<<< HEAD
void CConnman::ThreadMessageHandler()
{
    SetThreadPriority(THREAD_PRIORITY_BELOW_NORMAL);
    while (!flagInterruptMsgProc)
    {
        std::vector<CNode*> vNodesCopy = CopyNodeVector();

        bool fMoreWork = false;

        BOOST_FOREACH(CNode* pnode, vNodesCopy)
        {
=======

void ThreadMessageHandler()
{
    boost::mutex condition_mutex;
    boost::unique_lock<boost::mutex> lock(condition_mutex);

    SetThreadPriority(THREAD_PRIORITY_BELOW_NORMAL);
    while (true) {
        vector<CNode*> vNodesCopy;
        {
            LOCK(cs_vNodes);
            vNodesCopy = vNodes;
            BOOST_FOREACH (CNode* pnode, vNodesCopy) {
                pnode->AddRef();
            }
        }

        // Poll the connected nodes for messages
        CNode* pnodeTrickle = NULL;
        if (!vNodesCopy.empty())
            pnodeTrickle = vNodesCopy[GetRand(vNodesCopy.size())];

        bool fSleep = true;

        BOOST_FOREACH (CNode* pnode, vNodesCopy) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            if (pnode->fDisconnect)
                continue;

            // Receive messages
<<<<<<< HEAD
            bool fMoreNodeWork = GetNodeSignals().ProcessMessages(pnode, *this, flagInterruptMsgProc);
            fMoreWork |= (fMoreNodeWork && !pnode->fPauseSend);
            if (flagInterruptMsgProc)
                return;
=======
            {
                TRY_LOCK(pnode->cs_vRecvMsg, lockRecv);
                if (lockRecv) {
                    if (!g_signals.ProcessMessages(pnode))
                        pnode->CloseSocketDisconnect();

                    if (pnode->nSendSize < SendBufferSize()) {
                        if (!pnode->vRecvGetData.empty() || (!pnode->vRecvMsg.empty() && pnode->vRecvMsg[0].complete())) {
                            fSleep = false;
                        }
                    }
                }
            }
            boost::this_thread::interruption_point();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

            // Send messages
            {
                TRY_LOCK(pnode->cs_vSend, lockSend);
                if (lockSend)
<<<<<<< HEAD
                    GetNodeSignals().SendMessages(pnode, *this, flagInterruptMsgProc);
            }
            if (flagInterruptMsgProc)
                return;
        }

        ReleaseNodeVector(vNodesCopy);

        std::unique_lock<std::mutex> lock(mutexMsgProc);
        if (!fMoreWork) {
            condMsgProc.wait_until(lock, std::chrono::steady_clock::now() + std::chrono::milliseconds(100), [this] { return fMsgProcWake; });
        }
        fMsgProcWake = false;
    }
}






bool CConnman::BindListenPort(const CService &addrBind, std::string& strError, bool fWhitelisted)
=======
                    g_signals.SendMessages(pnode, pnode == pnodeTrickle || pnode->fWhitelisted);
            }
            boost::this_thread::interruption_point();
        }


        {
            LOCK(cs_vNodes);
            BOOST_FOREACH (CNode* pnode, vNodesCopy)
                pnode->Release();
        }

        if (fSleep)
            messageHandlerCondition.timed_wait(lock, boost::posix_time::microsec_clock::universal_time() + boost::posix_time::milliseconds(100));
    }
}

// ppcoin: stake minter thread
void static ThreadStakeMinter()
{
    boost::this_thread::interruption_point();
    LogPrintf("ThreadStakeMinter started\n");
    CWallet* pwallet = pwalletMain;
    try {
        BitcoinMiner(pwallet, true);
        boost::this_thread::interruption_point();
    } catch (std::exception& e) {
        LogPrintf("ThreadStakeMinter() exception \n");
    } catch (...) {
        LogPrintf("ThreadStakeMinter() error \n");
    }
    LogPrintf("ThreadStakeMinter exiting,\n");
}

bool BindListenPort(const CService& addrBind, string& strError, bool fWhitelisted)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    strError = "";
    int nOne = 1;

    // Create socket for listening for incoming connections
    struct sockaddr_storage sockaddr;
    socklen_t len = sizeof(sockaddr);
<<<<<<< HEAD
    if (!addrBind.GetSockAddr((struct sockaddr*)&sockaddr, &len))
    {
=======
    if (!addrBind.GetSockAddr((struct sockaddr*)&sockaddr, &len)) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        strError = strprintf("Error: Bind address family for %s not supported", addrBind.ToString());
        LogPrintf("%s\n", strError);
        return false;
    }

    SOCKET hListenSocket = socket(((struct sockaddr*)&sockaddr)->sa_family, SOCK_STREAM, IPPROTO_TCP);
<<<<<<< HEAD
    if (hListenSocket == INVALID_SOCKET)
    {
=======
    if (hListenSocket == INVALID_SOCKET) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        strError = strprintf("Error: Couldn't open socket for incoming connections (socket returned error %s)", NetworkErrorString(WSAGetLastError()));
        LogPrintf("%s\n", strError);
        return false;
    }
<<<<<<< HEAD
    if (!IsSelectableSocket(hListenSocket))
    {
=======
    if (!IsSelectableSocket(hListenSocket)) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        strError = "Error: Couldn't create a listenable socket for incoming connections";
        LogPrintf("%s\n", strError);
        return false;
    }


#ifndef WIN32
#ifdef SO_NOSIGPIPE
    // Different way of disabling SIGPIPE on BSD
    setsockopt(hListenSocket, SOL_SOCKET, SO_NOSIGPIPE, (void*)&nOne, sizeof(int));
#endif
    // Allow binding if the port is still in TIME_WAIT state after
<<<<<<< HEAD
    // the program was closed and restarted.
    setsockopt(hListenSocket, SOL_SOCKET, SO_REUSEADDR, (void*)&nOne, sizeof(int));
    // Disable Nagle's algorithm
    setsockopt(hListenSocket, IPPROTO_TCP, TCP_NODELAY, (void*)&nOne, sizeof(int));
#else
    setsockopt(hListenSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&nOne, sizeof(int));
    setsockopt(hListenSocket, IPPROTO_TCP, TCP_NODELAY, (const char*)&nOne, sizeof(int));
=======
    // the program was closed and restarted. Not an issue on windows!
    setsockopt(hListenSocket, SOL_SOCKET, SO_REUSEADDR, (void*)&nOne, sizeof(int));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#endif

    // Set to non-blocking, incoming connections will also inherit this
    if (!SetSocketNonBlocking(hListenSocket, true)) {
        strError = strprintf("BindListenPort: Setting listening socket to non-blocking failed, error %s\n", NetworkErrorString(WSAGetLastError()));
        LogPrintf("%s\n", strError);
        return false;
    }

    // some systems don't have IPV6_V6ONLY but are always v6only; others do have the option
    // and enable it by default or not. Try to enable it, if possible.
    if (addrBind.IsIPv6()) {
#ifdef IPV6_V6ONLY
#ifdef WIN32
        setsockopt(hListenSocket, IPPROTO_IPV6, IPV6_V6ONLY, (const char*)&nOne, sizeof(int));
#else
        setsockopt(hListenSocket, IPPROTO_IPV6, IPV6_V6ONLY, (void*)&nOne, sizeof(int));
#endif
#endif
#ifdef WIN32
        int nProtLevel = PROTECTION_LEVEL_UNRESTRICTED;
        setsockopt(hListenSocket, IPPROTO_IPV6, IPV6_PROTECTION_LEVEL, (const char*)&nProtLevel, sizeof(int));
#endif
    }

<<<<<<< HEAD
    if (::bind(hListenSocket, (struct sockaddr*)&sockaddr, len) == SOCKET_ERROR)
    {
        int nErr = WSAGetLastError();
        if (nErr == WSAEADDRINUSE)
            strError = strprintf(_("Unable to bind to %s on this computer. GelCoin is probably already running."), addrBind.ToString());
=======
    if (::bind(hListenSocket, (struct sockaddr*)&sockaddr, len) == SOCKET_ERROR) {
        int nErr = WSAGetLastError();
        if (nErr == WSAEADDRINUSE)
            strError = strprintf(_("Unable to bind to %s on this computer. LUX Core is probably already running."), addrBind.ToString());
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        else
            strError = strprintf(_("Unable to bind to %s on this computer (bind returned error %s)"), addrBind.ToString(), NetworkErrorString(nErr));
        LogPrintf("%s\n", strError);
        CloseSocket(hListenSocket);
        return false;
    }
    LogPrintf("Bound to %s\n", addrBind.ToString());

    // Listen for incoming connections
<<<<<<< HEAD
    if (listen(hListenSocket, SOMAXCONN) == SOCKET_ERROR)
    {
=======
    if (listen(hListenSocket, SOMAXCONN) == SOCKET_ERROR) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        strError = strprintf(_("Error: Listening for incoming connections failed (listen returned error %s)"), NetworkErrorString(WSAGetLastError()));
        LogPrintf("%s\n", strError);
        CloseSocket(hListenSocket);
        return false;
    }

    vhListenSocket.push_back(ListenSocket(hListenSocket, fWhitelisted));

    if (addrBind.IsRoutable() && fDiscover && !fWhitelisted)
        AddLocal(addrBind, LOCAL_BIND);

    return true;
}

<<<<<<< HEAD
void Discover(boost::thread_group& threadGroup)
=======
void static Discover(boost::thread_group& threadGroup)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    if (!fDiscover)
        return;

#ifdef WIN32
    // Get local host IP
    char pszHostName[256] = "";
<<<<<<< HEAD
    if (gethostname(pszHostName, sizeof(pszHostName)) != SOCKET_ERROR)
    {
        std::vector<CNetAddr> vaddr;
        if (LookupHost(pszHostName, vaddr, 0, true))
        {
            BOOST_FOREACH (const CNetAddr &addr, vaddr)
            {
=======
    if (gethostname(pszHostName, sizeof(pszHostName)) != SOCKET_ERROR) {
        vector<CNetAddr> vaddr;
        if (LookupHost(pszHostName, vaddr)) {
            BOOST_FOREACH (const CNetAddr& addr, vaddr) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                if (AddLocal(addr, LOCAL_IF))
                    LogPrintf("%s: %s - %s\n", __func__, pszHostName, addr.ToString());
            }
        }
    }
#else
    // Get local host ip
    struct ifaddrs* myaddrs;
<<<<<<< HEAD
    if (getifaddrs(&myaddrs) == 0)
    {
        for (struct ifaddrs* ifa = myaddrs; ifa != NULL; ifa = ifa->ifa_next)
        {
=======
    if (getifaddrs(&myaddrs) == 0) {
        for (struct ifaddrs* ifa = myaddrs; ifa != NULL; ifa = ifa->ifa_next) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            if (ifa->ifa_addr == NULL) continue;
            if ((ifa->ifa_flags & IFF_UP) == 0) continue;
            if (strcmp(ifa->ifa_name, "lo") == 0) continue;
            if (strcmp(ifa->ifa_name, "lo0") == 0) continue;
<<<<<<< HEAD
            if (ifa->ifa_addr->sa_family == AF_INET)
            {
=======
            if (ifa->ifa_addr->sa_family == AF_INET) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                struct sockaddr_in* s4 = (struct sockaddr_in*)(ifa->ifa_addr);
                CNetAddr addr(s4->sin_addr);
                if (AddLocal(addr, LOCAL_IF))
                    LogPrintf("%s: IPv4 %s: %s\n", __func__, ifa->ifa_name, addr.ToString());
<<<<<<< HEAD
            }
            else if (ifa->ifa_addr->sa_family == AF_INET6)
            {
=======
            } else if (ifa->ifa_addr->sa_family == AF_INET6) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                struct sockaddr_in6* s6 = (struct sockaddr_in6*)(ifa->ifa_addr);
                CNetAddr addr(s6->sin6_addr);
                if (AddLocal(addr, LOCAL_IF))
                    LogPrintf("%s: IPv6 %s: %s\n", __func__, ifa->ifa_name, addr.ToString());
            }
        }
        freeifaddrs(myaddrs);
    }
#endif
}

<<<<<<< HEAD
void CConnman::SetNetworkActive(bool active)
{
    if (fDebug) {
        LogPrint("net", "SetNetworkActive: %s\n", active);
    }

    if (!active) {
        fNetworkActive = false;

        LOCK(cs_vNodes);
        // Close sockets to all nodes
        BOOST_FOREACH(CNode* pnode, vNodes) {
            pnode->CloseSocketDisconnect();
        }
    } else {
        fNetworkActive = true;
    }

    uiInterface.NotifyNetworkActiveChanged(fNetworkActive);
}

CConnman::CConnman()
{
    fNetworkActive = true;
    setBannedIsDirty = false;
    fAddressesInitialized = false;
    nLastNodeId = 0;
    nSendBufferMaxSize = 0;
    nReceiveFloodSize = 0;
    semOutbound = NULL;
    semMasternodeOutbound = NULL;
    nMaxConnections = 0;
    nMaxOutbound = 0;
    nBestHeight = 0;
    clientInterface = NULL;
    flagInterruptMsgProc = false;
}

NodeId CConnman::GetNewNodeId()
{
    return nLastNodeId.fetch_add(1, std::memory_order_relaxed);
}

bool CConnman::Start(CScheduler& scheduler, std::string& strNodeError, Options connOptions)
{
    nTotalBytesRecv = 0;
    nTotalBytesSent = 0;
    nMaxOutboundLimit = 0;
    nMaxOutboundTotalBytesSentInCycle = 0;
    nMaxOutboundTimeframe = 60*60*24; //1 day
    nMaxOutboundCycleStartTime = 0;

    nRelevantServices = connOptions.nRelevantServices;
    nLocalServices = connOptions.nLocalServices;
    nMaxConnections = connOptions.nMaxConnections;
    nMaxOutbound = std::min((connOptions.nMaxOutbound), nMaxConnections);
    nMaxFeeler = connOptions.nMaxFeeler;

    nSendBufferMaxSize = connOptions.nSendBufferMaxSize;
    nReceiveFloodSize = connOptions.nReceiveFloodSize;

    SetBestHeight(connOptions.nBestHeight);

    clientInterface = connOptions.uiInterface;
    if (clientInterface)
        clientInterface->InitMessage(_("Loading addresses..."));
    // Load addresses from peers.dat
    int64_t nStart = GetTimeMillis();
    {
        CAddrDB adb;
        if (adb.Read(addrman))
            LogPrintf("Loaded %i addresses from peers.dat  %dms\n", addrman.size(), GetTimeMillis() - nStart);
        else {
            addrman.Clear(); // Addrman can be in an inconsistent state after failure, reset it
            LogPrintf("Invalid or missing peers.dat; recreating\n");
            DumpAddresses();
        }
    }
    if (clientInterface)
        clientInterface->InitMessage(_("Loading banlist..."));
    // Load addresses from banlist.dat
    nStart = GetTimeMillis();
    CBanDB bandb;
    banmap_t banmap;
    if (bandb.Read(banmap)) {
        SetBanned(banmap); // thread save setter
        SetBannedSetDirty(false); // no need to write down, just read data
        SweepBanned(); // sweep out unused entries

        LogPrint("net", "Loaded %d banned node ips/subnets from banlist.dat  %dms\n",
            banmap.size(), GetTimeMillis() - nStart);
    } else {
        LogPrintf("Invalid or missing banlist.dat; recreating\n");
        SetBannedSetDirty(true); // force write
        DumpBanlist();
    }

=======
void StartNode(boost::thread_group& threadGroup)
{
    uiInterface.InitMessage(_("Loading addresses..."));
    // Load addresses for peers.dat
    int64_t nStart = GetTimeMillis();
    {
        CAddrDB adb;
        if (!adb.Read(addrman))
            LogPrintf("Invalid or missing peers.dat; recreating\n");
    }
    LogPrintf("Loaded %i addresses from peers.dat  %dms\n",
        addrman.size(), GetTimeMillis() - nStart);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    fAddressesInitialized = true;

    if (semOutbound == NULL) {
        // initialize semaphore
<<<<<<< HEAD
        semOutbound = new CSemaphore(std::min((nMaxOutbound + nMaxFeeler), nMaxConnections));
    }

    if (semMasternodeOutbound == NULL) {
        // initialize semaphore
        semMasternodeOutbound = new CSemaphore(MAX_OUTBOUND_MASTERNODE_CONNECTIONS);
    }

    if (pnodeLocalHost == NULL) {
        CNetAddr local;
        LookupHost("127.0.0.1", local, false);
        pnodeLocalHost = new CNode(GetNewNodeId(), nLocalServices, GetBestHeight(), INVALID_SOCKET, CAddress(CService(local, 0), nLocalServices));
        GetNodeSignals().InitializeNode(pnodeLocalHost, *this);
    }
=======
        int nMaxOutbound = min(MAX_OUTBOUND_CONNECTIONS, nMaxConnections);
        semOutbound = new CSemaphore(nMaxOutbound);
    }

    if (pnodeLocalHost == NULL)
        pnodeLocalHost = new CNode(INVALID_SOCKET, CAddress(CService("127.0.0.1", 0), nLocalServices));

    Discover(threadGroup);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    //
    // Start threads
    //
<<<<<<< HEAD
    InterruptSocks5(false);
    interruptNet.reset();
    flagInterruptMsgProc = false;

    {
        std::unique_lock<std::mutex> lock(mutexMsgProc);
        fMsgProcWake = false;
    }

    // Send and receive from sockets, accept connections
    threadSocketHandler = std::thread(&TraceThread<std::function<void()> >, "net", std::function<void()>(std::bind(&CConnman::ThreadSocketHandler, this)));
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    if (!GetBoolArg("-dnsseed", true))
        LogPrintf("DNS seeding disabled\n");
    else
<<<<<<< HEAD
        threadDNSAddressSeed = std::thread(&TraceThread<std::function<void()> >, "dnsseed", std::function<void()>(std::bind(&CConnman::ThreadDNSAddressSeed, this)));

    // Initiate outbound connections from -addnode
    threadOpenAddedConnections = std::thread(&TraceThread<std::function<void()> >, "addcon", std::function<void()>(std::bind(&CConnman::ThreadOpenAddedConnections, this)));

    // Initiate outbound connections
    threadOpenConnections = std::thread(&TraceThread<std::function<void()> >, "opencon", std::function<void()>(std::bind(&CConnman::ThreadOpenConnections, this)));

    // Initiate masternode connections
    threadMnbRequestConnections = std::thread(&TraceThread<std::function<void()> >, "mnbcon", std::function<void()>(std::bind(&CConnman::ThreadMnbRequestConnections, this)));

    // Process messages
    threadMessageHandler = std::thread(&TraceThread<std::function<void()> >, "msghand", std::function<void()>(std::bind(&CConnman::ThreadMessageHandler, this)));

    // Dump network addresses
    scheduler.scheduleEvery(boost::bind(&CConnman::DumpData, this), DUMP_ADDRESSES_INTERVAL);
=======
        threadGroup.create_thread(boost::bind(&TraceThread<void (*)()>, "dnsseed", &ThreadDNSAddressSeed));

    // Map ports with UPnP
    MapPort(GetBoolArg("-upnp", DEFAULT_UPNP));

    // Send and receive from sockets, accept connections
    threadGroup.create_thread(boost::bind(&TraceThread<void (*)()>, "net", &ThreadSocketHandler));

    // Initiate outbound connections from -addnode
    threadGroup.create_thread(boost::bind(&TraceThread<void (*)()>, "addcon", &ThreadOpenAddedConnections));

    // Initiate outbound connections
    threadGroup.create_thread(boost::bind(&TraceThread<void (*)()>, "opencon", &ThreadOpenConnections));

    // Process messages
    threadGroup.create_thread(boost::bind(&TraceThread<void (*)()>, "msghand", &ThreadMessageHandler));

    // Dump network addresses
    threadGroup.create_thread(boost::bind(&LoopForever<void (*)()>, "dumpaddr", &DumpAddresses, DUMP_ADDRESSES_INTERVAL * 1000));

    // ppcoin:mint proof-of-stake blocks in the background
    if (GetBoolArg("-staking", true))
        threadGroup.create_thread(boost::bind(&TraceThread<void (*)()>, "stakemint", &ThreadStakeMinter));
}

bool StopNode()
{
    LogPrintf("StopNode()\n");
    MapPort(false);
    if (semOutbound)
        for (int i = 0; i < MAX_OUTBOUND_CONNECTIONS; i++)
            semOutbound->post();

    if (fAddressesInitialized) {
        DumpAddresses();
        fAddressesInitialized = false;
    }
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    return true;
}

class CNetCleanup
{
public:
    CNetCleanup() {}

    ~CNetCleanup()
    {
<<<<<<< HEAD
=======
        // Close sockets
        BOOST_FOREACH (CNode* pnode, vNodes)
            if (pnode->hSocket != INVALID_SOCKET)
                CloseSocket(pnode->hSocket);
        BOOST_FOREACH (ListenSocket& hListenSocket, vhListenSocket)
            if (hListenSocket.socket != INVALID_SOCKET)
                if (!CloseSocket(hListenSocket.socket))
                    LogPrintf("CloseSocket(hListenSocket) failed with error %s\n", NetworkErrorString(WSAGetLastError()));

        // clean up some globals (to help leak detection)
        BOOST_FOREACH (CNode* pnode, vNodes)
            delete pnode;
        BOOST_FOREACH (CNode* pnode, vNodesDisconnected)
            delete pnode;
        vNodes.clear();
        vNodesDisconnected.clear();
        vhListenSocket.clear();
        delete semOutbound;
        semOutbound = NULL;
        delete pnodeLocalHost;
        pnodeLocalHost = NULL;

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#ifdef WIN32
        // Shutdown Windows Sockets
        WSACleanup();
#endif
    }
<<<<<<< HEAD
}
instance_of_cnetcleanup;
=======
} instance_of_cnetcleanup;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

void CExplicitNetCleanup::callCleanup()
{
    // Explicit call to destructor of CNetCleanup because it's not implicitly called
    // when the wallet is restarted from within the wallet itself.
<<<<<<< HEAD
    CNetCleanup *tmp = new CNetCleanup();
    delete tmp; // Stroustrup's gonna kill me for that
}

void CConnman::Interrupt()
{
    {
        std::lock_guard<std::mutex> lock(mutexMsgProc);
        flagInterruptMsgProc = true;
    }
    condMsgProc.notify_all();

    interruptNet();
    InterruptSocks5(true);

    if (semOutbound)
        for (int i=0; i<(nMaxOutbound + nMaxFeeler); i++)
            semOutbound->post();
}

void CConnman::Stop()
{
    if (threadMessageHandler.joinable())
        threadMessageHandler.join();
    if (threadMnbRequestConnections.joinable())
        threadMnbRequestConnections.join();
    if (threadOpenConnections.joinable())
        threadOpenConnections.join();
    if (threadOpenAddedConnections.joinable())
        threadOpenAddedConnections.join();
    if (threadDNSAddressSeed.joinable())
        threadDNSAddressSeed.join();
    if (threadSocketHandler.joinable())
        threadSocketHandler.join();

    if (semMasternodeOutbound)
        for (int i=0; i<MAX_OUTBOUND_MASTERNODE_CONNECTIONS; i++)
            semMasternodeOutbound->post();

    if (fAddressesInitialized)
    {
        DumpData();
        fAddressesInitialized = false;
    }

    // Close sockets
    BOOST_FOREACH(CNode* pnode, vNodes)
        if (pnode->hSocket != INVALID_SOCKET)
            CloseSocket(pnode->hSocket);
    BOOST_FOREACH(ListenSocket& hListenSocket, vhListenSocket)
        if (hListenSocket.socket != INVALID_SOCKET)
            if (!CloseSocket(hListenSocket.socket))
                LogPrintf("CloseSocket(hListenSocket) failed with error %s\n", NetworkErrorString(WSAGetLastError()));

    // clean up some globals (to help leak detection)
    BOOST_FOREACH(CNode *pnode, vNodes) {
        DeleteNode(pnode);
    }
    BOOST_FOREACH(CNode *pnode, vNodesDisconnected) {
        DeleteNode(pnode);
    }
    vNodes.clear();
    vNodesDisconnected.clear();
    vhListenSocket.clear();
    delete semOutbound;
    semOutbound = NULL;
    delete semMasternodeOutbound;
    semMasternodeOutbound = NULL;
    if(pnodeLocalHost)
        DeleteNode(pnodeLocalHost);
    pnodeLocalHost = NULL;
}

void CConnman::DeleteNode(CNode* pnode)
{
    assert(pnode);
    bool fUpdateConnectionTime = false;
    GetNodeSignals().FinalizeNode(pnode->GetId(), fUpdateConnectionTime);
    if(fUpdateConnectionTime)
        addrman.Connected(pnode->addr);
    delete pnode;
}

CConnman::~CConnman()
{
    Interrupt();
    Stop();
}

size_t CConnman::GetAddressCount() const
{
    return addrman.size();
}

void CConnman::SetServices(const CService &addr, ServiceFlags nServices)
{
    addrman.SetServices(addr, nServices);
}

void CConnman::MarkAddressGood(const CAddress& addr)
{
    addrman.Good(addr);
}

void CConnman::AddNewAddress(const CAddress& addr, const CAddress& addrFrom, int64_t nTimePenalty)
{
    addrman.Add(addr, addrFrom, nTimePenalty);
}

void CConnman::AddNewAddresses(const std::vector<CAddress>& vAddr, const CAddress& addrFrom, int64_t nTimePenalty)
{
    addrman.Add(vAddr, addrFrom, nTimePenalty);
}

std::vector<CAddress> CConnman::GetAddresses()
{
    return addrman.GetAddr();
}

bool CConnman::AddNode(const std::string& strNode)
{
    LOCK(cs_vAddedNodes);
    for(std::vector<std::string>::const_iterator it = vAddedNodes.begin(); it != vAddedNodes.end(); ++it) {
        if (strNode == *it)
            return false;
    }

    vAddedNodes.push_back(strNode);
    return true;
}

bool CConnman::RemoveAddedNode(const std::string& strNode)
{
    LOCK(cs_vAddedNodes);
    for(std::vector<std::string>::iterator it = vAddedNodes.begin(); it != vAddedNodes.end(); ++it) {
        if (strNode == *it) {
            vAddedNodes.erase(it);
            return true;
        }
    }
    return false;
}

size_t CConnman::GetNodeCount(NumConnections flags)
{
    LOCK(cs_vNodes);
    if (flags == CConnman::CONNECTIONS_ALL) // Shortcut if we want total
        return vNodes.size();

    int nNum = 0;
    for(std::vector<CNode*>::const_iterator it = vNodes.begin(); it != vNodes.end(); ++it)
        if (flags & ((*it)->fInbound ? CONNECTIONS_IN : CONNECTIONS_OUT))
            nNum++;

    return nNum;
}

void CConnman::GetNodeStats(std::vector<CNodeStats>& vstats)
{
    vstats.clear();
    LOCK(cs_vNodes);
    vstats.reserve(vNodes.size());
    for(std::vector<CNode*>::iterator it = vNodes.begin(); it != vNodes.end(); ++it) {
        CNode* pnode = *it;
        CNodeStats stats;
        pnode->copyStats(stats);
        vstats.push_back(stats);
    }
}

bool CConnman::DisconnectNode(const std::string& strNode)
{
    LOCK(cs_vNodes);
    if (CNode* pnode = FindNode(strNode)) {
        pnode->fDisconnect = true;
        return true;
    }
    return false;
}
bool CConnman::DisconnectNode(NodeId id)
{
    LOCK(cs_vNodes);
    for(CNode* pnode : vNodes) {
        if (id == pnode->id) {
            pnode->fDisconnect = true;
            return true;
        }
    }
    return false;
}

void CConnman::RelayTransaction(const CTransaction& tx)
{
    CDataStream ss(SER_NETWORK, PROTOCOL_VERSION);
    ss.reserve(10000);
    uint256 hash = tx.GetHash();
    CTxLockRequest txLockRequest;
    CDarksendBroadcastTx dstx = CPrivateSend::GetDSTX(hash);
    if(dstx) { // MSG_DSTX
        ss << dstx;
    } else if(instantsend.GetTxLockRequest(hash, txLockRequest)) { // MSG_TXLOCK_REQUEST
        ss << txLockRequest;
    } else { // MSG_TX
        ss << tx;
    }
    RelayTransaction(tx, ss);
}

void CConnman::RelayTransaction(const CTransaction& tx, const CDataStream& ss)
{
    uint256 hash = tx.GetHash();
    int nInv = static_cast<bool>(CPrivateSend::GetDSTX(hash)) ? MSG_DSTX :
                (instantsend.HasTxLockRequest(hash) ? MSG_TXLOCK_REQUEST : MSG_TX);
    CInv inv(nInv, hash);
    {
        LOCK(cs_mapRelay);
        // Expire old relay messages
        while (!vRelayExpiration.empty() && vRelayExpiration.front().first < GetTime())
        {
            mapRelay.erase(vRelayExpiration.front().second);
            vRelayExpiration.pop_front();
        }

        // Save original serialized message so newer versions are preserved
        mapRelay.insert(std::make_pair(inv, ss));
        vRelayExpiration.push_back(std::make_pair(GetTime() + 15 * 60, inv));
    }
    LOCK(cs_vNodes);
    BOOST_FOREACH(CNode* pnode, vNodes)
    {
        if(!pnode->fRelayTxes)
            continue;
        LOCK(pnode->cs_filter);
        if (pnode->pfilter)
        {
            if (pnode->pfilter->IsRelevantAndUpdate(tx))
                pnode->PushInventory(inv);
        } else
            pnode->PushInventory(inv);
    }
}

void CConnman::RelayInv(CInv &inv, const int minProtoVersion) {
    LOCK(cs_vNodes);
    BOOST_FOREACH(CNode* pnode, vNodes)
        if(pnode->nVersion >= minProtoVersion)
            pnode->PushInventory(inv);
}

void CConnman::RecordBytesRecv(uint64_t bytes)
=======
    CNetCleanup* tmp = new CNetCleanup();
    delete tmp; // Stroustrup's gonna kill me for that
}

void RelayTransaction(const CTransaction& tx)
{
    CDataStream ss(SER_NETWORK, PROTOCOL_VERSION);
    ss.reserve(10000);
    ss << tx;
    RelayTransaction(tx, ss);
}

void RelayTransaction(const CTransaction& tx, const CDataStream& ss)
{
    CInv inv(MSG_TX, tx.GetHash());
    {
        LOCK(cs_mapRelay);
        // Expire old relay messages
        while (!vRelayExpiration.empty() && vRelayExpiration.front().first < GetTime()) {
            mapRelay.erase(vRelayExpiration.front().second);
            vRelayExpiration.pop_front();
        }

        // Save original serialized message so newer versions are preserved
        mapRelay.insert(std::make_pair(inv, ss));
        vRelayExpiration.push_back(std::make_pair(GetTime() + 15 * 60, inv));
    }
    LOCK(cs_vNodes);
    unsigned nRelayed = 0;
    BOOST_FOREACH (CNode* pnode, vNodes) {
        if (!pnode->fRelayTxes)
            continue;
        if (pnode->nVersion >= ActiveProtocol()) {
            LOCK(pnode->cs_filter);
            if (pnode->pfilter==nullptr || pnode->pfilter->IsRelevantAndUpdate(tx)) {
                pnode->PushInventory(inv);
                ++nRelayed;
            }
        }
    }
    if (nRelayed == 0) {
        LogPrintf("%s: tx %s not relayed\n", __func__, tx.GetHash().GetHex());
    }
}

void RelayTransactionLockReq(const CTransaction& tx, bool relayToAll)
{
    CInv inv(MSG_TXLOCK_REQUEST, tx.GetHash());

    //broadcast the new lock
    LOCK(cs_vNodes);
    BOOST_FOREACH (CNode* pnode, vNodes) {
        if (!relayToAll && !pnode->fRelayTxes)
            continue;

        pnode->PushMessage("ix", tx);
    }
}

void RelayInv(CInv& inv)
{
    LOCK(cs_vNodes);
    BOOST_FOREACH (CNode* pnode, vNodes) {
        if (pnode->nVersion >= ActiveProtocol())
            pnode->PushInventory(inv);
    }
}

void RelayDarkSendFinalTransaction(const int sessionID, const CTransaction& txNew)
{
    LOCK(cs_vNodes);
    BOOST_FOREACH(CNode* pnode, vNodes) {
        pnode->PushMessage("dsf", sessionID, txNew);
    }
}

void RelayDarkSendIn(const std::vector<CTxIn>& in, const int64_t& nAmount, const CTransaction& txCollateral, const std::vector<CTxOut>& out)
{
    LOCK(cs_vNodes);
    BOOST_FOREACH(CNode* pnode, vNodes) {
        if((CNetAddr)darkSendPool.submittedToMasternode != (CNetAddr)pnode->addr) continue;
        LogPrintf("RelayDarkSendIn - found master, relaying message - %s \n", pnode->addr.ToString().c_str());
        pnode->PushMessage("dsi", in, nAmount, txCollateral, out);
    }
}

void RelayDarkSendStatus(const int sessionID, const int newState, const int newEntriesCount, const int newAccepted, const std::string error)
{
    LOCK(cs_vNodes);
    BOOST_FOREACH(CNode* pnode, vNodes) {
        pnode->PushMessage("dssu", sessionID, newState, newEntriesCount, newAccepted, error);
    }
}

void RelayDarkSendElectionEntry(const CTxIn &vin, const CService addr, const std::vector<unsigned char> vchSig, const int64_t nNow, const CPubKey pubkey, const CPubKey pubkey2, const int count, const int current, const int64_t lastUpdated, const int protocolVersion)
{
    LOCK(cs_vNodes);
    BOOST_FOREACH(CNode* pnode, vNodes) {
        if(!pnode->fRelayTxes) continue;
        pnode->PushMessage("dsee", vin, addr, vchSig, nNow, pubkey, pubkey2, count, current, lastUpdated, protocolVersion);
    }
}

void SendDarkSendElectionEntry(const CTxIn &vin, const CService addr, const std::vector<unsigned char> vchSig, const int64_t nNow, const CPubKey pubkey, const CPubKey pubkey2, const int count, const int current, const int64_t lastUpdated, const int protocolVersion)
{
    LOCK(cs_vNodes);
    BOOST_FOREACH(CNode* pnode, vNodes) {
        pnode->PushMessage("dsee", vin, addr, vchSig, nNow, pubkey, pubkey2, count, current, lastUpdated, protocolVersion);
    }
}

void RelayDarkSendElectionEntryPing(const CTxIn &vin, const std::vector<unsigned char> vchSig, const int64_t nNow, const bool stop)
{
    LOCK(cs_vNodes);
    BOOST_FOREACH(CNode* pnode, vNodes) {
        if(!pnode->fRelayTxes) continue;
        pnode->PushMessage("dseep", vin, vchSig, nNow, stop);
    }
}

void SendDarkSendElectionEntryPing(const CTxIn &vin, const std::vector<unsigned char> vchSig, const int64_t nNow, const bool stop)
{
    LOCK(cs_vNodes);
    BOOST_FOREACH(CNode* pnode, vNodes) {
        pnode->PushMessage("dseep", vin, vchSig, nNow, stop);
    }
}

void RelayDarkSendCompletedTransaction(const int sessionID, const bool error, const std::string errorMessage)
{
    LOCK(cs_vNodes);
    BOOST_FOREACH(CNode* pnode, vNodes) {
        pnode->PushMessage("dsc", sessionID, error, errorMessage);
    }
}

void CNode::RecordBytesRecv(uint64_t bytes)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    LOCK(cs_totalBytesRecv);
    nTotalBytesRecv += bytes;
}

<<<<<<< HEAD
void CConnman::RecordBytesSent(uint64_t bytes)
{
    LOCK(cs_totalBytesSent);
    nTotalBytesSent += bytes;

    uint64_t now = GetTime();
    if (nMaxOutboundCycleStartTime + nMaxOutboundTimeframe < now)
    {
        // timeframe expired, reset cycle
        nMaxOutboundCycleStartTime = now;
        nMaxOutboundTotalBytesSentInCycle = 0;
    }

    // TODO, exclude whitebind peers
    nMaxOutboundTotalBytesSentInCycle += bytes;
}

void CConnman::SetMaxOutboundTarget(uint64_t limit)
{
    LOCK(cs_totalBytesSent);
    uint64_t recommendedMinimum = (nMaxOutboundTimeframe / 600) * MaxBlockSize(true);
    nMaxOutboundLimit = limit;

    if (limit > 0 && limit < recommendedMinimum)
        LogPrintf("Max outbound target is very small (%s bytes) and will be overshot. Recommended minimum is %s bytes.\n", nMaxOutboundLimit, recommendedMinimum);
}

uint64_t CConnman::GetMaxOutboundTarget()
{
    LOCK(cs_totalBytesSent);
    return nMaxOutboundLimit;
}

uint64_t CConnman::GetMaxOutboundTimeframe()
{
    LOCK(cs_totalBytesSent);
    return nMaxOutboundTimeframe;
}

uint64_t CConnman::GetMaxOutboundTimeLeftInCycle()
{
    LOCK(cs_totalBytesSent);
    if (nMaxOutboundLimit == 0)
        return 0;

    if (nMaxOutboundCycleStartTime == 0)
        return nMaxOutboundTimeframe;

    uint64_t cycleEndTime = nMaxOutboundCycleStartTime + nMaxOutboundTimeframe;
    uint64_t now = GetTime();
    return (cycleEndTime < now) ? 0 : cycleEndTime - GetTime();
}

void CConnman::SetMaxOutboundTimeframe(uint64_t timeframe)
{
    LOCK(cs_totalBytesSent);
    if (nMaxOutboundTimeframe != timeframe)
    {
        // reset measure-cycle in case of changing
        // the timeframe
        nMaxOutboundCycleStartTime = GetTime();
    }
    nMaxOutboundTimeframe = timeframe;
}

bool CConnman::OutboundTargetReached(bool historicalBlockServingLimit)
{
    LOCK(cs_totalBytesSent);
    if (nMaxOutboundLimit == 0)
        return false;

    if (historicalBlockServingLimit)
    {
        // keep a large enough buffer to at least relay each block once
        uint64_t timeLeftInCycle = GetMaxOutboundTimeLeftInCycle();
        uint64_t buffer = timeLeftInCycle / 600 * MaxBlockSize(fDIP0001ActiveAtTip);
        if (buffer >= nMaxOutboundLimit || nMaxOutboundTotalBytesSentInCycle >= nMaxOutboundLimit - buffer)
            return true;
    }
    else if (nMaxOutboundTotalBytesSentInCycle >= nMaxOutboundLimit)
        return true;

    return false;
}

uint64_t CConnman::GetOutboundTargetBytesLeft()
{
    LOCK(cs_totalBytesSent);
    if (nMaxOutboundLimit == 0)
        return 0;

    return (nMaxOutboundTotalBytesSentInCycle >= nMaxOutboundLimit) ? 0 : nMaxOutboundLimit - nMaxOutboundTotalBytesSentInCycle;
}

uint64_t CConnman::GetTotalBytesRecv()
{
    LOCK(cs_totalBytesRecv);
    return nTotalBytesRecv;
}

uint64_t CConnman::GetTotalBytesSent()
{
    LOCK(cs_totalBytesSent);
    return nTotalBytesSent;
}

ServiceFlags CConnman::GetLocalServices() const
{
    return nLocalServices;
}

void CConnman::SetBestHeight(int height)
{
    nBestHeight.store(height, std::memory_order_release);
}

int CConnman::GetBestHeight() const
{
    return nBestHeight.load(std::memory_order_acquire);
}

unsigned int CConnman::GetReceiveFloodSize() const { return nReceiveFloodSize; }
unsigned int CConnman::GetSendBufferSize() const{ return nSendBufferMaxSize; }

CNode::CNode(NodeId idIn, ServiceFlags nLocalServicesIn, int nMyStartingHeightIn, SOCKET hSocketIn, const CAddress& addrIn, const std::string& addrNameIn, bool fInboundIn, bool fNetworkNodeIn) :
    addrKnown(5000, 0.001),
    filterInventoryKnown(50000, 0.000001),
    nSendVersion(0)
{
    nServices = NODE_NONE;
    nServicesExpected = NODE_NONE;
=======
void CNode::RecordBytesSent(uint64_t bytes)
{
    LOCK(cs_totalBytesSent);
    nTotalBytesSent += bytes;
}

uint64_t CNode::GetTotalBytesRecv()
{
    LOCK(cs_totalBytesRecv);
    return nTotalBytesRecv;
}

uint64_t CNode::GetTotalBytesSent()
{
    LOCK(cs_totalBytesSent);
    return nTotalBytesSent;
}

void CNode::Fuzz(int nChance)
{
    if (!fSuccessfullyConnected) return; // Don't fuzz initial handshake
    if (GetRand(nChance) != 0) return;   // Fuzz 1 of every nChance messages

    switch (GetRand(3)) {
    case 0:
        // xor a random byte with a random value:
        if (!ssSend.empty()) {
            CDataStream::size_type pos = GetRand(ssSend.size());
            ssSend[pos] ^= (unsigned char)(GetRand(256));
        }
        break;
    case 1:
        // delete a random byte:
        if (!ssSend.empty()) {
            CDataStream::size_type pos = GetRand(ssSend.size());
            ssSend.erase(ssSend.begin() + pos);
        }
        break;
    case 2:
        // insert a random byte at a random position
        {
            CDataStream::size_type pos = GetRand(ssSend.size());
            char ch = (char)GetRand(256);
            ssSend.insert(ssSend.begin() + pos, ch);
        }
        break;
    }
    // Chance of more than one change half the time:
    // (more changes exponentially less likely):
    Fuzz(2);
}

//
// CAddrDB
//

CAddrDB::CAddrDB()
{
    pathAddr = GetDataDir() / "peers.dat";
}

bool CAddrDB::Write(const CAddrMan& addr)
{
    // Generate random temporary filename
    unsigned short randv = 0;
    GetRandBytes((unsigned char*)&randv, sizeof(randv));
    std::string tmpfn = strprintf("peers.dat.%04x", randv);

    // serialize addresses, checksum data up to that point, then append csum
    CDataStream ssPeers(SER_DISK, CLIENT_VERSION);
    ssPeers << FLATDATA(Params().MessageStart());
    ssPeers << addr;
    uint256 hash = Hash(ssPeers.begin(), ssPeers.end());
    ssPeers << hash;

    // open output file, and associate with CAutoFile
    boost::filesystem::path pathAddr = GetDataDir() / "peers.dat";
    FILE* file = fopen(pathAddr.string().c_str(), "wb");
    CAutoFile fileout(file, SER_DISK, CLIENT_VERSION);
    if (fileout.IsNull())
        return error("%s : Failed to open file %s", __func__, pathAddr.string());

    // Write and commit header, data
    try {
        fileout << ssPeers;
    } catch (std::exception& e) {
        return error("%s : Serialize or I/O error - %s", __func__, e.what());
    }
    FileCommit(fileout.Get());
    fileout.fclose();

    return true;
}

bool CAddrDB::Read(CAddrMan& addr)
{
    // open input file, and associate with CAutoFile
    FILE* file = fopen(pathAddr.string().c_str(), "rb");
    CAutoFile filein(file, SER_DISK, CLIENT_VERSION);
    if (filein.IsNull())
        return error("%s : Failed to open file %s", __func__, pathAddr.string());

    // use file size to size memory buffer
    int fileSize = boost::filesystem::file_size(pathAddr);
    int dataSize = fileSize - sizeof(uint256);
    // Don't try to resize to a negative number if file is small
    if (dataSize < 0)
        dataSize = 0;
    vector<unsigned char> vchData;
    vchData.resize(dataSize);
    uint256 hashIn;

    // read data and checksum from file
    try {
        filein.read((char*)&vchData[0], dataSize);
        filein >> hashIn;
    } catch (std::exception& e) {
        return error("%s : Deserialize or I/O error - %s", __func__, e.what());
    }
    filein.fclose();

    CDataStream ssPeers(vchData, SER_DISK, CLIENT_VERSION);

    // verify stored checksum matches input data
    uint256 hashTmp = Hash(ssPeers.begin(), ssPeers.end());
    if (hashIn != hashTmp)
        return error("%s : Checksum mismatch, data corrupted", __func__);

    unsigned char pchMsgTmp[4];
    try {
        // de-serialize file header (network specific magic number) and ..
        ssPeers >> FLATDATA(pchMsgTmp);

        // ... verify the network matches ours
        if (memcmp(pchMsgTmp, Params().MessageStart(), sizeof(pchMsgTmp)))
            return error("%s : Invalid network magic number", __func__);

        // de-serialize address data into one CAddrMan object
        ssPeers >> addr;
    } catch (std::exception& e) {
        return error("%s : Deserialize or I/O error - %s", __func__, e.what());
    }

    return true;
}

unsigned int ReceiveFloodSize() { return 1000 * GetArg("-maxreceivebuffer", 5 * 1000); }
unsigned int SendBufferSize() { return 1000 * GetArg("-maxsendbuffer", 1 * 1000); }

CNode::CNode(SOCKET hSocketIn, CAddress addrIn, std::string addrNameIn, bool fInboundIn) : ssSend(SER_NETWORK, INIT_PROTO_VERSION), setAddrKnown(5000)
{
    nServices = 0;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    hSocket = hSocketIn;
    nRecvVersion = INIT_PROTO_VERSION;
    nLastSend = 0;
    nLastRecv = 0;
    nSendBytes = 0;
    nRecvBytes = 0;
<<<<<<< HEAD
    nTimeConnected = GetSystemTimeInSeconds();
    nTimeOffset = 0;
    addr = addrIn;
    addrName = addrNameIn == "" ? addr.ToStringIPPort() : addrNameIn;
    nVersion = 0;
    nNumWarningsSkipped = 0;
    nLastWarningTime = 0;
=======
    nTimeConnected = GetTime();
    addr = addrIn;
    addrName = addrNameIn == "" ? addr.ToStringIPPort() : addrNameIn;
    nVersion = 0;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    strSubVer = "";
    fWhitelisted = false;
    fOneShot = false;
    fClient = false; // set by version message
<<<<<<< HEAD
    fFeeler = false;
    fInbound = fInboundIn;
    fNetworkNode = fNetworkNodeIn;
=======
    fInbound = fInboundIn;
    fNetworkNode = false;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    fSuccessfullyConnected = false;
    fDisconnect = false;
    nRefCount = 0;
    nSendSize = 0;
    nSendOffset = 0;
<<<<<<< HEAD
    hashContinue = uint256();
    nStartingHeight = -1;
    filterInventoryKnown.reset();
    fGetAddr = false;
    nNextLocalAddrSend = 0;
    nNextAddrSend = 0;
    nNextInvSend = 0;
    fRelayTxes = false;
    pfilter = new CBloomFilter();
    nLastBlockTime = 0;
    nLastTXTime = 0;
=======
    hashContinue = 0;
    nStartingHeight = -1;
    fGetAddr = false;
    fRelayTxes = false;
    setInventoryKnown.max_size(SendBufferSize() / 1000);
    pfilter = new CBloomFilter();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    nPingNonceSent = 0;
    nPingUsecStart = 0;
    nPingUsecTime = 0;
    fPingQueued = false;
<<<<<<< HEAD
    fMasternode = false;
    nMinPingUsecTime = std::numeric_limits<int64_t>::max();
    vchKeyedNetGroup = CalculateKeyedNetGroup(addr);
    id = idIn;
    nLocalServices = nLocalServicesIn;
    fPauseRecv = false;
    fPauseSend = false;
    nProcessQueueSize = 0;

    GetRandBytes((unsigned char*)&nLocalHostNonce, sizeof(nLocalHostNonce));
    nMyStartingHeight = nMyStartingHeightIn;

    BOOST_FOREACH(const std::string &msg, getAllNetMessageTypes())
        mapRecvBytesPerMsgCmd[msg] = 0;
    mapRecvBytesPerMsgCmd[NET_MESSAGE_COMMAND_OTHER] = 0;

    if(fNetworkNode || fInbound)
        AddRef();
=======
    fDarkSendMaster = false;

    {
        LOCK(cs_nLastNodeId);
        id = nLastNodeId++;
    }
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    if (fLogIPs)
        LogPrint("net", "Added connection to %s peer=%d\n", addrName, id);
    else
        LogPrint("net", "Added connection peer=%d\n", id);
<<<<<<< HEAD
=======

    // Be shy and don't send version until we hear
    if (hSocket != INVALID_SOCKET && !fInbound)
        PushVersion();

    GetNodeSignals().InitializeNode(GetId(), this);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

CNode::~CNode()
{
    CloseSocket(hSocket);

    if (pfilter)
        delete pfilter;
<<<<<<< HEAD
=======

    GetNodeSignals().FinalizeNode(GetId());
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

void CNode::AskFor(const CInv& inv)
{
<<<<<<< HEAD
    if (mapAskFor.size() > MAPASKFOR_MAX_SZ || setAskFor.size() > SETASKFOR_MAX_SZ) {
        int64_t nNow = GetTime();
        if(nNow - nLastWarningTime > WARNING_INTERVAL) {
            LogPrintf("CNode::AskFor -- WARNING: inventory message dropped: mapAskFor.size = %d, setAskFor.size = %d, MAPASKFOR_MAX_SZ = %d, SETASKFOR_MAX_SZ = %d, nSkipped = %d, peer=%d\n",
                      mapAskFor.size(), setAskFor.size(), MAPASKFOR_MAX_SZ, SETASKFOR_MAX_SZ, nNumWarningsSkipped, id);
            nLastWarningTime = nNow;
            nNumWarningsSkipped = 0;
        }
        else {
            ++nNumWarningsSkipped;
        }
        return;
    }
    // a peer may not have multiple non-responded queue positions for a single inv item
    if (!setAskFor.insert(inv.hash).second)
        return;

    // We're using mapAskFor as a priority queue,
    // the key is the earliest time the request can be sent
    int64_t nRequestTime;
    limitedmap<uint256, int64_t>::const_iterator it = mapAlreadyAskedFor.find(inv.hash);
=======
    if (mapAskFor.size() > MAPASKFOR_MAX_SZ)
        return;
    // We're using mapAskFor as a priority queue,
    // the key is the earliest time the request can be sent
    int64_t nRequestTime;
    limitedmap<CInv, int64_t>::const_iterator it = mapAlreadyAskedFor.find(inv);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    if (it != mapAlreadyAskedFor.end())
        nRequestTime = it->second;
    else
        nRequestTime = 0;
<<<<<<< HEAD

    LogPrint("net", "askfor %s  %d (%s) peer=%d\n", inv.ToString(), nRequestTime, DateTimeStrFormat("%H:%M:%S", nRequestTime/1000000), id);
=======
    LogPrint("net", "askfor %s  %d (%s) peer=%d\n", inv.ToString(), nRequestTime, DateTimeStrFormat("%H:%M:%S", nRequestTime / 1000000), id);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    // Make sure not to reuse time indexes to keep things in the same order
    int64_t nNow = GetTimeMicros() - 1000000;
    static int64_t nLastTime;
    ++nLastTime;
    nNow = std::max(nNow, nLastTime);
    nLastTime = nNow;

    // Each retry is 2 minutes after the last
    nRequestTime = std::max(nRequestTime + 2 * 60 * 1000000, nNow);
    if (it != mapAlreadyAskedFor.end())
        mapAlreadyAskedFor.update(it, nRequestTime);
    else
<<<<<<< HEAD
        mapAlreadyAskedFor.insert(std::make_pair(inv.hash, nRequestTime));
    mapAskFor.insert(std::make_pair(nRequestTime, inv));
}

bool CConnman::NodeFullyConnected(const CNode* pnode)
{
    return pnode && pnode->fSuccessfullyConnected && !pnode->fDisconnect;
}

std::vector<unsigned char> CNode::CalculateKeyedNetGroup(CAddress& address)
{
    if(vchSecretKey.size() == 0) {
        vchSecretKey.resize(32, 0);
        GetRandBytes(vchSecretKey.data(), vchSecretKey.size());
    }

    std::vector<unsigned char> vchGroup;
    CSHA256 hash;
    std::vector<unsigned char> vch(32);

    vchGroup = address.GetGroup();

    hash.Write(begin_ptr(vchGroup), vchGroup.size());

    hash.Write(begin_ptr(vchSecretKey), vchSecretKey.size());

    hash.Finalize(begin_ptr(vch));
    return vch;
}

CDataStream CConnman::BeginMessage(CNode* pnode, int nVersion, int flags, const std::string& sCommand)
{
    return {SER_NETWORK, (nVersion ? nVersion : pnode->GetSendVersion()) | flags, CMessageHeader(Params().MessageStart(), sCommand.c_str(), 0) };
}

void CConnman::EndMessage(CDataStream& strm)
{
    // Set the size
    assert(strm.size () >= CMessageHeader::HEADER_SIZE);
    unsigned int nSize = strm.size() - CMessageHeader::HEADER_SIZE;
    WriteLE32((uint8_t*)&strm[CMessageHeader::MESSAGE_SIZE_OFFSET], nSize);
    // Set the checksum
    uint256 hash = Hash(strm.begin() + CMessageHeader::HEADER_SIZE, strm.end());
    memcpy((char*)&strm[CMessageHeader::CHECKSUM_OFFSET], hash.begin(), CMessageHeader::CHECKSUM_SIZE);

}

void CConnman::PushMessage(CNode* pnode, CDataStream& strm, const std::string& sCommand)
{
    if(strm.empty())
        return;

    unsigned int nSize = strm.size() - CMessageHeader::HEADER_SIZE;
    LogPrint("net", "sending %s (%d bytes) peer=%d\n",  SanitizeString(sCommand.c_str()), nSize, pnode->id);

    size_t nBytesSent = 0;
    {
        LOCK(pnode->cs_vSend);
        if(pnode->hSocket == INVALID_SOCKET) {
            return;
        }
        bool optimisticSend(pnode->vSendMsg.empty());
        pnode->vSendMsg.emplace_back(strm.begin(), strm.end());

        //log total amount of bytes per command
        pnode->mapSendBytesPerMsgCmd[sCommand] += strm.size();
        pnode->nSendSize += strm.size();

        if (pnode->nSendSize > nSendBufferMaxSize)
            pnode->fPauseSend = true;

        // If write queue empty, attempt "optimistic write"
        if (optimisticSend == true)
            nBytesSent = SocketSendData(pnode);
    }
    if (nBytesSent)
        RecordBytesSent(nBytesSent);
}

bool CConnman::ForNode(const CService& addr, std::function<bool(const CNode* pnode)> cond, std::function<bool(CNode* pnode)> func)
{
    CNode* found = nullptr;
    LOCK(cs_vNodes);
    for (auto&& pnode : vNodes) {
        if((CService)pnode->addr == addr) {
            found = pnode;
            break;
        }
    }
    return found != nullptr && cond(found) && func(found);
}

bool CConnman::ForNode(NodeId id, std::function<bool(const CNode* pnode)> cond, std::function<bool(CNode* pnode)> func)
{
    CNode* found = nullptr;
    LOCK(cs_vNodes);
    for (auto&& pnode : vNodes) {
        if(pnode->id == id) {
            found = pnode;
            break;
        }
    }
    return found != nullptr && cond(found) && func(found);
}

int64_t PoissonNextSend(int64_t nNow, int average_interval_seconds) {
    return nNow + (int64_t)(log1p(GetRand(1ULL << 48) * -0.0000000000000035527136788 /* -1/2^48 */) * average_interval_seconds * -1000000.0 + 0.5);
}

std::vector<CNode*> CConnman::CopyNodeVector()
{
    std::vector<CNode*> vecNodesCopy;
    LOCK(cs_vNodes);
    for(size_t i = 0; i < vNodes.size(); ++i) {
        CNode* pnode = vNodes[i];
        pnode->AddRef();
        vecNodesCopy.push_back(pnode);
    }
    return vecNodesCopy;
}

void CConnman::ReleaseNodeVector(const std::vector<CNode*>& vecNodes)
{
    LOCK(cs_vNodes);
    for(size_t i = 0; i < vecNodes.size(); ++i) {
        CNode* pnode = vecNodes[i];
        pnode->Release();
    }
=======
        mapAlreadyAskedFor.insert(std::make_pair(inv, nRequestTime));
    mapAskFor.insert(std::make_pair(nRequestTime, inv));
}

void CNode::BeginMessage(const char* pszCommand) EXCLUSIVE_LOCK_FUNCTION(cs_vSend)
{
    ENTER_CRITICAL_SECTION(cs_vSend);
    assert(ssSend.size() == 0);
    ssSend << CMessageHeader(pszCommand, 0);
    LogPrint("net", "sending: %s ", SanitizeString(pszCommand));
}

void CNode::AbortMessage() UNLOCK_FUNCTION(cs_vSend)
{
    ssSend.clear();

    LEAVE_CRITICAL_SECTION(cs_vSend);

    LogPrint("net", "(aborted)\n");
}

void CNode::EndMessage() UNLOCK_FUNCTION(cs_vSend)
{
    // The -*messagestest options are intentionally not documented in the help message,
    // since they are only used during development to debug the networking code and are
    // not intended for end-users.
    if (mapArgs.count("-dropmessagestest") && GetRand(GetArg("-dropmessagestest", 2)) == 0) {
        LogPrint("net", "dropmessages DROPPING SEND MESSAGE\n");
        AbortMessage();
        return;
    }
    if (mapArgs.count("-fuzzmessagestest"))
        Fuzz(GetArg("-fuzzmessagestest", 10));

    if (ssSend.size() == 0)
        return;

    // Set the size
    unsigned int nSize = ssSend.size() - CMessageHeader::HEADER_SIZE;
    memcpy((char*)&ssSend[CMessageHeader::MESSAGE_SIZE_OFFSET], &nSize, sizeof(nSize));

    // Set the checksum
    uint256 hash = Hash(ssSend.begin() + CMessageHeader::HEADER_SIZE, ssSend.end());
    unsigned int nChecksum = 0;
    memcpy(&nChecksum, &hash, sizeof(nChecksum));
    assert(ssSend.size() >= CMessageHeader::CHECKSUM_OFFSET + sizeof(nChecksum));
    memcpy((char*)&ssSend[CMessageHeader::CHECKSUM_OFFSET], &nChecksum, sizeof(nChecksum));

    LogPrint("net", "(%d bytes) peer=%d\n", nSize, id);

    std::deque<CSerializeData>::iterator it = vSendMsg.insert(vSendMsg.end(), CSerializeData());
    ssSend.GetAndClear(*it);
    nSendSize += (*it).size();

    // If write queue empty, attempt "optimistic write"
    if (it == vSendMsg.begin())
        SocketSendData(this);

    LEAVE_CRITICAL_SECTION(cs_vSend);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}
