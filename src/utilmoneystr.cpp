// Copyright (c) 2009-2010 Satoshi Nakamoto
<<<<<<< HEAD
// Copyright (c) 2009-2015 The Bitcoin Core developers
=======
// Copyright (c) 2009-2014 The Bitcoin developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "utilmoneystr.h"

#include "primitives/transaction.h"
#include "tinyformat.h"
#include "utilstrencodings.h"

using namespace std;

<<<<<<< HEAD
std::string FormatMoney(const CAmount& n)
=======
string FormatMoney(const CAmount& n, bool fPlus)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    // Note: not using straight sprintf here because we do NOT want
    // localized number formatting.
    int64_t n_abs = (n > 0 ? n : -n);
<<<<<<< HEAD
    int64_t quotient = n_abs/COIN;
    int64_t remainder = n_abs%COIN;
=======
    int64_t quotient = n_abs / COIN;
    int64_t remainder = n_abs % COIN;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    string str = strprintf("%d.%08d", quotient, remainder);

    // Right-trim excess zeros before the decimal point:
    int nTrim = 0;
<<<<<<< HEAD
    for (int i = str.size()-1; (str[i] == '0' && isdigit(str[i-2])); --i)
        ++nTrim;
    if (nTrim)
        str.erase(str.size()-nTrim, nTrim);

    if (n < 0)
        str.insert((unsigned int)0, 1, '-');
=======
    for (int i = str.size() - 1; (str[i] == '0' && isdigit(str[i - 2])); --i)
        ++nTrim;
    if (nTrim)
        str.erase(str.size() - nTrim, nTrim);

    if (n < 0)
        str.insert((unsigned int)0, 1, '-');
    else if (fPlus && n > 0)
        str.insert((unsigned int)0, 1, '+');
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    return str;
}


bool ParseMoney(const string& str, CAmount& nRet)
{
    return ParseMoney(str.c_str(), nRet);
}

bool ParseMoney(const char* pszIn, CAmount& nRet)
{
    string strWhole;
    int64_t nUnits = 0;
    const char* p = pszIn;
    while (isspace(*p))
        p++;
<<<<<<< HEAD
    for (; *p; p++)
    {
        if (*p == '.')
        {
            p++;
            int64_t nMult = CENT*10;
            while (isdigit(*p) && (nMult > 0))
            {
=======
    for (; *p; p++) {
        if (*p == '.') {
            p++;
            int64_t nMult = CENT * 10;
            while (isdigit(*p) && (nMult > 0)) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                nUnits += nMult * (*p++ - '0');
                nMult /= 10;
            }
            break;
        }
        if (isspace(*p))
            break;
        if (!isdigit(*p))
            return false;
        strWhole.insert(strWhole.end(), *p);
    }
    for (; *p; p++)
        if (!isspace(*p))
            return false;
    if (strWhole.size() > 10) // guard against 63 bit overflow
        return false;
    if (nUnits < 0 || nUnits > COIN)
        return false;
    int64_t nWhole = atoi64(strWhole);
<<<<<<< HEAD
    CAmount nValue = nWhole*COIN + nUnits;
=======
    CAmount nValue = nWhole * COIN + nUnits;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    nRet = nValue;
    return true;
}
