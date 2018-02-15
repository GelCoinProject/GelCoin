<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "walletframe.h"

#include "bitcoingui.h"
#include "walletview.h"

#include <cstdio>

#include <QHBoxLayout>
#include <QLabel>

<<<<<<< HEAD
WalletFrame::WalletFrame(const PlatformStyle *platformStyle, BitcoinGUI *_gui) :
    QFrame(_gui),
    gui(_gui),
    platformStyle(platformStyle)
{
    // Leave HBox hook for adding a list view later
    QHBoxLayout *walletFrameLayout = new QHBoxLayout(this);
    setContentsMargins(0,0,0,0);
    walletStack = new QStackedWidget(this);
    walletFrameLayout->setContentsMargins(0,0,0,0);
    walletFrameLayout->addWidget(walletStack);

    QLabel *noWallet = new QLabel(tr("No wallet has been loaded."));
=======
WalletFrame::WalletFrame(BitcoinGUI* _gui) : QFrame(_gui),
                                             gui(_gui)
{
    // Leave HBox hook for adding a list view later
    QHBoxLayout* walletFrameLayout = new QHBoxLayout(this);
    setContentsMargins(0, 0, 0, 0);
    walletStack = new QStackedWidget(this);
    walletFrameLayout->setContentsMargins(0, 0, 0, 0);
    walletFrameLayout->addWidget(walletStack);

    QLabel* noWallet = new QLabel(tr("No wallet has been loaded."));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    noWallet->setAlignment(Qt::AlignCenter);
    walletStack->addWidget(noWallet);
}

WalletFrame::~WalletFrame()
{
}

<<<<<<< HEAD
void WalletFrame::setClientModel(ClientModel *clientModel)
=======
void WalletFrame::setClientModel(ClientModel* clientModel)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    this->clientModel = clientModel;
}

<<<<<<< HEAD
bool WalletFrame::addWallet(const QString& name, WalletModel *walletModel)
=======
bool WalletFrame::addWallet(const QString& name, WalletModel* walletModel)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    if (!gui || !clientModel || !walletModel || mapWalletViews.count(name) > 0)
        return false;

<<<<<<< HEAD
    WalletView *walletView = new WalletView(platformStyle, this);
=======
    WalletView* walletView = new WalletView(this);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    walletView->setBitcoinGUI(gui);
    walletView->setClientModel(clientModel);
    walletView->setWalletModel(walletModel);
    walletView->showOutOfSyncWarning(bOutOfSync);

<<<<<<< HEAD
     /* TODO we should goto the currently selected page once dynamically adding wallets is supported */
=======
    /* TODO we should goto the currently selected page once dynamically adding wallets is supported */
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    walletView->gotoOverviewPage();
    walletStack->addWidget(walletView);
    mapWalletViews[name] = walletView;

    // Ensure a walletView is able to show the main window
    connect(walletView, SIGNAL(showNormalIfMinimized()), gui, SLOT(showNormalIfMinimized()));

<<<<<<< HEAD
    connect(walletView, SIGNAL(outOfSyncWarningClicked()), this, SLOT(outOfSyncWarningClicked()));

=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    return true;
}

bool WalletFrame::setCurrentWallet(const QString& name)
{
    if (mapWalletViews.count(name) == 0)
        return false;

<<<<<<< HEAD
    WalletView *walletView = mapWalletViews.value(name);
=======
    WalletView* walletView = mapWalletViews.value(name);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    walletStack->setCurrentWidget(walletView);
    walletView->updateEncryptionStatus();
    return true;
}

<<<<<<< HEAD
bool WalletFrame::removeWallet(const QString &name)
=======
bool WalletFrame::removeWallet(const QString& name)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    if (mapWalletViews.count(name) == 0)
        return false;

<<<<<<< HEAD
    WalletView *walletView = mapWalletViews.take(name);
=======
    WalletView* walletView = mapWalletViews.take(name);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    walletStack->removeWidget(walletView);
    return true;
}

void WalletFrame::removeAllWallets()
{
    QMap<QString, WalletView*>::const_iterator i;
    for (i = mapWalletViews.constBegin(); i != mapWalletViews.constEnd(); ++i)
        walletStack->removeWidget(i.value());
    mapWalletViews.clear();
}

<<<<<<< HEAD
bool WalletFrame::handlePaymentRequest(const SendCoinsRecipient &recipient)
{
    WalletView *walletView = currentWalletView();
=======
bool WalletFrame::handlePaymentRequest(const SendCoinsRecipient& recipient)
{
    WalletView* walletView = currentWalletView();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    if (!walletView)
        return false;

    return walletView->handlePaymentRequest(recipient);
}

void WalletFrame::showOutOfSyncWarning(bool fShow)
{
    bOutOfSync = fShow;
    QMap<QString, WalletView*>::const_iterator i;
    for (i = mapWalletViews.constBegin(); i != mapWalletViews.constEnd(); ++i)
        i.value()->showOutOfSyncWarning(fShow);
}

void WalletFrame::gotoOverviewPage()
{
    QMap<QString, WalletView*>::const_iterator i;
    for (i = mapWalletViews.constBegin(); i != mapWalletViews.constEnd(); ++i)
        i.value()->gotoOverviewPage();
}

void WalletFrame::gotoHistoryPage()
{
    QMap<QString, WalletView*>::const_iterator i;
    for (i = mapWalletViews.constBegin(); i != mapWalletViews.constEnd(); ++i)
        i.value()->gotoHistoryPage();
}

<<<<<<< HEAD
void WalletFrame::gotoMasternodePage()
=======
void WalletFrame::gotoTradingPage()
{
    QMap<QString, WalletView*>::const_iterator i;
    for (i = mapWalletViews.constBegin(); i != mapWalletViews.constEnd(); ++i)
        i.value()->gotoTradingPage();
}

void WalletFrame::gotoMasternodePage() // Masternode list
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    QMap<QString, WalletView*>::const_iterator i;
    for (i = mapWalletViews.constBegin(); i != mapWalletViews.constEnd(); ++i)
        i.value()->gotoMasternodePage();
}

<<<<<<< HEAD
=======
void WalletFrame::gotoBlockExplorerPage()
{
    QMap<QString, WalletView*>::const_iterator i;
    for (i = mapWalletViews.constBegin(); i != mapWalletViews.constEnd(); ++i)
        i.value()->gotoBlockExplorerPage();
}

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
void WalletFrame::gotoReceiveCoinsPage()
{
    QMap<QString, WalletView*>::const_iterator i;
    for (i = mapWalletViews.constBegin(); i != mapWalletViews.constEnd(); ++i)
        i.value()->gotoReceiveCoinsPage();
}

void WalletFrame::gotoSendCoinsPage(QString addr)
{
    QMap<QString, WalletView*>::const_iterator i;
    for (i = mapWalletViews.constBegin(); i != mapWalletViews.constEnd(); ++i)
        i.value()->gotoSendCoinsPage(addr);
}

void WalletFrame::gotoSignMessageTab(QString addr)
{
<<<<<<< HEAD
    WalletView *walletView = currentWalletView();
=======
    WalletView* walletView = currentWalletView();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    if (walletView)
        walletView->gotoSignMessageTab(addr);
}

void WalletFrame::gotoVerifyMessageTab(QString addr)
{
<<<<<<< HEAD
    WalletView *walletView = currentWalletView();
=======
    WalletView* walletView = currentWalletView();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    if (walletView)
        walletView->gotoVerifyMessageTab(addr);
}

<<<<<<< HEAD
void WalletFrame::encryptWallet(bool status)
{
    WalletView *walletView = currentWalletView();
=======
void WalletFrame::gotoBip38Tool()
{
    WalletView* walletView = currentWalletView();
    if (walletView)
        walletView->gotoBip38Tool();
}

void WalletFrame::gotoMultiSendDialog()
{
    WalletView* walletView = currentWalletView();

    if (walletView)
        walletView->gotoMultiSendDialog();
}


void WalletFrame::encryptWallet(bool status)
{
    WalletView* walletView = currentWalletView();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    if (walletView)
        walletView->encryptWallet(status);
}

void WalletFrame::backupWallet()
{
<<<<<<< HEAD
    WalletView *walletView = currentWalletView();
=======
    WalletView* walletView = currentWalletView();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    if (walletView)
        walletView->backupWallet();
}

void WalletFrame::changePassphrase()
{
<<<<<<< HEAD
    WalletView *walletView = currentWalletView();
=======
    WalletView* walletView = currentWalletView();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    if (walletView)
        walletView->changePassphrase();
}

void WalletFrame::unlockWallet()
{
<<<<<<< HEAD
    WalletView *walletView = currentWalletView();
=======
    WalletView* walletView = currentWalletView();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    if (walletView)
        walletView->unlockWallet();
}

void WalletFrame::lockWallet()
{
<<<<<<< HEAD
    WalletView *walletView = currentWalletView();
=======
    WalletView* walletView = currentWalletView();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    if (walletView)
        walletView->lockWallet();
}

void WalletFrame::usedSendingAddresses()
{
<<<<<<< HEAD
    WalletView *walletView = currentWalletView();
=======
    WalletView* walletView = currentWalletView();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    if (walletView)
        walletView->usedSendingAddresses();
}

void WalletFrame::usedReceivingAddresses()
{
<<<<<<< HEAD
    WalletView *walletView = currentWalletView();
=======
    WalletView* walletView = currentWalletView();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    if (walletView)
        walletView->usedReceivingAddresses();
}

<<<<<<< HEAD
WalletView *WalletFrame::currentWalletView()
{
    return qobject_cast<WalletView*>(walletStack->currentWidget());
}

void WalletFrame::outOfSyncWarningClicked()
{
    Q_EMIT requestedSyncWarningInfo();
}
=======
WalletView* WalletFrame::currentWalletView()
{
    return qobject_cast<WalletView*>(walletStack->currentWidget());
}
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
