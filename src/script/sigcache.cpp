// Copyright (c) 2009-2010 Satoshi Nakamoto
<<<<<<< HEAD
// Copyright (c) 2009-2015 The Bitcoin Core developers
=======
// Copyright (c) 2009-2014 The Bitcoin developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "sigcache.h"

<<<<<<< HEAD
#include "memusage.h"
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include "pubkey.h"
#include "random.h"
#include "uint256.h"
#include "util.h"

#include <boost/thread.hpp>
<<<<<<< HEAD
#include <boost/unordered_set.hpp>
=======
#include <boost/tuple/tuple_comparison.hpp>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

namespace {

/**
<<<<<<< HEAD
 * We're hashing a nonce into the entries themselves, so we don't need extra
 * blinding in the set hash computation.
 */
class CSignatureCacheHasher
{
public:
    size_t operator()(const uint256& key) const {
        return key.GetCheapHash();
    }
};

/**
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
 * Valid signature cache, to avoid doing expensive ECDSA signature checking
 * twice for every transaction (once when accepted into memory pool, and
 * again when accepted into the block chain)
 */
class CSignatureCache
{
private:
<<<<<<< HEAD
     //! Entries are SHA256(nonce || signature hash || public key || signature):
    uint256 nonce;
    typedef boost::unordered_set<uint256, CSignatureCacheHasher> map_type;
    map_type setValid;
    boost::shared_mutex cs_sigcache;


public:
    CSignatureCache()
    {
        GetRandBytes(nonce.begin(), 32);
    }

    void
    ComputeEntry(uint256& entry, const uint256 &hash, const std::vector<unsigned char>& vchSig, const CPubKey& pubkey)
    {
        CSHA256().Write(nonce.begin(), 32).Write(hash.begin(), 32).Write(&pubkey[0], pubkey.size()).Write(&vchSig[0], vchSig.size()).Finalize(entry.begin());
    }

    bool
    Get(const uint256& entry)
    {
        boost::shared_lock<boost::shared_mutex> lock(cs_sigcache);
        return setValid.count(entry);
    }

    void Erase(const uint256& entry)
    {
        boost::unique_lock<boost::shared_mutex> lock(cs_sigcache);
        setValid.erase(entry);
    }

    void Set(const uint256& entry)
    {
        size_t nMaxCacheSize = GetArg("-maxsigcachesize", DEFAULT_MAX_SIG_CACHE_SIZE) * ((size_t) 1 << 20);
        if (nMaxCacheSize <= 0) return;

        boost::unique_lock<boost::shared_mutex> lock(cs_sigcache);
        while (memusage::DynamicUsage(setValid) > nMaxCacheSize)
        {
            map_type::size_type s = GetRand(setValid.bucket_count());
            map_type::local_iterator it = setValid.begin(s);
            if (it != setValid.end(s)) {
                setValid.erase(*it);
            }
        }

        setValid.insert(entry);
=======
     //! sigdata_type is (signature hash, signature, public key):
    typedef boost::tuple<uint256, std::vector<unsigned char>, CPubKey> sigdata_type;
    std::set< sigdata_type> setValid;
    boost::shared_mutex cs_sigcache;

public:
    bool
    Get(const uint256 &hash, const std::vector<unsigned char>& vchSig, const CPubKey& pubKey)
    {
        boost::shared_lock<boost::shared_mutex> lock(cs_sigcache);

        sigdata_type k(hash, vchSig, pubKey);
        std::set<sigdata_type>::iterator mi = setValid.find(k);
        if (mi != setValid.end())
            return true;
        return false;
    }

    void Set(const uint256 &hash, const std::vector<unsigned char>& vchSig, const CPubKey& pubKey)
    {
        // DoS prevention: limit cache size to less than 10MB
        // (~200 bytes per cache entry times 50,000 entries)
        // Since there are a maximum of 20,000 signature operations per block
        // 50,000 is a reasonable default.
        int64_t nMaxCacheSize = GetArg("-maxsigcachesize", 50000);
        if (nMaxCacheSize <= 0) return;

        boost::unique_lock<boost::shared_mutex> lock(cs_sigcache);

        while (static_cast<int64_t>(setValid.size()) > nMaxCacheSize)
        {
            // Evict a random entry. Random because that helps
            // foil would-be DoS attackers who might try to pre-generate
            // and re-use a set of valid signatures just-slightly-greater
            // than our cache size.
            uint256 randomHash = GetRandHash();
            std::vector<unsigned char> unused;
            std::set<sigdata_type>::iterator it =
                setValid.lower_bound(sigdata_type(randomHash, unused, unused));
            if (it == setValid.end())
                it = setValid.begin();
            setValid.erase(*it);
        }

        sigdata_type k(hash, vchSig, pubKey);
        setValid.insert(k);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }
};

}

bool CachingTransactionSignatureChecker::VerifySignature(const std::vector<unsigned char>& vchSig, const CPubKey& pubkey, const uint256& sighash) const
{
    static CSignatureCache signatureCache;

<<<<<<< HEAD
    uint256 entry;
    signatureCache.ComputeEntry(entry, sighash, vchSig, pubkey);

    if (signatureCache.Get(entry)) {
        if (!store) {
            signatureCache.Erase(entry);
        }
        return true;
    }
=======
    if (signatureCache.Get(sighash, vchSig, pubkey))
        return true;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    if (!TransactionSignatureChecker::VerifySignature(vchSig, pubkey, sighash))
        return false;

<<<<<<< HEAD
    if (store) {
        signatureCache.Set(entry);
    }
=======
    if (store)
        signatureCache.Set(sighash, vchSig, pubkey);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    return true;
}
