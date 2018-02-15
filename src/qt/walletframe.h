<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers           -*- c++ -*-
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_WALLETFRAME_H
#define BITCOIN_QT_WALLETFRAME_H

#include <QFrame>
#include <QMap>

class BitcoinGUI;
class ClientModel;
<<<<<<< HEAD
class PlatformStyle;
class SendCoinsRecipient;
class WalletModel;
class WalletView;
=======
class SendCoinsRecipient;
class WalletModel;
class WalletView;
class TradingDialog;
class BlockExplorer;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

QT_BEGIN_NAMESPACE
class QStackedWidget;
QT_END_NAMESPACE

class WalletFrame : public QFrame
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit WalletFrame(const PlatformStyle *platformStyle, BitcoinGUI *_gui = 0);
    ~WalletFrame();

    void setClientModel(ClientModel *clientModel);

    bool addWallet(const QString& name, WalletModel *walletModel);
    bool setCurrentWallet(const QString& name);
    bool removeWallet(const QString &name);
=======
    explicit WalletFrame(BitcoinGUI* _gui = 0);
    ~WalletFrame();

    void setClientModel(ClientModel* clientModel);

    bool addWallet(const QString& name, WalletModel* walletModel);
    bool setCurrentWallet(const QString& name);
    bool removeWallet(const QString& name);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void removeAllWallets();

    bool handlePaymentRequest(const SendCoinsRecipient& recipient);

    void showOutOfSyncWarning(bool fShow);

<<<<<<< HEAD
Q_SIGNALS:
    /** Notify that the user has requested more information about the out-of-sync warning */
    void requestedSyncWarningInfo();

private:
    QStackedWidget *walletStack;
    BitcoinGUI *gui;
    ClientModel *clientModel;
=======
private:
    QStackedWidget* walletStack;
    BitcoinGUI* gui;
    ClientModel* clientModel;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    QMap<QString, WalletView*> mapWalletViews;

    bool bOutOfSync;

<<<<<<< HEAD
    const PlatformStyle *platformStyle;

    WalletView *currentWalletView();

public Q_SLOTS:
=======
    WalletView* currentWalletView();

public slots:
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    /** Switch to overview (home) page */
    void gotoOverviewPage();
    /** Switch to history (transactions) page */
    void gotoHistoryPage();
<<<<<<< HEAD
=======
    /** Switch to trading page */
    void gotoTradingPage();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    /** Switch to masternode page */
    void gotoMasternodePage();
    /** Switch to receive coins page */
    void gotoReceiveCoinsPage();
    /** Switch to send coins page */
    void gotoSendCoinsPage(QString addr = "");
<<<<<<< HEAD

=======
    /** Switch to explorer page */
    void gotoBlockExplorerPage();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    /** Show Sign/Verify Message dialog and switch to sign message tab */
    void gotoSignMessageTab(QString addr = "");
    /** Show Sign/Verify Message dialog and switch to verify message tab */
    void gotoVerifyMessageTab(QString addr = "");
<<<<<<< HEAD
=======
    /** Show MultiSend Dialog **/
    void gotoMultiSendDialog();

    /** Show BIP 38 tool - default to Encryption tab */
    void gotoBip38Tool();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    /** Encrypt the wallet */
    void encryptWallet(bool status);
    /** Backup the wallet */
    void backupWallet();
    /** Change encrypted wallet passphrase */
    void changePassphrase();
    /** Ask for passphrase to unlock wallet temporarily */
    void unlockWallet();
    /** Lock wallet */
    void lockWallet();

    /** Show used sending addresses */
    void usedSendingAddresses();
    /** Show used receiving addresses */
    void usedReceivingAddresses();
<<<<<<< HEAD
    /** Pass on signal over requested out-of-sync-warning information */
    void outOfSyncWarningClicked();
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};

#endif // BITCOIN_QT_WALLETFRAME_H
