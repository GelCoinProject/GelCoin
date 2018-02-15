<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_PEERTABLEMODEL_H
#define BITCOIN_QT_PEERTABLEMODEL_H

<<<<<<< HEAD
#include "net_processing.h" // For CNodeStateStats
=======
#include "main.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include "net.h"

#include <QAbstractTableModel>
#include <QStringList>

class ClientModel;
class PeerTablePriv;

QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE

struct CNodeCombinedStats {
    CNodeStats nodeStats;
    CNodeStateStats nodeStateStats;
    bool fNodeStateStatsAvailable;
};

class NodeLessThan
{
public:
<<<<<<< HEAD
    NodeLessThan(int nColumn, Qt::SortOrder fOrder) :
        column(nColumn), order(fOrder) {}
    bool operator()(const CNodeCombinedStats &left, const CNodeCombinedStats &right) const;
=======
    NodeLessThan(int nColumn, Qt::SortOrder fOrder) : column(nColumn), order(fOrder) {}
    bool operator()(const CNodeCombinedStats& left, const CNodeCombinedStats& right) const;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

private:
    int column;
    Qt::SortOrder order;
};

/**
   Qt model providing information about connected peers, similar to the
   "getpeerinfo" RPC call. Used by the rpc console UI.
 */
class PeerTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit PeerTableModel(ClientModel *parent = 0);
    ~PeerTableModel();
    const CNodeCombinedStats *getNodeStats(int idx);
=======
    explicit PeerTableModel(ClientModel* parent = 0);
    const CNodeCombinedStats* getNodeStats(int idx);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    int getRowByNodeId(NodeId nodeid);
    void startAutoRefresh();
    void stopAutoRefresh();

    enum ColumnIndex {
<<<<<<< HEAD
        NetNodeId = 0,
        Address = 1,
        Subversion = 2,
        Ping = 3
=======
        Address = 0,
        Subversion = 1,
        Ping = 2
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    };

    /** @name Methods overridden from QAbstractTableModel
        @{*/
<<<<<<< HEAD
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void sort(int column, Qt::SortOrder order);
    /*@}*/

public Q_SLOTS:
    void refresh();

private:
    ClientModel *clientModel;
    QStringList columns;
    std::unique_ptr<PeerTablePriv> priv;
    QTimer *timer;
=======
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QModelIndex index(int row, int column, const QModelIndex& parent) const;
    Qt::ItemFlags flags(const QModelIndex& index) const;
    void sort(int column, Qt::SortOrder order);
    /*@}*/

public slots:
    void refresh();

private:
    ClientModel* clientModel;
    QStringList columns;
    PeerTablePriv* priv;
    QTimer* timer;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};

#endif // BITCOIN_QT_PEERTABLEMODEL_H
