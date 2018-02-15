<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Copyright (c) 2014-2017 The GelCoin developers
// Distributed under the MIT software license, see the accompanying
=======
// Copyright (c) 2011-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The LUX developers
// Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_CLIENTMODEL_H
#define BITCOIN_QT_CLIENTMODEL_H

#include <QObject>
<<<<<<< HEAD
#include <QDateTime>

#include <atomic>

class AddressTableModel;
class BanTableModel;
=======

class AddressTableModel;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
class OptionsModel;
class PeerTableModel;
class TransactionTableModel;

class CWallet;
<<<<<<< HEAD
class CBlockIndex;

QT_BEGIN_NAMESPACE
=======

QT_BEGIN_NAMESPACE
class QDateTime;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
class QTimer;
QT_END_NAMESPACE

enum BlockSource {
    BLOCK_SOURCE_NONE,
    BLOCK_SOURCE_REINDEX,
    BLOCK_SOURCE_DISK,
    BLOCK_SOURCE_NETWORK
};

enum NumConnections {
    CONNECTIONS_NONE = 0,
<<<<<<< HEAD
    CONNECTIONS_IN   = (1U << 0),
    CONNECTIONS_OUT  = (1U << 1),
    CONNECTIONS_ALL  = (CONNECTIONS_IN | CONNECTIONS_OUT),
};

/** Model for GelCoin network client. */
=======
    CONNECTIONS_IN = (1U << 0),
    CONNECTIONS_OUT = (1U << 1),
    CONNECTIONS_ALL = (CONNECTIONS_IN | CONNECTIONS_OUT),
};

/** Model for LUX network client. */
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
class ClientModel : public QObject
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit ClientModel(OptionsModel *optionsModel, QObject *parent = 0);
    ~ClientModel();

    OptionsModel *getOptionsModel();
    PeerTableModel *getPeerTableModel();
    BanTableModel *getBanTableModel();

    //! Return number of connections, default is in- and outbound (total)
    int getNumConnections(unsigned int flags = CONNECTIONS_ALL) const;
    QString getMasternodeCountString() const;
    int getNumBlocks() const;
    int getHeaderTipHeight() const;
    int64_t getHeaderTipTime() const;
    //! Return number of transactions in the mempool
    long getMempoolSize() const;
    //! Return the dynamic memory usage of the mempool
    size_t getMempoolDynamicUsage() const;
    
    quint64 getTotalBytesRecv() const;
    quint64 getTotalBytesSent() const;

    double getVerificationProgress(const CBlockIndex *tip) const;
=======
    explicit ClientModel(OptionsModel* optionsModel, QObject* parent = 0);
    ~ClientModel();

    OptionsModel* getOptionsModel();
    PeerTableModel* getPeerTableModel();

    //! Return number of connections, default is in- and outbound (total)
    int getNumConnections(unsigned int flags = CONNECTIONS_ALL) const;
    int getNumBlocks() const;
    int getNumBlocksAtStartup();

    quint64 getTotalBytesRecv() const;
    quint64 getTotalBytesSent() const;

    double getVerificationProgress() const;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    QDateTime getLastBlockDate() const;

    //! Return true if core is doing initial block download
    bool inInitialBlockDownload() const;
<<<<<<< HEAD
    //! Returns enum BlockSource of the current importing/syncing state
    enum BlockSource getBlockSource() const;
    //! Return true if network activity in core is enabled
    bool getNetworkActive() const;
    //! Toggle network activity state in core
    void setNetworkActive(bool active);
=======
    //! Return true if core is importing blocks
    enum BlockSource getBlockSource() const;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    //! Return warnings to be displayed in status bar
    QString getStatusBarWarnings() const;

    QString formatFullVersion() const;
<<<<<<< HEAD
    QString formatSubVersion() const;
    bool isReleaseVersion() const;
    QString clientName() const;
    QString formatClientStartupTime() const;
    QString dataDir() const;

    // caches for the best header
    mutable std::atomic<int> cachedBestHeaderHeight;
    mutable std::atomic<int64_t> cachedBestHeaderTime;

private:
    OptionsModel *optionsModel;
    PeerTableModel *peerTableModel;
    QString cachedMasternodeCountString;
    BanTableModel *banTableModel;

    QTimer *pollTimer;
    QTimer *pollMnTimer;
=======
    QString formatBuildDate() const;
    bool isReleaseVersion() const;
    QString clientName() const;
    QString formatClientStartupTime() const;

private:
    OptionsModel* optionsModel;
    PeerTableModel* peerTableModel;

    int cachedNumBlocks;
    QString cachedMasternodeCountString;
    bool cachedReindexing;
    bool cachedImporting;

    int numBlocksAtStartup;

    QTimer* pollTimer;
    QTimer* pollMnTimer;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    void subscribeToCoreSignals();
    void unsubscribeFromCoreSignals();

<<<<<<< HEAD
Q_SIGNALS:
    void numConnectionsChanged(int count);
    void strMasternodesChanged(const QString &strMasternodes);
    void numBlocksChanged(int count, const QDateTime& blockDate, double nVerificationProgress, bool header);
    void additionalDataSyncProgressChanged(double nSyncProgress);
    void mempoolSizeChanged(long count, size_t mempoolSizeInBytes);
    void networkActiveChanged(bool networkActive);
    void alertsChanged(const QString &warnings);
    void bytesChanged(quint64 totalBytesIn, quint64 totalBytesOut);

    //! Fired when a message should be reported to the user
    void message(const QString &title, const QString &message, unsigned int style);

    // Show progress dialog e.g. for verifychain
    void showProgress(const QString &title, int nProgress);

public Q_SLOTS:
    void updateTimer();
    void updateMnTimer();
    void updateNumConnections(int numConnections);
    void updateNetworkActive(bool networkActive);
    void updateAlert(const QString &hash, int status);
    void updateBanlist();
=======
signals:
    void numConnectionsChanged(int count);
    void numBlocksChanged(int count);
    void strMasternodesChanged(const QString& strMasternodes);
    void alertsChanged(const QString& warnings);
    void bytesChanged(quint64 totalBytesIn, quint64 totalBytesOut);

    //! Fired when a message should be reported to the user
    void message(const QString& title, const QString& message, unsigned int style);

    // Show progress dialog e.g. for verifychain
    void showProgress(const QString& title, int nProgress);

public slots:
    void updateTimer();
    void updateMnTimer();
    void updateNumConnections(int numConnections);
    void updateAlert(const QString& hash, int status);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};

#endif // BITCOIN_QT_CLIENTMODEL_H
