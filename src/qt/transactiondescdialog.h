<<<<<<< HEAD
// Copyright (c) 2011-2013 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_TRANSACTIONDESCDIALOG_H
#define BITCOIN_QT_TRANSACTIONDESCDIALOG_H

#include <QDialog>

<<<<<<< HEAD
namespace Ui {
    class TransactionDescDialog;
=======
namespace Ui
{
class TransactionDescDialog;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

/** Dialog showing transaction details. */
class TransactionDescDialog : public QDialog
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit TransactionDescDialog(const QModelIndex &idx, QWidget *parent = 0);
    ~TransactionDescDialog();

private:
    Ui::TransactionDescDialog *ui;
=======
    explicit TransactionDescDialog(const QModelIndex& idx, QWidget* parent = 0);
    ~TransactionDescDialog();

private:
    Ui::TransactionDescDialog* ui;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};

#endif // BITCOIN_QT_TRANSACTIONDESCDIALOG_H
