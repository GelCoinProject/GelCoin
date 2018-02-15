<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "transactionview.h"

#include "addresstablemodel.h"
#include "bitcoinunits.h"
#include "csvmodelwriter.h"
#include "editaddressdialog.h"
#include "guiutil.h"
#include "optionsmodel.h"
<<<<<<< HEAD
#include "platformstyle.h"
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include "transactiondescdialog.h"
#include "transactionfilterproxy.h"
#include "transactionrecord.h"
#include "transactiontablemodel.h"
#include "walletmodel.h"

#include "ui_interface.h"

#include <QComboBox>
#include <QDateTimeEdit>
#include <QDesktopServices>
#include <QDoubleValidator>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QPoint>
#include <QScrollBar>
#include <QSettings>
#include <QSignalMapper>
#include <QTableView>
#include <QUrl>
#include <QVBoxLayout>

<<<<<<< HEAD
/** Date format for persistence */
static const char* PERSISTENCE_DATE_FORMAT = "yyyy-MM-dd";

TransactionView::TransactionView(const PlatformStyle *platformStyle, QWidget *parent) :
    QWidget(parent), model(0), transactionProxyModel(0),
    transactionView(0), abandonAction(0), columnResizingFixer(0)
{
    QSettings settings;
    // Build filter row
    setContentsMargins(0,0,0,0);

    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->setContentsMargins(0,0,0,0);
    if (platformStyle->getUseExtraSpacing()) {
        hlayout->setSpacing(0);
        hlayout->addSpacing(6);
    } else {
        hlayout->setSpacing(1);
        hlayout->addSpacing(5);
    }
    QString theme = GUIUtil::getThemeName();
    watchOnlyWidget = new QComboBox(this);
    watchOnlyWidget->setFixedWidth(24);
    watchOnlyWidget->addItem("", TransactionFilterProxy::WatchOnlyFilter_All);
    watchOnlyWidget->addItem(QIcon(":/icons/" + theme + "/eye_plus"), "", TransactionFilterProxy::WatchOnlyFilter_Yes);
    watchOnlyWidget->addItem(QIcon(":/icons/" + theme + "/eye_minus"), "", TransactionFilterProxy::WatchOnlyFilter_No);
    hlayout->addWidget(watchOnlyWidget);

    dateWidget = new QComboBox(this);
    if (platformStyle->getUseExtraSpacing()) {
        dateWidget->setFixedWidth(120);
    } else {
        dateWidget->setFixedWidth(120);
    }
=======
TransactionView::TransactionView(QWidget* parent) : QWidget(parent), model(0), transactionProxyModel(0),
                                                    transactionView(0)
{
    QSettings settings;
    // Build filter row
    setContentsMargins(0, 0, 0, 0);

    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->setContentsMargins(0, 0, 0, 0);
#ifdef Q_OS_MAC
    hlayout->setSpacing(5);
    hlayout->addSpacing(26);
#else
    hlayout->setSpacing(0);
    hlayout->addSpacing(23);
#endif

    watchOnlyWidget = new QComboBox(this);
    watchOnlyWidget->setFixedWidth(24);
    watchOnlyWidget->addItem("", TransactionFilterProxy::WatchOnlyFilter_All);
    watchOnlyWidget->addItem(QIcon(":/icons/eye_plus"), "", TransactionFilterProxy::WatchOnlyFilter_Yes);
    watchOnlyWidget->addItem(QIcon(":/icons/eye_minus"), "", TransactionFilterProxy::WatchOnlyFilter_No);
    hlayout->addWidget(watchOnlyWidget);

    dateWidget = new QComboBox(this);
#ifdef Q_OS_MAC
    dateWidget->setFixedWidth(121);
#else
    dateWidget->setFixedWidth(120);
#endif
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    dateWidget->addItem(tr("All"), All);
    dateWidget->addItem(tr("Today"), Today);
    dateWidget->addItem(tr("This week"), ThisWeek);
    dateWidget->addItem(tr("This month"), ThisMonth);
    dateWidget->addItem(tr("Last month"), LastMonth);
    dateWidget->addItem(tr("This year"), ThisYear);
    dateWidget->addItem(tr("Range..."), Range);
    dateWidget->setCurrentIndex(settings.value("transactionDate").toInt());
    hlayout->addWidget(dateWidget);

    typeWidget = new QComboBox(this);
<<<<<<< HEAD
    if (platformStyle->getUseExtraSpacing()) {
        typeWidget->setFixedWidth(TYPE_COLUMN_WIDTH);
    } else {
        typeWidget->setFixedWidth(TYPE_COLUMN_WIDTH-1);
    }

    typeWidget->addItem(tr("All"), TransactionFilterProxy::ALL_TYPES);
    typeWidget->addItem(tr("Most Common"), TransactionFilterProxy::COMMON_TYPES);
    typeWidget->addItem(tr("Received with"), TransactionFilterProxy::TYPE(TransactionRecord::RecvWithAddress) |
                                        TransactionFilterProxy::TYPE(TransactionRecord::RecvFromOther));
    typeWidget->addItem(tr("Sent to"), TransactionFilterProxy::TYPE(TransactionRecord::SendToAddress) |
                                  TransactionFilterProxy::TYPE(TransactionRecord::SendToOther));
    typeWidget->addItem(tr("PrivateSend"), TransactionFilterProxy::TYPE(TransactionRecord::PrivateSend));
    typeWidget->addItem(tr("PrivateSend Make Collateral Inputs"), TransactionFilterProxy::TYPE(TransactionRecord::PrivateSendMakeCollaterals));
    typeWidget->addItem(tr("PrivateSend Create Denominations"), TransactionFilterProxy::TYPE(TransactionRecord::PrivateSendCreateDenominations));
    typeWidget->addItem(tr("PrivateSend Denominate"), TransactionFilterProxy::TYPE(TransactionRecord::PrivateSendDenominate));
    typeWidget->addItem(tr("PrivateSend Collateral Payment"), TransactionFilterProxy::TYPE(TransactionRecord::PrivateSendCollateralPayment));
    typeWidget->addItem(tr("To yourself"), TransactionFilterProxy::TYPE(TransactionRecord::SendToSelf));
    typeWidget->addItem(tr("Mined"), TransactionFilterProxy::TYPE(TransactionRecord::Generated));
=======
#ifdef Q_OS_MAC
    typeWidget->setFixedWidth(TYPE_COLUMN_WIDTH + 1);
#else
    typeWidget->setFixedWidth(TYPE_COLUMN_WIDTH);
#endif

    typeWidget->addItem(tr("All"), TransactionFilterProxy::ALL_TYPES);
    typeWidget->addItem(tr("Most Common"), TransactionFilterProxy::COMMON_TYPES);
    typeWidget->addItem(tr("Received with"), TransactionFilterProxy::TYPE(TransactionRecord::RecvWithAddress) | TransactionFilterProxy::TYPE(TransactionRecord::RecvFromOther));
    typeWidget->addItem(tr("Sent to"), TransactionFilterProxy::TYPE(TransactionRecord::SendToAddress) | TransactionFilterProxy::TYPE(TransactionRecord::SendToOther));
    typeWidget->addItem(tr("Obfuscated"), TransactionFilterProxy::TYPE(TransactionRecord::Obfuscated));
    typeWidget->addItem(tr("Obfuscation Make Collateral Inputs"), TransactionFilterProxy::TYPE(TransactionRecord::ObfuscationMakeCollaterals));
    typeWidget->addItem(tr("Obfuscation Create Denominations"), TransactionFilterProxy::TYPE(TransactionRecord::ObfuscationCreateDenominations));
    typeWidget->addItem(tr("Obfuscation Denominate"), TransactionFilterProxy::TYPE(TransactionRecord::ObfuscationDenominate));
    typeWidget->addItem(tr("Obfuscation Collateral Payment"), TransactionFilterProxy::TYPE(TransactionRecord::ObfuscationCollateralPayment));
    typeWidget->addItem(tr("To yourself"), TransactionFilterProxy::TYPE(TransactionRecord::SendToSelf));
    typeWidget->addItem(tr("Mined"), TransactionFilterProxy::TYPE(TransactionRecord::Generated));
    typeWidget->addItem(tr("Minted"), TransactionFilterProxy::TYPE(TransactionRecord::StakeMint));
    typeWidget->addItem(tr("Masternode Reward"), TransactionFilterProxy::TYPE(TransactionRecord::MNReward));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    typeWidget->addItem(tr("Other"), TransactionFilterProxy::TYPE(TransactionRecord::Other));
    typeWidget->setCurrentIndex(settings.value("transactionType").toInt());

    hlayout->addWidget(typeWidget);

    addressWidget = new QLineEdit(this);
#if QT_VERSION >= 0x040700
    addressWidget->setPlaceholderText(tr("Enter address or label to search"));
#endif
<<<<<<< HEAD
    addressWidget->setObjectName("addressWidget");
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    hlayout->addWidget(addressWidget);

    amountWidget = new QLineEdit(this);
#if QT_VERSION >= 0x040700
    amountWidget->setPlaceholderText(tr("Min amount"));
#endif
<<<<<<< HEAD
    if (platformStyle->getUseExtraSpacing()) {
        amountWidget->setFixedWidth(118);
    } else {
        amountWidget->setFixedWidth(125);
    }  
    amountWidget->setValidator(new QDoubleValidator(0, 1e20, 8, this));
    amountWidget->setObjectName("amountWidget");
    hlayout->addWidget(amountWidget);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setContentsMargins(0,0,0,0);
    vlayout->setSpacing(0);

    QTableView *view = new QTableView(this);
=======
#ifdef Q_OS_MAC
    amountWidget->setFixedWidth(97);
#else
    amountWidget->setFixedWidth(100);
#endif
    amountWidget->setValidator(new QDoubleValidator(0, 1e20, 8, this));
    hlayout->addWidget(amountWidget);

    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->setContentsMargins(0, 0, 0, 0);
    vlayout->setSpacing(0);

    QTableView* view = new QTableView(this);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    vlayout->addLayout(hlayout);
    vlayout->addWidget(createDateRangeWidget());
    vlayout->addWidget(view);
    vlayout->setSpacing(0);
    int width = view->verticalScrollBar()->sizeHint().width();
<<<<<<< HEAD
    // Cover scroll bar width with spacing
    if (platformStyle->getUseExtraSpacing()) {
        hlayout->addSpacing(width+2);
    } else {
        hlayout->addSpacing(width);
    }
=======
// Cover scroll bar width with spacing
#ifdef Q_OS_MAC
    hlayout->addSpacing(width + 2);
#else
    hlayout->addSpacing(width);
#endif
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    // Always show scroll bar
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    view->setTabKeyNavigation(false);
    view->setContextMenuPolicy(Qt::CustomContextMenu);

    view->installEventFilter(this);

    transactionView = view;

    // Actions
<<<<<<< HEAD
    abandonAction = new QAction(tr("Abandon transaction"), this);
    QAction *copyAddressAction = new QAction(tr("Copy address"), this);
    QAction *copyLabelAction = new QAction(tr("Copy label"), this);
    QAction *copyAmountAction = new QAction(tr("Copy amount"), this);
    QAction *copyTxIDAction = new QAction(tr("Copy transaction ID"), this);
    QAction *copyTxHexAction = new QAction(tr("Copy raw transaction"), this);
    QAction *copyTxPlainText = new QAction(tr("Copy full transaction details"), this);
    QAction *editLabelAction = new QAction(tr("Edit label"), this);
    QAction *showDetailsAction = new QAction(tr("Show transaction details"), this);

    contextMenu = new QMenu(this);
=======
    QAction* copyAddressAction = new QAction(tr("Copy address"), this);
    QAction* copyLabelAction = new QAction(tr("Copy label"), this);
    QAction* copyAmountAction = new QAction(tr("Copy amount"), this);
    QAction* copyTxIDAction = new QAction(tr("Copy transaction ID"), this);
    QAction* editLabelAction = new QAction(tr("Edit label"), this);
    QAction* showDetailsAction = new QAction(tr("Show transaction details"), this);

    contextMenu = new QMenu();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    contextMenu->addAction(copyAddressAction);
    contextMenu->addAction(copyLabelAction);
    contextMenu->addAction(copyAmountAction);
    contextMenu->addAction(copyTxIDAction);
<<<<<<< HEAD
    contextMenu->addAction(copyTxHexAction);
    contextMenu->addAction(copyTxPlainText);
    contextMenu->addAction(showDetailsAction);
    contextMenu->addSeparator();
    contextMenu->addAction(abandonAction);
    contextMenu->addAction(editLabelAction);
=======
    contextMenu->addAction(editLabelAction);
    contextMenu->addAction(showDetailsAction);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    mapperThirdPartyTxUrls = new QSignalMapper(this);

    // Connect actions
    connect(mapperThirdPartyTxUrls, SIGNAL(mapped(QString)), this, SLOT(openThirdPartyTxUrl(QString)));

    connect(dateWidget, SIGNAL(activated(int)), this, SLOT(chooseDate(int)));
    connect(typeWidget, SIGNAL(activated(int)), this, SLOT(chooseType(int)));
    connect(watchOnlyWidget, SIGNAL(activated(int)), this, SLOT(chooseWatchonly(int)));
    connect(addressWidget, SIGNAL(textChanged(QString)), this, SLOT(changedPrefix(QString)));
    connect(amountWidget, SIGNAL(textChanged(QString)), this, SLOT(changedAmount(QString)));

    connect(view, SIGNAL(doubleClicked(QModelIndex)), this, SIGNAL(doubleClicked(QModelIndex)));
    connect(view, SIGNAL(clicked(QModelIndex)), this, SLOT(computeSum()));
    connect(view, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextualMenu(QPoint)));

<<<<<<< HEAD
    connect(abandonAction, SIGNAL(triggered()), this, SLOT(abandonTx()));
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    connect(copyAddressAction, SIGNAL(triggered()), this, SLOT(copyAddress()));
    connect(copyLabelAction, SIGNAL(triggered()), this, SLOT(copyLabel()));
    connect(copyAmountAction, SIGNAL(triggered()), this, SLOT(copyAmount()));
    connect(copyTxIDAction, SIGNAL(triggered()), this, SLOT(copyTxID()));
<<<<<<< HEAD
    connect(copyTxHexAction, SIGNAL(triggered()), this, SLOT(copyTxHex()));
    connect(copyTxPlainText, SIGNAL(triggered()), this, SLOT(copyTxPlainText()));
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    connect(editLabelAction, SIGNAL(triggered()), this, SLOT(editLabel()));
    connect(showDetailsAction, SIGNAL(triggered()), this, SLOT(showDetails()));
}

<<<<<<< HEAD
void TransactionView::setModel(WalletModel *model)
{
    QSettings settings;
    this->model = model;
    if(model)
    {
=======
void TransactionView::setModel(WalletModel* model)
{
    QSettings settings;
    this->model = model;
    if (model) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        transactionProxyModel = new TransactionFilterProxy(this);
        transactionProxyModel->setSourceModel(model->getTransactionTableModel());
        transactionProxyModel->setDynamicSortFilter(true);
        transactionProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
        transactionProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

        transactionProxyModel->setSortRole(Qt::EditRole);

        transactionView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        transactionView->setModel(transactionProxyModel);
        transactionView->setAlternatingRowColors(true);
        transactionView->setSelectionBehavior(QAbstractItemView::SelectRows);
        transactionView->setSelectionMode(QAbstractItemView::ExtendedSelection);
        transactionView->setSortingEnabled(true);
<<<<<<< HEAD
        transactionView->sortByColumn(TransactionTableModel::Status, Qt::DescendingOrder);
=======
        transactionView->sortByColumn(TransactionTableModel::Date, Qt::DescendingOrder);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        transactionView->verticalHeader()->hide();

        transactionView->setColumnWidth(TransactionTableModel::Status, STATUS_COLUMN_WIDTH);
        transactionView->setColumnWidth(TransactionTableModel::Watchonly, WATCHONLY_COLUMN_WIDTH);
        transactionView->setColumnWidth(TransactionTableModel::Date, DATE_COLUMN_WIDTH);
        transactionView->setColumnWidth(TransactionTableModel::Type, TYPE_COLUMN_WIDTH);
        transactionView->setColumnWidth(TransactionTableModel::Amount, AMOUNT_MINIMUM_COLUMN_WIDTH);

        // Note: it's a good idea to connect this signal AFTER the model is set
        connect(transactionView->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this, SLOT(computeSum()));

<<<<<<< HEAD
        columnResizingFixer = new GUIUtil::TableViewLastColumnResizingFixer(transactionView, AMOUNT_MINIMUM_COLUMN_WIDTH, MINIMUM_COLUMN_WIDTH, this);

        if (model->getOptionsModel())
        {
            // Add third party transaction URLs to context menu
            QStringList listUrls = model->getOptionsModel()->getThirdPartyTxUrls().split("|", QString::SkipEmptyParts);
            for (int i = 0; i < listUrls.size(); ++i)
            {
                QString host = QUrl(listUrls[i].trimmed(), QUrl::StrictMode).host();
                if (!host.isEmpty())
                {
                    QAction *thirdPartyTxUrlAction = new QAction(host, this); // use host as menu item label
=======
        columnResizingFixer = new GUIUtil::TableViewLastColumnResizingFixer(transactionView, AMOUNT_MINIMUM_COLUMN_WIDTH, MINIMUM_COLUMN_WIDTH);

        if (model->getOptionsModel()) {
            // Add third party transaction URLs to context menu
            QStringList listUrls = model->getOptionsModel()->getThirdPartyTxUrls().split("|", QString::SkipEmptyParts);
            for (int i = 0; i < listUrls.size(); ++i) {
                QString host = QUrl(listUrls[i].trimmed(), QUrl::StrictMode).host();
                if (!host.isEmpty()) {
                    QAction* thirdPartyTxUrlAction = new QAction(host, this); // use host as menu item label
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                    if (i == 0)
                        contextMenu->addSeparator();
                    contextMenu->addAction(thirdPartyTxUrlAction);
                    connect(thirdPartyTxUrlAction, SIGNAL(triggered()), mapperThirdPartyTxUrls, SLOT(map()));
                    mapperThirdPartyTxUrls->setMapping(thirdPartyTxUrlAction, listUrls[i].trimmed());
                }
            }
        }

        // show/hide column Watch-only
        updateWatchOnlyColumn(model->haveWatchOnly());

        // Watch-only signal
        connect(model, SIGNAL(notifyWatchonlyChanged(bool)), this, SLOT(updateWatchOnlyColumn(bool)));
<<<<<<< HEAD
        
=======

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        // Update transaction list with persisted settings
        chooseType(settings.value("transactionType").toInt());
        chooseDate(settings.value("transactionDate").toInt());
    }
}

void TransactionView::chooseDate(int idx)
{
<<<<<<< HEAD
    if(!transactionProxyModel)
        return;
    
    QSettings settings;
    QDate current = QDate::currentDate();
    dateRangeWidget->setVisible(false);
    switch(dateWidget->itemData(idx).toInt())
    {
    case All:
        transactionProxyModel->setDateRange(
                TransactionFilterProxy::MIN_DATE,
                TransactionFilterProxy::MAX_DATE);
        break;
    case Today:
        transactionProxyModel->setDateRange(
                QDateTime(current),
                TransactionFilterProxy::MAX_DATE);
        break;
    case ThisWeek: {
        // Find last Monday
        QDate startOfWeek = current.addDays(-(current.dayOfWeek()-1));
        transactionProxyModel->setDateRange(
                QDateTime(startOfWeek),
                TransactionFilterProxy::MAX_DATE);

        } break;
    case ThisMonth:
        transactionProxyModel->setDateRange(
                QDateTime(QDate(current.year(), current.month(), 1)),
                TransactionFilterProxy::MAX_DATE);
        break;
    case LastMonth:
        transactionProxyModel->setDateRange(
                QDateTime(QDate(current.year(), current.month(), 1).addMonths(-1)),
                QDateTime(QDate(current.year(), current.month(), 1)));
        break;
    case ThisYear:
        transactionProxyModel->setDateRange(
                QDateTime(QDate(current.year(), 1, 1)),
                TransactionFilterProxy::MAX_DATE);
=======
    if (!transactionProxyModel)
        return;
    QDate current = QDate::currentDate();
    dateRangeWidget->setVisible(false);
    switch (dateWidget->itemData(idx).toInt()) {
    case All:
        transactionProxyModel->setDateRange(
            TransactionFilterProxy::MIN_DATE,
            TransactionFilterProxy::MAX_DATE);
        break;
    case Today:
        transactionProxyModel->setDateRange(
            QDateTime(current),
            TransactionFilterProxy::MAX_DATE);
        break;
    case ThisWeek: {
        // Find last Monday
        QDate startOfWeek = current.addDays(-(current.dayOfWeek() - 1));
        transactionProxyModel->setDateRange(
            QDateTime(startOfWeek),
            TransactionFilterProxy::MAX_DATE);

    } break;
    case ThisMonth:
        transactionProxyModel->setDateRange(
            QDateTime(QDate(current.year(), current.month(), 1)),
            TransactionFilterProxy::MAX_DATE);
        break;
    case LastMonth:
        transactionProxyModel->setDateRange(
            QDateTime(QDate(current.year(), current.month() - 1, 1)),
            QDateTime(QDate(current.year(), current.month(), 1)));
        break;
    case ThisYear:
        transactionProxyModel->setDateRange(
            QDateTime(QDate(current.year(), 1, 1)),
            TransactionFilterProxy::MAX_DATE);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        break;
    case Range:
        dateRangeWidget->setVisible(true);
        dateRangeChanged();
        break;
    }
<<<<<<< HEAD
    // Persist new date settings
    settings.setValue("transactionDate", idx);
    if (dateWidget->itemData(idx).toInt() == Range){
        settings.setValue("transactionDateFrom", dateFrom->date().toString(PERSISTENCE_DATE_FORMAT));
        settings.setValue("transactionDateTo", dateTo->date().toString(PERSISTENCE_DATE_FORMAT));
=======
    // Persist settings
    if (dateWidget->itemData(idx).toInt() != Range) {
        QSettings settings;
        settings.setValue("transactionDate", idx);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }
}

void TransactionView::chooseType(int idx)
{
<<<<<<< HEAD
    if(!transactionProxyModel)
=======
    if (!transactionProxyModel)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return;
    transactionProxyModel->setTypeFilter(
        typeWidget->itemData(idx).toInt());
    // Persist settings
    QSettings settings;
    settings.setValue("transactionType", idx);
}

void TransactionView::chooseWatchonly(int idx)
{
<<<<<<< HEAD
    if(!transactionProxyModel)
=======
    if (!transactionProxyModel)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return;
    transactionProxyModel->setWatchOnlyFilter(
        (TransactionFilterProxy::WatchOnlyFilter)watchOnlyWidget->itemData(idx).toInt());
}

<<<<<<< HEAD
void TransactionView::changedPrefix(const QString &prefix)
{
    if(!transactionProxyModel)
=======
void TransactionView::changedPrefix(const QString& prefix)
{
    if (!transactionProxyModel)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return;
    transactionProxyModel->setAddressPrefix(prefix);
}

<<<<<<< HEAD
void TransactionView::changedAmount(const QString &amount)
{
    if(!transactionProxyModel)
=======
void TransactionView::changedAmount(const QString& amount)
{
    if (!transactionProxyModel)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return;
    CAmount amount_parsed = 0;

    // Replace "," by "." so BitcoinUnits::parse will not fail for users entering "," as decimal separator
    QString newAmount = amount;
    newAmount.replace(QString(","), QString("."));

<<<<<<< HEAD
    if(BitcoinUnits::parse(model->getOptionsModel()->getDisplayUnit(), newAmount, &amount_parsed))
    {
        transactionProxyModel->setMinAmount(amount_parsed);
    }
    else
    {
=======
    if (BitcoinUnits::parse(model->getOptionsModel()->getDisplayUnit(), newAmount, &amount_parsed)) {
        transactionProxyModel->setMinAmount(amount_parsed);
    } else {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        transactionProxyModel->setMinAmount(0);
    }
}

void TransactionView::exportClicked()
{
    // CSV is currently the only supported format
    QString filename = GUIUtil::getSaveFileName(this,
        tr("Export Transaction History"), QString(),
        tr("Comma separated file (*.csv)"), NULL);

    if (filename.isNull())
        return;

    CSVModelWriter writer(filename);

    // name, column, role
    writer.setModel(transactionProxyModel);
    writer.addColumn(tr("Confirmed"), 0, TransactionTableModel::ConfirmedRole);
    if (model && model->haveWatchOnly())
        writer.addColumn(tr("Watch-only"), TransactionTableModel::Watchonly);
    writer.addColumn(tr("Date"), 0, TransactionTableModel::DateRole);
    writer.addColumn(tr("Type"), TransactionTableModel::Type, Qt::EditRole);
    writer.addColumn(tr("Label"), 0, TransactionTableModel::LabelRole);
    writer.addColumn(tr("Address"), 0, TransactionTableModel::AddressRole);
    writer.addColumn(BitcoinUnits::getAmountColumnTitle(model->getOptionsModel()->getDisplayUnit()), 0, TransactionTableModel::FormattedAmountRole);
    writer.addColumn(tr("ID"), 0, TransactionTableModel::TxIDRole);

<<<<<<< HEAD
    if(!writer.write()) {
        Q_EMIT message(tr("Exporting Failed"), tr("There was an error trying to save the transaction history to %1.").arg(filename),
            CClientUIInterface::MSG_ERROR);
    }
    else {
        Q_EMIT message(tr("Exporting Successful"), tr("The transaction history was successfully saved to %1.").arg(filename),
=======
    if (!writer.write()) {
        emit message(tr("Exporting Failed"), tr("There was an error trying to save the transaction history to %1.").arg(filename),
            CClientUIInterface::MSG_ERROR);
    } else {
        emit message(tr("Exporting Successful"), tr("The transaction history was successfully saved to %1.").arg(filename),
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            CClientUIInterface::MSG_INFORMATION);
    }
}

<<<<<<< HEAD
void TransactionView::contextualMenu(const QPoint &point)
{
    QModelIndex index = transactionView->indexAt(point);
    QModelIndexList selection = transactionView->selectionModel()->selectedRows(0);
    if (selection.empty())
        return;

    // check if transaction can be abandoned, disable context menu action in case it doesn't
    uint256 hash;
    hash.SetHex(selection.at(0).data(TransactionTableModel::TxHashRole).toString().toStdString());
    abandonAction->setEnabled(model->transactionCanBeAbandoned(hash));

    if(index.isValid())
    {
=======
void TransactionView::contextualMenu(const QPoint& point)
{
    QModelIndex index = transactionView->indexAt(point);
    if (index.isValid()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        contextMenu->exec(QCursor::pos());
    }
}

<<<<<<< HEAD
void TransactionView::abandonTx()
{
    if(!transactionView || !transactionView->selectionModel())
        return;
    QModelIndexList selection = transactionView->selectionModel()->selectedRows(0);

    // get the hash from the TxHashRole (QVariant / QString)
    uint256 hash;
    QString hashQStr = selection.at(0).data(TransactionTableModel::TxHashRole).toString();
    hash.SetHex(hashQStr.toStdString());

    // Abandon the wallet transaction over the walletModel
    model->abandonTransaction(hash);

    // Update the table
    model->getTransactionTableModel()->updateTransaction(hashQStr, CT_UPDATED, false);
}

=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
void TransactionView::copyAddress()
{
    GUIUtil::copyEntryData(transactionView, 0, TransactionTableModel::AddressRole);
}

void TransactionView::copyLabel()
{
    GUIUtil::copyEntryData(transactionView, 0, TransactionTableModel::LabelRole);
}

void TransactionView::copyAmount()
{
    GUIUtil::copyEntryData(transactionView, 0, TransactionTableModel::FormattedAmountRole);
}

void TransactionView::copyTxID()
{
    GUIUtil::copyEntryData(transactionView, 0, TransactionTableModel::TxIDRole);
}

<<<<<<< HEAD
void TransactionView::copyTxHex()
{
    GUIUtil::copyEntryData(transactionView, 0, TransactionTableModel::TxHexRole);
}

void TransactionView::copyTxPlainText()
{
    GUIUtil::copyEntryData(transactionView, 0, TransactionTableModel::TxPlainTextRole);
}

void TransactionView::editLabel()
{
    if(!transactionView->selectionModel() ||!model)
        return;
    QModelIndexList selection = transactionView->selectionModel()->selectedRows();
    if(!selection.isEmpty())
    {
        AddressTableModel *addressBook = model->getAddressTableModel();
        if(!addressBook)
            return;
        QString address = selection.at(0).data(TransactionTableModel::AddressRole).toString();
        if(address.isEmpty())
        {
=======
void TransactionView::editLabel()
{
    if (!transactionView->selectionModel() || !model)
        return;
    QModelIndexList selection = transactionView->selectionModel()->selectedRows();
    if (!selection.isEmpty()) {
        AddressTableModel* addressBook = model->getAddressTableModel();
        if (!addressBook)
            return;
        QString address = selection.at(0).data(TransactionTableModel::AddressRole).toString();
        if (address.isEmpty()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            // If this transaction has no associated address, exit
            return;
        }
        // Is address in address book? Address book can miss address when a transaction is
        // sent from outside the UI.
        int idx = addressBook->lookupAddress(address);
<<<<<<< HEAD
        if(idx != -1)
        {
=======
        if (idx != -1) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            // Edit sending / receiving address
            QModelIndex modelIdx = addressBook->index(idx, 0, QModelIndex());
            // Determine type of address, launch appropriate editor dialog type
            QString type = modelIdx.data(AddressTableModel::TypeRole).toString();

            EditAddressDialog dlg(
<<<<<<< HEAD
                type == AddressTableModel::Receive
                ? EditAddressDialog::EditReceivingAddress
                : EditAddressDialog::EditSendingAddress, this);
            dlg.setModel(addressBook);
            dlg.loadRow(idx);
            dlg.exec();
        }
        else
        {
=======
                type == AddressTableModel::Receive ? EditAddressDialog::EditReceivingAddress : EditAddressDialog::EditSendingAddress, this);
            dlg.setModel(addressBook);
            dlg.loadRow(idx);
            dlg.exec();
        } else {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            // Add sending address
            EditAddressDialog dlg(EditAddressDialog::NewSendingAddress,
                this);
            dlg.setModel(addressBook);
            dlg.setAddress(address);
            dlg.exec();
        }
    }
}

void TransactionView::showDetails()
{
<<<<<<< HEAD
    if(!transactionView->selectionModel())
        return;
    QModelIndexList selection = transactionView->selectionModel()->selectedRows();
    if(!selection.isEmpty())
    {
=======
    if (!transactionView->selectionModel())
        return;
    QModelIndexList selection = transactionView->selectionModel()->selectedRows();
    if (!selection.isEmpty()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        TransactionDescDialog dlg(selection.at(0));
        dlg.exec();
    }
}

/** Compute sum of all selected transactions */
void TransactionView::computeSum()
{
    qint64 amount = 0;
    int nDisplayUnit = model->getOptionsModel()->getDisplayUnit();
<<<<<<< HEAD
    if(!transactionView->selectionModel())
        return;
    QModelIndexList selection = transactionView->selectionModel()->selectedRows();

    Q_FOREACH (QModelIndex index, selection){
=======
    if (!transactionView->selectionModel())
        return;
    QModelIndexList selection = transactionView->selectionModel()->selectedRows();

    foreach (QModelIndex index, selection) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        amount += index.data(TransactionTableModel::AmountRole).toLongLong();
    }
    QString strAmount(BitcoinUnits::formatWithUnit(nDisplayUnit, amount, true, BitcoinUnits::separatorAlways));
    if (amount < 0) strAmount = "<span style='color:red;'>" + strAmount + "</span>";
<<<<<<< HEAD
    Q_EMIT trxAmount(strAmount);
=======
    emit trxAmount(strAmount);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

void TransactionView::openThirdPartyTxUrl(QString url)
{
<<<<<<< HEAD
    if(!transactionView || !transactionView->selectionModel())
        return;
    QModelIndexList selection = transactionView->selectionModel()->selectedRows(0);
    if(!selection.isEmpty())
         QDesktopServices::openUrl(QUrl::fromUserInput(url.replace("%s", selection.at(0).data(TransactionTableModel::TxHashRole).toString())));
}

QWidget *TransactionView::createDateRangeWidget()
{
    // Create default dates in case nothing is persisted
    QString defaultDateFrom = QDate::currentDate().toString(PERSISTENCE_DATE_FORMAT);
    QString defaultDateTo = QDate::currentDate().addDays(1).toString(PERSISTENCE_DATE_FORMAT);
    QSettings settings;
 
    dateRangeWidget = new QFrame();
    dateRangeWidget->setFrameStyle(QFrame::Panel | QFrame::Raised);
    dateRangeWidget->setContentsMargins(1,1,1,1);
    QHBoxLayout *layout = new QHBoxLayout(dateRangeWidget);
    layout->setContentsMargins(0,0,0,0);
=======
    if (!transactionView || !transactionView->selectionModel())
        return;
    QModelIndexList selection = transactionView->selectionModel()->selectedRows(0);
    if (!selection.isEmpty())
        QDesktopServices::openUrl(QUrl::fromUserInput(url.replace("%s", selection.at(0).data(TransactionTableModel::TxHashRole).toString())));
}

QWidget* TransactionView::createDateRangeWidget()
{
    dateRangeWidget = new QFrame();
    dateRangeWidget->setFrameStyle(QFrame::Panel | QFrame::Raised);
    dateRangeWidget->setContentsMargins(1, 1, 1, 1);
    QHBoxLayout* layout = new QHBoxLayout(dateRangeWidget);
    layout->setContentsMargins(0, 0, 0, 0);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    layout->addSpacing(23);
    layout->addWidget(new QLabel(tr("Range:")));

    dateFrom = new QDateTimeEdit(this);
<<<<<<< HEAD
    dateFrom->setCalendarPopup(true);
    dateFrom->setMinimumWidth(100);
    // Load persisted FROM date
    dateFrom->setDate(QDate::fromString(settings.value("transactionDateFrom", defaultDateFrom).toString(), PERSISTENCE_DATE_FORMAT));

=======
    dateFrom->setDisplayFormat("dd/MM/yy");
    dateFrom->setCalendarPopup(true);
    dateFrom->setMinimumWidth(100);
    dateFrom->setDate(QDate::currentDate().addDays(-7));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    layout->addWidget(dateFrom);
    layout->addWidget(new QLabel(tr("to")));

    dateTo = new QDateTimeEdit(this);
<<<<<<< HEAD
    dateTo->setCalendarPopup(true);
    dateTo->setMinimumWidth(100);
    // Load persisted TO date
    dateTo->setDate(QDate::fromString(settings.value("transactionDateTo", defaultDateTo).toString(), PERSISTENCE_DATE_FORMAT));

=======
    dateTo->setDisplayFormat("dd/MM/yy");
    dateTo->setCalendarPopup(true);
    dateTo->setMinimumWidth(100);
    dateTo->setDate(QDate::currentDate());
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    layout->addWidget(dateTo);
    layout->addStretch();

    // Hide by default
    dateRangeWidget->setVisible(false);

    // Notify on change
    connect(dateFrom, SIGNAL(dateChanged(QDate)), this, SLOT(dateRangeChanged()));
    connect(dateTo, SIGNAL(dateChanged(QDate)), this, SLOT(dateRangeChanged()));

    return dateRangeWidget;
}

void TransactionView::dateRangeChanged()
{
<<<<<<< HEAD
    if(!transactionProxyModel)
        return;
    
    // Persist new date range
    QSettings settings;
    settings.setValue("transactionDateFrom", dateFrom->date().toString(PERSISTENCE_DATE_FORMAT));
    settings.setValue("transactionDateTo", dateTo->date().toString(PERSISTENCE_DATE_FORMAT));
    
    transactionProxyModel->setDateRange(
            QDateTime(dateFrom->date()),
            QDateTime(dateTo->date()));
}

void TransactionView::focusTransaction(const QModelIndex &idx)
{
    if(!transactionProxyModel)
=======
    if (!transactionProxyModel)
        return;
    transactionProxyModel->setDateRange(
        QDateTime(dateFrom->date()),
        QDateTime(dateTo->date()).addDays(1));
}

void TransactionView::focusTransaction(const QModelIndex& idx)
{
    if (!transactionProxyModel)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return;
    QModelIndex targetIdx = transactionProxyModel->mapFromSource(idx);
    transactionView->selectRow(targetIdx.row());
    computeSum();
    transactionView->scrollTo(targetIdx);
    transactionView->setCurrentIndex(targetIdx);
    transactionView->setFocus();
}

// We override the virtual resizeEvent of the QWidget to adjust tables column
// sizes as the tables width is proportional to the dialogs width.
void TransactionView::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    columnResizingFixer->stretchColumnWidth(TransactionTableModel::ToAddress);
}

// Need to override default Ctrl+C action for amount as default behaviour is just to copy DisplayRole text
<<<<<<< HEAD
bool TransactionView::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);
        if (ke->key() == Qt::Key_C && ke->modifiers().testFlag(Qt::ControlModifier))
        {
             GUIUtil::copyEntryData(transactionView, 0, TransactionTableModel::TxPlainTextRole);
             return true;
=======
bool TransactionView::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* ke = static_cast<QKeyEvent*>(event);
        if (ke->key() == Qt::Key_C && ke->modifiers().testFlag(Qt::ControlModifier)) {
            QModelIndex i = this->transactionView->currentIndex();
            if (i.isValid() && i.column() == TransactionTableModel::Amount) {
                GUIUtil::setClipboard(i.data(TransactionTableModel::FormattedAmountRole).toString());
                return true;
            }
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        }
    }
    return QWidget::eventFilter(obj, event);
}

// show/hide column Watch-only
void TransactionView::updateWatchOnlyColumn(bool fHaveWatchOnly)
{
<<<<<<< HEAD
    watchOnlyWidget->setVisible(true);
=======
    watchOnlyWidget->setVisible(fHaveWatchOnly);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    transactionView->setColumnHidden(TransactionTableModel::Watchonly, !fHaveWatchOnly);
}
