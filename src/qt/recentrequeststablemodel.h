<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_RECENTREQUESTSTABLEMODEL_H
#define BITCOIN_QT_RECENTREQUESTSTABLEMODEL_H

#include "walletmodel.h"

#include <QAbstractTableModel>
<<<<<<< HEAD
#include <QStringList>
#include <QDateTime>
=======
#include <QDateTime>
#include <QStringList>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

class CWallet;

class RecentRequestEntry
{
public:
<<<<<<< HEAD
    RecentRequestEntry() : nVersion(RecentRequestEntry::CURRENT_VERSION), id(0) { }
=======
    RecentRequestEntry() : nVersion(RecentRequestEntry::CURRENT_VERSION), id(0) {}
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    static const int CURRENT_VERSION = 1;
    int nVersion;
    int64_t id;
    QDateTime date;
    SendCoinsRecipient recipient;

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
<<<<<<< HEAD
    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion) {
=======
    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion)
    {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        unsigned int nDate = date.toTime_t();

        READWRITE(this->nVersion);
        nVersion = this->nVersion;
        READWRITE(id);
        READWRITE(nDate);
        READWRITE(recipient);

        if (ser_action.ForRead())
            date = QDateTime::fromTime_t(nDate);
    }
};

class RecentRequestEntryLessThan
{
public:
<<<<<<< HEAD
    RecentRequestEntryLessThan(int nColumn, Qt::SortOrder fOrder):
        column(nColumn), order(fOrder) {}
    bool operator()(RecentRequestEntry &left, RecentRequestEntry &right) const;
=======
    RecentRequestEntryLessThan(int nColumn, Qt::SortOrder fOrder) : column(nColumn), order(fOrder) {}
    bool operator()(RecentRequestEntry& left, RecentRequestEntry& right) const;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

private:
    int column;
    Qt::SortOrder order;
};

<<<<<<< HEAD
/** Model for list of recently generated payment requests / gelcoin: URIs.
 * Part of wallet model.
 */
class RecentRequestsTableModel: public QAbstractTableModel
=======
/** Model for list of recently generated payment requests / lux: URIs.
 * Part of wallet model.
 */
class RecentRequestsTableModel : public QAbstractTableModel
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit RecentRequestsTableModel(CWallet *wallet, WalletModel *parent);
=======
    explicit RecentRequestsTableModel(CWallet* wallet, WalletModel* parent);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    ~RecentRequestsTableModel();

    enum ColumnIndex {
        Date = 0,
        Label = 1,
        Message = 2,
        Amount = 3,
        NUMBER_OF_COLUMNS
    };

    /** @name Methods overridden from QAbstractTableModel
        @{*/
<<<<<<< HEAD
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    Qt::ItemFlags flags(const QModelIndex &index) const;
    /*@}*/

    const RecentRequestEntry &entry(int row) const { return list[row]; }
    void addNewRequest(const SendCoinsRecipient &recipient);
    void addNewRequest(const std::string &recipient);
    void addNewRequest(RecentRequestEntry &recipient);

public Q_SLOTS:
=======
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QModelIndex index(int row, int column, const QModelIndex& parent) const;
    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex());
    Qt::ItemFlags flags(const QModelIndex& index) const;
    /*@}*/

    const RecentRequestEntry& entry(int row) const { return list[row]; }
    void addNewRequest(const SendCoinsRecipient& recipient);
    void addNewRequest(const std::string& recipient);
    void addNewRequest(RecentRequestEntry& recipient);

public slots:
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);
    void updateDisplayUnit();

private:
<<<<<<< HEAD
    WalletModel *walletModel;
=======
    WalletModel* walletModel;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    QStringList columns;
    QList<RecentRequestEntry> list;
    int64_t nReceiveRequestsMaxId;

    /** Updates the column title to "Amount (DisplayUnit)" and emits headerDataChanged() signal for table headers to react. */
    void updateAmountColumnTitle();
    /** Gets title for amount column including current display unit if optionsModel reference available. */
    QString getAmountTitle();
};

#endif // BITCOIN_QT_RECENTREQUESTSTABLEMODEL_H
