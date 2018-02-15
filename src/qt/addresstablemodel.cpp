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

#include "addresstablemodel.h"

#include "guiutil.h"
#include "walletmodel.h"

#include "base58.h"
<<<<<<< HEAD
#include "wallet/wallet.h"

#include <boost/foreach.hpp>

#include <QFont>
#include <QDebug>
=======
#include "wallet.h"

#include <QDebug>
#include <QFont>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

const QString AddressTableModel::Send = "S";
const QString AddressTableModel::Receive = "R";

<<<<<<< HEAD
struct AddressTableEntry
{
=======
struct AddressTableEntry {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    enum Type {
        Sending,
        Receiving,
        Hidden /* QSortFilterProxyModel will filter these out */
    };

    Type type;
    QString label;
    QString address;

    AddressTableEntry() {}
<<<<<<< HEAD
    AddressTableEntry(Type type, const QString &label, const QString &address):
        type(type), label(label), address(address) {}
};

struct AddressTableEntryLessThan
{
    bool operator()(const AddressTableEntry &a, const AddressTableEntry &b) const
    {
        return a.address < b.address;
    }
    bool operator()(const AddressTableEntry &a, const QString &b) const
    {
        return a.address < b;
    }
    bool operator()(const QString &a, const AddressTableEntry &b) const
=======
    AddressTableEntry(Type type, const QString& label, const QString& address) : type(type), label(label), address(address) {}
};

struct AddressTableEntryLessThan {
    bool operator()(const AddressTableEntry& a, const AddressTableEntry& b) const
    {
        return a.address < b.address;
    }
    bool operator()(const AddressTableEntry& a, const QString& b) const
    {
        return a.address < b;
    }
    bool operator()(const QString& a, const AddressTableEntry& b) const
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    {
        return a < b.address;
    }
};

/* Determine address type from address purpose */
<<<<<<< HEAD
static AddressTableEntry::Type translateTransactionType(const QString &strPurpose, bool isMine)
=======
static AddressTableEntry::Type translateTransactionType(const QString& strPurpose, bool isMine)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    AddressTableEntry::Type addressType = AddressTableEntry::Hidden;
    // "refund" addresses aren't shown, and change addresses aren't in mapAddressBook at all.
    if (strPurpose == "send")
        addressType = AddressTableEntry::Sending;
    else if (strPurpose == "receive")
        addressType = AddressTableEntry::Receiving;
    else if (strPurpose == "unknown" || strPurpose == "") // if purpose not set, guess
        addressType = (isMine ? AddressTableEntry::Receiving : AddressTableEntry::Sending);
    return addressType;
}

// Private implementation
class AddressTablePriv
{
public:
<<<<<<< HEAD
    CWallet *wallet;
    QList<AddressTableEntry> cachedAddressTable;
    AddressTableModel *parent;

    AddressTablePriv(CWallet *wallet, AddressTableModel *parent):
        wallet(wallet), parent(parent) {}
=======
    CWallet* wallet;
    QList<AddressTableEntry> cachedAddressTable;
    AddressTableModel* parent;

    AddressTablePriv(CWallet* wallet, AddressTableModel* parent) : wallet(wallet), parent(parent) {}
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    void refreshAddressTable()
    {
        cachedAddressTable.clear();
        {
            LOCK(wallet->cs_wallet);
<<<<<<< HEAD
            BOOST_FOREACH(const PAIRTYPE(CTxDestination, CAddressBookData)& item, wallet->mapAddressBook)
            {
                const CBitcoinAddress& address = item.first;
                bool fMine = IsMine(*wallet, address.Get());
                AddressTableEntry::Type addressType = translateTransactionType(
                        QString::fromStdString(item.second.purpose), fMine);
                const std::string& strName = item.second.name;
                cachedAddressTable.append(AddressTableEntry(addressType,
                                  QString::fromStdString(strName),
                                  QString::fromStdString(address.ToString())));
=======
            BOOST_FOREACH (const PAIRTYPE(CTxDestination, CAddressBookData) & item, wallet->mapAddressBook) {
                const CBitcoinAddress& address = item.first;
                bool fMine = IsMine(*wallet, address.Get());
                AddressTableEntry::Type addressType = translateTransactionType(
                    QString::fromStdString(item.second.purpose), fMine);
                const std::string& strName = item.second.name;
                cachedAddressTable.append(AddressTableEntry(addressType,
                    QString::fromStdString(strName),
                    QString::fromStdString(address.ToString())));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            }
        }
        // qLowerBound() and qUpperBound() require our cachedAddressTable list to be sorted in asc order
        // Even though the map is already sorted this re-sorting step is needed because the originating map
        // is sorted by binary address, not by base58() address.
        qSort(cachedAddressTable.begin(), cachedAddressTable.end(), AddressTableEntryLessThan());
    }

<<<<<<< HEAD
    void updateEntry(const QString &address, const QString &label, bool isMine, const QString &purpose, int status)
=======
    void updateEntry(const QString& address, const QString& label, bool isMine, const QString& purpose, int status)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    {
        // Find address / label in model
        QList<AddressTableEntry>::iterator lower = qLowerBound(
            cachedAddressTable.begin(), cachedAddressTable.end(), address, AddressTableEntryLessThan());
        QList<AddressTableEntry>::iterator upper = qUpperBound(
            cachedAddressTable.begin(), cachedAddressTable.end(), address, AddressTableEntryLessThan());
        int lowerIndex = (lower - cachedAddressTable.begin());
        int upperIndex = (upper - cachedAddressTable.begin());
        bool inModel = (lower != upper);
        AddressTableEntry::Type newEntryType = translateTransactionType(purpose, isMine);

<<<<<<< HEAD
        switch(status)
        {
        case CT_NEW:
            if(inModel)
            {
                qWarning() << "AddressTablePriv::updateEntry: Warning: Got CT_NEW, but entry is already in model";
=======
        switch (status) {
        case CT_NEW:
            if (inModel) {
                qWarning() << "AddressTablePriv::updateEntry : Warning: Got CT_NEW, but entry is already in model";
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                break;
            }
            parent->beginInsertRows(QModelIndex(), lowerIndex, lowerIndex);
            cachedAddressTable.insert(lowerIndex, AddressTableEntry(newEntryType, label, address));
            parent->endInsertRows();
            break;
        case CT_UPDATED:
<<<<<<< HEAD
            if(!inModel)
            {
                qWarning() << "AddressTablePriv::updateEntry: Warning: Got CT_UPDATED, but entry is not in model";
=======
            if (!inModel) {
                qWarning() << "AddressTablePriv::updateEntry : Warning: Got CT_UPDATED, but entry is not in model";
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                break;
            }
            lower->type = newEntryType;
            lower->label = label;
            parent->emitDataChanged(lowerIndex);
            break;
        case CT_DELETED:
<<<<<<< HEAD
            if(!inModel)
            {
                qWarning() << "AddressTablePriv::updateEntry: Warning: Got CT_DELETED, but entry is not in model";
                break;
            }
            parent->beginRemoveRows(QModelIndex(), lowerIndex, upperIndex-1);
=======
            if (!inModel) {
                qWarning() << "AddressTablePriv::updateEntry : Warning: Got CT_DELETED, but entry is not in model";
                break;
            }
            parent->beginRemoveRows(QModelIndex(), lowerIndex, upperIndex - 1);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            cachedAddressTable.erase(lower, upper);
            parent->endRemoveRows();
            break;
        }
    }

    int size()
    {
        return cachedAddressTable.size();
    }

<<<<<<< HEAD
    AddressTableEntry *index(int idx)
    {
        if(idx >= 0 && idx < cachedAddressTable.size())
        {
            return &cachedAddressTable[idx];
        }
        else
        {
=======
    AddressTableEntry* index(int idx)
    {
        if (idx >= 0 && idx < cachedAddressTable.size()) {
            return &cachedAddressTable[idx];
        } else {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            return 0;
        }
    }
};

<<<<<<< HEAD
AddressTableModel::AddressTableModel(CWallet *wallet, WalletModel *parent) :
    QAbstractTableModel(parent),walletModel(parent),wallet(wallet),priv(0)
=======
AddressTableModel::AddressTableModel(CWallet* wallet, WalletModel* parent) : QAbstractTableModel(parent), walletModel(parent), wallet(wallet), priv(0)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    columns << tr("Label") << tr("Address");
    priv = new AddressTablePriv(wallet, this);
    priv->refreshAddressTable();
}

AddressTableModel::~AddressTableModel()
{
    delete priv;
}

<<<<<<< HEAD
int AddressTableModel::rowCount(const QModelIndex &parent) const
=======
int AddressTableModel::rowCount(const QModelIndex& parent) const
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    Q_UNUSED(parent);
    return priv->size();
}

<<<<<<< HEAD
int AddressTableModel::columnCount(const QModelIndex &parent) const
=======
int AddressTableModel::columnCount(const QModelIndex& parent) const
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    Q_UNUSED(parent);
    return columns.length();
}

<<<<<<< HEAD
QVariant AddressTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    AddressTableEntry *rec = static_cast<AddressTableEntry*>(index.internalPointer());

    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch(index.column())
        {
        case Label:
            if(rec->label.isEmpty() && role == Qt::DisplayRole)
            {
                return tr("(no label)");
            }
            else
            {
=======
QVariant AddressTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    AddressTableEntry* rec = static_cast<AddressTableEntry*>(index.internalPointer());

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
        case Label:
            if (rec->label.isEmpty() && role == Qt::DisplayRole) {
                return tr("(no label)");
            } else {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                return rec->label;
            }
        case Address:
            return rec->address;
        }
<<<<<<< HEAD
    }
    else if (role == Qt::FontRole)
    {
        QFont font;
        if(index.column() == Address)
        {
            font = GUIUtil::fixedPitchFont();
        }
        return font;
    }
    else if (role == TypeRole)
    {
        switch(rec->type)
        {
=======
    } else if (role == Qt::FontRole) {
        QFont font;
        if (index.column() == Address) {
            font = GUIUtil::bitcoinAddressFont();
        }
        return font;
    } else if (role == TypeRole) {
        switch (rec->type) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        case AddressTableEntry::Sending:
            return Send;
        case AddressTableEntry::Receiving:
            return Receive;
<<<<<<< HEAD
        default: break;
=======
        default:
            break;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        }
    }
    return QVariant();
}

<<<<<<< HEAD
bool AddressTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
        return false;
    AddressTableEntry *rec = static_cast<AddressTableEntry*>(index.internalPointer());
    std::string strPurpose = (rec->type == AddressTableEntry::Sending ? "send" : "receive");
    editStatus = OK;

    if(role == Qt::EditRole)
    {
        LOCK(wallet->cs_wallet); /* For SetAddressBook / DelAddressBook */
        CTxDestination curAddress = CBitcoinAddress(rec->address.toStdString()).Get();
        if(index.column() == Label)
        {
            // Do nothing, if old label == new label
            if(rec->label == value.toString())
            {
=======
bool AddressTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid())
        return false;
    AddressTableEntry* rec = static_cast<AddressTableEntry*>(index.internalPointer());
    std::string strPurpose = (rec->type == AddressTableEntry::Sending ? "send" : "receive");
    editStatus = OK;

    if (role == Qt::EditRole) {
        LOCK(wallet->cs_wallet); /* For SetAddressBook / DelAddressBook */
        CTxDestination curAddress = CBitcoinAddress(rec->address.toStdString()).Get();
        if (index.column() == Label) {
            // Do nothing, if old label == new label
            if (rec->label == value.toString()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                editStatus = NO_CHANGES;
                return false;
            }
            wallet->SetAddressBook(curAddress, value.toString().toStdString(), strPurpose);
<<<<<<< HEAD
        } else if(index.column() == Address) {
            CTxDestination newAddress = CBitcoinAddress(value.toString().toStdString()).Get();
            // Refuse to set invalid address, set error status and return false
            if(boost::get<CNoDestination>(&newAddress))
            {
=======
        } else if (index.column() == Address) {
            CTxDestination newAddress = CBitcoinAddress(value.toString().toStdString()).Get();
            // Refuse to set invalid address, set error status and return false
            if (boost::get<CNoDestination>(&newAddress)) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                editStatus = INVALID_ADDRESS;
                return false;
            }
            // Do nothing, if old address == new address
<<<<<<< HEAD
            else if(newAddress == curAddress)
            {
=======
            else if (newAddress == curAddress) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                editStatus = NO_CHANGES;
                return false;
            }
            // Check for duplicate addresses to prevent accidental deletion of addresses, if you try
            // to paste an existing address over another address (with a different label)
<<<<<<< HEAD
            else if(wallet->mapAddressBook.count(newAddress))
            {
=======
            else if (wallet->mapAddressBook.count(newAddress)) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                editStatus = DUPLICATE_ADDRESS;
                return false;
            }
            // Double-check that we're not overwriting a receiving address
<<<<<<< HEAD
            else if(rec->type == AddressTableEntry::Sending)
            {
=======
            else if (rec->type == AddressTableEntry::Sending) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                // Remove old entry
                wallet->DelAddressBook(curAddress);
                // Add new entry with new address
                wallet->SetAddressBook(newAddress, rec->label.toStdString(), strPurpose);
            }
        }
        return true;
    }
    return false;
}

QVariant AddressTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
Qt::ItemFlags AddressTableModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return 0;
    AddressTableEntry *rec = static_cast<AddressTableEntry*>(index.internalPointer());
=======
Qt::ItemFlags AddressTableModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return 0;
    AddressTableEntry* rec = static_cast<AddressTableEntry*>(index.internalPointer());
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    Qt::ItemFlags retval = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    // Can edit address and label for sending addresses,
    // and only label for receiving addresses.
<<<<<<< HEAD
    if(rec->type == AddressTableEntry::Sending ||
      (rec->type == AddressTableEntry::Receiving && index.column()==Label))
    {
=======
    if (rec->type == AddressTableEntry::Sending ||
        (rec->type == AddressTableEntry::Receiving && index.column() == Label)) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        retval |= Qt::ItemIsEditable;
    }
    return retval;
}

<<<<<<< HEAD
QModelIndex AddressTableModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    AddressTableEntry *data = priv->index(row);
    if(data)
    {
        return createIndex(row, column, priv->index(row));
    }
    else
    {
=======
QModelIndex AddressTableModel::index(int row, int column, const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    AddressTableEntry* data = priv->index(row);
    if (data) {
        return createIndex(row, column, priv->index(row));
    } else {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return QModelIndex();
    }
}

<<<<<<< HEAD
void AddressTableModel::updateEntry(const QString &address,
        const QString &label, bool isMine, const QString &purpose, int status)
{
    // Update address book model from GelCoin core
    priv->updateEntry(address, label, isMine, purpose, status);
}

QString AddressTableModel::addRow(const QString &type, const QString &label, const QString &address)
=======
void AddressTableModel::updateEntry(const QString& address,
    const QString& label,
    bool isMine,
    const QString& purpose,
    int status)
{
    // Update address book model from Lux core
    priv->updateEntry(address, label, isMine, purpose, status);
}

QString AddressTableModel::addRow(const QString& type, const QString& label, const QString& address)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    std::string strLabel = label.toStdString();
    std::string strAddress = address.toStdString();

    editStatus = OK;

<<<<<<< HEAD
    if(type == Send)
    {
        if(!walletModel->validateAddress(address))
        {
=======
    if (type == Send) {
        if (!walletModel->validateAddress(address)) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            editStatus = INVALID_ADDRESS;
            return QString();
        }
        // Check for duplicate addresses
        {
            LOCK(wallet->cs_wallet);
<<<<<<< HEAD
            if(wallet->mapAddressBook.count(CBitcoinAddress(strAddress).Get()))
            {
=======
            if (wallet->mapAddressBook.count(CBitcoinAddress(strAddress).Get())) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                editStatus = DUPLICATE_ADDRESS;
                return QString();
            }
        }
<<<<<<< HEAD
    }
    else if(type == Receive)
    {
        // Generate a new address to associate with given label
        CPubKey newKey;
        if(!wallet->GetKeyFromPool(newKey, false))
        {
            WalletModel::UnlockContext ctx(walletModel->requestUnlock());
            if(!ctx.isValid())
            {
=======
    } else if (type == Receive) {
        // Generate a new address to associate with given label
        CPubKey newKey;
        if (!wallet->GetKeyFromPool(newKey)) {
            WalletModel::UnlockContext ctx(walletModel->requestUnlock(true));
            if (!ctx.isValid()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                // Unlock wallet failed or was cancelled
                editStatus = WALLET_UNLOCK_FAILURE;
                return QString();
            }
<<<<<<< HEAD
            if(!wallet->GetKeyFromPool(newKey, false))
            {
=======
            if (!wallet->GetKeyFromPool(newKey)) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                editStatus = KEY_GENERATION_FAILURE;
                return QString();
            }
        }
        strAddress = CBitcoinAddress(newKey.GetID()).ToString();
<<<<<<< HEAD
    }
    else
    {
=======
    } else {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return QString();
    }

    // Add entry
    {
        LOCK(wallet->cs_wallet);
        wallet->SetAddressBook(CBitcoinAddress(strAddress).Get(), strLabel,
<<<<<<< HEAD
                               (type == Send ? "send" : "receive"));
=======
            (type == Send ? "send" : "receive"));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }
    return QString::fromStdString(strAddress);
}

<<<<<<< HEAD
bool AddressTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    AddressTableEntry *rec = priv->index(row);
    if(count != 1 || !rec || rec->type == AddressTableEntry::Receiving)
    {
=======
bool AddressTableModel::removeRows(int row, int count, const QModelIndex& parent)
{
    Q_UNUSED(parent);
    AddressTableEntry* rec = priv->index(row);
    if (count != 1 || !rec || rec->type == AddressTableEntry::Receiving) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        // Can only remove one row at a time, and cannot remove rows not in model.
        // Also refuse to remove receiving addresses.
        return false;
    }
    {
        LOCK(wallet->cs_wallet);
        wallet->DelAddressBook(CBitcoinAddress(rec->address.toStdString()).Get());
    }
    return true;
}

/* Look up label for address in address book, if not found return empty string.
 */
<<<<<<< HEAD
QString AddressTableModel::labelForAddress(const QString &address) const
=======
QString AddressTableModel::labelForAddress(const QString& address) const
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    {
        LOCK(wallet->cs_wallet);
        CBitcoinAddress address_parsed(address.toStdString());
        std::map<CTxDestination, CAddressBookData>::iterator mi = wallet->mapAddressBook.find(address_parsed.Get());
<<<<<<< HEAD
        if (mi != wallet->mapAddressBook.end())
        {
=======
        if (mi != wallet->mapAddressBook.end()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            return QString::fromStdString(mi->second.name);
        }
    }
    return QString();
}

<<<<<<< HEAD
int AddressTableModel::lookupAddress(const QString &address) const
{
    QModelIndexList lst = match(index(0, Address, QModelIndex()),
                                Qt::EditRole, address, 1, Qt::MatchExactly);
    if(lst.isEmpty())
    {
        return -1;
    }
    else
    {
=======
int AddressTableModel::lookupAddress(const QString& address) const
{
    QModelIndexList lst = match(index(0, Address, QModelIndex()),
        Qt::EditRole, address, 1, Qt::MatchExactly);
    if (lst.isEmpty()) {
        return -1;
    } else {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return lst.at(0).row();
    }
}

void AddressTableModel::emitDataChanged(int idx)
{
<<<<<<< HEAD
    Q_EMIT dataChanged(index(idx, 0, QModelIndex()), index(idx, columns.length()-1, QModelIndex()));
=======
    emit dataChanged(index(idx, 0, QModelIndex()), index(idx, columns.length() - 1, QModelIndex()));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}
