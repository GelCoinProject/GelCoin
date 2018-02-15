<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_RPCCONSOLE_H
#define BITCOIN_QT_RPCCONSOLE_H

#include "guiutil.h"
#include "peertablemodel.h"
<<<<<<< HEAD
#include "trafficgraphdata.h"

#include "net.h"

#include <QWidget>
#include <QCompleter>
#include <QThread>

class ClientModel;
class PlatformStyle;
class RPCTimerInterface;

namespace Ui {
    class RPCConsole;
}

QT_BEGIN_NAMESPACE
class QMenu;
=======

#include "net.h"

#include <QDialog>

class ClientModel;

namespace Ui
{
class RPCConsole;
}

QT_BEGIN_NAMESPACE
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
class QItemSelection;
QT_END_NAMESPACE

/** Local Bitcoin RPC console. */
<<<<<<< HEAD
class RPCConsole: public QWidget
=======
class RPCConsole : public QDialog
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit RPCConsole(const PlatformStyle *platformStyle, QWidget *parent);
    ~RPCConsole();

    void setClientModel(ClientModel *model);
=======
    explicit RPCConsole(QWidget* parent);
    ~RPCConsole();

    void setClientModel(ClientModel* model);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    enum MessageClass {
        MC_ERROR,
        MC_DEBUG,
        CMD_REQUEST,
        CMD_REPLY,
        CMD_ERROR
    };

<<<<<<< HEAD
    enum TabTypes {
        TAB_INFO = 0,
        TAB_CONSOLE = 1,
        TAB_GRAPH = 2,
        TAB_PEERS = 3,
        TAB_REPAIR = 4
    };

protected:
    virtual bool eventFilter(QObject* obj, QEvent *event);
    void keyPressEvent(QKeyEvent *);

private Q_SLOTS:
=======
protected:
    virtual bool eventFilter(QObject* obj, QEvent* event);

private slots:
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void on_lineEdit_returnPressed();
    void on_tabWidget_currentChanged(int index);
    /** open the debug.log from the current datadir */
    void on_openDebugLogfileButton_clicked();
    /** change the time range of the network traffic graph */
    void on_sldGraphRange_valueChanged(int value);
    /** update traffic statistics */
    void updateTrafficStats(quint64 totalBytesIn, quint64 totalBytesOut);
<<<<<<< HEAD
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    /** Show custom context menu on Peers tab */
    void showPeersTableContextMenu(const QPoint& point);
    /** Show custom context menu on Bans tab */
    void showBanTableContextMenu(const QPoint& point);
    /** Hides ban table if no bans are present */
    void showOrHideBanTableIfRequired();
    /** clear the selected node */
    void clearSelectedNode();

public Q_SLOTS:
    void clear(bool clearHistory = true);
    void fontBigger();
    void fontSmaller();
    void setFontSize(int newSize);
    
=======
    void resizeEvent(QResizeEvent* event);
    void showEvent(QShowEvent* event);
    void hideEvent(QHideEvent* event);

public slots:
    void clear();

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    /** Wallet repair options */
    void walletSalvage();
    void walletRescan();
    void walletZaptxes1();
    void walletZaptxes2();
    void walletUpgrade();
    void walletReindex();
<<<<<<< HEAD
    
    /** Append the message to the message widget */
    void message(int category, const QString &message, bool html = false);
    /** Set number of connections shown in the UI */
    void setNumConnections(int count);
    /** Set network state shown in the UI */
    void setNetworkActive(bool networkActive);
    /** Set number of masternodes shown in the UI */
    void setMasternodeCount(const QString &strMasternodes);
    /** Set number of blocks and last block date shown in the UI */
    void setNumBlocks(int count, const QDateTime& blockDate, double nVerificationProgress, bool headers);
    /** Set size (number of transactions and memory usage) of the mempool in the UI */
    void setMempoolSize(long numberOfTxs, size_t dynUsage);
=======

    void reject();
    void message(int category, const QString& message, bool html = false);
    /** Set number of connections shown in the UI */
    void setNumConnections(int count);
    /** Set number of blocks shown in the UI */
    void setNumBlocks(int count);
    /** Set number of masternodes shown in the UI */
    void setMasternodeCount(const QString& strMasternodes);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    /** Go forward or back in history */
    void browseHistory(int offset);
    /** Scroll console view to end */
    void scrollToEnd();
<<<<<<< HEAD
    /** Handle selection of peer in peers list */
    void peerSelected(const QItemSelection &selected, const QItemSelection &deselected);
    /** Handle selection caching before update */
    void peerLayoutAboutToChange();
    /** Handle updated peer information */
    void peerLayoutChanged();
    /** Disconnect a selected node on the Peers tab */
    void disconnectSelectedNode();
    /** Ban a selected node on the Peers tab */
    void banSelectedNode(int bantime);
    /** Unban a selected node on the Bans tab */
    void unbanSelectedNode();
    /** set which tab has the focus (is visible) */
    void setTabFocus(enum TabTypes tabType);

Q_SIGNALS:
    // For RPC command executor
    void stopExecutor();
    void cmdRequest(const QString &command);
=======
    /** Switch to info tab and show */
    void showInfo();
    /** Switch to console tab and show */
    void showConsole();
    /** Switch to network tab and show */
    void showNetwork();
    /** Switch to peers tab and show */
    void showPeers();
    /** Switch to wallet-repair tab and show */
    void showRepair();
    /** Open external (default) editor with lux.conf */
    void showConfEditor();
    /** Open external (default) editor with masternode.conf */
    void showMNConfEditor();
    /** Handle selection of peer in peers list */
    void peerSelected(const QItemSelection& selected, const QItemSelection& deselected);
    /** Handle updated peer information */
    void peerLayoutChanged();
    /** Show folder with wallet backups in default browser */
    void showBackups();

signals:
    // For RPC command executor
    void stopExecutor();
    void cmdRequest(const QString& command);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    /** Get restart command-line parameters and handle restart */
    void handleRestart(QStringList args);

private:
    static QString FormatBytes(quint64 bytes);
    void startExecutor();
<<<<<<< HEAD
    void setTrafficGraphRange(TrafficGraphData::GraphRange range);
    /** Build parameter list for restart */
    void buildParameterlist(QString arg);
    /** show detailed information on ui about selected node */
    void updateNodeDetail(const CNodeCombinedStats *stats);

    enum ColumnWidths
    {
        ADDRESS_COLUMN_WIDTH = 170,
        SUBVERSION_COLUMN_WIDTH = 150,
        PING_COLUMN_WIDTH = 80,
        BANSUBNET_COLUMN_WIDTH = 200,
        BANTIME_COLUMN_WIDTH = 250

    };

    Ui::RPCConsole *ui;
    ClientModel *clientModel;
    QStringList history;
    int historyPtr;
    QList<NodeId> cachedNodeids;
    const PlatformStyle *platformStyle;
    RPCTimerInterface *rpcTimerInterface;
    QMenu *peersTableContextMenu;
    QMenu *banTableContextMenu;
    int consoleFontSize;
    QCompleter *autoCompleter;
    QThread thread;

    /** Update UI with latest network info from model. */
    void updateNetworkState();
=======
    void setTrafficGraphRange(int mins);
    /** Build parameter list for restart */
    void buildParameterlist(QString arg);
    /** show detailed information on ui about selected node */
    void updateNodeDetail(const CNodeCombinedStats* stats);

    enum ColumnWidths {
        ADDRESS_COLUMN_WIDTH = 170,
        SUBVERSION_COLUMN_WIDTH = 140,
        PING_COLUMN_WIDTH = 80
    };

    Ui::RPCConsole* ui;
    ClientModel* clientModel;
    QStringList history;
    int historyPtr;
    NodeId cachedNodeid;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};

#endif // BITCOIN_QT_RPCCONSOLE_H
