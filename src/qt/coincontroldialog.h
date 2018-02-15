<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_COINCONTROLDIALOG_H
#define BITCOIN_QT_COINCONTROLDIALOG_H

#include "amount.h"

#include <QAbstractButton>
#include <QAction>
#include <QDialog>
#include <QList>
#include <QMenu>
#include <QPoint>
#include <QString>
#include <QTreeWidgetItem>

<<<<<<< HEAD
class PlatformStyle;
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
class WalletModel;

class CCoinControl;
class CTxMemPool;

<<<<<<< HEAD
namespace Ui {
    class CoinControlDialog;
}

#define ASYMP_UTF8 "\xE2\x89\x88"

=======
namespace Ui
{
class CoinControlDialog;
}

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
class CoinControlDialog : public QDialog
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit CoinControlDialog(const PlatformStyle *platformStyle, QWidget *parent = 0);
    ~CoinControlDialog();

    void setModel(WalletModel *model);

    // static because also called from sendcoinsdialog
    static void updateLabels(WalletModel*, QDialog*);

    static QList<CAmount> payAmounts;
    static CCoinControl *coinControl;
    static bool fSubtractFeeFromAmount;

private:
    Ui::CoinControlDialog *ui;
    WalletModel *model;
    int sortColumn;
    Qt::SortOrder sortOrder;

    QMenu *contextMenu;
    QTreeWidgetItem *contextMenuItem;
    QAction *copyTransactionHashAction;
    QAction *lockAction;
    QAction *unlockAction;

    const PlatformStyle *platformStyle;
=======
    explicit CoinControlDialog(QWidget* parent = 0);
    ~CoinControlDialog();

    void setModel(WalletModel* model);

    // static because also called from sendcoinsdialog
    static void updateLabels(WalletModel*, QDialog*);
    static QString getPriorityLabel(double dPriority, double mempoolEstimatePriority);

    static QList<CAmount> payAmounts;
    static CCoinControl* coinControl;
    static int nSplitBlockDummy;

private:
    Ui::CoinControlDialog* ui;
    WalletModel* model;
    int sortColumn;
    Qt::SortOrder sortOrder;

    QMenu* contextMenu;
    QTreeWidgetItem* contextMenuItem;
    QAction* copyTransactionHashAction;
    QAction* lockAction;
    QAction* unlockAction;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    QString strPad(QString, int, QString);
    void sortView(int, Qt::SortOrder);
    void updateView();

<<<<<<< HEAD
    enum
    {
=======
    enum {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        COLUMN_CHECKBOX,
        COLUMN_AMOUNT,
        COLUMN_LABEL,
        COLUMN_ADDRESS,
<<<<<<< HEAD
        COLUMN_PRIVATESEND_ROUNDS,
        COLUMN_DATE,
        COLUMN_CONFIRMATIONS,
        COLUMN_TXHASH,
        COLUMN_VOUT_INDEX,
        COLUMN_AMOUNT_INT64,
=======
        COLUMN_OBFUSCATION_ROUNDS,
        COLUMN_DATE,
        COLUMN_CONFIRMATIONS,
        COLUMN_PRIORITY,
        COLUMN_TXHASH,
        COLUMN_VOUT_INDEX,
        COLUMN_AMOUNT_INT64,
        COLUMN_PRIORITY_INT64,
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        COLUMN_DATE_INT64
    };

    // some columns have a hidden column containing the value used for sorting
    int getMappedColumn(int column, bool fVisibleColumn = true)
    {
<<<<<<< HEAD
        if (fVisibleColumn)
        {
            if (column == COLUMN_AMOUNT_INT64)
                return COLUMN_AMOUNT;
            else if (column == COLUMN_DATE_INT64)
                return COLUMN_DATE;
        }
        else
        {
            if (column == COLUMN_AMOUNT)
                return COLUMN_AMOUNT_INT64;
=======
        if (fVisibleColumn) {
            if (column == COLUMN_AMOUNT_INT64)
                return COLUMN_AMOUNT;
            else if (column == COLUMN_PRIORITY_INT64)
                return COLUMN_PRIORITY;
            else if (column == COLUMN_DATE_INT64)
                return COLUMN_DATE;
        } else {
            if (column == COLUMN_AMOUNT)
                return COLUMN_AMOUNT_INT64;
            else if (column == COLUMN_PRIORITY)
                return COLUMN_PRIORITY_INT64;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            else if (column == COLUMN_DATE)
                return COLUMN_DATE_INT64;
        }

        return column;
    }

<<<<<<< HEAD
private Q_SLOTS:
    void showMenu(const QPoint &);
=======
private slots:
    void showMenu(const QPoint&);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void copyAmount();
    void copyLabel();
    void copyAddress();
    void copyTransactionHash();
    void lockCoin();
    void unlockCoin();
    void clipboardQuantity();
    void clipboardAmount();
    void clipboardFee();
    void clipboardAfterFee();
    void clipboardBytes();
<<<<<<< HEAD
=======
    void clipboardPriority();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void clipboardLowOutput();
    void clipboardChange();
    void radioTreeMode(bool);
    void radioListMode(bool);
    void viewItemChanged(QTreeWidgetItem*, int);
    void headerSectionClicked(int);
    void buttonBoxClicked(QAbstractButton*);
    void buttonSelectAllClicked();
    void buttonToggleLockClicked();
    void updateLabelLocked();
};

#endif // BITCOIN_QT_COINCONTROLDIALOG_H
