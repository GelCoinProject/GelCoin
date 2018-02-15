<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_SIGNVERIFYMESSAGEDIALOG_H
#define BITCOIN_QT_SIGNVERIFYMESSAGEDIALOG_H

#include <QDialog>

<<<<<<< HEAD
class PlatformStyle;
class WalletModel;

namespace Ui {
    class SignVerifyMessageDialog;
=======
class WalletModel;

namespace Ui
{
class SignVerifyMessageDialog;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

class SignVerifyMessageDialog : public QDialog
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit SignVerifyMessageDialog(const PlatformStyle *platformStyle, QWidget *parent);
    ~SignVerifyMessageDialog();

    void setModel(WalletModel *model);
    void setAddress_SM(const QString &address);
    void setAddress_VM(const QString &address);
=======
    explicit SignVerifyMessageDialog(QWidget* parent);
    ~SignVerifyMessageDialog();

    void setModel(WalletModel* model);
    void setAddress_SM(const QString& address);
    void setAddress_VM(const QString& address);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    void showTab_SM(bool fShow);
    void showTab_VM(bool fShow);

protected:
<<<<<<< HEAD
    bool eventFilter(QObject *object, QEvent *event);

private:
    Ui::SignVerifyMessageDialog *ui;
    WalletModel *model;
    const PlatformStyle *platformStyle;

private Q_SLOTS:
=======
    bool eventFilter(QObject* object, QEvent* event);

private:
    Ui::SignVerifyMessageDialog* ui;
    WalletModel* model;

private slots:
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    /* sign message */
    void on_addressBookButton_SM_clicked();
    void on_pasteButton_SM_clicked();
    void on_signMessageButton_SM_clicked();
    void on_copySignatureButton_SM_clicked();
    void on_clearButton_SM_clicked();
    /* verify message */
    void on_addressBookButton_VM_clicked();
    void on_verifyMessageButton_VM_clicked();
    void on_clearButton_VM_clicked();
};

#endif // BITCOIN_QT_SIGNVERIFYMESSAGEDIALOG_H
