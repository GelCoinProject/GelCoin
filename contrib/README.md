Wallet Tools
---------------------

<<<<<<< HEAD
=======
### [BitRPC](/contrib/bitrpc) ###
Allows for sending of all standard Bitcoin commands via RPC rather than as command line args.

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
### [SpendFrom](/contrib/spendfrom) ###

Use the raw transactions API to send coins received on a particular
address (or addresses).

Repository Tools
---------------------

### [Developer tools](/contrib/devtools) ###
Specific tools for developers working on this repository.
Contains the script `github-merge.sh` for merging github pull requests securely and signing them using GPG.

<<<<<<< HEAD
### [Verify-Commits](/contrib/verify-commits) ###
Tool to verify that every merge commit was signed by a developer using the above `github-merge.sh` script.

=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
### [Linearize](/contrib/linearize) ###
Construct a linear, no-fork, best version of the blockchain.

### [Qos](/contrib/qos) ###

<<<<<<< HEAD
A Linux bash script that will set up traffic control (tc) to limit the outgoing bandwidth for connections to the GelCoin network. This means one can have an always-on gelcoind instance running, and another local gelcoind/gelcoin-qt instance which connects to this node and receives blocks from it.
=======
A Linux bash script that will set up traffic control (tc) to limit the outgoing bandwidth for connections to the Bitcoin network. This means one can have an always-on bitcoind instance running, and another local bitcoind/bitcoin-qt instance which connects to this node and receives blocks from it.
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

### [Seeds](/contrib/seeds) ###
Utility to generate the pnSeed[] array that is compiled into the client.

Build Tools and Keys
---------------------

### [Debian](/contrib/debian) ###
<<<<<<< HEAD
Contains files used to package gelcoind/gelcoin-qt
for Debian-based Linux systems. If you compile gelcoind/gelcoin-qt yourself, there are some useful files here.
=======
Contains files used to package bitcoind/bitcoin-qt
for Debian-based Linux systems. If you compile bitcoind/bitcoin-qt yourself, there are some useful files here.
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

### [Gitian-descriptors](/contrib/gitian-descriptors) ###
Gavin's notes on getting gitian builds up and running using KVM.

### [Gitian-downloader](/contrib/gitian-downloader)
Various PGP files of core developers. 

### [MacDeploy](/contrib/macdeploy) ###
Scripts and notes for Mac builds. 

Test and Verify Tools 
---------------------

### [TestGen](/contrib/testgen) ###
<<<<<<< HEAD
Utilities to generate test vectors for the data-driven GelCoin tests.
=======
Utilities to generate test vectors for the data-driven Bitcoin tests.
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

### [Test Patches](/contrib/test-patches) ###
These patches are applied when the automated pull-tester
tests each pull and when master is tested using jenkins.

### [Verify SF Binaries](/contrib/verifysfbinaries) ###
This script attempts to download and verify the signature file SHA256SUMS.asc from SourceForge.
