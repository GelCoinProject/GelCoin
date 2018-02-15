// Copyright (c) 2010 Satoshi Nakamoto
<<<<<<< HEAD
// Copyright (c) 2009-2015 The Bitcoin Core developers
=======
// Copyright (c) 2009-2014 The Bitcoin developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparamsbase.h"

<<<<<<< HEAD
#include "tinyformat.h"
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include "util.h"

#include <assert.h>

<<<<<<< HEAD
const std::string CBaseChainParams::MAIN = "main";
const std::string CBaseChainParams::TESTNET = "test";
const std::string CBaseChainParams::REGTEST = "regtest";

void AppendParamsHelpMessages(std::string& strUsage, bool debugHelp)
{
    strUsage += HelpMessageGroup(_("Chain selection options:"));
    strUsage += HelpMessageOpt("-testnet", _("Use the test chain"));
    if (debugHelp) {
        strUsage += HelpMessageOpt("-regtest", "Enter regression test mode, which uses a special chain in which blocks can be solved instantly. "
                                   "This is intended for regression testing tools and app development.");
    }
}
=======
#include <boost/assign/list_of.hpp>

using namespace boost::assign;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

/**
 * Main network
 */
class CBaseMainParams : public CBaseChainParams
{
public:
    CBaseMainParams()
    {
<<<<<<< HEAD
        nRPCPort = 9598;
=======
        networkID = CBaseChainParams::MAIN;
        nRPCPort = 9888;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }
};
static CBaseMainParams mainParams;

/**
 * Testnet (v3)
 */
<<<<<<< HEAD
class CBaseTestNetParams : public CBaseChainParams
=======
class CBaseTestNetParams : public CBaseMainParams
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
public:
    CBaseTestNetParams()
    {
<<<<<<< HEAD
        nRPCPort = 19998;
        strDataDir = "testnet3";
=======
        networkID = CBaseChainParams::TESTNET;
        nRPCPort = 9777;
        strDataDir = "testnet4";
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }
};
static CBaseTestNetParams testNetParams;

/*
 * Regression test
 */
<<<<<<< HEAD
class CBaseRegTestParams : public CBaseChainParams
=======
class CBaseRegTestParams : public CBaseTestNetParams
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
public:
    CBaseRegTestParams()
    {
<<<<<<< HEAD
        nRPCPort = 18332;
=======
        networkID = CBaseChainParams::REGTEST;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        strDataDir = "regtest";
    }
};
static CBaseRegTestParams regTestParams;

<<<<<<< HEAD
=======
/*
 * Unit test
 */
class CBaseUnitTestParams : public CBaseMainParams
{
public:
    CBaseUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strDataDir = "unittest";
    }
};
static CBaseUnitTestParams unitTestParams;

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
static CBaseChainParams* pCurrentBaseParams = 0;

const CBaseChainParams& BaseParams()
{
    assert(pCurrentBaseParams);
    return *pCurrentBaseParams;
}

<<<<<<< HEAD
CBaseChainParams& BaseParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
        return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
        return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectBaseParams(const std::string& chain)
{
    pCurrentBaseParams = &BaseParams(chain);
}

std::string ChainNameFromCommandLine()
=======
void SelectBaseParams(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        pCurrentBaseParams = &mainParams;
        break;
    case CBaseChainParams::TESTNET:
        pCurrentBaseParams = &testNetParams;
        break;
    case CBaseChainParams::REGTEST:
        pCurrentBaseParams = &regTestParams;
        break;
    case CBaseChainParams::UNITTEST:
        pCurrentBaseParams = &unitTestParams;
        break;
    default:
        assert(false && "Unimplemented network");
        return;
    }
}

CBaseChainParams::Network NetworkIdFromCommandLine()
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest)
<<<<<<< HEAD
        throw std::runtime_error("Invalid combination of -regtest and -testnet.");
=======
        return CBaseChainParams::MAX_NETWORK_TYPES;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    if (fRegTest)
        return CBaseChainParams::REGTEST;
    if (fTestNet)
        return CBaseChainParams::TESTNET;
    return CBaseChainParams::MAIN;
}

<<<<<<< HEAD
=======
bool SelectBaseParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectBaseParams(network);
    return true;
}

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
bool AreBaseParamsConfigured()
{
    return pCurrentBaseParams != NULL;
}
