<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_ADDRESSBOOKPAGE_H
#define BITCOIN_QT_ADDRESSBOOKPAGE_H

#include <QDialog>

class AddressTableModel;
class OptionsModel;
<<<<<<< HEAD
class PlatformStyle;

namespace Ui {
    class AddressBookPage;
=======

namespace Ui
{
class AddressBookPage;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

QT_BEGIN_NAMESPACE
class QItemSelection;
class QMenu;
class QModelIndex;
class QSortFilterProxyModel;
class QTableView;
QT_END_NAMESPACE

/** Widget that shows a list of sending or receiving addresses.
  */
class AddressBookPage : public QDialog
{
    Q_OBJECT

public:
    enum Tabs {
        SendingTab = 0,
        ReceivingTab = 1
    };

    enum Mode {
        ForSelection, /**< Open address book to pick address */
<<<<<<< HEAD
        ForEditing  /**< Open address book for editing */
    };

    explicit AddressBookPage(const PlatformStyle *platformStyle, Mode mode, Tabs tab, QWidget *parent);
    ~AddressBookPage();

    void setModel(AddressTableModel *model);
    const QString &getReturnValue() const { return returnValue; }

public Q_SLOTS:
    void done(int retval);

private:
    Ui::AddressBookPage *ui;
    AddressTableModel *model;
    Mode mode;
    Tabs tab;
    QString returnValue;
    QSortFilterProxyModel *proxyModel;
    QMenu *contextMenu;
    QAction *deleteAction; // to be able to explicitly disable it
    QString newAddressToSelect;

private Q_SLOTS:
=======
        ForEditing    /**< Open address book for editing */
    };

    explicit AddressBookPage(Mode mode, Tabs tab, QWidget* parent);
    ~AddressBookPage();

    void setModel(AddressTableModel* model);
    const QString& getReturnValue() const { return returnValue; }

public slots:
    void done(int retval);

private:
    Ui::AddressBookPage* ui;
    AddressTableModel* model;
    Mode mode;
    Tabs tab;
    QString returnValue;
    QSortFilterProxyModel* proxyModel;
    QMenu* contextMenu;
    QAction* deleteAction; // to be able to explicitly disable it
    QString newAddressToSelect;

private slots:
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    /** Delete currently selected address entry */
    void on_deleteAddress_clicked();
    /** Create a new address for receiving coins and / or add a new address book entry */
    void on_newAddress_clicked();
    /** Copy address of currently selected address entry to clipboard */
    void on_copyAddress_clicked();
    /** Copy label of currently selected address entry to clipboard (no button) */
    void onCopyLabelAction();
    /** Edit currently selected address entry (no button) */
    void onEditAction();
    /** Export button clicked */
    void on_exportButton_clicked();

    /** Set button states based on selected tab and selection */
    void selectionChanged();
    /** Spawn contextual menu (right mouse menu) for address book entry */
<<<<<<< HEAD
    void contextualMenu(const QPoint &point);
    /** New entry/entries were added to address table */
    void selectNewAddress(const QModelIndex &parent, int begin, int /*end*/);

Q_SIGNALS:
=======
    void contextualMenu(const QPoint& point);
    /** New entry/entries were added to address table */
    void selectNewAddress(const QModelIndex& parent, int begin, int /*end*/);

signals:
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void sendCoins(QString addr);
};

#endif // BITCOIN_QT_ADDRESSBOOKPAGE_H
