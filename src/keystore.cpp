// Copyright (c) 2009-2010 Satoshi Nakamoto
<<<<<<< HEAD
// Copyright (c) 2009-2015 The Bitcoin Core developers
=======
// Copyright (c) 2009-2014 The Bitcoin developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "keystore.h"

<<<<<<< HEAD
#include "key.h"
#include "pubkey.h"
=======
#include "crypter.h"
#include "key.h"
#include "script/script.h"
#include "script/standard.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include "util.h"

#include <boost/foreach.hpp>

<<<<<<< HEAD
bool CKeyStore::AddKey(const CKey &key) {
    return AddKeyPubKey(key, key.GetPubKey());
}

bool CBasicKeyStore::GetPubKey(const CKeyID &address, CPubKey &vchPubKeyOut) const
{
    CKey key;
    if (!GetKey(address, key)) {
        LOCK(cs_KeyStore);
        WatchKeyMap::const_iterator it = mapWatchKeys.find(address);
        if (it != mapWatchKeys.end()) {
            vchPubKeyOut = it->second;
            return true;
        }
        return false;
    }
=======
bool CKeyStore::GetPubKey(const CKeyID& address, CPubKey& vchPubKeyOut) const
{
    CKey key;
    if (!GetKey(address, key))
        return false;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    vchPubKeyOut = key.GetPubKey();
    return true;
}

<<<<<<< HEAD
bool CBasicKeyStore::AddKeyPubKey(const CKey& key, const CPubKey &pubkey)
=======
bool CKeyStore::AddKey(const CKey& key)
{
    return AddKeyPubKey(key, key.GetPubKey());
}

bool CBasicKeyStore::AddKeyPubKey(const CKey& key, const CPubKey& pubkey)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    LOCK(cs_KeyStore);
    mapKeys[pubkey.GetID()] = key;
    return true;
}

bool CBasicKeyStore::AddCScript(const CScript& redeemScript)
{
    if (redeemScript.size() > MAX_SCRIPT_ELEMENT_SIZE)
<<<<<<< HEAD
        return error("CBasicKeyStore::AddCScript(): redeemScripts > %i bytes are invalid", MAX_SCRIPT_ELEMENT_SIZE);
=======
        return error("CBasicKeyStore::AddCScript() : redeemScripts > %i bytes are invalid", MAX_SCRIPT_ELEMENT_SIZE);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    LOCK(cs_KeyStore);
    mapScripts[CScriptID(redeemScript)] = redeemScript;
    return true;
}

bool CBasicKeyStore::HaveCScript(const CScriptID& hash) const
{
    LOCK(cs_KeyStore);
    return mapScripts.count(hash) > 0;
}

<<<<<<< HEAD
bool CBasicKeyStore::GetCScript(const CScriptID &hash, CScript& redeemScriptOut) const
{
    LOCK(cs_KeyStore);
    ScriptMap::const_iterator mi = mapScripts.find(hash);
    if (mi != mapScripts.end())
    {
=======
bool CBasicKeyStore::GetCScript(const CScriptID& hash, CScript& redeemScriptOut) const
{
    LOCK(cs_KeyStore);
    ScriptMap::const_iterator mi = mapScripts.find(hash);
    if (mi != mapScripts.end()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        redeemScriptOut = (*mi).second;
        return true;
    }
    return false;
}

<<<<<<< HEAD
static bool ExtractPubKey(const CScript &dest, CPubKey& pubKeyOut)
{
    //TODO: Use Solver to extract this?
    CScript::const_iterator pc = dest.begin();
    opcodetype opcode;
    std::vector<unsigned char> vch;
    if (!dest.GetOp(pc, opcode, vch) || vch.size() < 33 || vch.size() > 65)
        return false;
    pubKeyOut = CPubKey(vch);
    if (!pubKeyOut.IsFullyValid())
        return false;
    if (!dest.GetOp(pc, opcode, vch) || opcode != OP_CHECKSIG || dest.GetOp(pc, opcode, vch))
        return false;
    return true;
}

bool CBasicKeyStore::AddWatchOnly(const CScript &dest)
{
    LOCK(cs_KeyStore);
    setWatchOnly.insert(dest);
    CPubKey pubKey;
    if (ExtractPubKey(dest, pubKey))
        mapWatchKeys[pubKey.GetID()] = pubKey;
    return true;
}

bool CBasicKeyStore::RemoveWatchOnly(const CScript &dest)
{
    LOCK(cs_KeyStore);
    setWatchOnly.erase(dest);
    CPubKey pubKey;
    if (ExtractPubKey(dest, pubKey))
        mapWatchKeys.erase(pubKey.GetID());
    return true;
}

bool CBasicKeyStore::HaveWatchOnly(const CScript &dest) const
=======
bool CBasicKeyStore::AddWatchOnly(const CScript& dest)
{
    LOCK(cs_KeyStore);
    setWatchOnly.insert(dest);
    return true;
}

bool CBasicKeyStore::RemoveWatchOnly(const CScript& dest)
{
    LOCK(cs_KeyStore);
    setWatchOnly.erase(dest);
    return true;
}

bool CBasicKeyStore::HaveWatchOnly(const CScript& dest) const
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    LOCK(cs_KeyStore);
    return setWatchOnly.count(dest) > 0;
}

bool CBasicKeyStore::HaveWatchOnly() const
{
    LOCK(cs_KeyStore);
    return (!setWatchOnly.empty());
}
<<<<<<< HEAD

bool CBasicKeyStore::GetHDChain(CHDChain& hdChainRet) const
{
    hdChainRet = hdChain;
    return !hdChain.IsNull();
}
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
