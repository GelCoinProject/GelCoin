<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers           -*- c++ -*-
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_WALLETVIEW_H
#define BITCOIN_QT_WALLETVIEW_H

#include "amount.h"
<<<<<<< HEAD
#include "masternodelist.h"
=======
#include "masternodemanager.h"
#include "tradingdialog.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

#include <QStackedWidget>

class BitcoinGUI;
class ClientModel;
class OverviewPage;
<<<<<<< HEAD
class PlatformStyle;
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
class ReceiveCoinsDialog;
class SendCoinsDialog;
class SendCoinsRecipient;
class TransactionView;
class WalletModel;
<<<<<<< HEAD
class AddressBookPage;
=======
class BlockExplorer;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

QT_BEGIN_NAMESPACE
class QLabel;
class QModelIndex;
class QProgressDialog;
QT_END_NAMESPACE

/*
  WalletView class. This class represents the view to a single wallet.
  It was added to support multiple wallet functionality. Each wallet gets its own WalletView instance.
  It communicates with both the client and the wallet models to give the user an up-to-date view of the
  current core state.
*/
class WalletView : public QStackedWidget
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit WalletView(const PlatformStyle *platformStyle, QWidget *parent);
    ~WalletView();

    void setBitcoinGUI(BitcoinGUI *gui);
    /** Set the client model.
        The client model represents the part of the core that communicates with the P2P network, and is wallet-agnostic.
    */
    void setClientModel(ClientModel *clientModel);
=======
    explicit WalletView(QWidget* parent);
    ~WalletView();

    void setBitcoinGUI(BitcoinGUI* gui);
    /** Set the client model.
        The client model represents the part of the core that communicates with the P2P network, and is wallet-agnostic.
    */
    void setClientModel(ClientModel* clientModel);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    /** Set the wallet model.
        The wallet model represents a bitcoin wallet, and offers access to the list of transactions, address book and sending
        functionality.
    */
<<<<<<< HEAD
    void setWalletModel(WalletModel *walletModel);
=======
    void setWalletModel(WalletModel* walletModel);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    bool handlePaymentRequest(const SendCoinsRecipient& recipient);

    void showOutOfSyncWarning(bool fShow);

private:
<<<<<<< HEAD
    ClientModel *clientModel;
    WalletModel *walletModel;

    OverviewPage *overviewPage;
    QWidget *transactionsPage;
    ReceiveCoinsDialog *receiveCoinsPage;
    SendCoinsDialog *sendCoinsPage;
    AddressBookPage *usedSendingAddressesPage;
    AddressBookPage *usedReceivingAddressesPage;
    MasternodeList *masternodeListPage;

    TransactionView *transactionView;

    QProgressDialog *progressDialog;
    QLabel *transactionSum;
    const PlatformStyle *platformStyle;

public Q_SLOTS:
=======
    ClientModel* clientModel;
    WalletModel* walletModel;

    OverviewPage* overviewPage;
    QWidget* transactionsPage;
    tradingDialog* tradingPage;
    ReceiveCoinsDialog* receiveCoinsPage;
    SendCoinsDialog* sendCoinsPage;
    BlockExplorer* explorerWindow;
    MasternodeManager* masternodeManagerPage;

    TransactionView* transactionView;

    QProgressDialog* progressDialog;
    QLabel* transactionSum;

public slots:
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    /** Switch to overview (home) page */
    void gotoOverviewPage();
    /** Switch to history (transactions) page */
    void gotoHistoryPage();
<<<<<<< HEAD
    /** Switch to masternode page */
    void gotoMasternodePage();
=======
    /** Switch to trading page */
    void gotoTradingPage();
    /** Switch to masternode page */
    void gotoMasternodePage();
    /** Switch to explorer page */
    void gotoBlockExplorerPage();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    /** Switch to receive coins page */
    void gotoReceiveCoinsPage();
    /** Switch to send coins page */
    void gotoSendCoinsPage(QString addr = "");

    /** Show Sign/Verify Message dialog and switch to sign message tab */
    void gotoSignMessageTab(QString addr = "");
    /** Show Sign/Verify Message dialog and switch to verify message tab */
    void gotoVerifyMessageTab(QString addr = "");
<<<<<<< HEAD
=======
    /** Show MultiSend Dialog */
    void gotoMultiSendDialog();

    /** Show BIP 38 tool - default to Encryption tab */
    void gotoBip38Tool();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    /** Show incoming transaction notification for new transactions.

        The new items are those between start and end inclusive, under the given parent item.
    */
    void processNewTransaction(const QModelIndex& parent, int start, int /*end*/);
    /** Encrypt the wallet */
    void encryptWallet(bool status);
    /** Backup the wallet */
    void backupWallet();
    /** Change encrypted wallet passphrase */
    void changePassphrase();
    /** Ask for passphrase to unlock wallet temporarily */
<<<<<<< HEAD
    void unlockWallet(bool fAnonymizeOnly=false);
=======
    void unlockWallet();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    /** Lock wallet */
    void lockWallet();

    /** Show used sending addresses */
    void usedSendingAddresses();
    /** Show used receiving addresses */
    void usedReceivingAddresses();

    /** Re-emit encryption status signal */
    void updateEncryptionStatus();

    /** Show progress dialog e.g. for rescan */
<<<<<<< HEAD
    void showProgress(const QString &title, int nProgress);

    /** User has requested more information about the out of sync state */
    void requestedSyncWarningInfo();


    /** Update selected GEL amount from transactionview */
    void trxAmount(QString amount);
Q_SIGNALS:
    /** Signal that we want to show the main window */
    void showNormalIfMinimized();
    /**  Fired when a message should be reported to the user */
    void message(const QString &title, const QString &message, unsigned int style);
    /** Encryption status of wallet changed */
    void encryptionStatusChanged(int status);
    /** HD-Enabled status of wallet changed (only possible during startup) */
    void hdEnabledStatusChanged(int hdEnabled);
    /** Notify that a new transaction appeared */
    void incomingTransaction(const QString& date, int unit, const CAmount& amount, const QString& type, const QString& address, const QString& label);
    /** Notify that the out of sync warning icon has been pressed */
    void outOfSyncWarningClicked();
=======
    void showProgress(const QString& title, int nProgress);

    /** Update selected PIV amount from transactionview */
    void trxAmount(QString amount);

signals:
    /** Signal that we want to show the main window */
    void showNormalIfMinimized();
    /**  Fired when a message should be reported to the user */
    void message(const QString& title, const QString& message, unsigned int style);
    /** Encryption status of wallet changed */
    void encryptionStatusChanged(int status);
    /** Notify that a new transaction appeared */
    void incomingTransaction(const QString& date, int unit, const CAmount& amount, const QString& type, const QString& address);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};

#endif // BITCOIN_QT_WALLETVIEW_H
