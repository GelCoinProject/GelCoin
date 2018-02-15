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

#include "bitcoingui.h"

#include "bitcoinunits.h"
#include "clientmodel.h"
#include "guiconstants.h"
#include "guiutil.h"
<<<<<<< HEAD
#include "modaloverlay.h"
=======
#include "miner.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include "networkstyle.h"
#include "notificator.h"
#include "openuridialog.h"
#include "optionsdialog.h"
#include "optionsmodel.h"
<<<<<<< HEAD
#include "platformstyle.h"
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include "rpcconsole.h"
#include "utilitydialog.h"

#ifdef ENABLE_WALLET
<<<<<<< HEAD
=======
#include "blockexplorer.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include "walletframe.h"
#include "walletmodel.h"
#endif // ENABLE_WALLET

#ifdef Q_OS_MAC
#include "macdockiconhandler.h"
#endif

<<<<<<< HEAD
#include "chainparams.h"
#include "init.h"
#include "ui_interface.h"
#include "util.h"
#include "masternode-sync.h"
#include "masternodelist.h"
=======
#include "init.h"
#include "masternodemanager.h"
#include "ui_interface.h"
#include "util.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

#include <iostream>

#include <QAction>
#include <QApplication>
#include <QDateTime>
#include <QDesktopWidget>
#include <QDragEnterEvent>
<<<<<<< HEAD
=======
#include <QIcon>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include <QListWidget>
#include <QMenuBar>
#include <QMessageBox>
#include <QMimeData>
<<<<<<< HEAD
#include <QProgressDialog>
#include <QSettings>
#include <QShortcut>
=======
#include <QProgressBar>
#include <QProgressDialog>
#include <QSettings>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include <QStackedWidget>
#include <QStatusBar>
#include <QStyle>
#include <QTimer>
#include <QToolBar>
#include <QVBoxLayout>

#if QT_VERSION < 0x050000
#include <QTextDocument>
#include <QUrl>
#else
#include <QUrlQuery>
#endif

<<<<<<< HEAD
const std::string BitcoinGUI::DEFAULT_UIPLATFORM =
#if defined(Q_OS_MAC)
        "macosx"
#elif defined(Q_OS_WIN)
        "windows"
#else
        "other"
#endif
        ;

const QString BitcoinGUI::DEFAULT_WALLET = "~Default";

BitcoinGUI::BitcoinGUI(const PlatformStyle *platformStyle, const NetworkStyle *networkStyle, QWidget *parent) :
    QMainWindow(parent),
    clientModel(0),
    walletFrame(0),
    unitDisplayControl(0),
    labelEncryptionIcon(0),
    labelWalletHDStatusIcon(0),
    labelConnectionsIcon(0),
    labelBlocksIcon(0),
    progressBarLabel(0),
    progressBar(0),
    progressDialog(0),
    appMenuBar(0),
    overviewAction(0),
    historyAction(0),
    masternodeAction(0),
    quitAction(0),
    sendCoinsAction(0),
    sendCoinsMenuAction(0),
    usedSendingAddressesAction(0),
    usedReceivingAddressesAction(0),
    signMessageAction(0),
    verifyMessageAction(0),
    aboutAction(0),
    receiveCoinsAction(0),
    receiveCoinsMenuAction(0),
    optionsAction(0),
    toggleHideAction(0),
    encryptWalletAction(0),
    backupWalletAction(0),
    changePassphraseAction(0),
    aboutQtAction(0),
    openRPCConsoleAction(0),
    openAction(0),
    showHelpMessageAction(0),
    showPrivateSendHelpAction(0),
    trayIcon(0),
    trayIconMenu(0),
    dockIconMenu(0),
    notificator(0),
    rpcConsole(0),
    helpMessageDialog(0),
    modalOverlay(0),
    prevBlocks(0),
    spinnerFrame(0),
    platformStyle(platformStyle)
=======
const QString BitcoinGUI::DEFAULT_WALLET = "~Default";

BitcoinGUI::BitcoinGUI(const NetworkStyle* networkStyle, QWidget* parent) : QMainWindow(parent),
                                                                            clientModel(0),
                                                                            walletFrame(0),
                                                                            unitDisplayControl(0),
                                                                            labelStakingIcon(0),
                                                                            labelEncryptionIcon(0),
                                                                            labelConnectionsIcon(0),
                                                                            labelBlocksIcon(0),
                                                                            progressBarLabel(0),
                                                                            progressBar(0),
                                                                            progressDialog(0),
                                                                            appMenuBar(0),
                                                                            overviewAction(0),
                                                                            historyAction(0),
                                                                            tradingAction(0),
                                                                            masternodeAction(0),
                                                                            quitAction(0),
                                                                            sendCoinsAction(0),
                                                                            usedSendingAddressesAction(0),
                                                                            usedReceivingAddressesAction(0),
                                                                            signMessageAction(0),
                                                                            verifyMessageAction(0),
                                                                            bip38ToolAction(0),
                                                                            aboutAction(0),
                                                                            receiveCoinsAction(0),
                                                                            optionsAction(0),
                                                                            toggleHideAction(0),
                                                                            encryptWalletAction(0),
                                                                            backupWalletAction(0),
                                                                            changePassphraseAction(0),
                                                                            aboutQtAction(0),
                                                                            openRPCConsoleAction(0),
                                                                            openAction(0),
                                                                            showHelpMessageAction(0),
                                                                            multiSendAction(0),
                                                                            trayIcon(0),
                                                                            trayIconMenu(0),
                                                                            notificator(0),
                                                                            rpcConsole(0),
                                                                            explorerWindow(0),
                                                                            prevBlocks(0),
                                                                            spinnerFrame(0)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    /* Open CSS when configured */
    this->setStyleSheet(GUIUtil::loadStyleSheet());

    GUIUtil::restoreWindowGeometry("nWindow", QSize(850, 550), this);

<<<<<<< HEAD
    QString windowTitle = tr("GelCoin") + " - ";
=======
    QString windowTitle = tr("LUX Core") + " - ";
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#ifdef ENABLE_WALLET
    /* if compiled with wallet support, -disablewallet can still disable the wallet */
    enableWallet = !GetBoolArg("-disablewallet", false);
#else
    enableWallet = false;
#endif // ENABLE_WALLET
<<<<<<< HEAD
    if(enableWallet)
    {
=======
    if (enableWallet) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        windowTitle += tr("Wallet");
    } else {
        windowTitle += tr("Node");
    }
    QString userWindowTitle = QString::fromStdString(GetArg("-windowtitle", ""));
<<<<<<< HEAD
    if(!userWindowTitle.isEmpty()) windowTitle += " - " + userWindowTitle;
    windowTitle += " " + networkStyle->getTitleAddText();
#ifndef Q_OS_MAC
    QApplication::setWindowIcon(networkStyle->getTrayAndWindowIcon());
    setWindowIcon(networkStyle->getTrayAndWindowIcon());
=======
    if (!userWindowTitle.isEmpty()) windowTitle += " - " + userWindowTitle;
    windowTitle += " " + networkStyle->getTitleAddText();
#ifndef Q_OS_MAC
    QApplication::setWindowIcon(networkStyle->getAppIcon());
    setWindowIcon(networkStyle->getAppIcon());
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#else
    MacDockIconHandler::instance()->setIcon(networkStyle->getAppIcon());
#endif
    setWindowTitle(windowTitle);

#if defined(Q_OS_MAC) && QT_VERSION < 0x050000
    // This property is not implemented in Qt 5. Setting it has no effect.
    // A replacement API (QtMacUnifiedToolBar) is available in QtMacExtras.
    setUnifiedTitleAndToolBarOnMac(true);
#endif

<<<<<<< HEAD
    rpcConsole = new RPCConsole(platformStyle, 0);
    helpMessageDialog = new HelpMessageDialog(this, HelpMessageDialog::cmdline);
#ifdef ENABLE_WALLET
    if(enableWallet)
    {
        /** Create wallet frame*/
        walletFrame = new WalletFrame(platformStyle, this);
=======
    rpcConsole = new RPCConsole(enableWallet ? this : 0);
#ifdef ENABLE_WALLET
    if (enableWallet) {
        /** Create wallet frame*/
        walletFrame = new WalletFrame(this);
        explorerWindow = new BlockExplorer(this);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    } else
#endif // ENABLE_WALLET
    {
        /* When compiled without wallet or -disablewallet is provided,
         * the central widget is the rpc console.
         */
        setCentralWidget(rpcConsole);
    }

    // Accept D&D of URIs
    setAcceptDrops(true);

    // Create actions for the toolbar, menu bar and tray/dock icon
    // Needs walletFrame to be initialized
<<<<<<< HEAD
    createActions();
=======
    createActions(networkStyle);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    // Create application menu bar
    createMenuBar();

    // Create the toolbars
    createToolBars();

    // Create system tray icon and notification
    createTrayIcon(networkStyle);

    // Create status bar
    statusBar();

<<<<<<< HEAD
    // Disable size grip because it looks ugly and nobody needs it
    statusBar()->setSizeGripEnabled(false);

    // Status bar notification icons
    QFrame *frameBlocks = new QFrame();
    frameBlocks->setContentsMargins(0,0,0,0);
    frameBlocks->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    QHBoxLayout *frameBlocksLayout = new QHBoxLayout(frameBlocks);
    frameBlocksLayout->setContentsMargins(3,0,3,0);
    frameBlocksLayout->setSpacing(3);
    unitDisplayControl = new UnitDisplayStatusBarControl(platformStyle);
    labelEncryptionIcon = new QLabel();
    labelWalletHDStatusIcon = new QLabel();
    labelConnectionsIcon = new GUIUtil::ClickableLabel();

    labelBlocksIcon = new GUIUtil::ClickableLabel();
    if(enableWallet)
    {
=======
    // Status bar notification icons
    QFrame* frameBlocks = new QFrame();
    frameBlocks->setContentsMargins(0, 0, 0, 0);
    frameBlocks->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    QHBoxLayout* frameBlocksLayout = new QHBoxLayout(frameBlocks);
    frameBlocksLayout->setContentsMargins(3, 0, 3, 0);
    frameBlocksLayout->setSpacing(3);
    unitDisplayControl = new UnitDisplayStatusBarControl();
    labelStakingIcon = new QLabel();
    labelEncryptionIcon = new QLabel();
    labelConnectionsIcon = new QPushButton();
    labelConnectionsIcon->setFlat(true); // Make the button look like a label, but clickable
    labelConnectionsIcon->setStyleSheet(".QPushButton { background-color: rgba(255, 255, 255, 0);}");
    labelConnectionsIcon->setMaximumSize(STATUSBAR_ICONSIZE, STATUSBAR_ICONSIZE);
    labelBlocksIcon = new QLabel();

    if (enableWallet) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        frameBlocksLayout->addStretch();
        frameBlocksLayout->addWidget(unitDisplayControl);
        frameBlocksLayout->addStretch();
        frameBlocksLayout->addWidget(labelEncryptionIcon);
<<<<<<< HEAD
        frameBlocksLayout->addWidget(labelWalletHDStatusIcon);
    }
    frameBlocksLayout->addStretch();
=======
    }
    frameBlocksLayout->addStretch();
    frameBlocksLayout->addWidget(labelStakingIcon);
    frameBlocksLayout->addStretch();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    frameBlocksLayout->addWidget(labelConnectionsIcon);
    frameBlocksLayout->addStretch();
    frameBlocksLayout->addWidget(labelBlocksIcon);
    frameBlocksLayout->addStretch();

    // Progress bar and label for blocks download
    progressBarLabel = new QLabel();
    progressBarLabel->setVisible(true);
    progressBar = new GUIUtil::ProgressBar();
    progressBar->setAlignment(Qt::AlignCenter);
    progressBar->setVisible(true);

    // Override style sheet for progress bar for styles that have a segmented progress bar,
    // as they make the text unreadable (workaround for issue #1071)
    // See https://qt-project.org/doc/qt-4.8/gallery.html
    QString curStyle = QApplication::style()->metaObject()->className();
<<<<<<< HEAD
    if(curStyle == "QWindowsStyle" || curStyle == "QWindowsXPStyle")
    {
=======
    if (curStyle == "QWindowsStyle" || curStyle == "QWindowsXPStyle") {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        progressBar->setStyleSheet("QProgressBar { background-color: #F8F8F8; border: 1px solid grey; border-radius: 7px; padding: 1px; text-align: center; } QProgressBar::chunk { background: QLinearGradient(x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #00CCFF, stop: 1 #33CCFF); border-radius: 7px; margin: 0px; }");
    }

    statusBar()->addWidget(progressBarLabel);
    statusBar()->addWidget(progressBar);
    statusBar()->addPermanentWidget(frameBlocks);

<<<<<<< HEAD
=======
    // Jump directly to tabs in RPC-console
    connect(openInfoAction, SIGNAL(triggered()), rpcConsole, SLOT(showInfo()));
    connect(openRPCConsoleAction, SIGNAL(triggered()), rpcConsole, SLOT(showConsole()));
    connect(openNetworkAction, SIGNAL(triggered()), rpcConsole, SLOT(showNetwork()));
    connect(openPeersAction, SIGNAL(triggered()), rpcConsole, SLOT(showPeers()));
    connect(openRepairAction, SIGNAL(triggered()), rpcConsole, SLOT(showRepair()));
    connect(openConfEditorAction, SIGNAL(triggered()), rpcConsole, SLOT(showConfEditor()));
    connect(openMNConfEditorAction, SIGNAL(triggered()), rpcConsole, SLOT(showMNConfEditor()));
    connect(showBackupsAction, SIGNAL(triggered()), rpcConsole, SLOT(showBackups()));
    connect(labelConnectionsIcon, SIGNAL(clicked()), rpcConsole, SLOT(showPeers()));

    // Get restart command-line parameters and handle restart
    connect(rpcConsole, SIGNAL(handleRestart(QStringList)), this, SLOT(handleRestart(QStringList)));

    // prevents an open debug window from becoming stuck/unusable on client shutdown
    connect(quitAction, SIGNAL(triggered()), rpcConsole, SLOT(hide()));

    connect(openBlockExplorerAction, SIGNAL(triggered()), explorerWindow, SLOT(show()));

    // prevents an open debug window from becoming stuck/unusable on client shutdown
    connect(quitAction, SIGNAL(triggered()), explorerWindow, SLOT(hide()));

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    // Install event filter to be able to catch status tip events (QEvent::StatusTip)
    this->installEventFilter(this);

    // Initially wallet actions should be disabled
    setWalletActionsEnabled(false);

    // Subscribe to notifications from core
    subscribeToCoreSignals();

<<<<<<< HEAD
    // Jump to peers tab by clicking on connections icon
    connect(labelConnectionsIcon, SIGNAL(clicked(QPoint)), this, SLOT(showPeers()));

    modalOverlay = new ModalOverlay(this->centralWidget());
#ifdef ENABLE_WALLET
    if(enableWallet) {
        connect(walletFrame, SIGNAL(requestedSyncWarningInfo()), this, SLOT(showModalOverlay()));
        connect(labelBlocksIcon, SIGNAL(clicked(QPoint)), this, SLOT(showModalOverlay()));
        connect(progressBar, SIGNAL(clicked(QPoint)), this, SLOT(showModalOverlay()));
    }
#endif
=======
    QTimer* timerStakingIcon = new QTimer(labelStakingIcon);
    connect(timerStakingIcon, SIGNAL(timeout()), this, SLOT(setStakingStatus()));
    timerStakingIcon->start(10000);
    setStakingStatus();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

BitcoinGUI::~BitcoinGUI()
{
    // Unsubscribe from notifications from core
    unsubscribeFromCoreSignals();

    GUIUtil::saveWindowGeometry("nWindow", this);
<<<<<<< HEAD
    if(trayIcon) // Hide tray icon, as deleting will let it linger until quit (on Ubuntu)
=======
    if (trayIcon) // Hide tray icon, as deleting will let it linger until quit (on Ubuntu)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        trayIcon->hide();
#ifdef Q_OS_MAC
    delete appMenuBar;
    MacDockIconHandler::cleanup();
#endif
<<<<<<< HEAD

    delete rpcConsole;
}

void BitcoinGUI::createActions()
{
    QActionGroup *tabGroup = new QActionGroup(this);

    QString theme = GUIUtil::getThemeName();
    overviewAction = new QAction(QIcon(":/icons/" + theme + "/overview"), tr("&Overview"), this);
=======
}

void BitcoinGUI::createActions(const NetworkStyle* networkStyle)
{
    QActionGroup* tabGroup = new QActionGroup(this);

    overviewAction = new QAction(QIcon(":/icons/overview"), tr("&Overview"), this);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    overviewAction->setStatusTip(tr("Show general overview of wallet"));
    overviewAction->setToolTip(overviewAction->statusTip());
    overviewAction->setCheckable(true);
#ifdef Q_OS_MAC
    overviewAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_1));
#else
    overviewAction->setShortcut(QKeySequence(Qt::ALT + Qt::Key_1));
#endif
    tabGroup->addAction(overviewAction);

<<<<<<< HEAD
    sendCoinsAction = new QAction(QIcon(":/icons/" + theme + "/send"), tr("&Send"), this);
    sendCoinsAction->setStatusTip(tr("Send coins to a GelCoin address"));
=======
    sendCoinsAction = new QAction(QIcon(":/icons/send"), tr("&Send"), this);
    sendCoinsAction->setStatusTip(tr("Send coins to a LUX address"));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    sendCoinsAction->setToolTip(sendCoinsAction->statusTip());
    sendCoinsAction->setCheckable(true);
#ifdef Q_OS_MAC
    sendCoinsAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_2));
#else
    sendCoinsAction->setShortcut(QKeySequence(Qt::ALT + Qt::Key_2));
#endif
    tabGroup->addAction(sendCoinsAction);

<<<<<<< HEAD
    sendCoinsMenuAction = new QAction(QIcon(":/icons/" + theme + "/send"), sendCoinsAction->text(), this);
    sendCoinsMenuAction->setStatusTip(sendCoinsAction->statusTip());
    sendCoinsMenuAction->setToolTip(sendCoinsMenuAction->statusTip());

    receiveCoinsAction = new QAction(QIcon(":/icons/" + theme + "/receiving_addresses"), tr("&Receive"), this);
    receiveCoinsAction->setStatusTip(tr("Request payments (generates QR codes and gelcoin: URIs)"));
=======
    receiveCoinsAction = new QAction(QIcon(":/icons/receiving_addresses"), tr("&Receive"), this);
    receiveCoinsAction->setStatusTip(tr("Request payments (generates QR codes and lux: URIs)"));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    receiveCoinsAction->setToolTip(receiveCoinsAction->statusTip());
    receiveCoinsAction->setCheckable(true);
#ifdef Q_OS_MAC
    receiveCoinsAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_3));
#else
    receiveCoinsAction->setShortcut(QKeySequence(Qt::ALT + Qt::Key_3));
#endif
    tabGroup->addAction(receiveCoinsAction);

<<<<<<< HEAD
    receiveCoinsMenuAction = new QAction(QIcon(":/icons/" + theme + "/receiving_addresses"), receiveCoinsAction->text(), this);
    receiveCoinsMenuAction->setStatusTip(receiveCoinsAction->statusTip());
    receiveCoinsMenuAction->setToolTip(receiveCoinsMenuAction->statusTip());

    historyAction = new QAction(QIcon(":/icons/" + theme + "/history"), tr("&Transactions"), this);
=======
    historyAction = new QAction(QIcon(":/icons/history"), tr("&Transactions"), this);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    historyAction->setStatusTip(tr("Browse transaction history"));
    historyAction->setToolTip(historyAction->statusTip());
    historyAction->setCheckable(true);
#ifdef Q_OS_MAC
    historyAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_4));
#else
    historyAction->setShortcut(QKeySequence(Qt::ALT + Qt::Key_4));
#endif
    tabGroup->addAction(historyAction);

<<<<<<< HEAD
#ifdef ENABLE_WALLET
    QSettings settings;
    if (settings.value("fShowMasternodesTab").toBool()) {
        masternodeAction = new QAction(QIcon(":/icons/" + theme + "/masternodes"), tr("&Masternodes"), this);
=======
    tradingAction = new QAction(QIcon(":/icons/receiving_addresses"), tr("&Trading"), this);
    tradingAction->setStatusTip(tr("Trading on Cryptopia"));
    tradingAction->setToolTip(tradingAction->statusTip());
    tradingAction->setCheckable(true);
#ifdef Q_OS_MAC
    tradingAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_5));
#else
    tradingAction->setShortcut(QKeySequence(Qt::ALT + Qt::Key_5));
#endif
    tabGroup->addAction(tradingAction);

#ifdef ENABLE_WALLET

    QSettings settings;
    if (settings.value("fShowMasternodesTab").toBool()) {
        masternodeAction = new QAction(QIcon(":/icons/masternodes"), tr("&Masternodes"), this);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        masternodeAction->setStatusTip(tr("Browse masternodes"));
        masternodeAction->setToolTip(masternodeAction->statusTip());
        masternodeAction->setCheckable(true);
#ifdef Q_OS_MAC
        masternodeAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_5));
#else
        masternodeAction->setShortcut(QKeySequence(Qt::ALT + Qt::Key_5));
#endif
        tabGroup->addAction(masternodeAction);
        connect(masternodeAction, SIGNAL(triggered()), this, SLOT(showNormalIfMinimized()));
        connect(masternodeAction, SIGNAL(triggered()), this, SLOT(gotoMasternodePage()));
    }

    // These showNormalIfMinimized are needed because Send Coins and Receive Coins
    // can be triggered from the tray menu, and need to show the GUI to be useful.
    connect(overviewAction, SIGNAL(triggered()), this, SLOT(showNormalIfMinimized()));
    connect(overviewAction, SIGNAL(triggered()), this, SLOT(gotoOverviewPage()));
    connect(sendCoinsAction, SIGNAL(triggered()), this, SLOT(showNormalIfMinimized()));
    connect(sendCoinsAction, SIGNAL(triggered()), this, SLOT(gotoSendCoinsPage()));
<<<<<<< HEAD
    connect(sendCoinsMenuAction, SIGNAL(triggered()), this, SLOT(showNormalIfMinimized()));
    connect(sendCoinsMenuAction, SIGNAL(triggered()), this, SLOT(gotoSendCoinsPage()));
    connect(receiveCoinsAction, SIGNAL(triggered()), this, SLOT(showNormalIfMinimized()));
    connect(receiveCoinsAction, SIGNAL(triggered()), this, SLOT(gotoReceiveCoinsPage()));
    connect(receiveCoinsMenuAction, SIGNAL(triggered()), this, SLOT(showNormalIfMinimized()));
    connect(receiveCoinsMenuAction, SIGNAL(triggered()), this, SLOT(gotoReceiveCoinsPage()));
    connect(historyAction, SIGNAL(triggered()), this, SLOT(showNormalIfMinimized()));
    connect(historyAction, SIGNAL(triggered()), this, SLOT(gotoHistoryPage()));
#endif // ENABLE_WALLET

    quitAction = new QAction(QIcon(":/icons/" + theme + "/quit"), tr("E&xit"), this);
    quitAction->setStatusTip(tr("Quit application"));
    quitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    quitAction->setMenuRole(QAction::QuitRole);
    aboutAction = new QAction(QIcon(":/icons/" + theme + "/about"), tr("&About GelCoin"), this);
    aboutAction->setStatusTip(tr("Show information about GelCoin"));
    aboutAction->setMenuRole(QAction::AboutRole);
    aboutAction->setEnabled(false);
    aboutQtAction = new QAction(QIcon(":/icons/" + theme + "/about_qt"), tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show information about Qt"));
    aboutQtAction->setMenuRole(QAction::AboutQtRole);
    optionsAction = new QAction(QIcon(":/icons/" + theme + "/options"), tr("&Options..."), this);
    optionsAction->setStatusTip(tr("Modify configuration options for GelCoin"));
    optionsAction->setMenuRole(QAction::PreferencesRole);
    optionsAction->setEnabled(false);
    toggleHideAction = new QAction(QIcon(":/icons/" + theme + "/about"), tr("&Show / Hide"), this);
    toggleHideAction->setStatusTip(tr("Show or hide the main Window"));

    encryptWalletAction = new QAction(QIcon(":/icons/" + theme + "/lock_closed"), tr("&Encrypt Wallet..."), this);
    encryptWalletAction->setStatusTip(tr("Encrypt the private keys that belong to your wallet"));
    encryptWalletAction->setCheckable(true);
    backupWalletAction = new QAction(QIcon(":/icons/" + theme + "/filesave"), tr("&Backup Wallet..."), this);
    backupWalletAction->setStatusTip(tr("Backup wallet to another location"));
    changePassphraseAction = new QAction(QIcon(":/icons/" + theme + "/key"), tr("&Change Passphrase..."), this);
=======
    connect(receiveCoinsAction, SIGNAL(triggered()), this, SLOT(showNormalIfMinimized()));
    connect(receiveCoinsAction, SIGNAL(triggered()), this, SLOT(gotoReceiveCoinsPage()));
    connect(historyAction, SIGNAL(triggered()), this, SLOT(showNormalIfMinimized()));
    connect(historyAction, SIGNAL(triggered()), this, SLOT(gotoHistoryPage()));
    connect(tradingAction, SIGNAL(triggered()), this, SLOT(showNormalIfMinimized()));
    connect(tradingAction, SIGNAL(triggered()), this, SLOT(gotoTradingPage()));
#endif // ENABLE_WALLET

    quitAction = new QAction(QIcon(":/icons/quit"), tr("E&xit"), this);
    quitAction->setStatusTip(tr("Quit application"));
    quitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    quitAction->setMenuRole(QAction::QuitRole);
    aboutAction = new QAction(networkStyle->getAppIcon(), tr("&About LUX Core"), this);
    aboutAction->setStatusTip(tr("Show information about LUX Core"));
    aboutAction->setMenuRole(QAction::AboutRole);
#if QT_VERSION < 0x050000
    aboutQtAction = new QAction(QIcon(":/trolltech/qmessagebox/images/qtlogo-64.png"), tr("About &Qt"), this);
#else
    aboutQtAction = new QAction(QIcon(":/qt-project.org/qmessagebox/images/qtlogo-64.png"), tr("About &Qt"), this);
#endif
    aboutQtAction->setStatusTip(tr("Show information about Qt"));
    aboutQtAction->setMenuRole(QAction::AboutQtRole);
    optionsAction = new QAction(QIcon(":/icons/options"), tr("&Options..."), this);
    optionsAction->setStatusTip(tr("Modify configuration options for LUX"));
    optionsAction->setMenuRole(QAction::PreferencesRole);
    toggleHideAction = new QAction(networkStyle->getAppIcon(), tr("&Show / Hide"), this);
    toggleHideAction->setStatusTip(tr("Show or hide the main Window"));

    encryptWalletAction = new QAction(QIcon(":/icons/lock_closed"), tr("&Encrypt Wallet..."), this);
    encryptWalletAction->setStatusTip(tr("Encrypt the private keys that belong to your wallet"));
    encryptWalletAction->setCheckable(true);
    backupWalletAction = new QAction(QIcon(":/icons/filesave"), tr("&Backup Wallet..."), this);
    backupWalletAction->setStatusTip(tr("Backup wallet to another location"));
    changePassphraseAction = new QAction(QIcon(":/icons/key"), tr("&Change Passphrase..."), this);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    changePassphraseAction->setStatusTip(tr("Change the passphrase used for wallet encryption"));
    unlockWalletAction = new QAction(tr("&Unlock Wallet..."), this);
    unlockWalletAction->setToolTip(tr("Unlock wallet"));
    lockWalletAction = new QAction(tr("&Lock Wallet"), this);
<<<<<<< HEAD
    signMessageAction = new QAction(QIcon(":/icons/" + theme + "/edit"), tr("Sign &message..."), this);
    signMessageAction->setStatusTip(tr("Sign messages with your GelCoin addresses to prove you own them"));
    verifyMessageAction = new QAction(QIcon(":/icons/" + theme + "/transaction_0"), tr("&Verify message..."), this);
    verifyMessageAction->setStatusTip(tr("Verify messages to ensure they were signed with specified GelCoin addresses"));

    openInfoAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_MessageBoxInformation), tr("&Information"), this);
    openInfoAction->setStatusTip(tr("Show diagnostic information"));
    openRPCConsoleAction = new QAction(QIcon(":/icons/" + theme + "/debugwindow"), tr("&Debug console"), this);
    openRPCConsoleAction->setStatusTip(tr("Open debugging console"));
    openGraphAction = new QAction(QIcon(":/icons/" + theme + "/connect_4"), tr("&Network Monitor"), this);
    openGraphAction->setStatusTip(tr("Show network monitor"));
    openPeersAction = new QAction(QIcon(":/icons/" + theme + "/connect_4"), tr("&Peers list"), this);
    openPeersAction->setStatusTip(tr("Show peers info"));
    openRepairAction = new QAction(QIcon(":/icons/" + theme + "/options"), tr("Wallet &Repair"), this);
    openRepairAction->setStatusTip(tr("Show wallet repair options"));
    openConfEditorAction = new QAction(QIcon(":/icons/" + theme + "/edit"), tr("Open Wallet &Configuration File"), this);
    openConfEditorAction->setStatusTip(tr("Open configuration file"));
    openMNConfEditorAction = new QAction(QIcon(":/icons/" + theme + "/edit"), tr("Open &Masternode Configuration File"), this);
    openMNConfEditorAction->setStatusTip(tr("Open Masternode configuration file"));    
    showBackupsAction = new QAction(QIcon(":/icons/" + theme + "/browse"), tr("Show Automatic &Backups"), this);
    showBackupsAction->setStatusTip(tr("Show automatically created wallet backups"));
    // initially disable the debug window menu items
    openInfoAction->setEnabled(false);
    openRPCConsoleAction->setEnabled(false);
    openGraphAction->setEnabled(false);
    openPeersAction->setEnabled(false);
    openRepairAction->setEnabled(false);

    usedSendingAddressesAction = new QAction(QIcon(":/icons/" + theme + "/address-book"), tr("&Sending addresses..."), this);
    usedSendingAddressesAction->setStatusTip(tr("Show the list of used sending addresses and labels"));
    usedReceivingAddressesAction = new QAction(QIcon(":/icons/" + theme + "/address-book"), tr("&Receiving addresses..."), this);
    usedReceivingAddressesAction->setStatusTip(tr("Show the list of used receiving addresses and labels"));

    openAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_DirOpenIcon), tr("Open &URI..."), this);
    openAction->setStatusTip(tr("Open a gelcoin: URI or payment request"));

    showHelpMessageAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_MessageBoxInformation), tr("&Command-line options"), this);
    showHelpMessageAction->setMenuRole(QAction::NoRole);
    showHelpMessageAction->setStatusTip(tr("Show the GelCoin help message to get a list with possible GelCoin command-line options"));

    showPrivateSendHelpAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_MessageBoxInformation), tr("&PrivateSend information"), this);
    showPrivateSendHelpAction->setMenuRole(QAction::NoRole);
    showPrivateSendHelpAction->setStatusTip(tr("Show the PrivateSend basic information"));
=======
    signMessageAction = new QAction(QIcon(":/icons/edit"), tr("Sign &message..."), this);
    signMessageAction->setStatusTip(tr("Sign messages with your LUX addresses to prove you own them"));
    verifyMessageAction = new QAction(QIcon(":/icons/transaction_0"), tr("&Verify message..."), this);
    verifyMessageAction->setStatusTip(tr("Verify messages to ensure they were signed with specified LUX addresses"));
    bip38ToolAction = new QAction(QIcon(":/icons/key"), tr("&BIP38 tool"), this);
    bip38ToolAction->setToolTip(tr("Encrypt and decrypt private keys using a passphrase"));
    multiSendAction = new QAction(QIcon(":/icons/edit"), tr("&MultiSend"), this);
    multiSendAction->setToolTip(tr("MultiSend Settings"));
    multiSendAction->setCheckable(true);

    openInfoAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_MessageBoxInformation), tr("&Information"), this);
    openInfoAction->setStatusTip(tr("Show diagnostic information"));
    openRPCConsoleAction = new QAction(QIcon(":/icons/debugwindow"), tr("&Debug console"), this);
    openRPCConsoleAction->setStatusTip(tr("Open debugging console"));
    openNetworkAction = new QAction(QIcon(":/icons/connect_4"), tr("&Network Monitor"), this);
    openNetworkAction->setStatusTip(tr("Show network monitor"));
    openPeersAction = new QAction(QIcon(":/icons/connect_4"), tr("&Peers list"), this);
    openPeersAction->setStatusTip(tr("Show peers info"));
    openRepairAction = new QAction(QIcon(":/icons/options"), tr("Wallet &Repair"), this);
    openRepairAction->setStatusTip(tr("Show wallet repair options"));
    openConfEditorAction = new QAction(QIcon(":/icons/edit"), tr("Open Wallet &Configuration File"), this);
    openConfEditorAction->setStatusTip(tr("Open configuration file"));
    openMNConfEditorAction = new QAction(QIcon(":/icons/edit"), tr("Open &Masternode Configuration File"), this);
    openMNConfEditorAction->setStatusTip(tr("Open Masternode configuration file"));
    showBackupsAction = new QAction(QIcon(":/icons/browse"), tr("Show Automatic &Backups"), this);
    showBackupsAction->setStatusTip(tr("Show automatically created wallet backups"));

    usedSendingAddressesAction = new QAction(QIcon(":/icons/address-book"), tr("&Sending addresses..."), this);
    usedSendingAddressesAction->setStatusTip(tr("Show the list of used sending addresses and labels"));
    usedReceivingAddressesAction = new QAction(QIcon(":/icons/address-book"), tr("&Receiving addresses..."), this);
    usedReceivingAddressesAction->setStatusTip(tr("Show the list of used receiving addresses and labels"));

    openAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_FileIcon), tr("Open &URI..."), this);
    openAction->setStatusTip(tr("Open a LUX: URI or payment request"));
    openBlockExplorerAction = new QAction(QIcon(":/icons/explorer"), tr("&Blockchain explorer"), this);
    openBlockExplorerAction->setStatusTip(tr("Block explorer window"));

    showHelpMessageAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_MessageBoxInformation), tr("&Command-line options"), this);
    showHelpMessageAction->setMenuRole(QAction::NoRole);
    showHelpMessageAction->setStatusTip(tr("Show the LUX Core help message to get a list with possible LUX command-line options"));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutClicked()));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(optionsAction, SIGNAL(triggered()), this, SLOT(optionsClicked()));
    connect(toggleHideAction, SIGNAL(triggered()), this, SLOT(toggleHidden()));
    connect(showHelpMessageAction, SIGNAL(triggered()), this, SLOT(showHelpMessageClicked()));
<<<<<<< HEAD
    connect(showPrivateSendHelpAction, SIGNAL(triggered()), this, SLOT(showPrivateSendHelpClicked()));

    // Jump directly to tabs in RPC-console
    connect(openInfoAction, SIGNAL(triggered()), this, SLOT(showInfo()));
    connect(openRPCConsoleAction, SIGNAL(triggered()), this, SLOT(showConsole()));
    connect(openGraphAction, SIGNAL(triggered()), this, SLOT(showGraph()));
    connect(openPeersAction, SIGNAL(triggered()), this, SLOT(showPeers()));
    connect(openRepairAction, SIGNAL(triggered()), this, SLOT(showRepair()));

    // Open configs and backup folder from menu
    connect(openConfEditorAction, SIGNAL(triggered()), this, SLOT(showConfEditor()));
    connect(openMNConfEditorAction, SIGNAL(triggered()), this, SLOT(showMNConfEditor()));
    connect(showBackupsAction, SIGNAL(triggered()), this, SLOT(showBackups()));

    // Get restart command-line parameters and handle restart
    connect(rpcConsole, SIGNAL(handleRestart(QStringList)), this, SLOT(handleRestart(QStringList)));
    
    // prevents an open debug window from becoming stuck/unusable on client shutdown
    connect(quitAction, SIGNAL(triggered()), rpcConsole, SLOT(hide()));

#ifdef ENABLE_WALLET
    if(walletFrame)
    {
=======
#ifdef ENABLE_WALLET
    if (walletFrame) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        connect(encryptWalletAction, SIGNAL(triggered(bool)), walletFrame, SLOT(encryptWallet(bool)));
        connect(backupWalletAction, SIGNAL(triggered()), walletFrame, SLOT(backupWallet()));
        connect(changePassphraseAction, SIGNAL(triggered()), walletFrame, SLOT(changePassphrase()));
        connect(unlockWalletAction, SIGNAL(triggered()), walletFrame, SLOT(unlockWallet()));
        connect(lockWalletAction, SIGNAL(triggered()), walletFrame, SLOT(lockWallet()));
        connect(signMessageAction, SIGNAL(triggered()), this, SLOT(gotoSignMessageTab()));
        connect(verifyMessageAction, SIGNAL(triggered()), this, SLOT(gotoVerifyMessageTab()));
<<<<<<< HEAD
        connect(usedSendingAddressesAction, SIGNAL(triggered()), walletFrame, SLOT(usedSendingAddresses()));
        connect(usedReceivingAddressesAction, SIGNAL(triggered()), walletFrame, SLOT(usedReceivingAddresses()));
        connect(openAction, SIGNAL(triggered()), this, SLOT(openClicked()));
    }
#endif // ENABLE_WALLET

    new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_I), this, SLOT(showInfo()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_C), this, SLOT(showConsole()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_G), this, SLOT(showGraph()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_P), this, SLOT(showPeers()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_R), this, SLOT(showRepair()));
=======
        connect(bip38ToolAction, SIGNAL(triggered()), this, SLOT(gotoBip38Tool()));
        connect(usedSendingAddressesAction, SIGNAL(triggered()), walletFrame, SLOT(usedSendingAddresses()));
        connect(usedReceivingAddressesAction, SIGNAL(triggered()), walletFrame, SLOT(usedReceivingAddresses()));
        connect(openAction, SIGNAL(triggered()), this, SLOT(openClicked()));
        connect(multiSendAction, SIGNAL(triggered()), this, SLOT(gotoMultiSendDialog()));
    }
#endif // ENABLE_WALLET
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

void BitcoinGUI::createMenuBar()
{
#ifdef Q_OS_MAC
    // Create a decoupled menu bar on Mac which stays even if the window is closed
    appMenuBar = new QMenuBar();
#else
    // Get the main window's menu bar on other platforms
    appMenuBar = menuBar();
#endif

    // Configure the menus
<<<<<<< HEAD
    QMenu *file = appMenuBar->addMenu(tr("&File"));
    if(walletFrame)
    {
=======
    QMenu* file = appMenuBar->addMenu(tr("&File"));
    if (walletFrame) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        file->addAction(openAction);
        file->addAction(backupWalletAction);
        file->addAction(signMessageAction);
        file->addAction(verifyMessageAction);
        file->addSeparator();
        file->addAction(usedSendingAddressesAction);
        file->addAction(usedReceivingAddressesAction);
        file->addSeparator();
    }
    file->addAction(quitAction);

<<<<<<< HEAD
    QMenu *settings = appMenuBar->addMenu(tr("&Settings"));
    if(walletFrame)
    {
=======
    QMenu* settings = appMenuBar->addMenu(tr("&Settings"));
    if (walletFrame) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        settings->addAction(encryptWalletAction);
        settings->addAction(changePassphraseAction);
        settings->addAction(unlockWalletAction);
        settings->addAction(lockWalletAction);
<<<<<<< HEAD
=======
        settings->addAction(bip38ToolAction);
        settings->addAction(multiSendAction);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        settings->addSeparator();
    }
    settings->addAction(optionsAction);

<<<<<<< HEAD
    if(walletFrame)
    {
        QMenu *tools = appMenuBar->addMenu(tr("&Tools"));
        tools->addAction(openInfoAction);
        tools->addAction(openRPCConsoleAction);
        tools->addAction(openGraphAction);
=======
    if (walletFrame) {
        QMenu* tools = appMenuBar->addMenu(tr("&Tools"));
        tools->addAction(openInfoAction);
        tools->addAction(openRPCConsoleAction);
        tools->addAction(openNetworkAction);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        tools->addAction(openPeersAction);
        tools->addAction(openRepairAction);
        tools->addSeparator();
        tools->addAction(openConfEditorAction);
        tools->addAction(openMNConfEditorAction);
        tools->addAction(showBackupsAction);
<<<<<<< HEAD
    }

    QMenu *help = appMenuBar->addMenu(tr("&Help"));
    help->addAction(showHelpMessageAction);
    help->addAction(showPrivateSendHelpAction);
=======
        tools->addAction(openBlockExplorerAction);
    }

    QMenu* help = appMenuBar->addMenu(tr("&Help"));
    help->addAction(showHelpMessageAction);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    help->addSeparator();
    help->addAction(aboutAction);
    help->addAction(aboutQtAction);
}

void BitcoinGUI::createToolBars()
{
<<<<<<< HEAD
#ifdef ENABLE_WALLET
    if(walletFrame)
    {
        QToolBar *toolbar = new QToolBar(tr("Tabs toolbar"));
=======
    if (walletFrame) {
        QToolBar* toolbar = new QToolBar(tr("Tabs toolbar"));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        toolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolbar->addAction(overviewAction);
        toolbar->addAction(sendCoinsAction);
        toolbar->addAction(receiveCoinsAction);
        toolbar->addAction(historyAction);
<<<<<<< HEAD
        QSettings settings;
        if (settings.value("fShowMasternodesTab").toBool())
        {
=======
        toolbar->addAction(tradingAction);
        QSettings settings;
        if (settings.value("fShowMasternodesTab").toBool()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            toolbar->addAction(masternodeAction);
        }
        toolbar->setMovable(false); // remove unused icon in upper left corner
        overviewAction->setChecked(true);

        /** Create additional container for toolbar and walletFrame and make it the central widget.
            This is a workaround mostly for toolbar styling on Mac OS but should work fine for every other OSes too.
        */
<<<<<<< HEAD
        QVBoxLayout *layout = new QVBoxLayout;
=======
        QVBoxLayout* layout = new QVBoxLayout;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        layout->addWidget(toolbar);
        layout->addWidget(walletFrame);
        layout->setSpacing(0);
        layout->setContentsMargins(QMargins());
<<<<<<< HEAD
        QWidget *containerWidget = new QWidget();
        containerWidget->setLayout(layout);
        setCentralWidget(containerWidget);
    }
#endif // ENABLE_WALLET
}

void BitcoinGUI::setClientModel(ClientModel *clientModel)
{
    this->clientModel = clientModel;
    if(clientModel)
    {
        // Create system tray menu (or setup the dock menu) that late to prevent users from calling actions,
        // while the client has not yet fully loaded
        if (trayIcon) {
            // do so only if trayIcon is already set
            trayIconMenu = new QMenu(this);
            trayIcon->setContextMenu(trayIconMenu);
            createIconMenu(trayIconMenu);

#ifndef Q_OS_MAC
            // Show main window on tray icon click
            // Note: ignore this on Mac - this is not the way tray should work there
            connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                    this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
#else
            // Note: On Mac, the dock icon is also used to provide menu functionality
            // similar to one for tray icon
            MacDockIconHandler *dockIconHandler = MacDockIconHandler::instance();
            dockIconHandler->setMainWindow((QMainWindow *)this);
            dockIconMenu = dockIconHandler->dockMenu();
 
            createIconMenu(dockIconMenu);
#endif
        }

        // Keep up to date with client
        updateNetworkState();
        connect(clientModel, SIGNAL(numConnectionsChanged(int)), this, SLOT(setNumConnections(int)));
        connect(clientModel, SIGNAL(networkActiveChanged(bool)), this, SLOT(setNetworkActive(bool)));

        modalOverlay->setKnownBestHeight(clientModel->getHeaderTipHeight(), QDateTime::fromTime_t(clientModel->getHeaderTipTime()));
        setNumBlocks(clientModel->getNumBlocks(), clientModel->getLastBlockDate(), clientModel->getVerificationProgress(NULL), false);
        connect(clientModel, SIGNAL(numBlocksChanged(int,QDateTime,double,bool)), this, SLOT(setNumBlocks(int,QDateTime,double,bool)));

        connect(clientModel, SIGNAL(additionalDataSyncProgressChanged(double)), this, SLOT(setAdditionalDataSyncProgress(double)));

        // Receive and report messages from client model
        connect(clientModel, SIGNAL(message(QString,QString,unsigned int)), this, SLOT(message(QString,QString,unsigned int)));

        // Show progress dialog
        connect(clientModel, SIGNAL(showProgress(QString,int)), this, SLOT(showProgress(QString,int)));

        rpcConsole->setClientModel(clientModel);
#ifdef ENABLE_WALLET
        if(walletFrame)
        {
=======
        QWidget* containerWidget = new QWidget();
        containerWidget->setLayout(layout);
        setCentralWidget(containerWidget);
    }
}

void BitcoinGUI::setClientModel(ClientModel* clientModel)
{
    this->clientModel = clientModel;
    if (clientModel) {
        // Create system tray menu (or setup the dock menu) that late to prevent users from calling actions,
        // while the client has not yet fully loaded
        createTrayIconMenu();

        // Keep up to date with client
        setNumConnections(clientModel->getNumConnections());
        connect(clientModel, SIGNAL(numConnectionsChanged(int)), this, SLOT(setNumConnections(int)));

        setNumBlocks(clientModel->getNumBlocks());
        connect(clientModel, SIGNAL(numBlocksChanged(int)), this, SLOT(setNumBlocks(int)));

        // Receive and report messages from client model
        connect(clientModel, SIGNAL(message(QString, QString, unsigned int)), this, SLOT(message(QString, QString, unsigned int)));

        // Show progress dialog
        connect(clientModel, SIGNAL(showProgress(QString, int)), this, SLOT(showProgress(QString, int)));

        rpcConsole->setClientModel(clientModel);
#ifdef ENABLE_WALLET
        if (walletFrame) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            walletFrame->setClientModel(clientModel);
        }
#endif // ENABLE_WALLET
        unitDisplayControl->setOptionsModel(clientModel->getOptionsModel());
<<<<<<< HEAD
        
        OptionsModel* optionsModel = clientModel->getOptionsModel();
        if(optionsModel)
        {
            // be aware of the tray icon disable state change reported by the OptionsModel object.
            connect(optionsModel,SIGNAL(hideTrayIconChanged(bool)),this,SLOT(setTrayIconVisible(bool)));
        
            // initialize the disable state of the tray icon with the current value in the model.
            setTrayIconVisible(optionsModel->getHideTrayIcon());
        }
    } else {
        // Disable possibility to show main window via action
        toggleHideAction->setEnabled(false);
        if(trayIconMenu)
        {
            // Disable context menu on tray icon
            trayIconMenu->clear();
        }
        // Propagate cleared model to child objects
        rpcConsole->setClientModel(nullptr);
#ifdef ENABLE_WALLET
        walletFrame->setClientModel(nullptr);
#endif // ENABLE_WALLET
        unitDisplayControl->setOptionsModel(nullptr);

#ifdef Q_OS_MAC
        if(dockIconMenu)
        {
            // Disable context menu on dock icon
            dockIconMenu->clear();
        }
#endif
=======
    } else {
        // Disable possibility to show main window via action
        toggleHideAction->setEnabled(false);
        if (trayIconMenu) {
            // Disable context menu on tray icon
            trayIconMenu->clear();
        }
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }
}

#ifdef ENABLE_WALLET
<<<<<<< HEAD
bool BitcoinGUI::addWallet(const QString& name, WalletModel *walletModel)
{
    if(!walletFrame)
=======
bool BitcoinGUI::addWallet(const QString& name, WalletModel* walletModel)
{
    if (!walletFrame)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return false;
    setWalletActionsEnabled(true);
    return walletFrame->addWallet(name, walletModel);
}

bool BitcoinGUI::setCurrentWallet(const QString& name)
{
<<<<<<< HEAD
    if(!walletFrame)
=======
    if (!walletFrame)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return false;
    return walletFrame->setCurrentWallet(name);
}

void BitcoinGUI::removeAllWallets()
{
<<<<<<< HEAD
    if(!walletFrame)
=======
    if (!walletFrame)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return;
    setWalletActionsEnabled(false);
    walletFrame->removeAllWallets();
}
#endif // ENABLE_WALLET

void BitcoinGUI::setWalletActionsEnabled(bool enabled)
{
    overviewAction->setEnabled(enabled);
    sendCoinsAction->setEnabled(enabled);
<<<<<<< HEAD
    sendCoinsMenuAction->setEnabled(enabled);
    receiveCoinsAction->setEnabled(enabled);
    receiveCoinsMenuAction->setEnabled(enabled);
    historyAction->setEnabled(enabled);
    QSettings settings;
    if (settings.value("fShowMasternodesTab").toBool() && masternodeAction) {
=======
    receiveCoinsAction->setEnabled(enabled);
    historyAction->setEnabled(enabled);
    tradingAction->setEnabled(enabled);
    QSettings settings;
    if (settings.value("fShowMasternodesTab").toBool()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        masternodeAction->setEnabled(enabled);
    }
    encryptWalletAction->setEnabled(enabled);
    backupWalletAction->setEnabled(enabled);
    changePassphraseAction->setEnabled(enabled);
    signMessageAction->setEnabled(enabled);
    verifyMessageAction->setEnabled(enabled);
<<<<<<< HEAD
=======
    bip38ToolAction->setEnabled(enabled);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    usedSendingAddressesAction->setEnabled(enabled);
    usedReceivingAddressesAction->setEnabled(enabled);
    openAction->setEnabled(enabled);
}

<<<<<<< HEAD
void BitcoinGUI::createTrayIcon(const NetworkStyle *networkStyle)
{
    trayIcon = new QSystemTrayIcon(this);
    QString toolTip = tr("GelCoin client") + " " + networkStyle->getTitleAddText();
    trayIcon->setToolTip(toolTip);
    trayIcon->setIcon(networkStyle->getTrayAndWindowIcon());
    trayIcon->hide();
    notificator = new Notificator(QApplication::applicationName(), trayIcon, this);
}

void BitcoinGUI::createIconMenu(QMenu *pmenu)
{
    // Configuration of the tray icon (or dock icon) icon menu
    pmenu->addAction(toggleHideAction);
    pmenu->addSeparator();
    pmenu->addAction(sendCoinsMenuAction);
    pmenu->addAction(receiveCoinsMenuAction);
    pmenu->addSeparator();
    pmenu->addAction(signMessageAction);
    pmenu->addAction(verifyMessageAction);
    pmenu->addSeparator();
    pmenu->addAction(optionsAction);
    pmenu->addAction(openInfoAction);
    pmenu->addAction(openRPCConsoleAction);
    pmenu->addAction(openGraphAction);
    pmenu->addAction(openPeersAction);
    pmenu->addAction(openRepairAction);
    pmenu->addSeparator();
    pmenu->addAction(openConfEditorAction);
    pmenu->addAction(openMNConfEditorAction);
    pmenu->addAction(showBackupsAction);
#ifndef Q_OS_MAC // This is built-in on Mac
    pmenu->addSeparator();
    pmenu->addAction(quitAction);
=======
void BitcoinGUI::createTrayIcon(const NetworkStyle* networkStyle)
{
#ifndef Q_OS_MAC
    trayIcon = new QSystemTrayIcon(this);
    QString toolTip = tr("LUX Core client") + " " + networkStyle->getTitleAddText();
    trayIcon->setToolTip(toolTip);
    trayIcon->setIcon(networkStyle->getAppIcon());
    trayIcon->show();
#endif

    notificator = new Notificator(QApplication::applicationName(), trayIcon, this);
}

void BitcoinGUI::createTrayIconMenu()
{
#ifndef Q_OS_MAC
    // return if trayIcon is unset (only on non-Mac OSes)
    if (!trayIcon)
        return;

    trayIconMenu = new QMenu(this);
    trayIcon->setContextMenu(trayIconMenu);

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
        this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
#else
    // Note: On Mac, the dock icon is used to provide the tray's functionality.
    MacDockIconHandler* dockIconHandler = MacDockIconHandler::instance();
    dockIconHandler->setMainWindow((QMainWindow*)this);
    trayIconMenu = dockIconHandler->dockMenu();
#endif

    // Configuration of the tray icon (or dock icon) icon menu
    trayIconMenu->addAction(toggleHideAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(sendCoinsAction);
    trayIconMenu->addAction(receiveCoinsAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(signMessageAction);
    trayIconMenu->addAction(verifyMessageAction);
    trayIconMenu->addAction(bip38ToolAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(optionsAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(openInfoAction);
    trayIconMenu->addAction(openRPCConsoleAction);
    trayIconMenu->addAction(openNetworkAction);
    trayIconMenu->addAction(openPeersAction);
    trayIconMenu->addAction(openRepairAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(openConfEditorAction);
    trayIconMenu->addAction(openMNConfEditorAction);
    trayIconMenu->addAction(showBackupsAction);
    trayIconMenu->addAction(openBlockExplorerAction);
#ifndef Q_OS_MAC // This is built-in on Mac
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#endif
}

#ifndef Q_OS_MAC
void BitcoinGUI::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
<<<<<<< HEAD
    if(reason == QSystemTrayIcon::Trigger)
    {
=======
    if (reason == QSystemTrayIcon::Trigger) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        // Click on system tray icon triggers show/hide of the main window
        toggleHidden();
    }
}
#endif

void BitcoinGUI::optionsClicked()
{
<<<<<<< HEAD
    if(!clientModel || !clientModel->getOptionsModel())
=======
    if (!clientModel || !clientModel->getOptionsModel())
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return;

    OptionsDialog dlg(this, enableWallet);
    dlg.setModel(clientModel->getOptionsModel());
    dlg.exec();
}

void BitcoinGUI::aboutClicked()
{
<<<<<<< HEAD
    if(!clientModel)
        return;

    HelpMessageDialog dlg(this, HelpMessageDialog::about);
    dlg.exec();
}

void BitcoinGUI::showDebugWindow()
{
    rpcConsole->showNormal();
    rpcConsole->show();
    rpcConsole->raise();
    rpcConsole->activateWindow();
}

void BitcoinGUI::showInfo()
{
    rpcConsole->setTabFocus(RPCConsole::TAB_INFO);
    showDebugWindow();
}

void BitcoinGUI::showConsole()
{
    rpcConsole->setTabFocus(RPCConsole::TAB_CONSOLE);
    showDebugWindow();
}

void BitcoinGUI::showGraph()
{
    rpcConsole->setTabFocus(RPCConsole::TAB_GRAPH);
    showDebugWindow();
}

void BitcoinGUI::showPeers()
{
    rpcConsole->setTabFocus(RPCConsole::TAB_PEERS);
    showDebugWindow();
}

void BitcoinGUI::showRepair()
{
    rpcConsole->setTabFocus(RPCConsole::TAB_REPAIR);
    showDebugWindow();
}

void BitcoinGUI::showConfEditor()
{
    GUIUtil::openConfigfile();
}

void BitcoinGUI::showMNConfEditor()
{
    GUIUtil::openMNConfigfile();
}

void BitcoinGUI::showBackups()
{
    GUIUtil::showBackups();
}

void BitcoinGUI::showHelpMessageClicked()
{
    helpMessageDialog->show();
}

void BitcoinGUI::showPrivateSendHelpClicked()
{
    if(!clientModel)
        return;

    HelpMessageDialog dlg(this, HelpMessageDialog::pshelp);
    dlg.exec();
=======
    if (!clientModel)
        return;

    HelpMessageDialog dlg(this, true);
    dlg.exec();
}

void BitcoinGUI::showHelpMessageClicked()
{
    HelpMessageDialog* help = new HelpMessageDialog(this, false);
    help->setAttribute(Qt::WA_DeleteOnClose);
    help->show();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

#ifdef ENABLE_WALLET
void BitcoinGUI::openClicked()
{
    OpenURIDialog dlg(this);
<<<<<<< HEAD
    if(dlg.exec())
    {
        Q_EMIT receivedURI(dlg.getURI());
=======
    if (dlg.exec()) {
        emit receivedURI(dlg.getURI());
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }
}

void BitcoinGUI::gotoOverviewPage()
{
    overviewAction->setChecked(true);
    if (walletFrame) walletFrame->gotoOverviewPage();
}

void BitcoinGUI::gotoHistoryPage()
{
    historyAction->setChecked(true);
    if (walletFrame) walletFrame->gotoHistoryPage();
}

<<<<<<< HEAD
=======
void BitcoinGUI::gotoTradingPage()
{
    tradingAction->setChecked(true);
    if (walletFrame) walletFrame->gotoTradingPage();
}

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
void BitcoinGUI::gotoMasternodePage()
{
    QSettings settings;
    if (settings.value("fShowMasternodesTab").toBool()) {
        masternodeAction->setChecked(true);
        if (walletFrame) walletFrame->gotoMasternodePage();
    }
}

void BitcoinGUI::gotoReceiveCoinsPage()
{
    receiveCoinsAction->setChecked(true);
    if (walletFrame) walletFrame->gotoReceiveCoinsPage();
}

void BitcoinGUI::gotoSendCoinsPage(QString addr)
{
    sendCoinsAction->setChecked(true);
    if (walletFrame) walletFrame->gotoSendCoinsPage(addr);
}

void BitcoinGUI::gotoSignMessageTab(QString addr)
{
    if (walletFrame) walletFrame->gotoSignMessageTab(addr);
}

void BitcoinGUI::gotoVerifyMessageTab(QString addr)
{
    if (walletFrame) walletFrame->gotoVerifyMessageTab(addr);
}
<<<<<<< HEAD
#endif // ENABLE_WALLET

void BitcoinGUI::updateNetworkState()
{
    int count = clientModel->getNumConnections();
    QString icon;
    QString theme = GUIUtil::getThemeName();
    switch(count)
    {
    case 0: icon = ":/icons/" + theme + "/connect_0"; break;
    case 1: case 2: case 3: icon = ":/icons/" + theme + "/connect_1"; break;
    case 4: case 5: case 6: icon = ":/icons/" + theme + "/connect_2"; break;
    case 7: case 8: case 9: icon = ":/icons/" + theme + "/connect_3"; break;
    default: icon = ":/icons/" + theme + "/connect_4"; break;
    }

    if (clientModel->getNetworkActive()) {
        labelConnectionsIcon->setToolTip(tr("%n active connection(s) to GelCoin network", "", count));
    } else {
        labelConnectionsIcon->setToolTip(tr("Network activity disabled"));
        icon = ":/icons/" + theme + "/network_disabled";
    }

    labelConnectionsIcon->setPixmap(platformStyle->SingleColorIcon(icon).pixmap(STATUSBAR_ICONSIZE,STATUSBAR_ICONSIZE));
}

void BitcoinGUI::setNumConnections(int count)
{
    updateNetworkState();
}

void BitcoinGUI::setNetworkActive(bool networkActive)
{
    updateNetworkState();
}

void BitcoinGUI::updateHeadersSyncProgressLabel()
{
    int64_t headersTipTime = clientModel->getHeaderTipTime();
    int headersTipHeight = clientModel->getHeaderTipHeight();
    int estHeadersLeft = (GetTime() - headersTipTime) / Params().GetConsensus().nPowTargetSpacing;
    if (estHeadersLeft > HEADER_HEIGHT_DELTA_SYNC)
        progressBarLabel->setText(tr("Syncing Headers (%1%)...").arg(QString::number(100.0 / (headersTipHeight+estHeadersLeft)*headersTipHeight, 'f', 1)));
}

void BitcoinGUI::setNumBlocks(int count, const QDateTime& blockDate, double nVerificationProgress, bool header)
{
    if (modalOverlay)
    {
        if (header)
            modalOverlay->setKnownBestHeight(count, blockDate);
        else
            modalOverlay->tipUpdate(count, blockDate, nVerificationProgress);
    }
=======

void BitcoinGUI::gotoBip38Tool()
{
    if (walletFrame) walletFrame->gotoBip38Tool();
}

void BitcoinGUI::gotoMultiSendDialog()
{
    multiSendAction->setChecked(true);
    if (walletFrame)
        walletFrame->gotoMultiSendDialog();
}
void BitcoinGUI::gotoBlockExplorerPage()
{
    if (walletFrame) walletFrame->gotoBlockExplorerPage();
}

#endif // ENABLE_WALLET

void BitcoinGUI::setNumConnections(int count)
{
    QString icon;
    switch (count) {
    case 0:
        icon = ":/icons/connect_0";
        break;
    case 1:
    case 2:
    case 3:
        icon = ":/icons/connect_1";
        break;
    case 4:
    case 5:
    case 6:
        icon = ":/icons/connect_2";
        break;
    case 7:
    case 8:
    case 9:
        icon = ":/icons/connect_3";
        break;
    default:
        icon = ":/icons/connect_4";
        break;
    }
    QIcon connectionItem = QIcon(icon).pixmap(STATUSBAR_ICONSIZE, STATUSBAR_ICONSIZE);
    labelConnectionsIcon->setIcon(connectionItem);
    labelConnectionsIcon->setToolTip(tr("%n active connection(s) to LUX network", "", count));
}

void BitcoinGUI::setNumBlocks(int count)
{
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    if (!clientModel)
        return;

    // Prevent orphan statusbar messages (e.g. hover Quit in main menu, wait until chain-sync starts -> garbelled text)
    statusBar()->clearMessage();

    // Acquire current block source
    enum BlockSource blockSource = clientModel->getBlockSource();
    switch (blockSource) {
<<<<<<< HEAD
        case BLOCK_SOURCE_NETWORK:
            if (header) {
                updateHeadersSyncProgressLabel();
                return;
            }
            progressBarLabel->setText(tr("Synchronizing with network..."));
            updateHeadersSyncProgressLabel();
            break;
        case BLOCK_SOURCE_DISK:
            if (header) {
                progressBarLabel->setText(tr("Indexing blocks on disk..."));
            } else {
                progressBarLabel->setText(tr("Processing blocks on disk..."));
            }
            break;
        case BLOCK_SOURCE_REINDEX:
            progressBarLabel->setText(tr("Reindexing blocks on disk..."));
            break;
        case BLOCK_SOURCE_NONE:
            if (header) {
                return;
            }
            progressBarLabel->setText(tr("Connecting to peers..."));
            break;
=======
    case BLOCK_SOURCE_NETWORK:
        progressBarLabel->setText(tr("Synchronizing with network..."));
        break;
    case BLOCK_SOURCE_DISK:
        progressBarLabel->setText(tr("Importing blocks from disk..."));
        break;
    case BLOCK_SOURCE_REINDEX:
        progressBarLabel->setText(tr("Reindexing blocks on disk..."));
        break;
    case BLOCK_SOURCE_NONE:
        // Case: not Importing, not Reindexing and no network connection
        progressBarLabel->setText(tr("No block source available..."));
        break;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }

    QString tooltip;

<<<<<<< HEAD
    QDateTime currentDate = QDateTime::currentDateTime();
    qint64 secs = blockDate.secsTo(currentDate);

    tooltip = tr("Processed %n block(s) of transaction history.", "", count);

    // Set icon state: spinning if catching up, tick otherwise
    QString theme = GUIUtil::getThemeName();

#ifdef ENABLE_WALLET
    if (walletFrame)
    {
        if(secs < 25*60) // 90*60 in bitcoin
        {
            modalOverlay->showHide(true, true);
            // TODO instead of hiding it forever, we should add meaningful information about MN sync to the overlay
            modalOverlay->hideForever();
        }
        else
        {
            modalOverlay->showHide();
        }
    }
#endif // ENABLE_WALLET

    if(!masternodeSync.IsBlockchainSynced())
    {
        QString timeBehindText = GUIUtil::formatNiceTimeOffset(secs);
=======
    QDateTime lastBlockDate = clientModel->getLastBlockDate();
    QDateTime currentDate = QDateTime::currentDateTime();
    int secs = lastBlockDate.secsTo(currentDate);

    tooltip = tr("Processed %n blocks of transaction history.", "", count);

    // Set icon state: spinning if catching up, tick otherwise
    if (secs < 25*60) { // 90*60 for bitcoin but we are 4x times faster
#ifdef ENABLE_WALLET
        if (walletFrame)
            walletFrame->showOutOfSyncWarning(false);
#endif // ENABLE_WALLET
    } else {
        // Represent time from last generated block in human readable text
        QString timeBehindText;
        const int HOUR_IN_SECONDS = 60 * 60;
        const int DAY_IN_SECONDS = 24 * 60 * 60;
        const int WEEK_IN_SECONDS = 7 * 24 * 60 * 60;
        const int YEAR_IN_SECONDS = 31556952; // Average length of year in Gregorian calendar
        if (secs < 2 * DAY_IN_SECONDS) {
            timeBehindText = tr("%n hour(s)", "", secs / HOUR_IN_SECONDS);
        } else if (secs < 2 * WEEK_IN_SECONDS) {
            timeBehindText = tr("%n day(s)", "", secs / DAY_IN_SECONDS);
        } else if (secs < YEAR_IN_SECONDS) {
            timeBehindText = tr("%n week(s)", "", secs / WEEK_IN_SECONDS);
        } else {
            int years = secs / YEAR_IN_SECONDS;
            int remainder = secs % YEAR_IN_SECONDS;
            timeBehindText = tr("%1 and %2").arg(tr("%n year(s)", "", years)).arg(tr("%n week(s)", "", remainder / WEEK_IN_SECONDS));
        }
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

        progressBarLabel->setVisible(true);
        progressBar->setFormat(tr("%1 behind").arg(timeBehindText));
        progressBar->setMaximum(1000000000);
<<<<<<< HEAD
        progressBar->setValue(nVerificationProgress * 1000000000.0 + 0.5);
        progressBar->setVisible(true);

        tooltip = tr("Catching up...") + QString("<br>") + tooltip;
        if(count != prevBlocks)
        {
            labelBlocksIcon->setPixmap(platformStyle->SingleColorIcon(QString(
                ":/movies/spinner-%1").arg(spinnerFrame, 3, 10, QChar('0')))
                .pixmap(STATUSBAR_ICONSIZE, STATUSBAR_ICONSIZE));
=======
        progressBar->setValue(clientModel->getVerificationProgress() * 1000000000.0 + 0.5);
        progressBar->setVisible(true);

        tooltip = tr("Catching up...") + QString("<br>") + tooltip;
        if (count != prevBlocks) {
            labelBlocksIcon->setPixmap(QIcon(QString(
                                                 ":/movies/spinner-%1")
                                                 .arg(spinnerFrame, 3, 10, QChar('0')))
                                           .pixmap(STATUSBAR_ICONSIZE, STATUSBAR_ICONSIZE));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            spinnerFrame = (spinnerFrame + 1) % SPINNER_FRAMES;
        }
        prevBlocks = count;

#ifdef ENABLE_WALLET
<<<<<<< HEAD
        if(walletFrame)
        {
            walletFrame->showOutOfSyncWarning(true);
        }
=======
        if (walletFrame)
            walletFrame->showOutOfSyncWarning(true);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#endif // ENABLE_WALLET

        tooltip += QString("<br>");
        tooltip += tr("Last received block was generated %1 ago.").arg(timeBehindText);
        tooltip += QString("<br>");
        tooltip += tr("Transactions after this will not yet be visible.");
    }

    // Don't word-wrap this (fixed-width) tooltip
    tooltip = QString("<nobr>") + tooltip + QString("</nobr>");

    labelBlocksIcon->setToolTip(tooltip);
    progressBarLabel->setToolTip(tooltip);
    progressBar->setToolTip(tooltip);
}

<<<<<<< HEAD
void BitcoinGUI::setAdditionalDataSyncProgress(double nSyncProgress)
{
    if(!clientModel)
        return;

    // No additional data sync should be happening while blockchain is not synced, nothing to update
    if(!masternodeSync.IsBlockchainSynced())
        return;

    // Prevent orphan statusbar messages (e.g. hover Quit in main menu, wait until chain-sync starts -> garbelled text)
    statusBar()->clearMessage();

    QString tooltip;

    // Set icon state: spinning if catching up, tick otherwise
    QString theme = GUIUtil::getThemeName();

    QString strSyncStatus;
    tooltip = tr("Up to date") + QString(".<br>") + tooltip;

    if(masternodeSync.IsSynced()) {
        progressBarLabel->setVisible(false);
        progressBar->setVisible(false);
        labelBlocksIcon->setPixmap(QIcon(":/icons/" + theme + "/synced").pixmap(STATUSBAR_ICONSIZE, STATUSBAR_ICONSIZE));
    } else {

        labelBlocksIcon->setPixmap(platformStyle->SingleColorIcon(QString(
            ":/movies/spinner-%1").arg(spinnerFrame, 3, 10, QChar('0')))
            .pixmap(STATUSBAR_ICONSIZE, STATUSBAR_ICONSIZE));
        spinnerFrame = (spinnerFrame + 1) % SPINNER_FRAMES;

#ifdef ENABLE_WALLET
        if(walletFrame)
            walletFrame->showOutOfSyncWarning(false);
#endif // ENABLE_WALLET

        progressBar->setFormat(tr("Synchronizing additional data: %p%"));
        progressBar->setMaximum(1000000000);
        progressBar->setValue(nSyncProgress * 1000000000.0 + 0.5);
    }

    strSyncStatus = QString(masternodeSync.GetSyncStatus().c_str());
    progressBarLabel->setText(strSyncStatus);
    tooltip = strSyncStatus + QString("<br>") + tooltip;

    // Don't word-wrap this (fixed-width) tooltip
    tooltip = QString("<nobr>") + tooltip + QString("</nobr>");

    labelBlocksIcon->setToolTip(tooltip);
    progressBarLabel->setToolTip(tooltip);
    progressBar->setToolTip(tooltip);
}

void BitcoinGUI::message(const QString &title, const QString &message, unsigned int style, bool *ret)
{
    QString strTitle = tr("GelCoin"); // default title
=======
void BitcoinGUI::message(const QString& title, const QString& message, unsigned int style, bool* ret)
{
    QString strTitle = tr("LUX Core"); // default title
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    // Default to information icon
    int nMBoxIcon = QMessageBox::Information;
    int nNotifyIcon = Notificator::Information;

    QString msgType;

    // Prefer supplied title over style based title
    if (!title.isEmpty()) {
        msgType = title;
<<<<<<< HEAD
    }
    else {
=======
    } else {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        switch (style) {
        case CClientUIInterface::MSG_ERROR:
            msgType = tr("Error");
            break;
        case CClientUIInterface::MSG_WARNING:
            msgType = tr("Warning");
            break;
        case CClientUIInterface::MSG_INFORMATION:
            msgType = tr("Information");
            break;
        default:
            break;
        }
    }
<<<<<<< HEAD
    // Append title to "GelCoin - "
=======
    // Append title to "LUX - "
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    if (!msgType.isEmpty())
        strTitle += " - " + msgType;

    // Check for error/warning icon
    if (style & CClientUIInterface::ICON_ERROR) {
        nMBoxIcon = QMessageBox::Critical;
        nNotifyIcon = Notificator::Critical;
<<<<<<< HEAD
    }
    else if (style & CClientUIInterface::ICON_WARNING) {
=======
    } else if (style & CClientUIInterface::ICON_WARNING) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        nMBoxIcon = QMessageBox::Warning;
        nNotifyIcon = Notificator::Warning;
    }

    // Display message
    if (style & CClientUIInterface::MODAL) {
        // Check for buttons, use OK as default, if none was supplied
        QMessageBox::StandardButton buttons;
        if (!(buttons = (QMessageBox::StandardButton)(style & CClientUIInterface::BTN_MASK)))
            buttons = QMessageBox::Ok;

        showNormalIfMinimized();
        QMessageBox mBox((QMessageBox::Icon)nMBoxIcon, strTitle, message, buttons, this);
        int r = mBox.exec();
        if (ret != NULL)
            *ret = r == QMessageBox::Ok;
<<<<<<< HEAD
    }
    else
        notificator->notify((Notificator::Class)nNotifyIcon, strTitle, message);
}

void BitcoinGUI::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
#ifndef Q_OS_MAC // Ignored on Mac
    if(e->type() == QEvent::WindowStateChange)
    {
        if(clientModel && clientModel->getOptionsModel() && clientModel->getOptionsModel()->getMinimizeToTray())
        {
            QWindowStateChangeEvent *wsevt = static_cast<QWindowStateChangeEvent*>(e);
            if(!(wsevt->oldState() & Qt::WindowMinimized) && isMinimized())
            {
=======
    } else
        notificator->notify((Notificator::Class)nNotifyIcon, strTitle, message);
}

void BitcoinGUI::changeEvent(QEvent* e)
{
    QMainWindow::changeEvent(e);
#ifndef Q_OS_MAC // Ignored on Mac
    if (e->type() == QEvent::WindowStateChange) {
        if (clientModel && clientModel->getOptionsModel() && clientModel->getOptionsModel()->getMinimizeToTray()) {
            QWindowStateChangeEvent* wsevt = static_cast<QWindowStateChangeEvent*>(e);
            if (!(wsevt->oldState() & Qt::WindowMinimized) && isMinimized()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                QTimer::singleShot(0, this, SLOT(hide()));
                e->ignore();
            }
        }
    }
#endif
}

<<<<<<< HEAD
void BitcoinGUI::closeEvent(QCloseEvent *event)
{
#ifndef Q_OS_MAC // Ignored on Mac
    if(clientModel && clientModel->getOptionsModel())
    {
        if(!clientModel->getOptionsModel()->getMinimizeOnClose())
        {
            // close rpcConsole in case it was open to make some space for the shutdown window
            rpcConsole->close();

=======
void BitcoinGUI::closeEvent(QCloseEvent* event)
{
#ifndef Q_OS_MAC // Ignored on Mac
    if (clientModel && clientModel->getOptionsModel()) {
        if (!clientModel->getOptionsModel()->getMinimizeOnClose()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            QApplication::quit();
        }
    }
#endif
    QMainWindow::closeEvent(event);
}

<<<<<<< HEAD
void BitcoinGUI::showEvent(QShowEvent *event)
{
    // enable the debug window when the main window shows up
    openInfoAction->setEnabled(true);
    openRPCConsoleAction->setEnabled(true);
    openGraphAction->setEnabled(true);
    openPeersAction->setEnabled(true);
    openRepairAction->setEnabled(true);
    aboutAction->setEnabled(true);
    optionsAction->setEnabled(true);
}

#ifdef ENABLE_WALLET
void BitcoinGUI::incomingTransaction(const QString& date, int unit, const CAmount& amount, const QString& type, const QString& address, const QString& label)
{
    // On new transaction, make an info balloon
    QString msg = tr("Date: %1\n").arg(date) +
                  tr("Amount: %1\n").arg(BitcoinUnits::formatWithUnit(unit, amount, true)) +
                  tr("Type: %1\n").arg(type);
    if (!label.isEmpty())
        msg += tr("Label: %1\n").arg(label);
    else if (!address.isEmpty())
        msg += tr("Address: %1\n").arg(address);
    message((amount)<0 ? tr("Sent transaction") : tr("Incoming transaction"),
             msg, CClientUIInterface::MSG_INFORMATION);
}
#endif // ENABLE_WALLET

void BitcoinGUI::dragEnterEvent(QDragEnterEvent *event)
{
    // Accept only URIs
    if(event->mimeData()->hasUrls())
        event->acceptProposedAction();
}

void BitcoinGUI::dropEvent(QDropEvent *event)
{
    if(event->mimeData()->hasUrls())
    {
        Q_FOREACH(const QUrl &uri, event->mimeData()->urls())
        {
            Q_EMIT receivedURI(uri.toString());
=======
#ifdef ENABLE_WALLET
void BitcoinGUI::incomingTransaction(const QString& date, int unit, const CAmount& amount, const QString& type, const QString& address)
{
    // On new transaction, make an info balloon
    message((amount) < 0 ? (pwalletMain->fMultiSendNotify == true ? tr("Sent MultiSend transaction") : tr("Sent transaction")) : tr("Incoming transaction"),
        tr("Date: %1\n"
           "Amount: %2\n"
           "Type: %3\n"
           "Address: %4\n")
            .arg(date)
            .arg(BitcoinUnits::formatWithUnit(unit, amount, true))
            .arg(type)
            .arg(address),
        CClientUIInterface::MSG_INFORMATION);

    pwalletMain->fMultiSendNotify = false;
}
#endif // ENABLE_WALLET

void BitcoinGUI::dragEnterEvent(QDragEnterEvent* event)
{
    // Accept only URIs
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
}

void BitcoinGUI::dropEvent(QDropEvent* event)
{
    if (event->mimeData()->hasUrls()) {
        foreach (const QUrl& uri, event->mimeData()->urls()) {
            emit receivedURI(uri.toString());
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        }
    }
    event->acceptProposedAction();
}

<<<<<<< HEAD
bool BitcoinGUI::eventFilter(QObject *object, QEvent *event)
{
    // Catch status tip events
    if (event->type() == QEvent::StatusTip)
    {
=======
bool BitcoinGUI::eventFilter(QObject* object, QEvent* event)
{
    // Catch status tip events
    if (event->type() == QEvent::StatusTip) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        // Prevent adding text from setStatusTip(), if we currently use the status bar for displaying other stuff
        if (progressBarLabel->isVisible() || progressBar->isVisible())
            return true;
    }
    return QMainWindow::eventFilter(object, event);
}

<<<<<<< HEAD
=======
void BitcoinGUI::setStakingStatus()
{
    if (pwalletMain)
        fMultiSend = pwalletMain->isMultiSendEnabled();

    if (nLastCoinStakeSearchInterval) {
        labelStakingIcon->show();
        labelStakingIcon->setPixmap(QIcon(":/icons/staking_active").pixmap(STATUSBAR_ICONSIZE, STATUSBAR_ICONSIZE));
        labelStakingIcon->setToolTip(tr("Staking is active\n MultiSend: %1").arg(fMultiSend ? tr("Active") : tr("Not Active")));
    } else {
        labelStakingIcon->show();
        labelStakingIcon->setPixmap(QIcon(":/icons/staking_inactive").pixmap(STATUSBAR_ICONSIZE, STATUSBAR_ICONSIZE));
        labelStakingIcon->setToolTip(tr("Staking is not active\n MultiSend: %1").arg(fMultiSend ? tr("Active") : tr("Not Active")));
    }
}

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#ifdef ENABLE_WALLET
bool BitcoinGUI::handlePaymentRequest(const SendCoinsRecipient& recipient)
{
    // URI has to be valid
<<<<<<< HEAD
    if (walletFrame && walletFrame->handlePaymentRequest(recipient))
    {
=======
    if (walletFrame && walletFrame->handlePaymentRequest(recipient)) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        showNormalIfMinimized();
        gotoSendCoinsPage();
        return true;
    }
    return false;
}

<<<<<<< HEAD
void BitcoinGUI::setHDStatus(int hdEnabled)
{
    QString theme = GUIUtil::getThemeName();

    labelWalletHDStatusIcon->setPixmap(platformStyle->SingleColorIcon(hdEnabled ? ":/icons/" + theme + "/hd_enabled" : ":/icons/" + theme + "/hd_disabled").pixmap(STATUSBAR_ICONSIZE,STATUSBAR_ICONSIZE));
    labelWalletHDStatusIcon->setToolTip(hdEnabled ? tr("HD key generation is <b>enabled</b>") : tr("HD key generation is <b>disabled</b>"));

    // eventually disable the QLabel to set its opacity to 50%
    labelWalletHDStatusIcon->setEnabled(hdEnabled);
}

void BitcoinGUI::setEncryptionStatus(int status)
{
    QString theme = GUIUtil::getThemeName();
    switch(status)
    {
=======
void BitcoinGUI::setEncryptionStatus(int status)
{
    switch (status) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    case WalletModel::Unencrypted:
        labelEncryptionIcon->hide();
        encryptWalletAction->setChecked(false);
        changePassphraseAction->setEnabled(false);
        unlockWalletAction->setVisible(false);
        lockWalletAction->setVisible(false);
        encryptWalletAction->setEnabled(true);
        break;
    case WalletModel::Unlocked:
        labelEncryptionIcon->show();
<<<<<<< HEAD
        labelEncryptionIcon->setPixmap(QIcon(":/icons/" + theme + "/lock_open").pixmap(STATUSBAR_ICONSIZE,STATUSBAR_ICONSIZE));
=======
        labelEncryptionIcon->setPixmap(QIcon(":/icons/lock_open").pixmap(STATUSBAR_ICONSIZE, STATUSBAR_ICONSIZE));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        labelEncryptionIcon->setToolTip(tr("Wallet is <b>encrypted</b> and currently <b>unlocked</b>"));
        encryptWalletAction->setChecked(true);
        changePassphraseAction->setEnabled(true);
        unlockWalletAction->setVisible(false);
        lockWalletAction->setVisible(true);
        encryptWalletAction->setEnabled(false); // TODO: decrypt currently not supported
        break;
<<<<<<< HEAD
    case WalletModel::UnlockedForMixingOnly:
        labelEncryptionIcon->show();
        labelEncryptionIcon->setPixmap(QIcon(":/icons/" + theme + "/lock_open").pixmap(STATUSBAR_ICONSIZE,STATUSBAR_ICONSIZE));
        labelEncryptionIcon->setToolTip(tr("Wallet is <b>encrypted</b> and currently <b>unlocked</b> for mixing only"));
=======
    case WalletModel::UnlockedForAnonymizationOnly:
        labelEncryptionIcon->show();
        labelEncryptionIcon->setPixmap(QIcon(":/icons/lock_open").pixmap(STATUSBAR_ICONSIZE, STATUSBAR_ICONSIZE));
        labelEncryptionIcon->setToolTip(tr("Wallet is <b>encrypted</b> and currently <b>unlocked</b> for anonimization and staking only"));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        encryptWalletAction->setChecked(true);
        changePassphraseAction->setEnabled(true);
        unlockWalletAction->setVisible(true);
        lockWalletAction->setVisible(true);
        encryptWalletAction->setEnabled(false); // TODO: decrypt currently not supported
        break;
    case WalletModel::Locked:
        labelEncryptionIcon->show();
<<<<<<< HEAD
        labelEncryptionIcon->setPixmap(QIcon(":/icons/" + theme + "/lock_closed").pixmap(STATUSBAR_ICONSIZE,STATUSBAR_ICONSIZE));
=======
        labelEncryptionIcon->setPixmap(QIcon(":/icons/lock_closed").pixmap(STATUSBAR_ICONSIZE, STATUSBAR_ICONSIZE));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        labelEncryptionIcon->setToolTip(tr("Wallet is <b>encrypted</b> and currently <b>locked</b>"));
        encryptWalletAction->setChecked(true);
        changePassphraseAction->setEnabled(true);
        unlockWalletAction->setVisible(true);
        lockWalletAction->setVisible(false);
        encryptWalletAction->setEnabled(false); // TODO: decrypt currently not supported
        break;
    }
}
#endif // ENABLE_WALLET

void BitcoinGUI::showNormalIfMinimized(bool fToggleHidden)
{
<<<<<<< HEAD
    if(!clientModel)
        return;

    // activateWindow() (sometimes) helps with keyboard focus on Windows
    if (isHidden())
    {
        show();
        activateWindow();
    }
    else if (isMinimized())
    {
        showNormal();
        activateWindow();
    }
    else if (GUIUtil::isObscured(this))
    {
        raise();
        activateWindow();
    }
    else if(fToggleHidden)
=======
    if (!clientModel)
        return;

    // activateWindow() (sometimes) helps with keyboard focus on Windows
    if (isHidden()) {
        show();
        activateWindow();
    } else if (isMinimized()) {
        showNormal();
        activateWindow();
    } else if (GUIUtil::isObscured(this)) {
        raise();
        activateWindow();
    } else if (fToggleHidden)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        hide();
}

void BitcoinGUI::toggleHidden()
{
    showNormalIfMinimized(true);
}

void BitcoinGUI::detectShutdown()
{
<<<<<<< HEAD
    if (ShutdownRequested())
    {
        if(rpcConsole)
=======
    if (ShutdownRequested()) {
        if (rpcConsole)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            rpcConsole->hide();
        qApp->quit();
    }
}

<<<<<<< HEAD
void BitcoinGUI::showProgress(const QString &title, int nProgress)
{
    if (nProgress == 0)
    {
=======
void BitcoinGUI::showProgress(const QString& title, int nProgress)
{
    if (nProgress == 0) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        progressDialog = new QProgressDialog(title, "", 0, 100);
        progressDialog->setWindowModality(Qt::ApplicationModal);
        progressDialog->setMinimumDuration(0);
        progressDialog->setCancelButton(0);
        progressDialog->setAutoClose(false);
        progressDialog->setValue(0);
<<<<<<< HEAD
    }
    else if (nProgress == 100)
    {
        if (progressDialog)
        {
            progressDialog->close();
            progressDialog->deleteLater();
        }
    }
    else if (progressDialog)
        progressDialog->setValue(nProgress);
}

void BitcoinGUI::setTrayIconVisible(bool fHideTrayIcon)
{
    if (trayIcon)
    {
        trayIcon->setVisible(!fHideTrayIcon);
    }
}

void BitcoinGUI::showModalOverlay()
{
    if (modalOverlay && (progressBar->isVisible() || modalOverlay->isLayerVisible()))
        modalOverlay->toggleVisibility();
}

static bool ThreadSafeMessageBox(BitcoinGUI *gui, const std::string& message, const std::string& caption, unsigned int style)
=======
    } else if (nProgress == 100) {
        if (progressDialog) {
            progressDialog->close();
            progressDialog->deleteLater();
        }
    } else if (progressDialog)
        progressDialog->setValue(nProgress);
}

static bool ThreadSafeMessageBox(BitcoinGUI* gui, const std::string& message, const std::string& caption, unsigned int style)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    bool modal = (style & CClientUIInterface::MODAL);
    // The SECURE flag has no effect in the Qt GUI.
    // bool secure = (style & CClientUIInterface::SECURE);
    style &= ~CClientUIInterface::SECURE;
    bool ret = false;
    // In case of modal message, use blocking connection to wait for user to click a button
    QMetaObject::invokeMethod(gui, "message",
<<<<<<< HEAD
                               modal ? GUIUtil::blockingGUIThreadConnection() : Qt::QueuedConnection,
                               Q_ARG(QString, QString::fromStdString(caption)),
                               Q_ARG(QString, QString::fromStdString(message)),
                               Q_ARG(unsigned int, style),
                               Q_ARG(bool*, &ret));
=======
        modal ? GUIUtil::blockingGUIThreadConnection() : Qt::QueuedConnection,
        Q_ARG(QString, QString::fromStdString(caption)),
        Q_ARG(QString, QString::fromStdString(message)),
        Q_ARG(unsigned int, style),
        Q_ARG(bool*, &ret));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    return ret;
}

void BitcoinGUI::subscribeToCoreSignals()
{
    // Connect signals to client
    uiInterface.ThreadSafeMessageBox.connect(boost::bind(ThreadSafeMessageBox, this, _1, _2, _3));
<<<<<<< HEAD
    uiInterface.ThreadSafeQuestion.connect(boost::bind(ThreadSafeMessageBox, this, _1, _3, _4));
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

void BitcoinGUI::unsubscribeFromCoreSignals()
{
    // Disconnect signals from client
    uiInterface.ThreadSafeMessageBox.disconnect(boost::bind(ThreadSafeMessageBox, this, _1, _2, _3));
<<<<<<< HEAD
    uiInterface.ThreadSafeQuestion.disconnect(boost::bind(ThreadSafeMessageBox, this, _1, _3, _4));
}

void BitcoinGUI::toggleNetworkActive()
{
    if (clientModel) {
        clientModel->setNetworkActive(!clientModel->getNetworkActive());
    }
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

/** Get restart command-line parameters and request restart */
void BitcoinGUI::handleRestart(QStringList args)
{
    if (!ShutdownRequested())
<<<<<<< HEAD
        Q_EMIT requestedRestart(args);
}

UnitDisplayStatusBarControl::UnitDisplayStatusBarControl(const PlatformStyle *platformStyle) :
    optionsModel(0),
    menu(0)
{
    createContextMenu();
    setToolTip(tr("Unit to show amounts in. Click to select another unit."));
    QList<BitcoinUnits::Unit> units = BitcoinUnits::availableUnits();
    int max_width = 0;
    const QFontMetrics fm(font());
    Q_FOREACH (const BitcoinUnits::Unit unit, units)
    {
        max_width = qMax(max_width, fm.width(BitcoinUnits::name(unit)));
    }
    setMinimumSize(max_width, 0);
    setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    setStyleSheet(QString("QLabel { color : %1 }").arg(platformStyle->SingleColor().name()));
}

/** So that it responds to button clicks */
void UnitDisplayStatusBarControl::mousePressEvent(QMouseEvent *event)
=======
        emit requestedRestart(args);
}

UnitDisplayStatusBarControl::UnitDisplayStatusBarControl() : optionsModel(0),
                                                             menu(0)
{
    createContextMenu();
    setToolTip(tr("Unit to show amounts in. Click to select another unit."));
}

/** So that it responds to button clicks */
void UnitDisplayStatusBarControl::mousePressEvent(QMouseEvent* event)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    onDisplayUnitsClicked(event->pos());
}

/** Creates context menu, its actions, and wires up all the relevant signals for mouse events. */
void UnitDisplayStatusBarControl::createContextMenu()
{
<<<<<<< HEAD
    menu = new QMenu(this);
    Q_FOREACH(BitcoinUnits::Unit u, BitcoinUnits::availableUnits())
    {
        QAction *menuAction = new QAction(QString(BitcoinUnits::name(u)), this);
        menuAction->setData(QVariant(u));
        menu->addAction(menuAction);
    }
    connect(menu,SIGNAL(triggered(QAction*)),this,SLOT(onMenuSelection(QAction*)));
}

/** Lets the control know about the Options Model (and its signals) */
void UnitDisplayStatusBarControl::setOptionsModel(OptionsModel *optionsModel)
{
    if (optionsModel)
    {
        this->optionsModel = optionsModel;

        // be aware of a display unit change reported by the OptionsModel object.
        connect(optionsModel,SIGNAL(displayUnitChanged(int)),this,SLOT(updateDisplayUnit(int)));
=======
    menu = new QMenu();
    foreach (BitcoinUnits::Unit u, BitcoinUnits::availableUnits()) {
        QAction* menuAction = new QAction(QString(BitcoinUnits::name(u)), this);
        menuAction->setData(QVariant(u));
        menu->addAction(menuAction);
    }
    connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(onMenuSelection(QAction*)));
}

/** Lets the control know about the Options Model (and its signals) */
void UnitDisplayStatusBarControl::setOptionsModel(OptionsModel* optionsModel)
{
    if (optionsModel) {
        this->optionsModel = optionsModel;

        // be aware of a display unit change reported by the OptionsModel object.
        connect(optionsModel, SIGNAL(displayUnitChanged(int)), this, SLOT(updateDisplayUnit(int)));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

        // initialize the display units label with the current value in the model.
        updateDisplayUnit(optionsModel->getDisplayUnit());
    }
}

/** When Display Units are changed on OptionsModel it will refresh the display text of the control on the status bar */
void UnitDisplayStatusBarControl::updateDisplayUnit(int newUnits)
{
<<<<<<< HEAD
    setText(BitcoinUnits::name(newUnits));
=======
    if (Params().NetworkID() == CBaseChainParams::MAIN) {
        setPixmap(QIcon(":/icons/unit_" + BitcoinUnits::id(newUnits)).pixmap(39, STATUSBAR_ICONSIZE));
    } else {
        setPixmap(QIcon(":/icons/unit_t" + BitcoinUnits::id(newUnits)).pixmap(39, STATUSBAR_ICONSIZE));
    }
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

/** Shows context menu with Display Unit options by the mouse coordinates */
void UnitDisplayStatusBarControl::onDisplayUnitsClicked(const QPoint& point)
{
    QPoint globalPos = mapToGlobal(point);
    menu->exec(globalPos);
}

/** Tells underlying optionsModel to update its current display unit. */
void UnitDisplayStatusBarControl::onMenuSelection(QAction* action)
{
<<<<<<< HEAD
    if (action)
    {
=======
    if (action) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        optionsModel->setDisplayUnit(action->data());
    }
}
