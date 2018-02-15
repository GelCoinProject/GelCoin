<<<<<<< HEAD
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Copyright (c) 2014-2017 The GelCoin developers
=======
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The LUX developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#if defined(HAVE_CONFIG_H)
<<<<<<< HEAD
#include "config/gelcoin-config.h"
=======
#include "config/lux-config.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#endif

#include "util.h"
#include "uritests.h"
<<<<<<< HEAD
#include "compattests.h"
#include "trafficgraphdatatests.h"
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

#ifdef ENABLE_WALLET
#include "paymentservertests.h"
#endif

#include <QCoreApplication>
#include <QObject>
#include <QTest>

<<<<<<< HEAD
#include <openssl/ssl.h>

=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
#if defined(QT_STATICPLUGIN) && QT_VERSION < 0x050000
#include <QtPlugin>
Q_IMPORT_PLUGIN(qcncodecs)
Q_IMPORT_PLUGIN(qjpcodecs)
Q_IMPORT_PLUGIN(qtwcodecs)
Q_IMPORT_PLUGIN(qkrcodecs)
#endif

// This is all you need to run all the tests
int main(int argc, char *argv[])
{
    SetupEnvironment();
    bool fInvalid = false;

    // Don't remove this, it's needed to access
    // QCoreApplication:: in the tests
    QCoreApplication app(argc, argv);
<<<<<<< HEAD
    app.setApplicationName("GelCoin-Qt-test");

    SSL_library_init();
=======
    app.setApplicationName("Lux-Qt-test");
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    URITests test1;
    if (QTest::qExec(&test1) != 0)
        fInvalid = true;
#ifdef ENABLE_WALLET
    PaymentServerTests test2;
    if (QTest::qExec(&test2) != 0)
        fInvalid = true;
#endif
<<<<<<< HEAD
    CompatTests test4;
    if (QTest::qExec(&test4) != 0)
        fInvalid = true;

    TrafficGraphDataTests test5;
    if (QTest::qExec(&test5) != 0)
        fInvalid = true;
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    return fInvalid;
}
