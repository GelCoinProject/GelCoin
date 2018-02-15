<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin Core developers
=======
// Copyright (c) 2011-2014 The Bitcoin developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

//
// Wraps dumb protocol buffer paymentRequest
// with some extra methods
//

#include "paymentrequestplus.h"

<<<<<<< HEAD
#include "util.h"

#include <stdexcept>

=======
#include <stdexcept>

#include <openssl/x509.h>
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include <openssl/x509_vfy.h>

#include <QDateTime>
#include <QDebug>
#include <QSslCertificate>

<<<<<<< HEAD
class SSLVerifyError : public std::runtime_error
{
public:
    SSLVerifyError(std::string err) : std::runtime_error(err) { }
=======
using namespace std;

class SSLVerifyError : public std::runtime_error
{
public:
    SSLVerifyError(std::string err) : std::runtime_error(err) {}
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
};

bool PaymentRequestPlus::parse(const QByteArray& data)
{
    bool parseOK = paymentRequest.ParseFromArray(data.data(), data.size());
    if (!parseOK) {
<<<<<<< HEAD
        qWarning() << "PaymentRequestPlus::parse: Error parsing payment request";
        return false;
    }
    if (paymentRequest.payment_details_version() > 1) {
        qWarning() << "PaymentRequestPlus::parse: Received up-version payment details, version=" << paymentRequest.payment_details_version();
=======
        qWarning() << "PaymentRequestPlus::parse : Error parsing payment request";
        return false;
    }
    if (paymentRequest.payment_details_version() > 1) {
        qWarning() << "PaymentRequestPlus::parse : Received up-version payment details, version=" << paymentRequest.payment_details_version();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return false;
    }

    parseOK = details.ParseFromString(paymentRequest.serialized_payment_details());
<<<<<<< HEAD
    if (!parseOK)
    {
        qWarning() << "PaymentRequestPlus::parse: Error parsing payment details";
=======
    if (!parseOK) {
        qWarning() << "PaymentRequestPlus::parse : Error parsing payment details";
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        paymentRequest.Clear();
        return false;
    }
    return true;
}

<<<<<<< HEAD
bool PaymentRequestPlus::SerializeToString(std::string* output) const
=======
bool PaymentRequestPlus::SerializeToString(string* output) const
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    return paymentRequest.SerializeToString(output);
}

bool PaymentRequestPlus::IsInitialized() const
{
    return paymentRequest.IsInitialized();
}

<<<<<<< HEAD
=======
QString PaymentRequestPlus::getPKIType() const
{
    if (!IsInitialized()) return QString("none");
    return QString::fromStdString(paymentRequest.pki_type());
}

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
bool PaymentRequestPlus::getMerchant(X509_STORE* certStore, QString& merchant) const
{
    merchant.clear();

    if (!IsInitialized())
        return false;

    // One day we'll support more PKI types, but just
    // x509 for now:
    const EVP_MD* digestAlgorithm = NULL;
    if (paymentRequest.pki_type() == "x509+sha256") {
        digestAlgorithm = EVP_sha256();
<<<<<<< HEAD
    }
    else if (paymentRequest.pki_type() == "x509+sha1") {
        digestAlgorithm = EVP_sha1();
    }
    else if (paymentRequest.pki_type() == "none") {
        qWarning() << "PaymentRequestPlus::getMerchant: Payment request: pki_type == none";
        return false;
    }
    else {
        qWarning() << "PaymentRequestPlus::getMerchant: Payment request: unknown pki_type " << QString::fromStdString(paymentRequest.pki_type());
=======
    } else if (paymentRequest.pki_type() == "x509+sha1") {
        digestAlgorithm = EVP_sha1();
    } else if (paymentRequest.pki_type() == "none") {
        qWarning() << "PaymentRequestPlus::getMerchant : Payment request: pki_type == none";
        return false;
    } else {
        qWarning() << "PaymentRequestPlus::getMerchant : Payment request: unknown pki_type " << QString::fromStdString(paymentRequest.pki_type());
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return false;
    }

    payments::X509Certificates certChain;
    if (!certChain.ParseFromString(paymentRequest.pki_data())) {
<<<<<<< HEAD
        qWarning() << "PaymentRequestPlus::getMerchant: Payment request: error parsing pki_data";
=======
        qWarning() << "PaymentRequestPlus::getMerchant : Payment request: error parsing pki_data";
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return false;
    }

    std::vector<X509*> certs;
    const QDateTime currentTime = QDateTime::currentDateTime();
    for (int i = 0; i < certChain.certificate_size(); i++) {
        QByteArray certData(certChain.certificate(i).data(), certChain.certificate(i).size());
        QSslCertificate qCert(certData, QSsl::Der);
        if (currentTime < qCert.effectiveDate() || currentTime > qCert.expiryDate()) {
<<<<<<< HEAD
            qWarning() << "PaymentRequestPlus::getMerchant: Payment request: certificate expired or not yet active: " << qCert;
=======
            qWarning() << "PaymentRequestPlus::getMerchant : Payment request: certificate expired or not yet active: " << qCert;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            return false;
        }
#if QT_VERSION >= 0x050000
        if (qCert.isBlacklisted()) {
<<<<<<< HEAD
            qWarning() << "PaymentRequestPlus::getMerchant: Payment request: certificate blacklisted: " << qCert;
            return false;
        }
#endif
        const unsigned char *data = (const unsigned char *)certChain.certificate(i).data();
        X509 *cert = d2i_X509(NULL, &data, certChain.certificate(i).size());
=======
            qWarning() << "PaymentRequestPlus::getMerchant : Payment request: certificate blacklisted: " << qCert;
            return false;
        }
#endif
        const unsigned char* data = (const unsigned char*)certChain.certificate(i).data();
        X509* cert = d2i_X509(NULL, &data, certChain.certificate(i).size());
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        if (cert)
            certs.push_back(cert);
    }
    if (certs.empty()) {
<<<<<<< HEAD
        qWarning() << "PaymentRequestPlus::getMerchant: Payment request: empty certificate chain";
=======
        qWarning() << "PaymentRequestPlus::getMerchant : Payment request: empty certificate chain";
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        return false;
    }

    // The first cert is the signing cert, the rest are untrusted certs that chain
    // to a valid root authority. OpenSSL needs them separately.
<<<<<<< HEAD
    STACK_OF(X509) *chain = sk_X509_new_null();
    for (int i = certs.size() - 1; i > 0; i--) {
        sk_X509_push(chain, certs[i]);
    }
    X509 *signing_cert = certs[0];

    // Now create a "store context", which is a single use object for checking,
    // load the signing cert into it and verify.
    X509_STORE_CTX *store_ctx = X509_STORE_CTX_new();
    if (!store_ctx) {
        qWarning() << "PaymentRequestPlus::getMerchant: Payment request: error creating X509_STORE_CTX";
        return false;
    }

    char *website = NULL;
    bool fResult = true;
    try
    {
        if (!X509_STORE_CTX_init(store_ctx, certStore, signing_cert, chain))
        {
=======
    STACK_OF(X509)* chain = sk_X509_new_null();
    for (int i = certs.size() - 1; i > 0; i--) {
        sk_X509_push(chain, certs[i]);
    }
    X509* signing_cert = certs[0];

    // Now create a "store context", which is a single use object for checking,
    // load the signing cert into it and verify.
    X509_STORE_CTX* store_ctx = X509_STORE_CTX_new();
    if (!store_ctx) {
        qWarning() << "PaymentRequestPlus::getMerchant : Payment request: error creating X509_STORE_CTX";
        return false;
    }

    char* website = NULL;
    bool fResult = true;
    try {
        if (!X509_STORE_CTX_init(store_ctx, certStore, signing_cert, chain)) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            int error = X509_STORE_CTX_get_error(store_ctx);
            throw SSLVerifyError(X509_verify_cert_error_string(error));
        }

        // Now do the verification!
        int result = X509_verify_cert(store_ctx);
        if (result != 1) {
            int error = X509_STORE_CTX_get_error(store_ctx);
<<<<<<< HEAD
            // For testing payment requests, we allow self signed root certs!
            // This option is just shown in the UI options, if -help-debug is enabled.
            if (!(error == X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT && GetBoolArg("-allowselfsignedrootcertificates", DEFAULT_SELFSIGNED_ROOTCERTS))) {
                throw SSLVerifyError(X509_verify_cert_error_string(error));
            } else {
               qDebug() << "PaymentRequestPlus::getMerchant: Allowing self signed root certificate, because -allowselfsignedrootcertificates is true.";
            }
        }
        X509_NAME *certname = X509_get_subject_name(signing_cert);
=======
            throw SSLVerifyError(X509_verify_cert_error_string(error));
        }
        X509_NAME* certname = X509_get_subject_name(signing_cert);
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

        // Valid cert; check signature:
        payments::PaymentRequest rcopy(paymentRequest); // Copy
        rcopy.set_signature(std::string(""));
<<<<<<< HEAD
        std::string data_to_verify;                     // Everything but the signature
        rcopy.SerializeToString(&data_to_verify);

#if OPENSSL_VERSION_NUMBER >= 0x10100000L
        EVP_MD_CTX *ctx = EVP_MD_CTX_new();
        if (!ctx) throw SSLVerifyError("Error allocating OpenSSL context.");
#else
        EVP_MD_CTX _ctx;
        EVP_MD_CTX *ctx;
        ctx = &_ctx;
#endif

        EVP_PKEY *pubkey = X509_get_pubkey(signing_cert);

        EVP_MD_CTX_init(ctx);
        if (!EVP_VerifyInit_ex(ctx, digestAlgorithm, NULL) ||
            !EVP_VerifyUpdate(ctx, data_to_verify.data(), data_to_verify.size()) ||
            !EVP_VerifyFinal(ctx, (const unsigned char*)paymentRequest.signature().data(), (unsigned int)paymentRequest.signature().size(), pubkey)) {
            throw SSLVerifyError("Bad signature, invalid payment request.");
        }

#if OPENSSL_VERSION_NUMBER >= 0x10100000L
        EVP_MD_CTX_free(ctx);
#endif

=======
        std::string data_to_verify; // Everything but the signature
        rcopy.SerializeToString(&data_to_verify);

        EVP_MD_CTX ctx;
        EVP_PKEY* pubkey = X509_get_pubkey(signing_cert);
        EVP_MD_CTX_init(&ctx);
        if (!EVP_VerifyInit_ex(&ctx, digestAlgorithm, NULL) ||
            !EVP_VerifyUpdate(&ctx, data_to_verify.data(), data_to_verify.size()) ||
            !EVP_VerifyFinal(&ctx, (const unsigned char*)paymentRequest.signature().data(), paymentRequest.signature().size(), pubkey)) {
            throw SSLVerifyError("Bad signature, invalid PaymentRequest.");
        }

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        // OpenSSL API for getting human printable strings from certs is baroque.
        int textlen = X509_NAME_get_text_by_NID(certname, NID_commonName, NULL, 0);
        website = new char[textlen + 1];
        if (X509_NAME_get_text_by_NID(certname, NID_commonName, website, textlen + 1) == textlen && textlen > 0) {
            merchant = website;
<<<<<<< HEAD
        }
        else {
            throw SSLVerifyError("Bad certificate, missing common name.");
        }
        // TODO: detect EV certificates and set merchant = business name instead of unfriendly NID_commonName ?
    }
    catch (const SSLVerifyError& err) {
        fResult = false;
        qWarning() << "PaymentRequestPlus::getMerchant: SSL error: " << err.what();
=======
        } else {
            throw SSLVerifyError("Bad certificate, missing common name.");
        }
        // TODO: detect EV certificates and set merchant = business name instead of unfriendly NID_commonName ?
    } catch (SSLVerifyError& err) {
        fResult = false;
        qWarning() << "PaymentRequestPlus::getMerchant : SSL error: " << err.what();
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }

    if (website)
        delete[] website;
    X509_STORE_CTX_free(store_ctx);
    for (unsigned int i = 0; i < certs.size(); i++)
        X509_free(certs[i]);

    return fResult;
}

<<<<<<< HEAD
QList<std::pair<CScript,CAmount> > PaymentRequestPlus::getPayTo() const
{
    QList<std::pair<CScript,CAmount> > result;
    for (int i = 0; i < details.outputs_size(); i++)
    {
        const unsigned char* scriptStr = (const unsigned char*)details.outputs(i).script().data();
        CScript s(scriptStr, scriptStr+details.outputs(i).script().size());

        result.append(std::make_pair(s, details.outputs(i).amount()));
=======
QList<std::pair<CScript, CAmount> > PaymentRequestPlus::getPayTo() const
{
    QList<std::pair<CScript, CAmount> > result;
    for (int i = 0; i < details.outputs_size(); i++) {
        const unsigned char* scriptStr = (const unsigned char*)details.outputs(i).script().data();
        CScript s(scriptStr, scriptStr + details.outputs(i).script().size());

        result.append(make_pair(s, details.outputs(i).amount()));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    }
    return result;
}
