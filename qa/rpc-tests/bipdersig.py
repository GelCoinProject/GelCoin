#!/usr/bin/env python2
<<<<<<< HEAD
# Copyright (c) 2014-2015 The Bitcoin Core developers
=======
# Copyright (c) 2014 The Bitcoin Core developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

#
# Test the BIP66 changeover logic
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

class BIP66Test(BitcoinTestFramework):

    def setup_network(self):
        self.nodes = []
        self.nodes.append(start_node(0, self.options.tmpdir, []))
        self.nodes.append(start_node(1, self.options.tmpdir, ["-blockversion=2"]))
        self.nodes.append(start_node(2, self.options.tmpdir, ["-blockversion=3"]))
        connect_nodes(self.nodes[1], 0)
        connect_nodes(self.nodes[2], 0)
        self.is_network_split = False
        self.sync_all()

    def run_test(self):
        cnt = self.nodes[0].getblockcount()

        # Mine some old-version blocks
<<<<<<< HEAD
        self.nodes[1].generate(100)
=======
        self.nodes[1].setgenerate(True, 100)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        self.sync_all()
        if (self.nodes[0].getblockcount() != cnt + 100):
            raise AssertionError("Failed to mine 100 version=2 blocks")

        # Mine 750 new-version blocks
        for i in xrange(15):
<<<<<<< HEAD
            self.nodes[2].generate(50)
=======
            self.nodes[2].setgenerate(True, 50)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        self.sync_all()
        if (self.nodes[0].getblockcount() != cnt + 850):
            raise AssertionError("Failed to mine 750 version=3 blocks")

        # TODO: check that new DERSIG rules are not enforced

        # Mine 1 new-version block
<<<<<<< HEAD
        self.nodes[2].generate(1)
        self.sync_all()
        if (self.nodes[0].getblockcount() != cnt + 851):
            raise AssertionError("Failed to mine a version=3 blocks")
=======
        self.nodes[2].setgenerate(True, 1)
        self.sync_all()
        if (self.nodes[0].getblockcount() != cnt + 851):
            raise AssertionFailure("Failed to mine a version=3 blocks")
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

        # TODO: check that new DERSIG rules are enforced

        # Mine 198 new-version blocks
        for i in xrange(2):
<<<<<<< HEAD
            self.nodes[2].generate(99)
=======
            self.nodes[2].setgenerate(True, 99)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        self.sync_all()
        if (self.nodes[0].getblockcount() != cnt + 1049):
            raise AssertionError("Failed to mine 198 version=3 blocks")

        # Mine 1 old-version block
<<<<<<< HEAD
        self.nodes[1].generate(1)
=======
        self.nodes[1].setgenerate(True, 1)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        self.sync_all()
        if (self.nodes[0].getblockcount() != cnt + 1050):
            raise AssertionError("Failed to mine a version=2 block after 949 version=3 blocks")

        # Mine 1 new-version blocks
<<<<<<< HEAD
        self.nodes[2].generate(1)
=======
        self.nodes[2].setgenerate(True, 1)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        self.sync_all()
        if (self.nodes[0].getblockcount() != cnt + 1051):
            raise AssertionError("Failed to mine a version=3 block")

        # Mine 1 old-version blocks
        try:
<<<<<<< HEAD
            self.nodes[1].generate(1)
=======
            self.nodes[1].setgenerate(True, 1)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
            raise AssertionError("Succeeded to mine a version=2 block after 950 version=3 blocks")
        except JSONRPCException:
            pass
        self.sync_all()
        if (self.nodes[0].getblockcount() != cnt + 1051):
            raise AssertionError("Accepted a version=2 block after 950 version=3 blocks")

        # Mine 1 new-version blocks
<<<<<<< HEAD
        self.nodes[2].generate(1)
=======
        self.nodes[2].setgenerate(True, 1)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        self.sync_all()
        if (self.nodes[0].getblockcount() != cnt + 1052):
            raise AssertionError("Failed to mine a version=3 block")

if __name__ == '__main__':
    BIP66Test().main()
