<<<<<<< HEAD
// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
=======
// Copyright (c) 2009-2010 Satoshi Nakamoto                     -*- c++ -*-
// Copyright (c) 2009-2014 The Bitcoin developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_KEYSTORE_H
#define BITCOIN_KEYSTORE_H

<<<<<<< HEAD
#include "hdchain.h"
#include "key.h"
#include "pubkey.h"
#include "script/script.h"
#include "script/standard.h"
=======
#include "key.h"
#include "pubkey.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include "sync.h"

#include <boost/signals2/signal.hpp>
#include <boost/variant.hpp>

<<<<<<< HEAD
=======
class CScript;
class CScriptID;

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
/** A virtual base class for key stores */
class CKeyStore
{
protected:
    mutable CCriticalSection cs_KeyStore;

public:
    virtual ~CKeyStore() {}

    //! Add a key to the store.
<<<<<<< HEAD
    virtual bool AddKeyPubKey(const CKey &key, const CPubKey &pubkey) =0;
    virtual bool AddKey(const CKey &key);

    //! Check whether a key corresponding to a given address is present in the store.
    virtual bool HaveKey(const CKeyID &address) const =0;
    virtual bool GetKey(const CKeyID &address, CKey& keyOut) const =0;
    virtual void GetKeys(std::set<CKeyID> &setAddress) const =0;
    virtual bool GetPubKey(const CKeyID &address, CPubKey& vchPubKeyOut) const =0;

    //! Support for BIP 0013 : see https://github.com/bitcoin/bips/blob/master/bip-0013.mediawiki
    virtual bool AddCScript(const CScript& redeemScript) =0;
    virtual bool HaveCScript(const CScriptID &hash) const =0;
    virtual bool GetCScript(const CScriptID &hash, CScript& redeemScriptOut) const =0;

    //! Support for Watch-only addresses
    virtual bool AddWatchOnly(const CScript &dest) =0;
    virtual bool RemoveWatchOnly(const CScript &dest) =0;
    virtual bool HaveWatchOnly(const CScript &dest) const =0;
    virtual bool HaveWatchOnly() const =0;
};

typedef std::map<CKeyID, CKey> KeyMap;
typedef std::map<CKeyID, CPubKey> WatchKeyMap;
typedef std::map<CScriptID, CScript > ScriptMap;
=======
    virtual bool AddKeyPubKey(const CKey& key, const CPubKey& pubkey) = 0;
    virtual bool AddKey(const CKey& key);

    //! Check whether a key corresponding to a given address is present in the store.
    virtual bool HaveKey(const CKeyID& address) const = 0;
    virtual bool GetKey(const CKeyID& address, CKey& keyOut) const = 0;
    virtual void GetKeys(std::set<CKeyID>& setAddress) const = 0;
    virtual bool GetPubKey(const CKeyID& address, CPubKey& vchPubKeyOut) const;

    //! Support for BIP 0013 : see https://github.com/bitcoin/bips/blob/master/bip-0013.mediawiki
    virtual bool AddCScript(const CScript& redeemScript) = 0;
    virtual bool HaveCScript(const CScriptID& hash) const = 0;
    virtual bool GetCScript(const CScriptID& hash, CScript& redeemScriptOut) const = 0;

    //! Support for Watch-only addresses
    virtual bool AddWatchOnly(const CScript& dest) = 0;
    virtual bool RemoveWatchOnly(const CScript& dest) = 0;
    virtual bool HaveWatchOnly(const CScript& dest) const = 0;
    virtual bool HaveWatchOnly() const = 0;
};

typedef std::map<CKeyID, CKey> KeyMap;
typedef std::map<CScriptID, CScript> ScriptMap;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
typedef std::set<CScript> WatchOnlySet;

/** Basic key store, that keeps keys in an address->secret map */
class CBasicKeyStore : public CKeyStore
{
protected:
    KeyMap mapKeys;
<<<<<<< HEAD
    WatchKeyMap mapWatchKeys;
    ScriptMap mapScripts;
    WatchOnlySet setWatchOnly;
    /* the HD chain data model*/
    CHDChain hdChain;

public:
    bool AddKeyPubKey(const CKey& key, const CPubKey &pubkey);
    bool GetPubKey(const CKeyID &address, CPubKey& vchPubKeyOut) const;
    bool HaveKey(const CKeyID &address) const
=======
    ScriptMap mapScripts;
    WatchOnlySet setWatchOnly;

public:
    bool AddKeyPubKey(const CKey& key, const CPubKey& pubkey);
    bool HaveKey(const CKeyID& address) const
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    {
        bool result;
        {
            LOCK(cs_KeyStore);
            result = (mapKeys.count(address) > 0);
        }
        return result;
    }
<<<<<<< HEAD
    void GetKeys(std::set<CKeyID> &setAddress) const
=======
    void GetKeys(std::set<CKeyID>& setAddress) const
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    {
        setAddress.clear();
        {
            LOCK(cs_KeyStore);
            KeyMap::const_iterator mi = mapKeys.begin();
<<<<<<< HEAD
            while (mi != mapKeys.end())
            {
=======
            while (mi != mapKeys.end()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                setAddress.insert((*mi).first);
                mi++;
            }
        }
    }
<<<<<<< HEAD
    bool GetKey(const CKeyID &address, CKey &keyOut) const
=======
    bool GetKey(const CKeyID& address, CKey& keyOut) const
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    {
        {
            LOCK(cs_KeyStore);
            KeyMap::const_iterator mi = mapKeys.find(address);
<<<<<<< HEAD
            if (mi != mapKeys.end())
            {
=======
            if (mi != mapKeys.end()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                keyOut = mi->second;
                return true;
            }
        }
        return false;
    }
    virtual bool AddCScript(const CScript& redeemScript);
<<<<<<< HEAD
    virtual bool HaveCScript(const CScriptID &hash) const;
    virtual bool GetCScript(const CScriptID &hash, CScript& redeemScriptOut) const;

    virtual bool AddWatchOnly(const CScript &dest);
    virtual bool RemoveWatchOnly(const CScript &dest);
    virtual bool HaveWatchOnly(const CScript &dest) const;
    virtual bool HaveWatchOnly() const;

    bool GetHDChain(CHDChain& hdChainRet) const;
=======
    virtual bool HaveCScript(const CScriptID& hash) const;
    virtual bool GetCScript(const CScriptID& hash, CScript& redeemScriptOut) const;

    virtual bool AddWatchOnly(const CScript& dest);
    virtual bool RemoveWatchOnly(const CScript& dest);
    virtual bool HaveWatchOnly(const CScript& dest) const;
    virtual bool HaveWatchOnly() const;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};

typedef std::vector<unsigned char, secure_allocator<unsigned char> > CKeyingMaterial;
typedef std::map<CKeyID, std::pair<CPubKey, std::vector<unsigned char> > > CryptedKeyMap;

#endif // BITCOIN_KEYSTORE_H
