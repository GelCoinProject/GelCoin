<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_RECEIVEREQUESTDIALOG_H
#define BITCOIN_QT_RECEIVEREQUESTDIALOG_H

#include "walletmodel.h"

#include <QDialog>
#include <QImage>
#include <QLabel>

class OptionsModel;

<<<<<<< HEAD
namespace Ui {
    class ReceiveRequestDialog;
=======
namespace Ui
{
class ReceiveRequestDialog;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

QT_BEGIN_NAMESPACE
class QMenu;
QT_END_NAMESPACE

/* Label widget for QR code. This image can be dragged, dropped, copied and saved
 * to disk.
 */
class QRImageWidget : public QLabel
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit QRImageWidget(QWidget *parent = 0);
    QImage exportImage();

public Q_SLOTS:
=======
    explicit QRImageWidget(QWidget* parent = 0);
    QImage exportImage();

public slots:
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void saveImage();
    void copyImage();

protected:
<<<<<<< HEAD
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void contextMenuEvent(QContextMenuEvent *event);

private:
    QMenu *contextMenu;
=======
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void contextMenuEvent(QContextMenuEvent* event);

private:
    QMenu* contextMenu;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};

class ReceiveRequestDialog : public QDialog
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit ReceiveRequestDialog(QWidget *parent = 0);
    ~ReceiveRequestDialog();

    void setModel(OptionsModel *model);
    void setInfo(const SendCoinsRecipient &info);

private Q_SLOTS:
=======
    explicit ReceiveRequestDialog(QWidget* parent = 0);
    ~ReceiveRequestDialog();

    void setModel(OptionsModel* model);
    void setInfo(const SendCoinsRecipient& info);

private slots:
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void on_btnCopyURI_clicked();
    void on_btnCopyAddress_clicked();

    void update();

private:
<<<<<<< HEAD
    Ui::ReceiveRequestDialog *ui;
    OptionsModel *model;
=======
    Ui::ReceiveRequestDialog* ui;
    OptionsModel* model;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    SendCoinsRecipient info;
};

#endif // BITCOIN_QT_RECEIVEREQUESTDIALOG_H
