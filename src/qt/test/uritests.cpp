<<<<<<< HEAD
// Copyright (c) 2009-2014 The Bitcoin Core developers
=======
// Copyright (c) 2009-2014 The Bitcoin developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "uritests.h"

#include "guiutil.h"
#include "walletmodel.h"

#include <QUrl>

void URITests::uriTests()
{
    SendCoinsRecipient rv;
    QUrl uri;
<<<<<<< HEAD
    uri.setUrl(QString("gelcoin:XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg?req-dontexist="));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("gelcoin:XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg?dontexist="));
=======
    uri.setUrl(QString("lux:XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg?req-dontexist="));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("lux:XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg?dontexist="));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 0);

<<<<<<< HEAD
    uri.setUrl(QString("gelcoin:XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg?label=Some Example Address"));
=======
    uri.setUrl(QString("lux:XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg?label=Some Example Address"));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg"));
    QVERIFY(rv.label == QString("Some Example Address"));
    QVERIFY(rv.amount == 0);

<<<<<<< HEAD
    uri.setUrl(QString("gelcoin:XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg?amount=0.001"));
=======
    uri.setUrl(QString("lux:XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg?amount=0.001"));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100000);

<<<<<<< HEAD
    uri.setUrl(QString("gelcoin:XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg?amount=1.001"));
=======
    uri.setUrl(QString("lux:XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg?amount=1.001"));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100100000);

<<<<<<< HEAD
    uri.setUrl(QString("gelcoin:XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg?amount=100&label=Some Example"));
=======
    uri.setUrl(QString("lux:XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg?amount=100&label=Some Example"));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Some Example"));

<<<<<<< HEAD
    uri.setUrl(QString("gelcoin:XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg?message=Some Example Address"));
=======
    uri.setUrl(QString("lux:XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg?message=Some Example Address"));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg"));
    QVERIFY(rv.label == QString());

<<<<<<< HEAD
    QVERIFY(GUIUtil::parseBitcoinURI("gelcoin://XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg?message=Some Example Address", &rv));
    QVERIFY(rv.address == QString("XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg"));
    QVERIFY(rv.label == QString());

    uri.setUrl(QString("gelcoin:XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg?req-message=Some Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("gelcoin:XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg?amount=1,000&label=Some Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("gelcoin:XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg?amount=1,000.0&label=Some Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("gelcoin:XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg?amount=100&label=Some Example&message=Some Example Message&IS=1"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Some Example"));
    QVERIFY(rv.message == QString("Some Example Message"));
    QVERIFY(rv.fUseInstantSend == 1);

    uri.setUrl(QString("gelcoin:XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg?amount=100&label=Some Example&message=Some Example Message&IS=Something Invalid"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Some Example"));
    QVERIFY(rv.message == QString("Some Example Message"));
    QVERIFY(rv.fUseInstantSend != 1);

    uri.setUrl(QString("gelcoin:XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg?IS=1"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.fUseInstantSend == 1);

    uri.setUrl(QString("gelcoin:XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg?IS=0"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.fUseInstantSend != 1);

    uri.setUrl(QString("gelcoin:XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.fUseInstantSend != 1);
=======
    QVERIFY(GUIUtil::parseBitcoinURI("lux://XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg?message=Some Example Address", &rv));
    QVERIFY(rv.address == QString("XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg"));
    QVERIFY(rv.label == QString());

    uri.setUrl(QString("lux:XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg?req-message=Some Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("lux:XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg?amount=1,000&label=Some Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("lux:XwnLY9Tf7Zsef8gMGL2fhWA9ZmMjt4KPwg?amount=1,000.0&label=Some Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}
