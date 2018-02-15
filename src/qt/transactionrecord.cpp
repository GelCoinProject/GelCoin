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

#include "transactionrecord.h"

#include "base58.h"
<<<<<<< HEAD
#include "consensus/consensus.h"
#include "validation.h"
#include "timedata.h"
#include "wallet/wallet.h"

#include "instantx.h"
#include "privatesend.h"

#include <stdint.h>

#include <boost/foreach.hpp>

/* Return positive answer if transaction should be shown in list.
 */
bool TransactionRecord::showTransaction(const CWalletTx &wtx)
{
    if (wtx.IsCoinBase())
    {
        // Ensures we show generated coins / mined transactions at depth 1
        if (!wtx.IsInMainChain())
        {
=======
#include "timedata.h"
#include "wallet.h"

#include <stdint.h>

/* Return positive answer if transaction should be shown in list.
 */
bool TransactionRecord::showTransaction(const CWalletTx& wtx)
{
    if (wtx.IsCoinBase()) {
        // Ensures we show generated coins / mined transactions at depth 1
        if (!wtx.IsInMainChain()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            return false;
        }
    }
    return true;
}

/*
 * Decompose CWallet transaction to model transaction records.
 */
<<<<<<< HEAD
QList<TransactionRecord> TransactionRecord::decomposeTransaction(const CWallet *wallet, const CWalletTx &wtx)
=======
QList<TransactionRecord> TransactionRecord::decomposeTransaction(const CWallet* wallet, const CWalletTx& wtx)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    QList<TransactionRecord> parts;
    int64_t nTime = wtx.GetTxTime();
    CAmount nCredit = wtx.GetCredit(ISMINE_ALL);
    CAmount nDebit = wtx.GetDebit(ISMINE_ALL);
    CAmount nNet = nCredit - nDebit;
    uint256 hash = wtx.GetHash();
    std::map<std::string, std::string> mapValue = wtx.mapValue;

<<<<<<< HEAD
    if (nNet > 0 || wtx.IsCoinBase())
    {
        //
        // Credit
        //
        BOOST_FOREACH(const CTxOut& txout, wtx.vout)
        {
            isminetype mine = wallet->IsMine(txout);
            if(mine)
            {
=======
    if (wtx.IsCoinStake()) {
        TransactionRecord sub(hash, nTime);
        CTxDestination address;
        if (!ExtractDestination(wtx.vout[1].scriptPubKey, address))
            return parts;

        if (!IsMine(*wallet, address)) {
            //if the address is not yours then it means you have a tx sent to you in someone elses coinstake tx
            for (unsigned int i = 1; i < wtx.vout.size(); i++) {
                CTxDestination outAddress;
                if (ExtractDestination(wtx.vout[i].scriptPubKey, outAddress)) {
                    if (IsMine(*wallet, outAddress)) {
                        isminetype mine = wallet->IsMine(wtx.vout[i]);
                        sub.involvesWatchAddress = mine & ISMINE_WATCH_ONLY;
                        sub.type = TransactionRecord::MNReward;
                        sub.address = CBitcoinAddress(outAddress).ToString();
                        sub.credit = wtx.vout[i].nValue;
                    }
                }
            }
        } else {
            //stake reward
            isminetype mine = wallet->IsMine(wtx.vout[1]);
            sub.involvesWatchAddress = mine & ISMINE_WATCH_ONLY;
            sub.type = TransactionRecord::StakeMint;
            sub.address = CBitcoinAddress(address).ToString();
            sub.credit = nNet;
        }
        parts.append(sub);
    } else if (nNet > 0 || wtx.IsCoinBase()) {
        //
        // Credit
        //
        BOOST_FOREACH (const CTxOut& txout, wtx.vout) {
            isminetype mine = wallet->IsMine(txout);
            if (mine) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                TransactionRecord sub(hash, nTime);
                CTxDestination address;
                sub.idx = parts.size(); // sequence number
                sub.credit = txout.nValue;
                sub.involvesWatchAddress = mine & ISMINE_WATCH_ONLY;
<<<<<<< HEAD
                if (ExtractDestination(txout.scriptPubKey, address) && IsMine(*wallet, address))
                {
                    // Received by GelCoin Address
                    sub.type = TransactionRecord::RecvWithAddress;
                    sub.address = CBitcoinAddress(address).ToString();
                }
                else
                {
=======
                if (ExtractDestination(txout.scriptPubKey, address) && IsMine(*wallet, address)) {
                    // Received by LUX Address
                    sub.type = TransactionRecord::RecvWithAddress;
                    sub.address = CBitcoinAddress(address).ToString();
                } else {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                    // Received by IP connection (deprecated features), or a multisignature or other non-simple transaction
                    sub.type = TransactionRecord::RecvFromOther;
                    sub.address = mapValue["from"];
                }
<<<<<<< HEAD
                if (wtx.IsCoinBase())
                {
=======
                if (wtx.IsCoinBase()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                    // Generated
                    sub.type = TransactionRecord::Generated;
                }

                parts.append(sub);
            }
        }
<<<<<<< HEAD
    }
    else
    {
=======
    } else {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        bool fAllFromMeDenom = true;
        int nFromMe = 0;
        bool involvesWatchAddress = false;
        isminetype fAllFromMe = ISMINE_SPENDABLE;
<<<<<<< HEAD
        BOOST_FOREACH(const CTxIn& txin, wtx.vin)
        {
            if(wallet->IsMine(txin)) {
                fAllFromMeDenom = fAllFromMeDenom && wallet->IsDenominated(txin.prevout);
                nFromMe++;
            }
            isminetype mine = wallet->IsMine(txin);
            if(mine & ISMINE_WATCH_ONLY) involvesWatchAddress = true;
            if(fAllFromMe > mine) fAllFromMe = mine;
=======
        BOOST_FOREACH (const CTxIn& txin, wtx.vin) {
            if (wallet->IsMine(txin)) {
                fAllFromMeDenom = fAllFromMeDenom && wallet->IsDenominated(txin);
                nFromMe++;
            }
            isminetype mine = wallet->IsMine(txin);
            if (mine & ISMINE_WATCH_ONLY) involvesWatchAddress = true;
            if (fAllFromMe > mine) fAllFromMe = mine;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        }

        isminetype fAllToMe = ISMINE_SPENDABLE;
        bool fAllToMeDenom = true;
        int nToMe = 0;
<<<<<<< HEAD
        BOOST_FOREACH(const CTxOut& txout, wtx.vout) {
            if(wallet->IsMine(txout)) {
                fAllToMeDenom = fAllToMeDenom && CPrivateSend::IsDenominatedAmount(txout.nValue);
                nToMe++;
            }
            isminetype mine = wallet->IsMine(txout);
            if(mine & ISMINE_WATCH_ONLY) involvesWatchAddress = true;
            if(fAllToMe > mine) fAllToMe = mine;
        }

        if(fAllFromMeDenom && fAllToMeDenom && nFromMe * nToMe) {
            parts.append(TransactionRecord(hash, nTime, TransactionRecord::PrivateSendDenominate, "", -nDebit, nCredit));
            parts.last().involvesWatchAddress = false;   // maybe pass to TransactionRecord as constructor argument
        }
        else if (fAllFromMe && fAllToMe)
        {
=======
        BOOST_FOREACH (const CTxOut& txout, wtx.vout) {
            if (wallet->IsMine(txout)) {
                fAllToMeDenom = fAllToMeDenom && wallet->IsDenominatedAmount(txout.nValue);
                nToMe++;
            }
            isminetype mine = wallet->IsMine(txout);
            if (mine & ISMINE_WATCH_ONLY) involvesWatchAddress = true;
            if (fAllToMe > mine) fAllToMe = mine;
        }

        if (fAllFromMeDenom && fAllToMeDenom && nFromMe * nToMe) {
            parts.append(TransactionRecord(hash, nTime, TransactionRecord::ObfuscationDenominate, "", -nDebit, nCredit));
            parts.last().involvesWatchAddress = false; // maybe pass to TransactionRecord as constructor argument
        } else if (fAllFromMe && fAllToMe) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            // Payment to self
            // TODO: this section still not accurate but covers most cases,
            // might need some additional work however

            TransactionRecord sub(hash, nTime);
            // Payment to self by default
            sub.type = TransactionRecord::SendToSelf;
            sub.address = "";

<<<<<<< HEAD
            if(mapValue["DS"] == "1")
            {
                sub.type = TransactionRecord::PrivateSend;
                CTxDestination address;
                if (ExtractDestination(wtx.vout[0].scriptPubKey, address))
                {
                    // Sent to GelCoin Address
                    sub.address = CBitcoinAddress(address).ToString();
                }
                else
                {
                    // Sent to IP, or other non-address transaction like OP_EVAL
                    sub.address = mapValue["to"];
                }
            }
            else
            {
                for (unsigned int nOut = 0; nOut < wtx.vout.size(); nOut++)
                {
                    const CTxOut& txout = wtx.vout[nOut];
                    sub.idx = parts.size();

                    if(CPrivateSend::IsCollateralAmount(txout.nValue)) sub.type = TransactionRecord::PrivateSendMakeCollaterals;
                    if(CPrivateSend::IsDenominatedAmount(txout.nValue)) sub.type = TransactionRecord::PrivateSendCreateDenominations;
                    if(nDebit - wtx.GetValueOut() == CPrivateSend::GetCollateralAmount()) sub.type = TransactionRecord::PrivateSendCollateralPayment;
=======
            if (mapValue["DS"] == "1") {
                sub.type = TransactionRecord::Obfuscated;
                CTxDestination address;
                if (ExtractDestination(wtx.vout[0].scriptPubKey, address)) {
                    // Sent to LUX Address
                    sub.address = CBitcoinAddress(address).ToString();
                } else {
                    // Sent to IP, or other non-address transaction like OP_EVAL
                    sub.address = mapValue["to"];
                }
            } else {
                for (unsigned int nOut = 0; nOut < wtx.vout.size(); nOut++) {
                    const CTxOut& txout = wtx.vout[nOut];
                    sub.idx = parts.size();

                    if (wallet->IsCollateralAmount(txout.nValue)) sub.type = TransactionRecord::ObfuscationMakeCollaterals;
                    if (wallet->IsDenominatedAmount(txout.nValue)) sub.type = TransactionRecord::ObfuscationCreateDenominations;
                    if (nDebit - wtx.GetValueOut() == DARKSEND_COLLATERAL) sub.type = TransactionRecord::ObfuscationCollateralPayment;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                }
            }

            CAmount nChange = wtx.GetChange();

            sub.debit = -(nDebit - nChange);
            sub.credit = nCredit - nChange;
            parts.append(sub);
<<<<<<< HEAD
            parts.last().involvesWatchAddress = involvesWatchAddress;   // maybe pass to TransactionRecord as constructor argument
        }
        else if (fAllFromMe)
        {
=======
            parts.last().involvesWatchAddress = involvesWatchAddress; // maybe pass to TransactionRecord as constructor argument
        } else if (fAllFromMe) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            //
            // Debit
            //
            CAmount nTxFee = nDebit - wtx.GetValueOut();

<<<<<<< HEAD
            for (unsigned int nOut = 0; nOut < wtx.vout.size(); nOut++)
            {
=======
            for (unsigned int nOut = 0; nOut < wtx.vout.size(); nOut++) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                const CTxOut& txout = wtx.vout[nOut];
                TransactionRecord sub(hash, nTime);
                sub.idx = parts.size();
                sub.involvesWatchAddress = involvesWatchAddress;

<<<<<<< HEAD
                if(wallet->IsMine(txout))
                {
=======
                if (wallet->IsMine(txout)) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                    // Ignore parts sent to self, as this is usually the change
                    // from a transaction sent back to our own address.
                    continue;
                }

                CTxDestination address;
<<<<<<< HEAD
                if (ExtractDestination(txout.scriptPubKey, address))
                {
                    // Sent to GelCoin Address
                    sub.type = TransactionRecord::SendToAddress;
                    sub.address = CBitcoinAddress(address).ToString();
                }
                else
                {
=======
                if (ExtractDestination(txout.scriptPubKey, address)) {
                    // Sent to LUX Address
                    sub.type = TransactionRecord::SendToAddress;
                    sub.address = CBitcoinAddress(address).ToString();
                } else {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                    // Sent to IP, or other non-address transaction like OP_EVAL
                    sub.type = TransactionRecord::SendToOther;
                    sub.address = mapValue["to"];
                }

<<<<<<< HEAD
                if(mapValue["DS"] == "1")
                {
                    sub.type = TransactionRecord::PrivateSend;
=======
                if (mapValue["DS"] == "1") {
                    sub.type = TransactionRecord::Obfuscated;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                }

                CAmount nValue = txout.nValue;
                /* Add fee to first output */
<<<<<<< HEAD
                if (nTxFee > 0)
                {
=======
                if (nTxFee > 0) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                    nValue += nTxFee;
                    nTxFee = 0;
                }
                sub.debit = -nValue;

                parts.append(sub);
            }
<<<<<<< HEAD
        }
        else
        {
=======
        } else {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            //
            // Mixed debit transaction, can't break down payees
            //
            parts.append(TransactionRecord(hash, nTime, TransactionRecord::Other, "", nNet, 0));
            parts.last().involvesWatchAddress = involvesWatchAddress;
        }
    }

    return parts;
}

<<<<<<< HEAD
void TransactionRecord::updateStatus(const CWalletTx &wtx)
=======
void TransactionRecord::updateStatus(const CWalletTx& wtx)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
{
    AssertLockHeld(cs_main);
    // Determine transaction status

    // Find the block the tx is in
    CBlockIndex* pindex = NULL;
    BlockMap::iterator mi = mapBlockIndex.find(wtx.hashBlock);
    if (mi != mapBlockIndex.end())
        pindex = (*mi).second;

    // Sort order, unrecorded transactions sort to the top
    status.sortKey = strprintf("%010d-%01d-%010u-%03d",
        (pindex ? pindex->nHeight : std::numeric_limits<int>::max()),
        (wtx.IsCoinBase() ? 1 : 0),
        wtx.nTimeReceived,
        idx);
    status.countsForBalance = wtx.IsTrusted() && !(wtx.GetBlocksToMaturity() > 0);
    status.depth = wtx.GetDepthInMainChain();
    status.cur_num_blocks = chainActive.Height();
<<<<<<< HEAD
    status.cur_num_ix_locks = nCompleteTXLocks;

    if (!CheckFinalTx(wtx))
    {
        if (wtx.nLockTime < LOCKTIME_THRESHOLD)
        {
            status.status = TransactionStatus::OpenUntilBlock;
            status.open_for = wtx.nLockTime - chainActive.Height();
        }
        else
        {
=======
    //status.cur_num_ix_locks = nCompleteTXLocks;

    if (!IsFinalTx(wtx, chainActive.Height() + 1)) {
        if (wtx.nLockTime < LOCKTIME_THRESHOLD) {
            status.status = TransactionStatus::OpenUntilBlock;
            status.open_for = wtx.nLockTime - chainActive.Height();
        } else {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            status.status = TransactionStatus::OpenUntilDate;
            status.open_for = wtx.nLockTime;
        }
    }
    // For generated transactions, determine maturity
<<<<<<< HEAD
    else if(type == TransactionRecord::Generated)
    {
        if (wtx.GetBlocksToMaturity() > 0)
        {
            status.status = TransactionStatus::Immature;

            if (wtx.IsInMainChain())
            {
=======
    else if (type == TransactionRecord::Generated || type == TransactionRecord::StakeMint || type == TransactionRecord::MNReward) {
        if (wtx.GetBlocksToMaturity() > 0) {
            status.status = TransactionStatus::Immature;

            if (wtx.IsInMainChain()) {
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
                status.matures_in = wtx.GetBlocksToMaturity();

                // Check if the block was requested by anyone
                if (GetAdjustedTime() - wtx.nTimeReceived > 2 * 60 && wtx.GetRequestCount() == 0)
                    status.status = TransactionStatus::MaturesWarning;
<<<<<<< HEAD
            }
            else
            {
                status.status = TransactionStatus::NotAccepted;
            }
        }
        else
        {
            status.status = TransactionStatus::Confirmed;
        }
    }
    else
    {
        if (status.depth < 0)
        {
            status.status = TransactionStatus::Conflicted;
        }
        else if (GetAdjustedTime() - wtx.nTimeReceived > 2 * 60 && wtx.GetRequestCount() == 0)
        {
            status.status = TransactionStatus::Offline;
        }
        else if (status.depth == 0)
        {
            status.status = TransactionStatus::Unconfirmed;
            if (wtx.isAbandoned())
                status.status = TransactionStatus::Abandoned;
        }
        else if (status.depth < RecommendedNumConfirmations)
        {
            status.status = TransactionStatus::Confirming;
        }
        else
        {
            status.status = TransactionStatus::Confirmed;
        }
    }

=======
            } else {
                status.status = TransactionStatus::NotAccepted;
            }
        } else {
            status.status = TransactionStatus::Confirmed;
        }
    } else {
        if (status.depth < 0) {
            status.status = TransactionStatus::Conflicted;
        } else if (GetAdjustedTime() - wtx.nTimeReceived > 2 * 60 && wtx.GetRequestCount() == 0) {
            status.status = TransactionStatus::Offline;
        } else if (status.depth == 0) {
            status.status = TransactionStatus::Unconfirmed;
        } else if (status.depth < RecommendedNumConfirmations) {
            status.status = TransactionStatus::Confirming;
        } else {
            status.status = TransactionStatus::Confirmed;
        }
    }
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

bool TransactionRecord::statusUpdateNeeded()
{
    AssertLockHeld(cs_main);
<<<<<<< HEAD
    return status.cur_num_blocks != chainActive.Height() || status.cur_num_ix_locks != nCompleteTXLocks;
=======
    return status.cur_num_blocks != chainActive.Height() /*|| status.cur_num_ix_locks != nCompleteTXLocks*/;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
}

QString TransactionRecord::getTxID() const
{
<<<<<<< HEAD
    return formatSubTxId(hash, idx);
}

QString TransactionRecord::formatSubTxId(const uint256 &hash, int vout)
{
    return QString::fromStdString(hash.ToString() + strprintf("-%03d", vout));
}

=======
    return QString::fromStdString(hash.ToString());
}

int TransactionRecord::getOutputIndex() const
{
    return idx;
}
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
