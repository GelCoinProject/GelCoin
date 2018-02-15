<<<<<<< HEAD
// Copyright (c) 2011-2013 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_WALLETMODELTRANSACTION_H
#define BITCOIN_QT_WALLETMODELTRANSACTION_H

#include "walletmodel.h"

#include <QObject>

class SendCoinsRecipient;

class CReserveKey;
class CWallet;
class CWalletTx;

/** Data model for a walletmodel transaction. */
class WalletModelTransaction
{
public:
<<<<<<< HEAD
    explicit WalletModelTransaction(const QList<SendCoinsRecipient> &recipients);
=======
    explicit WalletModelTransaction(const QList<SendCoinsRecipient>& recipients);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    ~WalletModelTransaction();

    QList<SendCoinsRecipient> getRecipients();

<<<<<<< HEAD
    CWalletTx *getTransaction();
=======
    CWalletTx* getTransaction();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    unsigned int getTransactionSize();

    void setTransactionFee(const CAmount& newFee);
    CAmount getTransactionFee();

    CAmount getTotalTransactionAmount();

<<<<<<< HEAD
    void newPossibleKeyChange(CWallet *wallet);
    CReserveKey *getPossibleKeyChange();

    void reassignAmounts(int nChangePosRet); // needed for the subtract-fee-from-amount feature

private:
    QList<SendCoinsRecipient> recipients;
    CWalletTx *walletTransaction;
    CReserveKey *keyChange;
=======
    void newPossibleKeyChange(CWallet* wallet);
    CReserveKey* getPossibleKeyChange();

private:
    const QList<SendCoinsRecipient> recipients;
    CWalletTx* walletTransaction;
    CReserveKey* keyChange;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    CAmount fee;
};

#endif // BITCOIN_QT_WALLETMODELTRANSACTION_H
