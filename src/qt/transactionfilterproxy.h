<<<<<<< HEAD
// Copyright (c) 2011-2013 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_TRANSACTIONFILTERPROXY_H
#define BITCOIN_QT_TRANSACTIONFILTERPROXY_H

#include "amount.h"

#include <QDateTime>
#include <QSortFilterProxyModel>

/** Filter the transaction list according to pre-specified rules. */
class TransactionFilterProxy : public QSortFilterProxyModel
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit TransactionFilterProxy(QObject *parent = 0);
=======
    explicit TransactionFilterProxy(QObject* parent = 0);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    /** Earliest date that can be represented (far in the past) */
    static const QDateTime MIN_DATE;
    /** Last date that can be represented (far in the future) */
    static const QDateTime MAX_DATE;
    /** Type filter bit field (all types) */
    static const quint32 ALL_TYPES = 0xFFFFFFFF;
<<<<<<< HEAD
    /** Type filter bit field (all types but Darksend-SPAM) */
    static const quint32 COMMON_TYPES = 4223;

    static quint32 TYPE(int type) { return 1<<type; }

    enum WatchOnlyFilter
    {
=======
    /** Type filter bit field (all types but Obfuscation-SPAM) */
    static const quint32 COMMON_TYPES = 4479;

    static quint32 TYPE(int type) { return 1 << type; }

    enum WatchOnlyFilter {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        WatchOnlyFilter_All,
        WatchOnlyFilter_Yes,
        WatchOnlyFilter_No
    };

<<<<<<< HEAD
    void setDateRange(const QDateTime &from, const QDateTime &to);
    void setAddressPrefix(const QString &addrPrefix);
=======
    void setDateRange(const QDateTime& from, const QDateTime& to);
    void setAddressPrefix(const QString& addrPrefix);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    /**
      @note Type filter takes a bit field created with TYPE() or ALL_TYPES
     */
    void setTypeFilter(quint32 modes);
    void setMinAmount(const CAmount& minimum);
    void setWatchOnlyFilter(WatchOnlyFilter filter);

    /** Set maximum number of rows returned, -1 if unlimited. */
    void setLimit(int limit);

    /** Set whether to show conflicted transactions. */
    void setShowInactive(bool showInactive);

<<<<<<< HEAD
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex & source_parent) const;
=======
    int rowCount(const QModelIndex& parent = QModelIndex()) const;

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

private:
    QDateTime dateFrom;
    QDateTime dateTo;
    QString addrPrefix;
    quint32 typeFilter;
    WatchOnlyFilter watchOnlyFilter;
    CAmount minAmount;
    int limitRows;
    bool showInactive;
};

#endif // BITCOIN_QT_TRANSACTIONFILTERPROXY_H
