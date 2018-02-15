<<<<<<< HEAD
// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
=======
// Copyright (c) 2009-2010 Satoshi Nakamoto             -*- c++ -*-
// Copyright (c) 2009-2014 The Bitcoin developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

/**
 * Money parsing/formatting utilities.
 */
#ifndef BITCOIN_UTILMONEYSTR_H
#define BITCOIN_UTILMONEYSTR_H

#include <stdint.h>
#include <string>

#include "amount.h"

<<<<<<< HEAD
std::string FormatMoney(const CAmount& n);
=======
std::string FormatMoney(const CAmount& n, bool fPlus = false);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
bool ParseMoney(const std::string& str, CAmount& nRet);
bool ParseMoney(const char* pszIn, CAmount& nRet);

#endif // BITCOIN_UTILMONEYSTR_H
