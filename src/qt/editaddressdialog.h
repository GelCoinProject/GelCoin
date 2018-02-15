<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_EDITADDRESSDIALOG_H
#define BITCOIN_QT_EDITADDRESSDIALOG_H

#include <QDialog>

class AddressTableModel;

<<<<<<< HEAD
namespace Ui {
    class EditAddressDialog;
=======
namespace Ui
{
class EditAddressDialog;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

QT_BEGIN_NAMESPACE
class QDataWidgetMapper;
QT_END_NAMESPACE

/** Dialog for editing an address and associated information.
 */
class EditAddressDialog : public QDialog
{
    Q_OBJECT

public:
    enum Mode {
        NewReceivingAddress,
        NewSendingAddress,
        EditReceivingAddress,
        EditSendingAddress
    };

<<<<<<< HEAD
    explicit EditAddressDialog(Mode mode, QWidget *parent);
    ~EditAddressDialog();

    void setModel(AddressTableModel *model);
    void loadRow(int row);

    QString getAddress() const;
    void setAddress(const QString &address);

public Q_SLOTS:
=======
    explicit EditAddressDialog(Mode mode, QWidget* parent);
    ~EditAddressDialog();

    void setModel(AddressTableModel* model);
    void loadRow(int row);

    QString getAddress() const;
    void setAddress(const QString& address);

public slots:
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void accept();

private:
    bool saveCurrentRow();

<<<<<<< HEAD
    Ui::EditAddressDialog *ui;
    QDataWidgetMapper *mapper;
    Mode mode;
    AddressTableModel *model;
=======
    Ui::EditAddressDialog* ui;
    QDataWidgetMapper* mapper;
    Mode mode;
    AddressTableModel* model;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    QString address;
};

#endif // BITCOIN_QT_EDITADDRESSDIALOG_H
