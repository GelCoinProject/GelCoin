#!/usr/bin/env python2
<<<<<<< HEAD
# Copyright (c) 2014-2015 The Bitcoin Core developers
=======
# Copyright (c) 2014 The Bitcoin Core developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

#
<<<<<<< HEAD
# Test proper accounting with a double-spend conflict
#

from test_framework.test_framework import BitcoinTestFramework
from test_framework.util import *
=======
# Test proper accounting with malleable transactions
#

from test_framework import BitcoinTestFramework
from bitcoinrpc.authproxy import AuthServiceProxy, JSONRPCException
from decimal import Decimal
from util import *
import os
import shutil
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

class TxnMallTest(BitcoinTestFramework):

    def add_options(self, parser):
        parser.add_option("--mineblock", dest="mine_block", default=False, action="store_true",
                          help="Test double-spend of 1-confirmed transaction")

    def setup_network(self):
        # Start with split network:
        return super(TxnMallTest, self).setup_network(True)

    def run_test(self):
<<<<<<< HEAD
        # All nodes should start with 12,500 GEL:
        starting_balance = 12500
=======
        # All nodes should start with 1,250 BTC:
        starting_balance = 1250
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        for i in range(4):
            assert_equal(self.nodes[i].getbalance(), starting_balance)
            self.nodes[i].getnewaddress("")  # bug workaround, coins generated assigned to first getnewaddress!
        
        # Assign coins to foo and bar accounts:
<<<<<<< HEAD
        node0_address_foo = self.nodes[0].getnewaddress("foo")
        fund_foo_txid = self.nodes[0].sendfrom("", node0_address_foo, 12190)
        fund_foo_tx = self.nodes[0].gettransaction(fund_foo_txid)

        node0_address_bar = self.nodes[0].getnewaddress("bar")
        fund_bar_txid = self.nodes[0].sendfrom("", node0_address_bar, 290)
        fund_bar_tx = self.nodes[0].gettransaction(fund_bar_txid)

        assert_equal(self.nodes[0].getbalance(""),
                     starting_balance - 12190 - 290 + fund_foo_tx["fee"] + fund_bar_tx["fee"])
=======
        self.nodes[0].move("", "foo", 1220)
        self.nodes[0].move("", "bar", 30)
        assert_equal(self.nodes[0].getbalance(""), 0)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

        # Coins are sent to node1_address
        node1_address = self.nodes[1].getnewaddress("from0")

<<<<<<< HEAD
        # First: use raw transaction API to send 12400 GEL to node1_address,
        # but don't broadcast:
        doublespend_fee = Decimal('-.02')
        rawtx_input_0 = {}
        rawtx_input_0["txid"] = fund_foo_txid
        rawtx_input_0["vout"] = find_output(self.nodes[0], fund_foo_txid, 12190)
        rawtx_input_1 = {}
        rawtx_input_1["txid"] = fund_bar_txid
        rawtx_input_1["vout"] = find_output(self.nodes[0], fund_bar_txid, 290)
        inputs = [rawtx_input_0, rawtx_input_1]
        change_address = self.nodes[0].getnewaddress()
        outputs = {}
        outputs[node1_address] = 12400
        outputs[change_address] = 12480 - 12400 + doublespend_fee
=======
        # First: use raw transaction API to send 1210 BTC to node1_address,
        # but don't broadcast:
        (total_in, inputs) = gather_inputs(self.nodes[0], 1210)
        change_address = self.nodes[0].getnewaddress("foo")
        outputs = {}
        outputs[change_address] = 40
        outputs[node1_address] = 1210
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        rawtx = self.nodes[0].createrawtransaction(inputs, outputs)
        doublespend = self.nodes[0].signrawtransaction(rawtx)
        assert_equal(doublespend["complete"], True)

<<<<<<< HEAD
        # Create two spends using 1 500 GEL coin each
        txid1 = self.nodes[0].sendfrom("foo", node1_address, 400, 0)
        txid2 = self.nodes[0].sendfrom("bar", node1_address, 200, 0)
        
        # Have node0 mine a block:
        if (self.options.mine_block):
            self.nodes[0].generate(1)
=======
        # Create two transaction from node[0] to node[1]; the
        # second must spend change from the first because the first
        # spends all mature inputs:
        txid1 = self.nodes[0].sendfrom("foo", node1_address, 1210, 0)
        txid2 = self.nodes[0].sendfrom("bar", node1_address, 20, 0)
        
        # Have node0 mine a block:
        if (self.options.mine_block):
            self.nodes[0].setgenerate(True, 1)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            sync_blocks(self.nodes[0:2])

        tx1 = self.nodes[0].gettransaction(txid1)
        tx2 = self.nodes[0].gettransaction(txid2)

<<<<<<< HEAD
        # Node0's balance should be starting balance, plus 500GEL for another
        # matured block, minus 400, minus 200, and minus transaction fees:
        expected = starting_balance + fund_foo_tx["fee"] + fund_bar_tx["fee"]
        if self.options.mine_block: expected += 500
=======
        # Node0's balance should be starting balance, plus 50BTC for another
        # matured block, minus 1210, minus 20, and minus transaction fees:
        expected = starting_balance
        if self.options.mine_block: expected += 50
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        expected += tx1["amount"] + tx1["fee"]
        expected += tx2["amount"] + tx2["fee"]
        assert_equal(self.nodes[0].getbalance(), expected)

        # foo and bar accounts should be debited:
<<<<<<< HEAD
        assert_equal(self.nodes[0].getbalance("foo", 0), 12190+tx1["amount"]+tx1["fee"])
        assert_equal(self.nodes[0].getbalance("bar", 0), 290+tx2["amount"]+tx2["fee"])
=======
        assert_equal(self.nodes[0].getbalance("foo"), 1220+tx1["amount"]+tx1["fee"])
        assert_equal(self.nodes[0].getbalance("bar"), 30+tx2["amount"]+tx2["fee"])
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

        if self.options.mine_block:
            assert_equal(tx1["confirmations"], 1)
            assert_equal(tx2["confirmations"], 1)
            # Node1's "from0" balance should be both transaction amounts:
            assert_equal(self.nodes[1].getbalance("from0"), -(tx1["amount"]+tx2["amount"]))
        else:
            assert_equal(tx1["confirmations"], 0)
            assert_equal(tx2["confirmations"], 0)
        
<<<<<<< HEAD
        # Now give doublespend and its parents to miner:
        self.nodes[2].sendrawtransaction(fund_foo_tx["hex"])
        self.nodes[2].sendrawtransaction(fund_bar_tx["hex"])
        doublespend_txid = self.nodes[2].sendrawtransaction(doublespend["hex"])
        # ... mine a block...
        self.nodes[2].generate(1)

        # Reconnect the split network, and sync chain:
        connect_nodes(self.nodes[1], 2)
        self.nodes[2].generate(1)  # Mine another block to make sure we sync
        sync_blocks(self.nodes)
        assert_equal(self.nodes[0].gettransaction(doublespend_txid)["confirmations"], 2)
=======
        # Now give doublespend to miner:
        mutated_txid = self.nodes[2].sendrawtransaction(doublespend["hex"])
        # ... mine a block...
        self.nodes[2].setgenerate(True, 1)

        # Reconnect the split network, and sync chain:
        connect_nodes(self.nodes[1], 2)
        self.nodes[2].setgenerate(True, 1)  # Mine another block to make sure we sync
        sync_blocks(self.nodes)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

        # Re-fetch transaction info:
        tx1 = self.nodes[0].gettransaction(txid1)
        tx2 = self.nodes[0].gettransaction(txid2)
<<<<<<< HEAD

        # Both transactions should be conflicted
        assert_equal(tx1["confirmations"], -2)
        assert_equal(tx2["confirmations"], -2)

        # Node0's total balance should be starting balance, plus 1000GEL for
        # two more matured blocks, minus 12400 for the double-spend, plus fees (which are
        # negative):
        expected = starting_balance + 1000 - 12400 + fund_foo_tx["fee"] + fund_bar_tx["fee"] + doublespend_fee
        assert_equal(self.nodes[0].getbalance(), expected)
        assert_equal(self.nodes[0].getbalance("*"), expected)

        # Final "" balance is starting_balance - amount moved to accounts - doublespend + subsidies +
        # fees (which are negative)
        assert_equal(self.nodes[0].getbalance("foo"), 12190)
        assert_equal(self.nodes[0].getbalance("bar"), 290)
        assert_equal(self.nodes[0].getbalance(""), starting_balance
                                                              -12190
                                                              -  290
                                                              -12400
                                                              + 1000
                                                              + fund_foo_tx["fee"]
                                                              + fund_bar_tx["fee"]
                                                              + doublespend_fee)

        # Node1's "from0" account balance should be just the doublespend:
        assert_equal(self.nodes[1].getbalance("from0"), 12400)

if __name__ == '__main__':
    TxnMallTest().main()

=======
        
        # Both transactions should be conflicted
        assert_equal(tx1["confirmations"], -1)
        assert_equal(tx2["confirmations"], -1)

        # Node0's total balance should be starting balance, plus 100BTC for 
        # two more matured blocks, minus 1210 for the double-spend:
        expected = starting_balance + 100 - 1210
        assert_equal(self.nodes[0].getbalance(), expected)
        assert_equal(self.nodes[0].getbalance("*"), expected)

        # foo account should be debited, but bar account should not:
        assert_equal(self.nodes[0].getbalance("foo"), 1220-1210)
        assert_equal(self.nodes[0].getbalance("bar"), 30)

        # Node1's "from" account balance should be just the mutated send:
        assert_equal(self.nodes[1].getbalance("from0"), 1210)

if __name__ == '__main__':
    TxnMallTest().main()
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
