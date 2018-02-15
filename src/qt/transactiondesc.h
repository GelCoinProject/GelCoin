<<<<<<< HEAD
// Copyright (c) 2011-2013 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_TRANSACTIONDESC_H
#define BITCOIN_QT_TRANSACTIONDESC_H

#include <QObject>
#include <QString>

class TransactionRecord;

class CWallet;
class CWalletTx;

/** Provide a human-readable extended HTML description of a transaction.
 */
<<<<<<< HEAD
class TransactionDesc: public QObject
=======
class TransactionDesc : public QObject
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    Q_OBJECT

public:
<<<<<<< HEAD
    static QString toHTML(CWallet *wallet, CWalletTx &wtx, TransactionRecord *rec, int unit);
=======
    static QString toHTML(CWallet* wallet, CWalletTx& wtx, TransactionRecord* rec, int unit);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

private:
    TransactionDesc() {}

    static QString FormatTxStatus(const CWalletTx& wtx);
};

#endif // BITCOIN_QT_TRANSACTIONDESC_H
