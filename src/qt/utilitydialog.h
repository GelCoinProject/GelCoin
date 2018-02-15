<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_UTILITYDIALOG_H
#define BITCOIN_QT_UTILITYDIALOG_H

#include <QDialog>
#include <QObject>

class BitcoinGUI;
class ClientModel;

<<<<<<< HEAD
namespace Ui {
    class HelpMessageDialog;
=======
namespace Ui
{
class HelpMessageDialog;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

/** "Help message" dialog box */
class HelpMessageDialog : public QDialog
{
    Q_OBJECT

public:
<<<<<<< HEAD
    enum HelpMode {
        about,
        cmdline,
        pshelp
    };

    explicit HelpMessageDialog(QWidget *parent, HelpMode helpMode);
=======
    explicit HelpMessageDialog(QWidget* parent, bool about);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    ~HelpMessageDialog();

    void printToConsole();
    void showOrPrint();

private:
<<<<<<< HEAD
    Ui::HelpMessageDialog *ui;
    QString text;

private Q_SLOTS:
=======
    Ui::HelpMessageDialog* ui;
    QString text;

private slots:
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void on_okButton_accepted();
};


/** "Shutdown" window */
class ShutdownWindow : public QWidget
{
    Q_OBJECT

public:
<<<<<<< HEAD
    ShutdownWindow(QWidget *parent=0, Qt::WindowFlags f=0);
    static QWidget *showShutdownWindow(BitcoinGUI *window);

protected:
    void closeEvent(QCloseEvent *event);
=======
    ShutdownWindow(QWidget* parent = 0, Qt::WindowFlags f = 0);
    static void showShutdownWindow(BitcoinGUI* window);

protected:
    void closeEvent(QCloseEvent* event);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};

#endif // BITCOIN_QT_UTILITYDIALOG_H
