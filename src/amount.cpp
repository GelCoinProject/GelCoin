// Copyright (c) 2009-2010 Satoshi Nakamoto
<<<<<<< HEAD
// Copyright (c) 2009-2015 The Bitcoin Core developers
=======
// Copyright (c) 2009-2014 The Bitcoin developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "amount.h"

#include "tinyformat.h"

<<<<<<< HEAD
const std::string CURRENCY_UNIT = "GEL";

CFeeRate::CFeeRate(const CAmount& nFeePaid, size_t nSize)
{
    if (nSize > 0)
        nSatoshisPerK = nFeePaid*1000/nSize;
=======
CFeeRate::CFeeRate(const CAmount& nFeePaid, size_t nSize)
{
    if (nSize > 0)
        nSatoshisPerK = nFeePaid * 1000 / nSize;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    else
        nSatoshisPerK = 0;
}

CAmount CFeeRate::GetFee(size_t nSize) const
{
<<<<<<< HEAD
    CAmount nFee = nSatoshisPerK*nSize / 1000;
=======
    CAmount nFee = nSatoshisPerK * nSize / 1000;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    if (nFee == 0 && nSatoshisPerK > 0)
        nFee = nSatoshisPerK;

    return nFee;
}

std::string CFeeRate::ToString() const
{
<<<<<<< HEAD
    return strprintf("%d.%08d %s/kB", nSatoshisPerK / COIN, nSatoshisPerK % COIN, CURRENCY_UNIT);
=======
    return strprintf("%d.%08d LUX/kB", nSatoshisPerK / COIN, nSatoshisPerK % COIN);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}
