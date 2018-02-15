<<<<<<< HEAD
GelCoin version 0.12.2.3
==========================

Release is now available from:

  <https://www.gelcoin.org/downloads/#wallets>

This is a new minor version release, bringing various bugfixes and other
improvements.

Please report bugs using the issue tracker at github:

  <https://github.com/gelcoinpay/gelcoin/issues>


Upgrading and downgrading
=========================

How to Upgrade
--------------

If you are running an older version, shut it down. Wait until it has completely
shut down (which might take a few minutes for older versions), then run the
installer (on Windows) or just copy over /Applications/GelCoin-Qt (on Mac) or
gelcoind/gelcoin-qt (on Linux).

Downgrade warning
-----------------

### Downgrade to a version < 0.12.2.2

Because release 0.12.2.2 included the [per-UTXO fix](release-notes/gelcoin/release-notes-0.12.2.2.md#per-utxo-fix)
which changed the structure of the internal database, you will have to reindex
the database if you decide to use any pre-0.12.2.2 version.

Wallet forward or backward compatibility was not affected.

### Downgrade to 0.12.2.2

Downgrading to 0.12.2.2 does not require any additional actions, should be
fully compatible.

Notable changes
===============

InstantSend fixes
-----------------

Coin selection could work slightly incorrect in some edge cases which could
lead to a creation of an InstantSend transaction which only the local wallet
would consider to be a good candidate for a lock. Such txes was not locked by
the network but they were creating a confusion on the user side giving an
impression of a slightly higher InstantSend failure rate.

Another issue fixed in this release is that masternodes could vote for a tx
that is not going to be accepted to the mempool sometimes. This could lead to
a situation when user funds would be locked even though InstantSend transaction
would not show up on the receiving side.

Fix -liquidityprovider option
-----------------------------

Turned out that liquidityprovider mixing mode practically stopped working after
recent improvements in the PrivateSend mixing algorithm due to a suboptimal
looping which occurs only in this mode (due to a huge number of rounds). To fix
the issue a small part of the mixing algorithm was reverted to a pre-0.12.2 one
for this mode only. Regular users were not affected by the issue in any way and
will continue to use the improved one just like before.

Other improvements and bug fixes
--------------------------------

This release also fixes a few crashes and compatibility issues.


0.12.2.3 Change log
===================

See detailed [change log](https://github.com/gelcoinpay/gelcoin/compare/v0.12.2.2...gelcoinpay:v0.12.2.3) below.

### Backports:
- [`068b20bc7`](https://github.com/gelcoinpay/gelcoin/commit/068b20bc7) Merge #8256: BUG: bitcoin-qt crash
- [`f71ab1daf`](https://github.com/gelcoinpay/gelcoin/commit/f71ab1daf) Merge #11847: Fixes compatibility with boost 1.66 (#1836)

### PrivateSend:
- [`fa5fc418a`](https://github.com/gelcoinpay/gelcoin/commit/fa5fc418a) Fix -liquidityprovider option (#1829)
- [`d261575b4`](https://github.com/gelcoinpay/gelcoin/commit/d261575b4) Skip existing masternode conections on mixing (#1833)
- [`21a10057d`](https://github.com/gelcoinpay/gelcoin/commit/21a10057d) Protect CKeyHolderStorage via mutex (#1834)
- [`476888683`](https://github.com/gelcoinpay/gelcoin/commit/476888683) Avoid reference leakage in CKeyHolderStorage::AddKey (#1840)

### InstantSend:
- [`d6e2aa843`](https://github.com/gelcoinpay/gelcoin/commit/d6e2aa843) Swap iterations and fUseInstantSend parameters in ApproximateBestSubset (#1819)
- [`c9bafe154`](https://github.com/gelcoinpay/gelcoin/commit/c9bafe154) Vote on IS only if it was accepted to mempool (#1826)

### Other:
- [`ada41c3af`](https://github.com/gelcoinpay/gelcoin/commit/ada41c3af) Fix crash on exit when -createwalletbackups=0 (#1810)
- [`63e0e30e3`](https://github.com/gelcoinpay/gelcoin/commit/63e0e30e3) bump version to 0.12.2.3 (#1827)
=======
(note: this is a temporary file, to be added-to by anybody, and moved to release-notes at release time)

LUX Core version *version* is now available from:

  <https://github.com/216k155/lux/releases>

This is a new major version release, including various bug fixes and
performance improvements, as well as updated translations.

Please report bugs using the issue tracker at github:

  <https://github.com/216k155/lux/issues>

Mandatory Update
==============

LUX Core v3.0.0 is a mandatory update for all users. This release contains new consensus rules and improvements that are not backwards compatible with older versions. Users will have a grace period of one week to update their clients before enforcement of this update is enabled.

Users updating from a previous version after the 16th of October will require a full resync of their local blockchain from either the P2P network or by way of the bootstrap.

How to Upgrade
==============

If you are running an older version, shut it down. Wait until it has completely shut down (which might take a few minutes for older versions), then run the installer (on Windows) or just copy over /Applications/LUX-Qt (on Mac) or luxd/lux-qt (on Linux).

Compatibility
==============

LUX Core is extensively tested on multiple operating systems using
the Linux kernel, macOS 10.8+, and Windows Vista and later.

Microsoft ended support for Windows XP on [April 8th, 2014](https://www.microsoft.com/en-us/WindowsForBusiness/end-of-xp-support),
No attempt is made to prevent installing or running the software on Windows XP, you
can still do so at your own risk but be aware that there are known instabilities and issues.
Please do not report issues about Windows XP to the issue tracker.

LUX Core should also work on most other Unix-like systems but is not
frequently tested on them.

Notable Changes
===============

Zerocoin (zLUX) Protocol
---------------------

At long last, the zLUX release is here and the zerocoin protocol has been fully implemented! This allows users to send transactions with 100% fungible coins and absolutely zero history or link-ability to their previous owners.

Full and comprehensive details about the process and the use will be posted here during the days between Oct 6 and Oct 13.

Tor Service Integration Improvements
---------------------

Integrating with Tor is now easier than ever! Starting with Tor version 0.2.7.1 it is possible, through Tor's control socket API, to create and destroy 'ephemeral' hidden services programmatically. LUX Core has been updated to make use of this.

This means that if Tor is running (and proper authorization is available), LUX Core automatically creates a hidden service to listen on, without manual configuration. LUX Core will also use Tor automatically to connect to other .onion nodes if the control socket can be successfully opened. This will positively affect the number of available .onion nodes and their usage.

This new feature is enabled by default if LUX Core is listening, and a connection to Tor can be made. It can be configured with the `-listenonion`, `-torcontrol` and `-torpassword` settings. To show verbose debugging information, pass `-debug=tor`.

*version* Change log
=================

Detailed release notes follow. This overview includes changes that affect
behavior, not code moves, refactors and string updates. For convenience in locating
the code changes and accompanying discussion, both the pull request and
git merge commit are mentioned.

### Broad Features
- #264 `15e84e5` zLUX is here! (Fuzzbawls Mrs-X Presstab Spock LUX)

### P2P Protocol and Network Code
- #242 `0ecd77f` [P2P] Improve TOR service connectivity (Fuzzbawls)

### GUI
- #251 `79af8d2` [Qt] Adjust masternode count in information UI (Mrs-X)

### Miscellaneous
- #258 `c950765` [Depends] Update Depends with newer versions (Fuzzbawls)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

Credits
=======

Thanks to everyone who directly contributed to this release:
<<<<<<< HEAD

- Alexander Block
- lodgepole
- UdjinM6

As well as Bitcoin Core Developers and everyone that submitted issues,
reviewed pull requests or helped translating on
[Transifex](https://www.transifex.com/projects/p/gelcoin/).


Older releases
==============

GelCoin was previously known as Darkcoin.

Darkcoin tree 0.8.x was a fork of Litecoin tree 0.8, original name was XCoin
which was first released on Jan/18/2014.

Darkcoin tree 0.9.x was the open source implementation of masternodes based on
the 0.8.x tree and was first released on Mar/13/2014.

Darkcoin tree 0.10.x used to be the closed source implementation of Darksend
which was released open source on Sep/25/2014.

GelCoin tree 0.11.x was a fork of Bitcoin Core tree 0.9,
Darkcoin was rebranded to GelCoin.

GelCoin tree 0.12.0.x was a fork of Bitcoin Core tree 0.10.

GelCoin tree 0.12.1.x was a fork of Bitcoin Core tree 0.12.

These release are considered obsolete. Old release notes can be found here:

- [v0.12.2.2](release-notes/gelcoin/release-notes-0.12.2.2.md) released Dec/17/2017
- [v0.12.2](release-notes/gelcoin/release-notes-0.12.2.md) released Nov/08/2017
- [v0.12.1](release-notes/gelcoin/release-notes-0.12.1.md) released Feb/06/2017
- [v0.12.0](release-notes/gelcoin/release-notes-0.12.0.md) released Jun/15/2015
- [v0.11.2](release-notes/gelcoin/release-notes-0.11.2.md) released Mar/04/2015
- [v0.11.1](release-notes/gelcoin/release-notes-0.11.1.md) released Feb/10/2015
- [v0.11.0](release-notes/gelcoin/release-notes-0.11.0.md) released Jan/15/2015
- [v0.10.x](release-notes/gelcoin/release-notes-0.10.0.md) released Sep/25/2014
- [v0.9.x](release-notes/gelcoin/release-notes-0.9.0.md) released Mar/13/2014

=======
- Fuzzbawls
- Jon Spock
- Mrs-X
- LUX
- amirabrams
- presstab

As well as everyone that helped translating on [Transifex](https://www.transifex.com/projects/p/216k155-translations/).
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
