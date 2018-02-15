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
# Test -reindex and -reindex-chainstate with CheckBlockIndex
#
from test_framework.test_framework import BitcoinTestFramework
from test_framework.util import *
import time
=======
# Test -reindex with CheckBlockIndex
#
from test_framework import BitcoinTestFramework
from bitcoinrpc.authproxy import AuthServiceProxy, JSONRPCException
from util import *
import os.path
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

class ReindexTest(BitcoinTestFramework):

    def setup_chain(self):
        print("Initializing test directory "+self.options.tmpdir)
        initialize_chain_clean(self.options.tmpdir, 1)

    def setup_network(self):
        self.nodes = []
        self.is_network_split = False
        self.nodes.append(start_node(0, self.options.tmpdir))

<<<<<<< HEAD
    def reindex(self, justchainstate=False):
        self.nodes[0].generate(3)
        blockcount = self.nodes[0].getblockcount()
        stop_node(self.nodes[0], 0)
        wait_bitcoinds()
        self.nodes[0]=start_node(0, self.options.tmpdir, ["-debug", "-reindex-chainstate" if justchainstate else "-reindex", "-checkblockindex=1"])
        while self.nodes[0].getblockcount() < blockcount:
            time.sleep(0.1)
        assert_equal(self.nodes[0].getblockcount(), blockcount)
        print("Success")

    def run_test(self):
        self.reindex(False)
        self.reindex(True)
        self.reindex(False)
        self.reindex(True)
=======
    def run_test(self):
        self.nodes[0].generate(3)
        stop_node(self.nodes[0], 0)
        wait_bitcoinds()
        self.nodes[0]=start_node(0, self.options.tmpdir, ["-debug", "-reindex", "-checkblockindex=1"])
        assert_equal(self.nodes[0].getblockcount(), 3)
        print "Success"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

if __name__ == '__main__':
    ReindexTest().main()
