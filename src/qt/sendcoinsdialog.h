<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_SENDCOINSDIALOG_H
#define BITCOIN_QT_SENDCOINSDIALOG_H

#include "walletmodel.h"

#include <QDialog>
#include <QString>

static const int MAX_SEND_POPUP_ENTRIES = 10;

class ClientModel;
class OptionsModel;
<<<<<<< HEAD
class PlatformStyle;
class SendCoinsEntry;
class SendCoinsRecipient;

namespace Ui {
    class SendCoinsDialog;
=======
class SendCoinsEntry;
class SendCoinsRecipient;

namespace Ui
{
class SendCoinsDialog;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

QT_BEGIN_NAMESPACE
class QUrl;
QT_END_NAMESPACE

<<<<<<< HEAD
const int defaultConfirmTarget = 25;

=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
/** Dialog for sending bitcoins */
class SendCoinsDialog : public QDialog
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit SendCoinsDialog(const PlatformStyle *platformStyle, QWidget *parent = 0);
    ~SendCoinsDialog();

    void setClientModel(ClientModel *clientModel);
    void setModel(WalletModel *model);

    /** Set up the tab chain manually, as Qt messes up the tab chain by default in some cases (issue https://bugreports.qt-project.org/browse/QTBUG-10907).
     */
    QWidget *setupTabChain(QWidget *prev);

    void setAddress(const QString &address);
    void pasteEntry(const SendCoinsRecipient &rv);
    bool handlePaymentRequest(const SendCoinsRecipient &recipient);

public Q_SLOTS:
    void clear();
    void reject();
    void accept();
    SendCoinsEntry *addEntry();
    void updateTabsAndLabels();
    void setBalance(const CAmount& balance, const CAmount& unconfirmedBalance, const CAmount& immatureBalance, const CAmount& anonymizedBalance,
                    const CAmount& watchOnlyBalance, const CAmount& watchUnconfBalance, const CAmount& watchImmatureBalance);

private:
    Ui::SendCoinsDialog *ui;
    ClientModel *clientModel;
    WalletModel *model;
    bool fNewRecipientAllowed;
    void send(QList<SendCoinsRecipient> recipients, QString strFee, QString strFunds);
    bool fFeeMinimized;
    const PlatformStyle *platformStyle;

    // Process WalletModel::SendCoinsReturn and generate a pair consisting
    // of a message and message flags for use in Q_EMIT message().
    // Additional parameter msgArg can be used via .arg(msgArg).
    void processSendCoinsReturn(const WalletModel::SendCoinsReturn &sendCoinsReturn, const QString &msgArg = QString());
    void minimizeFeeSection(bool fMinimize);
    void updateFeeMinimizedLabel();

private Q_SLOTS:
=======
    explicit SendCoinsDialog(QWidget* parent = 0);
    ~SendCoinsDialog();

    void setClientModel(ClientModel* clientModel);
    void setModel(WalletModel* model);

    /** Set up the tab chain manually, as Qt messes up the tab chain by default in some cases (issue https://bugreports.qt-project.org/browse/QTBUG-10907).
     */
    QWidget* setupTabChain(QWidget* prev);

    void setAddress(const QString& address);
    void pasteEntry(const SendCoinsRecipient& rv);
    bool handlePaymentRequest(const SendCoinsRecipient& recipient);
    bool fSplitBlock;

public slots:
    void clear();
    void reject();
    void accept();
    SendCoinsEntry* addEntry();
    void updateTabsAndLabels();
    void setBalance(const CAmount& balance, const CAmount& unconfirmedBalance, const CAmount& immatureBalance, const CAmount& anonymizedBalance, const CAmount& watchOnlyBalance, const CAmount& watchUnconfBalance, const CAmount& watchImmatureBalance);

private:
    Ui::SendCoinsDialog* ui;
    ClientModel* clientModel;
    WalletModel* model;
    bool fNewRecipientAllowed;
    void send(QList<SendCoinsRecipient> recipients, QString strFee, QStringList formatted);
    bool fFeeMinimized;

    // Process WalletModel::SendCoinsReturn and generate a pair consisting
    // of a message and message flags for use in emit message().
    // Additional parameter msgArg can be used via .arg(msgArg).
    void processSendCoinsReturn(const WalletModel::SendCoinsReturn& sendCoinsReturn, const QString& msgArg = QString(), bool fPrepare = false);
    void minimizeFeeSection(bool fMinimize);
    void updateFeeMinimizedLabel();

private slots:
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void on_sendButton_clicked();
    void on_buttonChooseFee_clicked();
    void on_buttonMinimizeFee_clicked();
    void removeEntry(SendCoinsEntry* entry);
    void updateDisplayUnit();
<<<<<<< HEAD
    void updateInstantSend();
    void coinControlFeatureChanged(bool);
    void coinControlButtonClicked();
    void coinControlChangeChecked(int);
    void coinControlChangeEdited(const QString &);
=======
    void updateSwiftTX();
    void coinControlFeatureChanged(bool);
    void coinControlButtonClicked();
    void coinControlChangeChecked(int);
    void coinControlChangeEdited(const QString&);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void coinControlUpdateLabels();
    void coinControlClipboardQuantity();
    void coinControlClipboardAmount();
    void coinControlClipboardFee();
    void coinControlClipboardAfterFee();
    void coinControlClipboardBytes();
<<<<<<< HEAD
    void coinControlClipboardLowOutput();
    void coinControlClipboardChange();
=======
    void coinControlClipboardPriority();
    void coinControlClipboardLowOutput();
    void coinControlClipboardChange();
    void splitBlockChecked(int);
    void splitBlockLineEditChanged(const QString& text);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void setMinimumFee();
    void updateFeeSectionControls();
    void updateMinFeeLabel();
    void updateSmartFeeLabel();
    void updateGlobalFeeVariables();

<<<<<<< HEAD
Q_SIGNALS:
    // Fired when a message should be reported to the user
    void message(const QString &title, const QString &message, unsigned int style);
=======
signals:
    // Fired when a message should be reported to the user
    void message(const QString& title, const QString& message, unsigned int style);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};

#endif // BITCOIN_QT_SENDCOINSDIALOG_H
