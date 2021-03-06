<<<<<<< HEAD
// Copyright (c) 2012-2015 The Bitcoin Core developers
=======
// Copyright (c) 2012-2013 The Bitcoin Core developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "compat/sanity.h"
#include "key.h"
<<<<<<< HEAD
#include "test/test_gelcoin.h"

#include <boost/test/unit_test.hpp>

BOOST_FIXTURE_TEST_SUITE(sanity_tests, BasicTestingSetup)
=======

#include <boost/test/unit_test.hpp>
BOOST_AUTO_TEST_SUITE(sanity_tests)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

BOOST_AUTO_TEST_CASE(basic_sanity)
{
  BOOST_CHECK_MESSAGE(glibc_sanity_test() == true, "libc sanity test");
  BOOST_CHECK_MESSAGE(glibcxx_sanity_test() == true, "stdlib sanity test");
  BOOST_CHECK_MESSAGE(ECC_InitSanityCheck() == true, "openssl ECC test");
}

BOOST_AUTO_TEST_SUITE_END()
