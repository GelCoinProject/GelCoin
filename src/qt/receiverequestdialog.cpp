<<<<<<< HEAD
// Copyright (c) 2011-2013 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "receiverequestdialog.h"
#include "ui_receiverequestdialog.h"

#include "bitcoinunits.h"
#include "guiconstants.h"
#include "guiutil.h"
#include "optionsmodel.h"
#include "walletmodel.h"

#include <QClipboard>
#include <QDrag>
#include <QMenu>
#include <QMimeData>
#include <QMouseEvent>
#include <QPixmap>
#if QT_VERSION < 0x050000
#include <QUrl>
#endif

#if defined(HAVE_CONFIG_H)
<<<<<<< HEAD
#include "config/gelcoin-config.h" /* for USE_QRCODE */
=======
#include "config/lux-config.h" /* for USE_QRCODE */
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#endif

#ifdef USE_QRCODE
#include <qrencode.h>
#endif

<<<<<<< HEAD
QRImageWidget::QRImageWidget(QWidget *parent):
    QLabel(parent), contextMenu(0)
{
    contextMenu = new QMenu(this);
    QAction *saveImageAction = new QAction(tr("&Save Image..."), this);
    connect(saveImageAction, SIGNAL(triggered()), this, SLOT(saveImage()));
    contextMenu->addAction(saveImageAction);
    QAction *copyImageAction = new QAction(tr("&Copy Image"), this);
=======
QRImageWidget::QRImageWidget(QWidget* parent) : QLabel(parent), contextMenu(0)
{
    contextMenu = new QMenu();
    QAction* saveImageAction = new QAction(tr("&Save Image..."), this);
    connect(saveImageAction, SIGNAL(triggered()), this, SLOT(saveImage()));
    contextMenu->addAction(saveImageAction);
    QAction* copyImageAction = new QAction(tr("&Copy Image"), this);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    connect(copyImageAction, SIGNAL(triggered()), this, SLOT(copyImage()));
    contextMenu->addAction(copyImageAction);
}

QImage QRImageWidget::exportImage()
{
<<<<<<< HEAD
    if(!pixmap())
=======
    if (!pixmap())
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return QImage();
    return pixmap()->toImage().scaled(EXPORT_IMAGE_SIZE, EXPORT_IMAGE_SIZE);
}

<<<<<<< HEAD
void QRImageWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && pixmap())
    {
        event->accept();
        QMimeData *mimeData = new QMimeData;
        mimeData->setImageData(exportImage());

        QDrag *drag = new QDrag(this);
=======
void QRImageWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && pixmap()) {
        event->accept();
        QMimeData* mimeData = new QMimeData;
        mimeData->setImageData(exportImage());

        QDrag* drag = new QDrag(this);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        drag->setMimeData(mimeData);
        drag->exec();
    } else {
        QLabel::mousePressEvent(event);
    }
}

void QRImageWidget::saveImage()
{
<<<<<<< HEAD
    if(!pixmap())
        return;
    QString fn = GUIUtil::getSaveFileName(this, tr("Save QR Code"), QString(), tr("PNG Image (*.png)"), NULL);
    if (!fn.isEmpty())
    {
=======
    if (!pixmap())
        return;
    QString fn = GUIUtil::getSaveFileName(this, tr("Save QR Code"), QString(), tr("PNG Image (*.png)"), NULL);
    if (!fn.isEmpty()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        exportImage().save(fn);
    }
}

void QRImageWidget::copyImage()
{
<<<<<<< HEAD
    if(!pixmap())
=======
    if (!pixmap())
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return;
    QApplication::clipboard()->setImage(exportImage());
}

<<<<<<< HEAD
void QRImageWidget::contextMenuEvent(QContextMenuEvent *event)
{
    if(!pixmap())
=======
void QRImageWidget::contextMenuEvent(QContextMenuEvent* event)
{
    if (!pixmap())
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return;
    contextMenu->exec(event->globalPos());
}

<<<<<<< HEAD
ReceiveRequestDialog::ReceiveRequestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReceiveRequestDialog),
    model(0)
=======
ReceiveRequestDialog::ReceiveRequestDialog(QWidget* parent) : QDialog(parent),
                                                              ui(new Ui::ReceiveRequestDialog),
                                                              model(0)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    ui->setupUi(this);

#ifndef USE_QRCODE
    ui->btnSaveAs->setVisible(false);
    ui->lblQRCode->setVisible(false);
#endif

    connect(ui->btnSaveAs, SIGNAL(clicked()), ui->lblQRCode, SLOT(saveImage()));
}

ReceiveRequestDialog::~ReceiveRequestDialog()
{
    delete ui;
}

<<<<<<< HEAD
void ReceiveRequestDialog::setModel(OptionsModel *model)
=======
void ReceiveRequestDialog::setModel(OptionsModel* model)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    this->model = model;

    if (model)
        connect(model, SIGNAL(displayUnitChanged(int)), this, SLOT(update()));

    // update the display unit if necessary
    update();
}

<<<<<<< HEAD
void ReceiveRequestDialog::setInfo(const SendCoinsRecipient &info)
=======
void ReceiveRequestDialog::setInfo(const SendCoinsRecipient& info)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    this->info = info;
    update();
}

void ReceiveRequestDialog::update()
{
<<<<<<< HEAD
    if(!model)
        return;
    QString target = info.label;
    if(target.isEmpty())
=======
    if (!model)
        return;
    QString target = info.label;
    if (target.isEmpty())
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        target = info.address;
    setWindowTitle(tr("Request payment to %1").arg(target));

    QString uri = GUIUtil::formatBitcoinURI(info);
    ui->btnSaveAs->setEnabled(false);
    QString html;
    html += "<html><font face='verdana, arial, helvetica, sans-serif'>";
<<<<<<< HEAD
    html += "<b>"+tr("Payment information")+"</b><br>";
    html += "<b>"+tr("URI")+"</b>: ";
    html += "<a href=\""+uri+"\">" + GUIUtil::HtmlEscape(uri) + "</a><br>";
    html += "<b>"+tr("Address")+"</b>: " + GUIUtil::HtmlEscape(info.address) + "<br>";
    if(info.amount)
        html += "<b>"+tr("Amount")+"</b>: " + BitcoinUnits::formatHtmlWithUnit(model->getDisplayUnit(), info.amount) + "<br>";
    if(!info.label.isEmpty())
        html += "<b>"+tr("Label")+"</b>: " + GUIUtil::HtmlEscape(info.label) + "<br>";
    if(!info.message.isEmpty())
        html += "<b>"+tr("Message")+"</b>: " + GUIUtil::HtmlEscape(info.message) + "<br>";
    html += "<b>"+tr("InstantSend")+"</b>: " + (info.fUseInstantSend ? tr("Yes") : tr("No")) + "<br>";
=======
    html += "<b>" + tr("Payment information") + "</b><br>";
    html += "<b>" + tr("URI") + "</b>: ";
    html += "<a style=\"color:#5B4C7C;\" href=\"" + uri + "\">" + GUIUtil::HtmlEscape(uri) + "</a><br>";
    html += "<b>" + tr("Address") + "</b>: " + GUIUtil::HtmlEscape(info.address) + "<br>";
    if (info.amount)
        html += "<b>" + tr("Amount") + "</b>: " + BitcoinUnits::formatWithUnit(model->getDisplayUnit(), info.amount) + "<br>";
    if (!info.label.isEmpty())
        html += "<b>" + tr("Label") + "</b>: " + GUIUtil::HtmlEscape(info.label) + "<br>";
    if (!info.message.isEmpty())
        html += "<b>" + tr("Message") + "</b>: " + GUIUtil::HtmlEscape(info.message) + "<br>";
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    ui->outUri->setText(html);

#ifdef USE_QRCODE
    ui->lblQRCode->setText("");
<<<<<<< HEAD
    if(!uri.isEmpty())
    {
        // limit URI length
        if (uri.length() > MAX_URI_LENGTH)
        {
            ui->lblQRCode->setText(tr("Resulting URI too long, try to reduce the text for label / message."));
        } else {
            QRcode *code = QRcode_encodeString(uri.toUtf8().constData(), 0, QR_ECLEVEL_L, QR_MODE_8, 1);
            if (!code)
            {
=======
    if (!uri.isEmpty()) {
        // limit URI length
        if (uri.length() > MAX_URI_LENGTH) {
            ui->lblQRCode->setText(tr("Resulting URI too long, try to reduce the text for label / message."));
        } else {
            QRcode* code = QRcode_encodeString(uri.toUtf8().constData(), 0, QR_ECLEVEL_L, QR_MODE_8, 1);
            if (!code) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                ui->lblQRCode->setText(tr("Error encoding URI into QR Code."));
                return;
            }
            QImage myImage = QImage(code->width + 8, code->width + 8, QImage::Format_RGB32);
            myImage.fill(0xffffff);
<<<<<<< HEAD
            unsigned char *p = code->data;
            for (int y = 0; y < code->width; y++)
            {
                for (int x = 0; x < code->width; x++)
                {
=======
            unsigned char* p = code->data;
            for (int y = 0; y < code->width; y++) {
                for (int x = 0; x < code->width; x++) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                    myImage.setPixel(x + 4, y + 4, ((*p & 1) ? 0x0 : 0xffffff));
                    p++;
                }
            }
            QRcode_free(code);

            ui->lblQRCode->setPixmap(QPixmap::fromImage(myImage).scaled(300, 300));
            ui->btnSaveAs->setEnabled(true);
        }
    }
#endif
}

void ReceiveRequestDialog::on_btnCopyURI_clicked()
{
    GUIUtil::setClipboard(GUIUtil::formatBitcoinURI(info));
}

void ReceiveRequestDialog::on_btnCopyAddress_clicked()
{
    GUIUtil::setClipboard(info.address);
}
