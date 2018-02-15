<<<<<<< HEAD
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2009-2014 The Bitcoin developers               -*- c++ -*-
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CORE_IO_H
#define BITCOIN_CORE_IO_H

#include <string>
#include <vector>

class CBlock;
class CScript;
class CTransaction;
class uint256;
class UniValue;

// core_read.cpp
<<<<<<< HEAD
extern CScript ParseScript(const std::string& s);
extern std::string ScriptToAsmStr(const CScript& script, const bool fAttemptSighashDecode = false);
=======
extern CScript ParseScript(std::string s);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
extern bool DecodeHexTx(CTransaction& tx, const std::string& strHexTx);
extern bool DecodeHexBlk(CBlock&, const std::string& strHexBlk);
extern uint256 ParseHashUV(const UniValue& v, const std::string& strName);
extern uint256 ParseHashStr(const std::string&, const std::string& strName);
extern std::vector<unsigned char> ParseHexUV(const UniValue& v, const std::string& strName);

// core_write.cpp
extern std::string FormatScript(const CScript& script);
extern std::string EncodeHexTx(const CTransaction& tx);
<<<<<<< HEAD
extern void ScriptPubKeyToUniv(const CScript& scriptPubKey, UniValue& out, bool fIncludeHex);
=======
extern void ScriptPubKeyToUniv(const CScript& scriptPubKey,
    UniValue& out,
    bool fIncludeHex);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
extern void TxToUniv(const CTransaction& tx, const uint256& hashBlock, UniValue& entry);

#endif // BITCOIN_CORE_IO_H
