// Copyright (c) 2009-2010 Satoshi Nakamoto
<<<<<<< HEAD
// Copyright (c) 2009-2015 The Bitcoin Core developers
=======
// Copyright (c) 2009-2014 The Bitcoin developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "script/sign.h"

<<<<<<< HEAD
#include "key.h"
#include "keystore.h"
#include "policy/policy.h"
#include "primitives/transaction.h"
#include "script/standard.h"
#include "uint256.h"
=======
#include "primitives/transaction.h"
#include "key.h"
#include "keystore.h"
#include "script/standard.h"
#include "uint256.h"
#include "util.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

#include <boost/foreach.hpp>

using namespace std;

<<<<<<< HEAD
typedef std::vector<unsigned char> valtype;

TransactionSignatureCreator::TransactionSignatureCreator(const CKeyStore* keystoreIn, const CTransaction* txToIn, unsigned int nInIn, int nHashTypeIn) : BaseSignatureCreator(keystoreIn), txTo(txToIn), nIn(nInIn), nHashType(nHashTypeIn), checker(txTo, nIn) {}

bool TransactionSignatureCreator::CreateSig(std::vector<unsigned char>& vchSig, const CKeyID& address, const CScript& scriptCode) const
{
    CKey key;
    if (!keystore->GetKey(address, key))
        return false;

    uint256 hash = SignatureHash(scriptCode, *txTo, nIn, nHashType);
    if (!key.Sign(hash, vchSig))
        return false;
    vchSig.push_back((unsigned char)nHashType);
    return true;
}

static bool Sign1(const CKeyID& address, const BaseSignatureCreator& creator, const CScript& scriptCode, CScript& scriptSigRet)
{
    vector<unsigned char> vchSig;
    if (!creator.CreateSig(vchSig, address, scriptCode))
        return false;
    scriptSigRet << vchSig;
    return true;
}

static bool SignN(const vector<valtype>& multisigdata, const BaseSignatureCreator& creator, const CScript& scriptCode, CScript& scriptSigRet)
=======
typedef vector<unsigned char> valtype;

bool Sign1(const CKeyID& address, const CKeyStore& keystore, uint256 hash, int nHashType, CScript& scriptSigRet)
{
    CKey key;
    if (!keystore.GetKey(address, key))
        return false;

    vector<unsigned char> vchSig;
    if (!key.Sign(hash, vchSig))
        return false;
    vchSig.push_back((unsigned char)nHashType);
    scriptSigRet << vchSig;

    return true;
}

bool SignN(const vector<valtype>& multisigdata, const CKeyStore& keystore, uint256 hash, int nHashType, CScript& scriptSigRet)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    int nSigned = 0;
    int nRequired = multisigdata.front()[0];
    for (unsigned int i = 1; i < multisigdata.size()-1 && nSigned < nRequired; i++)
    {
        const valtype& pubkey = multisigdata[i];
        CKeyID keyID = CPubKey(pubkey).GetID();
<<<<<<< HEAD
        if (Sign1(keyID, creator, scriptCode, scriptSigRet))
=======
        if (Sign1(keyID, keystore, hash, nHashType, scriptSigRet))
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            ++nSigned;
    }
    return nSigned==nRequired;
}

/**
<<<<<<< HEAD
 * Sign scriptPubKey using signature made with creator.
=======
 * Sign scriptPubKey with private keys stored in keystore, given transaction hash and hash type.
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
 * Signatures are returned in scriptSigRet (or returns false if scriptPubKey can't be signed),
 * unless whichTypeRet is TX_SCRIPTHASH, in which case scriptSigRet is the redemption script.
 * Returns false if scriptPubKey could not be completely satisfied.
 */
<<<<<<< HEAD
static bool SignStep(const BaseSignatureCreator& creator, const CScript& scriptPubKey,
                     CScript& scriptSigRet, txnouttype& whichTypeRet)
=======
bool Solver(const CKeyStore& keystore, const CScript& scriptPubKey, uint256 hash, int nHashType,
                  CScript& scriptSigRet, txnouttype& whichTypeRet)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    scriptSigRet.clear();

    vector<valtype> vSolutions;
    if (!Solver(scriptPubKey, whichTypeRet, vSolutions))
<<<<<<< HEAD
        return false;
=======
    {
        LogPrintf("*** solver solver failed \n");
        return false;
    }
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    CKeyID keyID;
    switch (whichTypeRet)
    {
    case TX_NONSTANDARD:
    case TX_NULL_DATA:
<<<<<<< HEAD
        return false;
    case TX_PUBKEY:
        keyID = CPubKey(vSolutions[0]).GetID();
        return Sign1(keyID, creator, scriptPubKey, scriptSigRet);
    case TX_PUBKEYHASH:
        keyID = CKeyID(uint160(vSolutions[0]));
        if (!Sign1(keyID, creator, scriptPubKey, scriptSigRet))
            return false;
        else
        {
            CPubKey vch;
            creator.KeyStore().GetPubKey(keyID, vch);
=======
    {
        LogPrintf("*** null data \n");
        return false;
    }
    case TX_PUBKEY:
        keyID = CPubKey(vSolutions[0]).GetID();
        if(!Sign1(keyID, keystore, hash, nHashType, scriptSigRet))
        {
            LogPrintf("*** Sign1 failed \n");
            return false;
        }
        return true;
    case TX_PUBKEYHASH:
        keyID = CKeyID(uint160(vSolutions[0]));
        if (!Sign1(keyID, keystore, hash, nHashType, scriptSigRet))
        {
            LogPrintf("*** solver failed to sign \n");
            return false;
        }
        else
        {
            CPubKey vch;
            keystore.GetPubKey(keyID, vch);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            scriptSigRet << ToByteVector(vch);
        }
        return true;
    case TX_SCRIPTHASH:
<<<<<<< HEAD
        return creator.KeyStore().GetCScript(uint160(vSolutions[0]), scriptSigRet);

    case TX_MULTISIG:
        scriptSigRet << OP_0; // workaround CHECKMULTISIG bug
        return (SignN(vSolutions, creator, scriptPubKey, scriptSigRet));
    }
    return false;
}

bool ProduceSignature(const BaseSignatureCreator& creator, const CScript& fromPubKey, CScript& scriptSig)
{
    txnouttype whichType;
    if (!SignStep(creator, fromPubKey, scriptSig, whichType))
=======
        return keystore.GetCScript(uint160(vSolutions[0]), scriptSigRet);

    case TX_MULTISIG:
        scriptSigRet << OP_0; // workaround CHECKMULTISIG bug
        return (SignN(vSolutions, keystore, hash, nHashType, scriptSigRet));
    }
    LogPrintf("*** solver no case met \n");
    return false;
}

bool SignSignature(const CKeyStore &keystore, const CScript& fromPubKey, CMutableTransaction& txTo, unsigned int nIn, int nHashType)
{
    assert(nIn < txTo.vin.size());
    CTxIn& txin = txTo.vin[nIn];

    // Leave out the signature from the hash, since a signature can't sign itself.
    // The checksig op will also drop the signatures from its hash.
    uint256 hash = SignatureHash(fromPubKey, txTo, nIn, nHashType);

    txnouttype whichType;
    if (!Solver(keystore, fromPubKey, hash, nHashType, txin.scriptSig, whichType))
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return false;

    if (whichType == TX_SCRIPTHASH)
    {
        // Solver returns the subscript that need to be evaluated;
        // the final scriptSig is the signatures from that
        // and then the serialized subscript:
<<<<<<< HEAD
        CScript subscript = scriptSig;

        txnouttype subType;
        bool fSolved =
            SignStep(creator, subscript, scriptSig, subType) && subType != TX_SCRIPTHASH;
        // Append serialized subscript whether or not it is completely signed:
        scriptSig << valtype(subscript.begin(), subscript.end());
=======
        CScript subscript = txin.scriptSig;

        // Recompute txn hash using subscript in place of scriptPubKey:
        uint256 hash2 = SignatureHash(subscript, txTo, nIn, nHashType);

        txnouttype subType;
        bool fSolved =
            Solver(keystore, subscript, hash2, nHashType, txin.scriptSig, subType) && subType != TX_SCRIPTHASH;
        // Append serialized subscript whether or not it is completely signed:
        txin.scriptSig << static_cast<valtype>(subscript);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        if (!fSolved) return false;
    }

    // Test solution
<<<<<<< HEAD
    return VerifyScript(scriptSig, fromPubKey, STANDARD_SCRIPT_VERIFY_FLAGS, creator.Checker());
}

bool SignSignature(const CKeyStore &keystore, const CScript& fromPubKey, CMutableTransaction& txTo, unsigned int nIn, int nHashType)
{
    assert(nIn < txTo.vin.size());
    CTxIn& txin = txTo.vin[nIn];

    CTransaction txToConst(txTo);
    TransactionSignatureCreator creator(&keystore, &txToConst, nIn, nHashType);

    return ProduceSignature(creator, fromPubKey, txin.scriptSig);
=======
    return VerifyScript(txin.scriptSig, fromPubKey, STANDARD_SCRIPT_VERIFY_FLAGS, MutableTransactionSignatureChecker(&txTo, nIn));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

bool SignSignature(const CKeyStore &keystore, const CTransaction& txFrom, CMutableTransaction& txTo, unsigned int nIn, int nHashType)
{
    assert(nIn < txTo.vin.size());
    CTxIn& txin = txTo.vin[nIn];
    assert(txin.prevout.n < txFrom.vout.size());
    const CTxOut& txout = txFrom.vout[txin.prevout.n];

    return SignSignature(keystore, txout.scriptPubKey, txTo, nIn, nHashType);
}

static CScript PushAll(const vector<valtype>& values)
{
    CScript result;
    BOOST_FOREACH(const valtype& v, values)
        result << v;
    return result;
}

<<<<<<< HEAD
static CScript CombineMultisig(const CScript& scriptPubKey, const BaseSignatureChecker& checker,
=======
static CScript CombineMultisig(const CScript& scriptPubKey, const CTransaction& txTo, unsigned int nIn,
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                               const vector<valtype>& vSolutions,
                               const vector<valtype>& sigs1, const vector<valtype>& sigs2)
{
    // Combine all the signatures we've got:
    set<valtype> allsigs;
    BOOST_FOREACH(const valtype& v, sigs1)
    {
        if (!v.empty())
            allsigs.insert(v);
    }
    BOOST_FOREACH(const valtype& v, sigs2)
    {
        if (!v.empty())
            allsigs.insert(v);
    }

    // Build a map of pubkey -> signature by matching sigs to pubkeys:
    assert(vSolutions.size() > 1);
    unsigned int nSigsRequired = vSolutions.front()[0];
    unsigned int nPubKeys = vSolutions.size()-2;
    map<valtype, valtype> sigs;
    BOOST_FOREACH(const valtype& sig, allsigs)
    {
        for (unsigned int i = 0; i < nPubKeys; i++)
        {
            const valtype& pubkey = vSolutions[i+1];
            if (sigs.count(pubkey))
                continue; // Already got a sig for this pubkey

<<<<<<< HEAD
            if (checker.CheckSig(sig, pubkey, scriptPubKey))
=======
            if (TransactionSignatureChecker(&txTo, nIn).CheckSig(sig, pubkey, scriptPubKey))
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            {
                sigs[pubkey] = sig;
                break;
            }
        }
    }
    // Now build a merged CScript:
    unsigned int nSigsHave = 0;
    CScript result; result << OP_0; // pop-one-too-many workaround
    for (unsigned int i = 0; i < nPubKeys && nSigsHave < nSigsRequired; i++)
    {
        if (sigs.count(vSolutions[i+1]))
        {
            result << sigs[vSolutions[i+1]];
            ++nSigsHave;
        }
    }
    // Fill any missing with OP_0:
    for (unsigned int i = nSigsHave; i < nSigsRequired; i++)
        result << OP_0;

    return result;
}

<<<<<<< HEAD
static CScript CombineSignatures(const CScript& scriptPubKey, const BaseSignatureChecker& checker,
=======
static CScript CombineSignatures(const CScript& scriptPubKey, const CTransaction& txTo, unsigned int nIn,
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                                 const txnouttype txType, const vector<valtype>& vSolutions,
                                 vector<valtype>& sigs1, vector<valtype>& sigs2)
{
    switch (txType)
    {
    case TX_NONSTANDARD:
    case TX_NULL_DATA:
        // Don't know anything about this, assume bigger one is correct:
        if (sigs1.size() >= sigs2.size())
            return PushAll(sigs1);
        return PushAll(sigs2);
    case TX_PUBKEY:
    case TX_PUBKEYHASH:
        // Signatures are bigger than placeholders or empty scripts:
        if (sigs1.empty() || sigs1[0].empty())
            return PushAll(sigs2);
        return PushAll(sigs1);
    case TX_SCRIPTHASH:
        if (sigs1.empty() || sigs1.back().empty())
            return PushAll(sigs2);
        else if (sigs2.empty() || sigs2.back().empty())
            return PushAll(sigs1);
        else
        {
            // Recur to combine:
            valtype spk = sigs1.back();
            CScript pubKey2(spk.begin(), spk.end());

            txnouttype txType2;
            vector<vector<unsigned char> > vSolutions2;
            Solver(pubKey2, txType2, vSolutions2);
            sigs1.pop_back();
            sigs2.pop_back();
<<<<<<< HEAD
            CScript result = CombineSignatures(pubKey2, checker, txType2, vSolutions2, sigs1, sigs2);
=======
            CScript result = CombineSignatures(pubKey2, txTo, nIn, txType2, vSolutions2, sigs1, sigs2);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            result << spk;
            return result;
        }
    case TX_MULTISIG:
<<<<<<< HEAD
        return CombineMultisig(scriptPubKey, checker, vSolutions, sigs1, sigs2);
=======
        return CombineMultisig(scriptPubKey, txTo, nIn, vSolutions, sigs1, sigs2);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }

    return CScript();
}

CScript CombineSignatures(const CScript& scriptPubKey, const CTransaction& txTo, unsigned int nIn,
                          const CScript& scriptSig1, const CScript& scriptSig2)
{
<<<<<<< HEAD
    TransactionSignatureChecker checker(&txTo, nIn);
    return CombineSignatures(scriptPubKey, checker, scriptSig1, scriptSig2);
}

CScript CombineSignatures(const CScript& scriptPubKey, const BaseSignatureChecker& checker,
                          const CScript& scriptSig1, const CScript& scriptSig2)
{
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    txnouttype txType;
    vector<vector<unsigned char> > vSolutions;
    Solver(scriptPubKey, txType, vSolutions);

    vector<valtype> stack1;
    EvalScript(stack1, scriptSig1, SCRIPT_VERIFY_STRICTENC, BaseSignatureChecker());
    vector<valtype> stack2;
    EvalScript(stack2, scriptSig2, SCRIPT_VERIFY_STRICTENC, BaseSignatureChecker());

<<<<<<< HEAD
    return CombineSignatures(scriptPubKey, checker, txType, vSolutions, stack1, stack2);
}

namespace {
/** Dummy signature checker which accepts all signatures. */
class DummySignatureChecker : public BaseSignatureChecker
{
public:
    DummySignatureChecker() {}

    bool CheckSig(const std::vector<unsigned char>& scriptSig, const std::vector<unsigned char>& vchPubKey, const CScript& scriptCode) const
    {
        return true;
    }
};
const DummySignatureChecker dummyChecker;
}

const BaseSignatureChecker& DummySignatureCreator::Checker() const
{
    return dummyChecker;
}

bool DummySignatureCreator::CreateSig(std::vector<unsigned char>& vchSig, const CKeyID& keyid, const CScript& scriptCode) const
{
    // Create a dummy signature that is a valid DER-encoding
    vchSig.assign(72, '\000');
    vchSig[0] = 0x30;
    vchSig[1] = 69;
    vchSig[2] = 0x02;
    vchSig[3] = 33;
    vchSig[4] = 0x01;
    vchSig[4 + 33] = 0x02;
    vchSig[5 + 33] = 32;
    vchSig[6 + 33] = 0x01;
    vchSig[6 + 33 + 32] = SIGHASH_ALL;
    return true;
=======
    return CombineSignatures(scriptPubKey, txTo, nIn, txType, vSolutions, stack1, stack2);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}
