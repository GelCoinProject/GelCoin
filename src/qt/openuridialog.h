<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_OPENURIDIALOG_H
#define BITCOIN_QT_OPENURIDIALOG_H

#include <QDialog>

<<<<<<< HEAD
namespace Ui {
    class OpenURIDialog;
=======
namespace Ui
{
class OpenURIDialog;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

class OpenURIDialog : public QDialog
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit OpenURIDialog(QWidget *parent);
=======
    explicit OpenURIDialog(QWidget* parent);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    ~OpenURIDialog();

    QString getURI();

<<<<<<< HEAD
protected Q_SLOTS:
    void accept();

private Q_SLOTS:
    void on_selectFileButton_clicked();

private:
    Ui::OpenURIDialog *ui;
=======
protected slots:
    void accept();

private slots:
    void on_selectFileButton_clicked();

private:
    Ui::OpenURIDialog* ui;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};

#endif // BITCOIN_QT_OPENURIDIALOG_H
