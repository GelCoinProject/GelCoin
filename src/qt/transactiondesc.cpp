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

#include "transactiondesc.h"

#include "bitcoinunits.h"
#include "guiutil.h"
#include "paymentserver.h"
#include "transactionrecord.h"

#include "base58.h"
<<<<<<< HEAD
#include "consensus/consensus.h"
#include "validation.h"
#include "script/script.h"
#include "timedata.h"
#include "util.h"
#include "wallet/db.h"
#include "wallet/wallet.h"

#include "instantx.h"
=======
#include "db.h"
#include "main.h"
#include "script/script.h"
#include "timedata.h"
#include "ui_interface.h"
#include "util.h"
#include "wallet.h"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

#include <stdint.h>
#include <string>

<<<<<<< HEAD
QString TransactionDesc::FormatTxStatus(const CWalletTx& wtx)
{
    AssertLockHeld(cs_main);
    if (!CheckFinalTx(wtx))
    {
=======
using namespace std;

QString TransactionDesc::FormatTxStatus(const CWalletTx& wtx)
{
    AssertLockHeld(cs_main);
    if (!IsFinalTx(wtx, chainActive.Height() + 1)) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        if (wtx.nLockTime < LOCKTIME_THRESHOLD)
            return tr("Open for %n more block(s)", "", wtx.nLockTime - chainActive.Height());
        else
            return tr("Open until %1").arg(GUIUtil::dateTimeStr(wtx.nLockTime));
<<<<<<< HEAD
    }
    else
    {
        int nDepth = wtx.GetDepthInMainChain();
        if (nDepth < 0) return tr("conflicted");

        QString strTxStatus;
        bool fOffline = (GetAdjustedTime() - wtx.nTimeReceived > 2 * 60) && (wtx.GetRequestCount() == 0);

        if (fOffline) {
            strTxStatus = tr("%1/offline").arg(nDepth);
        } else if (nDepth == 0) {
            strTxStatus = tr("0/unconfirmed, %1").arg((wtx.InMempool() ? tr("in memory pool") : tr("not in memory pool"))) + (wtx.isAbandoned() ? ", "+tr("abandoned") : "");
        } else if (nDepth < 6) {
            strTxStatus = tr("%1/unconfirmed").arg(nDepth);
        } else {
            strTxStatus = tr("%1 confirmations").arg(nDepth);
        }

        if(!instantsend.HasTxLockRequest(wtx.GetHash())) return strTxStatus; // regular tx

        int nSignatures = instantsend.GetTransactionLockSignatures(wtx.GetHash());
        int nSignaturesMax = CTxLockRequest(wtx).GetMaxSignatures();
        // InstantSend
        strTxStatus += " (";
        if(instantsend.IsLockedInstantSendTransaction(wtx.GetHash())) {
            strTxStatus += tr("verified via InstantSend");
        } else if(!instantsend.IsTxLockCandidateTimedOut(wtx.GetHash())) {
            strTxStatus += tr("InstantSend verification in progress - %1 of %2 signatures").arg(nSignatures).arg(nSignaturesMax);
        } else {
            strTxStatus += tr("InstantSend verification failed");
        }
        strTxStatus += ")";

        return strTxStatus;
    }
}

QString TransactionDesc::toHTML(CWallet *wallet, CWalletTx &wtx, TransactionRecord *rec, int unit)
=======
    } else {
        int nDepth = wtx.GetDepthInMainChain();
        if (nDepth < 0)
            return tr("conflicted");
        else if (GetAdjustedTime() - wtx.nTimeReceived > 2 * 60 && wtx.GetRequestCount() == 0)
            return tr("%1/offline").arg(nDepth);
        else if (nDepth < 6)
            return tr("%1/unconfirmed").arg(nDepth);
        else
            return tr("%1 confirmations").arg(nDepth);
    }
}

QString TransactionDesc::toHTML(CWallet* wallet, CWalletTx& wtx, TransactionRecord* rec, int unit)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    QString strHTML;

    LOCK2(cs_main, wallet->cs_wallet);
    strHTML.reserve(4000);
    strHTML += "<html><font face='verdana, arial, helvetica, sans-serif'>";

    int64_t nTime = wtx.GetTxTime();
    CAmount nCredit = wtx.GetCredit(ISMINE_ALL);
    CAmount nDebit = wtx.GetDebit(ISMINE_ALL);
    CAmount nNet = nCredit - nDebit;

    strHTML += "<b>" + tr("Status") + ":</b> " + FormatTxStatus(wtx);
    int nRequests = wtx.GetRequestCount();
<<<<<<< HEAD
    if (nRequests != -1)
    {
=======
    if (nRequests != -1) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        if (nRequests == 0)
            strHTML += tr(", has not been successfully broadcast yet");
        else if (nRequests > 0)
            strHTML += tr(", broadcast through %n node(s)", "", nRequests);
    }
    strHTML += "<br>";

    strHTML += "<b>" + tr("Date") + ":</b> " + (nTime ? GUIUtil::dateTimeStr(nTime) : "") + "<br>";

    //
    // From
    //
<<<<<<< HEAD
    if (wtx.IsCoinBase())
    {
        strHTML += "<b>" + tr("Source") + ":</b> " + tr("Generated") + "<br>";
    }
    else if (wtx.mapValue.count("from") && !wtx.mapValue["from"].empty())
    {
        // Online transaction
        strHTML += "<b>" + tr("From") + ":</b> " + GUIUtil::HtmlEscape(wtx.mapValue["from"]) + "<br>";
    }
    else
    {
        // Offline transaction
        if (nNet > 0)
        {
            // Credit
            if (CBitcoinAddress(rec->address).IsValid())
            {
                CTxDestination address = CBitcoinAddress(rec->address).Get();
                if (wallet->mapAddressBook.count(address))
                {
=======
    if (wtx.IsCoinBase()) {
        strHTML += "<b>" + tr("Source") + ":</b> " + tr("Generated") + "<br>";
    } else if (wtx.mapValue.count("from") && !wtx.mapValue["from"].empty()) {
        // Online transaction
        strHTML += "<b>" + tr("From") + ":</b> " + GUIUtil::HtmlEscape(wtx.mapValue["from"]) + "<br>";
    } else {
        // Offline transaction
        if (nNet > 0) {
            // Credit
            if (CBitcoinAddress(rec->address).IsValid()) {
                CTxDestination address = CBitcoinAddress(rec->address).Get();
                if (wallet->mapAddressBook.count(address)) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                    strHTML += "<b>" + tr("From") + ":</b> " + tr("unknown") + "<br>";
                    strHTML += "<b>" + tr("To") + ":</b> ";
                    strHTML += GUIUtil::HtmlEscape(rec->address);
                    QString addressOwned = (::IsMine(*wallet, address) == ISMINE_SPENDABLE) ? tr("own address") : tr("watch-only");
                    if (!wallet->mapAddressBook[address].name.empty())
                        strHTML += " (" + addressOwned + ", " + tr("label") + ": " + GUIUtil::HtmlEscape(wallet->mapAddressBook[address].name) + ")";
                    else
                        strHTML += " (" + addressOwned + ")";
                    strHTML += "<br>";
                }
            }
        }
    }

    //
    // To
    //
<<<<<<< HEAD
    if (wtx.mapValue.count("to") && !wtx.mapValue["to"].empty())
    {
=======
    if (wtx.mapValue.count("to") && !wtx.mapValue["to"].empty()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        // Online transaction
        std::string strAddress = wtx.mapValue["to"];
        strHTML += "<b>" + tr("To") + ":</b> ";
        CTxDestination dest = CBitcoinAddress(strAddress).Get();
        if (wallet->mapAddressBook.count(dest) && !wallet->mapAddressBook[dest].name.empty())
            strHTML += GUIUtil::HtmlEscape(wallet->mapAddressBook[dest].name) + " ";
        strHTML += GUIUtil::HtmlEscape(strAddress) + "<br>";
    }

    //
    // Amount
    //
<<<<<<< HEAD
    if (wtx.IsCoinBase() && nCredit == 0)
    {
=======
    if (wtx.IsCoinBase() && nCredit == 0) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        //
        // Coinbase
        //
        CAmount nUnmatured = 0;
<<<<<<< HEAD
        BOOST_FOREACH(const CTxOut& txout, wtx.vout)
            nUnmatured += wallet->GetCredit(txout, ISMINE_ALL);
        strHTML += "<b>" + tr("Credit") + ":</b> ";
        if (wtx.IsInMainChain())
            strHTML += BitcoinUnits::formatHtmlWithUnit(unit, nUnmatured)+ " (" + tr("matures in %n more block(s)", "", wtx.GetBlocksToMaturity()) + ")";
        else
            strHTML += "(" + tr("not accepted") + ")";
        strHTML += "<br>";
    }
    else if (nNet > 0)
    {
=======
        BOOST_FOREACH (const CTxOut& txout, wtx.vout)
            nUnmatured += wallet->GetCredit(txout, ISMINE_ALL);
        strHTML += "<b>" + tr("Credit") + ":</b> ";
        if (wtx.IsInMainChain())
            strHTML += BitcoinUnits::formatHtmlWithUnit(unit, nUnmatured) + " (" + tr("matures in %n more block(s)", "", wtx.GetBlocksToMaturity()) + ")";
        else
            strHTML += "(" + tr("not accepted") + ")";
        strHTML += "<br>";
    } else if (nNet > 0) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        //
        // Credit
        //
        strHTML += "<b>" + tr("Credit") + ":</b> " + BitcoinUnits::formatHtmlWithUnit(unit, nNet) + "<br>";
<<<<<<< HEAD
    }
    else
    {
        isminetype fAllFromMe = ISMINE_SPENDABLE;
        BOOST_FOREACH(const CTxIn& txin, wtx.vin)
        {
            isminetype mine = wallet->IsMine(txin);
            if(fAllFromMe > mine) fAllFromMe = mine;
        }

        isminetype fAllToMe = ISMINE_SPENDABLE;
        BOOST_FOREACH(const CTxOut& txout, wtx.vout)
        {
            isminetype mine = wallet->IsMine(txout);
            if(fAllToMe > mine) fAllToMe = mine;
        }

        if (fAllFromMe)
        {
            if(fAllFromMe & ISMINE_WATCH_ONLY)
=======
    } else {
        isminetype fAllFromMe = ISMINE_SPENDABLE;
        BOOST_FOREACH (const CTxIn& txin, wtx.vin) {
            isminetype mine = wallet->IsMine(txin);
            if (fAllFromMe > mine) fAllFromMe = mine;
        }

        isminetype fAllToMe = ISMINE_SPENDABLE;
        BOOST_FOREACH (const CTxOut& txout, wtx.vout) {
            isminetype mine = wallet->IsMine(txout);
            if (fAllToMe > mine) fAllToMe = mine;
        }

        if (fAllFromMe) {
            if (fAllFromMe == ISMINE_WATCH_ONLY)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                strHTML += "<b>" + tr("From") + ":</b> " + tr("watch-only") + "<br>";

            //
            // Debit
            //
<<<<<<< HEAD
            BOOST_FOREACH(const CTxOut& txout, wtx.vout)
            {
=======
            BOOST_FOREACH (const CTxOut& txout, wtx.vout) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                // Ignore change
                isminetype toSelf = wallet->IsMine(txout);
                if ((toSelf == ISMINE_SPENDABLE) && (fAllFromMe == ISMINE_SPENDABLE))
                    continue;

<<<<<<< HEAD
                if (!wtx.mapValue.count("to") || wtx.mapValue["to"].empty())
                {
                    // Offline transaction
                    CTxDestination address;
                    if (ExtractDestination(txout.scriptPubKey, address))
                    {
=======
                if (!wtx.mapValue.count("to") || wtx.mapValue["to"].empty()) {
                    // Offline transaction
                    CTxDestination address;
                    if (ExtractDestination(txout.scriptPubKey, address)) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                        strHTML += "<b>" + tr("To") + ":</b> ";
                        if (wallet->mapAddressBook.count(address) && !wallet->mapAddressBook[address].name.empty())
                            strHTML += GUIUtil::HtmlEscape(wallet->mapAddressBook[address].name) + " ";
                        strHTML += GUIUtil::HtmlEscape(CBitcoinAddress(address).ToString());
<<<<<<< HEAD
                        if(toSelf == ISMINE_SPENDABLE)
                            strHTML += " (own address)";
                        else if(toSelf & ISMINE_WATCH_ONLY)
=======
                        if (toSelf == ISMINE_SPENDABLE)
                            strHTML += " (own address)";
                        else if (toSelf == ISMINE_WATCH_ONLY)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                            strHTML += " (watch-only)";
                        strHTML += "<br>";
                    }
                }

                strHTML += "<b>" + tr("Debit") + ":</b> " + BitcoinUnits::formatHtmlWithUnit(unit, -txout.nValue) + "<br>";
<<<<<<< HEAD
                if(toSelf)
                    strHTML += "<b>" + tr("Credit") + ":</b> " + BitcoinUnits::formatHtmlWithUnit(unit, txout.nValue) + "<br>";
            }

            if (fAllToMe)
            {
=======
                if (toSelf)
                    strHTML += "<b>" + tr("Credit") + ":</b> " + BitcoinUnits::formatHtmlWithUnit(unit, txout.nValue) + "<br>";
            }

            if (fAllToMe) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                // Payment to self
                CAmount nChange = wtx.GetChange();
                CAmount nValue = nCredit - nChange;
                strHTML += "<b>" + tr("Total debit") + ":</b> " + BitcoinUnits::formatHtmlWithUnit(unit, -nValue) + "<br>";
                strHTML += "<b>" + tr("Total credit") + ":</b> " + BitcoinUnits::formatHtmlWithUnit(unit, nValue) + "<br>";
            }

            CAmount nTxFee = nDebit - wtx.GetValueOut();
            if (nTxFee > 0)
                strHTML += "<b>" + tr("Transaction fee") + ":</b> " + BitcoinUnits::formatHtmlWithUnit(unit, -nTxFee) + "<br>";
<<<<<<< HEAD
        }
        else
        {
            //
            // Mixed debit transaction
            //
            BOOST_FOREACH(const CTxIn& txin, wtx.vin)
                if (wallet->IsMine(txin))
                    strHTML += "<b>" + tr("Debit") + ":</b> " + BitcoinUnits::formatHtmlWithUnit(unit, -wallet->GetDebit(txin, ISMINE_ALL)) + "<br>";
            BOOST_FOREACH(const CTxOut& txout, wtx.vout)
=======
        } else {
            //
            // Mixed debit transaction
            //
            BOOST_FOREACH (const CTxIn& txin, wtx.vin)
                if (wallet->IsMine(txin))
                    strHTML += "<b>" + tr("Debit") + ":</b> " + BitcoinUnits::formatHtmlWithUnit(unit, -wallet->GetDebit(txin, ISMINE_ALL)) + "<br>";
            BOOST_FOREACH (const CTxOut& txout, wtx.vout)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                if (wallet->IsMine(txout))
                    strHTML += "<b>" + tr("Credit") + ":</b> " + BitcoinUnits::formatHtmlWithUnit(unit, wallet->GetCredit(txout, ISMINE_ALL)) + "<br>";
        }
    }

    strHTML += "<b>" + tr("Net amount") + ":</b> " + BitcoinUnits::formatHtmlWithUnit(unit, nNet, true) + "<br>";

    //
    // Message
    //
    if (wtx.mapValue.count("message") && !wtx.mapValue["message"].empty())
        strHTML += "<br><b>" + tr("Message") + ":</b><br>" + GUIUtil::HtmlEscape(wtx.mapValue["message"], true) + "<br>";
    if (wtx.mapValue.count("comment") && !wtx.mapValue["comment"].empty())
        strHTML += "<br><b>" + tr("Comment") + ":</b><br>" + GUIUtil::HtmlEscape(wtx.mapValue["comment"], true) + "<br>";

<<<<<<< HEAD
    strHTML += "<b>" + tr("Transaction ID") + ":</b> " + TransactionRecord::formatSubTxId(wtx.GetHash(), rec->idx) + "<br>";
    strHTML += "<b>" + tr("Transaction total size") + ":</b> " + QString::number(wtx.GetTotalSize()) + " bytes<br>";

    // Message from normal gelcoin:URI (gelcoin:XyZ...?message=example)
    Q_FOREACH (const PAIRTYPE(std::string, std::string)& r, wtx.vOrderForm)
=======
    strHTML += "<b>" + tr("Transaction ID") + ":</b> " + rec->getTxID() + "<br>";
    strHTML += "<b>" + tr("Output index") + ":</b> " + QString::number(rec->getOutputIndex()) + "<br>";

    // Message from normal lux:URI (lux:XyZ...?message=example)
    foreach (const PAIRTYPE(string, string) & r, wtx.vOrderForm)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        if (r.first == "Message")
            strHTML += "<br><b>" + tr("Message") + ":</b><br>" + GUIUtil::HtmlEscape(r.second, true) + "<br>";

    //
    // PaymentRequest info:
    //
<<<<<<< HEAD
    Q_FOREACH (const PAIRTYPE(std::string, std::string)& r, wtx.vOrderForm)
    {
        if (r.first == "PaymentRequest")
        {
=======
    foreach (const PAIRTYPE(string, string) & r, wtx.vOrderForm) {
        if (r.first == "PaymentRequest") {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            PaymentRequestPlus req;
            req.parse(QByteArray::fromRawData(r.second.data(), r.second.size()));
            QString merchant;
            if (req.getMerchant(PaymentServer::getCertStore(), merchant))
                strHTML += "<b>" + tr("Merchant") + ":</b> " + GUIUtil::HtmlEscape(merchant) + "<br>";
        }
    }

<<<<<<< HEAD
    if (wtx.IsCoinBase())
    {
        quint32 numBlocksToMaturity = COINBASE_MATURITY +  1;
=======
    if (wtx.IsCoinBase()) {
        quint32 numBlocksToMaturity = Params().COINBASE_MATURITY() + 1;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        strHTML += "<br>" + tr("Generated coins must mature %1 blocks before they can be spent. When you generated this block, it was broadcast to the network to be added to the block chain. If it fails to get into the chain, its state will change to \"not accepted\" and it won't be spendable. This may occasionally happen if another node generates a block within a few seconds of yours.").arg(QString::number(numBlocksToMaturity)) + "<br>";
    }

    //
    // Debug view
    //
<<<<<<< HEAD
    if (fDebug)
    {
        strHTML += "<hr><br>" + tr("Debug information") + "<br><br>";
        BOOST_FOREACH(const CTxIn& txin, wtx.vin)
            if(wallet->IsMine(txin))
                strHTML += "<b>" + tr("Debit") + ":</b> " + BitcoinUnits::formatHtmlWithUnit(unit, -wallet->GetDebit(txin, ISMINE_ALL)) + "<br>";
        BOOST_FOREACH(const CTxOut& txout, wtx.vout)
            if(wallet->IsMine(txout))
=======
    if (fDebug) {
        strHTML += "<hr><br>" + tr("Debug information") + "<br><br>";
        BOOST_FOREACH (const CTxIn& txin, wtx.vin)
            if (wallet->IsMine(txin))
                strHTML += "<b>" + tr("Debit") + ":</b> " + BitcoinUnits::formatHtmlWithUnit(unit, -wallet->GetDebit(txin, ISMINE_ALL)) + "<br>";
        BOOST_FOREACH (const CTxOut& txout, wtx.vout)
            if (wallet->IsMine(txout))
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                strHTML += "<b>" + tr("Credit") + ":</b> " + BitcoinUnits::formatHtmlWithUnit(unit, wallet->GetCredit(txout, ISMINE_ALL)) + "<br>";

        strHTML += "<br><b>" + tr("Transaction") + ":</b><br>";
        strHTML += GUIUtil::HtmlEscape(wtx.ToString(), true);

        strHTML += "<br><b>" + tr("Inputs") + ":</b>";
        strHTML += "<ul>";

<<<<<<< HEAD
        BOOST_FOREACH(const CTxIn& txin, wtx.vin)
        {
            COutPoint prevout = txin.prevout;

            Coin prev;
            if(pcoinsTip->GetCoin(prevout, prev))
            {
                {
                    strHTML += "<li>";
                    const CTxOut &vout = prev.out;
                    CTxDestination address;
                    if (ExtractDestination(vout.scriptPubKey, address))
                    {
=======
        BOOST_FOREACH (const CTxIn& txin, wtx.vin) {
            COutPoint prevout = txin.prevout;

            CCoins prev;
            if (pcoinsTip->GetCoins(prevout.hash, prev)) {
                if (prevout.n < prev.vout.size()) {
                    strHTML += "<li>";
                    const CTxOut& vout = prev.vout[prevout.n];
                    CTxDestination address;
                    if (ExtractDestination(vout.scriptPubKey, address)) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                        if (wallet->mapAddressBook.count(address) && !wallet->mapAddressBook[address].name.empty())
                            strHTML += GUIUtil::HtmlEscape(wallet->mapAddressBook[address].name) + " ";
                        strHTML += QString::fromStdString(CBitcoinAddress(address).ToString());
                    }
                    strHTML = strHTML + " " + tr("Amount") + "=" + BitcoinUnits::formatHtmlWithUnit(unit, vout.nValue);
                    strHTML = strHTML + " IsMine=" + (wallet->IsMine(vout) & ISMINE_SPENDABLE ? tr("true") : tr("false"));
                    strHTML = strHTML + " IsWatchOnly=" + (wallet->IsMine(vout) & ISMINE_WATCH_ONLY ? tr("true") : tr("false")) + "</li>";
                }
            }
        }

        strHTML += "</ul>";
    }

    strHTML += "</font></html>";
    return strHTML;
}
