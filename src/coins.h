<<<<<<< HEAD
// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
=======
// Copyright (c) 2009-2010 Satoshi Nakamoto                     -*- c++ -*-
// Copyright (c) 2009-2014 The Bitcoin developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_COINS_H
#define BITCOIN_COINS_H

#include "compressor.h"
<<<<<<< HEAD
#include "core_memusage.h"
#include "hash.h"
#include "memusage.h"
#include "serialize.h"
#include "uint256.h"
=======
#include "script/standard.h"
#include "serialize.h"
#include "uint256.h"
#include "undo.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

#include <assert.h>
#include <stdint.h>

#include <boost/foreach.hpp>
<<<<<<< HEAD
#include <unordered_map>

/**
 * A UTXO entry.
 *
 * Serialized format:
 * - VARINT((coinbase ? 1 : 0) | (height << 1))
 * - the non-spent CTxOut (via CTxOutCompressor)
 */
class Coin
{
public:
    //! unspent transaction output
    CTxOut out;

    //! whether containing transaction was a coinbase
    unsigned int fCoinBase : 1;

    //! at which height this containing transaction was included in the active block chain
    uint32_t nHeight : 31;

    //! construct a Coin from a CTxOut and height/coinbase information.
    Coin(CTxOut&& outIn, int nHeightIn, bool fCoinBaseIn) : out(std::move(outIn)), fCoinBase(fCoinBaseIn), nHeight(nHeightIn) {}
    Coin(const CTxOut& outIn, int nHeightIn, bool fCoinBaseIn) : out(outIn), fCoinBase(fCoinBaseIn),nHeight(nHeightIn) {}

    void Clear() {
        out.SetNull();
        fCoinBase = false;
        nHeight = 0;
    }

    //! empty constructor
    Coin() : fCoinBase(false), nHeight(0) { }

    bool IsCoinBase() const {
        return fCoinBase;
    }

    template<typename Stream>
    void Serialize(Stream &s, int nType, int nVersion) const {
        assert(!IsSpent());
        uint32_t code = nHeight * 2 + fCoinBase;
        ::Serialize(s, VARINT(code), nType, nVersion);
        ::Serialize(s, CTxOutCompressor(REF(out)), nType, nVersion);
    }

    template<typename Stream>
    void Unserialize(Stream &s, int nType, int nVersion) {
        uint32_t code = 0;
        ::Unserialize(s, VARINT(code), nType, nVersion);
        nHeight = code >> 1;
        fCoinBase = code & 1;
        ::Unserialize(s, REF(CTxOutCompressor(out)), nType, nVersion);
    }

    bool IsSpent() const {
        return out.IsNull();
    }

    size_t DynamicMemoryUsage() const {
        return memusage::DynamicUsage(out.scriptPubKey);
    }
};

class SaltedOutpointHasher
{
private:
    /** Salt */
    const uint64_t k0, k1;

public:
    SaltedOutpointHasher();
=======
#include <boost/unordered_map.hpp>

/** 

    ****Note - for LUX we added fCoinStake to the 2nd bit. Keep in mind when reading the following and adjust as needed.
 * Pruned version of CTransaction: only retains metadata and unspent transaction outputs
 *
 * Serialized format:
 * - VARINT(nVersion)
 * - VARINT(nCode)
 * - unspentness bitvector, for vout[2] and further; least significant byte first
 * - the non-spent CTxOuts (via CTxOutCompressor)
 * - VARINT(nHeight)
 *
 * The nCode value consists of:
 * - bit 1: IsCoinBase()
 * - bit 2: vout[0] is not spent
 * - bit 4: vout[1] is not spent
 * - The higher bits encode N, the number of non-zero bytes in the following bitvector.
 *   - In case both bit 2 and bit 4 are unset, they encode N-1, as there must be at
 *     least one non-spent output).
 *
 * Example: 0104835800816115944e077fe7c803cfa57f29b36bf87c1d358bb85e
 *          <><><--------------------------------------------><---->
 *          |  \                  |                             /
 *    version   code             vout[1]                  height
 *
 *    - version = 1
 *    - code = 4 (vout[1] is not spent, and 0 non-zero bytes of bitvector follow)
 *    - unspentness bitvector: as 0 non-zero bytes follow, it has length 0
 *    - vout[1]: 835800816115944e077fe7c803cfa57f29b36bf87c1d35
 *               * 8358: compact amount representation for 60000000000 (600 BTC)
 *               * 00: special txout type pay-to-pubkey-hash
 *               * 816115944e077fe7c803cfa57f29b36bf87c1d35: address uint160
 *    - height = 203998
 *
 *
 * Example: 0109044086ef97d5790061b01caab50f1b8e9c50a5057eb43c2d9563a4eebbd123008c988f1a4a4de2161e0f50aac7f17e7f9555caa486af3b
 *          <><><--><--------------------------------------------------><----------------------------------------------><---->
 *         /  \   \                     |                                                           |                     /
 *  version  code  unspentness       vout[4]                                                     vout[16]           height
 *
 *  - version = 1
 *  - code = 9 (coinbase, neither vout[0] or vout[1] are unspent, 2 (1, +1 because both bit 2 and bit 4 are unset) non-zero bitvector bytes follow)
 *  - unspentness bitvector: bits 2 (0x04) and 14 (0x4000) are set, so vout[2+2] and vout[14+2] are unspent
 *  - vout[4]: 86ef97d5790061b01caab50f1b8e9c50a5057eb43c2d9563a4ee
 *             * 86ef97d579: compact amount representation for 234925952 (2.35 BTC)
 *             * 00: special txout type pay-to-pubkey-hash
 *             * 61b01caab50f1b8e9c50a5057eb43c2d9563a4ee: address uint160
 *  - vout[16]: bbd123008c988f1a4a4de2161e0f50aac7f17e7f9555caa4
 *              * bbd123: compact amount representation for 110397 (0.001 BTC)
 *              * 00: special txout type pay-to-pubkey-hash
 *              * 8c988f1a4a4de2161e0f50aac7f17e7f9555caa4: address uint160
 *  - height = 120891
 */
class CCoins
{
public:
    //! whether transaction is a coinbase
    bool fCoinBase;
    bool fCoinStake;

    //! unspent transaction outputs; spent outputs are .IsNull(); spent outputs at the end of the array are dropped
    std::vector<CTxOut> vout;

    //! at which height this transaction was included in the active block chain
    int nHeight;

    //! version of the CTransaction; accesses to this value should probably check for nHeight as well,
    //! as new tx version will probably only be introduced at certain heights
    int nVersion;

    void FromTx(const CTransaction& tx, int nHeightIn)
    {
        fCoinBase = tx.IsCoinBase();
        fCoinStake = tx.IsCoinStake();
        vout = tx.vout;
        nHeight = nHeightIn;
        nVersion = tx.nVersion;
        ClearUnspendable();
    }

    //! construct a CCoins from a CTransaction, at a given height
    CCoins(const CTransaction& tx, int nHeightIn)
    {
        FromTx(tx, nHeightIn);
    }

    void Clear()
    {
        fCoinBase = false;
        fCoinStake = false;
        std::vector<CTxOut>().swap(vout);
        nHeight = 0;
        nVersion = 0;
    }

    //! empty constructor
    CCoins() : fCoinBase(false), fCoinStake(false), vout(0), nHeight(0), nVersion(0) {}

    //!remove spent outputs at the end of vout
    void Cleanup()
    {
        while (vout.size() > 0 && vout.back().IsNull())
            vout.pop_back();
        if (vout.empty())
            std::vector<CTxOut>().swap(vout);
    }

    void ClearUnspendable()
    {
        BOOST_FOREACH (CTxOut& txout, vout) {
            if (txout.scriptPubKey.IsUnspendable())
                txout.SetNull();
        }
        Cleanup();
    }

    void swap(CCoins& to)
    {
        std::swap(to.fCoinBase, fCoinBase);
        std::swap(to.fCoinStake, fCoinStake);
        to.vout.swap(vout);
        std::swap(to.nHeight, nHeight);
        std::swap(to.nVersion, nVersion);
    }

    //! equality test
    friend bool operator==(const CCoins& a, const CCoins& b)
    {
        // Empty CCoins objects are always equal.
        if (a.IsPruned() && b.IsPruned())
            return true;
        return a.fCoinBase == b.fCoinBase &&
               a.fCoinStake == b.fCoinStake &&
               a.nHeight == b.nHeight &&
               a.nVersion == b.nVersion &&
               a.vout == b.vout;
    }
    friend bool operator!=(const CCoins& a, const CCoins& b)
    {
        return !(a == b);
    }

    void CalcMaskSize(unsigned int& nBytes, unsigned int& nNonzeroBytes) const;

    bool IsCoinBase() const
    {
        return fCoinBase;
    }

    bool IsCoinStake() const
    {
        return fCoinStake;
    }

    unsigned int GetSerializeSize(int nType, int nVersion) const
    {
        unsigned int nSize = 0;
        unsigned int nMaskSize = 0, nMaskCode = 0;
        CalcMaskSize(nMaskSize, nMaskCode);
        bool fFirst = vout.size() > 0 && !vout[0].IsNull();
        bool fSecond = vout.size() > 1 && !vout[1].IsNull();
        assert(fFirst || fSecond || nMaskCode);
        unsigned int nCode = 8 * (nMaskCode - (fFirst || fSecond ? 0 : 1)) + (fCoinBase ? 1 : 0) + (fCoinStake ? 2 : 0) + (fFirst ? 4 : 0) + (fSecond ? 8 : 0);
        // version
        nSize += ::GetSerializeSize(VARINT(this->nVersion), nType, nVersion);
        // size of header code
        nSize += ::GetSerializeSize(VARINT(nCode), nType, nVersion);
        // spentness bitmask
        nSize += nMaskSize;
        // txouts themself
        for (unsigned int i = 0; i < vout.size(); i++)
            if (!vout[i].IsNull())
                nSize += ::GetSerializeSize(CTxOutCompressor(REF(vout[i])), nType, nVersion);
        // height
        nSize += ::GetSerializeSize(VARINT(nHeight), nType, nVersion);
        return nSize;
    }

    template <typename Stream>
    void Serialize(Stream& s, int nType, int nVersion) const
    {
        unsigned int nMaskSize = 0, nMaskCode = 0;
        CalcMaskSize(nMaskSize, nMaskCode);
        bool fFirst = vout.size() > 0 && !vout[0].IsNull();
        bool fSecond = vout.size() > 1 && !vout[1].IsNull();
        assert(fFirst || fSecond || nMaskCode);
        unsigned int nCode = 16 * (nMaskCode - (fFirst || fSecond ? 0 : 1)) + (fCoinBase ? 1 : 0) + (fCoinStake ? 2 : 0) + (fFirst ? 4 : 0) + (fSecond ? 8 : 0);
        // version
        ::Serialize(s, VARINT(this->nVersion), nType, nVersion);
        // header code
        ::Serialize(s, VARINT(nCode), nType, nVersion);
        // spentness bitmask
        for (unsigned int b = 0; b < nMaskSize; b++) {
            unsigned char chAvail = 0;
            for (unsigned int i = 0; i < 8 && 2 + b * 8 + i < vout.size(); i++)
                if (!vout[2 + b * 8 + i].IsNull())
                    chAvail |= (1 << i);
            ::Serialize(s, chAvail, nType, nVersion);
        }
        // txouts themself
        for (unsigned int i = 0; i < vout.size(); i++) {
            if (!vout[i].IsNull())
                ::Serialize(s, CTxOutCompressor(REF(vout[i])), nType, nVersion);
        }
        // coinbase height
        ::Serialize(s, VARINT(nHeight), nType, nVersion);
    }

    template <typename Stream>
    void Unserialize(Stream& s, int nType, int nVersion)
    {
        unsigned int nCode = 0;
        // version
        ::Unserialize(s, VARINT(this->nVersion), nType, nVersion);
        // header code
        ::Unserialize(s, VARINT(nCode), nType, nVersion);
        fCoinBase = nCode & 1;         //0001 - means coinbase
        fCoinStake = (nCode & 2) != 0; //0010 coinstake
        std::vector<bool> vAvail(2, false);
        vAvail[0] = (nCode & 4) != 0; // 0100
        vAvail[1] = (nCode & 8) != 0; // 1000
        unsigned int nMaskCode = (nCode / 16) + ((nCode & 12) != 0 ? 0 : 1);
        // spentness bitmask
        while (nMaskCode > 0) {
            unsigned char chAvail = 0;
            ::Unserialize(s, chAvail, nType, nVersion);
            for (unsigned int p = 0; p < 8; p++) {
                bool f = (chAvail & (1 << p)) != 0;
                vAvail.push_back(f);
            }
            if (chAvail != 0)
                nMaskCode--;
        }
        // txouts themself
        vout.assign(vAvail.size(), CTxOut());
        for (unsigned int i = 0; i < vAvail.size(); i++) {
            if (vAvail[i])
                ::Unserialize(s, REF(CTxOutCompressor(vout[i])), nType, nVersion);
        }
        // coinbase height
        ::Unserialize(s, VARINT(nHeight), nType, nVersion);
        Cleanup();
    }

    //! mark an outpoint spent, and construct undo information
    bool Spend(const COutPoint& out, CTxInUndo& undo);

    //! mark a vout spent
    bool Spend(int nPos);

    //! check whether a particular output is still available
    bool IsAvailable(unsigned int nPos) const
    {
        return (nPos < vout.size() && !vout[nPos].IsNull());
    }

    //! check whether the entire CCoins is spent
    //! note that only !IsPruned() CCoins can be serialized
    bool IsPruned() const
    {
        BOOST_FOREACH (const CTxOut& out, vout)
            if (!out.IsNull())
                return false;
        return true;
    }
};

class CCoinsKeyHasher
{
private:
    uint256 salt;

public:
    CCoinsKeyHasher();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    /**
     * This *must* return size_t. With Boost 1.46 on 32-bit systems the
     * unordered_map will behave unpredictably if the custom hasher returns a
     * uint64_t, resulting in failures when syncing the chain (#4634).
     */
<<<<<<< HEAD
    size_t operator()(const COutPoint& id) const {
        return SipHashUint256Extra(k0, k1, id.hash, id.n);
    }
};

struct CCoinsCacheEntry
{
    Coin coin; // The actual cached data.
=======
    size_t operator()(const uint256& key) const
    {
        return key.GetHash(salt);
    }
};

struct CCoinsCacheEntry {
    CCoins coins; // The actual cached data.
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    unsigned char flags;

    enum Flags {
        DIRTY = (1 << 0), // This cache entry is potentially different from the version in the parent view.
        FRESH = (1 << 1), // The parent view does not have this entry (or it is pruned).
<<<<<<< HEAD
        /* Note that FRESH is a performance optimization with which we can
         * erase coins that are fully spent if we know we do not need to
         * flush the changes to the parent cache.  It is always safe to
         * not mark FRESH if that condition is not guaranteed.
         */
    };

    CCoinsCacheEntry() : flags(0) {}
    explicit CCoinsCacheEntry(Coin&& coin_) : coin(std::move(coin_)), flags(0) {}
};

typedef std::unordered_map<COutPoint, CCoinsCacheEntry, SaltedOutpointHasher> CCoinsMap;

/** Cursor for iterating over CoinsView state */
class CCoinsViewCursor
{
public:
    CCoinsViewCursor(const uint256 &hashBlockIn): hashBlock(hashBlockIn) {}
    virtual ~CCoinsViewCursor() {}

    virtual bool GetKey(COutPoint &key) const = 0;
    virtual bool GetValue(Coin &coin) const = 0;
    /* Don't care about GetKeySize here */
    virtual unsigned int GetValueSize() const = 0;

    virtual bool Valid() const = 0;
    virtual void Next() = 0;

    //! Get best block at the time this cursor was created
    const uint256 &GetBestBlock() const { return hashBlock; }
private:
    uint256 hashBlock;
};

=======
    };

    CCoinsCacheEntry() : coins(), flags(0) {}
};

typedef boost::unordered_map<uint256, CCoinsCacheEntry, CCoinsKeyHasher> CCoinsMap;

struct CCoinsStats {
    int nHeight;
    uint256 hashBlock;
    uint64_t nTransactions;
    uint64_t nTransactionOutputs;
    uint64_t nSerializedSize;
    uint256 hashSerialized;
    CAmount nTotalAmount;

    CCoinsStats() : nHeight(0), hashBlock(0), nTransactions(0), nTransactionOutputs(0), nSerializedSize(0), hashSerialized(0), nTotalAmount(0) {}
};


>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
/** Abstract view on the open txout dataset. */
class CCoinsView
{
public:
<<<<<<< HEAD
    /** Retrieve the Coin (unspent transaction output) for a given outpoint.
     *  Returns true only when an unspent coin was found, which is returned in coin.
     *  When false is returned, coin's value is unspecified.
     */
    virtual bool GetCoin(const COutPoint &outpoint, Coin &coin) const;

    //! Just check whether a given outpoint is unspent.
    virtual bool HaveCoin(const COutPoint &outpoint) const;
=======
    //! Retrieve the CCoins (unspent transaction outputs) for a given txid
    virtual bool GetCoins(const uint256& txid, CCoins& coins) const;

    //! Just check whether we have data for a given txid.
    //! This may (but cannot always) return true for fully spent transactions
    virtual bool HaveCoins(const uint256& txid) const;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    //! Retrieve the block hash whose state this CCoinsView currently represents
    virtual uint256 GetBestBlock() const;

<<<<<<< HEAD
    //! Do a bulk modification (multiple Coin changes + BestBlock change).
    //! The passed mapCoins can be modified.
    virtual bool BatchWrite(CCoinsMap &mapCoins, const uint256 &hashBlock);

    //! Get a cursor to iterate over the whole state
    virtual CCoinsViewCursor *Cursor() const;

    //! As we use CCoinsViews polymorphically, have a virtual destructor
    virtual ~CCoinsView() {}

    //! Estimate database size (0 if not implemented)
    virtual size_t EstimateSize() const { return 0; }
=======
    //! Do a bulk modification (multiple CCoins changes + BestBlock change).
    //! The passed mapCoins can be modified.
    virtual bool BatchWrite(CCoinsMap& mapCoins, const uint256& hashBlock);

    //! Calculate statistics about the unspent transaction output set
    virtual bool GetStats(CCoinsStats& stats) const;

    //! As we use CCoinsViews polymorphically, have a virtual destructor
    virtual ~CCoinsView() {}
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};


/** CCoinsView backed by another CCoinsView */
class CCoinsViewBacked : public CCoinsView
{
protected:
<<<<<<< HEAD
    CCoinsView *base;

public:
    CCoinsViewBacked(CCoinsView *viewIn);
    bool GetCoin(const COutPoint &outpoint, Coin &coin) const override;
    bool HaveCoin(const COutPoint &outpoint) const override;
    uint256 GetBestBlock() const override;
    void SetBackend(CCoinsView &viewIn);
    bool BatchWrite(CCoinsMap &mapCoins, const uint256 &hashBlock) override;
    CCoinsViewCursor *Cursor() const override;
    size_t EstimateSize() const override;
};

=======
    CCoinsView* base;

public:
    CCoinsViewBacked(CCoinsView* viewIn);
    bool GetCoins(const uint256& txid, CCoins& coins) const;
    bool HaveCoins(const uint256& txid) const;
    uint256 GetBestBlock() const;
    void SetBackend(CCoinsView& viewIn);
    bool BatchWrite(CCoinsMap& mapCoins, const uint256& hashBlock);
    bool GetStats(CCoinsStats& stats) const;
};

class CCoinsViewCache;

/** Flags for nSequence and nLockTime locks */
enum {
    /* Interpret sequence numbers as relative lock-time constraints. */
    LOCKTIME_VERIFY_SEQUENCE = (1 << 0),

    /* Use GetMedianTimePast() instead of nTime for end point timestamp. */
    LOCKTIME_MEDIAN_TIME_PAST = (1 << 1),
};

/** Used as the flags parameter to sequence and nLocktime checks in non-consensus code. */
static const unsigned int STANDARD_LOCKTIME_VERIFY_FLAGS = LOCKTIME_VERIFY_SEQUENCE |
                                                           LOCKTIME_MEDIAN_TIME_PAST;

/** 
 * A reference to a mutable cache entry. Encapsulating it allows us to run
 *  cleanup code after the modification is finished, and keeping track of
 *  concurrent modifications. 
 */
class CCoinsModifier
{
private:
    CCoinsViewCache& cache;
    CCoinsMap::iterator it;
    CCoinsModifier(CCoinsViewCache& cache_, CCoinsMap::iterator it_);

public:
    CCoins* operator->() { return &it->second.coins; }
    CCoins& operator*() { return it->second.coins; }
    ~CCoinsModifier();
    friend class CCoinsViewCache;
};
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

/** CCoinsView that adds a memory cache for transactions to another CCoinsView */
class CCoinsViewCache : public CCoinsViewBacked
{
protected:
<<<<<<< HEAD
=======
    /* Whether this cache has an active modifier. */
    bool hasModifier;

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    /**
     * Make mutable so that we can "fill the cache" even from Get-methods
     * declared as "const".  
     */
    mutable uint256 hashBlock;
    mutable CCoinsMap cacheCoins;

<<<<<<< HEAD
    /* Cached dynamic memory usage for the inner Coin objects. */
    mutable size_t cachedCoinsUsage;

public:
    CCoinsViewCache(CCoinsView *baseIn);

    // Standard CCoinsView methods
    bool GetCoin(const COutPoint &outpoint, Coin &coin) const override;
    bool HaveCoin(const COutPoint &outpoint) const override;
    uint256 GetBestBlock() const override;
    void SetBestBlock(const uint256 &hashBlock);
    bool BatchWrite(CCoinsMap &mapCoins, const uint256 &hashBlock) override;
    CCoinsViewCursor* Cursor() const override {
        throw std::logic_error("CCoinsViewCache cursor iteration not supported.");
    }

    /**
     * Check if we have the given utxo already loaded in this cache.
     * The semantics are the same as HaveCoin(), but no calls to
     * the backing CCoinsView are made.
     */
    bool HaveCoinInCache(const COutPoint &outpoint) const;

    /**
     * Return a reference to Coin in the cache, or a pruned one if not found. This is
     * more efficient than GetCoin.
     *
     * Generally, do not hold the reference returned for more than a short scope.
     * While the current implementation allows for modifications to the contents
     * of the cache while holding the reference, this behavior should not be relied
     * on! To be safe, best to not hold the returned reference through any other
     * calls to this cache.
     */
    const Coin& AccessCoin(const COutPoint &output) const;

    /**
     * Add a coin. Set potential_overwrite to true if a non-pruned version may
     * already exist.
     */
    void AddCoin(const COutPoint& outpoint, Coin&& coin, bool potential_overwrite);

    /**
     * Spend a coin. Pass moveto in order to get the deleted data.
     * If no unspent output exists for the passed outpoint, this call
     * has no effect.
     */
    bool SpendCoin(const COutPoint &outpoint, Coin* moveto = nullptr);
=======
public:
    CCoinsViewCache(CCoinsView* baseIn);
    ~CCoinsViewCache();

    // Standard CCoinsView methods
    bool GetCoins(const uint256& txid, CCoins& coins) const;
    bool HaveCoins(const uint256& txid) const;
    uint256 GetBestBlock() const;
    void SetBestBlock(const uint256& hashBlock);
    bool BatchWrite(CCoinsMap& mapCoins, const uint256& hashBlock);

    /**
     * Return a pointer to CCoins in the cache, or NULL if not found. This is
     * more efficient than GetCoins. Modifications to other cache entries are
     * allowed while accessing the returned pointer.
     */
    const CCoins* AccessCoins(const uint256& txid) const;

    /**
     * Return a modifiable reference to a CCoins. If no entry with the given
     * txid exists, a new one is created. Simultaneous modifications are not
     * allowed.
     */
    CCoinsModifier ModifyCoins(const uint256& txid);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    /**
     * Push the modifications applied to this cache to its base.
     * Failure to call this method before destruction will cause the changes to be forgotten.
     * If false is returned, the state of this cache (and its backing view) will be undefined.
     */
    bool Flush();

<<<<<<< HEAD
    /**
     * Removes the UTXO with the given outpoint from the cache, if it is
     * not modified.
     */
    void Uncache(const COutPoint &outpoint);

    //! Calculate the size of the cache (in number of transaction outputs)
    unsigned int GetCacheSize() const;

    //! Calculate the size of the cache (in bytes)
    size_t DynamicMemoryUsage() const;

    /** 
     * Amount of gelcoin coming in to a transaction
=======
    //! Calculate the size of the cache (in number of transactions)
    unsigned int GetCacheSize() const;

    /** 
     * Amount of lux coming in to a transaction
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
     * Note that lightweight clients may not know anything besides the hash of previous transactions,
     * so may not be able to calculate this.
     *
     * @param[in] tx	transaction for which we are checking input total
     * @return	Sum of value of all inputs (scriptSigs)
     */
    CAmount GetValueIn(const CTransaction& tx) const;

    //! Check whether all prevouts of the transaction are present in the UTXO set represented by this view
    bool HaveInputs(const CTransaction& tx) const;

<<<<<<< HEAD
    /**
     * Return priority of tx at height nHeight. Also calculate the sum of the values of the inputs
     * that are already in the chain.  These are the inputs that will age and increase priority as
     * new blocks are added to the chain.
     */
    double GetPriority(const CTransaction &tx, int nHeight, CAmount &inChainInputValue) const;

private:
    CCoinsMap::iterator FetchCoin(const COutPoint &outpoint) const;

    /**
     * By making the copy constructor private, we prevent accidentally using it when one intends to create a cache on top of a base cache.
     */
    CCoinsViewCache(const CCoinsViewCache &);
};

//! Utility function to add all of a transaction's outputs to a cache.
// It assumes that overwrites are only possible for coinbase transactions,
// TODO: pass in a boolean to limit these possible overwrites to known
// (pre-BIP34) cases.
void AddCoins(CCoinsViewCache& cache, const CTransaction& tx, int nHeight);

//! Utility function to find any unspent output with a given txid.
// This function can be quite expensive because in the event of a transaction
// which is not found in the cache, it can cause up to MAX_OUTPUTS_PER_BLOCK
// lookups to database, so it should be used with care.
const Coin& AccessByTxid(const CCoinsViewCache& cache, const uint256& txid);
=======
    //! Return priority of tx at height nHeight
    double GetPriority(const CTransaction& tx, int nHeight) const;

    const CTxOut& GetOutputFor(const CTxIn& input) const;

    friend class CCoinsModifier;

private:
    CCoinsMap::iterator FetchCoins(const uint256& txid);
    CCoinsMap::const_iterator FetchCoins(const uint256& txid) const;
};
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

#endif // BITCOIN_COINS_H
