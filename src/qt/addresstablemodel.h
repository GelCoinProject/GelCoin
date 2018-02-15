<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_ADDRESSTABLEMODEL_H
#define BITCOIN_QT_ADDRESSTABLEMODEL_H

#include <QAbstractTableModel>
#include <QStringList>

class AddressTablePriv;
class WalletModel;

class CWallet;

/**
   Qt model of the address book in the core. This allows views to access and modify the address book.
 */
class AddressTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit AddressTableModel(CWallet *wallet, WalletModel *parent = 0);
    ~AddressTableModel();

    enum ColumnIndex {
        Label = 0,   /**< User specified label */
        Address = 1  /**< Bitcoin address */
=======
    explicit AddressTableModel(CWallet* wallet, WalletModel* parent = 0);
    ~AddressTableModel();

    enum ColumnIndex {
        Label = 0,  /**< User specified label */
        Address = 1 /**< Bitcoin address */
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    };

    enum RoleIndex {
        TypeRole = Qt::UserRole /**< Type of address (#Send or #Receive) */
    };

    /** Return status of edit/insert operation */
    enum EditStatus {
<<<<<<< HEAD
        OK,                     /**< Everything ok */
        NO_CHANGES,             /**< No changes were made during edit operation */
        INVALID_ADDRESS,        /**< Unparseable address */
        DUPLICATE_ADDRESS,      /**< Address already in address book */
        WALLET_UNLOCK_FAILURE,  /**< Wallet could not be unlocked to create new receiving address */
        KEY_GENERATION_FAILURE  /**< Generating a new public key for a receiving address failed */
    };

    static const QString Send;      /**< Specifies send address */
    static const QString Receive;   /**< Specifies receive address */

    /** @name Methods overridden from QAbstractTableModel
        @{*/
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    Qt::ItemFlags flags(const QModelIndex &index) const;
=======
        OK,                    /**< Everything ok */
        NO_CHANGES,            /**< No changes were made during edit operation */
        INVALID_ADDRESS,       /**< Unparseable address */
        DUPLICATE_ADDRESS,     /**< Address already in address book */
        WALLET_UNLOCK_FAILURE, /**< Wallet could not be unlocked to create new receiving address */
        KEY_GENERATION_FAILURE /**< Generating a new public key for a receiving address failed */
    };

    static const QString Send;    /**< Specifies send address */
    static const QString Receive; /**< Specifies receive address */

    /** @name Methods overridden from QAbstractTableModel
        @{*/
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QModelIndex index(int row, int column, const QModelIndex& parent) const;
    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex());
    Qt::ItemFlags flags(const QModelIndex& index) const;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    /*@}*/

    /* Add an address to the model.
       Returns the added address on success, and an empty string otherwise.
     */
<<<<<<< HEAD
    QString addRow(const QString &type, const QString &label, const QString &address);

    /* Look up label for address in address book, if not found return empty string.
     */
    QString labelForAddress(const QString &address) const;
=======
    QString addRow(const QString& type, const QString& label, const QString& address);

    /* Look up label for address in address book, if not found return empty string.
     */
    QString labelForAddress(const QString& address) const;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    /* Look up row index of an address in the model.
       Return -1 if not found.
     */
<<<<<<< HEAD
    int lookupAddress(const QString &address) const;
=======
    int lookupAddress(const QString& address) const;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    EditStatus getEditStatus() const { return editStatus; }

private:
<<<<<<< HEAD
    WalletModel *walletModel;
    CWallet *wallet;
    AddressTablePriv *priv;
=======
    WalletModel* walletModel;
    CWallet* wallet;
    AddressTablePriv* priv;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    QStringList columns;
    EditStatus editStatus;

    /** Notify listeners that data changed. */
    void emitDataChanged(int index);

<<<<<<< HEAD
public Q_SLOTS:
    /* Update address list from core.
     */
    void updateEntry(const QString &address, const QString &label, bool isMine, const QString &purpose, int status);
=======
public slots:
    /* Update address list from core.
     */
    void updateEntry(const QString& address, const QString& label, bool isMine, const QString& purpose, int status);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    friend class AddressTablePriv;
};

#endif // BITCOIN_QT_ADDRESSTABLEMODEL_H
