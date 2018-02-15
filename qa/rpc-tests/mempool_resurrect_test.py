#!/usr/bin/env python2
<<<<<<< HEAD
# Copyright (c) 2014-2015 The Bitcoin Core developers
=======
# Copyright (c) 2014 The Bitcoin Core developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

#
# Test resurrection of mined transactions when
# the blockchain is re-organized.
#

<<<<<<< HEAD
from test_framework.test_framework import BitcoinTestFramework
from test_framework.util import *
=======
from test_framework import BitcoinTestFramework
from bitcoinrpc.authproxy import AuthServiceProxy, JSONRPCException
from util import *
import os
import shutil
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

# Create one-input, one-output, no-fee transaction:
class MempoolCoinbaseTest(BitcoinTestFramework):

    def setup_network(self):
        # Just need one node for this test
        args = ["-checkmempool", "-debug=mempool"]
        self.nodes = []
        self.nodes.append(start_node(0, self.options.tmpdir, args))
        self.is_network_split = False

<<<<<<< HEAD
    def run_test(self):
        node0_address = self.nodes[0].getnewaddress()
=======
    def create_tx(self, from_txid, to_address, amount):
        inputs = [{ "txid" : from_txid, "vout" : 0}]
        outputs = { to_address : amount }
        rawtx = self.nodes[0].createrawtransaction(inputs, outputs)
        signresult = self.nodes[0].signrawtransaction(rawtx)
        assert_equal(signresult["complete"], True)
        return signresult["hex"]

    def run_test(self):
        node0_address = self.nodes[0].getnewaddress()

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        # Spend block 1/2/3's coinbase transactions
        # Mine a block.
        # Create three more transactions, spending the spends
        # Mine another block.
        # ... make sure all the transactions are confirmed
        # Invalidate both blocks
        # ... make sure all the transactions are put back in the mempool
        # Mine a new block
        # ... make sure all the transactions are confirmed again.

        b = [ self.nodes[0].getblockhash(n) for n in range(1, 4) ]
        coinbase_txids = [ self.nodes[0].getblock(h)['tx'][0] for h in b ]
<<<<<<< HEAD
        spends1_raw = [ create_tx(self.nodes[0], txid, node0_address, 500) for txid in coinbase_txids ]
        spends1_id = [ self.nodes[0].sendrawtransaction(tx) for tx in spends1_raw ]

        blocks = []
        blocks.extend(self.nodes[0].generate(1))

        spends2_raw = [ create_tx(self.nodes[0], txid, node0_address, 499.99) for txid in spends1_id ]
        spends2_id = [ self.nodes[0].sendrawtransaction(tx) for tx in spends2_raw ]

        blocks.extend(self.nodes[0].generate(1))
=======
        spends1_raw = [ self.create_tx(txid, node0_address, 50) for txid in coinbase_txids ]
        spends1_id = [ self.nodes[0].sendrawtransaction(tx) for tx in spends1_raw ]

        blocks = []
        blocks.extend(self.nodes[0].setgenerate(True, 1))

        spends2_raw = [ self.create_tx(txid, node0_address, 49.99) for txid in spends1_id ]
        spends2_id = [ self.nodes[0].sendrawtransaction(tx) for tx in spends2_raw ]

        blocks.extend(self.nodes[0].setgenerate(True, 1))
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

        # mempool should be empty, all txns confirmed
        assert_equal(set(self.nodes[0].getrawmempool()), set())
        for txid in spends1_id+spends2_id:
            tx = self.nodes[0].gettransaction(txid)
            assert(tx["confirmations"] > 0)

        # Use invalidateblock to re-org back; all transactions should
        # end up unconfirmed and back in the mempool
        for node in self.nodes:
            node.invalidateblock(blocks[0])

        # mempool should be empty, all txns confirmed
        assert_equal(set(self.nodes[0].getrawmempool()), set(spends1_id+spends2_id))
        for txid in spends1_id+spends2_id:
            tx = self.nodes[0].gettransaction(txid)
            assert(tx["confirmations"] == 0)

        # Generate another block, they should all get mined
<<<<<<< HEAD
        self.nodes[0].generate(1)
=======
        self.nodes[0].setgenerate(True, 1)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        # mempool should be empty, all txns confirmed
        assert_equal(set(self.nodes[0].getrawmempool()), set())
        for txid in spends1_id+spends2_id:
            tx = self.nodes[0].gettransaction(txid)
            assert(tx["confirmations"] > 0)


if __name__ == '__main__':
    MempoolCoinbaseTest().main()
