<<<<<<< HEAD
// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2010 Satoshi Nakamoto                          -*- c++ -*-
// Copyright (c) 2009-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_ALERT_H
#define BITCOIN_ALERT_H

#include "serialize.h"
#include "sync.h"

#include <map>
#include <set>
#include <stdint.h>
#include <string>

class CAlert;
class CNode;
<<<<<<< HEAD
class CConnman;
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
class uint256;

extern std::map<uint256, CAlert> mapAlerts;
extern CCriticalSection cs_mapAlerts;

/** Alerts are for notifying old versions if they become too obsolete and
 * need to upgrade.  The message is displayed in the status bar.
 * Alert messages are broadcast as a vector of signed data.  Unserializing may
 * not read the entire buffer if the alert is for a newer version, but older
 * versions can still relay the original data.
 */
class CUnsignedAlert
{
public:
    int nVersion;
<<<<<<< HEAD
    int64_t nRelayUntil;      // when newer nodes stop relaying to newer nodes
=======
    int64_t nRelayUntil; // when newer nodes stop relaying to newer nodes
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    int64_t nExpiration;
    int nID;
    int nCancel;
    std::set<int> setCancel;
<<<<<<< HEAD
    int nMinVer;            // lowest version inclusive
    int nMaxVer;            // highest version inclusive
    std::set<std::string> setSubVer;  // empty matches all
=======
    int nMinVer;                     // lowest version inclusive
    int nMaxVer;                     // highest version inclusive
    std::set<std::string> setSubVer; // empty matches all
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    int nPriority;

    // Actions
    std::string strComment;
    std::string strStatusBar;
    std::string strReserved;

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
<<<<<<< HEAD
    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion) {
=======
    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion)
    {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        READWRITE(this->nVersion);
        nVersion = this->nVersion;
        READWRITE(nRelayUntil);
        READWRITE(nExpiration);
        READWRITE(nID);
        READWRITE(nCancel);
        READWRITE(setCancel);
        READWRITE(nMinVer);
        READWRITE(nMaxVer);
        READWRITE(setSubVer);
        READWRITE(nPriority);

        READWRITE(LIMITED_STRING(strComment, 65536));
        READWRITE(LIMITED_STRING(strStatusBar, 256));
        READWRITE(LIMITED_STRING(strReserved, 256));
    }

    void SetNull();

    std::string ToString() const;
};

/** An alert is a combination of a serialized CUnsignedAlert and a signature. */
class CAlert : public CUnsignedAlert
{
public:
    std::vector<unsigned char> vchMsg;
    std::vector<unsigned char> vchSig;

    CAlert()
    {
        SetNull();
    }

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
<<<<<<< HEAD
    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion) {
=======
    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion)
    {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        READWRITE(vchMsg);
        READWRITE(vchSig);
    }

    void SetNull();
    bool IsNull() const;
    uint256 GetHash() const;
    bool IsInEffect() const;
    bool Cancels(const CAlert& alert) const;
<<<<<<< HEAD
    bool AppliesTo(int nVersion, const std::string& strSubVerIn) const;
    bool AppliesToMe() const;
    bool RelayTo(CNode* pnode, CConnman& connman) const;
    bool Sign();
    bool CheckSignature(const std::vector<unsigned char>& alertKey) const;
    bool ProcessAlert(const std::vector<unsigned char>& alertKey, bool fThread = true); // fThread means run -alertnotify in a free-running thread
=======
    bool AppliesTo(int nVersion, std::string strSubVerIn) const;
    bool AppliesToMe() const;
    bool RelayTo(CNode* pnode) const;
    bool CheckSignature() const;
    bool ProcessAlert(bool fThread = true); // fThread means run -alertnotify in a free-running thread
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    static void Notify(const std::string& strMessage, bool fThread);

    /*
     * Get copy of (active) alert object by hash. Returns a null alert if it is not found.
     */
<<<<<<< HEAD
    static CAlert getAlertByHash(const uint256 &hash);
=======
    static CAlert getAlertByHash(const uint256& hash);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};

#endif // BITCOIN_ALERT_H
