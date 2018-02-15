<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#if defined(HAVE_CONFIG_H)
#include "config/gelcoin-config.h"
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#if defined(HAVE_CONFIG_H)
#include "config/lux-config.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#endif

#include "optionsdialog.h"
#include "ui_optionsdialog.h"

#include "bitcoinunits.h"
#include "guiutil.h"
<<<<<<< HEAD
#include "optionsmodel.h"

#include "validation.h" // for DEFAULT_SCRIPTCHECK_THREADS and MAX_SCRIPTCHECK_THREADS
=======
#include "darksend.h"
#include "optionsmodel.h"

#include "main.h" // for MAX_SCRIPTCHECK_THREADS
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include "netbase.h"
#include "txdb.h" // for -dbcache defaults

#ifdef ENABLE_WALLET
<<<<<<< HEAD
#include "wallet/wallet.h" // for CWallet::GetRequiredFee()

#include "privatesend-client.h"
#endif // ENABLE_WALLET
=======
#include "wallet.h" // for CWallet::minTxFee
#endif
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

#include <boost/thread.hpp>

#include <QDataWidgetMapper>
#include <QDir>
#include <QIntValidator>
#include <QLocale>
#include <QMessageBox>
#include <QTimer>

<<<<<<< HEAD
#ifdef ENABLE_WALLET
extern CWallet* pwalletMain;
#endif // ENABLE_WALLET

OptionsDialog::OptionsDialog(QWidget *parent, bool enableWallet) :
    QDialog(parent),
    ui(new Ui::OptionsDialog),
    model(0),
    mapper(0)
{
    ui->setupUi(this);
=======
OptionsDialog::OptionsDialog(QWidget* parent, bool enableWallet) : QDialog(parent),
                                                                   ui(new Ui::OptionsDialog),
                                                                   model(0),
                                                                   mapper(0),
                                                                   fProxyIpValid(true)
{
    ui->setupUi(this);
    GUIUtil::restoreWindowGeometry("nOptionsDialogWindow", this->size(), this);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    /* Main elements init */
    ui->databaseCache->setMinimum(nMinDbCache);
    ui->databaseCache->setMaximum(nMaxDbCache);
<<<<<<< HEAD
    ui->threadsScriptVerif->setMinimum(-GetNumCores());
    ui->threadsScriptVerif->setMaximum(MAX_SCRIPTCHECK_THREADS);

    /* Network elements init */
=======
    ui->threadsScriptVerif->setMinimum(-(int)boost::thread::hardware_concurrency());
    ui->threadsScriptVerif->setMaximum(MAX_SCRIPTCHECK_THREADS);

/* Network elements init */
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#ifndef USE_UPNP
    ui->mapPortUpnp->setEnabled(false);
#endif

    ui->proxyIp->setEnabled(false);
    ui->proxyPort->setEnabled(false);
    ui->proxyPort->setValidator(new QIntValidator(1, 65535, this));

<<<<<<< HEAD
    ui->proxyIpTor->setEnabled(false);
    ui->proxyPortTor->setEnabled(false);
    ui->proxyPortTor->setValidator(new QIntValidator(1, 65535, this));

    connect(ui->connectSocks, SIGNAL(toggled(bool)), ui->proxyIp, SLOT(setEnabled(bool)));
    connect(ui->connectSocks, SIGNAL(toggled(bool)), ui->proxyPort, SLOT(setEnabled(bool)));
    connect(ui->connectSocks, SIGNAL(toggled(bool)), this, SLOT(updateProxyValidationState()));

    connect(ui->connectSocksTor, SIGNAL(toggled(bool)), ui->proxyIpTor, SLOT(setEnabled(bool)));
    connect(ui->connectSocksTor, SIGNAL(toggled(bool)), ui->proxyPortTor, SLOT(setEnabled(bool)));
    connect(ui->connectSocksTor, SIGNAL(toggled(bool)), this, SLOT(updateProxyValidationState()));

    /* Window elements init */
=======
    connect(ui->connectSocks, SIGNAL(toggled(bool)), ui->proxyIp, SLOT(setEnabled(bool)));
    connect(ui->connectSocks, SIGNAL(toggled(bool)), ui->proxyPort, SLOT(setEnabled(bool)));

    ui->proxyIp->installEventFilter(this);

/* Window elements init */
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#ifdef Q_OS_MAC
    /* remove Window tab on Mac */
    ui->tabWidget->removeTab(ui->tabWidget->indexOf(ui->tabWindow));
#endif

    /* remove Wallet tab in case of -disablewallet */
    if (!enableWallet) {
        ui->tabWidget->removeTab(ui->tabWidget->indexOf(ui->tabWallet));
    }

    /* Display elements init */
<<<<<<< HEAD
    
    /* Number of displayed decimal digits selector */
    QString digits;
    for(int index = 2; index <=8; index++){
        digits.setNum(index);
        ui->digits->addItem(digits, digits);
    }
    
    /* Theme selector */
    ui->theme->addItem(QString("GEL-light"), QVariant("light"));
    ui->theme->addItem(QString("GEL-light-hires"), QVariant("light-hires"));
    ui->theme->addItem(QString("GEL-blue"), QVariant("drkblue"));
    ui->theme->addItem(QString("GEL-Crownium"), QVariant("crownium"));
    ui->theme->addItem(QString("GEL-traditional"), QVariant("trad"));
    
    /* Language selector */
    QDir translations(":translations");
    ui->lang->addItem(QString("(") + tr("default") + QString(")"), QVariant(""));
    Q_FOREACH(const QString &langStr, translations.entryList())
    {
        QLocale locale(langStr);

        /** check if the locale name consists of 2 parts (language_country) */
        if(langStr.contains("_"))
        {
=======

    /* Number of displayed decimal digits selector */
    QString digits;
    for (int index = 2; index <= 8; index++) {
        digits.setNum(index);
        ui->digits->addItem(digits, digits);
    }

    /* Theme selector static themes */
    ui->theme->addItem(QString("Default"), QVariant("default"));

    /* Theme selector external themes */
    boost::filesystem::path pathAddr = GetDataDir() / "themes";
    QDir dir(pathAddr.string().c_str());
    dir.setFilter(QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    QFileInfoList list = dir.entryInfoList();

    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        ui->theme->addItem(fileInfo.fileName(), QVariant(fileInfo.fileName()));
    }

    /* Language selector */
    QDir translations(":translations");
    ui->lang->addItem(QString("(") + tr("default") + QString(")"), QVariant(""));
    foreach (const QString& langStr, translations.entryList()) {
        QLocale locale(langStr);

        /** check if the locale name consists of 2 parts (language_country) */
        if (langStr.contains("_")) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#if QT_VERSION >= 0x040800
            /** display language strings as "native language - native country (locale name)", e.g. "Deutsch - Deutschland (de)" */
            ui->lang->addItem(locale.nativeLanguageName() + QString(" - ") + locale.nativeCountryName() + QString(" (") + langStr + QString(")"), QVariant(langStr));
#else
            /** display language strings as "language - country (locale name)", e.g. "German - Germany (de)" */
            ui->lang->addItem(QLocale::languageToString(locale.language()) + QString(" - ") + QLocale::countryToString(locale.country()) + QString(" (") + langStr + QString(")"), QVariant(langStr));
#endif
<<<<<<< HEAD
        }
        else
        {
=======
        } else {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#if QT_VERSION >= 0x040800
            /** display language strings as "native language (locale name)", e.g. "Deutsch (de)" */
            ui->lang->addItem(locale.nativeLanguageName() + QString(" (") + langStr + QString(")"), QVariant(langStr));
#else
            /** display language strings as "language (locale name)", e.g. "German (de)" */
            ui->lang->addItem(QLocale::languageToString(locale.language()) + QString(" (") + langStr + QString(")"), QVariant(langStr));
#endif
        }
    }
#if QT_VERSION >= 0x040700
    ui->thirdPartyTxUrls->setPlaceholderText("https://example.com/tx/%s");
#endif

    ui->unit->setModel(new BitcoinUnits(this));

    /* Widget-to-option mapper */
    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper->setOrientation(Qt::Vertical);

<<<<<<< HEAD
    /* setup/change UI elements when proxy IPs are invalid/valid */
    ui->proxyIp->setCheckValidator(new ProxyAddressValidator(parent));
    ui->proxyIpTor->setCheckValidator(new ProxyAddressValidator(parent));
    connect(ui->proxyIp, SIGNAL(validationDidChange(QValidatedLineEdit *)), this, SLOT(updateProxyValidationState()));
    connect(ui->proxyIpTor, SIGNAL(validationDidChange(QValidatedLineEdit *)), this, SLOT(updateProxyValidationState()));
    connect(ui->proxyPort, SIGNAL(textChanged(const QString&)), this, SLOT(updateProxyValidationState()));
    connect(ui->proxyPortTor, SIGNAL(textChanged(const QString&)), this, SLOT(updateProxyValidationState()));
=======
    /* setup/change UI elements when proxy IP is invalid/valid */
    connect(this, SIGNAL(proxyIpChecks(QValidatedLineEdit*, int)), this, SLOT(doProxyIpChecks(QValidatedLineEdit*, int)));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

OptionsDialog::~OptionsDialog()
{
<<<<<<< HEAD
    delete ui;
}

void OptionsDialog::setModel(OptionsModel *model)
{
    this->model = model;

    if(model)
    {
=======
    GUIUtil::saveWindowGeometry("nOptionsDialogWindow", this);
    delete ui;
}

void OptionsDialog::setModel(OptionsModel* model)
{
    this->model = model;

    if (model) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        /* check if client restart is needed and show persistent message */
        if (model->isRestartRequired())
            showRestartWarning(true);

        QString strLabel = model->getOverriddenByCommandLine();
        if (strLabel.isEmpty())
            strLabel = tr("none");
        ui->overriddenByCommandLineLabel->setText(strLabel);

        mapper->setModel(model);
        setMapper();
        mapper->toFirst();
<<<<<<< HEAD

        updateDefaultProxyNets();
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }

    /* warn when one of the following settings changes by user action (placed here so init via mapper doesn't trigger them) */

    /* Main */
    connect(ui->databaseCache, SIGNAL(valueChanged(int)), this, SLOT(showRestartWarning()));
    connect(ui->threadsScriptVerif, SIGNAL(valueChanged(int)), this, SLOT(showRestartWarning()));
    /* Wallet */
<<<<<<< HEAD
    connect(ui->showMasternodesTab, SIGNAL(clicked(bool)), this, SLOT(showRestartWarning()));
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    connect(ui->spendZeroConfChange, SIGNAL(clicked(bool)), this, SLOT(showRestartWarning()));
    /* Network */
    connect(ui->allowIncoming, SIGNAL(clicked(bool)), this, SLOT(showRestartWarning()));
    connect(ui->connectSocks, SIGNAL(clicked(bool)), this, SLOT(showRestartWarning()));
<<<<<<< HEAD
    connect(ui->connectSocksTor, SIGNAL(clicked(bool)), this, SLOT(showRestartWarning()));
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    /* Display */
    connect(ui->digits, SIGNAL(valueChanged()), this, SLOT(showRestartWarning()));
    connect(ui->theme, SIGNAL(valueChanged()), this, SLOT(showRestartWarning()));
    connect(ui->lang, SIGNAL(valueChanged()), this, SLOT(showRestartWarning()));
<<<<<<< HEAD
    connect(ui->thirdPartyTxUrls, SIGNAL(textChanged(const QString &)), this, SLOT(showRestartWarning()));
=======
    connect(ui->thirdPartyTxUrls, SIGNAL(textChanged(const QString&)), this, SLOT(showRestartWarning()));
    connect(ui->showMasternodesTab, SIGNAL(clicked(bool)), this, SLOT(showRestartWarning()));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

void OptionsDialog::setMapper()
{
    /* Main */
    mapper->addMapping(ui->bitcoinAtStartup, OptionsModel::StartAtStartup);
    mapper->addMapping(ui->threadsScriptVerif, OptionsModel::ThreadsScriptVerif);
    mapper->addMapping(ui->databaseCache, OptionsModel::DatabaseCache);

    /* Wallet */
<<<<<<< HEAD
    mapper->addMapping(ui->coinControlFeatures, OptionsModel::CoinControlFeatures);
    mapper->addMapping(ui->showMasternodesTab, OptionsModel::ShowMasternodesTab);
    mapper->addMapping(ui->showAdvancedPSUI, OptionsModel::ShowAdvancedPSUI);
    mapper->addMapping(ui->lowKeysWarning, OptionsModel::LowKeysWarning);
    mapper->addMapping(ui->privateSendMultiSession, OptionsModel::PrivateSendMultiSession);
    mapper->addMapping(ui->spendZeroConfChange, OptionsModel::SpendZeroConfChange);
    mapper->addMapping(ui->privateSendRounds, OptionsModel::PrivateSendRounds);
    mapper->addMapping(ui->privateSendAmount, OptionsModel::PrivateSendAmount);
=======
    mapper->addMapping(ui->spendZeroConfChange, OptionsModel::SpendZeroConfChange);
    mapper->addMapping(ui->coinControlFeatures, OptionsModel::CoinControlFeatures);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    /* Network */
    mapper->addMapping(ui->mapPortUpnp, OptionsModel::MapPortUPnP);
    mapper->addMapping(ui->allowIncoming, OptionsModel::Listen);

    mapper->addMapping(ui->connectSocks, OptionsModel::ProxyUse);
    mapper->addMapping(ui->proxyIp, OptionsModel::ProxyIP);
    mapper->addMapping(ui->proxyPort, OptionsModel::ProxyPort);

<<<<<<< HEAD
    mapper->addMapping(ui->connectSocksTor, OptionsModel::ProxyUseTor);
    mapper->addMapping(ui->proxyIpTor, OptionsModel::ProxyIPTor);
    mapper->addMapping(ui->proxyPortTor, OptionsModel::ProxyPortTor);

    /* Window */
#ifndef Q_OS_MAC
    mapper->addMapping(ui->hideTrayIcon, OptionsModel::HideTrayIcon);
=======
/* Window */
#ifndef Q_OS_MAC
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    mapper->addMapping(ui->minimizeToTray, OptionsModel::MinimizeToTray);
    mapper->addMapping(ui->minimizeOnClose, OptionsModel::MinimizeOnClose);
#endif

    /* Display */
    mapper->addMapping(ui->digits, OptionsModel::Digits);
    mapper->addMapping(ui->theme, OptionsModel::Theme);
<<<<<<< HEAD
=======
    mapper->addMapping(ui->theme, OptionsModel::Theme);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    mapper->addMapping(ui->lang, OptionsModel::Language);
    mapper->addMapping(ui->unit, OptionsModel::DisplayUnit);
    mapper->addMapping(ui->thirdPartyTxUrls, OptionsModel::ThirdPartyTxUrls);

<<<<<<< HEAD
=======

    /* LuxSend Rounds */
    mapper->addMapping(ui->darksendRounds, OptionsModel::DarksendRounds);
    mapper->addMapping(ui->anonymizeLux, OptionsModel::AnonymizeLuxAmount);
    mapper->addMapping(ui->showMasternodesTab, OptionsModel::ShowMasternodesTab);
}

void OptionsDialog::enableOkButton()
{
    /* prevent enabling of the OK button when data modified, if there is an invalid proxy address present */
    if (fProxyIpValid)
        setOkButtonState(true);
}

void OptionsDialog::disableOkButton()
{
    setOkButtonState(false);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

void OptionsDialog::setOkButtonState(bool fState)
{
    ui->okButton->setEnabled(fState);
}

void OptionsDialog::on_resetButton_clicked()
{
<<<<<<< HEAD
    if(model)
    {
        // confirmation dialog
        QMessageBox::StandardButton btnRetVal = QMessageBox::question(this, tr("Confirm options reset"),
            tr("Client restart required to activate changes.") + "<br><br>" + tr("Client will be shut down. Do you want to proceed?"),
            QMessageBox::Yes | QMessageBox::Cancel, QMessageBox::Cancel);

        if(btnRetVal == QMessageBox::Cancel)
=======
    if (model) {
        // confirmation dialog
        QMessageBox::StandardButton btnRetVal = QMessageBox::question(this, tr("Confirm options reset"),
            tr("Client restart required to activate changes.") + "<br><br>" + tr("Client will be shutdown, do you want to proceed?"),
            QMessageBox::Yes | QMessageBox::Cancel, QMessageBox::Cancel);

        if (btnRetVal == QMessageBox::Cancel)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            return;

        /* reset all options and close GUI */
        model->Reset();
        QApplication::quit();
    }
}

void OptionsDialog::on_okButton_clicked()
{
    mapper->submit();
<<<<<<< HEAD
#ifdef ENABLE_WALLET
    privateSendClient.nCachedNumBlocks = std::numeric_limits<int>::max();
    if(pwalletMain)
        pwalletMain->MarkDirty();
#endif // ENABLE_WALLET
    accept();
    updateDefaultProxyNets();
=======
    //obfuscationPool.cachedNumBlocks = std::numeric_limits<int>::max();
    pwalletMain->MarkDirty();
    accept();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

void OptionsDialog::on_cancelButton_clicked()
{
    reject();
}

<<<<<<< HEAD
void OptionsDialog::on_hideTrayIcon_stateChanged(int fState)
{
    if(fState)
    {
        ui->minimizeToTray->setChecked(false);
        ui->minimizeToTray->setEnabled(false);
    }
    else
    {
        ui->minimizeToTray->setEnabled(true);
    }
}

=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
void OptionsDialog::showRestartWarning(bool fPersistent)
{
    ui->statusLabel->setStyleSheet("QLabel { color: red; }");

<<<<<<< HEAD
    if(fPersistent)
    {
        ui->statusLabel->setText(tr("Client restart required to activate changes."));
    }
    else
    {
=======
    if (fPersistent) {
        ui->statusLabel->setText(tr("Client restart required to activate changes."));
    } else {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        ui->statusLabel->setText(tr("This change would require a client restart."));
        // clear non-persistent status label after 10 seconds
        // Todo: should perhaps be a class attribute, if we extend the use of statusLabel
        QTimer::singleShot(10000, this, SLOT(clearStatusLabel()));
    }
}

void OptionsDialog::clearStatusLabel()
{
    ui->statusLabel->clear();
}

<<<<<<< HEAD
void OptionsDialog::updateProxyValidationState()
{
    QValidatedLineEdit *pUiProxyIp = ui->proxyIp;
    QValidatedLineEdit *otherProxyWidget = (pUiProxyIp == ui->proxyIpTor) ? ui->proxyIp : ui->proxyIpTor;
    if (pUiProxyIp->isValid() && (!ui->proxyPort->isEnabled() || ui->proxyPort->text().toInt() > 0) && (!ui->proxyPortTor->isEnabled() || ui->proxyPortTor->text().toInt() > 0))
    {
        setOkButtonState(otherProxyWidget->isValid()); //only enable ok button if both proxys are valid
        ui->statusLabel->clear();
    }
    else
    {
        setOkButtonState(false);
        ui->statusLabel->setStyleSheet("QLabel { color: red; }");
        ui->statusLabel->setText(tr("The supplied proxy address is invalid."));
    }
}

void OptionsDialog::updateDefaultProxyNets()
{
    proxyType proxy;
    std::string strProxy;
    QString strDefaultProxyGUI;

    GetProxy(NET_IPV4, proxy);
    strProxy = proxy.proxy.ToStringIP() + ":" + proxy.proxy.ToStringPort();
    strDefaultProxyGUI = ui->proxyIp->text() + ":" + ui->proxyPort->text();
    (strProxy == strDefaultProxyGUI.toStdString()) ? ui->proxyReachIPv4->setChecked(true) : ui->proxyReachIPv4->setChecked(false);

    GetProxy(NET_IPV6, proxy);
    strProxy = proxy.proxy.ToStringIP() + ":" + proxy.proxy.ToStringPort();
    strDefaultProxyGUI = ui->proxyIp->text() + ":" + ui->proxyPort->text();
    (strProxy == strDefaultProxyGUI.toStdString()) ? ui->proxyReachIPv6->setChecked(true) : ui->proxyReachIPv6->setChecked(false);

    GetProxy(NET_TOR, proxy);
    strProxy = proxy.proxy.ToStringIP() + ":" + proxy.proxy.ToStringPort();
    strDefaultProxyGUI = ui->proxyIp->text() + ":" + ui->proxyPort->text();
    (strProxy == strDefaultProxyGUI.toStdString()) ? ui->proxyReachTor->setChecked(true) : ui->proxyReachTor->setChecked(false);
}

ProxyAddressValidator::ProxyAddressValidator(QObject *parent) :
QValidator(parent)
{
}

QValidator::State ProxyAddressValidator::validate(QString &input, int &pos) const
{
    Q_UNUSED(pos);
    // Validate the proxy
    CService serv(LookupNumeric(input.toStdString().c_str(), 9050));
    proxyType addrProxy = proxyType(serv, true);
    if (addrProxy.IsValid())
        return QValidator::Acceptable;

    return QValidator::Invalid;
=======
void OptionsDialog::doProxyIpChecks(QValidatedLineEdit* pUiProxyIp, int nProxyPort)
{
    Q_UNUSED(nProxyPort);

    const std::string strAddrProxy = pUiProxyIp->text().toStdString();
    CService addrProxy;

    /* Check for a valid IPv4 / IPv6 address */
    if (!(fProxyIpValid = LookupNumeric(strAddrProxy.c_str(), addrProxy))) {
        disableOkButton();
        pUiProxyIp->setValid(false);
        ui->statusLabel->setStyleSheet("QLabel { color: red; }");
        ui->statusLabel->setText(tr("The supplied proxy address is invalid."));
    } else {
        enableOkButton();
        ui->statusLabel->clear();
    }
}

bool OptionsDialog::eventFilter(QObject* object, QEvent* event)
{
    if (event->type() == QEvent::FocusOut) {
        if (object == ui->proxyIp) {
            emit proxyIpChecks(ui->proxyIp, ui->proxyPort->text().toInt());
        }
    }
    return QDialog::eventFilter(object, event);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}
