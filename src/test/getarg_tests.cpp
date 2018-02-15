<<<<<<< HEAD
// Copyright (c) 2012-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "util.h"
#include "test/test_gelcoin.h"
=======
// Copyright (c) 2012-2013 The Bitcoin Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "util.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

<<<<<<< HEAD
BOOST_FIXTURE_TEST_SUITE(getarg_tests, BasicTestingSetup)
=======
BOOST_AUTO_TEST_SUITE(getarg_tests)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

static void ResetArgs(const std::string& strArg)
{
    std::vector<std::string> vecArg;
    if (strArg.size())
      boost::split(vecArg, strArg, boost::is_space(), boost::token_compress_on);

    // Insert dummy executable name:
<<<<<<< HEAD
    vecArg.insert(vecArg.begin(), "testgelcoin");
=======
    vecArg.insert(vecArg.begin(), "testbitcoin");
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    // Convert to char*:
    std::vector<const char*> vecChar;
    BOOST_FOREACH(std::string& s, vecArg)
        vecChar.push_back(s.c_str());

    ParseParameters(vecChar.size(), &vecChar[0]);
}

BOOST_AUTO_TEST_CASE(boolarg)
{
    ResetArgs("-foo");
    BOOST_CHECK(GetBoolArg("-foo", false));
    BOOST_CHECK(GetBoolArg("-foo", true));

    BOOST_CHECK(!GetBoolArg("-fo", false));
    BOOST_CHECK(GetBoolArg("-fo", true));

    BOOST_CHECK(!GetBoolArg("-fooo", false));
    BOOST_CHECK(GetBoolArg("-fooo", true));

    ResetArgs("-foo=0");
    BOOST_CHECK(!GetBoolArg("-foo", false));
    BOOST_CHECK(!GetBoolArg("-foo", true));

    ResetArgs("-foo=1");
    BOOST_CHECK(GetBoolArg("-foo", false));
    BOOST_CHECK(GetBoolArg("-foo", true));

    // New 0.6 feature: auto-map -nosomething to !-something:
    ResetArgs("-nofoo");
    BOOST_CHECK(!GetBoolArg("-foo", false));
    BOOST_CHECK(!GetBoolArg("-foo", true));

    ResetArgs("-nofoo=1");
    BOOST_CHECK(!GetBoolArg("-foo", false));
    BOOST_CHECK(!GetBoolArg("-foo", true));

<<<<<<< HEAD
    ResetArgs("-foo -nofoo");  // -nofoo should win
    BOOST_CHECK(!GetBoolArg("-foo", false));
    BOOST_CHECK(!GetBoolArg("-foo", true));

    ResetArgs("-foo=1 -nofoo=1");  // -nofoo should win
    BOOST_CHECK(!GetBoolArg("-foo", false));
    BOOST_CHECK(!GetBoolArg("-foo", true));

    ResetArgs("-foo=0 -nofoo=0");  // -nofoo=0 should win
    BOOST_CHECK(GetBoolArg("-foo", false));
    BOOST_CHECK(GetBoolArg("-foo", true));

=======
    ResetArgs("-foo -nofoo");  // -foo should win
    BOOST_CHECK(GetBoolArg("-foo", false));
    BOOST_CHECK(GetBoolArg("-foo", true));

    ResetArgs("-foo=1 -nofoo=1");  // -foo should win
    BOOST_CHECK(GetBoolArg("-foo", false));
    BOOST_CHECK(GetBoolArg("-foo", true));

    ResetArgs("-foo=0 -nofoo=0");  // -foo should win
    BOOST_CHECK(!GetBoolArg("-foo", false));
    BOOST_CHECK(!GetBoolArg("-foo", true));

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    // New 0.6 feature: treat -- same as -:
    ResetArgs("--foo=1");
    BOOST_CHECK(GetBoolArg("-foo", false));
    BOOST_CHECK(GetBoolArg("-foo", true));

    ResetArgs("--nofoo=1");
    BOOST_CHECK(!GetBoolArg("-foo", false));
    BOOST_CHECK(!GetBoolArg("-foo", true));

}

BOOST_AUTO_TEST_CASE(stringarg)
{
    ResetArgs("");
    BOOST_CHECK_EQUAL(GetArg("-foo", ""), "");
    BOOST_CHECK_EQUAL(GetArg("-foo", "eleven"), "eleven");

    ResetArgs("-foo -bar");
    BOOST_CHECK_EQUAL(GetArg("-foo", ""), "");
    BOOST_CHECK_EQUAL(GetArg("-foo", "eleven"), "");

    ResetArgs("-foo=");
    BOOST_CHECK_EQUAL(GetArg("-foo", ""), "");
    BOOST_CHECK_EQUAL(GetArg("-foo", "eleven"), "");

    ResetArgs("-foo=11");
    BOOST_CHECK_EQUAL(GetArg("-foo", ""), "11");
    BOOST_CHECK_EQUAL(GetArg("-foo", "eleven"), "11");

    ResetArgs("-foo=eleven");
    BOOST_CHECK_EQUAL(GetArg("-foo", ""), "eleven");
    BOOST_CHECK_EQUAL(GetArg("-foo", "eleven"), "eleven");

}

BOOST_AUTO_TEST_CASE(intarg)
{
    ResetArgs("");
    BOOST_CHECK_EQUAL(GetArg("-foo", 11), 11);
    BOOST_CHECK_EQUAL(GetArg("-foo", 0), 0);

    ResetArgs("-foo -bar");
    BOOST_CHECK_EQUAL(GetArg("-foo", 11), 0);
    BOOST_CHECK_EQUAL(GetArg("-bar", 11), 0);

    ResetArgs("-foo=11 -bar=12");
    BOOST_CHECK_EQUAL(GetArg("-foo", 0), 11);
    BOOST_CHECK_EQUAL(GetArg("-bar", 11), 12);

    ResetArgs("-foo=NaN -bar=NotANumber");
    BOOST_CHECK_EQUAL(GetArg("-foo", 1), 0);
    BOOST_CHECK_EQUAL(GetArg("-bar", 11), 0);
}

<<<<<<< HEAD
BOOST_AUTO_TEST_CASE(doublegelcoin)
=======
BOOST_AUTO_TEST_CASE(doublelux)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    ResetArgs("--foo");
    BOOST_CHECK_EQUAL(GetBoolArg("-foo", false), true);

    ResetArgs("--foo=verbose --bar=1");
    BOOST_CHECK_EQUAL(GetArg("-foo", ""), "verbose");
    BOOST_CHECK_EQUAL(GetArg("-bar", 0), 1);
}

BOOST_AUTO_TEST_CASE(boolargno)
{
    ResetArgs("-nofoo");
    BOOST_CHECK(!GetBoolArg("-foo", true));
    BOOST_CHECK(!GetBoolArg("-foo", false));

    ResetArgs("-nofoo=1");
    BOOST_CHECK(!GetBoolArg("-foo", true));
    BOOST_CHECK(!GetBoolArg("-foo", false));

    ResetArgs("-nofoo=0");
    BOOST_CHECK(GetBoolArg("-foo", true));
    BOOST_CHECK(GetBoolArg("-foo", false));

<<<<<<< HEAD
    ResetArgs("-foo --nofoo"); // --nofoo should win
    BOOST_CHECK(!GetBoolArg("-foo", true));
    BOOST_CHECK(!GetBoolArg("-foo", false));
=======
    ResetArgs("-foo --nofoo");
    BOOST_CHECK(GetBoolArg("-foo", true));
    BOOST_CHECK(GetBoolArg("-foo", false));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    ResetArgs("-nofoo -foo"); // foo always wins:
    BOOST_CHECK(GetBoolArg("-foo", true));
    BOOST_CHECK(GetBoolArg("-foo", false));
}

BOOST_AUTO_TEST_SUITE_END()
