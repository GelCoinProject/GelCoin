<<<<<<< HEAD
// Copyright (c) 2014-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// Copyright (c) 2014-2017 The GelCoin developers
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "validation.h"
#include "net.h"

#include "test/test_gelcoin.h"

#include <boost/signals2/signal.hpp>
#include <boost/test/unit_test.hpp>

BOOST_FIXTURE_TEST_SUITE(main_tests, TestingSetup)

static void TestBlockSubsidyHalvings(const Consensus::Params& consensusParams)
{
    // tested in gelcoin_tests.cpp
    //int maxHalvings = 64;
    //CAmount nInitialSubsidy = 50 * COIN;

    //CAmount nPreviousSubsidy = nInitialSubsidy * 2; // for height == 0
    //BOOST_CHECK_EQUAL(nPreviousSubsidy, nInitialSubsidy * 2);
    //for (int nHalvings = 0; nHalvings < maxHalvings; nHalvings++) {
    //    int nHeight = nHalvings * consensusParams.nSubsidyHalvingInterval;
    //    CAmount nSubsidy = GetBlockSubsidy(0, nHeight, consensusParams);
    //    BOOST_CHECK(nSubsidy <= nInitialSubsidy);
    //    BOOST_CHECK_EQUAL(nSubsidy, nPreviousSubsidy / 2);
    //    nPreviousSubsidy = nSubsidy;
    //}
    //BOOST_CHECK_EQUAL(GetBlockSubsidy(0, maxHalvings * consensusParams.nSubsidyHalvingInterval, consensusParams), 0);
}

static void TestBlockSubsidyHalvings(int nSubsidyHalvingInterval)
{
    // tested in gelcoin_tests.cpp
    //Consensus::Params consensusParams;
    //consensusParams.nSubsidyHalvingInterval = nSubsidyHalvingInterval;
    //TestBlockSubsidyHalvings(consensusParams);
}

BOOST_AUTO_TEST_CASE(block_subsidy_test)
{
    // tested in gelcoin_tests.cpp
    //TestBlockSubsidyHalvings(Params(CBaseChainParams::MAIN).GetConsensus()); // As in main
    //TestBlockSubsidyHalvings(150); // As in regtest
    //TestBlockSubsidyHalvings(1000); // Just another interval
}

BOOST_AUTO_TEST_CASE(subsidy_limit_test)
{
    // tested in gelcoin_tests.cpp
    //const Consensus::Params& consensusParams = Params(CBaseChainParams::MAIN).GetConsensus();
    //CAmount nSum = 0;
    //for (int nHeight = 0; nHeight < 14000000; nHeight += 1000) {
    //    /* @TODO fix subsidity, add nBits */
    //    CAmount nSubsidy = GetBlockSubsidy(0, nHeight, consensusParams);
    //    BOOST_CHECK(nSubsidy <= 25 * COIN);
    //    nSum += nSubsidy * 1000;
    //    BOOST_CHECK(MoneyRange(nSum));
    //}
    //BOOST_CHECK_EQUAL(nSum, 1350824726649000ULL);
}

bool ReturnFalse() { return false; }
bool ReturnTrue() { return true; }

BOOST_AUTO_TEST_CASE(test_combiner_all)
{
    boost::signals2::signal<bool (), CombinerAll> Test;
    BOOST_CHECK(Test());
    Test.connect(&ReturnFalse);
    BOOST_CHECK(!Test());
    Test.connect(&ReturnTrue);
    BOOST_CHECK(!Test());
    Test.disconnect(&ReturnFalse);
    BOOST_CHECK(Test());
    Test.disconnect(&ReturnTrue);
    BOOST_CHECK(Test());
}
=======
// Copyright (c) 2014 The Bitcoin Core developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The LUX developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "primitives/transaction.h"
#include "main.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(main_tests)

BOOST_AUTO_TEST_CASE(subsidy_limit_test)
{
    CAmount nSum = 0;
    for (int nHeight = 0; nHeight < 14000000; nHeight += 1000) {
        /* @TODO fix subsidity, add nBits */
        CAmount nSubsidy = GetProofOfWorkReward(0, nHeight);
        BOOST_CHECK(nSubsidy <= 50 * COIN);
        nSum += nSubsidy * 1000;
        BOOST_CHECK(MoneyRange(nSum));
    }
    BOOST_CHECK(nSum == 2099999997690000ULL);
}

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
BOOST_AUTO_TEST_SUITE_END()
