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

#include "openuridialog.h"
#include "ui_openuridialog.h"

#include "guiutil.h"
#include "walletmodel.h"

#include <QUrl>

<<<<<<< HEAD
OpenURIDialog::OpenURIDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenURIDialog)
{
    ui->setupUi(this);
#if QT_VERSION >= 0x040700
    ui->uriEdit->setPlaceholderText("gelcoin:");
=======
OpenURIDialog::OpenURIDialog(QWidget* parent) : QDialog(parent),
                                                ui(new Ui::OpenURIDialog)
{
    ui->setupUi(this);
#if QT_VERSION >= 0x040700
    ui->uriEdit->setPlaceholderText("lux:");
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#endif
}

OpenURIDialog::~OpenURIDialog()
{
    delete ui;
}

QString OpenURIDialog::getURI()
{
    return ui->uriEdit->text();
}

void OpenURIDialog::accept()
{
    SendCoinsRecipient rcp;
<<<<<<< HEAD
    if(GUIUtil::parseBitcoinURI(getURI(), &rcp))
    {
=======
    if (GUIUtil::parseBitcoinURI(getURI(), &rcp)) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        /* Only accept value URIs */
        QDialog::accept();
    } else {
        ui->uriEdit->setValid(false);
    }
}

void OpenURIDialog::on_selectFileButton_clicked()
{
    QString filename = GUIUtil::getOpenFileName(this, tr("Select payment request file to open"), "", "", NULL);
<<<<<<< HEAD
    if(filename.isEmpty())
        return;
    QUrl fileUri = QUrl::fromLocalFile(filename);
    ui->uriEdit->setText("gelcoin:?r=" + QUrl::toPercentEncoding(fileUri.toString()));
=======
    if (filename.isEmpty())
        return;
    QUrl fileUri = QUrl::fromLocalFile(filename);
    ui->uriEdit->setText("lux:?r=" + QUrl::toPercentEncoding(fileUri.toString()));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}
