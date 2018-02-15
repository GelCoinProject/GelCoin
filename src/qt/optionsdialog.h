<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_OPTIONSDIALOG_H
#define BITCOIN_QT_OPTIONSDIALOG_H

#include <QDialog>
<<<<<<< HEAD
#include <QValidator>
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

class OptionsModel;
class QValidatedLineEdit;

QT_BEGIN_NAMESPACE
class QDataWidgetMapper;
QT_END_NAMESPACE

<<<<<<< HEAD
namespace Ui {
class OptionsDialog;
}

/** Proxy address widget validator, checks for a valid proxy address.
 */
class ProxyAddressValidator : public QValidator
{
    Q_OBJECT

public:
    explicit ProxyAddressValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

=======
namespace Ui
{
class OptionsDialog;
}

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
/** Preferences dialog. */
class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit OptionsDialog(QWidget *parent, bool enableWallet);
    ~OptionsDialog();

    void setModel(OptionsModel *model);
    void setMapper();

private Q_SLOTS:
=======
    explicit OptionsDialog(QWidget* parent, bool enableWallet);
    ~OptionsDialog();

    void setModel(OptionsModel* model);
    void setMapper();

protected:
    bool eventFilter(QObject* object, QEvent* event);

private slots:
    /* enable OK button */
    void enableOkButton();
    /* disable OK button */
    void disableOkButton();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    /* set OK button state (enabled / disabled) */
    void setOkButtonState(bool fState);
    void on_resetButton_clicked();
    void on_okButton_clicked();
    void on_cancelButton_clicked();
<<<<<<< HEAD
    
    void on_hideTrayIcon_stateChanged(int fState);

    void showRestartWarning(bool fPersistent = false);
    void clearStatusLabel();
    void updateProxyValidationState();
    /* query the networks, for which the default proxy is used */
    void updateDefaultProxyNets();

Q_SIGNALS:
    void proxyIpChecks(QValidatedLineEdit *pUiProxyIp, int nProxyPort);

private:
    Ui::OptionsDialog *ui;
    OptionsModel *model;
    QDataWidgetMapper *mapper;
=======

    void showRestartWarning(bool fPersistent = false);
    void clearStatusLabel();
    void doProxyIpChecks(QValidatedLineEdit* pUiProxyIp, int nProxyPort);

signals:
    void proxyIpChecks(QValidatedLineEdit* pUiProxyIp, int nProxyPort);

private:
    Ui::OptionsDialog* ui;
    OptionsModel* model;
    QDataWidgetMapper* mapper;
    bool fProxyIpValid;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};

#endif // BITCOIN_QT_OPTIONSDIALOG_H
