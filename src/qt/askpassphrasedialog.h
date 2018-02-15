<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_ASKPASSPHRASEDIALOG_H
#define BITCOIN_QT_ASKPASSPHRASEDIALOG_H

#include <QDialog>

class WalletModel;

<<<<<<< HEAD
namespace Ui {
    class AskPassphraseDialog;
=======
namespace Ui
{
class AskPassphraseDialog;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

/** Multifunctional dialog to ask for passphrases. Used for encryption, unlocking, and changing the passphrase.
 */
class AskPassphraseDialog : public QDialog
{
    Q_OBJECT

public:
    enum Mode {
<<<<<<< HEAD
        Encrypt,    /**< Ask passphrase twice and encrypt */
        UnlockMixing,     /**< Ask passphrase and unlock only for mixing */
        Unlock,     /**< Ask passphrase and unlock */
        ChangePass, /**< Ask old passphrase + new passphrase twice */
        Decrypt     /**< Ask passphrase and decrypt wallet */
    };

    explicit AskPassphraseDialog(Mode mode, QWidget *parent);
=======
        Encrypt,         /**< Ask passphrase twice and encrypt */
        UnlockAnonymize, /**< Ask passphrase and unlock only for anonymization */
        Unlock,          /**< Ask passphrase and unlock */
        ChangePass,      /**< Ask old passphrase + new passphrase twice */
        Decrypt          /**< Ask passphrase and decrypt wallet */
    };

    explicit AskPassphraseDialog(Mode mode, QWidget* parent, WalletModel* model);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    ~AskPassphraseDialog();

    void accept();

<<<<<<< HEAD
    void setModel(WalletModel *model);

private:
    Ui::AskPassphraseDialog *ui;
    Mode mode;
    WalletModel *model;
    bool fCapsLock;

private Q_SLOTS:
    void textChanged();
    void secureClearPassFields();

protected:
    bool event(QEvent *event);
    bool eventFilter(QObject *object, QEvent *event);
=======
    void setModel(WalletModel* model);

private:
    Ui::AskPassphraseDialog* ui;
    Mode mode;
    WalletModel* model;
    bool fCapsLock;

private slots:
    void textChanged();

protected:
    bool event(QEvent* event);
    bool eventFilter(QObject* object, QEvent* event);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};

#endif // BITCOIN_QT_ASKPASSPHRASEDIALOG_H
