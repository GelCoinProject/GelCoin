<<<<<<< HEAD
// Copyright (c) 2011-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_BITCOINADDRESSVALIDATOR_H
#define BITCOIN_QT_BITCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class BitcoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit BitcoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
=======
    explicit BitcoinAddressEntryValidator(QObject* parent);

    State validate(QString& input, int& pos) const;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};

/** Bitcoin address widget validator, checks for a valid bitcoin address.
 */
class BitcoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit BitcoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
=======
    explicit BitcoinAddressCheckValidator(QObject* parent);

    State validate(QString& input, int& pos) const;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};

#endif // BITCOIN_QT_BITCOINADDRESSVALIDATOR_H
