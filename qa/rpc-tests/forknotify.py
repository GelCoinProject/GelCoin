#!/usr/bin/env python2
<<<<<<< HEAD
# Copyright (c) 2014-2015 The Bitcoin Core developers
=======
# Copyright (c) 2014 The Bitcoin Core developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

#
# Test -alertnotify 
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

class ForkNotifyTest(BitcoinTestFramework):

    alert_filename = None  # Set by setup_network

    def setup_network(self):
        self.nodes = []
        self.alert_filename = os.path.join(self.options.tmpdir, "alert.txt")
        with open(self.alert_filename, 'w') as f:
            pass  # Just open then close to create zero-length file
        self.nodes.append(start_node(0, self.options.tmpdir,
                            ["-blockversion=2", "-alertnotify=echo %s >> \"" + self.alert_filename + "\""]))
        # Node1 mines block.version=211 blocks
        self.nodes.append(start_node(1, self.options.tmpdir,
                                ["-blockversion=211"]))
        connect_nodes(self.nodes[1], 0)

        self.is_network_split = False
        self.sync_all()

    def run_test(self):
        # Mine 51 up-version blocks
<<<<<<< HEAD
        self.nodes[1].generate(51)
=======
        self.nodes[1].setgenerate(True, 51)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        self.sync_all()
        # -alertnotify should trigger on the 51'st,
        # but mine and sync another to give
        # -alertnotify time to write
<<<<<<< HEAD
        self.nodes[1].generate(1)
=======
        self.nodes[1].setgenerate(True, 1)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        self.sync_all()

        with open(self.alert_filename, 'r') as f:
            alert_text = f.read()

        if len(alert_text) == 0:
            raise AssertionError("-alertnotify did not warn of up-version blocks")

        # Mine more up-version blocks, should not get more alerts:
<<<<<<< HEAD
        self.nodes[1].generate(1)
        self.sync_all()
        self.nodes[1].generate(1)
=======
        self.nodes[1].setgenerate(True, 1)
        self.sync_all()
        self.nodes[1].setgenerate(True, 1)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        self.sync_all()

        with open(self.alert_filename, 'r') as f:
            alert_text2 = f.read()

        if alert_text != alert_text2:
            raise AssertionError("-alertnotify excessive warning of up-version blocks")

if __name__ == '__main__':
    ForkNotifyTest().main()
