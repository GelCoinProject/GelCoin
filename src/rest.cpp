// Copyright (c) 2009-2010 Satoshi Nakamoto
<<<<<<< HEAD
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chain.h"
#include "chainparams.h"
#include "primitives/block.h"
#include "primitives/transaction.h"
#include "validation.h"
#include "httpserver.h"
#include "rpc/server.h"
#include "streams.h"
#include "sync.h"
#include "txmempool.h"
=======
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "main.h"
#include "primitives/block.h"
#include "primitives/transaction.h"
#include "rpcserver.h"
#include "streams.h"
#include "sync.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include "utilstrencodings.h"
#include "version.h"

#include <boost/algorithm/string.hpp>
<<<<<<< HEAD
#include <boost/dynamic_bitset.hpp>

#include <univalue.h>

using namespace std;

static const size_t MAX_GETUTXOS_OUTPOINTS = 15; //allow a max of 15 outpoints to be queried at once
=======

using namespace std;
using namespace json_spirit;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

enum RetFormat {
    RF_UNDEF,
    RF_BINARY,
    RF_HEX,
    RF_JSON,
};

static const struct {
    enum RetFormat rf;
    const char* name;
} rf_names[] = {
<<<<<<< HEAD
      {RF_UNDEF, ""},
      {RF_BINARY, "bin"},
      {RF_HEX, "hex"},
      {RF_JSON, "json"},
};

struct CCoin {
    uint32_t nHeight;
    CTxOut out;

    ADD_SERIALIZE_METHODS;

    CCoin() : nHeight(0) {}
    CCoin(Coin&& in) : nHeight(in.nHeight), out(std::move(in.out)) {}

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion)
    {
        uint32_t nTxVerDummy = 0;
        READWRITE(nTxVerDummy);
        READWRITE(nHeight);
        READWRITE(out);
    }
};

extern void TxToJSON(const CTransaction& tx, const uint256 hashBlock, UniValue& entry);
extern UniValue blockToJSON(const CBlock& block, const CBlockIndex* blockindex, bool txDetails = false);
extern UniValue mempoolInfoToJSON();
extern UniValue mempoolToJSON(bool fVerbose = false);
extern void ScriptPubKeyToJSON(const CScript& scriptPubKey, UniValue& out, bool fIncludeHex);
extern UniValue blockheaderToJSON(const CBlockIndex* blockindex);

static bool RESTERR(HTTPRequest* req, enum HTTPStatusCode status, string message)
{
    req->WriteHeader("Content-Type", "text/plain");
    req->WriteReply(status, message + "\r\n");
    return false;
}

static enum RetFormat ParseDataFormat(std::string& param, const std::string& strReq)
{
    const std::string::size_type pos = strReq.rfind('.');
    if (pos == std::string::npos)
    {
        param = strReq;
        return rf_names[0].rf;
    }

    param = strReq.substr(0, pos);
    const std::string suff(strReq, pos + 1);

    for (unsigned int i = 0; i < ARRAYLEN(rf_names); i++)
        if (suff == rf_names[i].name)
            return rf_names[i].rf;

    /* If no suffix is found, return original string.  */
    param = strReq;
=======
    {RF_UNDEF, ""},
    {RF_BINARY, "bin"},
    {RF_HEX, "hex"},
    {RF_JSON, "json"},
};

class RestErr
{
public:
    enum HTTPStatusCode status;
    string message;
};

extern void TxToJSON(const CTransaction& tx, const uint256 hashBlock, Object& entry);
extern Object blockToJSON(const CBlock& block, const CBlockIndex* blockindex, bool txDetails = false);

static RestErr RESTERR(enum HTTPStatusCode status, string message)
{
    RestErr re;
    re.status = status;
    re.message = message;
    return re;
}

static enum RetFormat ParseDataFormat(vector<string>& params, const string strReq)
{
    boost::split(params, strReq, boost::is_any_of("."));
    if (params.size() > 1) {
        for (unsigned int i = 0; i < ARRAYLEN(rf_names); i++)
            if (params[1] == rf_names[i].name)
                return rf_names[i].rf;
    }

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    return rf_names[0].rf;
}

static string AvailableDataFormatsString()
{
    string formats = "";
    for (unsigned int i = 0; i < ARRAYLEN(rf_names); i++)
        if (strlen(rf_names[i].name) > 0) {
            formats.append(".");
            formats.append(rf_names[i].name);
            formats.append(", ");
        }

    if (formats.length() > 0)
        return formats.substr(0, formats.length() - 2);

    return formats;
}

static bool ParseHashStr(const string& strReq, uint256& v)
{
    if (!IsHex(strReq) || (strReq.size() != 64))
        return false;

    v.SetHex(strReq);
    return true;
}

<<<<<<< HEAD
static bool CheckWarmup(HTTPRequest* req)
{
    std::string statusmessage;
    if (RPCIsInWarmup(&statusmessage))
         return RESTERR(req, HTTP_SERVICE_UNAVAILABLE, "Service temporarily unavailable: " + statusmessage);
    return true;
}

static bool rest_headers(HTTPRequest* req,
                         const std::string& strURIPart)
{
    if (!CheckWarmup(req))
        return false;
    std::string param;
    const RetFormat rf = ParseDataFormat(param, strURIPart);
    vector<string> path;
    boost::split(path, param, boost::is_any_of("/"));

    if (path.size() != 2)
        return RESTERR(req, HTTP_BAD_REQUEST, "No header count specified. Use /rest/headers/<count>/<hash>.<ext>.");

    long count = strtol(path[0].c_str(), NULL, 10);
    if (count < 1 || count > 2000)
        return RESTERR(req, HTTP_BAD_REQUEST, "Header count out of range: " + path[0]);

    string hashStr = path[1];
    uint256 hash;
    if (!ParseHashStr(hashStr, hash))
        return RESTERR(req, HTTP_BAD_REQUEST, "Invalid hash: " + hashStr);

    std::vector<const CBlockIndex *> headers;
    headers.reserve(count);
    {
        LOCK(cs_main);
        BlockMap::const_iterator it = mapBlockIndex.find(hash);
        const CBlockIndex *pindex = (it != mapBlockIndex.end()) ? it->second : NULL;
        while (pindex != NULL && chainActive.Contains(pindex)) {
            headers.push_back(pindex);
            if (headers.size() == (unsigned long)count)
                break;
            pindex = chainActive.Next(pindex);
        }
    }

    CDataStream ssHeader(SER_NETWORK, PROTOCOL_VERSION);
    BOOST_FOREACH(const CBlockIndex *pindex, headers) {
        ssHeader << pindex->GetBlockHeader();
    }

    switch (rf) {
    case RF_BINARY: {
        string binaryHeader = ssHeader.str();
        req->WriteHeader("Content-Type", "application/octet-stream");
        req->WriteReply(HTTP_OK, binaryHeader);
        return true;
    }

    case RF_HEX: {
        string strHex = HexStr(ssHeader.begin(), ssHeader.end()) + "\n";
        req->WriteHeader("Content-Type", "text/plain");
        req->WriteReply(HTTP_OK, strHex);
        return true;
    }
    case RF_JSON: {
        UniValue jsonHeaders(UniValue::VARR);
        BOOST_FOREACH(const CBlockIndex *pindex, headers) {
            jsonHeaders.push_back(blockheaderToJSON(pindex));
        }
        string strJSON = jsonHeaders.write() + "\n";
        req->WriteHeader("Content-Type", "application/json");
        req->WriteReply(HTTP_OK, strJSON);
        return true;
    }
    default: {
        return RESTERR(req, HTTP_NOT_FOUND, "output format not found (available: .bin, .hex)");
    }
    }

    // not reached
    return true; // continue to process further HTTP reqs on this cxn
}

static bool rest_block(HTTPRequest* req,
                       const std::string& strURIPart,
                       bool showTxDetails)
{
    if (!CheckWarmup(req))
        return false;
    std::string hashStr;
    const RetFormat rf = ParseDataFormat(hashStr, strURIPart);

    uint256 hash;
    if (!ParseHashStr(hashStr, hash))
        return RESTERR(req, HTTP_BAD_REQUEST, "Invalid hash: " + hashStr);
=======
static bool rest_block(AcceptedConnection* conn,
    string& strReq,
    map<string, string>& mapHeaders,
    bool fRun,
    bool showTxDetails)
{
    vector<string> params;
    enum RetFormat rf = ParseDataFormat(params, strReq);

    string hashStr = params[0];
    uint256 hash;
    if (!ParseHashStr(hashStr, hash))
        throw RESTERR(HTTP_BAD_REQUEST, "Invalid hash: " + hashStr);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    CBlock block;
    CBlockIndex* pblockindex = NULL;
    {
        LOCK(cs_main);
        if (mapBlockIndex.count(hash) == 0)
<<<<<<< HEAD
            return RESTERR(req, HTTP_NOT_FOUND, hashStr + " not found");

        pblockindex = mapBlockIndex[hash];
        if (fHavePruned && !(pblockindex->nStatus & BLOCK_HAVE_DATA) && pblockindex->nTx > 0)
            return RESTERR(req, HTTP_NOT_FOUND, hashStr + " not available (pruned data)");

        if (!ReadBlockFromDisk(block, pblockindex, Params().GetConsensus()))
            return RESTERR(req, HTTP_NOT_FOUND, hashStr + " not found");
=======
            throw RESTERR(HTTP_NOT_FOUND, hashStr + " not found");

        pblockindex = mapBlockIndex[hash];
        if (!ReadBlockFromDisk(block, pblockindex))
            throw RESTERR(HTTP_NOT_FOUND, hashStr + " not found");
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }

    CDataStream ssBlock(SER_NETWORK, PROTOCOL_VERSION);
    ssBlock << block;

    switch (rf) {
    case RF_BINARY: {
        string binaryBlock = ssBlock.str();
<<<<<<< HEAD
        req->WriteHeader("Content-Type", "application/octet-stream");
        req->WriteReply(HTTP_OK, binaryBlock);
=======
        conn->stream() << HTTPReplyHeader(HTTP_OK, fRun, binaryBlock.size(), "application/octet-stream") << binaryBlock << std::flush;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return true;
    }

    case RF_HEX: {
        string strHex = HexStr(ssBlock.begin(), ssBlock.end()) + "\n";
<<<<<<< HEAD
        req->WriteHeader("Content-Type", "text/plain");
        req->WriteReply(HTTP_OK, strHex);
=======
        conn->stream() << HTTPReply(HTTP_OK, strHex, fRun, false, "text/plain") << std::flush;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return true;
    }

    case RF_JSON: {
<<<<<<< HEAD
        UniValue objBlock = blockToJSON(block, pblockindex, showTxDetails);
        string strJSON = objBlock.write() + "\n";
        req->WriteHeader("Content-Type", "application/json");
        req->WriteReply(HTTP_OK, strJSON);
=======
        Object objBlock = blockToJSON(block, pblockindex, showTxDetails);
        string strJSON = write_string(Value(objBlock), false) + "\n";
        conn->stream() << HTTPReply(HTTP_OK, strJSON, fRun) << std::flush;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return true;
    }

    default: {
<<<<<<< HEAD
        return RESTERR(req, HTTP_NOT_FOUND, "output format not found (available: " + AvailableDataFormatsString() + ")");
=======
        throw RESTERR(HTTP_NOT_FOUND, "output format not found (available: " + AvailableDataFormatsString() + ")");
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }
    }

    // not reached
    return true; // continue to process further HTTP reqs on this cxn
}

<<<<<<< HEAD
static bool rest_block_extended(HTTPRequest* req, const std::string& strURIPart)
{
    return rest_block(req, strURIPart, true);
}

static bool rest_block_notxdetails(HTTPRequest* req, const std::string& strURIPart)
{
    return rest_block(req, strURIPart, false);
}

static bool rest_chaininfo(HTTPRequest* req, const std::string& strURIPart)
{
    if (!CheckWarmup(req))
        return false;
    std::string param;
    const RetFormat rf = ParseDataFormat(param, strURIPart);

    switch (rf) {
    case RF_JSON: {
        UniValue rpcParams(UniValue::VARR);
        UniValue chainInfoObject = getblockchaininfo(rpcParams, false);
        string strJSON = chainInfoObject.write() + "\n";
        req->WriteHeader("Content-Type", "application/json");
        req->WriteReply(HTTP_OK, strJSON);
        return true;
    }
    default: {
        return RESTERR(req, HTTP_NOT_FOUND, "output format not found (available: json)");
    }
    }

    // not reached
    return true; // continue to process further HTTP reqs on this cxn
}

static bool rest_mempool_info(HTTPRequest* req, const std::string& strURIPart)
{
    if (!CheckWarmup(req))
        return false;
    std::string param;
    const RetFormat rf = ParseDataFormat(param, strURIPart);

    switch (rf) {
    case RF_JSON: {
        UniValue mempoolInfoObject = mempoolInfoToJSON();

        string strJSON = mempoolInfoObject.write() + "\n";
        req->WriteHeader("Content-Type", "application/json");
        req->WriteReply(HTTP_OK, strJSON);
        return true;
    }
    default: {
        return RESTERR(req, HTTP_NOT_FOUND, "output format not found (available: json)");
    }
    }

    // not reached
    return true; // continue to process further HTTP reqs on this cxn
}

static bool rest_mempool_contents(HTTPRequest* req, const std::string& strURIPart)
{
    if (!CheckWarmup(req))
        return false;
    std::string param;
    const RetFormat rf = ParseDataFormat(param, strURIPart);

    switch (rf) {
    case RF_JSON: {
        UniValue mempoolObject = mempoolToJSON(true);

        string strJSON = mempoolObject.write() + "\n";
        req->WriteHeader("Content-Type", "application/json");
        req->WriteReply(HTTP_OK, strJSON);
        return true;
    }
    default: {
        return RESTERR(req, HTTP_NOT_FOUND, "output format not found (available: json)");
    }
    }

    // not reached
    return true; // continue to process further HTTP reqs on this cxn
}

static bool rest_tx(HTTPRequest* req, const std::string& strURIPart)
{
    if (!CheckWarmup(req))
        return false;
    std::string hashStr;
    const RetFormat rf = ParseDataFormat(hashStr, strURIPart);

    uint256 hash;
    if (!ParseHashStr(hashStr, hash))
        return RESTERR(req, HTTP_BAD_REQUEST, "Invalid hash: " + hashStr);

    CTransaction tx;
    uint256 hashBlock = uint256();
    if (!GetTransaction(hash, tx, Params().GetConsensus(), hashBlock, true))
        return RESTERR(req, HTTP_NOT_FOUND, hashStr + " not found");
=======
static bool rest_block_extended(AcceptedConnection* conn,
    string& strReq,
    map<string, string>& mapHeaders,
    bool fRun)
{
    return rest_block(conn, strReq, mapHeaders, fRun, true);
}

static bool rest_block_notxdetails(AcceptedConnection* conn,
    string& strReq,
    map<string, string>& mapHeaders,
    bool fRun)
{
    return rest_block(conn, strReq, mapHeaders, fRun, false);
}

static bool rest_tx(AcceptedConnection* conn,
    string& strReq,
    map<string, string>& mapHeaders,
    bool fRun)
{
    vector<string> params;
    enum RetFormat rf = ParseDataFormat(params, strReq);

    string hashStr = params[0];
    uint256 hash;
    if (!ParseHashStr(hashStr, hash))
        throw RESTERR(HTTP_BAD_REQUEST, "Invalid hash: " + hashStr);

    CTransaction tx;
    uint256 hashBlock = 0;
    if (!GetTransaction(hash, tx, hashBlock, true))
        throw RESTERR(HTTP_NOT_FOUND, hashStr + " not found");
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    CDataStream ssTx(SER_NETWORK, PROTOCOL_VERSION);
    ssTx << tx;

    switch (rf) {
    case RF_BINARY: {
        string binaryTx = ssTx.str();
<<<<<<< HEAD
        req->WriteHeader("Content-Type", "application/octet-stream");
        req->WriteReply(HTTP_OK, binaryTx);
=======
        conn->stream() << HTTPReplyHeader(HTTP_OK, fRun, binaryTx.size(), "application/octet-stream") << binaryTx << std::flush;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return true;
    }

    case RF_HEX: {
        string strHex = HexStr(ssTx.begin(), ssTx.end()) + "\n";
<<<<<<< HEAD
        req->WriteHeader("Content-Type", "text/plain");
        req->WriteReply(HTTP_OK, strHex);
=======
        conn->stream() << HTTPReply(HTTP_OK, strHex, fRun, false, "text/plain") << std::flush;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return true;
    }

    case RF_JSON: {
<<<<<<< HEAD
        UniValue objTx(UniValue::VOBJ);
        TxToJSON(tx, hashBlock, objTx);
        string strJSON = objTx.write() + "\n";
        req->WriteHeader("Content-Type", "application/json");
        req->WriteReply(HTTP_OK, strJSON);
        return true;
    }

    default: {
        return RESTERR(req, HTTP_NOT_FOUND, "output format not found (available: " + AvailableDataFormatsString() + ")");
    }
    }

    // not reached
    return true; // continue to process further HTTP reqs on this cxn
}

static bool rest_getutxos(HTTPRequest* req, const std::string& strURIPart)
{
    if (!CheckWarmup(req))
        return false;
    std::string param;
    const RetFormat rf = ParseDataFormat(param, strURIPart);

    vector<string> uriParts;
    if (param.length() > 1)
    {
        std::string strUriParams = param.substr(1);
        boost::split(uriParts, strUriParams, boost::is_any_of("/"));
    }

    // throw exception in case of a empty request
    std::string strRequestMutable = req->ReadBody();
    if (strRequestMutable.length() == 0 && uriParts.size() == 0)
        return RESTERR(req, HTTP_INTERNAL_SERVER_ERROR, "Error: empty request");

    bool fInputParsed = false;
    bool fCheckMemPool = false;
    vector<COutPoint> vOutPoints;

    // parse/deserialize input
    // input-format = output-format, rest/getutxos/bin requires binary input, gives binary output, ...

    if (uriParts.size() > 0)
    {

        //inputs is sent over URI scheme (/rest/getutxos/checkmempool/txid1-n/txid2-n/...)
        if (uriParts.size() > 0 && uriParts[0] == "checkmempool")
            fCheckMemPool = true;

        for (size_t i = (fCheckMemPool) ? 1 : 0; i < uriParts.size(); i++)
        {
            uint256 txid;
            int32_t nOutput;
            std::string strTxid = uriParts[i].substr(0, uriParts[i].find("-"));
            std::string strOutput = uriParts[i].substr(uriParts[i].find("-")+1);

            if (!ParseInt32(strOutput, &nOutput) || !IsHex(strTxid))
                return RESTERR(req, HTTP_INTERNAL_SERVER_ERROR, "Parse error");

            txid.SetHex(strTxid);
            vOutPoints.push_back(COutPoint(txid, (uint32_t)nOutput));
        }

        if (vOutPoints.size() > 0)
            fInputParsed = true;
        else
            return RESTERR(req, HTTP_INTERNAL_SERVER_ERROR, "Error: empty request");
    }

    switch (rf) {
    case RF_HEX: {
        // convert hex to bin, continue then with bin part
        std::vector<unsigned char> strRequestV = ParseHex(strRequestMutable);
        strRequestMutable.assign(strRequestV.begin(), strRequestV.end());
    }

    case RF_BINARY: {
        try {
            //deserialize only if user sent a request
            if (strRequestMutable.size() > 0)
            {
                if (fInputParsed) //don't allow sending input over URI and HTTP RAW DATA
                    return RESTERR(req, HTTP_INTERNAL_SERVER_ERROR, "Combination of URI scheme inputs and raw post data is not allowed");

                CDataStream oss(SER_NETWORK, PROTOCOL_VERSION);
                oss << strRequestMutable;
                oss >> fCheckMemPool;
                oss >> vOutPoints;
            }
        } catch (const std::ios_base::failure& e) {
            // abort in case of unreadable binary data
            return RESTERR(req, HTTP_INTERNAL_SERVER_ERROR, "Parse error");
        }
        break;
    }

    case RF_JSON: {
        if (!fInputParsed)
            return RESTERR(req, HTTP_INTERNAL_SERVER_ERROR, "Error: empty request");
        break;
    }
    default: {
        return RESTERR(req, HTTP_NOT_FOUND, "output format not found (available: " + AvailableDataFormatsString() + ")");
    }
    }

    // limit max outpoints
    if (vOutPoints.size() > MAX_GETUTXOS_OUTPOINTS)
        return RESTERR(req, HTTP_INTERNAL_SERVER_ERROR, strprintf("Error: max outpoints exceeded (max: %d, tried: %d)", MAX_GETUTXOS_OUTPOINTS, vOutPoints.size()));

    // check spentness and form a bitmap (as well as a JSON capable human-readable string representation)
    vector<unsigned char> bitmap;
    vector<CCoin> outs;
    std::string bitmapStringRepresentation;
    boost::dynamic_bitset<unsigned char> hits(vOutPoints.size());
    {
        LOCK2(cs_main, mempool.cs);

        CCoinsView viewDummy;
        CCoinsViewCache view(&viewDummy);

        CCoinsViewCache& viewChain = *pcoinsTip;
        CCoinsViewMemPool viewMempool(&viewChain, mempool);

        if (fCheckMemPool)
            view.SetBackend(viewMempool); // switch cache backend to db+mempool in case user likes to query mempool

        for (size_t i = 0; i < vOutPoints.size(); i++) {
            Coin coin;
            if (view.GetCoin(vOutPoints[i], coin) && !mempool.isSpent(vOutPoints[i])) {
                hits[i] = true;
                outs.emplace_back(std::move(coin));
            }

            bitmapStringRepresentation.append(hits[i] ? "1" : "0"); // form a binary string representation (human-readable for json output)
        }
    }
    boost::to_block_range(hits, std::back_inserter(bitmap));

    switch (rf) {
    case RF_BINARY: {
        // serialize data
        // use exact same output as mentioned in Bip64
        CDataStream ssGetUTXOResponse(SER_NETWORK, PROTOCOL_VERSION);
        ssGetUTXOResponse << chainActive.Height() << chainActive.Tip()->GetBlockHash() << bitmap << outs;
        string ssGetUTXOResponseString = ssGetUTXOResponse.str();

        req->WriteHeader("Content-Type", "application/octet-stream");
        req->WriteReply(HTTP_OK, ssGetUTXOResponseString);
        return true;
    }

    case RF_HEX: {
        CDataStream ssGetUTXOResponse(SER_NETWORK, PROTOCOL_VERSION);
        ssGetUTXOResponse << chainActive.Height() << chainActive.Tip()->GetBlockHash() << bitmap << outs;
        string strHex = HexStr(ssGetUTXOResponse.begin(), ssGetUTXOResponse.end()) + "\n";

        req->WriteHeader("Content-Type", "text/plain");
        req->WriteReply(HTTP_OK, strHex);
        return true;
    }

    case RF_JSON: {
        UniValue objGetUTXOResponse(UniValue::VOBJ);

        // pack in some essentials
        // use more or less the same output as mentioned in Bip64
        objGetUTXOResponse.push_back(Pair("chainHeight", chainActive.Height()));
        objGetUTXOResponse.push_back(Pair("chaintipHash", chainActive.Tip()->GetBlockHash().GetHex()));
        objGetUTXOResponse.push_back(Pair("bitmap", bitmapStringRepresentation));

        UniValue utxos(UniValue::VARR);
        BOOST_FOREACH (const CCoin& coin, outs) {
            UniValue utxo(UniValue::VOBJ);
            utxo.push_back(Pair("height", (int32_t)coin.nHeight));
            utxo.push_back(Pair("value", ValueFromAmount(coin.out.nValue)));

            // include the script in a json output
            UniValue o(UniValue::VOBJ);
            ScriptPubKeyToJSON(coin.out.scriptPubKey, o, true);
            utxo.push_back(Pair("scriptPubKey", o));
            utxos.push_back(utxo);
        }
        objGetUTXOResponse.push_back(Pair("utxos", utxos));

        // return json string
        string strJSON = objGetUTXOResponse.write() + "\n";
        req->WriteHeader("Content-Type", "application/json");
        req->WriteReply(HTTP_OK, strJSON);
        return true;
    }
    default: {
        return RESTERR(req, HTTP_NOT_FOUND, "output format not found (available: " + AvailableDataFormatsString() + ")");
=======
        Object objTx;
        TxToJSON(tx, hashBlock, objTx);
        string strJSON = write_string(Value(objTx), false) + "\n";
        conn->stream() << HTTPReply(HTTP_OK, strJSON, fRun) << std::flush;
        return true;
    }

    default: {
        throw RESTERR(HTTP_NOT_FOUND, "output format not found (available: " + AvailableDataFormatsString() + ")");
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }
    }

    // not reached
    return true; // continue to process further HTTP reqs on this cxn
}

static const struct {
    const char* prefix;
<<<<<<< HEAD
    bool (*handler)(HTTPRequest* req, const std::string& strReq);
} uri_prefixes[] = {
      {"/rest/tx/", rest_tx},
      {"/rest/block/notxdetails/", rest_block_notxdetails},
      {"/rest/block/", rest_block_extended},
      {"/rest/chaininfo", rest_chaininfo},
      {"/rest/mempool/info", rest_mempool_info},
      {"/rest/mempool/contents", rest_mempool_contents},
      {"/rest/headers/", rest_headers},
      {"/rest/getutxos", rest_getutxos},
};

bool StartREST()
{
    for (unsigned int i = 0; i < ARRAYLEN(uri_prefixes); i++)
        RegisterHTTPHandler(uri_prefixes[i].prefix, false, uri_prefixes[i].handler);
    return true;
}

void InterruptREST()
{
}

void StopREST()
{
    for (unsigned int i = 0; i < ARRAYLEN(uri_prefixes); i++)
        UnregisterHTTPHandler(uri_prefixes[i].prefix, false);
=======
    bool (*handler)(AcceptedConnection* conn,
        string& strURI,
        map<string, string>& mapHeaders,
        bool fRun);
} uri_prefixes[] = {
    {"/rest/tx/", rest_tx},
    {"/rest/block/notxdetails/", rest_block_notxdetails},
    {"/rest/block/", rest_block_extended},
};

bool HTTPReq_REST(AcceptedConnection* conn,
    string& strURI,
    map<string, string>& mapHeaders,
    bool fRun)
{
    try {
        std::string statusmessage;
        if (RPCIsInWarmup(&statusmessage))
            throw RESTERR(HTTP_SERVICE_UNAVAILABLE, "Service temporarily unavailable: " + statusmessage);

        for (unsigned int i = 0; i < ARRAYLEN(uri_prefixes); i++) {
            unsigned int plen = strlen(uri_prefixes[i].prefix);
            if (strURI.substr(0, plen) == uri_prefixes[i].prefix) {
                string strReq = strURI.substr(plen);
                return uri_prefixes[i].handler(conn, strReq, mapHeaders, fRun);
            }
        }
    } catch (RestErr& re) {
        conn->stream() << HTTPReply(re.status, re.message + "\r\n", false, false, "text/plain") << std::flush;
        return false;
    }

    conn->stream() << HTTPError(HTTP_NOT_FOUND, false) << std::flush;
    return false;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}
