<<<<<<< HEAD
// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
=======
// Copyright (c) 2009-2010 Satoshi Nakamoto                     -*- c++ -*-
// Copyright (c) 2009-2014 The Bitcoin developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_COMPRESSOR_H
#define BITCOIN_COMPRESSOR_H

#include "primitives/transaction.h"
#include "script/script.h"
#include "serialize.h"

class CKeyID;
class CPubKey;
class CScriptID;

/** Compact serializer for scripts.
 *
 *  It detects common cases and encodes them much more efficiently.
 *  3 special cases are defined:
 *  * Pay to pubkey hash (encoded as 21 bytes)
 *  * Pay to script hash (encoded as 21 bytes)
 *  * Pay to pubkey starting with 0x02, 0x03 or 0x04 (encoded as 33 bytes)
 *
 *  Other scripts up to 121 bytes require 1 byte + script length. Above
 *  that, scripts up to 16505 bytes require 2 bytes + script length.
 */
class CScriptCompressor
{
private:
    /**
     * make this static for now (there are only 6 special scripts defined)
     * this can potentially be extended together with a new nVersion for
     * transactions, in which case this value becomes dependent on nVersion
     * and nHeight of the enclosing transaction.
     */
    static const unsigned int nSpecialScripts = 6;

<<<<<<< HEAD
    CScript &script;
=======
    CScript& script;

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
protected:
    /**
     * These check for scripts for which a special case with a shorter encoding is defined.
     * They are implemented separately from the CScript test, as these test for exact byte
     * sequence correspondences, and are more strict. For example, IsToPubKey also verifies
     * whether the public key is valid (as invalid ones cannot be represented in compressed
     * form).
     */
<<<<<<< HEAD
    bool IsToKeyID(CKeyID &hash) const;
    bool IsToScriptID(CScriptID &hash) const;
    bool IsToPubKey(CPubKey &pubkey) const;

    bool Compress(std::vector<unsigned char> &out) const;
    unsigned int GetSpecialSize(unsigned int nSize) const;
    bool Decompress(unsigned int nSize, const std::vector<unsigned char> &out);
public:
    CScriptCompressor(CScript &scriptIn) : script(scriptIn) { }

    unsigned int GetSerializeSize(int nType, int nVersion) const {
=======
    bool IsToKeyID(CKeyID& hash) const;
    bool IsToScriptID(CScriptID& hash) const;
    bool IsToPubKey(CPubKey& pubkey) const;

    bool Compress(std::vector<unsigned char>& out) const;
    unsigned int GetSpecialSize(unsigned int nSize) const;
    bool Decompress(unsigned int nSize, const std::vector<unsigned char>& out);

public:
    CScriptCompressor(CScript& scriptIn) : script(scriptIn) {}

    unsigned int GetSerializeSize(int nType, int nVersion) const
    {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        std::vector<unsigned char> compr;
        if (Compress(compr))
            return compr.size();
        unsigned int nSize = script.size() + nSpecialScripts;
        return script.size() + VARINT(nSize).GetSerializeSize(nType, nVersion);
    }

<<<<<<< HEAD
    template<typename Stream>
    void Serialize(Stream &s, int nType, int nVersion) const {
=======
    template <typename Stream>
    void Serialize(Stream& s, int nType, int nVersion) const
    {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        std::vector<unsigned char> compr;
        if (Compress(compr)) {
            s << CFlatData(compr);
            return;
        }
        unsigned int nSize = script.size() + nSpecialScripts;
        s << VARINT(nSize);
        s << CFlatData(script);
    }

<<<<<<< HEAD
    template<typename Stream>
    void Unserialize(Stream &s, int nType, int nVersion) {
=======
    template <typename Stream>
    void Unserialize(Stream& s, int nType, int nVersion)
    {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        unsigned int nSize = 0;
        s >> VARINT(nSize);
        if (nSize < nSpecialScripts) {
            std::vector<unsigned char> vch(GetSpecialSize(nSize), 0x00);
            s >> REF(CFlatData(vch));
            Decompress(nSize, vch);
            return;
        }
        nSize -= nSpecialScripts;
<<<<<<< HEAD
        if (nSize > MAX_SCRIPT_SIZE) {
            // Overly long script, replace with a short invalid one
            script << OP_RETURN;
            s.ignore(nSize);
        } else {
            script.resize(nSize);
            s >> REF(CFlatData(script));
        }
=======
        script.resize(nSize);
        s >> REF(CFlatData(script));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }
};

/** wrapper for CTxOut that provides a more compact serialization */
class CTxOutCompressor
{
private:
<<<<<<< HEAD
    CTxOut &txout;
=======
    CTxOut& txout;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

public:
    static uint64_t CompressAmount(uint64_t nAmount);
    static uint64_t DecompressAmount(uint64_t nAmount);

<<<<<<< HEAD
    CTxOutCompressor(CTxOut &txoutIn) : txout(txoutIn) { }
=======
    CTxOutCompressor(CTxOut& txoutIn) : txout(txoutIn) {}
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
<<<<<<< HEAD
    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion) {
=======
    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion)
    {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        if (!ser_action.ForRead()) {
            uint64_t nVal = CompressAmount(txout.nValue);
            READWRITE(VARINT(nVal));
        } else {
            uint64_t nVal = 0;
            READWRITE(VARINT(nVal));
            txout.nValue = DecompressAmount(nVal);
        }
        CScriptCompressor cscript(REF(txout.scriptPubKey));
        READWRITE(cscript);
    }
};

#endif // BITCOIN_COMPRESSOR_H
