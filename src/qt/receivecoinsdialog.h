<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_RECEIVECOINSDIALOG_H
#define BITCOIN_QT_RECEIVECOINSDIALOG_H

#include "guiutil.h"

#include <QDialog>
#include <QHeaderView>
#include <QItemSelection>
#include <QKeyEvent>
#include <QMenu>
#include <QPoint>
#include <QVariant>

class OptionsModel;
<<<<<<< HEAD
class PlatformStyle;
class WalletModel;

namespace Ui {
    class ReceiveCoinsDialog;
=======
class WalletModel;

namespace Ui
{
class ReceiveCoinsDialog;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

/** Dialog for requesting payment of bitcoins */
class ReceiveCoinsDialog : public QDialog
{
    Q_OBJECT

public:
    enum ColumnWidths {
        DATE_COLUMN_WIDTH = 130,
        LABEL_COLUMN_WIDTH = 120,
        AMOUNT_MINIMUM_COLUMN_WIDTH = 160,
        MINIMUM_COLUMN_WIDTH = 130
    };

<<<<<<< HEAD
    explicit ReceiveCoinsDialog(const PlatformStyle *platformStyle, QWidget *parent = 0);
    ~ReceiveCoinsDialog();

    void setModel(WalletModel *model);

public Q_SLOTS:
=======
    explicit ReceiveCoinsDialog(QWidget* parent = 0);
    ~ReceiveCoinsDialog();

    void setModel(WalletModel* model);

public slots:
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void clear();
    void reject();
    void accept();

protected:
<<<<<<< HEAD
    virtual void keyPressEvent(QKeyEvent *event);

private:
    Ui::ReceiveCoinsDialog *ui;
    GUIUtil::TableViewLastColumnResizingFixer *columnResizingFixer;
    WalletModel *model;
    QMenu *contextMenu;
    const PlatformStyle *platformStyle;

    QModelIndex selectedRow();
    void copyColumnToClipboard(int column);
    virtual void resizeEvent(QResizeEvent *event);

private Q_SLOTS:
    void on_receiveButton_clicked();
    void on_showRequestButton_clicked();
    void on_removeRequestButton_clicked();
    void on_recentRequestsView_doubleClicked(const QModelIndex &index);
    void recentRequestsView_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void updateDisplayUnit();
    void showMenu(const QPoint &point);
    void copyURI();
=======
    virtual void keyPressEvent(QKeyEvent* event);

private:
    Ui::ReceiveCoinsDialog* ui;
    GUIUtil::TableViewLastColumnResizingFixer* columnResizingFixer;
    WalletModel* model;
    QMenu* contextMenu;
    void copyColumnToClipboard(int column);
    virtual void resizeEvent(QResizeEvent* event);

private slots:
    void on_receiveButton_clicked();
    void on_showRequestButton_clicked();
    void on_removeRequestButton_clicked();
    void on_recentRequestsView_doubleClicked(const QModelIndex& index);
    void recentRequestsView_selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
    void updateDisplayUnit();
    void showMenu(const QPoint& point);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void copyLabel();
    void copyMessage();
    void copyAmount();
};

#endif // BITCOIN_QT_RECEIVECOINSDIALOG_H
