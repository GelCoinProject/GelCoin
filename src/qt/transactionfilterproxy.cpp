<<<<<<< HEAD
// Copyright (c) 2011-2013 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "transactionfilterproxy.h"

<<<<<<< HEAD
#include "transactiontablemodel.h"
#include "transactionrecord.h"
=======
#include "transactionrecord.h"
#include "transactiontablemodel.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

#include <cstdlib>

#include <QDateTime>

// Earliest date that can be represented (far in the past)
const QDateTime TransactionFilterProxy::MIN_DATE = QDateTime::fromTime_t(0);
// Last date that can be represented (far in the future)
const QDateTime TransactionFilterProxy::MAX_DATE = QDateTime::fromTime_t(0xFFFFFFFF);

<<<<<<< HEAD
TransactionFilterProxy::TransactionFilterProxy(QObject *parent) :
    QSortFilterProxyModel(parent),
    dateFrom(MIN_DATE),
    dateTo(MAX_DATE),
    addrPrefix(),
    typeFilter(COMMON_TYPES),
    watchOnlyFilter(WatchOnlyFilter_All),
    minAmount(0),
    limitRows(-1),
    showInactive(true)
{
}

bool TransactionFilterProxy::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
=======
TransactionFilterProxy::TransactionFilterProxy(QObject* parent) : QSortFilterProxyModel(parent),
                                                                  dateFrom(MIN_DATE),
                                                                  dateTo(MAX_DATE),
                                                                  addrPrefix(),
                                                                  typeFilter(COMMON_TYPES),
                                                                  watchOnlyFilter(WatchOnlyFilter_All),
                                                                  minAmount(0),
                                                                  limitRows(-1),
                                                                  showInactive(true)
{
}

bool TransactionFilterProxy::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    int type = index.data(TransactionTableModel::TypeRole).toInt();
    QDateTime datetime = index.data(TransactionTableModel::DateRole).toDateTime();
    bool involvesWatchAddress = index.data(TransactionTableModel::WatchonlyRole).toBool();
    QString address = index.data(TransactionTableModel::AddressRole).toString();
    QString label = index.data(TransactionTableModel::LabelRole).toString();
    qint64 amount = llabs(index.data(TransactionTableModel::AmountRole).toLongLong());
    int status = index.data(TransactionTableModel::StatusRole).toInt();

<<<<<<< HEAD
    if(!showInactive && status == TransactionStatus::Conflicted)
        return false;
    if(!(TYPE(type) & typeFilter))
=======
    if (!showInactive && status == TransactionStatus::Conflicted)
        return false;
    if (!(TYPE(type) & typeFilter))
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return false;
    if (involvesWatchAddress && watchOnlyFilter == WatchOnlyFilter_No)
        return false;
    if (!involvesWatchAddress && watchOnlyFilter == WatchOnlyFilter_Yes)
        return false;
<<<<<<< HEAD
    if(datetime < dateFrom || datetime > dateTo)
        return false;
    if (!address.contains(addrPrefix, Qt::CaseInsensitive) && !label.contains(addrPrefix, Qt::CaseInsensitive))
        return false;
    if(amount < minAmount)
=======
    if (datetime < dateFrom || datetime > dateTo)
        return false;
    if (!address.contains(addrPrefix, Qt::CaseInsensitive) && !label.contains(addrPrefix, Qt::CaseInsensitive))
        return false;
    if (amount < minAmount)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return false;

    return true;
}

<<<<<<< HEAD
void TransactionFilterProxy::setDateRange(const QDateTime &from, const QDateTime &to)
=======
void TransactionFilterProxy::setDateRange(const QDateTime& from, const QDateTime& to)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    this->dateFrom = from;
    this->dateTo = to;
    invalidateFilter();
}

<<<<<<< HEAD
void TransactionFilterProxy::setAddressPrefix(const QString &addrPrefix)
=======
void TransactionFilterProxy::setAddressPrefix(const QString& addrPrefix)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    this->addrPrefix = addrPrefix;
    invalidateFilter();
}

void TransactionFilterProxy::setTypeFilter(quint32 modes)
{
    this->typeFilter = modes;
    invalidateFilter();
}

void TransactionFilterProxy::setMinAmount(const CAmount& minimum)
{
    this->minAmount = minimum;
    invalidateFilter();
}

void TransactionFilterProxy::setWatchOnlyFilter(WatchOnlyFilter filter)
{
    this->watchOnlyFilter = filter;
    invalidateFilter();
}

void TransactionFilterProxy::setLimit(int limit)
{
    this->limitRows = limit;
}

void TransactionFilterProxy::setShowInactive(bool showInactive)
{
    this->showInactive = showInactive;
    invalidateFilter();
}

<<<<<<< HEAD
int TransactionFilterProxy::rowCount(const QModelIndex &parent) const
{
    if(limitRows != -1)
    {
        return std::min(QSortFilterProxyModel::rowCount(parent), limitRows);
    }
    else
    {
=======
int TransactionFilterProxy::rowCount(const QModelIndex& parent) const
{
    if (limitRows != -1) {
        return std::min(QSortFilterProxyModel::rowCount(parent), limitRows);
    } else {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return QSortFilterProxyModel::rowCount(parent);
    }
}
