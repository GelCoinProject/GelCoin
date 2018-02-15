<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "walletmodeltransaction.h"

<<<<<<< HEAD
#include "wallet/wallet.h"

WalletModelTransaction::WalletModelTransaction(const QList<SendCoinsRecipient> &recipients) :
    recipients(recipients),
    walletTransaction(0),
    keyChange(0),
    fee(0)
=======
#include "wallet.h"

WalletModelTransaction::WalletModelTransaction(const QList<SendCoinsRecipient>& recipients) : recipients(recipients),
                                                                                              walletTransaction(0),
                                                                                              keyChange(0),
                                                                                              fee(0)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    walletTransaction = new CWalletTx();
}

WalletModelTransaction::~WalletModelTransaction()
{
    delete keyChange;
    delete walletTransaction;
}

QList<SendCoinsRecipient> WalletModelTransaction::getRecipients()
{
    return recipients;
}

<<<<<<< HEAD
CWalletTx *WalletModelTransaction::getTransaction()
=======
CWalletTx* WalletModelTransaction::getTransaction()
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    return walletTransaction;
}

unsigned int WalletModelTransaction::getTransactionSize()
{
    return (!walletTransaction ? 0 : (::GetSerializeSize(*(CTransaction*)walletTransaction, SER_NETWORK, PROTOCOL_VERSION)));
}

CAmount WalletModelTransaction::getTransactionFee()
{
    return fee;
}

void WalletModelTransaction::setTransactionFee(const CAmount& newFee)
{
    fee = newFee;
}

<<<<<<< HEAD
void WalletModelTransaction::reassignAmounts(int nChangePosRet)
{
    int i = 0;
    for (QList<SendCoinsRecipient>::iterator it = recipients.begin(); it != recipients.end(); ++it)
    {
        SendCoinsRecipient& rcp = (*it);

        if (rcp.paymentRequest.IsInitialized())
        {
            CAmount subtotal = 0;
            const payments::PaymentDetails& details = rcp.paymentRequest.getDetails();
            for (int j = 0; j < details.outputs_size(); j++)
            {
                const payments::Output& out = details.outputs(j);
                if (out.amount() <= 0) continue;
                if (i == nChangePosRet)
                    i++;
                subtotal += walletTransaction->vout[i].nValue;
                i++;
            }
            rcp.amount = subtotal;
        }
        else // normal recipient (no payment request)
        {
            if (i == nChangePosRet)
                i++;
            rcp.amount = walletTransaction->vout[i].nValue;
            i++;
        }
    }
}

CAmount WalletModelTransaction::getTotalTransactionAmount()
{
    CAmount totalTransactionAmount = 0;
    Q_FOREACH(const SendCoinsRecipient &rcp, recipients)
    {
=======
CAmount WalletModelTransaction::getTotalTransactionAmount()
{
    CAmount totalTransactionAmount = 0;
    foreach (const SendCoinsRecipient& rcp, recipients) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        totalTransactionAmount += rcp.amount;
    }
    return totalTransactionAmount;
}

<<<<<<< HEAD
void WalletModelTransaction::newPossibleKeyChange(CWallet *wallet)
=======
void WalletModelTransaction::newPossibleKeyChange(CWallet* wallet)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    keyChange = new CReserveKey(wallet);
}

<<<<<<< HEAD
CReserveKey *WalletModelTransaction::getPossibleKeyChange()
=======
CReserveKey* WalletModelTransaction::getPossibleKeyChange()
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    return keyChange;
}
