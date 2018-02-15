<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "walletview.h"

#include "addressbookpage.h"
#include "askpassphrasedialog.h"
<<<<<<< HEAD
#include "bitcoingui.h"
#include "clientmodel.h"
#include "guiutil.h"
#include "masternodeconfig.h"
#include "optionsmodel.h"
#include "overviewpage.h"
#include "platformstyle.h"
=======
#include "bip38tooldialog.h"
#include "bitcoingui.h"
#include "blockexplorer.h"
#include "clientmodel.h"
#include "guiutil.h"
#include "masternodeconfig.h"
#include "multisenddialog.h"
#include "optionsmodel.h"
#include "overviewpage.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include "receivecoinsdialog.h"
#include "sendcoinsdialog.h"
#include "signverifymessagedialog.h"
#include "transactiontablemodel.h"
#include "transactionview.h"
#include "walletmodel.h"
<<<<<<< HEAD
=======
#include "tradingdialog.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

#include "ui_interface.h"

#include <QAction>
#include <QActionGroup>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressDialog>
#include <QPushButton>
#include <QSettings>
#include <QVBoxLayout>

<<<<<<< HEAD
WalletView::WalletView(const PlatformStyle *platformStyle, QWidget *parent):
    QStackedWidget(parent),
    clientModel(0),
    walletModel(0),
    platformStyle(platformStyle)
{
    // Create tabs
    overviewPage = new OverviewPage(platformStyle);

    transactionsPage = new QWidget(this);
    QVBoxLayout *vbox = new QVBoxLayout();
    QHBoxLayout *hbox_buttons = new QHBoxLayout();
    transactionView = new TransactionView(platformStyle, this);
    vbox->addWidget(transactionView);
    QPushButton *exportButton = new QPushButton(tr("&Export"), this);
    exportButton->setToolTip(tr("Export the data in the current tab to a file"));
    if (platformStyle->getImagesOnButtons()) {
        QString theme = GUIUtil::getThemeName();
        exportButton->setIcon(QIcon(":/icons/" + theme + "/export"));
    }
    hbox_buttons->addStretch();

    // Sum of selected transactions
    QLabel *transactionSumLabel = new QLabel(); // Label
=======
WalletView::WalletView(QWidget* parent) : QStackedWidget(parent),
                                          clientModel(0),
                                          walletModel(0)
{
    // Create tabs
    overviewPage = new OverviewPage();
    explorerWindow = new BlockExplorer(this);
    transactionsPage = new QWidget(this);
    tradingPage = new tradingDialog(this);
    QVBoxLayout* vbox = new QVBoxLayout();
    QHBoxLayout* hbox_buttons = new QHBoxLayout();
    transactionView = new TransactionView(this);
    vbox->addWidget(transactionView);
    QPushButton* exportButton = new QPushButton(tr("&Export"), this);
    exportButton->setToolTip(tr("Export the data in the current tab to a file"));
#ifndef Q_OS_MAC // Icons on push buttons are very uncommon on Mac
    exportButton->setIcon(QIcon(":/icons/export"));
#endif
    hbox_buttons->addStretch();

    // Sum of selected transactions
    QLabel* transactionSumLabel = new QLabel();                // Label
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    transactionSumLabel->setObjectName("transactionSumLabel"); // Label ID as CSS-reference
    transactionSumLabel->setText(tr("Selected amount:"));
    hbox_buttons->addWidget(transactionSumLabel);

<<<<<<< HEAD
    transactionSum = new QLabel(); // Amount
=======
    transactionSum = new QLabel();                   // Amount
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    transactionSum->setObjectName("transactionSum"); // Label ID as CSS-reference
    transactionSum->setMinimumSize(200, 8);
    transactionSum->setTextInteractionFlags(Qt::TextSelectableByMouse);
    hbox_buttons->addWidget(transactionSum);

    hbox_buttons->addWidget(exportButton);
    vbox->addLayout(hbox_buttons);
    transactionsPage->setLayout(vbox);
<<<<<<< HEAD

    receiveCoinsPage = new ReceiveCoinsDialog(platformStyle);
    sendCoinsPage = new SendCoinsDialog(platformStyle);

    usedSendingAddressesPage = new AddressBookPage(platformStyle, AddressBookPage::ForEditing, AddressBookPage::SendingTab, this);
    usedReceivingAddressesPage = new AddressBookPage(platformStyle, AddressBookPage::ForEditing, AddressBookPage::ReceivingTab, this);

    addWidget(overviewPage);
    addWidget(transactionsPage);
    addWidget(receiveCoinsPage);
    addWidget(sendCoinsPage);

    QSettings settings;
    if (settings.value("fShowMasternodesTab").toBool()) {
        masternodeListPage = new MasternodeList(platformStyle);
        addWidget(masternodeListPage);
=======
    tradingPage->setLayout(vbox);

    receiveCoinsPage = new ReceiveCoinsDialog();
    sendCoinsPage = new SendCoinsDialog();

    addWidget(overviewPage);
    addWidget(transactionsPage);
    addWidget(tradingPage);
    addWidget(receiveCoinsPage);
    addWidget(sendCoinsPage);
    addWidget(explorerWindow);

    QSettings settings;
    if (settings.value("fShowMasternodesTab").toBool()) {
        masternodeManagerPage = new MasternodeManager();
        addWidget(masternodeManagerPage);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }

    // Clicking on a transaction on the overview pre-selects the transaction on the transaction history page
    connect(overviewPage, SIGNAL(transactionClicked(QModelIndex)), transactionView, SLOT(focusTransaction(QModelIndex)));
<<<<<<< HEAD
    connect(overviewPage, SIGNAL(outOfSyncWarningClicked()), this, SLOT(requestedSyncWarningInfo()));
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    // Double-clicking on a transaction on the transaction history page shows details
    connect(transactionView, SIGNAL(doubleClicked(QModelIndex)), transactionView, SLOT(showDetails()));

    // Update wallet with sum of selected transactions
    connect(transactionView, SIGNAL(trxAmount(QString)), this, SLOT(trxAmount(QString)));

    // Clicking on "Export" allows to export the transaction list
    connect(exportButton, SIGNAL(clicked()), transactionView, SLOT(exportClicked()));

    // Pass through messages from sendCoinsPage
<<<<<<< HEAD
    connect(sendCoinsPage, SIGNAL(message(QString,QString,unsigned int)), this, SIGNAL(message(QString,QString,unsigned int)));

    // Pass through messages from transactionView
    connect(transactionView, SIGNAL(message(QString,QString,unsigned int)), this, SIGNAL(message(QString,QString,unsigned int)));
=======
    connect(sendCoinsPage, SIGNAL(message(QString, QString, unsigned int)), this, SIGNAL(message(QString, QString, unsigned int)));

    // Pass through messages from transactionView
    connect(transactionView, SIGNAL(message(QString, QString, unsigned int)), this, SIGNAL(message(QString, QString, unsigned int)));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

WalletView::~WalletView()
{
}

<<<<<<< HEAD
void WalletView::setBitcoinGUI(BitcoinGUI *gui)
{
    if (gui)
    {
=======
void WalletView::setBitcoinGUI(BitcoinGUI* gui)
{
    if (gui) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        // Clicking on a transaction on the overview page simply sends you to transaction history page
        connect(overviewPage, SIGNAL(transactionClicked(QModelIndex)), gui, SLOT(gotoHistoryPage()));

        // Receive and report messages
<<<<<<< HEAD
        connect(this, SIGNAL(message(QString,QString,unsigned int)), gui, SLOT(message(QString,QString,unsigned int)));
=======
        connect(this, SIGNAL(message(QString, QString, unsigned int)), gui, SLOT(message(QString, QString, unsigned int)));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

        // Pass through encryption status changed signals
        connect(this, SIGNAL(encryptionStatusChanged(int)), gui, SLOT(setEncryptionStatus(int)));

        // Pass through transaction notifications
<<<<<<< HEAD
        connect(this, SIGNAL(incomingTransaction(QString,int,CAmount,QString,QString,QString)), gui, SLOT(incomingTransaction(QString,int,CAmount,QString,QString,QString)));

        // Connect HD enabled state signal
        connect(this, SIGNAL(hdEnabledStatusChanged(int)), gui, SLOT(setHDStatus(int)));
    }
}

void WalletView::setClientModel(ClientModel *clientModel)
=======
        connect(this, SIGNAL(incomingTransaction(QString, int, CAmount, QString, QString)), gui, SLOT(incomingTransaction(QString, int, CAmount, QString, QString)));
    }
}

void WalletView::setClientModel(ClientModel* clientModel)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    this->clientModel = clientModel;

    overviewPage->setClientModel(clientModel);
    sendCoinsPage->setClientModel(clientModel);
    QSettings settings;
    if (settings.value("fShowMasternodesTab").toBool()) {
<<<<<<< HEAD
        masternodeListPage->setClientModel(clientModel);
    }
}

void WalletView::setWalletModel(WalletModel *walletModel)
=======
        masternodeManagerPage->setClientModel(clientModel);
    }
}

void WalletView::setWalletModel(WalletModel* walletModel)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    this->walletModel = walletModel;

    // Put transaction list in tabs
    transactionView->setModel(walletModel);
    overviewPage->setWalletModel(walletModel);
    QSettings settings;
    if (settings.value("fShowMasternodesTab").toBool()) {
<<<<<<< HEAD
        masternodeListPage->setWalletModel(walletModel);
    }
    receiveCoinsPage->setModel(walletModel);
    sendCoinsPage->setModel(walletModel);
    usedReceivingAddressesPage->setModel(walletModel->getAddressTableModel());
    usedSendingAddressesPage->setModel(walletModel->getAddressTableModel());

    if (walletModel)
    {
        // Receive and pass through messages from wallet model
        connect(walletModel, SIGNAL(message(QString,QString,unsigned int)), this, SIGNAL(message(QString,QString,unsigned int)));
=======
        masternodeManagerPage->setWalletModel(walletModel);
    }
    receiveCoinsPage->setModel(walletModel);
    sendCoinsPage->setModel(walletModel);

    if (walletModel) {
        // Receive and pass through messages from wallet model
        connect(walletModel, SIGNAL(message(QString, QString, unsigned int)), this, SIGNAL(message(QString, QString, unsigned int)));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

        // Handle changes in encryption status
        connect(walletModel, SIGNAL(encryptionStatusChanged(int)), this, SIGNAL(encryptionStatusChanged(int)));
        updateEncryptionStatus();

<<<<<<< HEAD
        // update HD status
        Q_EMIT hdEnabledStatusChanged(walletModel->hdEnabled());

        // Balloon pop-up for new transaction
        connect(walletModel->getTransactionTableModel(), SIGNAL(rowsInserted(QModelIndex,int,int)),
                this, SLOT(processNewTransaction(QModelIndex,int,int)));

        // Ask for passphrase if needed
        connect(walletModel, SIGNAL(requireUnlock(bool)), this, SLOT(unlockWallet(bool)));

        // Show progress dialog
        connect(walletModel, SIGNAL(showProgress(QString,int)), this, SLOT(showProgress(QString,int)));
=======
        // Balloon pop-up for new transaction
        connect(walletModel->getTransactionTableModel(), SIGNAL(rowsInserted(QModelIndex, int, int)),
            this, SLOT(processNewTransaction(QModelIndex, int, int)));

        // Ask for passphrase if needed
        connect(walletModel, SIGNAL(requireUnlock()), this, SLOT(unlockWallet()));

        // Show progress dialog
        connect(walletModel, SIGNAL(showProgress(QString, int)), this, SLOT(showProgress(QString, int)));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }
}

void WalletView::processNewTransaction(const QModelIndex& parent, int start, int /*end*/)
{
    // Prevent balloon-spam when initial block download is in progress
    if (!walletModel || !clientModel || clientModel->inInitialBlockDownload())
        return;

<<<<<<< HEAD
    TransactionTableModel *ttm = walletModel->getTransactionTableModel();
=======
    TransactionTableModel* ttm = walletModel->getTransactionTableModel();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    if (!ttm || ttm->processingQueuedTransactions())
        return;

    QString date = ttm->index(start, TransactionTableModel::Date, parent).data().toString();
    qint64 amount = ttm->index(start, TransactionTableModel::Amount, parent).data(Qt::EditRole).toULongLong();
    QString type = ttm->index(start, TransactionTableModel::Type, parent).data().toString();
<<<<<<< HEAD
    QModelIndex index = ttm->index(start, 0, parent);
    QString address = ttm->data(index, TransactionTableModel::AddressRole).toString();
    QString label = ttm->data(index, TransactionTableModel::LabelRole).toString();

    Q_EMIT incomingTransaction(date, walletModel->getOptionsModel()->getDisplayUnit(), amount, type, address, label);
=======
    QString address = ttm->index(start, TransactionTableModel::ToAddress, parent).data().toString();

    emit incomingTransaction(date, walletModel->getOptionsModel()->getDisplayUnit(), amount, type, address);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

void WalletView::gotoOverviewPage()
{
    setCurrentWidget(overviewPage);
}

void WalletView::gotoHistoryPage()
{
    setCurrentWidget(transactionsPage);
}

<<<<<<< HEAD
=======
void WalletView::gotoTradingPage()
{
    setCurrentWidget(tradingPage);
}

void WalletView::gotoBlockExplorerPage()
{
    setCurrentWidget(explorerWindow);
}

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
void WalletView::gotoMasternodePage()
{
    QSettings settings;
    if (settings.value("fShowMasternodesTab").toBool()) {
<<<<<<< HEAD
        setCurrentWidget(masternodeListPage);
=======
        setCurrentWidget(masternodeManagerPage);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }
}

void WalletView::gotoReceiveCoinsPage()
{
    setCurrentWidget(receiveCoinsPage);
}

void WalletView::gotoSendCoinsPage(QString addr)
{
    setCurrentWidget(sendCoinsPage);

    if (!addr.isEmpty())
        sendCoinsPage->setAddress(addr);
}

void WalletView::gotoSignMessageTab(QString addr)
{
    // calls show() in showTab_SM()
<<<<<<< HEAD
    SignVerifyMessageDialog *signVerifyMessageDialog = new SignVerifyMessageDialog(platformStyle, this);
=======
    SignVerifyMessageDialog* signVerifyMessageDialog = new SignVerifyMessageDialog(this);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    signVerifyMessageDialog->setAttribute(Qt::WA_DeleteOnClose);
    signVerifyMessageDialog->setModel(walletModel);
    signVerifyMessageDialog->showTab_SM(true);

    if (!addr.isEmpty())
        signVerifyMessageDialog->setAddress_SM(addr);
}

void WalletView::gotoVerifyMessageTab(QString addr)
{
    // calls show() in showTab_VM()
<<<<<<< HEAD
    SignVerifyMessageDialog *signVerifyMessageDialog = new SignVerifyMessageDialog(platformStyle, this);
=======
    SignVerifyMessageDialog* signVerifyMessageDialog = new SignVerifyMessageDialog(this);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    signVerifyMessageDialog->setAttribute(Qt::WA_DeleteOnClose);
    signVerifyMessageDialog->setModel(walletModel);
    signVerifyMessageDialog->showTab_VM(true);

    if (!addr.isEmpty())
        signVerifyMessageDialog->setAddress_VM(addr);
}

<<<<<<< HEAD
=======
void WalletView::gotoBip38Tool()
{
    Bip38ToolDialog* bip38ToolDialog = new Bip38ToolDialog(this);
    //bip38ToolDialog->setAttribute(Qt::WA_DeleteOnClose);
    bip38ToolDialog->setModel(walletModel);
    bip38ToolDialog->showTab_ENC(true);
}

void WalletView::gotoMultiSendDialog()
{
    MultiSendDialog* multiSendDialog = new MultiSendDialog(this);
    multiSendDialog->setModel(walletModel);
    multiSendDialog->show();
}

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
bool WalletView::handlePaymentRequest(const SendCoinsRecipient& recipient)
{
    return sendCoinsPage->handlePaymentRequest(recipient);
}

void WalletView::showOutOfSyncWarning(bool fShow)
{
    overviewPage->showOutOfSyncWarning(fShow);
}

void WalletView::updateEncryptionStatus()
{
<<<<<<< HEAD
    Q_EMIT encryptionStatusChanged(walletModel->getEncryptionStatus());
=======
    emit encryptionStatusChanged(walletModel->getEncryptionStatus());
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

void WalletView::encryptWallet(bool status)
{
<<<<<<< HEAD
    if(!walletModel)
        return;
    AskPassphraseDialog dlg(status ? AskPassphraseDialog::Encrypt : AskPassphraseDialog::Decrypt, this);
    dlg.setModel(walletModel);
=======
    if (!walletModel)
        return;
    AskPassphraseDialog dlg(status ? AskPassphraseDialog::Encrypt : AskPassphraseDialog::Decrypt, this, walletModel);
//  dlg.setModel(walletModel);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    dlg.exec();

    updateEncryptionStatus();
}

void WalletView::backupWallet()
{
    QString filename = GUIUtil::getSaveFileName(this,
        tr("Backup Wallet"), QString(),
        tr("Wallet Data (*.dat)"), NULL);

    if (filename.isEmpty())
        return;

    if (!walletModel->backupWallet(filename)) {
<<<<<<< HEAD
        Q_EMIT message(tr("Backup Failed"), tr("There was an error trying to save the wallet data to %1.").arg(filename),
            CClientUIInterface::MSG_ERROR);
        }
    else {
        Q_EMIT message(tr("Backup Successful"), tr("The wallet data was successfully saved to %1.").arg(filename),
=======
        emit message(tr("Backup Failed"), tr("There was an error trying to save the wallet data to %1.").arg(filename),
            CClientUIInterface::MSG_ERROR);
    } else {
        emit message(tr("Backup Successful"), tr("The wallet data was successfully saved to %1.").arg(filename),
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            CClientUIInterface::MSG_INFORMATION);
    }
}

void WalletView::changePassphrase()
{
<<<<<<< HEAD
    AskPassphraseDialog dlg(AskPassphraseDialog::ChangePass, this);
    dlg.setModel(walletModel);
    dlg.exec();
}

void WalletView::unlockWallet(bool fForMixingOnly)
{
    if(!walletModel)
        return;
    // Unlock wallet when requested by wallet model

    if (walletModel->getEncryptionStatus() == WalletModel::Locked || walletModel->getEncryptionStatus() == WalletModel::UnlockedForMixingOnly)
    {
        AskPassphraseDialog dlg(fForMixingOnly ? AskPassphraseDialog::UnlockMixing : AskPassphraseDialog::Unlock, this);
        dlg.setModel(walletModel);
=======
    AskPassphraseDialog dlg(AskPassphraseDialog::ChangePass, this, walletModel);
//  dlg.setModel(walletModel);
    dlg.exec();
}

void WalletView::unlockWallet()
{
    if (!walletModel)
        return;
    // Unlock wallet when requested by wallet model

    if (walletModel->getEncryptionStatus() == WalletModel::Locked || walletModel->getEncryptionStatus() == WalletModel::UnlockedForAnonymizationOnly) {
        AskPassphraseDialog dlg(AskPassphraseDialog::UnlockAnonymize, this, walletModel);
//      dlg.setModel(walletModel);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        dlg.exec();
    }
}

void WalletView::lockWallet()
{
<<<<<<< HEAD
    if(!walletModel)
=======
    if (!walletModel)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return;

    walletModel->setWalletLocked(true);
}

void WalletView::usedSendingAddresses()
{
<<<<<<< HEAD
    if(!walletModel)
        return;

    usedSendingAddressesPage->show();
    usedSendingAddressesPage->raise();
    usedSendingAddressesPage->activateWindow();
=======
    if (!walletModel)
        return;
    AddressBookPage* dlg = new AddressBookPage(AddressBookPage::ForEditing, AddressBookPage::SendingTab, this);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setModel(walletModel->getAddressTableModel());
    dlg->show();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

void WalletView::usedReceivingAddresses()
{
<<<<<<< HEAD
    if(!walletModel)
        return;

    usedReceivingAddressesPage->show();
    usedReceivingAddressesPage->raise();
    usedReceivingAddressesPage->activateWindow();
}

void WalletView::showProgress(const QString &title, int nProgress)
{
    if (nProgress == 0)
    {
=======
    if (!walletModel)
        return;
    AddressBookPage* dlg = new AddressBookPage(AddressBookPage::ForEditing, AddressBookPage::ReceivingTab, this);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setModel(walletModel->getAddressTableModel());
    dlg->show();
}

void WalletView::showProgress(const QString& title, int nProgress)
{
    if (nProgress == 0) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        progressDialog = new QProgressDialog(title, "", 0, 100);
        progressDialog->setWindowModality(Qt::ApplicationModal);
        progressDialog->setMinimumDuration(0);
        progressDialog->setCancelButton(0);
        progressDialog->setAutoClose(false);
        progressDialog->setValue(0);
<<<<<<< HEAD
    }
    else if (nProgress == 100)
    {
        if (progressDialog)
        {
            progressDialog->close();
            progressDialog->deleteLater();
        }
    }
    else if (progressDialog)
        progressDialog->setValue(nProgress);
}

void WalletView::requestedSyncWarningInfo()
{
    Q_EMIT outOfSyncWarningClicked();
}

=======
    } else if (nProgress == 100) {
        if (progressDialog) {
            progressDialog->close();
            progressDialog->deleteLater();
        }
    } else if (progressDialog)
        progressDialog->setValue(nProgress);
}

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
/** Update wallet with the sum of the selected transactions */
void WalletView::trxAmount(QString amount)
{
    transactionSum->setText(amount);
}
