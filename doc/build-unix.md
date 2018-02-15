UNIX BUILD NOTES
====================
<<<<<<< HEAD
Some notes on how to build GelCoin in Unix.

(for OpenBSD specific instructions, see [build-openbsd.md](build-openbsd.md))

Note
---------------------
Always use absolute paths to configure and compile GelCoin and the dependencies,
=======
Some notes on how to build LUX in Unix.

Note
---------------------
Always use absolute paths to configure and compile lux and the dependencies,
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
for example, when specifying the the path of the dependency:

	../dist/configure --enable-cxx --disable-shared --with-pic --prefix=$BDB_PREFIX

Here BDB_PREFIX must absolute path - it is defined using $(pwd) which ensures
the usage of the absolute path.

To Build
---------------------

```bash
./autogen.sh
./configure
make
make install # optional
```

<<<<<<< HEAD
This will build gelcoin-qt as well if the dependencies are met.
=======
This will build lux-qt as well if the dependencies are met.
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

Dependencies
---------------------

These dependencies are required:

 Library     | Purpose          | Description
 ------------|------------------|----------------------
<<<<<<< HEAD
 libssl      | Crypto           | Random Number Generation, Elliptic Curve Cryptography
 libboost    | Utility          | Library for threading, data structures, etc
 libevent    | Networking       | OS independent asynchronous networking
=======
 libssl      | SSL Support      | Secure communications
 libboost    | Boost            | C++ Library
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

Optional dependencies:

 Library     | Purpose          | Description
 ------------|------------------|----------------------
 miniupnpc   | UPnP Support     | Firewall-jumping support
 libdb4.8    | Berkeley DB      | Wallet storage (only needed when wallet enabled)
 qt          | GUI              | GUI toolkit (only needed when GUI enabled)
 protobuf    | Payments in GUI  | Data interchange format used for payment protocol (only needed when GUI enabled)
 libqrencode | QR codes in GUI  | Optional for generating QR codes (only needed when GUI enabled)
<<<<<<< HEAD
 univalue    | Utility          | JSON parsing and encoding (bundled version will be used unless --with-system-univalue passed to configure)
 libzmq3     | ZMQ notification | Optional, allows generating ZMQ notifications (requires ZMQ version >= 4.x)
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

For the versions used in the release, see [release-process.md](release-process.md) under *Fetch and build inputs*.

System requirements
--------------------

C++ compilers are memory-hungry. It is recommended to have at least 1 GB of
<<<<<<< HEAD
memory available when compiling GelCoin. With 512MB of memory or less
=======
memory available when compiling LUX Core. With 512MB of memory or less
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
compilation will take much longer due to swap thrashing.

Dependency Build Instructions: Ubuntu & Debian
----------------------------------------------
Build requirements:

<<<<<<< HEAD
    sudo apt-get install build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils

On at least Ubuntu 14.04+ and Debian 7+ there are generic names for the
individual boost development packages, so the following can be used to only
install necessary parts of boost:

    sudo apt-get install libboost-system-dev libboost-filesystem-dev libboost-chrono-dev libboost-program-options-dev libboost-test-dev libboost-thread-dev

If that doesn't work, you can install all boost development packages with:

    sudo apt-get install libboost-all-dev

BerkeleyDB is required for the wallet. db4.8 packages are available [here](https://launchpad.net/~bitcoin/+archive/bitcoin).
You can add the repository and install using the following commands:

    sudo add-apt-repository ppa:bitcoin/bitcoin
    sudo apt-get update
    sudo apt-get install libdb4.8-dev libdb4.8++-dev

Ubuntu and Debian have their own libdb-dev and libdb++-dev packages, but these will install
BerkeleyDB 5.1 or later, which break binary wallet compatibility with the distributed executables which
are based on BerkeleyDB 4.8. If you do not care about wallet compatibility,
pass `--with-incompatible-bdb` to configure.

See the section "Disable-wallet mode" to build GelCoin without wallet.

Optional:

    sudo apt-get install libminiupnpc-dev (see --with-miniupnpc and --enable-upnp-default)

ZMQ dependencies:

    sudo apt-get install libzmq3-dev (provides ZMQ API 4.x)
=======
	sudo apt-get install build-essential libtool autotools-dev autoconf pkg-config libssl-dev

For Ubuntu 12.04 and later or Debian 7 and later libboost-all-dev has to be installed:

	sudo apt-get install libboost-all-dev

 db4.8 packages are available [here](https://launchpad.net/~bitcoin/+archive/bitcoin).
 You can add the repository using the following command:

        sudo add-apt-repository ppa:bitcoin/bitcoin
        sudo apt-get update

 Ubuntu 12.04 and later have packages for libdb5.1-dev and libdb5.1++-dev,
 but using these will break binary wallet compatibility, and is not recommended.

For other Debian & Ubuntu (with ppa):

	sudo apt-get install libdb4.8-dev libdb4.8++-dev

Optional:

	sudo apt-get install libminiupnpc-dev (see --with-miniupnpc and --enable-upnp-default)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

Dependencies for the GUI: Ubuntu & Debian
-----------------------------------------

<<<<<<< HEAD
If you want to build GelCoin-Qt, make sure that the required packages for Qt development
are installed. Either Qt 5 or Qt 4 are necessary to build the GUI.
If both Qt 4 and Qt 5 are installed, Qt 5 will be used. Pass `--with-gui=qt4` to configure to choose Qt4.
To build without GUI pass `--without-gui`.

To build with Qt 5 (recommended) you need the following:

    sudo apt-get install libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler

Alternatively, to build with Qt 4 you need the following:

    sudo apt-get install libqt4-dev libprotobuf-dev protobuf-compiler

=======
If you want to build LUX-Qt, make sure that the required packages for Qt development
are installed. Qt 5 is necessary to build the GUI.
If both Qt 4 and Qt 5 are installed, Qt 5 will be used.
To build without GUI pass `--without-gui`.

For Qt 5 you need the following:

    sudo apt-get install libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
libqrencode (optional) can be installed with:

    sudo apt-get install libqrencode-dev

<<<<<<< HEAD
Once these are installed, they will be found by configure and a gelcoin-qt executable will be
=======
Once these are installed, they will be found by configure and a lux-qt executable will be
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
built by default.

Notes
-----
<<<<<<< HEAD
The release is built with GCC and then "strip gelcoind" to strip the debug
=======
The release is built with GCC and then "strip luxd" to strip the debug
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
symbols, which reduces the executable size by about 90%.


miniupnpc
---------

[miniupnpc](http://miniupnp.free.fr/) may be used for UPnP port mapping.  It can be downloaded from [here](
http://miniupnp.tuxfamily.org/files/).  UPnP support is compiled in and
turned off by default.  See the configure options for upnp behavior desired:

	--without-miniupnpc      No UPnP support miniupnp not required
	--disable-upnp-default   (the default) UPnP support turned off by default at runtime
	--enable-upnp-default    UPnP support turned on by default at runtime

<<<<<<< HEAD
=======
To build:

	tar -xzvf miniupnpc-1.6.tar.gz
	cd miniupnpc-1.6
	make
	sudo su
	make install

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

Berkeley DB
-----------
It is recommended to use Berkeley DB 4.8. If you have to build it yourself:

```bash
<<<<<<< HEAD
GEL_ROOT=$(pwd)

# Pick some path to install BDB to, here we create a directory within the gelcoin directory
BDB_PREFIX="${GEL_ROOT}/db4"
=======
LUX_ROOT=$(pwd)

# Pick some path to install BDB to, here we create a directory within the lux directory
BDB_PREFIX="${LUX_ROOT}/db4"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
mkdir -p $BDB_PREFIX

# Fetch the source and verify that it is not tampered with
wget 'http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz'
echo '12edc0df75bf9abd7f82f821795bcee50f42cb2e5f76a6a281b85732798364ef  db-4.8.30.NC.tar.gz' | sha256sum -c
# -> db-4.8.30.NC.tar.gz: OK
tar -xzvf db-4.8.30.NC.tar.gz

# Build the library and install to our prefix
cd db-4.8.30.NC/build_unix/
<<<<<<< HEAD
#  Note: Do a static build so that it can be embedded into the executable, instead of having to find a .so at runtime
../dist/configure --enable-cxx --disable-shared --with-pic --prefix=$BDB_PREFIX
make install

# Configure GelCoin to use our own-built instance of BDB
cd $GEL_ROOT
./autogen.sh
./configure LDFLAGS="-L${BDB_PREFIX}/lib/" CPPFLAGS="-I${BDB_PREFIX}/include/" # (other args...)
=======
#  Note: Do a static build so that it can be embedded into the exectuable, instead of having to find a .so at runtime
../dist/configure --enable-cxx --disable-shared --with-pic --prefix=$BDB_PREFIX
make install

# Configure LUX Core to use our own-built instance of BDB
cd $LUX_ROOT
./configure (other args...) LDFLAGS="-L${BDB_PREFIX}/lib/" CPPFLAGS="-I${BDB_PREFIX}/include/"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
```

**Note**: You only need Berkeley DB if the wallet is enabled (see the section *Disable-Wallet mode* below).

Boost
-----
If you need to build Boost yourself:

	sudo su
	./bootstrap.sh
	./bjam install


Security
--------
<<<<<<< HEAD
To help make your GelCoin installation more secure by making certain attacks impossible to
=======
To help make your LUX installation more secure by making certain attacks impossible to
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
exploit even if a vulnerability is found, binaries are hardened by default.
This can be disabled with:

Hardening Flags:

	./configure --enable-hardening
	./configure --disable-hardening


Hardening enables the following features:

* Position Independent Executable
    Build position independent code to take advantage of Address Space Layout Randomization
<<<<<<< HEAD
    offered by some kernels. Attackers who can cause execution of code at an arbitrary memory
    location are thwarted if they don't know where anything useful is located.
    The stack and heap are randomly located by default but this allows the code section to be
    randomly located as well.

    On an AMD64 processor where a library was not compiled with -fPIC, this will cause an error
=======
    offered by some kernels. An attacker who is able to cause execution of code at an arbitrary
    memory location is thwarted if he doesn't know where anything useful is located.
    The stack and heap are randomly located by default but this allows the code section to be
    randomly located as well.

    On an Amd64 processor where a library was not compiled with -fPIC, this will cause an error
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    such as: "relocation R_X86_64_32 against `......' can not be used when making a shared object;"

    To test that you have built PIE executable, install scanelf, part of paxutils, and use:

<<<<<<< HEAD
    	scanelf -e ./gelcoind

    The output should contain:

=======
    	scanelf -e ./luxd

    The output should contain:
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
     TYPE
    ET_DYN

* Non-executable Stack
    If the stack is executable then trivial stack based buffer overflow exploits are possible if
<<<<<<< HEAD
    vulnerable buffers are found. By default, GelCoin should be built with a non-executable stack
=======
    vulnerable buffers are found. By default, lux should be built with a non-executable stack
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    but if one of the libraries it uses asks for an executable stack or someone makes a mistake
    and uses a compiler extension which requires an executable stack, it will silently build an
    executable without the non-executable stack protection.

    To verify that the stack is non-executable after compiling use:
<<<<<<< HEAD
    `scanelf -e ./gelcoind`
=======
    `scanelf -e ./luxd`
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

    the output should contain:
	STK/REL/PTL
	RW- R-- RW-

    The STK RW- means that the stack is readable and writeable but not executable.
<<<<<<< HEAD

Disable-wallet mode
--------------------
When the intention is to run only a P2P node without a wallet, GelCoin may be compiled in
disable-wallet mode with:

    ./configure --disable-wallet

In this case there is no dependency on Berkeley DB 4.8.

Mining is also possible in disable-wallet mode, but only using the `getblocktemplate` RPC
call not `getwork`.

Additional Configure Flags
--------------------------
A list of additional configure flags can be displayed with:

    ./configure --help

ARM Cross-compilation
-------------------
These steps can be performed on, for example, an Ubuntu VM. The depends system
will also work on other Linux distributions, however the commands for
installing the toolchain will be different.

First install the toolchain:

    sudo apt-get install g++-arm-linux-gnueabihf

To build executables for ARM:

    cd depends
    make HOST=arm-linux-gnueabihf NO_QT=1
    cd ..
    ./configure --prefix=$PWD/depends/arm-linux-gnueabihf --enable-glibc-back-compat --enable-reduce-exports LDFLAGS=-static-libstdc++
    make


For further documentation on the depends system see [README.md](../depends/README.md) in the depends directory.
=======
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
