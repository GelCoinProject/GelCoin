<<<<<<< HEAD
// Copyright (c) 2012-2014 The Bitcoin Core developers
// Copyright (c) 2014-2017 The GelCoin developers
=======
// Copyright (c) 2012-2014 The Bitcoin developers       -*- c++ -*-
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The LUX developers
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_VERSION_H
#define BITCOIN_VERSION_H

/**
 * network protocol versioning
 */

<<<<<<< HEAD
static const int PROTOCOL_VERSION = 70208;
=======
static const int PROTOCOL_VERSION = 69200;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

//! initial proto version, to be increased after version/verack negotiation
static const int INIT_PROTO_VERSION = 209;

//! In this version, 'getheaders' was introduced.
static const int GETHEADERS_VERSION = 70077;

//! disconnect from peers older than this proto version
<<<<<<< HEAD
static const int MIN_PEER_PROTO_VERSION = 70208;
=======
static const int MIN_PEER_PROTO_VERSION_BEFORE_ENFORCEMENT = 69100;
static const int MIN_PEER_PROTO_VERSION_AFTER_ENFORCEMENT = 69100;

static const int MIN_INSTANTX_PROTO_VERSION = 69100;
static const int MIN_MN_PROTO_VERSION = 69100;
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

//! nTime field added to CAddress, starting with this version;
//! if possible, avoid requesting addresses nodes older than this
static const int CADDR_TIME_VERSION = 31402;

//! only request blocks from nodes outside this range of versions
static const int NOBLKS_VERSION_START = 32000;
static const int NOBLKS_VERSION_END = 32400;

//! BIP 0031, pong message, is enabled for all versions AFTER this one
static const int BIP0031_VERSION = 60000;

//! "mempool" command, enhanced "getdata" behavior starts with this version
<<<<<<< HEAD
static const int MEMPOOL_GD_VERSION = 60002;

//! "filter*" commands are disabled without NODE_BLOOM after and including this version
static const int NO_BLOOM_VERSION = 70201;

//! "sendheaders" command and announcing blocks with headers starts with this version
static const int SENDHEADERS_VERSION = 70201;

//! DIP0001 was activated in this version
static const int DIP0001_PROTOCOL_VERSION = 70208;
=======
static const int MEMPOOL_GD_VERSION = 60005;

//! "filter*" commands are disabled without NODE_BLOOM after and including this version
static const int NO_BLOOM_VERSION = 70005;

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

#endif // BITCOIN_VERSION_H
