<<<<<<< HEAD
// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2013 The Bitcoin Core developers
=======
// Copyright (c) 2009-2010 Satoshi Nakamoto             -*- c++ -*-
// Copyright (c) 2009-2013 The Bitcoin developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_UNDO_H
#define BITCOIN_UNDO_H

<<<<<<< HEAD
#include "compressor.h" 
#include "consensus/consensus.h"
=======
#include "compressor.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include "primitives/transaction.h"
#include "serialize.h"

/** Undo information for a CTxIn
 *
<<<<<<< HEAD
 *  Contains the prevout's CTxOut being spent, and its metadata as well
 *  (coinbase or not, height). The serialization contains a dummy value of
 *  zero. This is be compatible with older versions which expect to see
 *  the transaction version there.
 */
class TxInUndoSerializer
{
    const Coin* txout;

public:
    template<typename Stream>
    void Serialize(Stream &s, int nType, int nVersion) const {
        ::Serialize(s, VARINT(txout->nHeight * 2 + (txout->fCoinBase ? 1 : 0)), nType, nVersion);
        if (txout->nHeight > 0) {
            // Required to maintain compatibility with older undo format.
            ::Serialize(s, (unsigned char)0, nType, nVersion);
        }
        ::Serialize(s, CTxOutCompressor(REF(txout->out)), nType, nVersion);
    }

    TxInUndoSerializer(const Coin* coin) : txout(coin) {}
};

class TxInUndoDeserializer
{
    Coin* txout;

public:
    template<typename Stream>
    void Unserialize(Stream &s, int nType, int nVersion) {
        unsigned int nCode = 0;
        ::Unserialize(s, VARINT(nCode), nType, nVersion);
        txout->nHeight = nCode / 2;
        txout->fCoinBase = nCode & 1;
        if (txout->nHeight > 0) {
            // Old versions stored the version number for the last spend of
            // a transaction's outputs. Non-final spends were indicated with
            // height = 0.
            int nVersionDummy;
            ::Unserialize(s, VARINT(nVersionDummy), nType, nVersion);
        }
        ::Unserialize(s, REF(CTxOutCompressor(REF(txout->out))), nType, nVersion);
    }

    TxInUndoDeserializer(Coin* coin) : txout(coin) {}
};

static const size_t MAX_INPUTS_PER_BLOCK = MaxBlockSize(true) / ::GetSerializeSize(CTxIn(), SER_NETWORK, PROTOCOL_VERSION);

=======
 *  Contains the prevout's CTxOut being spent, and if this was the
 *  last output of the affected transaction, its metadata as well
 *  (coinbase or not, height, transaction version)
 */
class CTxInUndo
{
public:
    CTxOut txout;   // the txout data before being spent
    bool fCoinBase; // if the outpoint was the last unspent: whether it belonged to a coinbase
    bool fCoinStake;
    unsigned int nHeight; // if the outpoint was the last unspent: its height
    int nVersion;         // if the outpoint was the last unspent: its version

    CTxInUndo() : txout(), fCoinBase(false), fCoinStake(false), nHeight(0), nVersion(0) {}
    CTxInUndo(const CTxOut& txoutIn, bool fCoinBaseIn = false, bool fCoinStakeIn = false, unsigned int nHeightIn = 0, int nVersionIn = 0) : txout(txoutIn), fCoinBase(fCoinBaseIn), fCoinStake(fCoinStakeIn), nHeight(nHeightIn), nVersion(nVersionIn) {}

    unsigned int GetSerializeSize(int nType, int nVersion) const
    {
        return ::GetSerializeSize(VARINT(nHeight * 4 + (fCoinBase ? 2 : 0) + (fCoinStake ? 1 : 0)), nType, nVersion) +
               (nHeight > 0 ? ::GetSerializeSize(VARINT(this->nVersion), nType, nVersion) : 0) +
               ::GetSerializeSize(CTxOutCompressor(REF(txout)), nType, nVersion);
    }

    template <typename Stream>
    void Serialize(Stream& s, int nType, int nVersion) const
    {
        ::Serialize(s, VARINT(nHeight * 4 + (fCoinBase ? 2 : 0) + (fCoinStake ? 1 : 0)), nType, nVersion);
        if (nHeight > 0)
            ::Serialize(s, VARINT(this->nVersion), nType, nVersion);
        ::Serialize(s, CTxOutCompressor(REF(txout)), nType, nVersion);
    }

    template <typename Stream>
    void Unserialize(Stream& s, int nType, int nVersion)
    {
        unsigned int nCode = 0;
        ::Unserialize(s, VARINT(nCode), nType, nVersion);
        nHeight = nCode >> 2;
        fCoinBase = nCode & 2;
        fCoinStake = nCode & 1;
        if (nHeight > 0)
            ::Unserialize(s, VARINT(this->nVersion), nType, nVersion);
        ::Unserialize(s, REF(CTxOutCompressor(REF(txout))), nType, nVersion);
    }
};

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
/** Undo information for a CTransaction */
class CTxUndo
{
public:
    // undo information for all txins
<<<<<<< HEAD
    std::vector<Coin> vprevout;

    template <typename Stream>
    void Serialize(Stream& s, int nType, int nVersion) const {
        // TODO: avoid reimplementing vector serializer
        uint64_t count = vprevout.size();
        ::Serialize(s, COMPACTSIZE(REF(count)), nType, nVersion);
        for (const auto& prevout : vprevout) {
            ::Serialize(s, REF(TxInUndoSerializer(&prevout)), nType, nVersion);
        }
    }

    template <typename Stream>
    void Unserialize(Stream& s, int nType, int nVersion) {
        // TODO: avoid reimplementing vector deserializer
        uint64_t count = 0;
        ::Unserialize(s, COMPACTSIZE(count), nType, nVersion);
        if (count > MAX_INPUTS_PER_BLOCK) {
            throw std::ios_base::failure("Too many input undo records");
        }
        vprevout.resize(count);
        for (auto& prevout : vprevout) {
            ::Unserialize(s, REF(TxInUndoDeserializer(&prevout)), nType, nVersion);
        }
    }
};

/** Undo information for a CBlock */
class CBlockUndo
{
public:
    std::vector<CTxUndo> vtxundo; // for all but the coinbase
=======
    std::vector<CTxInUndo> vprevout;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
<<<<<<< HEAD
    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion) {
        READWRITE(vtxundo);
=======
    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion)
    {
        READWRITE(vprevout);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }
};

#endif // BITCOIN_UNDO_H
