<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_TRANSACTIONTABLEMODEL_H
#define BITCOIN_QT_TRANSACTIONTABLEMODEL_H

#include "bitcoinunits.h"

#include <QAbstractTableModel>
#include <QStringList>

<<<<<<< HEAD
class PlatformStyle;
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
class TransactionRecord;
class TransactionTablePriv;
class WalletModel;

class CWallet;

/** UI model for the transaction table of a wallet.
 */
class TransactionTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit TransactionTableModel(const PlatformStyle *platformStyle, CWallet* wallet, WalletModel *parent = 0);
=======
    explicit TransactionTableModel(CWallet* wallet, WalletModel* parent = 0);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    ~TransactionTableModel();

    enum ColumnIndex {
        Status = 0,
        Watchonly = 1,
        Date = 2,
        Type = 3,
        ToAddress = 4,
        Amount = 5
    };

    /** Roles to get specific information from a transaction row.
        These are independent of column.
    */
    enum RoleIndex {
        /** Type of transaction */
        TypeRole = Qt::UserRole,
        /** Date and time this transaction was created */
        DateRole,
        /** Watch-only boolean */
        WatchonlyRole,
        /** Watch-only icon */
        WatchonlyDecorationRole,
        /** Long description (HTML format) */
        LongDescriptionRole,
        /** Address of transaction */
        AddressRole,
        /** Label of address related to transaction */
        LabelRole,
        /** Net amount of transaction */
        AmountRole,
        /** Unique identifier */
        TxIDRole,
        /** Transaction hash */
        TxHashRole,
<<<<<<< HEAD
        /** Transaction data, hex-encoded */
        TxHexRole,
        /** Whole transaction as plain text */
        TxPlainTextRole,
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        /** Is transaction confirmed? */
        ConfirmedRole,
        /** Formatted amount, without brackets when unconfirmed */
        FormattedAmountRole,
        /** Transaction status (TransactionRecord::Status) */
<<<<<<< HEAD
        StatusRole,
        /** Unprocessed icon */
        RawDecorationRole,
    };

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
=======
        StatusRole
    };

    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    bool processingQueuedTransactions() { return fProcessingQueuedTransactions; }

private:
    CWallet* wallet;
<<<<<<< HEAD
    WalletModel *walletModel;
    QStringList columns;
    TransactionTablePriv *priv;
    bool fProcessingQueuedTransactions;
    const PlatformStyle *platformStyle;
=======
    WalletModel* walletModel;
    QStringList columns;
    TransactionTablePriv* priv;
    bool fProcessingQueuedTransactions;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    void subscribeToCoreSignals();
    void unsubscribeFromCoreSignals();

<<<<<<< HEAD
    QString lookupAddress(const std::string &address, bool tooltip) const;
    QVariant addressColor(const TransactionRecord *wtx) const;
    QString formatTxStatus(const TransactionRecord *wtx) const;
    QString formatTxDate(const TransactionRecord *wtx) const;
    QString formatTxType(const TransactionRecord *wtx) const;
    QString formatTxToAddress(const TransactionRecord *wtx, bool tooltip) const;
    QString formatTxAmount(const TransactionRecord *wtx, bool showUnconfirmed=true, BitcoinUnits::SeparatorStyle separators=BitcoinUnits::separatorStandard) const;
    QString formatTooltip(const TransactionRecord *rec) const;
    QVariant txStatusDecoration(const TransactionRecord *wtx) const;
    QVariant txWatchonlyDecoration(const TransactionRecord *wtx) const;
    QVariant txAddressDecoration(const TransactionRecord *wtx) const;

public Q_SLOTS:
    /* New transaction, or transaction changed status */
    void updateTransaction(const QString &hash, int status, bool showTransaction);
=======
    QString lookupAddress(const std::string& address, bool tooltip) const;
    QVariant addressColor(const TransactionRecord* wtx) const;
    QString formatTxStatus(const TransactionRecord* wtx) const;
    QString formatTxDate(const TransactionRecord* wtx) const;
    QString formatTxType(const TransactionRecord* wtx) const;
    QString formatTxToAddress(const TransactionRecord* wtx, bool tooltip) const;
    QString formatTxAmount(const TransactionRecord* wtx, bool showUnconfirmed = true, BitcoinUnits::SeparatorStyle separators = BitcoinUnits::separatorStandard) const;
    QString formatTooltip(const TransactionRecord* rec) const;
    QVariant txStatusDecoration(const TransactionRecord* wtx) const;
    QVariant txWatchonlyDecoration(const TransactionRecord* wtx) const;
    QVariant txAddressDecoration(const TransactionRecord* wtx) const;

public slots:
    /* New transaction, or transaction changed status */
    void updateTransaction(const QString& hash, int status, bool showTransaction);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void updateConfirmations();
    void updateDisplayUnit();
    /** Updates the column title to "Amount (DisplayUnit)" and emits headerDataChanged() signal for table headers to react. */
    void updateAmountColumnTitle();
    /* Needed to update fProcessingQueuedTransactions through a QueuedConnection */
    void setProcessingQueuedTransactions(bool value) { fProcessingQueuedTransactions = value; }

    friend class TransactionTablePriv;
};

#endif // BITCOIN_QT_TRANSACTIONTABLEMODEL_H
