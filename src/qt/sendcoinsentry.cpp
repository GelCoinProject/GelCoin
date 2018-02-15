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

#include "sendcoinsentry.h"
#include "ui_sendcoinsentry.h"

#include "addressbookpage.h"
#include "addresstablemodel.h"
#include "guiutil.h"
#include "optionsmodel.h"
<<<<<<< HEAD
#include "platformstyle.h"
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include "walletmodel.h"

#include <QApplication>
#include <QClipboard>

<<<<<<< HEAD
SendCoinsEntry::SendCoinsEntry(const PlatformStyle *platformStyle, QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::SendCoinsEntry),
    model(0),
    platformStyle(platformStyle)
=======
SendCoinsEntry::SendCoinsEntry(QWidget* parent) : QStackedWidget(parent),
                                                  ui(new Ui::SendCoinsEntry),
                                                  model(0)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    ui->setupUi(this);

    setCurrentWidget(ui->SendCoins);

<<<<<<< HEAD
    if (platformStyle->getUseExtraSpacing())
        ui->payToLayout->setSpacing(4);
=======
#ifdef Q_OS_MAC
    ui->payToLayout->setSpacing(4);
#endif
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#if QT_VERSION >= 0x040700
    ui->addAsLabel->setPlaceholderText(tr("Enter a label for this address to add it to your address book"));
#endif

<<<<<<< HEAD
    QString theme = GUIUtil::getThemeName();

    // These icons are needed on Mac also!
    ui->addressBookButton->setIcon(QIcon(":/icons/" + theme + "/address-book"));
    ui->pasteButton->setIcon(QIcon(":/icons/" + theme + "/editpaste"));
    ui->deleteButton->setIcon(QIcon(":/icons/" + theme + "/remove"));
    ui->deleteButton_is->setIcon(QIcon(":/icons/" + theme + "/remove"));
    ui->deleteButton_s->setIcon(QIcon(":/icons/" + theme + "/remove"));
      
    // normal gelcoin address field
    GUIUtil::setupAddressWidget(ui->payTo, this);
    // just a label for displaying gelcoin address(es)
    ui->payTo_is->setFont(GUIUtil::fixedPitchFont());

    // Connect signals
    connect(ui->payAmount, SIGNAL(valueChanged()), this, SIGNAL(payAmountChanged()));
    connect(ui->checkboxSubtractFeeFromAmount, SIGNAL(toggled(bool)), this, SIGNAL(subtractFeeFromAmountChanged()));
=======
    // normal lux address field
    GUIUtil::setupAddressWidget(ui->payTo, this);
    // just a label for displaying lux address(es)
    ui->payTo_is->setFont(GUIUtil::bitcoinAddressFont());

    // Connect signals
    connect(ui->payAmount, SIGNAL(valueChanged()), this, SIGNAL(payAmountChanged()));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));
    connect(ui->deleteButton_is, SIGNAL(clicked()), this, SLOT(deleteClicked()));
    connect(ui->deleteButton_s, SIGNAL(clicked()), this, SLOT(deleteClicked()));
}

SendCoinsEntry::~SendCoinsEntry()
{
    delete ui;
}

void SendCoinsEntry::on_pasteButton_clicked()
{
    // Paste text from clipboard into recipient field
    ui->payTo->setText(QApplication::clipboard()->text());
}

void SendCoinsEntry::on_addressBookButton_clicked()
{
<<<<<<< HEAD
    if(!model)
        return;
    AddressBookPage dlg(platformStyle, AddressBookPage::ForSelection, AddressBookPage::SendingTab, this);
    dlg.setModel(model->getAddressTableModel());
    if(dlg.exec())
    {
=======
    if (!model)
        return;
    AddressBookPage dlg(AddressBookPage::ForSelection, AddressBookPage::SendingTab, this);
    dlg.setModel(model->getAddressTableModel());
    if (dlg.exec()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        ui->payTo->setText(dlg.getReturnValue());
        ui->payAmount->setFocus();
    }
}

<<<<<<< HEAD
void SendCoinsEntry::on_payTo_textChanged(const QString &address)
=======
void SendCoinsEntry::on_payTo_textChanged(const QString& address)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    updateLabel(address);
}

<<<<<<< HEAD
void SendCoinsEntry::setModel(WalletModel *model)
=======
void SendCoinsEntry::setModel(WalletModel* model)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    this->model = model;

    if (model && model->getOptionsModel())
        connect(model->getOptionsModel(), SIGNAL(displayUnitChanged(int)), this, SLOT(updateDisplayUnit()));

    clear();
}

void SendCoinsEntry::clear()
{
    // clear UI elements for normal payment
    ui->payTo->clear();
    ui->addAsLabel->clear();
    ui->payAmount->clear();
<<<<<<< HEAD
    ui->checkboxSubtractFeeFromAmount->setCheckState(Qt::Unchecked);
    ui->messageTextLabel->clear();
    ui->messageTextLabel->hide();
    ui->messageLabel->hide();
    // clear UI elements for unauthenticated payment request
    ui->payTo_is->clear();
    ui->memoTextLabel_is->clear();
    ui->payAmount_is->clear();
    // clear UI elements for authenticated payment request
=======
    ui->messageTextLabel->clear();
    ui->messageTextLabel->hide();
    ui->messageLabel->hide();
    // clear UI elements for insecure payment request
    ui->payTo_is->clear();
    ui->memoTextLabel_is->clear();
    ui->payAmount_is->clear();
    // clear UI elements for secure payment request
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    ui->payTo_s->clear();
    ui->memoTextLabel_s->clear();
    ui->payAmount_s->clear();

    // update the display unit, to not use the default ("BTC")
    updateDisplayUnit();
}

void SendCoinsEntry::deleteClicked()
{
<<<<<<< HEAD
    Q_EMIT removeEntry(this);
=======
    emit removeEntry(this);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

bool SendCoinsEntry::validate()
{
    if (!model)
        return false;

    // Check input validity
    bool retval = true;

    // Skip checks for payment request
    if (recipient.paymentRequest.IsInitialized())
        return retval;

<<<<<<< HEAD
    if (!model->validateAddress(ui->payTo->text()))
    {
=======
    if (!model->validateAddress(ui->payTo->text())) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        ui->payTo->setValid(false);
        retval = false;
    }

<<<<<<< HEAD
    if (!ui->payAmount->validate())
    {
=======
    if (!ui->payAmount->validate()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        retval = false;
    }

    // Sending a zero amount is invalid
<<<<<<< HEAD
    if (ui->payAmount->value(0) <= 0)
    {
=======
    if (ui->payAmount->value(0) <= 0) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        ui->payAmount->setValid(false);
        retval = false;
    }

    // Reject dust outputs:
    if (retval && GUIUtil::isDust(ui->payTo->text(), ui->payAmount->value())) {
        ui->payAmount->setValid(false);
        retval = false;
    }

    return retval;
}

SendCoinsRecipient SendCoinsEntry::getValue()
{
    // Payment request
    if (recipient.paymentRequest.IsInitialized())
        return recipient;

    // Normal payment
    recipient.address = ui->payTo->text();
    recipient.label = ui->addAsLabel->text();
    recipient.amount = ui->payAmount->value();
    recipient.message = ui->messageTextLabel->text();
<<<<<<< HEAD
    recipient.fSubtractFeeFromAmount = (ui->checkboxSubtractFeeFromAmount->checkState() == Qt::Checked);
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    return recipient;
}

<<<<<<< HEAD
QWidget *SendCoinsEntry::setupTabChain(QWidget *prev)
{
    QWidget::setTabOrder(prev, ui->payTo);
    QWidget::setTabOrder(ui->payTo, ui->addAsLabel);
    QWidget *w = ui->payAmount->setupTabChain(ui->addAsLabel);
    QWidget::setTabOrder(w, ui->checkboxSubtractFeeFromAmount);
    QWidget::setTabOrder(ui->checkboxSubtractFeeFromAmount, ui->addressBookButton);
=======
QWidget* SendCoinsEntry::setupTabChain(QWidget* prev)
{
    QWidget::setTabOrder(prev, ui->payTo);
    QWidget::setTabOrder(ui->payTo, ui->addAsLabel);
    QWidget* w = ui->payAmount->setupTabChain(ui->addAsLabel);
    QWidget::setTabOrder(w, ui->addressBookButton);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    QWidget::setTabOrder(ui->addressBookButton, ui->pasteButton);
    QWidget::setTabOrder(ui->pasteButton, ui->deleteButton);
    return ui->deleteButton;
}

<<<<<<< HEAD
void SendCoinsEntry::setValue(const SendCoinsRecipient &value)
=======
void SendCoinsEntry::setValue(const SendCoinsRecipient& value)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    recipient = value;

    if (recipient.paymentRequest.IsInitialized()) // payment request
    {
<<<<<<< HEAD
        if (recipient.authenticatedMerchant.isEmpty()) // unauthenticated
=======
        if (recipient.authenticatedMerchant.isEmpty()) // insecure
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        {
            ui->payTo_is->setText(recipient.address);
            ui->memoTextLabel_is->setText(recipient.message);
            ui->payAmount_is->setValue(recipient.amount);
            ui->payAmount_is->setReadOnly(true);
<<<<<<< HEAD
            setCurrentWidget(ui->SendCoins_UnauthenticatedPaymentRequest);
        }
        else // authenticated
=======
            setCurrentWidget(ui->SendCoins_InsecurePaymentRequest);
        } else // secure
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        {
            ui->payTo_s->setText(recipient.authenticatedMerchant);
            ui->memoTextLabel_s->setText(recipient.message);
            ui->payAmount_s->setValue(recipient.amount);
            ui->payAmount_s->setReadOnly(true);
<<<<<<< HEAD
            setCurrentWidget(ui->SendCoins_AuthenticatedPaymentRequest);
        }
    }
    else // normal payment
=======
            setCurrentWidget(ui->SendCoins_SecurePaymentRequest);
        }
    } else // normal payment
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    {
        // message
        ui->messageTextLabel->setText(recipient.message);
        ui->messageTextLabel->setVisible(!recipient.message.isEmpty());
        ui->messageLabel->setVisible(!recipient.message.isEmpty());

        ui->addAsLabel->clear();
        ui->payTo->setText(recipient.address); // this may set a label from addressbook
<<<<<<< HEAD
        if (!recipient.label.isEmpty()) // if a label had been set from the addressbook, don't overwrite with an empty label
=======
        if (!recipient.label.isEmpty())        // if a label had been set from the addressbook, dont overwrite with an empty label
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            ui->addAsLabel->setText(recipient.label);
        ui->payAmount->setValue(recipient.amount);
    }
}

<<<<<<< HEAD
void SendCoinsEntry::setAddress(const QString &address)
=======
void SendCoinsEntry::setAddress(const QString& address)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    ui->payTo->setText(address);
    ui->payAmount->setFocus();
}

bool SendCoinsEntry::isClear()
{
    return ui->payTo->text().isEmpty() && ui->payTo_is->text().isEmpty() && ui->payTo_s->text().isEmpty();
}

void SendCoinsEntry::setFocus()
{
    ui->payTo->setFocus();
}

void SendCoinsEntry::updateDisplayUnit()
{
<<<<<<< HEAD
    if(model && model->getOptionsModel())
    {
=======
    if (model && model->getOptionsModel()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        // Update payAmount with the current unit
        ui->payAmount->setDisplayUnit(model->getOptionsModel()->getDisplayUnit());
        ui->payAmount_is->setDisplayUnit(model->getOptionsModel()->getDisplayUnit());
        ui->payAmount_s->setDisplayUnit(model->getOptionsModel()->getDisplayUnit());
    }
}

<<<<<<< HEAD
bool SendCoinsEntry::updateLabel(const QString &address)
{
    if(!model)
=======
bool SendCoinsEntry::updateLabel(const QString& address)
{
    if (!model)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return false;

    // Fill in label from address book, if address has an associated label
    QString associatedLabel = model->getAddressTableModel()->labelForAddress(address);
<<<<<<< HEAD
    if(!associatedLabel.isEmpty())
    {
=======
    if (!associatedLabel.isEmpty()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        ui->addAsLabel->setText(associatedLabel);
        return true;
    }

    return false;
}
