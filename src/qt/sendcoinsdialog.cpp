<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Copyright (c) 2014-2017 The GelCoin developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The LUX developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "sendcoinsdialog.h"
#include "ui_sendcoinsdialog.h"
<<<<<<< HEAD
=======
#include "askpassphrasedialog.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

#include "addresstablemodel.h"
#include "bitcoinunits.h"
#include "clientmodel.h"
#include "coincontroldialog.h"
#include "guiutil.h"
#include "optionsmodel.h"
<<<<<<< HEAD
#include "platformstyle.h"
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include "sendcoinsentry.h"
#include "walletmodel.h"

#include "base58.h"
#include "coincontrol.h"
<<<<<<< HEAD
#include "validation.h" // mempool and minRelayTxFee
#include "ui_interface.h"
#include "txmempool.h"
#include "wallet/wallet.h"

#include "privatesend.h"
=======
#include "ui_interface.h"
#include "utilmoneystr.h"
#include "wallet.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

#include <QMessageBox>
#include <QScrollBar>
#include <QSettings>
#include <QTextDocument>

<<<<<<< HEAD
SendCoinsDialog::SendCoinsDialog(const PlatformStyle *platformStyle, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SendCoinsDialog),
    clientModel(0),
    model(0),
    fNewRecipientAllowed(true),
    fFeeMinimized(true),
    platformStyle(platformStyle)
{
    ui->setupUi(this);
    QString theme = GUIUtil::getThemeName();

    if (!platformStyle->getImagesOnButtons()) {
        ui->addButton->setIcon(QIcon());
        ui->clearButton->setIcon(QIcon());
        ui->sendButton->setIcon(QIcon());
    } else {
        ui->addButton->setIcon(QIcon(":/icons/" + theme + "/add"));
        ui->clearButton->setIcon(QIcon(":/icons/" + theme + "/remove"));
        ui->sendButton->setIcon(QIcon(":/icons/" + theme + "/send"));
    }
=======
SendCoinsDialog::SendCoinsDialog(QWidget* parent) : QDialog(parent),
                                                    ui(new Ui::SendCoinsDialog),
                                                    clientModel(0),
                                                    model(0),
                                                    fNewRecipientAllowed(true),
                                                    fFeeMinimized(true)
{
    ui->setupUi(this);

#ifdef Q_OS_MAC // Icons on push buttons are very uncommon on Mac
    ui->addButton->setIcon(QIcon());
    ui->clearButton->setIcon(QIcon());
    ui->sendButton->setIcon(QIcon());
#endif
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    GUIUtil::setupAddressWidget(ui->lineEditCoinControlChange, this);

    addEntry();

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addEntry()));
    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clear()));

    // Coin Control
    connect(ui->pushButtonCoinControl, SIGNAL(clicked()), this, SLOT(coinControlButtonClicked()));
    connect(ui->checkBoxCoinControlChange, SIGNAL(stateChanged(int)), this, SLOT(coinControlChangeChecked(int)));
<<<<<<< HEAD
    connect(ui->lineEditCoinControlChange, SIGNAL(textEdited(const QString &)), this, SLOT(coinControlChangeEdited(const QString &)));

    // GelCoin specific
    QSettings settings;
    if (!settings.contains("bUseDarkSend"))
        settings.setValue("bUseDarkSend", false);
    if (!settings.contains("bUseInstantX"))
        settings.setValue("bUseInstantX", false);

    bool fUsePrivateSend = settings.value("bUseDarkSend").toBool();
    bool fUseInstantSend = settings.value("bUseInstantX").toBool();
    if(fLiteMode) {
        ui->checkUsePrivateSend->setChecked(false);
        ui->checkUsePrivateSend->setVisible(false);
        ui->checkUseInstantSend->setVisible(false);
        CoinControlDialog::coinControl->fUsePrivateSend = false;
        CoinControlDialog::coinControl->fUseInstantSend = false;
    }
    else{
        ui->checkUsePrivateSend->setChecked(fUsePrivateSend);
        ui->checkUseInstantSend->setChecked(fUseInstantSend);
        CoinControlDialog::coinControl->fUsePrivateSend = fUsePrivateSend;
        CoinControlDialog::coinControl->fUseInstantSend = fUseInstantSend;
    }

    connect(ui->checkUsePrivateSend, SIGNAL(stateChanged ( int )), this, SLOT(updateDisplayUnit()));
    connect(ui->checkUseInstantSend, SIGNAL(stateChanged ( int )), this, SLOT(updateInstantSend()));

    // Coin Control: clipboard actions
    QAction *clipboardQuantityAction = new QAction(tr("Copy quantity"), this);
    QAction *clipboardAmountAction = new QAction(tr("Copy amount"), this);
    QAction *clipboardFeeAction = new QAction(tr("Copy fee"), this);
    QAction *clipboardAfterFeeAction = new QAction(tr("Copy after fee"), this);
    QAction *clipboardBytesAction = new QAction(tr("Copy bytes"), this);
    QAction *clipboardLowOutputAction = new QAction(tr("Copy dust"), this);
    QAction *clipboardChangeAction = new QAction(tr("Copy change"), this);
=======
    connect(ui->lineEditCoinControlChange, SIGNAL(textEdited(const QString&)), this, SLOT(coinControlChangeEdited(const QString&)));

    // UTXO Splitter
    connect(ui->splitBlockCheckBox, SIGNAL(stateChanged(int)), this, SLOT(splitBlockChecked(int)));
    connect(ui->splitBlockLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(splitBlockLineEditChanged(const QString&)));

    // LUX specific
    QSettings settings;
    if (!settings.contains("bUseObfuscation"))
        settings.setValue("bUseObfuscation", false);
    if (!settings.contains("bUseSwiftTX"))
        settings.setValue("bUseSwiftTX", false);

    bool useObfuscation = settings.value("bUseObfuscation").toBool();
    bool useSwiftTX = settings.value("bUseSwiftTX").toBool();
    if (fLiteMode) {
        ui->checkUseObfuscation->setChecked(false);
        ui->checkUseObfuscation->setVisible(false);
        ui->checkSwiftTX->setVisible(false);
        CoinControlDialog::coinControl->useObfuscation = false;
        CoinControlDialog::coinControl->useSwiftTX = false;
    } else {
        ui->checkUseObfuscation->setChecked(useObfuscation);
        ui->checkSwiftTX->setChecked(useSwiftTX);
        CoinControlDialog::coinControl->useObfuscation = useObfuscation;
        CoinControlDialog::coinControl->useSwiftTX = useSwiftTX;
    }

    connect(ui->checkUseObfuscation, SIGNAL(stateChanged(int)), this, SLOT(updateDisplayUnit()));
    connect(ui->checkSwiftTX, SIGNAL(stateChanged(int)), this, SLOT(updateSwiftTX()));

    // Coin Control: clipboard actions
    QAction* clipboardQuantityAction = new QAction(tr("Copy quantity"), this);
    QAction* clipboardAmountAction = new QAction(tr("Copy amount"), this);
    QAction* clipboardFeeAction = new QAction(tr("Copy fee"), this);
    QAction* clipboardAfterFeeAction = new QAction(tr("Copy after fee"), this);
    QAction* clipboardBytesAction = new QAction(tr("Copy bytes"), this);
    QAction* clipboardPriorityAction = new QAction(tr("Copy priority"), this);
    QAction* clipboardLowOutputAction = new QAction(tr("Copy dust"), this);
    QAction* clipboardChangeAction = new QAction(tr("Copy change"), this);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    connect(clipboardQuantityAction, SIGNAL(triggered()), this, SLOT(coinControlClipboardQuantity()));
    connect(clipboardAmountAction, SIGNAL(triggered()), this, SLOT(coinControlClipboardAmount()));
    connect(clipboardFeeAction, SIGNAL(triggered()), this, SLOT(coinControlClipboardFee()));
    connect(clipboardAfterFeeAction, SIGNAL(triggered()), this, SLOT(coinControlClipboardAfterFee()));
    connect(clipboardBytesAction, SIGNAL(triggered()), this, SLOT(coinControlClipboardBytes()));
<<<<<<< HEAD
=======
    connect(clipboardPriorityAction, SIGNAL(triggered()), this, SLOT(coinControlClipboardPriority()));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    connect(clipboardLowOutputAction, SIGNAL(triggered()), this, SLOT(coinControlClipboardLowOutput()));
    connect(clipboardChangeAction, SIGNAL(triggered()), this, SLOT(coinControlClipboardChange()));
    ui->labelCoinControlQuantity->addAction(clipboardQuantityAction);
    ui->labelCoinControlAmount->addAction(clipboardAmountAction);
    ui->labelCoinControlFee->addAction(clipboardFeeAction);
    ui->labelCoinControlAfterFee->addAction(clipboardAfterFeeAction);
    ui->labelCoinControlBytes->addAction(clipboardBytesAction);
<<<<<<< HEAD
=======
    ui->labelCoinControlPriority->addAction(clipboardPriorityAction);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    ui->labelCoinControlLowOutput->addAction(clipboardLowOutputAction);
    ui->labelCoinControlChange->addAction(clipboardChangeAction);

    // init transaction fee section
    if (!settings.contains("fFeeSectionMinimized"))
        settings.setValue("fFeeSectionMinimized", true);
    if (!settings.contains("nFeeRadio") && settings.contains("nTransactionFee") && settings.value("nTransactionFee").toLongLong() > 0) // compatibility
<<<<<<< HEAD
        settings.setValue("nFeeRadio", 1); // custom
    if (!settings.contains("nFeeRadio"))
        settings.setValue("nFeeRadio", 0); // recommended
    if (!settings.contains("nCustomFeeRadio") && settings.contains("nTransactionFee") && settings.value("nTransactionFee").toLongLong() > 0) // compatibility
        settings.setValue("nCustomFeeRadio", 1); // total at least
=======
        settings.setValue("nFeeRadio", 1);                                                                                             // custom
    if (!settings.contains("nFeeRadio"))
        settings.setValue("nFeeRadio", 0);                                                                                                   // recommended
    if (!settings.contains("nCustomFeeRadio") && settings.contains("nTransactionFee") && settings.value("nTransactionFee").toLongLong() > 0) // compatibility
        settings.setValue("nCustomFeeRadio", 1);                                                                                             // total at least
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    if (!settings.contains("nCustomFeeRadio"))
        settings.setValue("nCustomFeeRadio", 0); // per kilobyte
    if (!settings.contains("nSmartFeeSliderPosition"))
        settings.setValue("nSmartFeeSliderPosition", 0);
    if (!settings.contains("nTransactionFee"))
        settings.setValue("nTransactionFee", (qint64)DEFAULT_TRANSACTION_FEE);
    if (!settings.contains("fPayOnlyMinFee"))
        settings.setValue("fPayOnlyMinFee", false);
    if (!settings.contains("fSendFreeTransactions"))
        settings.setValue("fSendFreeTransactions", false);

    ui->groupFee->setId(ui->radioSmartFee, 0);
    ui->groupFee->setId(ui->radioCustomFee, 1);
    ui->groupFee->button((int)std::max(0, std::min(1, settings.value("nFeeRadio").toInt())))->setChecked(true);
    ui->groupCustomFee->setId(ui->radioCustomPerKilobyte, 0);
    ui->groupCustomFee->setId(ui->radioCustomAtLeast, 1);
    ui->groupCustomFee->button((int)std::max(0, std::min(1, settings.value("nCustomFeeRadio").toInt())))->setChecked(true);
    ui->sliderSmartFee->setValue(settings.value("nSmartFeeSliderPosition").toInt());
    ui->customFee->setValue(settings.value("nTransactionFee").toLongLong());
    ui->checkBoxMinimumFee->setChecked(settings.value("fPayOnlyMinFee").toBool());
    ui->checkBoxFreeTx->setChecked(settings.value("fSendFreeTransactions").toBool());
    minimizeFeeSection(settings.value("fFeeSectionMinimized").toBool());
}

<<<<<<< HEAD
void SendCoinsDialog::setClientModel(ClientModel *clientModel)
=======
void SendCoinsDialog::setClientModel(ClientModel* clientModel)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    this->clientModel = clientModel;

    if (clientModel) {
<<<<<<< HEAD
        connect(clientModel, SIGNAL(numBlocksChanged(int,QDateTime,double,bool)), this, SLOT(updateSmartFeeLabel()));
    }
}

void SendCoinsDialog::setModel(WalletModel *model)
{
    this->model = model;

    if(model && model->getOptionsModel())
    {
        for(int i = 0; i < ui->entries->count(); ++i)
        {
            SendCoinsEntry *entry = qobject_cast<SendCoinsEntry*>(ui->entries->itemAt(i)->widget());
            if(entry)
            {
=======
        connect(clientModel, SIGNAL(numBlocksChanged(int)), this, SLOT(updateSmartFeeLabel()));
    }
}

void SendCoinsDialog::setModel(WalletModel* model)
{
    this->model = model;

    if (model && model->getOptionsModel()) {
        for (int i = 0; i < ui->entries->count(); ++i) {
            SendCoinsEntry* entry = qobject_cast<SendCoinsEntry*>(ui->entries->itemAt(i)->widget());
            if (entry) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                entry->setModel(model);
            }
        }

        setBalance(model->getBalance(), model->getUnconfirmedBalance(), model->getImmatureBalance(), model->getAnonymizedBalance(),
<<<<<<< HEAD
                   model->getWatchBalance(), model->getWatchUnconfirmedBalance(), model->getWatchImmatureBalance());
        connect(model, SIGNAL(balanceChanged(CAmount,CAmount,CAmount,CAmount,CAmount,CAmount,CAmount)), this, SLOT(setBalance(CAmount,CAmount,CAmount,CAmount,CAmount,CAmount,CAmount)));
=======
            model->getWatchBalance(), model->getWatchUnconfirmedBalance(), model->getWatchImmatureBalance());
        connect(model, SIGNAL(balanceChanged(CAmount, CAmount, CAmount, CAmount, CAmount, CAmount, CAmount)), this, SLOT(setBalance(CAmount, CAmount, CAmount, CAmount, CAmount, CAmount, CAmount)));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        connect(model->getOptionsModel(), SIGNAL(displayUnitChanged(int)), this, SLOT(updateDisplayUnit()));
        updateDisplayUnit();

        // Coin Control
        connect(model->getOptionsModel(), SIGNAL(displayUnitChanged(int)), this, SLOT(coinControlUpdateLabels()));
        connect(model->getOptionsModel(), SIGNAL(coinControlFeaturesChanged(bool)), this, SLOT(coinControlFeatureChanged(bool)));
        ui->frameCoinControl->setVisible(model->getOptionsModel()->getCoinControlFeatures());
        coinControlUpdateLabels();

        // fee section
        connect(ui->sliderSmartFee, SIGNAL(valueChanged(int)), this, SLOT(updateSmartFeeLabel()));
        connect(ui->sliderSmartFee, SIGNAL(valueChanged(int)), this, SLOT(updateGlobalFeeVariables()));
        connect(ui->sliderSmartFee, SIGNAL(valueChanged(int)), this, SLOT(coinControlUpdateLabels()));
        connect(ui->groupFee, SIGNAL(buttonClicked(int)), this, SLOT(updateFeeSectionControls()));
        connect(ui->groupFee, SIGNAL(buttonClicked(int)), this, SLOT(updateGlobalFeeVariables()));
        connect(ui->groupFee, SIGNAL(buttonClicked(int)), this, SLOT(coinControlUpdateLabels()));
        connect(ui->groupCustomFee, SIGNAL(buttonClicked(int)), this, SLOT(updateGlobalFeeVariables()));
        connect(ui->groupCustomFee, SIGNAL(buttonClicked(int)), this, SLOT(coinControlUpdateLabels()));
        connect(ui->customFee, SIGNAL(valueChanged()), this, SLOT(updateGlobalFeeVariables()));
        connect(ui->customFee, SIGNAL(valueChanged()), this, SLOT(coinControlUpdateLabels()));
        connect(ui->checkBoxMinimumFee, SIGNAL(stateChanged(int)), this, SLOT(setMinimumFee()));
        connect(ui->checkBoxMinimumFee, SIGNAL(stateChanged(int)), this, SLOT(updateFeeSectionControls()));
        connect(ui->checkBoxMinimumFee, SIGNAL(stateChanged(int)), this, SLOT(updateGlobalFeeVariables()));
        connect(ui->checkBoxMinimumFee, SIGNAL(stateChanged(int)), this, SLOT(coinControlUpdateLabels()));
        connect(ui->checkBoxFreeTx, SIGNAL(stateChanged(int)), this, SLOT(updateGlobalFeeVariables()));
        connect(ui->checkBoxFreeTx, SIGNAL(stateChanged(int)), this, SLOT(coinControlUpdateLabels()));
<<<<<<< HEAD
        ui->customFee->setSingleStep(CWallet::GetRequiredFee(1000));
=======
        ui->customFee->setSingleStep(CWallet::minTxFee.GetFeePerK());
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        updateFeeSectionControls();
        updateMinFeeLabel();
        updateSmartFeeLabel();
        updateGlobalFeeVariables();
    }
}

SendCoinsDialog::~SendCoinsDialog()
{
    QSettings settings;
    settings.setValue("fFeeSectionMinimized", fFeeMinimized);
    settings.setValue("nFeeRadio", ui->groupFee->checkedId());
    settings.setValue("nCustomFeeRadio", ui->groupCustomFee->checkedId());
    settings.setValue("nSmartFeeSliderPosition", ui->sliderSmartFee->value());
    settings.setValue("nTransactionFee", (qint64)ui->customFee->value());
    settings.setValue("fPayOnlyMinFee", ui->checkBoxMinimumFee->isChecked());
    settings.setValue("fSendFreeTransactions", ui->checkBoxFreeTx->isChecked());

    delete ui;
}

void SendCoinsDialog::on_sendButton_clicked()
{
<<<<<<< HEAD
    if(!model || !model->getOptionsModel())
=======
    if (!model || !model->getOptionsModel())
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return;

    QList<SendCoinsRecipient> recipients;
    bool valid = true;

<<<<<<< HEAD
    for(int i = 0; i < ui->entries->count(); ++i)
    {
        SendCoinsEntry *entry = qobject_cast<SendCoinsEntry*>(ui->entries->itemAt(i)->widget());
        if(entry)
        {
            if(entry->validate())
            {
                recipients.append(entry->getValue());
            }
            else
            {
=======
    for (int i = 0; i < ui->entries->count(); ++i) {
        SendCoinsEntry* entry = qobject_cast<SendCoinsEntry*>(ui->entries->itemAt(i)->widget());

        //UTXO splitter - address should be our own
        CBitcoinAddress address = entry->getValue().address.toStdString();
        if (!model->isMine(address) && ui->splitBlockCheckBox->checkState() == Qt::Checked) {
            CoinControlDialog::coinControl->fSplitBlock = false;
            ui->splitBlockCheckBox->setCheckState(Qt::Unchecked);
            QMessageBox::warning(this, tr("Send Coins"),
                tr("The split block tool does not work when sending to outside addresses. Try again."),
                QMessageBox::Ok, QMessageBox::Ok);
            return;
        }

        if (entry) {
            if (entry->validate()) {
                recipients.append(entry->getValue());
            } else {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                valid = false;
            }
        }
    }

<<<<<<< HEAD
    if(!valid || recipients.isEmpty())
    {
        return;
    }

=======
    if (!valid || recipients.isEmpty()) {
        return;
    }

    //set split block in model
    CoinControlDialog::coinControl->fSplitBlock = ui->splitBlockCheckBox->checkState() == Qt::Checked;

    if (ui->entries->count() > 1 && ui->splitBlockCheckBox->checkState() == Qt::Checked) {
        CoinControlDialog::coinControl->fSplitBlock = false;
        ui->splitBlockCheckBox->setCheckState(Qt::Unchecked);
        QMessageBox::warning(this, tr("Send Coins"),
            tr("The split block tool does not work with multiple addresses. Try again."),
            QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    if (CoinControlDialog::coinControl->fSplitBlock)
        CoinControlDialog::coinControl->nSplitBlock = int(ui->splitBlockLineEdit->text().toInt());

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    QString strFunds = tr("using") + " <b>" + tr("anonymous funds") + "</b>";
    QString strFee = "";
    recipients[0].inputType = ONLY_DENOMINATED;

<<<<<<< HEAD
    if(ui->checkUsePrivateSend->isChecked()) {
=======
    if (ui->checkUseObfuscation->isChecked()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        recipients[0].inputType = ONLY_DENOMINATED;
        strFunds = tr("using") + " <b>" + tr("anonymous funds") + "</b>";
        QString strNearestAmount(
            BitcoinUnits::formatWithUnit(
<<<<<<< HEAD
                model->getOptionsModel()->getDisplayUnit(), CPrivateSend::GetSmallestDenomination()));
        strFee = QString(tr(
            "(privatesend requires this amount to be rounded up to the nearest %1)."
        ).arg(strNearestAmount));
    } else {
        recipients[0].inputType = ALL_COINS;
        strFunds = tr("using") + " <b>" + tr("any available funds (not anonymous)") + "</b>";
    }

    if(ui->checkUseInstantSend->isChecked()) {
        recipients[0].fUseInstantSend = true;
        strFunds += " ";
        strFunds += tr("and InstantSend");
    } else {
        recipients[0].fUseInstantSend = false;
    }


    fNewRecipientAllowed = false;
=======
                model->getOptionsModel()->getDisplayUnit(), 0.1 * COIN));
        strFee = QString(tr(
            "(obfuscation requires this amount to be rounded up to the nearest %1).")
                             .arg(strNearestAmount));
    } else {
        recipients[0].inputType = ALL_COINS;
        strFunds = tr("using") + " <b>" + tr("any available funds (not recommended)") + "</b>";
    }

    if (ui->checkSwiftTX->isChecked()) {
        recipients[0].useSwiftTX = true;
        strFunds += " ";
        strFunds += tr("and SwiftTX");
    } else {
        recipients[0].useSwiftTX = false;
    }


    // Format confirmation message
    QStringList formatted;
    foreach (const SendCoinsRecipient& rcp, recipients) {
        // generate bold amount string
        QString amount = "<b>" + BitcoinUnits::formatHtmlWithUnit(model->getOptionsModel()->getDisplayUnit(), rcp.amount);
        amount.append("</b> ").append(strFunds);

        // generate monospace address string
        QString address = "<span style='font-family: monospace;'>" + rcp.address;
        address.append("</span>");

        QString recipientElement;

        if (!rcp.paymentRequest.IsInitialized()) // normal payment
        {
            if (rcp.label.length() > 0) // label with address
            {
                recipientElement = tr("%1 to %2").arg(amount, GUIUtil::HtmlEscape(rcp.label));
                recipientElement.append(QString(" (%1)").arg(address));
            } else // just address
            {
                recipientElement = tr("%1 to %2").arg(amount, address);
            }
        } else if (!rcp.authenticatedMerchant.isEmpty()) // secure payment request
        {
            recipientElement = tr("%1 to %2").arg(amount, GUIUtil::HtmlEscape(rcp.authenticatedMerchant));
        } else // insecure payment request
        {
            recipientElement = tr("%1 to %2").arg(amount, address);
        }

        if (fSplitBlock) {
            recipientElement.append(tr(" split into %1 outputs using the UTXO splitter.").arg(CoinControlDialog::coinControl->nSplitBlock));
        }

        formatted.append(recipientElement);
    }

    fNewRecipientAllowed = false;

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    // request unlock only if was locked or unlocked for mixing:
    // this way we let users unlock by walletpassphrase or by menu
    // and make many transactions while unlocking through this dialog
    // will call relock
    WalletModel::EncryptionStatus encStatus = model->getEncryptionStatus();
<<<<<<< HEAD
    if(encStatus == model->Locked || encStatus == model->UnlockedForMixingOnly)
    {
        WalletModel::UnlockContext ctx(model->requestUnlock());
        if(!ctx.isValid())
        {
=======
    if (encStatus == model->Locked || encStatus == model->UnlockedForAnonymizationOnly) {
        WalletModel::UnlockContext ctx(model->requestUnlock(true));
        if (!ctx.isValid()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            // Unlock wallet was cancelled
            fNewRecipientAllowed = true;
            return;
        }
<<<<<<< HEAD
        send(recipients, strFee, strFunds);
        return;
    }
    // already unlocked or not encrypted at all
    send(recipients, strFee, strFunds);
}

void SendCoinsDialog::send(QList<SendCoinsRecipient> recipients, QString strFee, QString strFunds)
=======
        send(recipients, strFee, formatted);
        return;
    }
    // already unlocked or not encrypted at all
    send(recipients, strFee, formatted);
}

void SendCoinsDialog::send(QList<SendCoinsRecipient> recipients, QString strFee, QStringList formatted)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    // prepare transaction for getting txFee earlier
    WalletModelTransaction currentTransaction(recipients);
    WalletModel::SendCoinsReturn prepareStatus;
    if (model->getOptionsModel()->getCoinControlFeatures()) // coin control enabled
        prepareStatus = model->prepareTransaction(currentTransaction, CoinControlDialog::coinControl);
    else
        prepareStatus = model->prepareTransaction(currentTransaction);

    // process prepareStatus and on error generate message shown to user
    processSendCoinsReturn(prepareStatus,
<<<<<<< HEAD
        BitcoinUnits::formatWithUnit(model->getOptionsModel()->getDisplayUnit(), currentTransaction.getTransactionFee()));

    if(prepareStatus.status != WalletModel::OK) {
=======
        BitcoinUnits::formatWithUnit(model->getOptionsModel()->getDisplayUnit(), currentTransaction.getTransactionFee()), true);

    if (prepareStatus.status != WalletModel::OK) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        fNewRecipientAllowed = true;
        return;
    }

    CAmount txFee = currentTransaction.getTransactionFee();
<<<<<<< HEAD

    // Format confirmation message
    QStringList formatted;
    Q_FOREACH(const SendCoinsRecipient &rcp, currentTransaction.getRecipients())
    {
        // generate bold amount string
        QString amount = "<b>" + BitcoinUnits::formatHtmlWithUnit(model->getOptionsModel()->getDisplayUnit(), rcp.amount);
        amount.append("</b> ").append(strFunds);

        // generate monospace address string
        QString address = "<span style='font-family: monospace;'>" + rcp.address;
        address.append("</span>");

        QString recipientElement;

        if (!rcp.paymentRequest.IsInitialized()) // normal payment
        {
            if(rcp.label.length() > 0) // label with address
            {
                recipientElement = tr("%1 to %2").arg(amount, GUIUtil::HtmlEscape(rcp.label));
                recipientElement.append(QString(" (%1)").arg(address));
            }
            else // just address
            {
                recipientElement = tr("%1 to %2").arg(amount, address);
            }
        }
        else if(!rcp.authenticatedMerchant.isEmpty()) // authenticated payment request
        {
            recipientElement = tr("%1 to %2").arg(amount, GUIUtil::HtmlEscape(rcp.authenticatedMerchant));
        }
        else // unauthenticated payment request
        {
            recipientElement = tr("%1 to %2").arg(amount, address);
        }

        formatted.append(recipientElement);
    }

    QString questionString = tr("Are you sure you want to send?");
    questionString.append("<br /><br />%1");

    if(txFee > 0)
    {
=======
    QString questionString = tr("Are you sure you want to send?");
    questionString.append("<br /><br />%1");

    if (txFee > 0) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        // append fee string if a fee is required
        questionString.append("<hr /><span style='color:#aa0000;'>");
        questionString.append(BitcoinUnits::formatHtmlWithUnit(model->getOptionsModel()->getDisplayUnit(), txFee));
        questionString.append("</span> ");
        questionString.append(tr("are added as transaction fee"));
        questionString.append(" ");
        questionString.append(strFee);

        // append transaction size
        questionString.append(" (" + QString::number((double)currentTransaction.getTransactionSize() / 1000) + " kB)");
    }

    // add total amount in all subdivision units
    questionString.append("<hr />");
    CAmount totalAmount = currentTransaction.getTotalTransactionAmount() + txFee;
    QStringList alternativeUnits;
<<<<<<< HEAD
    Q_FOREACH(BitcoinUnits::Unit u, BitcoinUnits::availableUnits())
    {
        if(u != model->getOptionsModel()->getDisplayUnit())
=======
    foreach (BitcoinUnits::Unit u, BitcoinUnits::availableUnits()) {
        if (u != model->getOptionsModel()->getDisplayUnit())
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            alternativeUnits.append(BitcoinUnits::formatHtmlWithUnit(u, totalAmount));
    }

    // Show total amount + all alternative units
    questionString.append(tr("Total Amount = <b>%1</b><br />= %2")
<<<<<<< HEAD
        .arg(BitcoinUnits::formatHtmlWithUnit(model->getOptionsModel()->getDisplayUnit(), totalAmount))
        .arg(alternativeUnits.join("<br />= ")));
=======
                              .arg(BitcoinUnits::formatHtmlWithUnit(model->getOptionsModel()->getDisplayUnit(), totalAmount))
                              .arg(alternativeUnits.join("<br />= ")));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    // Limit number of displayed entries
    int messageEntries = formatted.size();
    int displayedEntries = 0;
<<<<<<< HEAD
    for(int i = 0; i < formatted.size(); i++){
        if(i >= MAX_SEND_POPUP_ENTRIES){
            formatted.removeLast();
            i--;
        }
        else{
            displayedEntries = i+1;
=======
    for (int i = 0; i < formatted.size(); i++) {
        if (i >= MAX_SEND_POPUP_ENTRIES) {
            formatted.removeLast();
            i--;
        } else {
            displayedEntries = i + 1;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        }
    }
    questionString.append("<hr />");
    questionString.append(tr("<b>(%1 of %2 entries displayed)</b>").arg(displayedEntries).arg(messageEntries));

    // Display message box
    QMessageBox::StandardButton retval = QMessageBox::question(this, tr("Confirm send coins"),
        questionString.arg(formatted.join("<br />")),
        QMessageBox::Yes | QMessageBox::Cancel,
        QMessageBox::Cancel);

<<<<<<< HEAD
    if(retval != QMessageBox::Yes)
    {
=======
    if (retval != QMessageBox::Yes) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        fNewRecipientAllowed = true;
        return;
    }

    // now send the prepared transaction
    WalletModel::SendCoinsReturn sendStatus = model->sendCoins(currentTransaction);
    // process sendStatus and on error generate message shown to user
    processSendCoinsReturn(sendStatus);

<<<<<<< HEAD
    if (sendStatus.status == WalletModel::OK)
    {
=======
    if (sendStatus.status == WalletModel::OK) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        accept();
        CoinControlDialog::coinControl->UnSelectAll();
        coinControlUpdateLabels();
    }
    fNewRecipientAllowed = true;
}

void SendCoinsDialog::clear()
{
    // Remove entries until only one left
<<<<<<< HEAD
    while(ui->entries->count())
    {
=======
    while (ui->entries->count()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        ui->entries->takeAt(0)->widget()->deleteLater();
    }
    addEntry();

    updateTabsAndLabels();
}

void SendCoinsDialog::reject()
{
    clear();
}

void SendCoinsDialog::accept()
{
    clear();
}

<<<<<<< HEAD
SendCoinsEntry *SendCoinsDialog::addEntry()
{
    SendCoinsEntry *entry = new SendCoinsEntry(platformStyle, this);
=======
SendCoinsEntry* SendCoinsDialog::addEntry()
{
    SendCoinsEntry* entry = new SendCoinsEntry(this);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    entry->setModel(model);
    ui->entries->addWidget(entry);
    connect(entry, SIGNAL(removeEntry(SendCoinsEntry*)), this, SLOT(removeEntry(SendCoinsEntry*)));
    connect(entry, SIGNAL(payAmountChanged()), this, SLOT(coinControlUpdateLabels()));
<<<<<<< HEAD
    connect(entry, SIGNAL(subtractFeeFromAmountChanged()), this, SLOT(coinControlUpdateLabels()));
=======

    updateTabsAndLabels();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    // Focus the field, so that entry can start immediately
    entry->clear();
    entry->setFocus();
    ui->scrollAreaWidgetContents->resize(ui->scrollAreaWidgetContents->sizeHint());
    qApp->processEvents();
    QScrollBar* bar = ui->scrollArea->verticalScrollBar();
<<<<<<< HEAD
    if(bar)
        bar->setSliderPosition(bar->maximum());

    updateTabsAndLabels();
=======
    if (bar)
        bar->setSliderPosition(bar->maximum());
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    return entry;
}

void SendCoinsDialog::updateTabsAndLabels()
{
    setupTabChain(0);
    coinControlUpdateLabels();
}

void SendCoinsDialog::removeEntry(SendCoinsEntry* entry)
{
    entry->hide();

    // If the last entry is about to be removed add an empty one
    if (ui->entries->count() == 1)
        addEntry();

    entry->deleteLater();

    updateTabsAndLabels();
}

<<<<<<< HEAD
QWidget *SendCoinsDialog::setupTabChain(QWidget *prev)
{
    for(int i = 0; i < ui->entries->count(); ++i)
    {
        SendCoinsEntry *entry = qobject_cast<SendCoinsEntry*>(ui->entries->itemAt(i)->widget());
        if(entry)
        {
=======
QWidget* SendCoinsDialog::setupTabChain(QWidget* prev)
{
    for (int i = 0; i < ui->entries->count(); ++i) {
        SendCoinsEntry* entry = qobject_cast<SendCoinsEntry*>(ui->entries->itemAt(i)->widget());
        if (entry) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            prev = entry->setupTabChain(prev);
        }
    }
    QWidget::setTabOrder(prev, ui->sendButton);
    QWidget::setTabOrder(ui->sendButton, ui->clearButton);
    QWidget::setTabOrder(ui->clearButton, ui->addButton);
    return ui->addButton;
}

<<<<<<< HEAD
void SendCoinsDialog::setAddress(const QString &address)
{
    SendCoinsEntry *entry = 0;
    // Replace the first entry if it is still unused
    if(ui->entries->count() == 1)
    {
        SendCoinsEntry *first = qobject_cast<SendCoinsEntry*>(ui->entries->itemAt(0)->widget());
        if(first->isClear())
        {
            entry = first;
        }
    }
    if(!entry)
    {
=======
void SendCoinsDialog::setAddress(const QString& address)
{
    SendCoinsEntry* entry = 0;
    // Replace the first entry if it is still unused
    if (ui->entries->count() == 1) {
        SendCoinsEntry* first = qobject_cast<SendCoinsEntry*>(ui->entries->itemAt(0)->widget());
        if (first->isClear()) {
            entry = first;
        }
    }
    if (!entry) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        entry = addEntry();
    }

    entry->setAddress(address);
}

<<<<<<< HEAD
void SendCoinsDialog::pasteEntry(const SendCoinsRecipient &rv)
{
    if(!fNewRecipientAllowed)
        return;

    SendCoinsEntry *entry = 0;
    // Replace the first entry if it is still unused
    if(ui->entries->count() == 1)
    {
        SendCoinsEntry *first = qobject_cast<SendCoinsEntry*>(ui->entries->itemAt(0)->widget());
        if(first->isClear())
        {
            entry = first;
        }
    }
    if(!entry)
    {
=======
void SendCoinsDialog::pasteEntry(const SendCoinsRecipient& rv)
{
    if (!fNewRecipientAllowed)
        return;

    SendCoinsEntry* entry = 0;
    // Replace the first entry if it is still unused
    if (ui->entries->count() == 1) {
        SendCoinsEntry* first = qobject_cast<SendCoinsEntry*>(ui->entries->itemAt(0)->widget());
        if (first->isClear()) {
            entry = first;
        }
    }
    if (!entry) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        entry = addEntry();
    }

    entry->setValue(rv);
    updateTabsAndLabels();
}

<<<<<<< HEAD
bool SendCoinsDialog::handlePaymentRequest(const SendCoinsRecipient &rv)
=======
bool SendCoinsDialog::handlePaymentRequest(const SendCoinsRecipient& rv)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    // Just paste the entry, all pre-checks
    // are done in paymentserver.cpp.
    pasteEntry(rv);
    return true;
}

<<<<<<< HEAD
void SendCoinsDialog::setBalance(const CAmount& balance, const CAmount& unconfirmedBalance, const CAmount& immatureBalance, const CAmount& anonymizedBalance,
                                 const CAmount& watchBalance, const CAmount& watchUnconfirmedBalance, const CAmount& watchImmatureBalance)
=======
void SendCoinsDialog::setBalance(const CAmount& balance, const CAmount& unconfirmedBalance, const CAmount& immatureBalance, const CAmount& anonymizedBalance, const CAmount& watchBalance, const CAmount& watchUnconfirmedBalance, const CAmount& watchImmatureBalance)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    Q_UNUSED(unconfirmedBalance);
    Q_UNUSED(immatureBalance);
    Q_UNUSED(anonymizedBalance);
    Q_UNUSED(watchBalance);
    Q_UNUSED(watchUnconfirmedBalance);
    Q_UNUSED(watchImmatureBalance);

<<<<<<< HEAD
    if(model && model->getOptionsModel())
    {
	    uint64_t bal = 0;
        QSettings settings;
        settings.setValue("bUseDarkSend", ui->checkUsePrivateSend->isChecked());
	    if(ui->checkUsePrivateSend->isChecked()) {
		    bal = anonymizedBalance;
	    } else {
		    bal = balance;
	    }
=======
    if (model && model->getOptionsModel()) {
        uint64_t bal = 0;
        QSettings settings;
        settings.setValue("bUseObfuscation", ui->checkUseObfuscation->isChecked());
        if (ui->checkUseObfuscation->isChecked()) {
            bal = anonymizedBalance;
        } else {
            bal = balance;
        }
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

        ui->labelBalance->setText(BitcoinUnits::formatWithUnit(model->getOptionsModel()->getDisplayUnit(), bal));
    }
}

void SendCoinsDialog::updateDisplayUnit()
{
<<<<<<< HEAD
    setBalance(model->getBalance(), model->getUnconfirmedBalance(), model->getImmatureBalance(), model->getAnonymizedBalance(),
                   model->getWatchBalance(), model->getWatchUnconfirmedBalance(), model->getWatchImmatureBalance());
    CoinControlDialog::coinControl->fUsePrivateSend = ui->checkUsePrivateSend->isChecked();
=======
    TRY_LOCK(cs_main, lockMain);
    if (!lockMain) return;

    setBalance(model->getBalance(), model->getUnconfirmedBalance(), model->getImmatureBalance(), model->getAnonymizedBalance(),
        model->getWatchBalance(), model->getWatchUnconfirmedBalance(), model->getWatchImmatureBalance());
    CoinControlDialog::coinControl->useObfuscation = ui->checkUseObfuscation->isChecked();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    coinControlUpdateLabels();
    ui->customFee->setDisplayUnit(model->getOptionsModel()->getDisplayUnit());
    updateMinFeeLabel();
    updateSmartFeeLabel();
}

<<<<<<< HEAD
void SendCoinsDialog::updateInstantSend()
{
    QSettings settings;
    settings.setValue("bUseInstantX", ui->checkUseInstantSend->isChecked());
    CoinControlDialog::coinControl->fUseInstantSend = ui->checkUseInstantSend->isChecked();
    coinControlUpdateLabels();
}

void SendCoinsDialog::processSendCoinsReturn(const WalletModel::SendCoinsReturn &sendCoinsReturn, const QString &msgArg)
{
=======
void SendCoinsDialog::updateSwiftTX()
{
    QSettings settings;
    settings.setValue("bUseSwiftTX", ui->checkSwiftTX->isChecked());
    CoinControlDialog::coinControl->useSwiftTX = ui->checkSwiftTX->isChecked();
    coinControlUpdateLabels();
}

void SendCoinsDialog::processSendCoinsReturn(const WalletModel::SendCoinsReturn& sendCoinsReturn, const QString& msgArg, bool fPrepare)
{
    bool fAskForUnlock = false;

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    QPair<QString, CClientUIInterface::MessageBoxFlags> msgParams;
    // Default to a warning message, override if error message is needed
    msgParams.second = CClientUIInterface::MSG_WARNING;

    // This comment is specific to SendCoinsDialog usage of WalletModel::SendCoinsReturn.
    // WalletModel::TransactionCommitFailed is used only in WalletModel::sendCoins()
    // all others are used only in WalletModel::prepareTransaction()
<<<<<<< HEAD
    switch(sendCoinsReturn.status)
    {
    case WalletModel::InvalidAddress:
        msgParams.first = tr("The recipient address is not valid. Please recheck.");
=======
    switch (sendCoinsReturn.status) {
    case WalletModel::InvalidAddress:
        msgParams.first = tr("The recipient address is not valid, please recheck.");
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        break;
    case WalletModel::InvalidAmount:
        msgParams.first = tr("The amount to pay must be larger than 0.");
        break;
    case WalletModel::AmountExceedsBalance:
        msgParams.first = tr("The amount exceeds your balance.");
        break;
    case WalletModel::AmountWithFeeExceedsBalance:
        msgParams.first = tr("The total exceeds your balance when the %1 transaction fee is included.").arg(msgArg);
        break;
    case WalletModel::DuplicateAddress:
<<<<<<< HEAD
        msgParams.first = tr("Duplicate address found: addresses should only be used once each.");
=======
        msgParams.first = tr("Duplicate address found, can only send to each address once per send operation.");
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        break;
    case WalletModel::TransactionCreationFailed:
        msgParams.first = tr("Transaction creation failed!");
        msgParams.second = CClientUIInterface::MSG_ERROR;
        break;
    case WalletModel::TransactionCommitFailed:
        msgParams.first = tr("The transaction was rejected! This might happen if some of the coins in your wallet were already spent, such as if you used a copy of wallet.dat and coins were spent in the copy but not marked as spent here.");
        msgParams.second = CClientUIInterface::MSG_ERROR;
        break;
<<<<<<< HEAD
    case WalletModel::AbsurdFee:
        msgParams.first = tr("A fee higher than %1 is considered an absurdly high fee.").arg(BitcoinUnits::formatWithUnit(model->getOptionsModel()->getDisplayUnit(), maxTxFee));
        break;
    case WalletModel::PaymentRequestExpired:
        msgParams.first = tr("Payment request expired.");
        msgParams.second = CClientUIInterface::MSG_ERROR;
=======
    case WalletModel::AnonymizeOnlyUnlocked:
        // Unlock is only need when the coins are send
        if(!fPrepare)
            fAskForUnlock = true;
        else
            msgParams.first = tr("Error: The wallet was unlocked only to anonymize coins.");
        break;

    case WalletModel::InsaneFee:
        msgParams.first = tr("A fee %1 times higher than %2 per kB is considered an insanely high fee.").arg(10000).arg(BitcoinUnits::formatWithUnit(model->getOptionsModel()->getDisplayUnit(), ::minRelayTxFee.GetFeePerK()));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        break;
    // included to prevent a compiler warning.
    case WalletModel::OK:
    default:
        return;
    }

<<<<<<< HEAD
    Q_EMIT message(tr("Send Coins"), msgParams.first, msgParams.second);
=======
     // Unlock wallet if it wasn't fully unlocked already
        if(fAskForUnlock) {
         model->requestUnlock(false);
         if(model->getEncryptionStatus () != WalletModel::Unlocked) {
             msgParams.first = tr("Error: The wallet was unlocked only to anonymize coins. Unlock canceled.");
         }
         else {
      // Wallet unlocked
         return;
         }
     }

    emit message(tr("Send Coins"), msgParams.first, msgParams.second);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

void SendCoinsDialog::minimizeFeeSection(bool fMinimize)
{
    ui->labelFeeMinimized->setVisible(fMinimize);
<<<<<<< HEAD
    ui->buttonChooseFee  ->setVisible(fMinimize);
=======
    ui->buttonChooseFee->setVisible(fMinimize);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    ui->buttonMinimizeFee->setVisible(!fMinimize);
    ui->frameFeeSelection->setVisible(!fMinimize);
    ui->horizontalLayoutSmartFee->setContentsMargins(0, (fMinimize ? 0 : 6), 0, 0);
    fFeeMinimized = fMinimize;
}

void SendCoinsDialog::on_buttonChooseFee_clicked()
{
    minimizeFeeSection(false);
}

void SendCoinsDialog::on_buttonMinimizeFee_clicked()
{
    updateFeeMinimizedLabel();
    minimizeFeeSection(true);
}

void SendCoinsDialog::setMinimumFee()
{
    ui->radioCustomPerKilobyte->setChecked(true);
<<<<<<< HEAD
    ui->customFee->setValue(CWallet::GetRequiredFee(1000));
=======
    ui->customFee->setValue(CWallet::minTxFee.GetFeePerK());
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

void SendCoinsDialog::updateFeeSectionControls()
{
<<<<<<< HEAD
    ui->sliderSmartFee          ->setEnabled(ui->radioSmartFee->isChecked());
    ui->labelSmartFee           ->setEnabled(ui->radioSmartFee->isChecked());
    ui->labelSmartFee2          ->setEnabled(ui->radioSmartFee->isChecked());
    ui->labelSmartFee3          ->setEnabled(ui->radioSmartFee->isChecked());
    ui->labelFeeEstimation      ->setEnabled(ui->radioSmartFee->isChecked());
    ui->labelSmartFeeNormal     ->setEnabled(ui->radioSmartFee->isChecked());
    ui->labelSmartFeeFast       ->setEnabled(ui->radioSmartFee->isChecked());
    ui->checkBoxMinimumFee      ->setEnabled(ui->radioCustomFee->isChecked());
    ui->labelMinFeeWarning      ->setEnabled(ui->radioCustomFee->isChecked());
    ui->radioCustomPerKilobyte  ->setEnabled(ui->radioCustomFee->isChecked() && !ui->checkBoxMinimumFee->isChecked());
    ui->radioCustomAtLeast      ->setEnabled(ui->radioCustomFee->isChecked() && !ui->checkBoxMinimumFee->isChecked() && CoinControlDialog::coinControl->HasSelected());
    ui->customFee               ->setEnabled(ui->radioCustomFee->isChecked() && !ui->checkBoxMinimumFee->isChecked());
=======
    ui->sliderSmartFee->setEnabled(ui->radioSmartFee->isChecked());
    ui->labelSmartFee->setEnabled(ui->radioSmartFee->isChecked());
    ui->labelSmartFee2->setEnabled(ui->radioSmartFee->isChecked());
    ui->labelSmartFee3->setEnabled(ui->radioSmartFee->isChecked());
    ui->labelFeeEstimation->setEnabled(ui->radioSmartFee->isChecked());
    ui->labelSmartFeeNormal->setEnabled(ui->radioSmartFee->isChecked());
    ui->labelSmartFeeFast->setEnabled(ui->radioSmartFee->isChecked());
    ui->checkBoxMinimumFee->setEnabled(ui->radioCustomFee->isChecked());
    ui->labelMinFeeWarning->setEnabled(ui->radioCustomFee->isChecked());
    ui->radioCustomPerKilobyte->setEnabled(ui->radioCustomFee->isChecked() && !ui->checkBoxMinimumFee->isChecked());
    ui->radioCustomAtLeast->setEnabled(ui->radioCustomFee->isChecked() && !ui->checkBoxMinimumFee->isChecked());
    ui->customFee->setEnabled(ui->radioCustomFee->isChecked() && !ui->checkBoxMinimumFee->isChecked());
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

void SendCoinsDialog::updateGlobalFeeVariables()
{
<<<<<<< HEAD
    if (ui->radioSmartFee->isChecked())
    {
        nTxConfirmTarget = defaultConfirmTarget - ui->sliderSmartFee->value();
        payTxFee = CFeeRate(0);

        // set nMinimumTotalFee to 0 to not accidentally pay a custom fee
        CoinControlDialog::coinControl->nMinimumTotalFee = 0;
    }
    else
    {
        nTxConfirmTarget = defaultConfirmTarget;
        payTxFee = CFeeRate(ui->customFee->value());

        // if user has selected to set a minimum absolute fee, pass the value to coincontrol
        // set nMinimumTotalFee to 0 in case of user has selected that the fee is per KB
        CoinControlDialog::coinControl->nMinimumTotalFee = ui->radioCustomAtLeast->isChecked() ? ui->customFee->value() : 0;
=======
    if (ui->radioSmartFee->isChecked()) {
        nTxConfirmTarget = (int)25 - (int)std::max(0, std::min(24, ui->sliderSmartFee->value()));
        payTxFee = CFeeRate(0);
    } else {
        nTxConfirmTarget = 25;
        payTxFee = CFeeRate(ui->customFee->value());
        fPayAtLeastCustomFee = ui->radioCustomAtLeast->isChecked();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }

    fSendFreeTransactions = ui->checkBoxFreeTx->isChecked();
}

void SendCoinsDialog::updateFeeMinimizedLabel()
{
<<<<<<< HEAD
    if(!model || !model->getOptionsModel())
=======
    if (!model || !model->getOptionsModel())
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return;

    if (ui->radioSmartFee->isChecked())
        ui->labelFeeMinimized->setText(ui->labelSmartFee->text());
    else {
        ui->labelFeeMinimized->setText(BitcoinUnits::formatWithUnit(model->getOptionsModel()->getDisplayUnit(), ui->customFee->value()) +
<<<<<<< HEAD
            ((ui->radioCustomPerKilobyte->isChecked()) ? "/kB" : ""));
=======
                                       ((ui->radioCustomPerKilobyte->isChecked()) ? "/kB" : ""));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }
}

void SendCoinsDialog::updateMinFeeLabel()
{
    if (model && model->getOptionsModel())
<<<<<<< HEAD
        ui->checkBoxMinimumFee->setText(tr("Pay only the required fee of %1").arg(
            BitcoinUnits::formatWithUnit(model->getOptionsModel()->getDisplayUnit(), CWallet::GetRequiredFee(1000)) + "/kB")
        );
=======
        ui->checkBoxMinimumFee->setText(tr("Pay only the minimum fee of %1").arg(BitcoinUnits::formatWithUnit(model->getOptionsModel()->getDisplayUnit(), CWallet::minTxFee.GetFeePerK()) + "/kB"));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

void SendCoinsDialog::updateSmartFeeLabel()
{
<<<<<<< HEAD
    if(!model || !model->getOptionsModel())
        return;

    int nBlocksToConfirm = defaultConfirmTarget - ui->sliderSmartFee->value();
    int estimateFoundAtBlocks = nBlocksToConfirm;
    CFeeRate feeRate = mempool.estimateSmartFee(nBlocksToConfirm, &estimateFoundAtBlocks);
    if (feeRate <= CFeeRate(0)) // not enough data => minfee
    {
        ui->labelSmartFee->setText(BitcoinUnits::formatWithUnit(model->getOptionsModel()->getDisplayUnit(),
                                                                std::max(CWallet::fallbackFee.GetFeePerK(), CWallet::GetRequiredFee(1000))) + "/kB");
        ui->labelSmartFee2->show(); // (Smart fee not initialized yet. This usually takes a few blocks...)
        ui->labelFeeEstimation->setText("");
    }
    else
    {
        ui->labelSmartFee->setText(BitcoinUnits::formatWithUnit(model->getOptionsModel()->getDisplayUnit(),
                                                                std::max(feeRate.GetFeePerK(), CWallet::GetRequiredFee(1000))) + "/kB");
        ui->labelSmartFee2->hide();
        ui->labelFeeEstimation->setText(tr("Estimated to begin confirmation within %n block(s).", "", estimateFoundAtBlocks));
=======
    if (!model || !model->getOptionsModel())
        return;

    int nBlocksToConfirm = (int)25 - (int)std::max(0, std::min(24, ui->sliderSmartFee->value()));
    CFeeRate feeRate = mempool.estimateFee(nBlocksToConfirm);
    if (feeRate <= CFeeRate(0)) // not enough data => minfee
    {
        ui->labelSmartFee->setText(BitcoinUnits::formatWithUnit(model->getOptionsModel()->getDisplayUnit(), CWallet::minTxFee.GetFeePerK()) + "/kB");
        ui->labelSmartFee2->show(); // (Smart fee not initialized yet. This usually takes a few blocks...)
        ui->labelFeeEstimation->setText("");
    } else {
        ui->labelSmartFee->setText(BitcoinUnits::formatWithUnit(model->getOptionsModel()->getDisplayUnit(), feeRate.GetFeePerK()) + "/kB");
        ui->labelSmartFee2->hide();
        ui->labelFeeEstimation->setText(tr("Estimated to begin confirmation within %n block(s).", "", nBlocksToConfirm));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }

    updateFeeMinimizedLabel();
}

<<<<<<< HEAD
=======
// UTXO splitter
void SendCoinsDialog::splitBlockChecked(int state)
{
    if (model) {
        CoinControlDialog::coinControl->fSplitBlock = (state == Qt::Checked);
        fSplitBlock = (state == Qt::Checked);
        ui->splitBlockLineEdit->setEnabled((state == Qt::Checked));
        ui->labelBlockSizeText->setEnabled((state == Qt::Checked));
        ui->labelBlockSize->setEnabled((state == Qt::Checked));
        coinControlUpdateLabels();
    }
}

//UTXO splitter
void SendCoinsDialog::splitBlockLineEditChanged(const QString& text)
{
    //grab the amount in Coin Control AFter Fee field
    QString qAfterFee = ui->labelCoinControlAfterFee->text().left(ui->labelCoinControlAfterFee->text().indexOf(" ")).replace("~", "").simplified().replace(" ", "");

    //convert to CAmount
    CAmount nAfterFee;
    ParseMoney(qAfterFee.toStdString().c_str(), nAfterFee);

    //if greater than 0 then divide after fee by the amount of blocks
    CAmount nSize = nAfterFee;
    int nBlocks = text.toInt();
    if (nAfterFee && nBlocks)
        nSize = nAfterFee / nBlocks;

    //assign to split block dummy, which is used to recalculate the fee amount more outputs
    CoinControlDialog::nSplitBlockDummy = nBlocks;

    //update labels
    ui->labelBlockSize->setText(QString::fromStdString(FormatMoney(nSize)));
    coinControlUpdateLabels();
}

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Coin Control: copy label "Quantity" to clipboard
void SendCoinsDialog::coinControlClipboardQuantity()
{
    GUIUtil::setClipboard(ui->labelCoinControlQuantity->text());
}

// Coin Control: copy label "Amount" to clipboard
void SendCoinsDialog::coinControlClipboardAmount()
{
    GUIUtil::setClipboard(ui->labelCoinControlAmount->text().left(ui->labelCoinControlAmount->text().indexOf(" ")));
}

// Coin Control: copy label "Fee" to clipboard
void SendCoinsDialog::coinControlClipboardFee()
{
<<<<<<< HEAD
    GUIUtil::setClipboard(ui->labelCoinControlFee->text().left(ui->labelCoinControlFee->text().indexOf(" ")).replace(ASYMP_UTF8, ""));
=======
    GUIUtil::setClipboard(ui->labelCoinControlFee->text().left(ui->labelCoinControlFee->text().indexOf(" ")).replace("~", ""));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

// Coin Control: copy label "After fee" to clipboard
void SendCoinsDialog::coinControlClipboardAfterFee()
{
<<<<<<< HEAD
    GUIUtil::setClipboard(ui->labelCoinControlAfterFee->text().left(ui->labelCoinControlAfterFee->text().indexOf(" ")).replace(ASYMP_UTF8, ""));
=======
    GUIUtil::setClipboard(ui->labelCoinControlAfterFee->text().left(ui->labelCoinControlAfterFee->text().indexOf(" ")).replace("~", ""));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

// Coin Control: copy label "Bytes" to clipboard
void SendCoinsDialog::coinControlClipboardBytes()
{
<<<<<<< HEAD
    GUIUtil::setClipboard(ui->labelCoinControlBytes->text().replace(ASYMP_UTF8, ""));
=======
    GUIUtil::setClipboard(ui->labelCoinControlBytes->text().replace("~", ""));
}

// Coin Control: copy label "Priority" to clipboard
void SendCoinsDialog::coinControlClipboardPriority()
{
    GUIUtil::setClipboard(ui->labelCoinControlPriority->text());
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

// Coin Control: copy label "Dust" to clipboard
void SendCoinsDialog::coinControlClipboardLowOutput()
{
    GUIUtil::setClipboard(ui->labelCoinControlLowOutput->text());
}

// Coin Control: copy label "Change" to clipboard
void SendCoinsDialog::coinControlClipboardChange()
{
<<<<<<< HEAD
    GUIUtil::setClipboard(ui->labelCoinControlChange->text().left(ui->labelCoinControlChange->text().indexOf(" ")).replace(ASYMP_UTF8, ""));
=======
    GUIUtil::setClipboard(ui->labelCoinControlChange->text().left(ui->labelCoinControlChange->text().indexOf(" ")).replace("~", ""));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

// Coin Control: settings menu - coin control enabled/disabled by user
void SendCoinsDialog::coinControlFeatureChanged(bool checked)
{
    ui->frameCoinControl->setVisible(checked);

    if (!checked && model) // coin control features disabled
        CoinControlDialog::coinControl->SetNull();

<<<<<<< HEAD
    coinControlUpdateLabels();
=======
    if (checked)
        coinControlUpdateLabels();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

// Coin Control: button inputs -> show actual coin control dialog
void SendCoinsDialog::coinControlButtonClicked()
{
<<<<<<< HEAD
    CoinControlDialog dlg(platformStyle);
=======
    CoinControlDialog dlg;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    dlg.setModel(model);
    dlg.exec();
    coinControlUpdateLabels();
}

// Coin Control: checkbox custom change address
void SendCoinsDialog::coinControlChangeChecked(int state)
{
<<<<<<< HEAD
    if (state == Qt::Unchecked)
    {
        CoinControlDialog::coinControl->destChange = CNoDestination();
        ui->labelCoinControlChangeLabel->clear();
    }
    else
=======
    if (state == Qt::Unchecked) {
        CoinControlDialog::coinControl->destChange = CNoDestination();
        ui->labelCoinControlChangeLabel->clear();
    } else
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        // use this to re-validate an already entered address
        coinControlChangeEdited(ui->lineEditCoinControlChange->text());

    ui->lineEditCoinControlChange->setEnabled((state == Qt::Checked));
}

// Coin Control: custom change address changed
void SendCoinsDialog::coinControlChangeEdited(const QString& text)
{
<<<<<<< HEAD
    if (model && model->getAddressTableModel())
    {
=======
    if (model && model->getAddressTableModel()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        // Default to no change address until verified
        CoinControlDialog::coinControl->destChange = CNoDestination();
        ui->labelCoinControlChangeLabel->setStyleSheet("QLabel{color:red;}");

        CBitcoinAddress addr = CBitcoinAddress(text.toStdString());

        if (text.isEmpty()) // Nothing entered
        {
            ui->labelCoinControlChangeLabel->setText("");
<<<<<<< HEAD
        }
        else if (!addr.IsValid()) // Invalid address
        {
            ui->labelCoinControlChangeLabel->setText(tr("Warning: Invalid GelCoin address"));
        }
        else // Valid address
        {
            CKeyID keyid;
            addr.GetKeyID(keyid);
            if (!model->havePrivKey(keyid)) // Unknown change address
            {
                ui->labelCoinControlChangeLabel->setText(tr("Warning: Unknown change address"));
            }
            else // Known change address
=======
        } else if (!addr.IsValid()) // Invalid address
        {
            ui->labelCoinControlChangeLabel->setText(tr("Warning: Invalid LUX address"));
        } else // Valid address
        {
            CPubKey pubkey;
            CKeyID keyid;
            addr.GetKeyID(keyid);
            if (!model->getPubKey(keyid, pubkey)) // Unknown change address
            {
                ui->labelCoinControlChangeLabel->setText(tr("Warning: Unknown change address"));
            } else // Known change address
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            {
                ui->labelCoinControlChangeLabel->setStyleSheet("QLabel{color:black;}");

                // Query label
                QString associatedLabel = model->getAddressTableModel()->labelForAddress(text);
                if (!associatedLabel.isEmpty())
                    ui->labelCoinControlChangeLabel->setText(associatedLabel);
                else
                    ui->labelCoinControlChangeLabel->setText(tr("(no label)"));

                CoinControlDialog::coinControl->destChange = addr.Get();
            }
        }
    }
}

// Coin Control: update labels
void SendCoinsDialog::coinControlUpdateLabels()
{
<<<<<<< HEAD
    if (!model || !model->getOptionsModel())
        return;

    if (model->getOptionsModel()->getCoinControlFeatures())
    {
        // enable minimum absolute fee UI controls
        ui->radioCustomAtLeast->setVisible(true);

        // only enable the feature if inputs are selected
        ui->radioCustomAtLeast->setEnabled(ui->radioCustomFee->isChecked() && !ui->checkBoxMinimumFee->isChecked() &&CoinControlDialog::coinControl->HasSelected());
    }
    else
    {
        // in case coin control is disabled (=default), hide minimum absolute fee UI controls
        ui->radioCustomAtLeast->setVisible(false);
        return;
    }

    // set pay amounts
    CoinControlDialog::payAmounts.clear();
    CoinControlDialog::fSubtractFeeFromAmount = false;
    for(int i = 0; i < ui->entries->count(); ++i)
    {
        SendCoinsEntry *entry = qobject_cast<SendCoinsEntry*>(ui->entries->itemAt(i)->widget());
        if(entry && !entry->isHidden())
        {
            SendCoinsRecipient rcp = entry->getValue();
            CoinControlDialog::payAmounts.append(rcp.amount);
            if (rcp.fSubtractFeeFromAmount)
                CoinControlDialog::fSubtractFeeFromAmount = true;
        }
    }

    ui->checkUsePrivateSend->setChecked(CoinControlDialog::coinControl->fUsePrivateSend);

    if (CoinControlDialog::coinControl->HasSelected())
    {
=======
    if (!model || !model->getOptionsModel() || !model->getOptionsModel()->getCoinControlFeatures())
        return;

    // set pay amounts
    CoinControlDialog::payAmounts.clear();
    for (int i = 0; i < ui->entries->count(); ++i) {
        SendCoinsEntry* entry = qobject_cast<SendCoinsEntry*>(ui->entries->itemAt(i)->widget());
        if (entry)
            CoinControlDialog::payAmounts.append(entry->getValue().amount);
    }

    ui->checkUseObfuscation->setChecked(CoinControlDialog::coinControl->useObfuscation);

    if (CoinControlDialog::coinControl->HasSelected()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        // actual coin control calculation
        CoinControlDialog::updateLabels(model, this);

        // show coin control stats
        ui->labelCoinControlAutomaticallySelected->hide();
        ui->widgetCoinControl->show();
<<<<<<< HEAD
    }
    else
    {
=======
    } else {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        // hide coin control stats
        ui->labelCoinControlAutomaticallySelected->show();
        ui->widgetCoinControl->hide();
        ui->labelCoinControlInsuffFunds->hide();
    }
}
