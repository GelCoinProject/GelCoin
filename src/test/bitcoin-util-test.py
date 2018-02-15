#!/usr/bin/python
# Copyright 2014 BitPay, Inc.
<<<<<<< HEAD
# Distributed under the MIT software license, see the accompanying
=======
# Distributed under the MIT/X11 software license, see the accompanying
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

import os
import bctest
import buildenv

if __name__ == '__main__':
	bctest.bctester(os.environ["srcdir"] + "/test/data",
			"bitcoin-util-test.json",buildenv)

