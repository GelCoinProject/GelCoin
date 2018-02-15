<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2013 The Bitcoin developers       -*- c++ -*-
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_OPTIONSMODEL_H
#define BITCOIN_QT_OPTIONSMODEL_H

#include "amount.h"

#include <QAbstractListModel>

QT_BEGIN_NAMESPACE
class QNetworkProxy;
QT_END_NAMESPACE

/** Interface from Qt to configuration data structure for Bitcoin client.
   To Qt, the options are presented as a list with the different options
   laid out vertically.
   This can be changed to a tree once the settings become sufficiently
   complex.
 */
class OptionsModel : public QAbstractListModel
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit OptionsModel(QObject *parent = 0, bool resetSettings = false);

    enum OptionID {
        StartAtStartup,         // bool
        HideTrayIcon,           // bool
        MinimizeToTray,         // bool
        MapPortUPnP,            // bool
        MinimizeOnClose,        // bool
        ProxyUse,               // bool
        ProxyIP,                // QString
        ProxyPort,              // int
        ProxyUseTor,            // bool
        ProxyIPTor,             // QString
        ProxyPortTor,           // int
        DisplayUnit,            // BitcoinUnits::Unit
        ThirdPartyTxUrls,       // QString
        Digits,                 // QString
        Theme,                  // QString
        Language,               // QString
        CoinControlFeatures,    // bool
        ThreadsScriptVerif,     // int
        DatabaseCache,          // int
        SpendZeroConfChange,    // bool
        ShowMasternodesTab,     // bool
        ShowAdvancedPSUI,       // bool
        LowKeysWarning,         // bool
        PrivateSendRounds,      // int
        PrivateSendAmount,      // int
        PrivateSendMultiSession,// bool
        Listen,                 // bool
        OptionIDRowCount,
    };

    void Init(bool resetSettings = false);
    void Reset();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    /** Updates current unit in memory, settings and emits displayUnitChanged(newUnit) signal */
    void setDisplayUnit(const QVariant &value);

    /* Explicit getters */
    bool getHideTrayIcon() { return fHideTrayIcon; }
=======
    explicit OptionsModel(QObject* parent = 0);

    enum OptionID {
        StartAtStartup,      // bool
        MinimizeToTray,      // bool
        MapPortUPnP,         // bool
        MinimizeOnClose,     // bool
        ProxyUse,            // bool
        ProxyIP,             // QString
        ProxyPort,           // int
        DisplayUnit,         // BitcoinUnits::Unit
        ThirdPartyTxUrls,    // QString
        Digits,              // QString
        Theme,               // QString
        Language,            // QString
        CoinControlFeatures, // bool
        ThreadsScriptVerif,  // int
        DatabaseCache,       // int
        SpendZeroConfChange, // bool
        DarksendRounds,      // int
        AnonymizeLuxAmount,  //int
        ShowMasternodesTab,  // bool
        Listen,              // bool
        OptionIDRowCount,
    };

    void Init();
    void Reset();

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
    /** Updates current unit in memory, settings and emits displayUnitChanged(newUnit) signal */
    void setDisplayUnit(const QVariant& value);

    /* Explicit getters */
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    bool getMinimizeToTray() { return fMinimizeToTray; }
    bool getMinimizeOnClose() { return fMinimizeOnClose; }
    int getDisplayUnit() { return nDisplayUnit; }
    QString getThirdPartyTxUrls() { return strThirdPartyTxUrls; }
    bool getProxySettings(QNetworkProxy& proxy) const;
    bool getCoinControlFeatures() { return fCoinControlFeatures; }
<<<<<<< HEAD
    bool getShowAdvancedPSUI() { return fShowAdvancedPSUI; }
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    const QString& getOverriddenByCommandLine() { return strOverriddenByCommandLine; }

    /* Restart flag helper */
    void setRestartRequired(bool fRequired);
    bool isRestartRequired();
    bool resetSettings;

private:
    /* Qt-only settings */
<<<<<<< HEAD
    bool fHideTrayIcon;
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    bool fMinimizeToTray;
    bool fMinimizeOnClose;
    QString language;
    int nDisplayUnit;
    QString strThirdPartyTxUrls;
    bool fCoinControlFeatures;
<<<<<<< HEAD
    bool fShowAdvancedPSUI;
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    /* settings that were overriden by command-line */
    QString strOverriddenByCommandLine;

    /// Add option to list of GUI options overridden through command line/config file
<<<<<<< HEAD
    void addOverriddenOption(const std::string &option);

Q_SIGNALS:
    void displayUnitChanged(int unit);
    void privateSendRoundsChanged();
    void privateSentAmountChanged();
    void advancedPSUIChanged(bool);
    void coinControlFeaturesChanged(bool);
    void hideTrayIconChanged(bool);
=======
    void addOverriddenOption(const std::string& option);

signals:
    void displayUnitChanged(int unit);
    void obfuscationRoundsChanged(int);
    void anonymizeLuxAmountChanged(int);
    void coinControlFeaturesChanged(bool);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};

#endif // BITCOIN_QT_OPTIONSMODEL_H
