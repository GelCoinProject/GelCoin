<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "receivecoinsdialog.h"
#include "ui_receivecoinsdialog.h"

#include "addressbookpage.h"
#include "addresstablemodel.h"
#include "bitcoinunits.h"
#include "guiutil.h"
#include "optionsmodel.h"
<<<<<<< HEAD
#include "platformstyle.h"
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include "receiverequestdialog.h"
#include "recentrequeststablemodel.h"
#include "walletmodel.h"

#include <QAction>
#include <QCursor>
#include <QItemSelection>
#include <QMessageBox>
#include <QScrollBar>
#include <QTextDocument>

<<<<<<< HEAD
ReceiveCoinsDialog::ReceiveCoinsDialog(const PlatformStyle *platformStyle, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReceiveCoinsDialog),
    columnResizingFixer(0),
    model(0),
    platformStyle(platformStyle)
{
    ui->setupUi(this);
    QString theme = GUIUtil::getThemeName();
    
    if (!platformStyle->getImagesOnButtons()) {
        ui->clearButton->setIcon(QIcon());
        ui->receiveButton->setIcon(QIcon());
        ui->showRequestButton->setIcon(QIcon());
        ui->removeRequestButton->setIcon(QIcon());
    } else {
        ui->clearButton->setIcon(QIcon(":/icons/" + theme + "/remove"));
        ui->receiveButton->setIcon(QIcon(":/icons/" + theme + "/receiving_addresses"));
        ui->showRequestButton->setIcon(QIcon(":/icons/" + theme + "/edit"));
        ui->removeRequestButton->setIcon(QIcon(":/icons/" + theme + "/remove"));
    }

    // context menu actions
    QAction *copyURIAction = new QAction(tr("Copy URI"), this);
    QAction *copyLabelAction = new QAction(tr("Copy label"), this);
    QAction *copyMessageAction = new QAction(tr("Copy message"), this);
    QAction *copyAmountAction = new QAction(tr("Copy amount"), this);

    // context menu
    contextMenu = new QMenu(this);
    contextMenu->addAction(copyURIAction);
=======
ReceiveCoinsDialog::ReceiveCoinsDialog(QWidget* parent) : QDialog(parent),
                                                          ui(new Ui::ReceiveCoinsDialog),
                                                          model(0)
{
    ui->setupUi(this);

#ifdef Q_OS_MAC // Icons on push buttons are very uncommon on Mac
    ui->clearButton->setIcon(QIcon());
    ui->receiveButton->setIcon(QIcon());
    ui->showRequestButton->setIcon(QIcon());
    ui->removeRequestButton->setIcon(QIcon());
#endif

    // context menu actions
    QAction* copyLabelAction = new QAction(tr("Copy label"), this);
    QAction* copyMessageAction = new QAction(tr("Copy message"), this);
    QAction* copyAmountAction = new QAction(tr("Copy amount"), this);

    // context menu
    contextMenu = new QMenu();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    contextMenu->addAction(copyLabelAction);
    contextMenu->addAction(copyMessageAction);
    contextMenu->addAction(copyAmountAction);

    // context menu signals
    connect(ui->recentRequestsView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showMenu(QPoint)));
<<<<<<< HEAD
    connect(copyURIAction, SIGNAL(triggered()), this, SLOT(copyURI()));
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    connect(copyLabelAction, SIGNAL(triggered()), this, SLOT(copyLabel()));
    connect(copyMessageAction, SIGNAL(triggered()), this, SLOT(copyMessage()));
    connect(copyAmountAction, SIGNAL(triggered()), this, SLOT(copyAmount()));

    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clear()));
}

<<<<<<< HEAD
void ReceiveCoinsDialog::setModel(WalletModel *model)
{
    this->model = model;

    if(model && model->getOptionsModel())
    {
=======
void ReceiveCoinsDialog::setModel(WalletModel* model)
{
    this->model = model;

    if (model && model->getOptionsModel()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        model->getRecentRequestsTableModel()->sort(RecentRequestsTableModel::Date, Qt::DescendingOrder);
        connect(model->getOptionsModel(), SIGNAL(displayUnitChanged(int)), this, SLOT(updateDisplayUnit()));
        updateDisplayUnit();

        QTableView* tableView = ui->recentRequestsView;

        tableView->verticalHeader()->hide();
        tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableView->setModel(model->getRecentRequestsTableModel());
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setSelectionMode(QAbstractItemView::ContiguousSelection);
        tableView->setColumnWidth(RecentRequestsTableModel::Date, DATE_COLUMN_WIDTH);
        tableView->setColumnWidth(RecentRequestsTableModel::Label, LABEL_COLUMN_WIDTH);

        connect(tableView->selectionModel(),
            SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
            SLOT(recentRequestsView_selectionChanged(QItemSelection, QItemSelection)));
        // Last 2 columns are set by the columnResizingFixer, when the table geometry is ready.
<<<<<<< HEAD
        columnResizingFixer = new GUIUtil::TableViewLastColumnResizingFixer(tableView, AMOUNT_MINIMUM_COLUMN_WIDTH, DATE_COLUMN_WIDTH, this);
=======
        columnResizingFixer = new GUIUtil::TableViewLastColumnResizingFixer(tableView, AMOUNT_MINIMUM_COLUMN_WIDTH, DATE_COLUMN_WIDTH);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }
}

ReceiveCoinsDialog::~ReceiveCoinsDialog()
{
    delete ui;
}

void ReceiveCoinsDialog::clear()
{
    ui->reqAmount->clear();
    ui->reqLabel->setText("");
    ui->reqMessage->setText("");
    ui->reuseAddress->setChecked(false);
    updateDisplayUnit();
}

void ReceiveCoinsDialog::reject()
{
    clear();
}

void ReceiveCoinsDialog::accept()
{
    clear();
}

void ReceiveCoinsDialog::updateDisplayUnit()
{
<<<<<<< HEAD
    if(model && model->getOptionsModel())
    {
=======
    if (model && model->getOptionsModel()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        ui->reqAmount->setDisplayUnit(model->getOptionsModel()->getDisplayUnit());
    }
}

void ReceiveCoinsDialog::on_receiveButton_clicked()
{
<<<<<<< HEAD
    if(!model || !model->getOptionsModel() || !model->getAddressTableModel() || !model->getRecentRequestsTableModel())
=======
    if (!model || !model->getOptionsModel() || !model->getAddressTableModel() || !model->getRecentRequestsTableModel())
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return;

    QString address;
    QString label = ui->reqLabel->text();
<<<<<<< HEAD
    if(ui->reuseAddress->isChecked())
    {
        /* Choose existing receiving address */
        AddressBookPage dlg(platformStyle, AddressBookPage::ForSelection, AddressBookPage::ReceivingTab, this);
        dlg.setModel(model->getAddressTableModel());
        if(dlg.exec())
        {
            address = dlg.getReturnValue();
            if(label.isEmpty()) /* If no label provided, use the previously used label */
=======
    if (ui->reuseAddress->isChecked()) {
        /* Choose existing receiving address */
        AddressBookPage dlg(AddressBookPage::ForSelection, AddressBookPage::ReceivingTab, this);
        dlg.setModel(model->getAddressTableModel());
        if (dlg.exec()) {
            address = dlg.getReturnValue();
            if (label.isEmpty()) /* If no label provided, use the previously used label */
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            {
                label = model->getAddressTableModel()->labelForAddress(address);
            }
        } else {
            return;
        }
    } else {
        /* Generate new receiving address */
        address = model->getAddressTableModel()->addRow(AddressTableModel::Receive, label, "");
    }
    SendCoinsRecipient info(address, label,
        ui->reqAmount->value(), ui->reqMessage->text());
<<<<<<< HEAD
    info.fUseInstantSend = ui->checkUseInstantSend->isChecked();
    ReceiveRequestDialog *dialog = new ReceiveRequestDialog(this);
=======
    ReceiveRequestDialog* dialog = new ReceiveRequestDialog(this);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setModel(model->getOptionsModel());
    dialog->setInfo(info);
    dialog->show();
    clear();

    /* Store request for later reference */
    model->getRecentRequestsTableModel()->addNewRequest(info);
}

<<<<<<< HEAD
void ReceiveCoinsDialog::on_recentRequestsView_doubleClicked(const QModelIndex &index)
{
    const RecentRequestsTableModel *submodel = model->getRecentRequestsTableModel();
    ReceiveRequestDialog *dialog = new ReceiveRequestDialog(this);
=======
void ReceiveCoinsDialog::on_recentRequestsView_doubleClicked(const QModelIndex& index)
{
    const RecentRequestsTableModel* submodel = model->getRecentRequestsTableModel();
    ReceiveRequestDialog* dialog = new ReceiveRequestDialog(this);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    dialog->setModel(model->getOptionsModel());
    dialog->setInfo(submodel->entry(index.row()).recipient);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

<<<<<<< HEAD
void ReceiveCoinsDialog::recentRequestsView_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
=======
void ReceiveCoinsDialog::recentRequestsView_selectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    // Enable Show/Remove buttons only if anything is selected.
    bool enable = !ui->recentRequestsView->selectionModel()->selectedRows().isEmpty();
    ui->showRequestButton->setEnabled(enable);
    ui->removeRequestButton->setEnabled(enable);
}

void ReceiveCoinsDialog::on_showRequestButton_clicked()
{
<<<<<<< HEAD
    if(!model || !model->getRecentRequestsTableModel() || !ui->recentRequestsView->selectionModel())
        return;
    QModelIndexList selection = ui->recentRequestsView->selectionModel()->selectedRows();

    Q_FOREACH (const QModelIndex& index, selection) {
=======
    if (!model || !model->getRecentRequestsTableModel() || !ui->recentRequestsView->selectionModel())
        return;
    QModelIndexList selection = ui->recentRequestsView->selectionModel()->selectedRows();

    foreach (QModelIndex index, selection) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        on_recentRequestsView_doubleClicked(index);
    }
}

void ReceiveCoinsDialog::on_removeRequestButton_clicked()
{
<<<<<<< HEAD
    if(!model || !model->getRecentRequestsTableModel() || !ui->recentRequestsView->selectionModel())
        return;
    QModelIndexList selection = ui->recentRequestsView->selectionModel()->selectedRows();
    if(selection.empty())
=======
    if (!model || !model->getRecentRequestsTableModel() || !ui->recentRequestsView->selectionModel())
        return;
    QModelIndexList selection = ui->recentRequestsView->selectionModel()->selectedRows();
    if (selection.empty())
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return;
    // correct for selection mode ContiguousSelection
    QModelIndex firstIndex = selection.at(0);
    model->getRecentRequestsTableModel()->removeRows(firstIndex.row(), selection.length(), firstIndex.parent());
}

// We override the virtual resizeEvent of the QWidget to adjust tables column
// sizes as the tables width is proportional to the dialogs width.
<<<<<<< HEAD
void ReceiveCoinsDialog::resizeEvent(QResizeEvent *event)
=======
void ReceiveCoinsDialog::resizeEvent(QResizeEvent* event)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    QWidget::resizeEvent(event);
    columnResizingFixer->stretchColumnWidth(RecentRequestsTableModel::Message);
}

<<<<<<< HEAD
void ReceiveCoinsDialog::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
    {
        // press return -> submit form
        if (ui->reqLabel->hasFocus() || ui->reqAmount->hasFocus() || ui->reqMessage->hasFocus())
        {
=======
void ReceiveCoinsDialog::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Return) {
        // press return -> submit form
        if (ui->reqLabel->hasFocus() || ui->reqAmount->hasFocus() || ui->reqMessage->hasFocus()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            event->ignore();
            on_receiveButton_clicked();
            return;
        }
    }

    this->QDialog::keyPressEvent(event);
}

<<<<<<< HEAD
QModelIndex ReceiveCoinsDialog::selectedRow()
{
    if(!model || !model->getRecentRequestsTableModel() || !ui->recentRequestsView->selectionModel())
        return QModelIndex();
    QModelIndexList selection = ui->recentRequestsView->selectionModel()->selectedRows();
    if(selection.empty())
        return QModelIndex();
    // correct for selection mode ContiguousSelection
    QModelIndex firstIndex = selection.at(0);
    return firstIndex;
}

// copy column of selected row to clipboard
void ReceiveCoinsDialog::copyColumnToClipboard(int column)
{
    QModelIndex firstIndex = selectedRow();
    if (!firstIndex.isValid()) {
        return;
    }
=======
// copy column of selected row to clipboard
void ReceiveCoinsDialog::copyColumnToClipboard(int column)
{
    if (!model || !model->getRecentRequestsTableModel() || !ui->recentRequestsView->selectionModel())
        return;
    QModelIndexList selection = ui->recentRequestsView->selectionModel()->selectedRows();
    if (selection.empty())
        return;
    // correct for selection mode ContiguousSelection
    QModelIndex firstIndex = selection.at(0);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    GUIUtil::setClipboard(model->getRecentRequestsTableModel()->data(firstIndex.child(firstIndex.row(), column), Qt::EditRole).toString());
}

// context menu
<<<<<<< HEAD
void ReceiveCoinsDialog::showMenu(const QPoint &point)
{
    if (!selectedRow().isValid()) {
        return;
    }
    contextMenu->exec(QCursor::pos());
}

// context menu action: copy URI
void ReceiveCoinsDialog::copyURI()
{
    QModelIndex sel = selectedRow();
    if (!sel.isValid()) {
        return;
    }

    const RecentRequestsTableModel * const submodel = model->getRecentRequestsTableModel();
    const QString uri = GUIUtil::formatBitcoinURI(submodel->entry(sel.row()).recipient);
    GUIUtil::setClipboard(uri);
=======
void ReceiveCoinsDialog::showMenu(const QPoint& point)
{
    if (!model || !model->getRecentRequestsTableModel() || !ui->recentRequestsView->selectionModel())
        return;
    QModelIndexList selection = ui->recentRequestsView->selectionModel()->selectedRows();
    if (selection.empty())
        return;
    contextMenu->exec(QCursor::pos());
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

// context menu action: copy label
void ReceiveCoinsDialog::copyLabel()
{
    copyColumnToClipboard(RecentRequestsTableModel::Label);
}

// context menu action: copy message
void ReceiveCoinsDialog::copyMessage()
{
    copyColumnToClipboard(RecentRequestsTableModel::Message);
}

// context menu action: copy amount
void ReceiveCoinsDialog::copyAmount()
{
    copyColumnToClipboard(RecentRequestsTableModel::Amount);
}
