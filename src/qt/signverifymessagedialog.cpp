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

#include "signverifymessagedialog.h"
#include "ui_signverifymessagedialog.h"

#include "addressbookpage.h"
#include "guiutil.h"
<<<<<<< HEAD
#include "platformstyle.h"
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include "walletmodel.h"

#include "base58.h"
#include "init.h"
<<<<<<< HEAD
#include "validation.h" // For strMessageMagic
#include "wallet/wallet.h"
=======
#include "wallet.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

#include <string>
#include <vector>

#include <QClipboard>

<<<<<<< HEAD
SignVerifyMessageDialog::SignVerifyMessageDialog(const PlatformStyle *platformStyle, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignVerifyMessageDialog),
    model(0),
    platformStyle(platformStyle)
=======
SignVerifyMessageDialog::SignVerifyMessageDialog(QWidget* parent) : QDialog(parent),
                                                                    ui(new Ui::SignVerifyMessageDialog),
                                                                    model(0)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    ui->setupUi(this);

#if QT_VERSION >= 0x040700
    ui->signatureOut_SM->setPlaceholderText(tr("Click \"Sign Message\" to generate signature"));
#endif

<<<<<<< HEAD
    QString theme = GUIUtil::getThemeName();

#ifdef Q_OS_MAC // Icons on push buttons are very uncommon on Mac
    ui->signMessageButton_SM->setIcon(QIcon());
    ui->clearButton_SM->setIcon(QIcon());
    ui->verifyMessageButton_VM->setIcon(QIcon());
    ui->clearButton_VM->setIcon(QIcon());
#else
    ui->signMessageButton_SM->setIcon(QIcon(":/icons/" + theme + "/edit"));
    ui->clearButton_SM->setIcon(QIcon(":/icons/" + theme + "/remove"));
    ui->verifyMessageButton_VM->setIcon(QIcon(":/icons/" + theme + "/transaction_0"));
    ui->clearButton_VM->setIcon(QIcon(":/icons/" + theme + "/remove"));
#endif

    // These icons are needed on Mac also
    ui->addressBookButton_SM->setIcon(QIcon(":/icons/" + theme + "/address-book"));
    ui->pasteButton_SM->setIcon(QIcon(":/icons/" + theme + "/editpaste"));
    ui->copySignatureButton_SM->setIcon(QIcon(":/icons/" + theme + "/editcopy"));   
    ui->addressBookButton_VM->setIcon(QIcon(":/icons/" + theme + "/address-book"));

      
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    GUIUtil::setupAddressWidget(ui->addressIn_SM, this);
    GUIUtil::setupAddressWidget(ui->addressIn_VM, this);

    ui->addressIn_SM->installEventFilter(this);
    ui->messageIn_SM->installEventFilter(this);
    ui->signatureOut_SM->installEventFilter(this);
    ui->addressIn_VM->installEventFilter(this);
    ui->messageIn_VM->installEventFilter(this);
    ui->signatureIn_VM->installEventFilter(this);

<<<<<<< HEAD
    ui->signatureOut_SM->setFont(GUIUtil::fixedPitchFont());
    ui->signatureIn_VM->setFont(GUIUtil::fixedPitchFont());
=======
    ui->signatureOut_SM->setFont(GUIUtil::bitcoinAddressFont());
    ui->signatureIn_VM->setFont(GUIUtil::bitcoinAddressFont());
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

SignVerifyMessageDialog::~SignVerifyMessageDialog()
{
    delete ui;
}

<<<<<<< HEAD
void SignVerifyMessageDialog::setModel(WalletModel *model)
=======
void SignVerifyMessageDialog::setModel(WalletModel* model)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    this->model = model;
}

<<<<<<< HEAD
void SignVerifyMessageDialog::setAddress_SM(const QString &address)
=======
void SignVerifyMessageDialog::setAddress_SM(const QString& address)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    ui->addressIn_SM->setText(address);
    ui->messageIn_SM->setFocus();
}

<<<<<<< HEAD
void SignVerifyMessageDialog::setAddress_VM(const QString &address)
=======
void SignVerifyMessageDialog::setAddress_VM(const QString& address)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    ui->addressIn_VM->setText(address);
    ui->messageIn_VM->setFocus();
}

void SignVerifyMessageDialog::showTab_SM(bool fShow)
{
    ui->tabWidget->setCurrentIndex(0);
    if (fShow)
        this->show();
}

void SignVerifyMessageDialog::showTab_VM(bool fShow)
{
    ui->tabWidget->setCurrentIndex(1);
    if (fShow)
        this->show();
}

void SignVerifyMessageDialog::on_addressBookButton_SM_clicked()
{
<<<<<<< HEAD
    if (model && model->getAddressTableModel())
    {
        AddressBookPage dlg(platformStyle, AddressBookPage::ForSelection, AddressBookPage::ReceivingTab, this);
        dlg.setModel(model->getAddressTableModel());
        if (dlg.exec())
        {
=======
    if (model && model->getAddressTableModel()) {
        AddressBookPage dlg(AddressBookPage::ForSelection, AddressBookPage::ReceivingTab, this);
        dlg.setModel(model->getAddressTableModel());
        if (dlg.exec()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            setAddress_SM(dlg.getReturnValue());
        }
    }
}

void SignVerifyMessageDialog::on_pasteButton_SM_clicked()
{
    setAddress_SM(QApplication::clipboard()->text());
}

void SignVerifyMessageDialog::on_signMessageButton_SM_clicked()
{
    if (!model)
        return;

    /* Clear old signature to ensure users don't get confused on error with an old signature displayed */
    ui->signatureOut_SM->clear();

    CBitcoinAddress addr(ui->addressIn_SM->text().toStdString());
<<<<<<< HEAD
    if (!addr.IsValid())
    {
=======
    if (!addr.IsValid()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        ui->statusLabel_SM->setStyleSheet("QLabel { color: red; }");
        ui->statusLabel_SM->setText(tr("The entered address is invalid.") + QString(" ") + tr("Please check the address and try again."));
        return;
    }
    CKeyID keyID;
<<<<<<< HEAD
    if (!addr.GetKeyID(keyID))
    {
=======
    if (!addr.GetKeyID(keyID)) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        ui->addressIn_SM->setValid(false);
        ui->statusLabel_SM->setStyleSheet("QLabel { color: red; }");
        ui->statusLabel_SM->setText(tr("The entered address does not refer to a key.") + QString(" ") + tr("Please check the address and try again."));
        return;
    }

<<<<<<< HEAD
    WalletModel::UnlockContext ctx(model->requestUnlock());
    if (!ctx.isValid())
    {
=======
    WalletModel::UnlockContext ctx(model->requestUnlock(true));
    if (!ctx.isValid()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        ui->statusLabel_SM->setStyleSheet("QLabel { color: red; }");
        ui->statusLabel_SM->setText(tr("Wallet unlock was cancelled."));
        return;
    }

    CKey key;
<<<<<<< HEAD
    if (!pwalletMain->GetKey(keyID, key))
    {
=======
    if (!pwalletMain->GetKey(keyID, key)) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        ui->statusLabel_SM->setStyleSheet("QLabel { color: red; }");
        ui->statusLabel_SM->setText(tr("Private key for the entered address is not available."));
        return;
    }

<<<<<<< HEAD
    CHashWriter ss(SER_GETHASH, 0);
=======
    CDataStream ss(SER_GETHASH, 0);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    ss << strMessageMagic;
    ss << ui->messageIn_SM->document()->toPlainText().toStdString();

    std::vector<unsigned char> vchSig;
<<<<<<< HEAD
    if (!key.SignCompact(ss.GetHash(), vchSig))
    {
=======
    if (!key.SignCompact(Hash(ss.begin(), ss.end()), vchSig)) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        ui->statusLabel_SM->setStyleSheet("QLabel { color: red; }");
        ui->statusLabel_SM->setText(QString("<nobr>") + tr("Message signing failed.") + QString("</nobr>"));
        return;
    }

    ui->statusLabel_SM->setStyleSheet("QLabel { color: green; }");
    ui->statusLabel_SM->setText(QString("<nobr>") + tr("Message signed.") + QString("</nobr>"));

    ui->signatureOut_SM->setText(QString::fromStdString(EncodeBase64(&vchSig[0], vchSig.size())));
}

void SignVerifyMessageDialog::on_copySignatureButton_SM_clicked()
{
    GUIUtil::setClipboard(ui->signatureOut_SM->text());
}

void SignVerifyMessageDialog::on_clearButton_SM_clicked()
{
    ui->addressIn_SM->clear();
    ui->messageIn_SM->clear();
    ui->signatureOut_SM->clear();
    ui->statusLabel_SM->clear();

    ui->addressIn_SM->setFocus();
}

void SignVerifyMessageDialog::on_addressBookButton_VM_clicked()
{
<<<<<<< HEAD
    if (model && model->getAddressTableModel())
    {
        AddressBookPage dlg(platformStyle, AddressBookPage::ForSelection, AddressBookPage::SendingTab, this);
        dlg.setModel(model->getAddressTableModel());
        if (dlg.exec())
        {
=======
    if (model && model->getAddressTableModel()) {
        AddressBookPage dlg(AddressBookPage::ForSelection, AddressBookPage::SendingTab, this);
        dlg.setModel(model->getAddressTableModel());
        if (dlg.exec()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            setAddress_VM(dlg.getReturnValue());
        }
    }
}

void SignVerifyMessageDialog::on_verifyMessageButton_VM_clicked()
{
    CBitcoinAddress addr(ui->addressIn_VM->text().toStdString());
<<<<<<< HEAD
    if (!addr.IsValid())
    {
=======
    if (!addr.IsValid()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        ui->statusLabel_VM->setStyleSheet("QLabel { color: red; }");
        ui->statusLabel_VM->setText(tr("The entered address is invalid.") + QString(" ") + tr("Please check the address and try again."));
        return;
    }
    CKeyID keyID;
<<<<<<< HEAD
    if (!addr.GetKeyID(keyID))
    {
=======
    if (!addr.GetKeyID(keyID)) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        ui->addressIn_VM->setValid(false);
        ui->statusLabel_VM->setStyleSheet("QLabel { color: red; }");
        ui->statusLabel_VM->setText(tr("The entered address does not refer to a key.") + QString(" ") + tr("Please check the address and try again."));
        return;
    }

    bool fInvalid = false;
    std::vector<unsigned char> vchSig = DecodeBase64(ui->signatureIn_VM->text().toStdString().c_str(), &fInvalid);

<<<<<<< HEAD
    if (fInvalid)
    {
=======
    if (fInvalid) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        ui->signatureIn_VM->setValid(false);
        ui->statusLabel_VM->setStyleSheet("QLabel { color: red; }");
        ui->statusLabel_VM->setText(tr("The signature could not be decoded.") + QString(" ") + tr("Please check the signature and try again."));
        return;
    }

<<<<<<< HEAD
    CHashWriter ss(SER_GETHASH, 0);
=======
    CDataStream ss(SER_GETHASH, 0);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    ss << strMessageMagic;
    ss << ui->messageIn_VM->document()->toPlainText().toStdString();

    CPubKey pubkey;
<<<<<<< HEAD
    if (!pubkey.RecoverCompact(ss.GetHash(), vchSig))
    {
=======
    if (!pubkey.RecoverCompact(Hash(ss.begin(), ss.end()), vchSig)) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        ui->signatureIn_VM->setValid(false);
        ui->statusLabel_VM->setStyleSheet("QLabel { color: red; }");
        ui->statusLabel_VM->setText(tr("The signature did not match the message digest.") + QString(" ") + tr("Please check the signature and try again."));
        return;
    }

<<<<<<< HEAD
    if (!(CBitcoinAddress(pubkey.GetID()) == addr))
    {
=======
    if (!(CBitcoinAddress(pubkey.GetID()) == addr)) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        ui->statusLabel_VM->setStyleSheet("QLabel { color: red; }");
        ui->statusLabel_VM->setText(QString("<nobr>") + tr("Message verification failed.") + QString("</nobr>"));
        return;
    }

    ui->statusLabel_VM->setStyleSheet("QLabel { color: green; }");
    ui->statusLabel_VM->setText(QString("<nobr>") + tr("Message verified.") + QString("</nobr>"));
}

void SignVerifyMessageDialog::on_clearButton_VM_clicked()
{
    ui->addressIn_VM->clear();
    ui->signatureIn_VM->clear();
    ui->messageIn_VM->clear();
    ui->statusLabel_VM->clear();

    ui->addressIn_VM->setFocus();
}

<<<<<<< HEAD
bool SignVerifyMessageDialog::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::FocusIn)
    {
        if (ui->tabWidget->currentIndex() == 0)
        {
=======
bool SignVerifyMessageDialog::eventFilter(QObject* object, QEvent* event)
{
    if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::FocusIn) {
        if (ui->tabWidget->currentIndex() == 0) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            /* Clear status message on focus change */
            ui->statusLabel_SM->clear();

            /* Select generated signature */
<<<<<<< HEAD
            if (object == ui->signatureOut_SM)
            {
                ui->signatureOut_SM->selectAll();
                return true;
            }
        }
        else if (ui->tabWidget->currentIndex() == 1)
        {
=======
            if (object == ui->signatureOut_SM) {
                ui->signatureOut_SM->selectAll();
                return true;
            }
        } else if (ui->tabWidget->currentIndex() == 1) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            /* Clear status message on focus change */
            ui->statusLabel_VM->clear();
        }
    }
    return QDialog::eventFilter(object, event);
}
