<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_SENDCOINSENTRY_H
#define BITCOIN_QT_SENDCOINSENTRY_H

#include "walletmodel.h"

#include <QStackedWidget>

class WalletModel;
<<<<<<< HEAD
class PlatformStyle;

namespace Ui {
    class SendCoinsEntry;
=======

namespace Ui
{
class SendCoinsEntry;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

/**
 * A single entry in the dialog for sending bitcoins.
 * Stacked widget, with different UIs for payment requests
 * with a strong payee identity.
 */
class SendCoinsEntry : public QStackedWidget
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit SendCoinsEntry(const PlatformStyle *platformStyle, QWidget *parent = 0);
    ~SendCoinsEntry();

    void setModel(WalletModel *model);
=======
    explicit SendCoinsEntry(QWidget* parent = 0);
    ~SendCoinsEntry();

    void setModel(WalletModel* model);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    bool validate();
    SendCoinsRecipient getValue();

    /** Return whether the entry is still empty and unedited */
    bool isClear();

<<<<<<< HEAD
    void setValue(const SendCoinsRecipient &value);
    void setAddress(const QString &address);
=======
    void setValue(const SendCoinsRecipient& value);
    void setAddress(const QString& address);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    /** Set up the tab chain manually, as Qt messes up the tab chain by default in some cases
     *  (issue https://bugreports.qt-project.org/browse/QTBUG-10907).
     */
<<<<<<< HEAD
    QWidget *setupTabChain(QWidget *prev);

    void setFocus();

public Q_SLOTS:
    void clear();

Q_SIGNALS:
    void removeEntry(SendCoinsEntry *entry);
    void payAmountChanged();
    void subtractFeeFromAmountChanged();

private Q_SLOTS:
    void deleteClicked();
    void on_payTo_textChanged(const QString &address);
=======
    QWidget* setupTabChain(QWidget* prev);

    void setFocus();

public slots:
    void clear();

signals:
    void removeEntry(SendCoinsEntry* entry);
    void payAmountChanged();

private slots:
    void deleteClicked();
    void on_payTo_textChanged(const QString& address);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void on_addressBookButton_clicked();
    void on_pasteButton_clicked();
    void updateDisplayUnit();

private:
    SendCoinsRecipient recipient;
<<<<<<< HEAD
    Ui::SendCoinsEntry *ui;
    WalletModel *model;
    const PlatformStyle *platformStyle;

    bool updateLabel(const QString &address);
=======
    Ui::SendCoinsEntry* ui;
    WalletModel* model;

    bool updateLabel(const QString& address);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};

#endif // BITCOIN_QT_SENDCOINSENTRY_H
