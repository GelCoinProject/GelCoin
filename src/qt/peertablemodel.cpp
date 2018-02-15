<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "peertablemodel.h"

#include "clientmodel.h"
#include "guiconstants.h"
#include "guiutil.h"

<<<<<<< HEAD
#include "validation.h" // for cs_main
=======
#include "net.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include "sync.h"

#include <QDebug>
#include <QList>
#include <QTimer>

<<<<<<< HEAD
bool NodeLessThan::operator()(const CNodeCombinedStats &left, const CNodeCombinedStats &right) const
{
    const CNodeStats *pLeft = &(left.nodeStats);
    const CNodeStats *pRight = &(right.nodeStats);
=======
bool NodeLessThan::operator()(const CNodeCombinedStats& left, const CNodeCombinedStats& right) const
{
    const CNodeStats* pLeft = &(left.nodeStats);
    const CNodeStats* pRight = &(right.nodeStats);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    if (order == Qt::DescendingOrder)
        std::swap(pLeft, pRight);

<<<<<<< HEAD
    switch(column)
    {
    case PeerTableModel::NetNodeId:
        return pLeft->nodeid < pRight->nodeid;
=======
    switch (column) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    case PeerTableModel::Address:
        return pLeft->addrName.compare(pRight->addrName) < 0;
    case PeerTableModel::Subversion:
        return pLeft->cleanSubVer.compare(pRight->cleanSubVer) < 0;
    case PeerTableModel::Ping:
<<<<<<< HEAD
        return pLeft->dMinPing < pRight->dMinPing;
=======
        return pLeft->dPingTime < pRight->dPingTime;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }

    return false;
}

// private implementation
class PeerTablePriv
{
public:
    /** Local cache of peer information */
    QList<CNodeCombinedStats> cachedNodeStats;
    /** Column to sort nodes by */
    int sortColumn;
    /** Order (ascending or descending) to sort nodes by */
    Qt::SortOrder sortOrder;
    /** Index of rows by node ID */
    std::map<NodeId, int> mapNodeRows;

    /** Pull a full list of peers from vNodes into our cache */
    void refreshPeers()
    {
        {
<<<<<<< HEAD
            cachedNodeStats.clear();
            std::vector<CNodeStats> vstats;
            if(g_connman)
                g_connman->GetNodeStats(vstats);
#if QT_VERSION >= 0x040700
            cachedNodeStats.reserve(vstats.size());
#endif
            Q_FOREACH (const CNodeStats& nodestats, vstats)
            {
                CNodeCombinedStats stats;
                stats.nodeStateStats.nMisbehavior = 0;
                stats.nodeStateStats.nSyncHeight = -1;
                stats.nodeStateStats.nCommonHeight = -1;
                stats.fNodeStateStatsAvailable = false;
                stats.nodeStats = nodestats;
=======
            TRY_LOCK(cs_vNodes, lockNodes);
            if (!lockNodes) {
                // skip the refresh if we can't immediately get the lock
                return;
            }
            cachedNodeStats.clear();
#if QT_VERSION >= 0x040700
            cachedNodeStats.reserve(vNodes.size());
#endif
            BOOST_FOREACH (CNode* pnode, vNodes) {
                CNodeCombinedStats stats;
                stats.nodeStateStats.nMisbehavior = 0;
                stats.nodeStateStats.nSyncHeight = -1;
                stats.fNodeStateStatsAvailable = false;
                pnode->copyStats(stats.nodeStats);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                cachedNodeStats.append(stats);
            }
        }

        // Try to retrieve the CNodeStateStats for each node.
        {
            TRY_LOCK(cs_main, lockMain);
<<<<<<< HEAD
            if (lockMain)
            {
                BOOST_FOREACH(CNodeCombinedStats &stats, cachedNodeStats)
=======
            if (lockMain) {
                BOOST_FOREACH (CNodeCombinedStats& stats, cachedNodeStats)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                    stats.fNodeStateStatsAvailable = GetNodeStateStats(stats.nodeStats.nodeid, stats.nodeStateStats);
            }
        }

        if (sortColumn >= 0)
<<<<<<< HEAD
            // sort cacheNodeStats (use stable sort to prevent rows jumping around unnecessarily)
=======
            // sort cacheNodeStats (use stable sort to prevent rows jumping around unneceesarily)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            qStableSort(cachedNodeStats.begin(), cachedNodeStats.end(), NodeLessThan(sortColumn, sortOrder));

        // build index map
        mapNodeRows.clear();
        int row = 0;
<<<<<<< HEAD
        Q_FOREACH (const CNodeCombinedStats& stats, cachedNodeStats)
            mapNodeRows.insert(std::pair<NodeId, int>(stats.nodeStats.nodeid, row++));
    }

    int size() const
=======
        BOOST_FOREACH (CNodeCombinedStats& stats, cachedNodeStats)
            mapNodeRows.insert(std::pair<NodeId, int>(stats.nodeStats.nodeid, row++));
    }

    int size()
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    {
        return cachedNodeStats.size();
    }

<<<<<<< HEAD
    CNodeCombinedStats *index(int idx)
    {
        if (idx >= 0 && idx < cachedNodeStats.size())
            return &cachedNodeStats[idx];

        return 0;
    }
};

PeerTableModel::PeerTableModel(ClientModel *parent) :
    QAbstractTableModel(parent),
    clientModel(parent),
    timer(0)
{
    columns << tr("NodeId") << tr("Node/Service") << tr("User Agent") << tr("Ping");
    priv.reset(new PeerTablePriv());
=======
    CNodeCombinedStats* index(int idx)
    {
        if (idx >= 0 && idx < cachedNodeStats.size()) {
            return &cachedNodeStats[idx];
        } else {
            return 0;
        }
    }
};

PeerTableModel::PeerTableModel(ClientModel* parent) : QAbstractTableModel(parent),
                                                      clientModel(parent),
                                                      timer(0)
{
    columns << tr("Address/Hostname") << tr("Version") << tr("Ping Time");
    priv = new PeerTablePriv();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    // default to unsorted
    priv->sortColumn = -1;

    // set up timer for auto refresh
<<<<<<< HEAD
    timer = new QTimer(this);
=======
    timer = new QTimer();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    connect(timer, SIGNAL(timeout()), SLOT(refresh()));
    timer->setInterval(MODEL_UPDATE_DELAY);

    // load initial data
    refresh();
}

<<<<<<< HEAD
PeerTableModel::~PeerTableModel()
{
    // Intentionally left empty
}

=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
void PeerTableModel::startAutoRefresh()
{
    timer->start();
}

void PeerTableModel::stopAutoRefresh()
{
    timer->stop();
}

<<<<<<< HEAD
int PeerTableModel::rowCount(const QModelIndex &parent) const
=======
int PeerTableModel::rowCount(const QModelIndex& parent) const
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    Q_UNUSED(parent);
    return priv->size();
}

<<<<<<< HEAD
int PeerTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return columns.length();
}

QVariant PeerTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    CNodeCombinedStats *rec = static_cast<CNodeCombinedStats*>(index.internalPointer());

    if (role == Qt::DisplayRole) {
        switch(index.column())
        {
        case NetNodeId:
            return rec->nodeStats.nodeid;
=======
int PeerTableModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return columns.length();
    ;
}

QVariant PeerTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    CNodeCombinedStats* rec = static_cast<CNodeCombinedStats*>(index.internalPointer());

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        case Address:
            return QString::fromStdString(rec->nodeStats.addrName);
        case Subversion:
            return QString::fromStdString(rec->nodeStats.cleanSubVer);
        case Ping:
<<<<<<< HEAD
            return GUIUtil::formatPingTime(rec->nodeStats.dMinPing);
        }
    } else if (role == Qt::TextAlignmentRole) {
        if (index.column() == Ping)
            return (QVariant)(Qt::AlignRight | Qt::AlignVCenter);
=======
            return GUIUtil::formatPingTime(rec->nodeStats.dPingTime);
        }
    } else if (role == Qt::TextAlignmentRole) {
        if (index.column() == Ping)
            return (int)(Qt::AlignRight | Qt::AlignVCenter);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }

    return QVariant();
}

QVariant PeerTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
<<<<<<< HEAD
    if(orientation == Qt::Horizontal)
    {
        if(role == Qt::DisplayRole && section < columns.size())
        {
=======
    if (orientation == Qt::Horizontal) {
        if (role == Qt::DisplayRole && section < columns.size()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            return columns[section];
        }
    }
    return QVariant();
}

<<<<<<< HEAD
Qt::ItemFlags PeerTableModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
=======
Qt::ItemFlags PeerTableModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return 0;

    Qt::ItemFlags retval = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    return retval;
}

<<<<<<< HEAD
QModelIndex PeerTableModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    CNodeCombinedStats *data = priv->index(row);

    if (data)
        return createIndex(row, column, data);
    return QModelIndex();
}

const CNodeCombinedStats *PeerTableModel::getNodeStats(int idx)
=======
QModelIndex PeerTableModel::index(int row, int column, const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    CNodeCombinedStats* data = priv->index(row);

    if (data) {
        return createIndex(row, column, data);
    } else {
        return QModelIndex();
    }
}

const CNodeCombinedStats* PeerTableModel::getNodeStats(int idx)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    return priv->index(idx);
}

void PeerTableModel::refresh()
{
<<<<<<< HEAD
    Q_EMIT layoutAboutToBeChanged();
    priv->refreshPeers();
    Q_EMIT layoutChanged();
=======
    emit layoutAboutToBeChanged();
    priv->refreshPeers();
    emit layoutChanged();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

int PeerTableModel::getRowByNodeId(NodeId nodeid)
{
    std::map<NodeId, int>::iterator it = priv->mapNodeRows.find(nodeid);
    if (it == priv->mapNodeRows.end())
        return -1;

    return it->second;
}

void PeerTableModel::sort(int column, Qt::SortOrder order)
{
    priv->sortColumn = column;
    priv->sortOrder = order;
    refresh();
}
