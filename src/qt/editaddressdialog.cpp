<<<<<<< HEAD
// Copyright (c) 2011-2013 The Bitcoin Core developers
// Copyright (c) 2014-2017 The GelCoin developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The LUX developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "editaddressdialog.h"
#include "ui_editaddressdialog.h"

#include "addresstablemodel.h"
#include "guiutil.h"

#include <QDataWidgetMapper>
#include <QMessageBox>

<<<<<<< HEAD
EditAddressDialog::EditAddressDialog(Mode mode, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditAddressDialog),
    mapper(0),
    mode(mode),
    model(0)
=======
EditAddressDialog::EditAddressDialog(Mode mode, QWidget* parent) : QDialog(parent),
                                                                   ui(new Ui::EditAddressDialog),
                                                                   mapper(0),
                                                                   mode(mode),
                                                                   model(0)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    ui->setupUi(this);

    GUIUtil::setupAddressWidget(ui->addressEdit, this);

<<<<<<< HEAD
    switch(mode)
    {
=======
    switch (mode) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    case NewReceivingAddress:
        setWindowTitle(tr("New receiving address"));
        ui->addressEdit->setEnabled(false);
        break;
    case NewSendingAddress:
        setWindowTitle(tr("New sending address"));
        break;
    case EditReceivingAddress:
        setWindowTitle(tr("Edit receiving address"));
        ui->addressEdit->setEnabled(false);
        break;
    case EditSendingAddress:
        setWindowTitle(tr("Edit sending address"));
        break;
    }

    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

EditAddressDialog::~EditAddressDialog()
{
    delete ui;
}

<<<<<<< HEAD
void EditAddressDialog::setModel(AddressTableModel *model)
{
    this->model = model;
    if(!model)
=======
void EditAddressDialog::setModel(AddressTableModel* model)
{
    this->model = model;
    if (!model)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return;

    mapper->setModel(model);
    mapper->addMapping(ui->labelEdit, AddressTableModel::Label);
    mapper->addMapping(ui->addressEdit, AddressTableModel::Address);
}

void EditAddressDialog::loadRow(int row)
{
    mapper->setCurrentIndex(row);
}

bool EditAddressDialog::saveCurrentRow()
{
<<<<<<< HEAD
    if(!model)
        return false;

    switch(mode)
    {
    case NewReceivingAddress:
    case NewSendingAddress:
        address = model->addRow(
                mode == NewSendingAddress ? AddressTableModel::Send : AddressTableModel::Receive,
                ui->labelEdit->text(),
                ui->addressEdit->text());
        break;
    case EditReceivingAddress:
    case EditSendingAddress:
        if(mapper->submit())
        {
=======
    if (!model)
        return false;

    switch (mode) {
    case NewReceivingAddress:
    case NewSendingAddress:
        address = model->addRow(
            mode == NewSendingAddress ? AddressTableModel::Send : AddressTableModel::Receive,
            ui->labelEdit->text(),
            ui->addressEdit->text());
        break;
    case EditReceivingAddress:
    case EditSendingAddress:
        if (mapper->submit()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            address = ui->addressEdit->text();
        }
        break;
    }
    return !address.isEmpty();
}

void EditAddressDialog::accept()
{
<<<<<<< HEAD
    if(!model)
        return;

    if(!saveCurrentRow())
    {
        switch(model->getEditStatus())
        {
=======
    if (!model)
        return;

    if (!saveCurrentRow()) {
        switch (model->getEditStatus()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        case AddressTableModel::OK:
            // Failed with unknown reason. Just reject.
            break;
        case AddressTableModel::NO_CHANGES:
            // No changes were made during edit operation. Just reject.
            break;
        case AddressTableModel::INVALID_ADDRESS:
            QMessageBox::warning(this, windowTitle(),
<<<<<<< HEAD
                tr("The entered address \"%1\" is not a valid GelCoin address.").arg(ui->addressEdit->text()),
=======
                tr("The entered address \"%1\" is not a valid LUX address.").arg(ui->addressEdit->text()),
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                QMessageBox::Ok, QMessageBox::Ok);
            break;
        case AddressTableModel::DUPLICATE_ADDRESS:
            QMessageBox::warning(this, windowTitle(),
                tr("The entered address \"%1\" is already in the address book.").arg(ui->addressEdit->text()),
                QMessageBox::Ok, QMessageBox::Ok);
            break;
        case AddressTableModel::WALLET_UNLOCK_FAILURE:
            QMessageBox::critical(this, windowTitle(),
                tr("Could not unlock wallet."),
                QMessageBox::Ok, QMessageBox::Ok);
            break;
        case AddressTableModel::KEY_GENERATION_FAILURE:
            QMessageBox::critical(this, windowTitle(),
                tr("New key generation failed."),
                QMessageBox::Ok, QMessageBox::Ok);
            break;
<<<<<<< HEAD

=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        }
        return;
    }
    QDialog::accept();
}

QString EditAddressDialog::getAddress() const
{
    return address;
}

<<<<<<< HEAD
void EditAddressDialog::setAddress(const QString &address)
=======
void EditAddressDialog::setAddress(const QString& address)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    this->address = address;
    ui->addressEdit->setText(address);
}
