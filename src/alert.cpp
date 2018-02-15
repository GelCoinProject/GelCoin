// Copyright (c) 2010 Satoshi Nakamoto
<<<<<<< HEAD
// Copyright (c) 2009-2015 The Bitcoin Core developers
=======
// Copyright (c) 2009-2014 The Bitcoin developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "alert.h"

<<<<<<< HEAD
#include "base58.h"
=======
#include "chainparams.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include "clientversion.h"
#include "net.h"
#include "pubkey.h"
#include "timedata.h"
#include "ui_interface.h"
#include "util.h"
<<<<<<< HEAD
#include "utilstrencodings.h"

#include <stdint.h>
#include <algorithm>
#include <map>
=======

#include <algorithm>
#include <map>
#include <stdint.h>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/foreach.hpp>
#include <boost/thread.hpp>

using namespace std;

map<uint256, CAlert> mapAlerts;
CCriticalSection cs_mapAlerts;

void CUnsignedAlert::SetNull()
{
    nVersion = 1;
    nRelayUntil = 0;
    nExpiration = 0;
    nID = 0;
    nCancel = 0;
    setCancel.clear();
    nMinVer = 0;
    nMaxVer = 0;
    setSubVer.clear();
    nPriority = 0;

    strComment.clear();
    strStatusBar.clear();
    strReserved.clear();
}

std::string CUnsignedAlert::ToString() const
{
    std::string strSetCancel;
<<<<<<< HEAD
    BOOST_FOREACH(int n, setCancel)
        strSetCancel += strprintf("%d ", n);
    std::string strSetSubVer;
    BOOST_FOREACH(const std::string& str, setSubVer)
=======
    for (auto& n: setCancel)
        strSetCancel += strprintf("%d ", n);
    std::string strSetSubVer;
    BOOST_FOREACH (std::string str, setSubVer)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        strSetSubVer += "\"" + str + "\" ";
    return strprintf(
        "CAlert(\n"
        "    nVersion     = %d\n"
        "    nRelayUntil  = %d\n"
        "    nExpiration  = %d\n"
        "    nID          = %d\n"
        "    nCancel      = %d\n"
        "    setCancel    = %s\n"
        "    nMinVer      = %d\n"
        "    nMaxVer      = %d\n"
        "    setSubVer    = %s\n"
        "    nPriority    = %d\n"
        "    strComment   = \"%s\"\n"
        "    strStatusBar = \"%s\"\n"
        ")\n",
        nVersion,
        nRelayUntil,
        nExpiration,
        nID,
        nCancel,
        strSetCancel,
        nMinVer,
        nMaxVer,
        strSetSubVer,
        nPriority,
        strComment,
        strStatusBar);
}

void CAlert::SetNull()
{
    CUnsignedAlert::SetNull();
    vchMsg.clear();
    vchSig.clear();
}

bool CAlert::IsNull() const
{
    return (nExpiration == 0);
}

uint256 CAlert::GetHash() const
{
    return Hash(this->vchMsg.begin(), this->vchMsg.end());
}

bool CAlert::IsInEffect() const
{
    return (GetAdjustedTime() < nExpiration);
}

bool CAlert::Cancels(const CAlert& alert) const
{
    if (!IsInEffect())
        return false; // this was a no-op before 31403
    return (alert.nID <= nCancel || setCancel.count(alert.nID));
}

<<<<<<< HEAD
bool CAlert::AppliesTo(int nVersion, const std::string& strSubVerIn) const
=======
bool CAlert::AppliesTo(int nVersion, std::string strSubVerIn) const
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    // TODO: rework for client-version-embedded-in-strSubVer ?
    return (IsInEffect() &&
            nMinVer <= nVersion && nVersion <= nMaxVer &&
            (setSubVer.empty() || setSubVer.count(strSubVerIn)));
}

bool CAlert::AppliesToMe() const
{
    return AppliesTo(PROTOCOL_VERSION, FormatSubVersion(CLIENT_NAME, CLIENT_VERSION, std::vector<std::string>()));
}

<<<<<<< HEAD
bool CAlert::RelayTo(CNode* pnode, CConnman& connman) const
=======
bool CAlert::RelayTo(CNode* pnode) const
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    if (!IsInEffect())
        return false;
    // don't relay to nodes which haven't sent their version message
    if (pnode->nVersion == 0)
        return false;
    // returns true if wasn't already contained in the set
<<<<<<< HEAD
    if (pnode->setKnown.insert(GetHash()).second)
    {
        if (AppliesTo(pnode->nVersion, pnode->strSubVer) ||
            AppliesToMe() ||
            GetAdjustedTime() < nRelayUntil)
        {
            connman.PushMessage(pnode, NetMsgType::ALERT, *this);
=======
    if (pnode->setKnown.insert(GetHash()).second) {
        if (AppliesTo(pnode->nVersion, pnode->strSubVer) ||
            AppliesToMe() ||
            GetAdjustedTime() < nRelayUntil) {
            pnode->PushMessage("alert", *this);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            return true;
        }
    }
    return false;
}

<<<<<<< HEAD
bool CAlert::Sign()
{
    CDataStream sMsg(SER_NETWORK, CLIENT_VERSION);
    sMsg << *(CUnsignedAlert*)this;
    vchMsg = std::vector<unsigned char>(sMsg.begin(), sMsg.end());
    CBitcoinSecret vchSecret;
    if (!vchSecret.SetString(GetArg("-alertkey", "")))
    {
        printf("CAlert::SignAlert() : vchSecret.SetString failed\n");
        return false;
    }
    CKey key = vchSecret.GetKey();
    if (!key.Sign(Hash(vchMsg.begin(), vchMsg.end()), vchSig))
    {
        printf("CAlert::SignAlert() : key.Sign failed\n");
        return false;
    }

    return true;
}

bool CAlert::CheckSignature(const std::vector<unsigned char>& alertKey) const
{
    CPubKey key(alertKey);
    if (!key.Verify(Hash(vchMsg.begin(), vchMsg.end()), vchSig))
        return error("CAlert::CheckSignature(): verify signature failed");
=======
bool CAlert::CheckSignature() const
{
    CPubKey key(Params().AlertKey());
    if (!key.Verify(Hash(vchMsg.begin(), vchMsg.end()), vchSig))
        return error("CAlert::CheckSignature() : verify signature failed");
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    // Now unserialize the data
    CDataStream sMsg(vchMsg, SER_NETWORK, PROTOCOL_VERSION);
    sMsg >> *(CUnsignedAlert*)this;
    return true;
}

<<<<<<< HEAD
CAlert CAlert::getAlertByHash(const uint256 &hash)
=======
CAlert CAlert::getAlertByHash(const uint256& hash)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    CAlert retval;
    {
        LOCK(cs_mapAlerts);
        map<uint256, CAlert>::iterator mi = mapAlerts.find(hash);
<<<<<<< HEAD
        if(mi != mapAlerts.end())
=======
        if (mi != mapAlerts.end())
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            retval = mi->second;
    }
    return retval;
}

<<<<<<< HEAD
bool CAlert::ProcessAlert(const std::vector<unsigned char>& alertKey, bool fThread)
{
    if (!CheckSignature(alertKey))
=======
bool CAlert::ProcessAlert(bool fThread)
{
    if (!CheckSignature())
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return false;
    if (!IsInEffect())
        return false;

    // alert.nID=max is reserved for if the alert key is
    // compromised. It must have a pre-defined message,
    // must never expire, must apply to all versions,
    // and must cancel all previous
    // alerts or it will be ignored (so an attacker can't
    // send an "everything is OK, don't panic" version that
    // cannot be overridden):
    int maxInt = std::numeric_limits<int>::max();
<<<<<<< HEAD
    if (nID == maxInt)
    {
        if (!(
                nExpiration == maxInt &&
                nCancel == (maxInt-1) &&
=======
    if (nID == maxInt) {
        if (!(
                nExpiration == maxInt &&
                nCancel == (maxInt - 1) &&
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                nMinVer == 0 &&
                nMaxVer == maxInt &&
                setSubVer.empty() &&
                nPriority == maxInt &&
<<<<<<< HEAD
                strStatusBar == "URGENT: Alert key compromised, upgrade required"
                ))
=======
                strStatusBar == "URGENT: Alert key compromised, upgrade required"))
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            return false;
    }

    {
        LOCK(cs_mapAlerts);
        // Cancel previous alerts
<<<<<<< HEAD
        for (map<uint256, CAlert>::iterator mi = mapAlerts.begin(); mi != mapAlerts.end();)
        {
            const CAlert& alert = (*mi).second;
            if (Cancels(alert))
            {
                LogPrint("alert", "cancelling alert %d\n", alert.nID);
                uiInterface.NotifyAlertChanged((*mi).first, CT_DELETED);
                mapAlerts.erase(mi++);
            }
            else if (!alert.IsInEffect())
            {
                LogPrint("alert", "expiring alert %d\n", alert.nID);
                uiInterface.NotifyAlertChanged((*mi).first, CT_DELETED);
                mapAlerts.erase(mi++);
            }
            else
=======
        for (map<uint256, CAlert>::iterator mi = mapAlerts.begin(); mi != mapAlerts.end();) {
            const CAlert& alert = (*mi).second;
            if (Cancels(alert)) {
                LogPrint("alert", "cancelling alert %d\n", alert.nID);
                uiInterface.NotifyAlertChanged((*mi).first, CT_DELETED);
                mapAlerts.erase(mi++);
            } else if (!alert.IsInEffect()) {
                LogPrint("alert", "expiring alert %d\n", alert.nID);
                uiInterface.NotifyAlertChanged((*mi).first, CT_DELETED);
                mapAlerts.erase(mi++);
            } else
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                mi++;
        }

        // Check if this alert has been cancelled
<<<<<<< HEAD
        BOOST_FOREACH(PAIRTYPE(const uint256, CAlert)& item, mapAlerts)
        {
            const CAlert& alert = item.second;
            if (alert.Cancels(*this))
            {
=======
        BOOST_FOREACH (PAIRTYPE(const uint256, CAlert) & item, mapAlerts) {
            const CAlert& alert = item.second;
            if (alert.Cancels(*this)) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                LogPrint("alert", "alert already cancelled by %d\n", alert.nID);
                return false;
            }
        }

        // Add to mapAlerts
        mapAlerts.insert(make_pair(GetHash(), *this));
        // Notify UI and -alertnotify if it applies to me
<<<<<<< HEAD
        if(AppliesToMe())
        {
=======
        if (AppliesToMe()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            uiInterface.NotifyAlertChanged(GetHash(), CT_NEW);
            Notify(strStatusBar, fThread);
        }
    }

    LogPrint("alert", "accepted alert %d, AppliesToMe()=%d\n", nID, AppliesToMe());
    return true;
}

<<<<<<< HEAD
void
CAlert::Notify(const std::string& strMessage, bool fThread)
=======
void CAlert::Notify(const std::string& strMessage, bool fThread)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    std::string strCmd = GetArg("-alertnotify", "");
    if (strCmd.empty()) return;

    // Alert text should be plain ascii coming from a trusted source, but to
    // be safe we first strip anything not in safeChars, then add single quotes around
    // the whole string before passing it to the shell:
    std::string singleQuote("'");
    std::string safeStatus = SanitizeString(strMessage);
<<<<<<< HEAD
    safeStatus = singleQuote+safeStatus+singleQuote;
=======
    safeStatus = singleQuote + safeStatus + singleQuote;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    boost::replace_all(strCmd, "%s", safeStatus);

    if (fThread)
        boost::thread t(runCommand, strCmd); // thread runs free
    else
        runCommand(strCmd);
}
