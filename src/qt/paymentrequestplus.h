<<<<<<< HEAD
// Copyright (c) 2011-2015 The Bitcoin developers
=======
// Copyright (c) 2011-2014 The Bitcoin developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_PAYMENTREQUESTPLUS_H
#define BITCOIN_QT_PAYMENTREQUESTPLUS_H

#include "paymentrequest.pb.h"

#include "base58.h"

<<<<<<< HEAD
#include <openssl/x509.h>

=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#include <QByteArray>
#include <QList>
#include <QString>

<<<<<<< HEAD
static const bool DEFAULT_SELFSIGNED_ROOTCERTS = false;

=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
//
// Wraps dumb protocol buffer paymentRequest
// with extra methods
//

class PaymentRequestPlus
{
public:
<<<<<<< HEAD
    PaymentRequestPlus() { }
=======
    PaymentRequestPlus() {}
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    bool parse(const QByteArray& data);
    bool SerializeToString(std::string* output) const;

    bool IsInitialized() const;
<<<<<<< HEAD
=======
    QString getPKIType() const;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    // Returns true if merchant's identity is authenticated, and
    // returns human-readable merchant identity in merchant
    bool getMerchant(X509_STORE* certStore, QString& merchant) const;

    // Returns list of outputs, amount
<<<<<<< HEAD
    QList<std::pair<CScript,CAmount> > getPayTo() const;
=======
    QList<std::pair<CScript, CAmount> > getPayTo() const;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    const payments::PaymentDetails& getDetails() const { return details; }

private:
    payments::PaymentRequest paymentRequest;
    payments::PaymentDetails details;
};

#endif // BITCOIN_QT_PAYMENTREQUESTPLUS_H
