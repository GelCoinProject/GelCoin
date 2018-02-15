<<<<<<< HEAD
GelCoin 0.12.1
=====================

This is the official reference wallet for GelCoin digital currency and comprises the backbone of the GelCoin peer-to-peer network. You can [download GelCoin](https://www.gelcoin.org/downloads/) or [build it yourself](#building) using the guides below.

Running
---------------------
The following are some helpful notes on how to run GelCoin on your native platform.
=======
LUX Core
=====================

Setup
---------------------
[LUX Core](http://luxcore.io) is the original LUX client and it builds the backbone of the network. However, it downloads and stores the entire history of LUX transactions; depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more. Thankfully you only have to do this once.

Running
---------------------
The following are some helpful notes on how to run LUX on your native platform.
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

### Unix

Unpack the files into a directory and run:

<<<<<<< HEAD
- `bin/gelcoin-qt` (GUI) or
- `bin/gelcoind` (headless)

### Windows

Unpack the files into a directory, and then run gelcoin-qt.exe.

### OS X

Drag GelCoin-Qt to your applications folder, and then run GelCoin-Qt.

### Need Help?

* See the [GelCoin documentation](https://gelcoinpay.atlassian.net/wiki/display/DOC)
for help and more information.
* Ask for help on [#gelcoinpay](http://webchat.freenode.net?channels=gelcoinpay) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net?channels=gelcoinpay).
* Ask for help on the [GelCoinTalk](https://gelcointalk.org/) forums.

Building
---------------------
The following are developer notes on how to build GelCoin on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [OS X Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [OpenBSD Build Notes](build-openbsd.md)
=======
- bin/32/lux-qt (GUI, 32-bit) or bin/32/luxd (headless, 32-bit)
- bin/64/lux-qt (GUI, 64-bit) or bin/64/luxd (headless, 64-bit)

### Windows

Unpack the files into a directory, and then run lux-qt.exe.

### OSX

Drag LUX-Qt to your applications folder, and then run LUX-Qt.

### Need Help?

* See the documentation at the [LUX Wiki](https://github.com/216k155/lux/wiki) ***TODO***
for help and more information.
* Ask for help on [BitcoinTalk](https://bitcointalk.org/index.php?topic=2254046.0) or on the [LUX Telegram](https://t.me/LUXcoinOfficialChat).

Building
---------------------
The following are developer notes on how to build LUX on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [OSX Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
- [Gitian Building Guide](gitian-building.md)

Development
---------------------
<<<<<<< HEAD
The GelCoin repo's [root README](/README.md) contains relevant information on the development process and automated testing.
=======
The Lux repo's [root README](https://github.com/LUX-Project/LUX/blob/master/README.md) contains relevant information on the development process and automated testing.
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

- [Developer Notes](developer-notes.md)
- [Multiwallet Qt Development](multiwallet-qt.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
<<<<<<< HEAD
- Source Code Documentation ***TODO***
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [Unit Tests](unit-tests.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Shared Libraries](shared-libraries.md)
- [BIPS](bips.md)
- [Dnsseed Policy](dnsseed-policy.md)

### Resources
* Discuss on the [GelCoinTalk](https://gelcointalk.org/) forums, in the Development & Technical Discussion board.
* Discuss on [#gelcoinpay](http://webchat.freenode.net/?channels=gelcoinpay) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net/?channels=gelcoinpay).
=======
- [Source Code Documentation (External Link)](https://dev.visucore.com/bitcoin/doxygen/) ***TODO***
- [Translation Process](translation_process.md)
- [Unit Tests](unit-tests.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Dnsseed Policy](dnsseed-policy.md)

### Resources

* Discuss on the [BitcoinTalk](https://bitcointalk.org/index.php?topic=1262920.0) or the [LUX](http://forum.lux.org/) forum.
* Join the [LUX-Dev](https://lux-dev.slack.com/) Slack group ([Sign-Up](https://lux-dev.herokuapp.com/)).
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)

License
---------------------
<<<<<<< HEAD
Distributed under the [MIT software license](http://www.opensource.org/licenses/mit-license.php).
=======
Distributed under the [MIT/X11 software license](http://www.opensource.org/licenses/mit-license.php).
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
