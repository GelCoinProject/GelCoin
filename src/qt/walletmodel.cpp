<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Copyright (c) 2014-2017 The GelCoin developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The LUX developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "walletmodel.h"

#include "addresstablemodel.h"
#include "guiconstants.h"
<<<<<<< HEAD
#include "guiutil.h"
#include "paymentserver.h"
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include "recentrequeststablemodel.h"
#include "transactiontablemodel.h"

#include "base58.h"
<<<<<<< HEAD
#include "keystore.h"
#include "validation.h"
#include "net.h" // for g_connman
#include "sync.h"
#include "ui_interface.h"
#include "util.h" // for GetBoolArg
#include "wallet/wallet.h"
#include "wallet/walletdb.h" // for BackupWallet

#include "instantx.h"
#include "spork.h"
#include "privatesend-client.h"

=======
#include "db.h"
#include "keystore.h"
#include "main.h"
#include "spork.h"
#include "sync.h"
#include "ui_interface.h"
#include "wallet.h"
#include "walletdb.h" // for BackupWallet
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include <stdint.h>

#include <QDebug>
#include <QSet>
#include <QTimer>

<<<<<<< HEAD
#include <boost/foreach.hpp>

WalletModel::WalletModel(const PlatformStyle *platformStyle, CWallet *wallet, OptionsModel *optionsModel, QObject *parent) :
    QObject(parent), wallet(wallet), optionsModel(optionsModel), addressTableModel(0),
    transactionTableModel(0),
    recentRequestsTableModel(0),
    cachedBalance(0),
    cachedUnconfirmedBalance(0),
    cachedImmatureBalance(0),
    cachedAnonymizedBalance(0),
    cachedWatchOnlyBalance(0),
    cachedWatchUnconfBalance(0),
    cachedWatchImmatureBalance(0),
    cachedEncryptionStatus(Unencrypted),
    cachedNumBlocks(0),
    cachedTxLocks(0),
    cachedPrivateSendRounds(0)
=======
using namespace std;

WalletModel::WalletModel(CWallet* wallet, OptionsModel* optionsModel, QObject* parent) : QObject(parent), wallet(wallet), optionsModel(optionsModel), addressTableModel(0),
                                                                                         transactionTableModel(0),
                                                                                         recentRequestsTableModel(0),
                                                                                         cachedBalance(0), cachedUnconfirmedBalance(0), cachedImmatureBalance(0),
                                                                                         cachedEncryptionStatus(Unencrypted),
                                                                                         cachedNumBlocks(0)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    fHaveWatchOnly = wallet->HaveWatchOnly();
    fForceCheckBalanceChanged = false;

    addressTableModel = new AddressTableModel(wallet, this);
<<<<<<< HEAD
    transactionTableModel = new TransactionTableModel(platformStyle, wallet, this);
=======
    transactionTableModel = new TransactionTableModel(wallet, this);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    recentRequestsTableModel = new RecentRequestsTableModel(wallet, this);

    // This timer will be fired repeatedly to update the balance
    pollTimer = new QTimer(this);
    connect(pollTimer, SIGNAL(timeout()), this, SLOT(pollBalanceChanged()));
    pollTimer->start(MODEL_UPDATE_DELAY);

    subscribeToCoreSignals();
}

WalletModel::~WalletModel()
{
    unsubscribeFromCoreSignals();
}

<<<<<<< HEAD
CAmount WalletModel::getBalance(const CCoinControl *coinControl) const
{
    if (coinControl)
    {
        CAmount nBalance = 0;
        std::vector<COutput> vCoins;
        wallet->AvailableCoins(vCoins, true, coinControl);
        BOOST_FOREACH(const COutput& out, vCoins)
            if(out.fSpendable)
=======
CAmount WalletModel::getBalance(const CCoinControl* coinControl) const
{
    if (coinControl) {
        CAmount nBalance = 0;
        std::vector<COutput> vCoins;
        wallet->AvailableCoins(vCoins, true, coinControl);
        BOOST_FOREACH (const COutput& out, vCoins)
            if (out.fSpendable)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                nBalance += out.tx->vout[out.i].nValue;

        return nBalance;
    }

    return wallet->GetBalance();
}


CAmount WalletModel::getAnonymizedBalance() const
{
    return wallet->GetAnonymizedBalance();
}

CAmount WalletModel::getUnconfirmedBalance() const
{
    return wallet->GetUnconfirmedBalance();
}

CAmount WalletModel::getImmatureBalance() const
{
    return wallet->GetImmatureBalance();
}

bool WalletModel::haveWatchOnly() const
{
    return fHaveWatchOnly;
}

CAmount WalletModel::getWatchBalance() const
{
    return wallet->GetWatchOnlyBalance();
}

CAmount WalletModel::getWatchUnconfirmedBalance() const
{
    return wallet->GetUnconfirmedWatchOnlyBalance();
}

CAmount WalletModel::getWatchImmatureBalance() const
{
    return wallet->GetImmatureWatchOnlyBalance();
}

void WalletModel::updateStatus()
{
    EncryptionStatus newEncryptionStatus = getEncryptionStatus();

<<<<<<< HEAD
    if(cachedEncryptionStatus != newEncryptionStatus)
        Q_EMIT encryptionStatusChanged(newEncryptionStatus);
=======
    if (cachedEncryptionStatus != newEncryptionStatus)
        emit encryptionStatusChanged(newEncryptionStatus);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

void WalletModel::pollBalanceChanged()
{
    // Get required locks upfront. This avoids the GUI from getting stuck on
    // periodical polls if the core is holding the locks for a longer time -
    // for example, during a wallet rescan.
    TRY_LOCK(cs_main, lockMain);
<<<<<<< HEAD
    if(!lockMain)
        return;
    TRY_LOCK(wallet->cs_wallet, lockWallet);
    if(!lockWallet)
        return;

    if(fForceCheckBalanceChanged || chainActive.Height() != cachedNumBlocks || privateSendClient.nPrivateSendRounds != cachedPrivateSendRounds || cachedTxLocks != nCompleteTXLocks)
    {
=======
    if (!lockMain)
        return;
    TRY_LOCK(wallet->cs_wallet, lockWallet);
    if (!lockWallet)
        return;

    if (fForceCheckBalanceChanged || chainActive.Height() != cachedNumBlocks || nDarksendRounds != cachedObfuscationRounds || cachedTxLocks != nCompleteTXLocks) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        fForceCheckBalanceChanged = false;

        // Balance and number of transactions might have changed
        cachedNumBlocks = chainActive.Height();
<<<<<<< HEAD
        cachedPrivateSendRounds = privateSendClient.nPrivateSendRounds;

        checkBalanceChanged();
        if(transactionTableModel)
            transactionTableModel->updateConfirmations();
=======
        cachedObfuscationRounds = nDarksendRounds;

        checkBalanceChanged();
        if (transactionTableModel) {
            transactionTableModel->updateConfirmations();
        }
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }
}

void WalletModel::checkBalanceChanged()
{
<<<<<<< HEAD
=======
    TRY_LOCK(cs_main, lockMain);
    if (!lockMain) return;

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    CAmount newBalance = getBalance();
    CAmount newUnconfirmedBalance = getUnconfirmedBalance();
    CAmount newImmatureBalance = getImmatureBalance();
    CAmount newAnonymizedBalance = getAnonymizedBalance();
    CAmount newWatchOnlyBalance = 0;
    CAmount newWatchUnconfBalance = 0;
    CAmount newWatchImmatureBalance = 0;
<<<<<<< HEAD
    if (haveWatchOnly())
    {
=======
    if (haveWatchOnly()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        newWatchOnlyBalance = getWatchBalance();
        newWatchUnconfBalance = getWatchUnconfirmedBalance();
        newWatchImmatureBalance = getWatchImmatureBalance();
    }

<<<<<<< HEAD
    if(cachedBalance != newBalance || cachedUnconfirmedBalance != newUnconfirmedBalance || cachedImmatureBalance != newImmatureBalance ||
        cachedAnonymizedBalance != newAnonymizedBalance || cachedTxLocks != nCompleteTXLocks ||
        cachedWatchOnlyBalance != newWatchOnlyBalance || cachedWatchUnconfBalance != newWatchUnconfBalance || cachedWatchImmatureBalance != newWatchImmatureBalance)
    {
=======
    if (cachedBalance != newBalance || cachedUnconfirmedBalance != newUnconfirmedBalance || cachedImmatureBalance != newImmatureBalance ||
        cachedAnonymizedBalance != newAnonymizedBalance || cachedTxLocks != nCompleteTXLocks ||
        cachedWatchOnlyBalance != newWatchOnlyBalance || cachedWatchUnconfBalance != newWatchUnconfBalance || cachedWatchImmatureBalance != newWatchImmatureBalance) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        cachedBalance = newBalance;
        cachedUnconfirmedBalance = newUnconfirmedBalance;
        cachedImmatureBalance = newImmatureBalance;
        cachedAnonymizedBalance = newAnonymizedBalance;
        cachedTxLocks = nCompleteTXLocks;
        cachedWatchOnlyBalance = newWatchOnlyBalance;
        cachedWatchUnconfBalance = newWatchUnconfBalance;
        cachedWatchImmatureBalance = newWatchImmatureBalance;
<<<<<<< HEAD
        Q_EMIT balanceChanged(newBalance, newUnconfirmedBalance, newImmatureBalance, newAnonymizedBalance,
                            newWatchOnlyBalance, newWatchUnconfBalance, newWatchImmatureBalance);
=======
        emit balanceChanged(newBalance, newUnconfirmedBalance, newImmatureBalance, newAnonymizedBalance,
            newWatchOnlyBalance, newWatchUnconfBalance, newWatchImmatureBalance);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }
}

void WalletModel::updateTransaction()
{
    // Balance and number of transactions might have changed
    fForceCheckBalanceChanged = true;
}

<<<<<<< HEAD
void WalletModel::updateAddressBook(const QString &address, const QString &label,
        bool isMine, const QString &purpose, int status)
{
    if(addressTableModel)
=======
void WalletModel::updateAddressBook(const QString& address, const QString& label, bool isMine, const QString& purpose, int status)
{
    if (addressTableModel)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        addressTableModel->updateEntry(address, label, isMine, purpose, status);
}

void WalletModel::updateWatchOnlyFlag(bool fHaveWatchonly)
{
    fHaveWatchOnly = fHaveWatchonly;
<<<<<<< HEAD
    Q_EMIT notifyWatchonlyChanged(fHaveWatchonly);
}

bool WalletModel::validateAddress(const QString &address)
=======
    emit notifyWatchonlyChanged(fHaveWatchonly);
}

bool WalletModel::validateAddress(const QString& address)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    CBitcoinAddress addressParsed(address.toStdString());
    return addressParsed.IsValid();
}

<<<<<<< HEAD
WalletModel::SendCoinsReturn WalletModel::prepareTransaction(WalletModelTransaction &transaction, const CCoinControl *coinControl)
{
    CAmount total = 0;
    bool fSubtractFeeFromAmount = false;
    QList<SendCoinsRecipient> recipients = transaction.getRecipients();
    std::vector<CRecipient> vecSend;

    if(recipients.empty())
    {
        return OK;
    }

    // This should never really happen, yet another safety check, just in case.
    if(wallet->IsLocked()) {
        return TransactionCreationFailed;
=======
WalletModel::SendCoinsReturn WalletModel::prepareTransaction(WalletModelTransaction& transaction, const CCoinControl* coinControl)
{
    CAmount total = 0;
    QList<SendCoinsRecipient> recipients = transaction.getRecipients();
    std::vector<std::pair<CScript, CAmount> > vecSend;

    if (recipients.empty()) {
        return OK;
    }

    if (isAnonymizeOnlyUnlocked()) {
        return AnonymizeOnlyUnlocked;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }

    QSet<QString> setAddress; // Used to detect duplicates
    int nAddresses = 0;

    // Pre-check input data for validity
<<<<<<< HEAD
    Q_FOREACH(const SendCoinsRecipient &rcp, recipients)
    {
        if (rcp.fSubtractFeeFromAmount)
            fSubtractFeeFromAmount = true;

        if (rcp.paymentRequest.IsInitialized())
        {   // PaymentRequest...
            CAmount subtotal = 0;
            const payments::PaymentDetails& details = rcp.paymentRequest.getDetails();
            for (int i = 0; i < details.outputs_size(); i++)
            {
=======
    foreach (const SendCoinsRecipient& rcp, recipients) {
        if (rcp.paymentRequest.IsInitialized()) { // PaymentRequest...
            CAmount subtotal = 0;
            const payments::PaymentDetails& details = rcp.paymentRequest.getDetails();
            for (int i = 0; i < details.outputs_size(); i++) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                const payments::Output& out = details.outputs(i);
                if (out.amount() <= 0) continue;
                subtotal += out.amount();
                const unsigned char* scriptStr = (const unsigned char*)out.script().data();
<<<<<<< HEAD
                CScript scriptPubKey(scriptStr, scriptStr+out.script().size());
                CAmount nAmount = out.amount();
                CRecipient recipient = {scriptPubKey, nAmount, rcp.fSubtractFeeFromAmount};
                vecSend.push_back(recipient);
            }
            if (subtotal <= 0)
            {
                return InvalidAmount;
            }
            total += subtotal;
        }
        else
        {   // User-entered gelcoin address / amount:
            if(!validateAddress(rcp.address))
            {
                return InvalidAddress;
            }
            if(rcp.amount <= 0)
            {
=======
                CScript scriptPubKey(scriptStr, scriptStr + out.script().size());
                vecSend.push_back(std::pair<CScript, CAmount>(scriptPubKey, out.amount()));
            }
            if (subtotal <= 0) {
                return InvalidAmount;
            }
            total += subtotal;
        } else { // User-entered lux address / amount:
            if (!validateAddress(rcp.address)) {
                return InvalidAddress;
            }
            if (rcp.amount <= 0) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                return InvalidAmount;
            }
            setAddress.insert(rcp.address);
            ++nAddresses;

            CScript scriptPubKey = GetScriptForDestination(CBitcoinAddress(rcp.address.toStdString()).Get());
<<<<<<< HEAD
            CRecipient recipient = {scriptPubKey, rcp.amount, rcp.fSubtractFeeFromAmount};
            vecSend.push_back(recipient);
=======
            vecSend.push_back(std::pair<CScript, CAmount>(scriptPubKey, rcp.amount));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

            total += rcp.amount;
        }
    }
<<<<<<< HEAD
    if(setAddress.size() != nAddresses)
    {
=======
    if (setAddress.size() != nAddresses) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return DuplicateAddress;
    }

    CAmount nBalance = getBalance(coinControl);

<<<<<<< HEAD
    if(total > nBalance)
    {
=======
    if (total > nBalance) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return AmountExceedsBalance;
    }

    {
        LOCK2(cs_main, wallet->cs_wallet);

        transaction.newPossibleKeyChange(wallet);
<<<<<<< HEAD

        CAmount nFeeRequired = 0;
        int nChangePosRet = -1;
        std::string strFailReason;

        CWalletTx *newTx = transaction.getTransaction();
        CReserveKey *keyChange = transaction.getPossibleKeyChange();

        if(recipients[0].fUseInstantSend && total > sporkManager.GetSporkValue(SPORK_5_INSTANTSEND_MAX_VALUE)*COIN){
            Q_EMIT message(tr("Send Coins"), tr("InstantSend doesn't support sending values that high yet. Transactions are currently limited to %1 GEL.").arg(sporkManager.GetSporkValue(SPORK_5_INSTANTSEND_MAX_VALUE)),
                         CClientUIInterface::MSG_ERROR);
            return TransactionCreationFailed;
        }

        bool fCreated = wallet->CreateTransaction(vecSend, *newTx, *keyChange, nFeeRequired, nChangePosRet, strFailReason, coinControl, true, recipients[0].inputType, recipients[0].fUseInstantSend);
        transaction.setTransactionFee(nFeeRequired);
        if (fSubtractFeeFromAmount && fCreated)
            transaction.reassignAmounts(nChangePosRet);

        if(recipients[0].fUseInstantSend) {
            if(newTx->GetValueOut() > sporkManager.GetSporkValue(SPORK_5_INSTANTSEND_MAX_VALUE)*COIN) {
                Q_EMIT message(tr("Send Coins"), tr("InstantSend doesn't support sending values that high yet. Transactions are currently limited to %1 GEL.").arg(sporkManager.GetSporkValue(SPORK_5_INSTANTSEND_MAX_VALUE)),
                             CClientUIInterface::MSG_ERROR);
                return TransactionCreationFailed;
            }
            if(newTx->vin.size() > CTxLockRequest::WARN_MANY_INPUTS) {
                Q_EMIT message(tr("Send Coins"), tr("Used way too many inputs (>%1) for this InstantSend transaction, fees could be huge.").arg(CTxLockRequest::WARN_MANY_INPUTS),
                             CClientUIInterface::MSG_WARNING);
            }
        }

        if(!fCreated)
        {
            if(!fSubtractFeeFromAmount && (total + nFeeRequired) > nBalance)
            {
                return SendCoinsReturn(AmountWithFeeExceedsBalance);
            }
            Q_EMIT message(tr("Send Coins"), QString::fromStdString(strFailReason),
                         CClientUIInterface::MSG_ERROR);
            return TransactionCreationFailed;
        }

        // reject absurdly high fee. (This can never happen because the
        // wallet caps the fee at maxTxFee. This merely serves as a
        // belt-and-suspenders check)
        if (nFeeRequired > maxTxFee)
            return AbsurdFee;
=======
        CAmount nFeeRequired = 0;
        std::string strFailReason;

        CWalletTx* newTx = transaction.getTransaction();
        CReserveKey* keyChange = transaction.getPossibleKeyChange();


        if (recipients[0].useSwiftTX && total > GetSporkValue(SPORK_2_MAX_VALUE) * COIN) {
            emit message(tr("Send Coins"), tr("SwiftTX doesn't support sending values that high yet. Transactions are currently limited to %1 LUX.").arg(GetSporkValue(SPORK_2_MAX_VALUE)),
                CClientUIInterface::MSG_ERROR);
            return TransactionCreationFailed;
        }

        bool fCreated = wallet->CreateTransaction(vecSend, *newTx, *keyChange, nFeeRequired, strFailReason, coinControl, recipients[0].inputType, recipients[0].useSwiftTX);
        transaction.setTransactionFee(nFeeRequired);

        if (recipients[0].useSwiftTX && newTx->GetValueOut() > GetSporkValue(SPORK_2_MAX_VALUE) * COIN) {
            emit message(tr("Send Coins"), tr("SwiftTX doesn't support sending values that high yet. Transactions are currently limited to %1 LUX.").arg(GetSporkValue(SPORK_2_MAX_VALUE)),
                CClientUIInterface::MSG_ERROR);
            return TransactionCreationFailed;
        }

        if (!fCreated) {
            if ((total + nFeeRequired) > nBalance) {
                return SendCoinsReturn(AmountWithFeeExceedsBalance);
            }
            emit message(tr("Send Coins"), QString::fromStdString(strFailReason),
                CClientUIInterface::MSG_ERROR);
            return TransactionCreationFailed;
        }

        // reject insane fee
        if (nFeeRequired > ::minRelayTxFee.GetFee(transaction.getTransactionSize()) * 10000)
            return InsaneFee;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }

    return SendCoinsReturn(OK);
}

<<<<<<< HEAD
WalletModel::SendCoinsReturn WalletModel::sendCoins(WalletModelTransaction &transaction)
{
    QByteArray transaction_array; /* store serialized transaction */

    {
        LOCK2(cs_main, wallet->cs_wallet);
        CWalletTx *newTx = transaction.getTransaction();
        QList<SendCoinsRecipient> recipients = transaction.getRecipients();

        Q_FOREACH(const SendCoinsRecipient &rcp, recipients)
        {
            if (rcp.paymentRequest.IsInitialized())
            {
                // Make sure any payment requests involved are still valid.
                if (PaymentServer::verifyExpired(rcp.paymentRequest.getDetails())) {
                    return PaymentRequestExpired;
                }

                // Store PaymentRequests in wtx.vOrderForm in wallet.
=======
WalletModel::SendCoinsReturn WalletModel::sendCoins(WalletModelTransaction& transaction)
{
    QByteArray transaction_array; /* store serialized transaction */

    if (isAnonymizeOnlyUnlocked()) {
        return AnonymizeOnlyUnlocked;
    }

    {
        LOCK2(cs_main, wallet->cs_wallet);
        CWalletTx* newTx = transaction.getTransaction();
        QList<SendCoinsRecipient> recipients = transaction.getRecipients();

        // Store PaymentRequests in wtx.vOrderForm in wallet.
        foreach (const SendCoinsRecipient& rcp, recipients) {
            if (rcp.paymentRequest.IsInitialized()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                std::string key("PaymentRequest");
                std::string value;
                rcp.paymentRequest.SerializeToString(&value);
                newTx->vOrderForm.push_back(make_pair(key, value));
<<<<<<< HEAD
            }
            else if (!rcp.message.isEmpty()) // Message from normal gelcoin:URI (gelcoin:XyZ...?message=example)
=======
            } else if (!rcp.message.isEmpty()) // Message from normal lux:URI (lux:XyZ...?message=example)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            {
                newTx->vOrderForm.push_back(make_pair("Message", rcp.message.toStdString()));
            }
        }

<<<<<<< HEAD
        CReserveKey *keyChange = transaction.getPossibleKeyChange();

        if(!wallet->CommitTransaction(*newTx, *keyChange, g_connman.get(), recipients[0].fUseInstantSend ? NetMsgType::TXLOCKREQUEST : NetMsgType::TX))
=======
        CReserveKey* keyChange = transaction.getPossibleKeyChange();

        transaction.getRecipients();

        if (!wallet->CommitTransaction(*newTx, *keyChange, (recipients[0].useSwiftTX) ? "ix" : "tx"))
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            return TransactionCommitFailed;

        CTransaction* t = (CTransaction*)newTx;
        CDataStream ssTx(SER_NETWORK, PROTOCOL_VERSION);
        ssTx << *t;
        transaction_array.append(&(ssTx[0]), ssTx.size());
    }

    // Add addresses / update labels that we've sent to to the address book,
    // and emit coinsSent signal for each recipient
<<<<<<< HEAD
    Q_FOREACH(const SendCoinsRecipient &rcp, transaction.getRecipients())
    {
        // Don't touch the address book when we have a payment request
        if (!rcp.paymentRequest.IsInitialized())
        {
=======
    foreach (const SendCoinsRecipient& rcp, transaction.getRecipients()) {
        // Don't touch the address book when we have a payment request
        if (!rcp.paymentRequest.IsInitialized()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            std::string strAddress = rcp.address.toStdString();
            CTxDestination dest = CBitcoinAddress(strAddress).Get();
            std::string strLabel = rcp.label.toStdString();
            {
                LOCK(wallet->cs_wallet);

                std::map<CTxDestination, CAddressBookData>::iterator mi = wallet->mapAddressBook.find(dest);

                // Check if we have a new address or an updated label
<<<<<<< HEAD
                if (mi == wallet->mapAddressBook.end())
                {
                    wallet->SetAddressBook(dest, strLabel, "send");
                }
                else if (mi->second.name != strLabel)
                {
=======
                if (mi == wallet->mapAddressBook.end()) {
                    wallet->SetAddressBook(dest, strLabel, "send");
                } else if (mi->second.name != strLabel) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                    wallet->SetAddressBook(dest, strLabel, ""); // "" means don't change purpose
                }
            }
        }
<<<<<<< HEAD
        Q_EMIT coinsSent(wallet, rcp, transaction_array);
=======
        emit coinsSent(wallet, rcp, transaction_array);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }
    checkBalanceChanged(); // update balance immediately, otherwise there could be a short noticeable delay until pollBalanceChanged hits

    return SendCoinsReturn(OK);
}

<<<<<<< HEAD
OptionsModel *WalletModel::getOptionsModel()
=======
OptionsModel* WalletModel::getOptionsModel()
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    return optionsModel;
}

<<<<<<< HEAD
AddressTableModel *WalletModel::getAddressTableModel()
=======
AddressTableModel* WalletModel::getAddressTableModel()
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    return addressTableModel;
}

<<<<<<< HEAD
TransactionTableModel *WalletModel::getTransactionTableModel()
=======
TransactionTableModel* WalletModel::getTransactionTableModel()
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    return transactionTableModel;
}

<<<<<<< HEAD
RecentRequestsTableModel *WalletModel::getRecentRequestsTableModel()
=======
RecentRequestsTableModel* WalletModel::getRecentRequestsTableModel()
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    return recentRequestsTableModel;
}

WalletModel::EncryptionStatus WalletModel::getEncryptionStatus() const
{
<<<<<<< HEAD
    if(!wallet->IsCrypted())
    {
        return Unencrypted;
    }
    else if(wallet->IsLocked(true))
    {
        return Locked;
    }
    else if (wallet->IsLocked())
    {
        return UnlockedForMixingOnly;
    }
    else
    {
=======
    if (!wallet->IsCrypted()) {
        return Unencrypted;
    } else if (wallet->fWalletUnlockAnonymizeOnly) {
        return UnlockedForAnonymizationOnly;
    } else if (wallet->IsLocked()) {
        return Locked;
    } else {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return Unlocked;
    }
}

<<<<<<< HEAD
bool WalletModel::setWalletEncrypted(bool encrypted, const SecureString &passphrase)
{
    if(encrypted)
    {
        // Encrypt
        return wallet->EncryptWallet(passphrase);
    }
    else
    {
=======
bool WalletModel::setWalletEncrypted(bool encrypted, const SecureString& passphrase)
{
    if (encrypted) {
        // Encrypt
        return wallet->EncryptWallet(passphrase);
    } else {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        // Decrypt -- TODO; not supported yet
        return false;
    }
}

<<<<<<< HEAD
bool WalletModel::setWalletLocked(bool locked, const SecureString &passPhrase, bool fMixing)
{
    if(locked)
    {
        // Lock
        return wallet->Lock(fMixing);
    }
    else
    {
        // Unlock
        return wallet->Unlock(passPhrase, fMixing);
    }
}

bool WalletModel::changePassphrase(const SecureString &oldPass, const SecureString &newPass)
=======
bool WalletModel::setWalletLocked(bool locked, const SecureString& passPhrase, bool anonymizeOnly)
{
    if (locked) {
        // Lock
        return wallet->Lock();
    } else {
        // Unlock
        return wallet->Unlock(passPhrase, anonymizeOnly);
    }
}

bool WalletModel::isAnonymizeOnlyUnlocked()
{
    return wallet->fWalletUnlockAnonymizeOnly;
}

bool WalletModel::changePassphrase(const SecureString& oldPass, const SecureString& newPass)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    bool retval;
    {
        LOCK(wallet->cs_wallet);
        wallet->Lock(); // Make sure wallet is locked before attempting pass change
        retval = wallet->ChangeWalletPassphrase(oldPass, newPass);
    }
    return retval;
}

<<<<<<< HEAD
bool WalletModel::backupWallet(const QString &filename)
=======
bool WalletModel::backupWallet(const QString& filename)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    return BackupWallet(*wallet, filename.toLocal8Bit().data());
}

// Handlers for core signals
<<<<<<< HEAD
static void NotifyKeyStoreStatusChanged(WalletModel *walletmodel, CCryptoKeyStore *wallet)
=======
static void NotifyKeyStoreStatusChanged(WalletModel* walletmodel, CCryptoKeyStore* wallet)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    qDebug() << "NotifyKeyStoreStatusChanged";
    QMetaObject::invokeMethod(walletmodel, "updateStatus", Qt::QueuedConnection);
}

<<<<<<< HEAD
static void NotifyAddressBookChanged(WalletModel *walletmodel, CWallet *wallet,
        const CTxDestination &address, const std::string &label, bool isMine,
        const std::string &purpose, ChangeType status)
=======
static void NotifyAddressBookChanged(WalletModel* walletmodel, CWallet* wallet, const CTxDestination& address, const std::string& label, bool isMine, const std::string& purpose, ChangeType status)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    QString strAddress = QString::fromStdString(CBitcoinAddress(address).ToString());
    QString strLabel = QString::fromStdString(label);
    QString strPurpose = QString::fromStdString(purpose);

<<<<<<< HEAD
    qDebug() << "NotifyAddressBookChanged: " + strAddress + " " + strLabel + " isMine=" + QString::number(isMine) + " purpose=" + strPurpose + " status=" + QString::number(status);
    QMetaObject::invokeMethod(walletmodel, "updateAddressBook", Qt::QueuedConnection,
                              Q_ARG(QString, strAddress),
                              Q_ARG(QString, strLabel),
                              Q_ARG(bool, isMine),
                              Q_ARG(QString, strPurpose),
                              Q_ARG(int, status));
}

static void NotifyTransactionChanged(WalletModel *walletmodel, CWallet *wallet, const uint256 &hash, ChangeType status)
{
    Q_UNUSED(wallet);
    Q_UNUSED(hash);
    Q_UNUSED(status);
    QMetaObject::invokeMethod(walletmodel, "updateTransaction", Qt::QueuedConnection);
}

static void ShowProgress(WalletModel *walletmodel, const std::string &title, int nProgress)
{
    // emits signal "showProgress"
    QMetaObject::invokeMethod(walletmodel, "showProgress", Qt::QueuedConnection,
                              Q_ARG(QString, QString::fromStdString(title)),
                              Q_ARG(int, nProgress));
}

static void NotifyWatchonlyChanged(WalletModel *walletmodel, bool fHaveWatchonly)
{
    QMetaObject::invokeMethod(walletmodel, "updateWatchOnlyFlag", Qt::QueuedConnection,
                              Q_ARG(bool, fHaveWatchonly));
=======
    qDebug() << "NotifyAddressBookChanged : " + strAddress + " " + strLabel + " isMine=" + QString::number(isMine) + " purpose=" + strPurpose + " status=" + QString::number(status);
    QMetaObject::invokeMethod(walletmodel, "updateAddressBook", Qt::QueuedConnection,
        Q_ARG(QString, strAddress),
        Q_ARG(QString, strLabel),
        Q_ARG(bool, isMine),
        Q_ARG(QString, strPurpose),
        Q_ARG(int, status));
}

// queue notifications to show a non freezing progress dialog e.g. for rescan
static bool fQueueNotifications = false;
static std::vector<std::pair<uint256, ChangeType> > vQueueNotifications;
static void NotifyTransactionChanged(WalletModel* walletmodel, CWallet* wallet, const uint256& hash, ChangeType status)
{
    if (fQueueNotifications) {
        vQueueNotifications.push_back(make_pair(hash, status));
        return;
    }

    QString strHash = QString::fromStdString(hash.GetHex());

    qDebug() << "NotifyTransactionChanged : " + strHash + " status= " + QString::number(status);
    QMetaObject::invokeMethod(walletmodel, "updateTransaction", Qt::QueuedConnection /*,
                              Q_ARG(QString, strHash),
                              Q_ARG(int, status)*/);
}

static void ShowProgress(WalletModel* walletmodel, const std::string& title, int nProgress)
{
    // emits signal "showProgress"
    QMetaObject::invokeMethod(walletmodel, "showProgress", Qt::QueuedConnection,
        Q_ARG(QString, QString::fromStdString(title)),
        Q_ARG(int, nProgress));
}

static void NotifyWatchonlyChanged(WalletModel* walletmodel, bool fHaveWatchonly)
{
    QMetaObject::invokeMethod(walletmodel, "updateWatchOnlyFlag", Qt::QueuedConnection,
        Q_ARG(bool, fHaveWatchonly));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

void WalletModel::subscribeToCoreSignals()
{
    // Connect signals to wallet
    wallet->NotifyStatusChanged.connect(boost::bind(&NotifyKeyStoreStatusChanged, this, _1));
    wallet->NotifyAddressBookChanged.connect(boost::bind(NotifyAddressBookChanged, this, _1, _2, _3, _4, _5, _6));
    wallet->NotifyTransactionChanged.connect(boost::bind(NotifyTransactionChanged, this, _1, _2, _3));
    wallet->ShowProgress.connect(boost::bind(ShowProgress, this, _1, _2));
    wallet->NotifyWatchonlyChanged.connect(boost::bind(NotifyWatchonlyChanged, this, _1));
}

void WalletModel::unsubscribeFromCoreSignals()
{
    // Disconnect signals from wallet
    wallet->NotifyStatusChanged.disconnect(boost::bind(&NotifyKeyStoreStatusChanged, this, _1));
    wallet->NotifyAddressBookChanged.disconnect(boost::bind(NotifyAddressBookChanged, this, _1, _2, _3, _4, _5, _6));
    wallet->NotifyTransactionChanged.disconnect(boost::bind(NotifyTransactionChanged, this, _1, _2, _3));
    wallet->ShowProgress.disconnect(boost::bind(ShowProgress, this, _1, _2));
    wallet->NotifyWatchonlyChanged.disconnect(boost::bind(NotifyWatchonlyChanged, this, _1));
}

// WalletModel::UnlockContext implementation
<<<<<<< HEAD
WalletModel::UnlockContext WalletModel::requestUnlock(bool fForMixingOnly)
{
    EncryptionStatus encStatusOld = getEncryptionStatus();

    // Wallet was completely locked
    bool was_locked = (encStatusOld == Locked);
    // Wallet was unlocked for mixing
    bool was_mixing = (encStatusOld == UnlockedForMixingOnly);
    // Wallet was unlocked for mixing and now user requested to fully unlock it
    bool fMixingToFullRequested = !fForMixingOnly && was_mixing;

    if(was_locked || fMixingToFullRequested) {
        // Request UI to unlock wallet
        Q_EMIT requireUnlock(fForMixingOnly);
    }

    EncryptionStatus encStatusNew = getEncryptionStatus();

    // Wallet was locked, user requested to unlock it for mixing and failed to do so
    bool fMixingUnlockFailed = fForMixingOnly && !(encStatusNew == UnlockedForMixingOnly);
    // Wallet was unlocked for mixing, user requested to fully unlock it and failed
    bool fMixingToFullFailed = fMixingToFullRequested && !(encStatusNew == Unlocked);
    // If wallet is still locked, unlock failed or was cancelled, mark context as invalid
    bool fInvalid = (encStatusNew == Locked) || fMixingUnlockFailed || fMixingToFullFailed;
    // Wallet was not locked in any way or user tried to unlock it for mixing only and succeeded, keep it unlocked
    bool fKeepUnlocked = !was_locked || (fForMixingOnly && !fMixingUnlockFailed);

    return UnlockContext(this, !fInvalid, !fKeepUnlocked, was_mixing);
}

WalletModel::UnlockContext::UnlockContext(WalletModel *wallet, bool valid, bool was_locked, bool was_mixing):
        wallet(wallet),
        valid(valid),
        was_locked(was_locked),
        was_mixing(was_mixing)
=======
WalletModel::UnlockContext WalletModel::requestUnlock(bool relock)
{
    bool was_locked = getEncryptionStatus() == Locked;

    if (!was_locked && isAnonymizeOnlyUnlocked()) {
        setWalletLocked(true);
        wallet->fWalletUnlockAnonymizeOnly = false;
        was_locked = getEncryptionStatus() == Locked;
    }

    if (was_locked) {
        // Request UI to unlock wallet
        emit requireUnlock();
    }
    // If wallet is still locked, unlock was failed or cancelled, mark context as invalid
    bool valid = getEncryptionStatus() != Locked;

    return UnlockContext(this, valid, relock);
    //    return UnlockContext(this, valid, was_locked && !isAnonymizeOnlyUnlocked());
}

WalletModel::UnlockContext::UnlockContext(WalletModel* wallet, bool valid, bool relock) : wallet(wallet),
                                                                                          valid(valid),
                                                                                          relock(relock)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
}

WalletModel::UnlockContext::~UnlockContext()
{
<<<<<<< HEAD
    if(valid && (was_locked || was_mixing))
    {
        wallet->setWalletLocked(true, "", was_mixing);
    }
=======

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

void WalletModel::UnlockContext::CopyFrom(const UnlockContext& rhs)
{
    // Transfer context; old object no longer relocks wallet
    *this = rhs;
<<<<<<< HEAD
    rhs.was_locked = false;
    rhs.was_mixing = false;
}

bool WalletModel::getPubKey(const CKeyID &address, CPubKey& vchPubKeyOut) const
=======
    rhs.relock = false;
}

bool WalletModel::getPubKey(const CKeyID& address, CPubKey& vchPubKeyOut) const
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    return wallet->GetPubKey(address, vchPubKeyOut);
}

<<<<<<< HEAD
bool WalletModel::havePrivKey(const CKeyID &address) const
{
    return wallet->HaveKey(address);
}

=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// returns a list of COutputs from COutPoints
void WalletModel::getOutputs(const std::vector<COutPoint>& vOutpoints, std::vector<COutput>& vOutputs)
{
    LOCK2(cs_main, wallet->cs_wallet);
<<<<<<< HEAD
    BOOST_FOREACH(const COutPoint& outpoint, vOutpoints)
    {
        if (!wallet->mapWallet.count(outpoint.hash)) continue;
        int nDepth = wallet->mapWallet[outpoint.hash].GetDepthInMainChain();
        if (nDepth < 0) continue;
        COutput out(&wallet->mapWallet[outpoint.hash], outpoint.n, nDepth, true, true);
=======
    BOOST_FOREACH (const COutPoint& outpoint, vOutpoints) {
        if (!wallet->mapWallet.count(outpoint.hash)) continue;
        int nDepth = wallet->mapWallet[outpoint.hash].GetDepthInMainChain();
        if (nDepth < 0) continue;
        COutput out(&wallet->mapWallet[outpoint.hash], outpoint.n, nDepth, true);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        vOutputs.push_back(out);
    }
}

bool WalletModel::isSpent(const COutPoint& outpoint) const
{
    LOCK2(cs_main, wallet->cs_wallet);
    return wallet->IsSpent(outpoint.hash, outpoint.n);
}

// AvailableCoins + LockedCoins grouped by wallet address (put change in one group with wallet address)
void WalletModel::listCoins(std::map<QString, std::vector<COutput> >& mapCoins) const
{
    std::vector<COutput> vCoins;
    wallet->AvailableCoins(vCoins);

    LOCK2(cs_main, wallet->cs_wallet); // ListLockedCoins, mapWallet
    std::vector<COutPoint> vLockedCoins;
    wallet->ListLockedCoins(vLockedCoins);

    // add locked coins
<<<<<<< HEAD
    BOOST_FOREACH(const COutPoint& outpoint, vLockedCoins)
    {
        if (!wallet->mapWallet.count(outpoint.hash)) continue;
        int nDepth = wallet->mapWallet[outpoint.hash].GetDepthInMainChain();
        if (nDepth < 0) continue;
        COutput out(&wallet->mapWallet[outpoint.hash], outpoint.n, nDepth, true, true);
=======
    BOOST_FOREACH (const COutPoint& outpoint, vLockedCoins) {
        if (!wallet->mapWallet.count(outpoint.hash)) continue;
        int nDepth = wallet->mapWallet[outpoint.hash].GetDepthInMainChain();
        if (nDepth < 0) continue;
        COutput out(&wallet->mapWallet[outpoint.hash], outpoint.n, nDepth, true);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        if (outpoint.n < out.tx->vout.size() && wallet->IsMine(out.tx->vout[outpoint.n]) == ISMINE_SPENDABLE)
            vCoins.push_back(out);
    }

<<<<<<< HEAD
    BOOST_FOREACH(const COutput& out, vCoins)
    {
        COutput cout = out;

        while (wallet->IsChange(cout.tx->vout[cout.i]) && cout.tx->vin.size() > 0 && wallet->IsMine(cout.tx->vin[0]))
        {
            if (!wallet->mapWallet.count(cout.tx->vin[0].prevout.hash)) break;
            cout = COutput(&wallet->mapWallet[cout.tx->vin[0].prevout.hash], cout.tx->vin[0].prevout.n, 0, true, true);
        }

        CTxDestination address;
        if(!out.fSpendable || !ExtractDestination(cout.tx->vout[cout.i].scriptPubKey, address))
=======
    BOOST_FOREACH (const COutput& out, vCoins) {
        COutput cout = out;

        while (wallet->IsChange(cout.tx->vout[cout.i]) && cout.tx->vin.size() > 0 && wallet->IsMine(cout.tx->vin[0])) {
            if (!wallet->mapWallet.count(cout.tx->vin[0].prevout.hash)) break;
            cout = COutput(&wallet->mapWallet[cout.tx->vin[0].prevout.hash], cout.tx->vin[0].prevout.n, 0, true);
        }

        CTxDestination address;
        if (!out.fSpendable || !ExtractDestination(cout.tx->vout[cout.i].scriptPubKey, address))
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            continue;
        mapCoins[QString::fromStdString(CBitcoinAddress(address).ToString())].push_back(out);
    }
}

bool WalletModel::isLockedCoin(uint256 hash, unsigned int n) const
{
    LOCK2(cs_main, wallet->cs_wallet);
    return wallet->IsLockedCoin(hash, n);
}

void WalletModel::lockCoin(COutPoint& output)
{
    LOCK2(cs_main, wallet->cs_wallet);
    wallet->LockCoin(output);
}

void WalletModel::unlockCoin(COutPoint& output)
{
    LOCK2(cs_main, wallet->cs_wallet);
    wallet->UnlockCoin(output);
}

void WalletModel::listLockedCoins(std::vector<COutPoint>& vOutpts)
{
    LOCK2(cs_main, wallet->cs_wallet);
    wallet->ListLockedCoins(vOutpts);
}

void WalletModel::loadReceiveRequests(std::vector<std::string>& vReceiveRequests)
{
    LOCK(wallet->cs_wallet);
<<<<<<< HEAD
    BOOST_FOREACH(const PAIRTYPE(CTxDestination, CAddressBookData)& item, wallet->mapAddressBook)
        BOOST_FOREACH(const PAIRTYPE(std::string, std::string)& item2, item.second.destdata)
            if (item2.first.size() > 2 && item2.first.substr(0,2) == "rr") // receive request
                vReceiveRequests.push_back(item2.second);
}

bool WalletModel::saveReceiveRequest(const std::string &sAddress, const int64_t nId, const std::string &sRequest)
=======
    BOOST_FOREACH (const PAIRTYPE(CTxDestination, CAddressBookData) & item, wallet->mapAddressBook)
        BOOST_FOREACH (const PAIRTYPE(std::string, std::string) & item2, item.second.destdata)
            if (item2.first.size() > 2 && item2.first.substr(0, 2) == "rr") // receive request
                vReceiveRequests.push_back(item2.second);
}

bool WalletModel::saveReceiveRequest(const std::string& sAddress, const int64_t nId, const std::string& sRequest)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    CTxDestination dest = CBitcoinAddress(sAddress).Get();

    std::stringstream ss;
    ss << nId;
    std::string key = "rr" + ss.str(); // "rr" prefix = "receive request" in destdata

    LOCK(wallet->cs_wallet);
    if (sRequest.empty())
        return wallet->EraseDestData(dest, key);
    else
        return wallet->AddDestData(dest, key, sRequest);
}

<<<<<<< HEAD
bool WalletModel::transactionCanBeAbandoned(uint256 hash) const
{
    LOCK2(cs_main, wallet->cs_wallet);
    const CWalletTx *wtx = wallet->GetWalletTx(hash);
    if (!wtx || wtx->isAbandoned() || wtx->GetDepthInMainChain() > 0 || wtx->InMempool())
        return false;
    return true;
}

bool WalletModel::abandonTransaction(uint256 hash) const
{
    LOCK2(cs_main, wallet->cs_wallet);
    return wallet->AbandonTransaction(hash);
}

bool WalletModel::hdEnabled() const
{
    return wallet->IsHDEnabled();
=======
bool WalletModel::isMine(CBitcoinAddress address)
{
    return IsMine(*wallet, address.Get());
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}
