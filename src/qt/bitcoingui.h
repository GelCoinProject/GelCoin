<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_BITCOINGUI_H
#define BITCOIN_QT_BITCOINGUI_H

#if defined(HAVE_CONFIG_H)
<<<<<<< HEAD
#include "config/gelcoin-config.h"
=======
#include "config/lux-config.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#endif

#include "amount.h"

#include <QLabel>
#include <QMainWindow>
#include <QMap>
#include <QMenu>
#include <QPoint>
#include <QPushButton>
#include <QSystemTrayIcon>

class ClientModel;
class NetworkStyle;
class Notificator;
class OptionsModel;
<<<<<<< HEAD
class PlatformStyle;
=======
class BlockExplorer;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
class RPCConsole;
class SendCoinsRecipient;
class UnitDisplayStatusBarControl;
class WalletFrame;
class WalletModel;
<<<<<<< HEAD
class HelpMessageDialog;
class ModalOverlay;
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
class MasternodeList;

class CWallet;

QT_BEGIN_NAMESPACE
class QAction;
class QProgressBar;
class QProgressDialog;
QT_END_NAMESPACE

/**
  Bitcoin GUI main class. This class represents the main window of the Bitcoin UI. It communicates with both the client and
  wallet models to give the user an up-to-date view of the current core state.
*/
class BitcoinGUI : public QMainWindow
{
    Q_OBJECT

public:
    static const QString DEFAULT_WALLET;
<<<<<<< HEAD
    static const std::string DEFAULT_UIPLATFORM;

    explicit BitcoinGUI(const PlatformStyle *platformStyle, const NetworkStyle *networkStyle, QWidget *parent = 0);
=======

    explicit BitcoinGUI(const NetworkStyle* networkStyle, QWidget* parent = 0);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    ~BitcoinGUI();

    /** Set the client model.
        The client model represents the part of the core that communicates with the P2P network, and is wallet-agnostic.
    */
<<<<<<< HEAD
    void setClientModel(ClientModel *clientModel);
=======
    void setClientModel(ClientModel* clientModel);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

#ifdef ENABLE_WALLET
    /** Set the wallet model.
        The wallet model represents a bitcoin wallet, and offers access to the list of transactions, address book and sending
        functionality.
    */
<<<<<<< HEAD
    bool addWallet(const QString& name, WalletModel *walletModel);
=======
    bool addWallet(const QString& name, WalletModel* walletModel);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    bool setCurrentWallet(const QString& name);
    void removeAllWallets();
#endif // ENABLE_WALLET
    bool enableWallet;
<<<<<<< HEAD

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    bool eventFilter(QObject *object, QEvent *event);

private:
    ClientModel *clientModel;
    WalletFrame *walletFrame;

    UnitDisplayStatusBarControl *unitDisplayControl;
    QLabel *labelEncryptionIcon;
    QLabel *labelWalletHDStatusIcon;
    QLabel *labelConnectionsIcon;
    QLabel *labelBlocksIcon;
    QLabel *progressBarLabel;
    QProgressBar *progressBar;
    QProgressDialog *progressDialog;

    QMenuBar *appMenuBar;
    QAction *overviewAction;
    QAction *historyAction;
    QAction *masternodeAction;
    QAction *quitAction;
    QAction *sendCoinsAction;
    QAction *sendCoinsMenuAction;
    QAction *usedSendingAddressesAction;
    QAction *usedReceivingAddressesAction;
    QAction *signMessageAction;
    QAction *verifyMessageAction;
    QAction *aboutAction;
    QAction *receiveCoinsAction;
    QAction *receiveCoinsMenuAction;
    QAction *optionsAction;
    QAction *toggleHideAction;
    QAction *encryptWalletAction;
    QAction *backupWalletAction;
    QAction *changePassphraseAction;
    QAction *unlockWalletAction;
    QAction *lockWalletAction;
    QAction *aboutQtAction;
    QAction *openInfoAction;
    QAction *openRPCConsoleAction;
    QAction *openGraphAction;
    QAction *openPeersAction;
    QAction *openRepairAction;
    QAction *openConfEditorAction;
    QAction *openMNConfEditorAction;
    QAction *showBackupsAction;
    QAction *openAction;
    QAction *showHelpMessageAction;
    QAction *showPrivateSendHelpAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QMenu *dockIconMenu;
    Notificator *notificator;
    RPCConsole *rpcConsole;
    HelpMessageDialog *helpMessageDialog;
    ModalOverlay *modalOverlay;
=======
    bool fMultiSend = false;

protected:
    void changeEvent(QEvent* e);
    void closeEvent(QCloseEvent* event);
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent* event);
    bool eventFilter(QObject* object, QEvent* event);

private:
    ClientModel* clientModel;
    WalletFrame* walletFrame;

    UnitDisplayStatusBarControl* unitDisplayControl;
    QLabel* labelStakingIcon;
    QLabel* labelEncryptionIcon;
    QPushButton* labelConnectionsIcon;
    QLabel* labelBlocksIcon;
    QLabel* progressBarLabel;
    QProgressBar* progressBar;
    QProgressDialog* progressDialog;

    QMenuBar* appMenuBar;
    QAction* overviewAction;
    QAction* historyAction;
    QAction* tradingAction;
    QAction* masternodeAction;
    QAction* quitAction;
    QAction* sendCoinsAction;
    QAction* usedSendingAddressesAction;
    QAction* usedReceivingAddressesAction;
    QAction* signMessageAction;
    QAction* verifyMessageAction;
    QAction* bip38ToolAction;
    QAction* aboutAction;
    QAction* receiveCoinsAction;
    QAction* optionsAction;
    QAction* toggleHideAction;
    QAction* encryptWalletAction;
    QAction* backupWalletAction;
    QAction* changePassphraseAction;
    QAction* unlockWalletAction;
    QAction* lockWalletAction;
    QAction* aboutQtAction;
    QAction* openInfoAction;
    QAction* openRPCConsoleAction;
    QAction* openNetworkAction;
    QAction* openPeersAction;
    QAction* openRepairAction;
    QAction* openConfEditorAction;
    QAction* openMNConfEditorAction;
    QAction* showBackupsAction;
    QAction* openAction;
    QAction* openBlockExplorerAction;
    QAction* showHelpMessageAction;
    QAction* multiSendAction;

    QSystemTrayIcon* trayIcon;
    QMenu* trayIconMenu;
    Notificator* notificator;
    RPCConsole* rpcConsole;
    BlockExplorer* explorerWindow;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    /** Keep track of previous number of blocks, to detect progress */
    int prevBlocks;
    int spinnerFrame;

<<<<<<< HEAD
    const PlatformStyle *platformStyle;

    /** Create the main UI actions. */
    void createActions();
=======
    /** Create the main UI actions. */
    void createActions(const NetworkStyle* networkStyle);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    /** Create the menu bar and sub-menus. */
    void createMenuBar();
    /** Create the toolbars */
    void createToolBars();
    /** Create system tray icon and notification */
<<<<<<< HEAD
    void createTrayIcon(const NetworkStyle *networkStyle);
    /** Create system tray menu (or setup the dock menu) */
    void createIconMenu(QMenu *pmenu);
=======
    void createTrayIcon(const NetworkStyle* networkStyle);
    /** Create system tray menu (or setup the dock menu) */
    void createTrayIconMenu();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    /** Enable or disable all wallet-related actions */
    void setWalletActionsEnabled(bool enabled);

    /** Connect core signals to GUI client */
    void subscribeToCoreSignals();
    /** Disconnect core signals from GUI client */
    void unsubscribeFromCoreSignals();

<<<<<<< HEAD
    /** Update UI with latest network info from model. */
    void updateNetworkState();

    void updateHeadersSyncProgressLabel();

Q_SIGNALS:
    /** Signal raised when a URI was entered or dragged to the GUI */
    void receivedURI(const QString &uri);
    /** Restart handling */
    void requestedRestart(QStringList args);

public Q_SLOTS:
    /** Set number of connections shown in the UI */
    void setNumConnections(int count);
    /** Set network state shown in the UI */
    void setNetworkActive(bool networkActive);
    /** Get restart command-line parameters and request restart */
    void handleRestart(QStringList args);
    /** Set number of blocks and last block date shown in the UI */
    void setNumBlocks(int count, const QDateTime& blockDate, double nVerificationProgress, bool headers);
    /** Set additional data sync status shown in the UI */
    void setAdditionalDataSyncProgress(double nSyncProgress);
=======
signals:
    /** Signal raised when a URI was entered or dragged to the GUI */
    void receivedURI(const QString& uri);
    /** Restart handling */
    void requestedRestart(QStringList args);

public slots:
    /** Set number of connections shown in the UI */
    void setNumConnections(int count);
    /** Set number of blocks shown in the UI */
    void setNumBlocks(int count);
    /** Get restart command-line parameters and request restart */
    void handleRestart(QStringList args);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    /** Notify the user of an event from the core network or transaction handling code.
       @param[in] title     the message box / notification title
       @param[in] message   the displayed text
       @param[in] style     modality and style definitions (icon and used buttons - buttons only for message boxes)
                            @see CClientUIInterface::MessageBoxFlags
       @param[in] ret       pointer to a bool that will be modified to whether Ok was clicked (modal only)
    */
<<<<<<< HEAD
    void message(const QString &title, const QString &message, unsigned int style, bool *ret = NULL);

#ifdef ENABLE_WALLET
    /** Set the hd-enabled status as shown in the UI.
     @param[in] status            current hd enabled status
     @see WalletModel::EncryptionStatus
     */
    void setHDStatus(int hdEnabled);

=======
    void message(const QString& title, const QString& message, unsigned int style, bool* ret = NULL);

    void setStakingStatus();

#ifdef ENABLE_WALLET
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    /** Set the encryption status as shown in the UI.
       @param[in] status            current encryption status
       @see WalletModel::EncryptionStatus
    */
    void setEncryptionStatus(int status);

    bool handlePaymentRequest(const SendCoinsRecipient& recipient);

    /** Show incoming transaction notification for new transactions. */
<<<<<<< HEAD
    void incomingTransaction(const QString& date, int unit, const CAmount& amount, const QString& type, const QString& address, const QString& label);
#endif // ENABLE_WALLET

private Q_SLOTS:
=======
    void incomingTransaction(const QString& date, int unit, const CAmount& amount, const QString& type, const QString& address);
#endif // ENABLE_WALLET

private slots:
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#ifdef ENABLE_WALLET
    /** Switch to overview (home) page */
    void gotoOverviewPage();
    /** Switch to history (transactions) page */
    void gotoHistoryPage();
<<<<<<< HEAD
=======
    /** Switch to trading page */
    void gotoTradingPage();
    /** Switch to Explorer Page */
    void gotoBlockExplorerPage();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    /** Switch to masternode page */
    void gotoMasternodePage();
    /** Switch to receive coins page */
    void gotoReceiveCoinsPage();
    /** Switch to send coins page */
    void gotoSendCoinsPage(QString addr = "");

    /** Show Sign/Verify Message dialog and switch to sign message tab */
    void gotoSignMessageTab(QString addr = "");
    /** Show Sign/Verify Message dialog and switch to verify message tab */
    void gotoVerifyMessageTab(QString addr = "");
<<<<<<< HEAD

    /** Show open dialog */
    void openClicked();
=======
    /** Show MultiSend Dialog */
    void gotoMultiSendDialog();

    /** Show BIP 38 tool - default to Encryption tab */
    void gotoBip38Tool();

    /** Show open dialog */
    void openClicked();

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#endif // ENABLE_WALLET
    /** Show configuration dialog */
    void optionsClicked();
    /** Show about dialog */
    void aboutClicked();
<<<<<<< HEAD
    /** Show debug window */
    void showDebugWindow();

    /** Show debug window and set focus to the appropriate tab */
    void showInfo();
    void showConsole();
    void showGraph();
    void showPeers();
    void showRepair();

    /** Open external (default) editor with gelcoin.conf */
    void showConfEditor();
    /** Open external (default) editor with masternode.conf */
    void showMNConfEditor();
    /** Show folder with wallet backups in default file browser */
    void showBackups();

    /** Show help message dialog */
    void showHelpMessageClicked();
    /** Show PrivateSend help message dialog */
    void showPrivateSendHelpClicked();
=======
    /** Show help message dialog */
    void showHelpMessageClicked();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#ifndef Q_OS_MAC
    /** Handle tray icon clicked */
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
#endif

    /** Show window if hidden, unminimize when minimized, rise when obscured or show if hidden and fToggleHidden is true */
    void showNormalIfMinimized(bool fToggleHidden = false);
    /** Simply calls showNormalIfMinimized(true) for use in SLOT() macro */
    void toggleHidden();

    /** called by a timer to check if fRequestShutdown has been set **/
    void detectShutdown();

    /** Show progress dialog e.g. for verifychain */
<<<<<<< HEAD
    void showProgress(const QString &title, int nProgress);
    
    /** When hideTrayIcon setting is changed in OptionsModel hide or show the icon accordingly. */
    void setTrayIconVisible(bool);

    /** Toggle networking */
    void toggleNetworkActive();

    void showModalOverlay();
=======
    void showProgress(const QString& title, int nProgress);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};

class UnitDisplayStatusBarControl : public QLabel
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit UnitDisplayStatusBarControl(const PlatformStyle *platformStyle);
    /** Lets the control know about the Options Model (and its signals) */
    void setOptionsModel(OptionsModel *optionsModel);

protected:
    /** So that it responds to left-button clicks */
    void mousePressEvent(QMouseEvent *event);

private:
    OptionsModel *optionsModel;
=======
    explicit UnitDisplayStatusBarControl();
    /** Lets the control know about the Options Model (and its signals) */
    void setOptionsModel(OptionsModel* optionsModel);

protected:
    /** So that it responds to left-button clicks */
    void mousePressEvent(QMouseEvent* event);

private:
    OptionsModel* optionsModel;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    QMenu* menu;

    /** Shows context menu with Display Unit options by the mouse coordinates */
    void onDisplayUnitsClicked(const QPoint& point);
    /** Creates context menu, its actions, and wires up all the relevant signals for mouse events. */
    void createContextMenu();

<<<<<<< HEAD
private Q_SLOTS:
=======
private slots:
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    /** When Display Units are changed on OptionsModel it will refresh the display text of the control on the status bar */
    void updateDisplayUnit(int newUnits);
    /** Tells underlying optionsModel to update its current display unit. */
    void onMenuSelection(QAction* action);
};

#endif // BITCOIN_QT_BITCOINGUI_H
