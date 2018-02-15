<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Copyright (c) 2014-2017 The GelCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#if defined(HAVE_CONFIG_H)
#include "config/gelcoin-config.h"
=======
// Copyright (c) 2011-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The LUX developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#if defined(HAVE_CONFIG_H)
#include "config/lux-config.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#endif

#include "optionsmodel.h"

#include "bitcoinunits.h"
#include "guiutil.h"

#include "amount.h"
#include "init.h"
<<<<<<< HEAD
#include "validation.h" // For DEFAULT_SCRIPTCHECK_THREADS
#include "net.h"
#include "netbase.h"
#include "txdb.h" // for -dbcache defaults

#ifdef ENABLE_WALLET
#include "wallet/wallet.h"
#include "wallet/walletdb.h"

#include "masternodeconfig.h"
#include "privatesend-client.h"
=======
#include "main.h"
#include "net.h"
#include "txdb.h" // for -dbcache defaults

#ifdef ENABLE_WALLET
#include "masternodeconfig.h"
#include "wallet.h"
#include "walletdb.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#endif

#include <QNetworkProxy>
#include <QSettings>
#include <QStringList>

<<<<<<< HEAD
OptionsModel::OptionsModel(QObject *parent, bool resetSettings) :
    QAbstractListModel(parent)
{
    Init(resetSettings);
}

void OptionsModel::addOverriddenOption(const std::string &option)
=======
OptionsModel::OptionsModel(QObject* parent) : QAbstractListModel(parent)
{
    Init();
}

void OptionsModel::addOverriddenOption(const std::string& option)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    strOverriddenByCommandLine += QString::fromStdString(option) + "=" + QString::fromStdString(mapArgs[option]) + " ";
}

// Writes all missing QSettings with their default values
<<<<<<< HEAD
void OptionsModel::Init(bool resetSettings)
{
    if (resetSettings)
        Reset();

    this->resetSettings = resetSettings;

=======
void OptionsModel::Init()
{
    resetSettings = false;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    QSettings settings;

    // Ensure restart flag is unset on client startup
    setRestartRequired(false);

    // These are Qt-only settings:

    // Window
<<<<<<< HEAD
    if (!settings.contains("fHideTrayIcon"))
        settings.setValue("fHideTrayIcon", false);
    fHideTrayIcon = settings.value("fHideTrayIcon").toBool();
    Q_EMIT hideTrayIconChanged(fHideTrayIcon);
    
    if (!settings.contains("fMinimizeToTray"))
        settings.setValue("fMinimizeToTray", false);
    fMinimizeToTray = settings.value("fMinimizeToTray").toBool() && !fHideTrayIcon;
=======
    if (!settings.contains("fMinimizeToTray"))
        settings.setValue("fMinimizeToTray", false);
    fMinimizeToTray = settings.value("fMinimizeToTray").toBool();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    if (!settings.contains("fMinimizeOnClose"))
        settings.setValue("fMinimizeOnClose", false);
    fMinimizeOnClose = settings.value("fMinimizeOnClose").toBool();

    // Display
    if (!settings.contains("nDisplayUnit"))
<<<<<<< HEAD
        settings.setValue("nDisplayUnit", BitcoinUnits::GEL);
=======
        settings.setValue("nDisplayUnit", BitcoinUnits::LUX);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    nDisplayUnit = settings.value("nDisplayUnit").toInt();

    if (!settings.contains("strThirdPartyTxUrls"))
        settings.setValue("strThirdPartyTxUrls", "");
    strThirdPartyTxUrls = settings.value("strThirdPartyTxUrls", "").toString();

<<<<<<< HEAD
    if (!settings.contains("theme"))
        settings.setValue("theme", "");

#ifdef ENABLE_WALLET
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    if (!settings.contains("fCoinControlFeatures"))
        settings.setValue("fCoinControlFeatures", false);
    fCoinControlFeatures = settings.value("fCoinControlFeatures", false).toBool();

<<<<<<< HEAD
    if (!settings.contains("digits"))
        settings.setValue("digits", "2");

    if (!settings.contains("fShowMasternodesTab"))
        settings.setValue("fShowMasternodesTab", masternodeConfig.getCount());

    if (!settings.contains("fShowAdvancedPSUI"))
        settings.setValue("fShowAdvancedPSUI", false);
    fShowAdvancedPSUI = settings.value("fShowAdvancedPSUI", false).toBool();

    if (!settings.contains("fLowKeysWarning"))
        settings.setValue("fLowKeysWarning", true);
#endif // ENABLE_WALLET
=======
    if (!settings.contains("nDarksendRounds"))
        settings.setValue("nDarksendRounds", 2);

    if (!settings.contains("nAnonymizeLuxAmount"))
        settings.setValue("nAnonymizeLuxAmount", 1000);

    nDarksendRounds = settings.value("nDarksendRounds").toLongLong();
    nAnonymizeLuxAmount = settings.value("nAnonymizeLuxAmount").toLongLong();

    if (!settings.contains("fShowMasternodesTab"))
        settings.setValue("fShowMasternodesTab", masternodeConfig.getCount());
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    // These are shared with the core or have a command-line parameter
    // and we want command-line parameters to overwrite the GUI settings.
    //
    // If setting doesn't exist create it with defaults.
    //
    // If SoftSetArg() or SoftSetBoolArg() return false we were overridden
    // by command-line and show this in the UI.

    // Main
    if (!settings.contains("nDatabaseCache"))
        settings.setValue("nDatabaseCache", (qint64)nDefaultDbCache);
    if (!SoftSetArg("-dbcache", settings.value("nDatabaseCache").toString().toStdString()))
        addOverriddenOption("-dbcache");

    if (!settings.contains("nThreadsScriptVerif"))
        settings.setValue("nThreadsScriptVerif", DEFAULT_SCRIPTCHECK_THREADS);
    if (!SoftSetArg("-par", settings.value("nThreadsScriptVerif").toString().toStdString()))
        addOverriddenOption("-par");

<<<<<<< HEAD
    // Wallet
=======
// Wallet
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#ifdef ENABLE_WALLET
    if (!settings.contains("bSpendZeroConfChange"))
        settings.setValue("bSpendZeroConfChange", true);
    if (!SoftSetBoolArg("-spendzeroconfchange", settings.value("bSpendZeroConfChange").toBool()))
        addOverriddenOption("-spendzeroconfchange");
<<<<<<< HEAD

    // PrivateSend
    if (!settings.contains("nPrivateSendRounds"))
        settings.setValue("nPrivateSendRounds", DEFAULT_PRIVATESEND_ROUNDS);
    if (!SoftSetArg("-privatesendrounds", settings.value("nPrivateSendRounds").toString().toStdString()))
        addOverriddenOption("-privatesendrounds");
    privateSendClient.nPrivateSendRounds = settings.value("nPrivateSendRounds").toInt();

    if (!settings.contains("nPrivateSendAmount")) {
        // for migration from old settings
        if (!settings.contains("nAnonymizeGelCoinAmount"))
            settings.setValue("nPrivateSendAmount", DEFAULT_PRIVATESEND_AMOUNT);
        else
            settings.setValue("nPrivateSendAmount", settings.value("nAnonymizeGelCoinAmount").toInt());
    }
    if (!SoftSetArg("-privatesendamount", settings.value("nPrivateSendAmount").toString().toStdString()))
        addOverriddenOption("-privatesendamount");
    privateSendClient.nPrivateSendAmount = settings.value("nPrivateSendAmount").toInt();

    if (!settings.contains("fPrivateSendMultiSession"))
        settings.setValue("fPrivateSendMultiSession", DEFAULT_PRIVATESEND_MULTISESSION);
    if (!SoftSetBoolArg("-privatesendmultisession", settings.value("fPrivateSendMultiSession").toBool()))
        addOverriddenOption("-privatesendmultisession");
    privateSendClient.fPrivateSendMultiSession = settings.value("fPrivateSendMultiSession").toBool();
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#endif

    // Network
    if (!settings.contains("fUseUPnP"))
        settings.setValue("fUseUPnP", DEFAULT_UPNP);
    if (!SoftSetBoolArg("-upnp", settings.value("fUseUPnP").toBool()))
        addOverriddenOption("-upnp");

    if (!settings.contains("fListen"))
        settings.setValue("fListen", DEFAULT_LISTEN);
    if (!SoftSetBoolArg("-listen", settings.value("fListen").toBool()))
        addOverriddenOption("-listen");

    if (!settings.contains("fUseProxy"))
        settings.setValue("fUseProxy", false);
    if (!settings.contains("addrProxy"))
        settings.setValue("addrProxy", "127.0.0.1:9050");
    // Only try to set -proxy, if user has enabled fUseProxy
    if (settings.value("fUseProxy").toBool() && !SoftSetArg("-proxy", settings.value("addrProxy").toString().toStdString()))
        addOverriddenOption("-proxy");
<<<<<<< HEAD
    else if(!settings.value("fUseProxy").toBool() && !GetArg("-proxy", "").empty())
        addOverriddenOption("-proxy");

    if (!settings.contains("fUseSeparateProxyTor"))
        settings.setValue("fUseSeparateProxyTor", false);
    if (!settings.contains("addrSeparateProxyTor"))
        settings.setValue("addrSeparateProxyTor", "127.0.0.1:9050");
    // Only try to set -onion, if user has enabled fUseSeparateProxyTor
    if (settings.value("fUseSeparateProxyTor").toBool() && !SoftSetArg("-onion", settings.value("addrSeparateProxyTor").toString().toStdString()))
        addOverriddenOption("-onion");
    else if(!settings.value("fUseSeparateProxyTor").toBool() && !GetArg("-onion", "").empty())
        addOverriddenOption("-onion");

    // Display
=======
    else if (!settings.value("fUseProxy").toBool() && !GetArg("-proxy", "").empty())
        addOverriddenOption("-proxy");

    // Display
    if (!settings.contains("digits"))
        settings.setValue("digits", "2");
    if (!settings.contains("theme"))
        settings.setValue("theme", "");
    if (!settings.contains("fCSSexternal"))
        settings.setValue("fCSSexternal", false);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    if (!settings.contains("language"))
        settings.setValue("language", "");
    if (!SoftSetArg("-lang", settings.value("language").toString().toStdString()))
        addOverriddenOption("-lang");

<<<<<<< HEAD
=======
    if (settings.contains("nDarksendRounds"))
        SoftSetArg("-obfuscationrounds", settings.value("nDarksendRounds").toString().toStdString());
    if (settings.contains("nAnonymizeLuxAmount"))
        SoftSetArg("-anonymizeluxamount", settings.value("nAnonymizeLuxAmount").toString().toStdString());

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    language = settings.value("language").toString();
}

void OptionsModel::Reset()
{
    QSettings settings;

    // Remove all entries from our QSettings object
    settings.clear();
<<<<<<< HEAD
    resetSettings = true; // Needed in gelcoin.cpp during shotdown to also remove the window positions
=======
    resetSettings = true; // Needed in lux.cpp during shotdown to also remove the window positions
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    // default setting for OptionsModel::StartAtStartup - disabled
    if (GUIUtil::GetStartOnSystemStartup())
        GUIUtil::SetStartOnSystemStartup(false);
}

<<<<<<< HEAD
int OptionsModel::rowCount(const QModelIndex & parent) const
=======
int OptionsModel::rowCount(const QModelIndex& parent) const
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    return OptionIDRowCount;
}

// read QSettings values and return them
<<<<<<< HEAD
QVariant OptionsModel::data(const QModelIndex & index, int role) const
{
    if(role == Qt::EditRole)
    {
        QSettings settings;
        switch(index.row())
        {
        case StartAtStartup:
            return GUIUtil::GetStartOnSystemStartup();
        case HideTrayIcon:
            return fHideTrayIcon;
=======
QVariant OptionsModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::EditRole) {
        QSettings settings;
        switch (index.row()) {
        case StartAtStartup:
            return GUIUtil::GetStartOnSystemStartup();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        case MinimizeToTray:
            return fMinimizeToTray;
        case MapPortUPnP:
#ifdef USE_UPNP
            return settings.value("fUseUPnP");
#else
            return false;
#endif
        case MinimizeOnClose:
            return fMinimizeOnClose;

        // default proxy
        case ProxyUse:
            return settings.value("fUseProxy", false);
        case ProxyIP: {
            // contains IP at index 0 and port at index 1
            QStringList strlIpPort = settings.value("addrProxy").toString().split(":", QString::SkipEmptyParts);
            return strlIpPort.at(0);
        }
        case ProxyPort: {
            // contains IP at index 0 and port at index 1
            QStringList strlIpPort = settings.value("addrProxy").toString().split(":", QString::SkipEmptyParts);
            return strlIpPort.at(1);
        }

<<<<<<< HEAD
        // separate Tor proxy
        case ProxyUseTor:
            return settings.value("fUseSeparateProxyTor", false);
        case ProxyIPTor: {
            // contains IP at index 0 and port at index 1
            QStringList strlIpPort = settings.value("addrSeparateProxyTor").toString().split(":", QString::SkipEmptyParts);
            return strlIpPort.at(0);
        }
        case ProxyPortTor: {
            // contains IP at index 0 and port at index 1
            QStringList strlIpPort = settings.value("addrSeparateProxyTor").toString().split(":", QString::SkipEmptyParts);
            return strlIpPort.at(1);
        }

=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#ifdef ENABLE_WALLET
        case SpendZeroConfChange:
            return settings.value("bSpendZeroConfChange");
        case ShowMasternodesTab:
            return settings.value("fShowMasternodesTab");
<<<<<<< HEAD
        case ShowAdvancedPSUI:
            return fShowAdvancedPSUI;
        case LowKeysWarning:
            return settings.value("fLowKeysWarning");
        case PrivateSendRounds:
            return settings.value("nPrivateSendRounds");
        case PrivateSendAmount:
            return settings.value("nPrivateSendAmount");
        case PrivateSendMultiSession:
            return settings.value("fPrivateSendMultiSession");
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#endif
        case DisplayUnit:
            return nDisplayUnit;
        case ThirdPartyTxUrls:
            return strThirdPartyTxUrls;
<<<<<<< HEAD
#ifdef ENABLE_WALLET
        case Digits:
            return settings.value("digits");
#endif // ENABLE_WALLET
=======
        case Digits:
            return settings.value("digits");
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        case Theme:
            return settings.value("theme");
        case Language:
            return settings.value("language");
<<<<<<< HEAD
#ifdef ENABLE_WALLET
        case CoinControlFeatures:
            return fCoinControlFeatures;
#endif // ENABLE_WALLET
=======
        case CoinControlFeatures:
            return fCoinControlFeatures;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        case DatabaseCache:
            return settings.value("nDatabaseCache");
        case ThreadsScriptVerif:
            return settings.value("nThreadsScriptVerif");
<<<<<<< HEAD
=======
        case DarksendRounds:
            return QVariant(nDarksendRounds);
        case AnonymizeLuxAmount:
            return QVariant(nAnonymizeLuxAmount);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        case Listen:
            return settings.value("fListen");
        default:
            return QVariant();
        }
    }
    return QVariant();
}

// write QSettings values
<<<<<<< HEAD
bool OptionsModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    bool successful = true; /* set to false on parse error */
    if(role == Qt::EditRole)
    {
        QSettings settings;
        switch(index.row())
        {
        case StartAtStartup:
            successful = GUIUtil::SetStartOnSystemStartup(value.toBool());
            break;
        case HideTrayIcon:
            fHideTrayIcon = value.toBool();
            settings.setValue("fHideTrayIcon", fHideTrayIcon);
    		Q_EMIT hideTrayIconChanged(fHideTrayIcon);
            break;
=======
bool OptionsModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    bool successful = true; /* set to false on parse error */
    if (role == Qt::EditRole) {
        QSettings settings;
        switch (index.row()) {
        case StartAtStartup:
            successful = GUIUtil::SetStartOnSystemStartup(value.toBool());
            break;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        case MinimizeToTray:
            fMinimizeToTray = value.toBool();
            settings.setValue("fMinimizeToTray", fMinimizeToTray);
            break;
        case MapPortUPnP: // core option - can be changed on-the-fly
            settings.setValue("fUseUPnP", value.toBool());
            MapPort(value.toBool());
            break;
        case MinimizeOnClose:
            fMinimizeOnClose = value.toBool();
            settings.setValue("fMinimizeOnClose", fMinimizeOnClose);
            break;

        // default proxy
        case ProxyUse:
            if (settings.value("fUseProxy") != value) {
                settings.setValue("fUseProxy", value.toBool());
                setRestartRequired(true);
            }
            break;
        case ProxyIP: {
            // contains current IP at index 0 and current port at index 1
            QStringList strlIpPort = settings.value("addrProxy").toString().split(":", QString::SkipEmptyParts);
            // if that key doesn't exist or has a changed IP
            if (!settings.contains("addrProxy") || strlIpPort.at(0) != value.toString()) {
                // construct new value from new IP and current port
                QString strNewValue = value.toString() + ":" + strlIpPort.at(1);
                settings.setValue("addrProxy", strNewValue);
                setRestartRequired(true);
            }
<<<<<<< HEAD
        }
        break;
=======
        } break;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        case ProxyPort: {
            // contains current IP at index 0 and current port at index 1
            QStringList strlIpPort = settings.value("addrProxy").toString().split(":", QString::SkipEmptyParts);
            // if that key doesn't exist or has a changed port
            if (!settings.contains("addrProxy") || strlIpPort.at(1) != value.toString()) {
                // construct new value from current IP and new port
                QString strNewValue = strlIpPort.at(0) + ":" + value.toString();
                settings.setValue("addrProxy", strNewValue);
                setRestartRequired(true);
            }
<<<<<<< HEAD
        }
        break;

        // separate Tor proxy
        case ProxyUseTor:
            if (settings.value("fUseSeparateProxyTor") != value) {
                settings.setValue("fUseSeparateProxyTor", value.toBool());
                setRestartRequired(true);
            }
            break;
        case ProxyIPTor: {
            // contains current IP at index 0 and current port at index 1
            QStringList strlIpPort = settings.value("addrSeparateProxyTor").toString().split(":", QString::SkipEmptyParts);
            // if that key doesn't exist or has a changed IP
            if (!settings.contains("addrSeparateProxyTor") || strlIpPort.at(0) != value.toString()) {
                // construct new value from new IP and current port
                QString strNewValue = value.toString() + ":" + strlIpPort.at(1);
                settings.setValue("addrSeparateProxyTor", strNewValue);
                setRestartRequired(true);
            }
        }
        break;
        case ProxyPortTor: {
            // contains current IP at index 0 and current port at index 1
            QStringList strlIpPort = settings.value("addrSeparateProxyTor").toString().split(":", QString::SkipEmptyParts);
            // if that key doesn't exist or has a changed port
            if (!settings.contains("addrSeparateProxyTor") || strlIpPort.at(1) != value.toString()) {
                // construct new value from current IP and new port
                QString strNewValue = strlIpPort.at(0) + ":" + value.toString();
                settings.setValue("addrSeparateProxyTor", strNewValue);
                setRestartRequired(true);
            }
        }
        break;

=======
        } break;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#ifdef ENABLE_WALLET
        case SpendZeroConfChange:
            if (settings.value("bSpendZeroConfChange") != value) {
                settings.setValue("bSpendZeroConfChange", value);
                setRestartRequired(true);
            }
            break;
        case ShowMasternodesTab:
            if (settings.value("fShowMasternodesTab") != value) {
                settings.setValue("fShowMasternodesTab", value);
                setRestartRequired(true);
            }
            break;
<<<<<<< HEAD
        case ShowAdvancedPSUI:
            fShowAdvancedPSUI = value.toBool();
            settings.setValue("fShowAdvancedPSUI", fShowAdvancedPSUI);
            Q_EMIT advancedPSUIChanged(fShowAdvancedPSUI);
            break;
        case LowKeysWarning:
            settings.setValue("fLowKeysWarning", value);
            break;
        case PrivateSendRounds:
            if (settings.value("nPrivateSendRounds") != value)
            {
                privateSendClient.nPrivateSendRounds = value.toInt();
                settings.setValue("nPrivateSendRounds", privateSendClient.nPrivateSendRounds);
                Q_EMIT privateSendRoundsChanged();
            }
            break;
        case PrivateSendAmount:
            if (settings.value("nPrivateSendAmount") != value)
            {
                privateSendClient.nPrivateSendAmount = value.toInt();
                settings.setValue("nPrivateSendAmount", privateSendClient.nPrivateSendAmount);
                Q_EMIT privateSentAmountChanged();
            }
            break;
        case PrivateSendMultiSession:
            if (settings.value("fPrivateSendMultiSession") != value)
            {
                privateSendClient.fPrivateSendMultiSession = value.toBool();
                settings.setValue("fPrivateSendMultiSession", privateSendClient.fPrivateSendMultiSession);
            }
            break;
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#endif
        case DisplayUnit:
            setDisplayUnit(value);
            break;
        case ThirdPartyTxUrls:
            if (strThirdPartyTxUrls != value.toString()) {
                strThirdPartyTxUrls = value.toString();
                settings.setValue("strThirdPartyTxUrls", strThirdPartyTxUrls);
                setRestartRequired(true);
            }
            break;
<<<<<<< HEAD
#ifdef ENABLE_WALLET
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        case Digits:
            if (settings.value("digits") != value) {
                settings.setValue("digits", value);
                setRestartRequired(true);
            }
<<<<<<< HEAD
            break;            
#endif // ENABLE_WALLET
=======
            break;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        case Theme:
            if (settings.value("theme") != value) {
                settings.setValue("theme", value);
                setRestartRequired(true);
            }
<<<<<<< HEAD
            break;            
=======
            break;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        case Language:
            if (settings.value("language") != value) {
                settings.setValue("language", value);
                setRestartRequired(true);
            }
            break;
<<<<<<< HEAD
#ifdef ENABLE_WALLET
        case CoinControlFeatures:
            fCoinControlFeatures = value.toBool();
            settings.setValue("fCoinControlFeatures", fCoinControlFeatures);
            Q_EMIT coinControlFeaturesChanged(fCoinControlFeatures);
            break;
#endif // ENABLE_WALLET
=======
        case DarksendRounds:
            nDarksendRounds = value.toInt();
            settings.setValue("nDarksendRounds", nDarksendRounds);
            emit obfuscationRoundsChanged(nDarksendRounds);
            break;
        case AnonymizeLuxAmount:
            nAnonymizeLuxAmount = value.toInt();
            settings.setValue("nAnonymizeLuxAmount", nAnonymizeLuxAmount);
            emit anonymizeLuxAmountChanged(nAnonymizeLuxAmount);
            break;
        case CoinControlFeatures:
            fCoinControlFeatures = value.toBool();
            settings.setValue("fCoinControlFeatures", fCoinControlFeatures);
            emit coinControlFeaturesChanged(fCoinControlFeatures);
            break;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        case DatabaseCache:
            if (settings.value("nDatabaseCache") != value) {
                settings.setValue("nDatabaseCache", value);
                setRestartRequired(true);
            }
            break;
        case ThreadsScriptVerif:
            if (settings.value("nThreadsScriptVerif") != value) {
                settings.setValue("nThreadsScriptVerif", value);
                setRestartRequired(true);
            }
            break;
        case Listen:
            if (settings.value("fListen") != value) {
                settings.setValue("fListen", value);
                setRestartRequired(true);
            }
            break;
        default:
            break;
        }
    }

<<<<<<< HEAD
    Q_EMIT dataChanged(index, index);
=======
    emit dataChanged(index, index);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    return successful;
}

/** Updates current unit in memory, settings and emits displayUnitChanged(newUnit) signal */
<<<<<<< HEAD
void OptionsModel::setDisplayUnit(const QVariant &value)
{
    if (!value.isNull())
    {
        QSettings settings;
        nDisplayUnit = value.toInt();
        settings.setValue("nDisplayUnit", nDisplayUnit);
        Q_EMIT displayUnitChanged(nDisplayUnit);
=======
void OptionsModel::setDisplayUnit(const QVariant& value)
{
    if (!value.isNull()) {
        QSettings settings;
        nDisplayUnit = value.toInt();
        settings.setValue("nDisplayUnit", nDisplayUnit);
        emit displayUnitChanged(nDisplayUnit);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }
}

bool OptionsModel::getProxySettings(QNetworkProxy& proxy) const
{
    // Directly query current base proxy, because
    // GUI settings can be overridden with -proxy.
    proxyType curProxy;
    if (GetProxy(NET_IPV4, curProxy)) {
        proxy.setType(QNetworkProxy::Socks5Proxy);
<<<<<<< HEAD
        proxy.setHostName(QString::fromStdString(curProxy.proxy.ToStringIP()));
        proxy.setPort(curProxy.proxy.GetPort());

        return true;
    }
    else
=======
        proxy.setHostName(QString::fromStdString(curProxy.ToStringIP()));
        proxy.setPort(curProxy.GetPort());

        return true;
    } else
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        proxy.setType(QNetworkProxy::NoProxy);

    return false;
}

void OptionsModel::setRestartRequired(bool fRequired)
{
    QSettings settings;
    return settings.setValue("fRestartRequired", fRequired);
}

bool OptionsModel::isRestartRequired()
{
    QSettings settings;
    return settings.value("fRestartRequired", false).toBool();
}
