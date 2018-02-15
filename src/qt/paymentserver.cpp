<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
// Copyright (c) 2014-2017 The GelCoin developers
=======
// Copyright (c) 2011-2014 The Bitcoin developers
// Copyright (c) 2017 The lux developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "paymentserver.h"

#include "bitcoinunits.h"
#include "guiutil.h"
#include "optionsmodel.h"

#include "base58.h"
#include "chainparams.h"
<<<<<<< HEAD
#include "validation.h" // For minRelayTxFee
#include "ui_interface.h"
#include "util.h"
#include "wallet/wallet.h"

#include <cstdlib>

=======
#include "ui_interface.h"
#include "util.h"
#include "wallet.h"

#include <cstdlib>

#include <openssl/x509.h>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include <openssl/x509_vfy.h>

#include <QApplication>
#include <QByteArray>
#include <QDataStream>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QFileOpenEvent>
#include <QHash>
#include <QList>
#include <QLocalServer>
#include <QLocalSocket>
#include <QNetworkAccessManager>
#include <QNetworkProxy>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSslCertificate>
#include <QSslError>
#include <QSslSocket>
#include <QStringList>
#include <QTextDocument>

#if QT_VERSION < 0x050000
#include <QUrl>
#else
#include <QUrlQuery>
#endif

<<<<<<< HEAD
const int BITCOIN_IPC_CONNECT_TIMEOUT = 1000; // milliseconds
const QString BITCOIN_IPC_PREFIX("gelcoin:");
=======
using namespace boost;
using namespace std;

const int BITCOIN_IPC_CONNECT_TIMEOUT = 1000; // milliseconds
const QString BITCOIN_IPC_PREFIX("lux:");
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// BIP70 payment protocol messages
const char* BIP70_MESSAGE_PAYMENTACK = "PaymentACK";
const char* BIP70_MESSAGE_PAYMENTREQUEST = "PaymentRequest";
// BIP71 payment protocol media types
<<<<<<< HEAD
const char* BIP71_MIMETYPE_PAYMENT = "application/gelcoin-payment";
const char* BIP71_MIMETYPE_PAYMENTACK = "application/gelcoin-paymentack";
const char* BIP71_MIMETYPE_PAYMENTREQUEST = "application/gelcoin-paymentrequest";
=======
const char* BIP71_MIMETYPE_PAYMENT = "application/lux-payment";
const char* BIP71_MIMETYPE_PAYMENTACK = "application/lux-paymentack";
const char* BIP71_MIMETYPE_PAYMENTREQUEST = "application/lux-paymentrequest";
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// BIP70 max payment request size in bytes (DoS protection)
const qint64 BIP70_MAX_PAYMENTREQUEST_SIZE = 50000;

struct X509StoreDeleter {
      void operator()(X509_STORE* b) {
          X509_STORE_free(b);
      }
};

struct X509Deleter {
      void operator()(X509* b) { X509_free(b); }
};

namespace // Anon namespace
{
<<<<<<< HEAD
=======

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    std::unique_ptr<X509_STORE, X509StoreDeleter> certStore;
}

//
// Create a name that is unique for:
//  testnet / non-testnet
//  data directory
//
static QString ipcServerName()
{
<<<<<<< HEAD
    QString name("GelCoinQt");
=======
    QString name("luxQt");
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    // Append a simple hash of the datadir
    // Note that GetDataDir(true) returns a different path
    // for -testnet versus main net
    QString ddir(QString::fromStdString(GetDataDir(true).string()));
    name.append(QString::number(qHash(ddir)));

    return name;
}

//
// We store payment URIs and requests received before
// the main GUI window is up and ready to ask the user
// to send payment.

static QList<QString> savedPaymentRequests;

static void ReportInvalidCertificate(const QSslCertificate& cert)
{
<<<<<<< HEAD
#if QT_VERSION < 0x050000
    qDebug() << QString("%1: Payment server found an invalid certificate: ").arg(__func__) << cert.serialNumber() << cert.subjectInfo(QSslCertificate::CommonName) << cert.subjectInfo(QSslCertificate::OrganizationalUnitName);
#else
    qDebug() << QString("%1: Payment server found an invalid certificate: ").arg(__func__) << cert.serialNumber() << cert.subjectInfo(QSslCertificate::CommonName) << cert.subjectInfo(QSslCertificate::DistinguishedNameQualifier) << cert.subjectInfo(QSslCertificate::OrganizationalUnitName);
#endif
=======
    qDebug() << "ReportInvalidCertificate : Payment server found an invalid certificate: " << cert.subjectInfo(QSslCertificate::CommonName);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

//
// Load OpenSSL's list of root certificate authorities
//
void PaymentServer::LoadRootCAs(X509_STORE* _store)
{
    // Unit tests mostly use this, to pass in fake root CAs:
<<<<<<< HEAD
    if (_store)
    {
=======
    if (_store) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        certStore.reset(_store);
        return;
    }

    // Normal execution, use either -rootcertificates or system certs:
    certStore.reset(X509_STORE_new());

    // Note: use "-system-" default here so that users can pass -rootcertificates=""
    // and get 'I don't like X.509 certificates, don't trust anybody' behavior:
    QString certFile = QString::fromStdString(GetArg("-rootcertificates", "-system-"));

<<<<<<< HEAD
    // Empty store
    if (certFile.isEmpty()) {
        qDebug() << QString("PaymentServer::%1: Payment request authentication via X.509 certificates disabled.").arg(__func__);
        return;
    }
=======
    if (certFile.isEmpty())
        return; // Empty store
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    QList<QSslCertificate> certList;

    if (certFile != "-system-") {
<<<<<<< HEAD
            qDebug() << QString("PaymentServer::%1: Using \"%2\" as trusted root certificate.").arg(__func__).arg(certFile);

=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        certList = QSslCertificate::fromPath(certFile);
        // Use those certificates when fetching payment requests, too:
        QSslSocket::setDefaultCaCertificates(certList);
    } else
        certList = QSslSocket::systemCaCertificates();

    int nRootCerts = 0;
    const QDateTime currentTime = QDateTime::currentDateTime();
<<<<<<< HEAD

    Q_FOREACH (const QSslCertificate& cert, certList) {
        // Don't log NULL certificates
        if (cert.isNull())
            continue;

        // Not yet active/valid, or expired certificate
=======
    foreach (const QSslCertificate& cert, certList) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        if (currentTime < cert.effectiveDate() || currentTime > cert.expiryDate()) {
            ReportInvalidCertificate(cert);
            continue;
        }
<<<<<<< HEAD

#if QT_VERSION >= 0x050000
        // Blacklisted certificate
=======
#if QT_VERSION >= 0x050000
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        if (cert.isBlacklisted()) {
            ReportInvalidCertificate(cert);
            continue;
        }
#endif
        QByteArray certData = cert.toDer();
<<<<<<< HEAD
        const unsigned char *data = (const unsigned char *)certData.data();

        std::unique_ptr<X509, X509Deleter> x509(d2i_X509(0, &data, certData.size()));
        if (x509 && X509_STORE_add_cert(certStore.get(), x509.get()))
        {
            // Note: X509_STORE increases the reference count to the X509 object,
            // we still have to release our reference to it.
            ++nRootCerts;
        }
        else
        {
=======
        const unsigned char* data = (const unsigned char*)certData.data();

        std::unique_ptr<X509, X509Deleter> x509(d2i_X509(0, &data, certData.size()));
        if (x509 && X509_STORE_add_cert(certStore.get(), x509.get())) {
            // Note: X509_STORE increases the reference count to the X509 object,
            // we still have to release our reference to it.
            ++nRootCerts;
        } else {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            ReportInvalidCertificate(cert);
            continue;
        }
    }
<<<<<<< HEAD
    qWarning() << "PaymentServer::LoadRootCAs: Loaded " << nRootCerts << " root certificates";
=======
    qWarning() << "PaymentServer::LoadRootCAs : Loaded " << nRootCerts << " root certificates";
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    // Project for another day:
    // Fetch certificate revocation lists, and add them to certStore.
    // Issues to consider:
    //   performance (start a thread to fetch in background?)
    //   privacy (fetch through tor/proxy so IP address isn't revealed)
    //   would it be easier to just use a compiled-in blacklist?
    //    or use Qt's blacklist?
    //   "certificate stapling" with server-side caching is more efficient
}

//
// Sending to the server is done synchronously, at startup.
// If the server isn't already running, startup continues,
// and the items in savedPaymentRequest will be handled
// when uiReady() is called.
//
// Warning: ipcSendCommandLine() is called early in init,
<<<<<<< HEAD
// so don't use "Q_EMIT message()", but "QMessageBox::"!
//
void PaymentServer::ipcParseCommandLine(int argc, char* argv[])
{
    for (int i = 1; i < argc; i++)
    {
=======
// so don't use "emit message()", but "QMessageBox::"!
//
void PaymentServer::ipcParseCommandLine(int argc, char* argv[])
{
    for (int i = 1; i < argc; i++) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        QString arg(argv[i]);
        if (arg.startsWith("-"))
            continue;

<<<<<<< HEAD
        // If the gelcoin: URI contains a payment request, we are not able to detect the
        // network as that would require fetching and parsing the payment request.
        // That means clicking such an URI which contains a testnet payment request
        // will start a mainnet instance and throw a "wrong network" error.
        if (arg.startsWith(BITCOIN_IPC_PREFIX, Qt::CaseInsensitive)) // gelcoin: URI
=======
        // If the lux: URI contains a payment request, we are not able to detect the
        // network as that would require fetching and parsing the payment request.
        // That means clicking such an URI which contains a testnet payment request
        // will start a mainnet instance and throw a "wrong network" error.
        if (arg.startsWith(BITCOIN_IPC_PREFIX, Qt::CaseInsensitive)) // lux: URI
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        {
            savedPaymentRequests.append(arg);

            SendCoinsRecipient r;
<<<<<<< HEAD
            if (GUIUtil::parseBitcoinURI(arg, &r) && !r.address.isEmpty())
            {
                CBitcoinAddress address(r.address.toStdString());

                if (address.IsValid(Params(CBaseChainParams::MAIN)))
                {
                    SelectParams(CBaseChainParams::MAIN);
                }
                else if (address.IsValid(Params(CBaseChainParams::TESTNET)))
                {
                    SelectParams(CBaseChainParams::TESTNET);
                }
            }
        }
        else if (QFile::exists(arg)) // Filename
=======
            if (GUIUtil::parseBitcoinURI(arg, &r) && !r.address.isEmpty()) {
                CBitcoinAddress address(r.address.toStdString());

                if (address.IsValid(Params(CBaseChainParams::MAIN))) {
                    SelectParams(CBaseChainParams::MAIN);
                } else if (address.IsValid(Params(CBaseChainParams::TESTNET))) {
                    SelectParams(CBaseChainParams::TESTNET);
                }
            }
        } else if (QFile::exists(arg)) // Filename
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        {
            savedPaymentRequests.append(arg);

            PaymentRequestPlus request;
<<<<<<< HEAD
            if (readPaymentRequestFromFile(arg, request))
            {
                if (request.getDetails().network() == "main")
                {
                    SelectParams(CBaseChainParams::MAIN);
                }
                else if (request.getDetails().network() == "test")
                {
                    SelectParams(CBaseChainParams::TESTNET);
                }
            }
        }
        else
        {
            // Printing to debug.log is about the best we can do here, the
            // GUI hasn't started yet so we can't pop up a message box.
            qWarning() << "PaymentServer::ipcSendCommandLine: Payment request file does not exist: " << arg;
=======
            if (readPaymentRequestFromFile(arg, request)) {
                if (request.getDetails().network() == "main") {
                    SelectParams(CBaseChainParams::MAIN);
                } else if (request.getDetails().network() == "test") {
                    SelectParams(CBaseChainParams::TESTNET);
                }
            }
        } else {
            // Printing to debug.log is about the best we can do here, the
            // GUI hasn't started yet so we can't pop up a message box.
            qWarning() << "PaymentServer::ipcSendCommandLine : Payment request file does not exist: " << arg;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        }
    }
}

//
// Sending to the server is done synchronously, at startup.
// If the server isn't already running, startup continues,
// and the items in savedPaymentRequest will be handled
// when uiReady() is called.
//
bool PaymentServer::ipcSendCommandLine()
{
    bool fResult = false;
<<<<<<< HEAD
    Q_FOREACH (const QString& r, savedPaymentRequests)
    {
        QLocalSocket* socket = new QLocalSocket();
        socket->connectToServer(ipcServerName(), QIODevice::WriteOnly);
        if (!socket->waitForConnected(BITCOIN_IPC_CONNECT_TIMEOUT))
        {
=======
    foreach (const QString& r, savedPaymentRequests) {
        QLocalSocket* socket = new QLocalSocket();
        socket->connectToServer(ipcServerName(), QIODevice::WriteOnly);
        if (!socket->waitForConnected(BITCOIN_IPC_CONNECT_TIMEOUT)) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            delete socket;
            socket = NULL;
            return false;
        }

        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_0);
        out << r;
        out.device()->seek(0);

        socket->write(block);
        socket->flush();
        socket->waitForBytesWritten(BITCOIN_IPC_CONNECT_TIMEOUT);
        socket->disconnectFromServer();

        delete socket;
        socket = NULL;
        fResult = true;
    }

    return fResult;
}

<<<<<<< HEAD
PaymentServer::PaymentServer(QObject* parent, bool startLocalServer) :
    QObject(parent),
    saveURIs(true),
    uriServer(0),
    netManager(0),
    optionsModel(0)
=======
PaymentServer::PaymentServer(QObject* parent, bool startLocalServer) : QObject(parent),
                                                                       saveURIs(true),
                                                                       uriServer(0),
                                                                       netManager(0),
                                                                       optionsModel(0)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    // Install global event filter to catch QFileOpenEvents
<<<<<<< HEAD
    // on Mac: sent when you click gelcoin: links
    // other OSes: helpful when dealing with payment request files
=======
    // on Mac: sent when you click lux: links
    // other OSes: helpful when dealing with payment request files (in the future)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    if (parent)
        parent->installEventFilter(this);

    QString name = ipcServerName();

    // Clean up old socket leftover from a crash:
    QLocalServer::removeServer(name);

<<<<<<< HEAD
    if (startLocalServer)
    {
        uriServer = new QLocalServer(this);

        if (!uriServer->listen(name)) {
            // constructor is called early in init, so don't use "Q_EMIT message()" here
            QMessageBox::critical(0, tr("Payment request error"),
                tr("Cannot start gelcoin: click-to-pay handler"));
        }
        else {
=======
    if (startLocalServer) {
        uriServer = new QLocalServer(this);

        if (!uriServer->listen(name)) {
            // constructor is called early in init, so don't use "emit message()" here
            QMessageBox::critical(0, tr("Payment request error"),
                tr("Cannot start lux: click-to-pay handler"));
        } else {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            connect(uriServer, SIGNAL(newConnection()), this, SLOT(handleURIConnection()));
            connect(this, SIGNAL(receivedPaymentACK(QString)), this, SLOT(handlePaymentACK(QString)));
        }
    }
}

PaymentServer::~PaymentServer()
{
    google::protobuf::ShutdownProtobufLibrary();
}

//
<<<<<<< HEAD
// OSX-specific way of handling gelcoin: URIs and PaymentRequest mime types.
// Also used by paymentservertests.cpp and when opening a payment request file
// via "Open URI..." menu entry.
//
bool PaymentServer::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::FileOpen) {
        QFileOpenEvent *fileEvent = static_cast<QFileOpenEvent*>(event);
=======
// OSX-specific way of handling lux: URIs and
// PaymentRequest mime types
//
bool PaymentServer::eventFilter(QObject* object, QEvent* event)
{
    // clicking on lux: URIs creates FileOpen events on the Mac
    if (event->type() == QEvent::FileOpen) {
        QFileOpenEvent* fileEvent = static_cast<QFileOpenEvent*>(event);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        if (!fileEvent->file().isEmpty())
            handleURIOrFile(fileEvent->file());
        else if (!fileEvent->url().isEmpty())
            handleURIOrFile(fileEvent->url().toString());

        return true;
    }

    return QObject::eventFilter(object, event);
}

void PaymentServer::initNetManager()
{
    if (!optionsModel)
        return;
    if (netManager != NULL)
        delete netManager;

<<<<<<< HEAD
    // netManager is used to fetch paymentrequests given in gelcoin: URIs
=======
    // netManager is used to fetch paymentrequests given in lux: URIs
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    netManager = new QNetworkAccessManager(this);

    QNetworkProxy proxy;

    // Query active SOCKS5 proxy
    if (optionsModel->getProxySettings(proxy)) {
        netManager->setProxy(proxy);

<<<<<<< HEAD
        qDebug() << "PaymentServer::initNetManager: Using SOCKS5 proxy" << proxy.hostName() << ":" << proxy.port();
    }
    else
        qDebug() << "PaymentServer::initNetManager: No active proxy server found.";

    connect(netManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(netRequestFinished(QNetworkReply*)));
    connect(netManager, SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError> &)),
            this, SLOT(reportSslErrors(QNetworkReply*, const QList<QSslError> &)));
=======
        qDebug() << "PaymentServer::initNetManager : Using SOCKS5 proxy" << proxy.hostName() << ":" << proxy.port();
    } else
        qDebug() << "PaymentServer::initNetManager : No active proxy server found.";

    connect(netManager, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(netRequestFinished(QNetworkReply*)));
    connect(netManager, SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError>&)),
        this, SLOT(reportSslErrors(QNetworkReply*, const QList<QSslError>&)));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

void PaymentServer::uiReady()
{
    initNetManager();

    saveURIs = false;
<<<<<<< HEAD
    Q_FOREACH (const QString& s, savedPaymentRequests)
    {
=======
    foreach (const QString& s, savedPaymentRequests) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        handleURIOrFile(s);
    }
    savedPaymentRequests.clear();
}

void PaymentServer::handleURIOrFile(const QString& s)
{
<<<<<<< HEAD
    if (saveURIs)
    {
=======
    if (saveURIs) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        savedPaymentRequests.append(s);
        return;
    }

<<<<<<< HEAD
    if (s.startsWith(BITCOIN_IPC_PREFIX, Qt::CaseInsensitive)) // gelcoin: URI
=======
    if (s.startsWith(BITCOIN_IPC_PREFIX, Qt::CaseInsensitive)) // lux: URI
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    {
#if QT_VERSION < 0x050000
        QUrl uri(s);
#else
        QUrlQuery uri((QUrl(s)));
#endif
        if (uri.hasQueryItem("r")) // payment request URI
        {
            QByteArray temp;
            temp.append(uri.queryItemValue("r"));
            QString decoded = QUrl::fromPercentEncoding(temp);
            QUrl fetchUrl(decoded, QUrl::StrictMode);

<<<<<<< HEAD
            if (fetchUrl.isValid())
            {
                qDebug() << "PaymentServer::handleURIOrFile: fetchRequest(" << fetchUrl << ")";
                fetchRequest(fetchUrl);
            }
            else
            {
                qWarning() << "PaymentServer::handleURIOrFile: Invalid URL: " << fetchUrl;
                Q_EMIT message(tr("URI handling"),
=======
            if (fetchUrl.isValid()) {
                qDebug() << "PaymentServer::handleURIOrFile : fetchRequest(" << fetchUrl << ")";
                fetchRequest(fetchUrl);
            } else {
                qWarning() << "PaymentServer::handleURIOrFile : Invalid URL: " << fetchUrl;
                emit message(tr("URI handling"),
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                    tr("Payment request fetch URL is invalid: %1").arg(fetchUrl.toString()),
                    CClientUIInterface::ICON_WARNING);
            }

            return;
<<<<<<< HEAD
        }
        else // normal URI
        {
            SendCoinsRecipient recipient;
            if (GUIUtil::parseBitcoinURI(s, &recipient))
            {
                CBitcoinAddress address(recipient.address.toStdString());
                if (!address.IsValid()) {
                    Q_EMIT message(tr("URI handling"), tr("Invalid payment address %1").arg(recipient.address),
                        CClientUIInterface::MSG_ERROR);
                }
                else
                    Q_EMIT receivedPaymentRequest(recipient);
            }
            else
                Q_EMIT message(tr("URI handling"),
                    tr("URI cannot be parsed! This can be caused by an invalid GelCoin address or malformed URI parameters."),
=======
        } else // normal URI
        {
            SendCoinsRecipient recipient;
            if (GUIUtil::parseBitcoinURI(s, &recipient)) {
                CBitcoinAddress address(recipient.address.toStdString());
                if (!address.IsValid()) {
                    emit message(tr("URI handling"), tr("Invalid payment address %1").arg(recipient.address),
                        CClientUIInterface::MSG_ERROR);
                } else
                    emit receivedPaymentRequest(recipient);
            } else
                emit message(tr("URI handling"),
                    tr("URI cannot be parsed! This can be caused by an invalid lux address or malformed URI parameters."),
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                    CClientUIInterface::ICON_WARNING);

            return;
        }
    }

    if (QFile::exists(s)) // payment request file
    {
        PaymentRequestPlus request;
        SendCoinsRecipient recipient;
<<<<<<< HEAD
        if (!readPaymentRequestFromFile(s, request))
        {
            Q_EMIT message(tr("Payment request file handling"),
                tr("Payment request file cannot be read! This can be caused by an invalid payment request file."),
                CClientUIInterface::ICON_WARNING);
        }
        else if (processPaymentRequest(request, recipient))
            Q_EMIT receivedPaymentRequest(recipient);
=======
        if (!readPaymentRequestFromFile(s, request)) {
            emit message(tr("Payment request file handling"),
                tr("Payment request file cannot be read! This can be caused by an invalid payment request file."),
                CClientUIInterface::ICON_WARNING);
        } else if (processPaymentRequest(request, recipient))
            emit receivedPaymentRequest(recipient);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

        return;
    }
}

void PaymentServer::handleURIConnection()
{
<<<<<<< HEAD
    QLocalSocket *clientConnection = uriServer->nextPendingConnection();
=======
    QLocalSocket* clientConnection = uriServer->nextPendingConnection();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    while (clientConnection->bytesAvailable() < (int)sizeof(quint32))
        clientConnection->waitForReadyRead();

    connect(clientConnection, SIGNAL(disconnected()),
<<<<<<< HEAD
            clientConnection, SLOT(deleteLater()));
=======
        clientConnection, SLOT(deleteLater()));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    QDataStream in(clientConnection);
    in.setVersion(QDataStream::Qt_4_0);
    if (clientConnection->bytesAvailable() < (int)sizeof(quint16)) {
        return;
    }
    QString msg;
    in >> msg;

    handleURIOrFile(msg);
}

//
// Warning: readPaymentRequestFromFile() is used in ipcSendCommandLine()
<<<<<<< HEAD
// so don't use "Q_EMIT message()", but "QMessageBox::"!
=======
// so don't use "emit message()", but "QMessageBox::"!
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
//
bool PaymentServer::readPaymentRequestFromFile(const QString& filename, PaymentRequestPlus& request)
{
    QFile f(filename);
    if (!f.open(QIODevice::ReadOnly)) {
        qWarning() << QString("PaymentServer::%1: Failed to open %2").arg(__func__).arg(filename);
        return false;
    }

    // BIP70 DoS protection
<<<<<<< HEAD
    if (!verifySize(f.size())) {
=======
    if (f.size() > BIP70_MAX_PAYMENTREQUEST_SIZE) {
        qWarning() << QString("PaymentServer::%1: Payment request %2 is too large (%3 bytes, allowed %4 bytes).")
                          .arg(__func__)
                          .arg(filename)
                          .arg(f.size())
                          .arg(BIP70_MAX_PAYMENTREQUEST_SIZE);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return false;
    }

    QByteArray data = f.readAll();

    return request.parse(data);
}

<<<<<<< HEAD
bool PaymentServer::processPaymentRequest(const PaymentRequestPlus& request, SendCoinsRecipient& recipient)
=======
bool PaymentServer::processPaymentRequest(PaymentRequestPlus& request, SendCoinsRecipient& recipient)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    if (!optionsModel)
        return false;

    if (request.IsInitialized()) {
<<<<<<< HEAD
        // Payment request network matches client network?
        if (!verifyNetwork(request.getDetails())) {
            Q_EMIT message(tr("Payment request rejected"), tr("Payment request network doesn't match client network."),
=======
        const payments::PaymentDetails& details = request.getDetails();

        // Payment request network matches client network?
        if (details.network() != Params().NetworkIDString()) {
            emit message(tr("Payment request rejected"), tr("Payment request network doesn't match client network."),
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                CClientUIInterface::MSG_ERROR);

            return false;
        }

<<<<<<< HEAD
        // Make sure any payment requests involved are still valid.
        // This is re-checked just before sending coins in WalletModel::sendCoins().
        if (verifyExpired(request.getDetails())) {
            Q_EMIT message(tr("Payment request rejected"), tr("Payment request expired."),
=======
        // Expired payment request?
        if (details.has_expires() && (int64_t)details.expires() < GetTime()) {
            emit message(tr("Payment request rejected"), tr("Payment request has expired."),
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                CClientUIInterface::MSG_ERROR);

            return false;
        }
    } else {
<<<<<<< HEAD
        Q_EMIT message(tr("Payment request error"), tr("Payment request is not initialized."),
=======
        emit message(tr("Payment request error"), tr("Payment request is not initialized."),
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            CClientUIInterface::MSG_ERROR);

        return false;
    }

    recipient.paymentRequest = request;
    recipient.message = GUIUtil::HtmlEscape(request.getDetails().memo());

    request.getMerchant(certStore.get(), recipient.authenticatedMerchant);

    QList<std::pair<CScript, CAmount> > sendingTos = request.getPayTo();
    QStringList addresses;

<<<<<<< HEAD
    Q_FOREACH(const PAIRTYPE(CScript, CAmount)& sendingTo, sendingTos) {
=======
    foreach (const PAIRTYPE(CScript, CAmount) & sendingTo, sendingTos) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        // Extract and check destination addresses
        CTxDestination dest;
        if (ExtractDestination(sendingTo.first, dest)) {
            // Append destination address
            addresses.append(QString::fromStdString(CBitcoinAddress(dest).ToString()));
<<<<<<< HEAD
        }
        else if (!recipient.authenticatedMerchant.isEmpty()) {
            // Unauthenticated payment requests to custom gelcoin addresses are not supported
            // (there is no good way to tell the user where they are paying in a way they'd
            // have a chance of understanding).
            Q_EMIT message(tr("Payment request rejected"),
=======
        } else if (!recipient.authenticatedMerchant.isEmpty()) {
            // Insecure payments to custom lux addresses are not supported
            // (there is no good way to tell the user where they are paying in a way
            // they'd have a chance of understanding).
            emit message(tr("Payment request rejected"),
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                tr("Unverified payment requests to custom payment scripts are unsupported."),
                CClientUIInterface::MSG_ERROR);
            return false;
        }

<<<<<<< HEAD
        // GelCoin amounts are stored as (optional) uint64 in the protobuf messages (see paymentrequest.proto),
        // but CAmount is defined as int64_t. Because of that we need to verify that amounts are in a valid range
        // and no overflow has happened.
        if (!verifyAmount(sendingTo.second)) {
            Q_EMIT message(tr("Payment request rejected"), tr("Invalid payment request."), CClientUIInterface::MSG_ERROR);
            return false;
        }

        // Extract and check amounts
        CTxOut txOut(sendingTo.second, sendingTo.first);
        if (txOut.IsDust(::minRelayTxFee)) {
            Q_EMIT message(tr("Payment request error"), tr("Requested payment amount of %1 is too small (considered dust).")
                .arg(BitcoinUnits::formatWithUnit(optionsModel->getDisplayUnit(), sendingTo.second)),
=======
        // Extract and check amounts
        CTxOut txOut(sendingTo.second, sendingTo.first);
        if (txOut.IsDust(::minRelayTxFee)) {
            emit message(tr("Payment request error"), tr("Requested payment amount of %1 is too small (considered dust).").arg(BitcoinUnits::formatWithUnit(optionsModel->getDisplayUnit(), sendingTo.second)),
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                CClientUIInterface::MSG_ERROR);

            return false;
        }

        recipient.amount += sendingTo.second;
<<<<<<< HEAD
        // Also verify that the final amount is still in a valid range after adding additional amounts.
        if (!verifyAmount(recipient.amount)) {
            Q_EMIT message(tr("Payment request rejected"), tr("Invalid payment request."), CClientUIInterface::MSG_ERROR);
            return false;
        }
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }
    // Store addresses and format them to fit nicely into the GUI
    recipient.address = addresses.join("<br />");

    if (!recipient.authenticatedMerchant.isEmpty()) {
<<<<<<< HEAD
        qDebug() << "PaymentServer::processPaymentRequest: Secure payment request from " << recipient.authenticatedMerchant;
    }
    else {
        qDebug() << "PaymentServer::processPaymentRequest: Insecure payment request to " << addresses.join(", ");
=======
        qDebug() << "PaymentServer::processPaymentRequest : Secure payment request from " << recipient.authenticatedMerchant;
    } else {
        qDebug() << "PaymentServer::processPaymentRequest : Insecure payment request to " << addresses.join(", ");
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }

    return true;
}

void PaymentServer::fetchRequest(const QUrl& url)
{
    QNetworkRequest netRequest;
    netRequest.setAttribute(QNetworkRequest::User, BIP70_MESSAGE_PAYMENTREQUEST);
    netRequest.setUrl(url);
    netRequest.setRawHeader("User-Agent", CLIENT_NAME.c_str());
    netRequest.setRawHeader("Accept", BIP71_MIMETYPE_PAYMENTREQUEST);
    netManager->get(netRequest);
}

void PaymentServer::fetchPaymentACK(CWallet* wallet, SendCoinsRecipient recipient, QByteArray transaction)
{
    const payments::PaymentDetails& details = recipient.paymentRequest.getDetails();
    if (!details.has_payment_url())
        return;

    QNetworkRequest netRequest;
    netRequest.setAttribute(QNetworkRequest::User, BIP70_MESSAGE_PAYMENTACK);
    netRequest.setUrl(QString::fromStdString(details.payment_url()));
    netRequest.setHeader(QNetworkRequest::ContentTypeHeader, BIP71_MIMETYPE_PAYMENT);
    netRequest.setRawHeader("User-Agent", CLIENT_NAME.c_str());
    netRequest.setRawHeader("Accept", BIP71_MIMETYPE_PAYMENTACK);

    payments::Payment payment;
    payment.set_merchant_data(details.merchant_data());
    payment.add_transactions(transaction.data(), transaction.size());

    // Create a new refund address, or re-use:
    QString account = tr("Refund from %1").arg(recipient.authenticatedMerchant);
    std::string strAccount = account.toStdString();
<<<<<<< HEAD
    std::set<CTxDestination> refundAddresses = wallet->GetAccountAddresses(strAccount);
=======
    set<CTxDestination> refundAddresses = wallet->GetAccountAddresses(strAccount);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    if (!refundAddresses.empty()) {
        CScript s = GetScriptForDestination(*refundAddresses.begin());
        payments::Output* refund_to = payment.add_refund_to();
        refund_to->set_script(&s[0], s.size());
<<<<<<< HEAD
    }
    else {
        CPubKey newKey;
        if (wallet->GetKeyFromPool(newKey, false)) {
=======
    } else {
        CPubKey newKey;
        if (wallet->GetKeyFromPool(newKey)) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            CKeyID keyID = newKey.GetID();
            wallet->SetAddressBook(keyID, strAccount, "refund");

            CScript s = GetScriptForDestination(keyID);
            payments::Output* refund_to = payment.add_refund_to();
            refund_to->set_script(&s[0], s.size());
<<<<<<< HEAD
        }
        else {
            // This should never happen, because sending coins should have
            // just unlocked the wallet and refilled the keypool.
            qWarning() << "PaymentServer::fetchPaymentACK: Error getting refund key, refund_to not set";
=======
        } else {
            // This should never happen, because sending coins should have
            // just unlocked the wallet and refilled the keypool.
            qWarning() << "PaymentServer::fetchPaymentACK : Error getting refund key, refund_to not set";
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        }
    }

    int length = payment.ByteSize();
    netRequest.setHeader(QNetworkRequest::ContentLengthHeader, length);
    QByteArray serData(length, '\0');
    if (payment.SerializeToArray(serData.data(), length)) {
        netManager->post(netRequest, serData);
<<<<<<< HEAD
    }
    else {
        // This should never happen, either.
        qWarning() << "PaymentServer::fetchPaymentACK: Error serializing payment message";
=======
    } else {
        // This should never happen, either.
        qWarning() << "PaymentServer::fetchPaymentACK : Error serializing payment message";
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }
}

void PaymentServer::netRequestFinished(QNetworkReply* reply)
{
    reply->deleteLater();

    // BIP70 DoS protection
<<<<<<< HEAD
    if (!verifySize(reply->size())) {
        Q_EMIT message(tr("Payment request rejected"),
            tr("Payment request %1 is too large (%2 bytes, allowed %3 bytes).")
                .arg(reply->request().url().toString())
                .arg(reply->size())
                .arg(BIP70_MAX_PAYMENTREQUEST_SIZE),
            CClientUIInterface::MSG_ERROR);
=======
    if (reply->size() > BIP70_MAX_PAYMENTREQUEST_SIZE) {
        QString msg = tr("Payment request %1 is too large (%2 bytes, allowed %3 bytes).")
                          .arg(reply->request().url().toString())
                          .arg(reply->size())
                          .arg(BIP70_MAX_PAYMENTREQUEST_SIZE);

        qWarning() << QString("PaymentServer::%1:").arg(__func__) << msg;
        emit message(tr("Payment request DoS protection"), msg, CClientUIInterface::MSG_ERROR);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return;
    }

    if (reply->error() != QNetworkReply::NoError) {
        QString msg = tr("Error communicating with %1: %2")
<<<<<<< HEAD
            .arg(reply->request().url().toString())
            .arg(reply->errorString());

        qWarning() << "PaymentServer::netRequestFinished: " << msg;
        Q_EMIT message(tr("Payment request error"), msg, CClientUIInterface::MSG_ERROR);
=======
                          .arg(reply->request().url().toString())
                          .arg(reply->errorString());

        qWarning() << "PaymentServer::netRequestFinished: " << msg;
        emit message(tr("Payment request error"), msg, CClientUIInterface::MSG_ERROR);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return;
    }

    QByteArray data = reply->readAll();

    QString requestType = reply->request().attribute(QNetworkRequest::User).toString();
<<<<<<< HEAD
    if (requestType == BIP70_MESSAGE_PAYMENTREQUEST)
    {
        PaymentRequestPlus request;
        SendCoinsRecipient recipient;
        if (!request.parse(data))
        {
            qWarning() << "PaymentServer::netRequestFinished: Error parsing payment request";
            Q_EMIT message(tr("Payment request error"),
                tr("Payment request cannot be parsed!"),
                CClientUIInterface::MSG_ERROR);
        }
        else if (processPaymentRequest(request, recipient))
            Q_EMIT receivedPaymentRequest(recipient);

        return;
    }
    else if (requestType == BIP70_MESSAGE_PAYMENTACK)
    {
        payments::PaymentACK paymentACK;
        if (!paymentACK.ParseFromArray(data.data(), data.size()))
        {
            QString msg = tr("Bad response from server %1")
                .arg(reply->request().url().toString());

            qWarning() << "PaymentServer::netRequestFinished: " << msg;
            Q_EMIT message(tr("Payment request error"), msg, CClientUIInterface::MSG_ERROR);
        }
        else
        {
            Q_EMIT receivedPaymentACK(GUIUtil::HtmlEscape(paymentACK.memo()));
=======
    if (requestType == BIP70_MESSAGE_PAYMENTREQUEST) {
        PaymentRequestPlus request;
        SendCoinsRecipient recipient;
        if (!request.parse(data)) {
            qWarning() << "PaymentServer::netRequestFinished : Error parsing payment request";
            emit message(tr("Payment request error"),
                tr("Payment request cannot be parsed!"),
                CClientUIInterface::MSG_ERROR);
        } else if (processPaymentRequest(request, recipient))
            emit receivedPaymentRequest(recipient);

        return;
    } else if (requestType == BIP70_MESSAGE_PAYMENTACK) {
        payments::PaymentACK paymentACK;
        if (!paymentACK.ParseFromArray(data.data(), data.size())) {
            QString msg = tr("Bad response from server %1")
                              .arg(reply->request().url().toString());

            qWarning() << "PaymentServer::netRequestFinished : " << msg;
            emit message(tr("Payment request error"), msg, CClientUIInterface::MSG_ERROR);
        } else {
            emit receivedPaymentACK(GUIUtil::HtmlEscape(paymentACK.memo()));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        }
    }
}

<<<<<<< HEAD
void PaymentServer::reportSslErrors(QNetworkReply* reply, const QList<QSslError> &errs)
=======
void PaymentServer::reportSslErrors(QNetworkReply* reply, const QList<QSslError>& errs)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    Q_UNUSED(reply);

    QString errString;
<<<<<<< HEAD
    Q_FOREACH (const QSslError& err, errs) {
        qWarning() << "PaymentServer::reportSslErrors: " << err;
        errString += err.errorString() + "\n";
    }
    Q_EMIT message(tr("Network request error"), errString, CClientUIInterface::MSG_ERROR);
}

void PaymentServer::setOptionsModel(OptionsModel *optionsModel)
=======
    foreach (const QSslError& err, errs) {
        qWarning() << "PaymentServer::reportSslErrors : " << err;
        errString += err.errorString() + "\n";
    }
    emit message(tr("Network request error"), errString, CClientUIInterface::MSG_ERROR);
}

void PaymentServer::setOptionsModel(OptionsModel* optionsModel)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    this->optionsModel = optionsModel;
}

void PaymentServer::handlePaymentACK(const QString& paymentACKMsg)
{
<<<<<<< HEAD
    // currently we don't further process or store the paymentACK message
    Q_EMIT message(tr("Payment acknowledged"), paymentACKMsg, CClientUIInterface::ICON_INFORMATION | CClientUIInterface::MODAL);
}

bool PaymentServer::verifyNetwork(const payments::PaymentDetails& requestDetails)
{
    bool fVerified = requestDetails.network() == Params().NetworkIDString();
    if (!fVerified) {
        qWarning() << QString("PaymentServer::%1: Payment request network \"%2\" doesn't match client network \"%3\".")
            .arg(__func__)
            .arg(QString::fromStdString(requestDetails.network()))
            .arg(QString::fromStdString(Params().NetworkIDString()));
    }
    return fVerified;
}

bool PaymentServer::verifyExpired(const payments::PaymentDetails& requestDetails)
{
    bool fVerified = (requestDetails.has_expires() && (int64_t)requestDetails.expires() < GetTime());
    if (fVerified) {
        const QString requestExpires = QString::fromStdString(DateTimeStrFormat("%Y-%m-%d %H:%M:%S", (int64_t)requestDetails.expires()));
        qWarning() << QString("PaymentServer::%1: Payment request expired \"%2\".")
            .arg(__func__)
            .arg(requestExpires);
    }
    return fVerified;
}

bool PaymentServer::verifySize(qint64 requestSize)
{
    bool fVerified = (requestSize <= BIP70_MAX_PAYMENTREQUEST_SIZE);
    if (!fVerified) {
        qWarning() << QString("PaymentServer::%1: Payment request too large (%2 bytes, allowed %3 bytes).")
            .arg(__func__)
            .arg(requestSize)
            .arg(BIP70_MAX_PAYMENTREQUEST_SIZE);
    }
    return fVerified;
}

bool PaymentServer::verifyAmount(const CAmount& requestAmount)
{
    bool fVerified = MoneyRange(requestAmount);
    if (!fVerified) {
        qWarning() << QString("PaymentServer::%1: Payment request amount out of allowed range (%2, allowed 0 - %3).")
            .arg(__func__)
            .arg(requestAmount)
            .arg(MAX_MONEY);
    }
    return fVerified;
=======
    // currently we don't futher process or store the paymentACK message
    emit message(tr("Payment acknowledged"), paymentACKMsg, CClientUIInterface::ICON_INFORMATION | CClientUIInterface::MODAL);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

X509_STORE* PaymentServer::getCertStore()
{
    return certStore.get();
}
