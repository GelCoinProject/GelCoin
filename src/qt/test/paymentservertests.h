<<<<<<< HEAD
// Copyright (c) 2009-2015 The Bitcoin Core developers
=======
// Copyright (c) 2009-2014 The Bitcoin developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_TEST_PAYMENTSERVERTESTS_H
#define BITCOIN_QT_TEST_PAYMENTSERVERTESTS_H

#include "../paymentserver.h"

#include <QObject>
#include <QTest>

class PaymentServerTests : public QObject
{
    Q_OBJECT

<<<<<<< HEAD
private Q_SLOTS:
=======
private slots:
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void paymentServerTests();
};

// Dummy class to receive paymentserver signals.
// If SendCoinsRecipient was a proper QObject, then
// we could use QSignalSpy... but it's not.
class RecipientCatcher : public QObject
{
    Q_OBJECT

<<<<<<< HEAD
public Q_SLOTS:
=======
public slots:
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    void getRecipient(SendCoinsRecipient r);

public:
    SendCoinsRecipient recipient;
};

#endif // BITCOIN_QT_TEST_PAYMENTSERVERTESTS_H
