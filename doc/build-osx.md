Mac OS X Build Instructions and Notes
====================================
<<<<<<< HEAD
This guide will show you how to build gelcoind (headless client) for OSX.
=======
This guide will show you how to build luxd (headless client) for OSX.
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

Notes
-----

<<<<<<< HEAD
* Tested on OS X 10.7 through 10.11 on 64-bit Intel processors only.
=======
* Tested on OS X 10.7 through 10.10 on 64-bit Intel processors only.
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

* All of the commands should be executed in a Terminal application. The
built-in one is located in `/Applications/Utilities`.

Preparation
-----------

<<<<<<< HEAD
You need to install Xcode with all the options checked so that the compiler
and everything is available in /usr not just /Developer. Xcode should be
=======
You need to install XCode with all the options checked so that the compiler
and everything is available in /usr not just /Developer. XCode should be
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
available on your OS X installation media, but if not, you can get the
current version from https://developer.apple.com/xcode/. If you install
Xcode 4.3 or later, you'll need to install its command line tools. This can
be done in `Xcode > Preferences > Downloads > Components` and generally must
be re-done or updated every time Xcode is updated.

<<<<<<< HEAD
You will also need to install [Homebrew](http://brew.sh) in order to install library
dependencies.

The installation of the actual dependencies is covered in the instructions
=======
There's also an assumption that you already have `git` installed. If
not, it's the path of least resistance to install [Github for Mac](https://mac.github.com/)
(OS X 10.7+) or
[Git for OS X](https://code.google.com/p/git-osx-installer/). It is also
available via Homebrew.

You will also need to install [Homebrew](http://brew.sh) in order to install library
dependencies.

The installation of the actual dependencies is covered in the Instructions
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
sections below.

Instructions: Homebrew
----------------------

#### Install dependencies using Homebrew

<<<<<<< HEAD
    brew install autoconf automake berkeley-db4 libtool boost miniupnpc openssl pkg-config protobuf libevent qt

NOTE: Building with Qt4 is still supported, however, doing so could result in a broken UI. Therefore, building with Qt5 is recommended. Be aware that Qt5 5.7+ requires C++11 compiler support.

### Building GelCoin

1. Clone the GitHub tree to get the source code and go into the directory.

        git clone https://github.com/gelcoinpay/gelcoin.git
        cd gelcoin

2.  Build GelCoin:
    This will configure and build the headless gelcoin binaries as well as the gui (if Qt is found).
    You can disable the gui build by passing `--without-gui` to configure.

        ./autogen.sh
        ./configure
=======
        brew install autoconf automake berkeley-db4 libtool boost miniupnpc openssl pkg-config protobuf qt5 libzmq

### Building `luxd`

1. Clone the github tree to get the source code and go into the directory.

        git clone https://github.com/LUX-Project/LUX.git
        cd LUX

2.  Build luxd:

        ./autogen.sh
        ./configure --with-gui=qt5
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
        make

3.  It is also a good idea to build and run the unit tests:

        make check

<<<<<<< HEAD
4.  (Optional) You can also install gelcoind to your path:
=======
4.  (Optional) You can also install luxd to your path:
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

        make install

Use Qt Creator as IDE
------------------------
You can use Qt Creator as IDE, for debugging and for manipulating forms, etc.
<<<<<<< HEAD
Download Qt Creator from https://www.qt.io/download/. Download the "community edition" and only install Qt Creator (uncheck the rest during the installation process).

1. Make sure you installed everything through Homebrew mentioned above
2. Do a proper ./configure --enable-debug
3. In Qt Creator do "New Project" -> Import Project -> Import Existing Project
4. Enter "gelcoin-qt" as project name, enter src/qt as location
=======
Download Qt Creator from http://www.qt.io/download/. Download the "community edition" and only install Qt Creator (uncheck the rest during the installation process).

1. Make sure you installed everything through homebrew mentioned above
2. Do a proper ./configure --with-gui=qt5 --enable-debug
3. In Qt Creator do "New Project" -> Import Project -> Import Existing Project
4. Enter "lux-qt" as project name, enter src/qt as location
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
5. Leave the file selection as it is
6. Confirm the "summary page"
7. In the "Projects" tab select "Manage Kits..."
8. Select the default "Desktop" kit and select "Clang (x86 64bit in /usr/bin)" as compiler
<<<<<<< HEAD
9. Select LLDB as debugger (you might need to set the path to your installation)
=======
9. Select LLDB as debugger (you might need to set the path to your installtion)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
10. Start debugging with Qt Creator

Creating a release build
------------------------
<<<<<<< HEAD
You can ignore this section if you are building `gelcoind` for your own use.

gelcoind/gelcoin-cli binaries are not included in the GelCoin-Qt.app bundle.

If you are building `gelcoind` or `GelCoin` for others, your build machine should be set up
=======
You can ignore this section if you are building `luxd` for your own use.

luxd/lux-cli binaries are not included in the lux-Qt.app bundle.

If you are building `luxd` or `lux-qt` for others, your build machine should be set up
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
as follows for maximum compatibility:

All dependencies should be compiled with these flags:

 -mmacosx-version-min=10.7
 -arch x86_64
 -isysroot $(xcode-select --print-path)/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.7.sdk

<<<<<<< HEAD
Once dependencies are compiled, see [doc/release-process.md](release-process.md) for how the GelCoin
=======
Once dependencies are compiled, see release-process.md for how the LUX-Qt.app
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
bundle is packaged and signed to create the .dmg disk image that is distributed.

Running
-------

<<<<<<< HEAD
It's now available at `./gelcoind`, provided that you are still in the `src`
directory. We have to first create the RPC configuration file, though.

Run `./gelcoind` to get the filename where it should be put, or just try these
commands:

    echo -e "rpcuser=gelcoinrpc\nrpcpassword=$(xxd -l 16 -p /dev/urandom)" > "/Users/${USER}/Library/Application Support/GelCoinCore/gelcoin.conf"
    chmod 600 "/Users/${USER}/Library/Application Support/GelCoinCore/gelcoin.conf"
=======
It's now available at `./luxd`, provided that you are still in the `src`
directory. We have to first create the RPC configuration file, though.

Run `./luxd` to get the filename where it should be put, or just try these
commands:

    echo -e "rpcuser=luxrpc\nrpcpassword=$(xxd -l 16 -p /dev/urandom)" > "/Users/${USER}/Library/Application Support/LUX/lux.conf"
    chmod 600 "/Users/${USER}/Library/Application Support/LUX/lux.conf"
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

The next time you run it, it will start downloading the blockchain, but it won't
output anything while it's doing this. This process may take several hours;
you can monitor its process by looking at the debug.log file, like this:

<<<<<<< HEAD
    tail -f $HOME/Library/Application\ Support/GelCoinCore/debug.log
=======
    tail -f $HOME/Library/Application\ Support/LUX/debug.log
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

Other commands:
-------

<<<<<<< HEAD
    ./gelcoind -daemon # to start the gelcoin daemon.
    ./gelcoin-cli --help  # for a list of command-line options.
    ./gelcoin-cli help    # When the daemon is running, to get a list of RPC commands
=======
    ./luxd -daemon # to start the lux daemon.
    ./lux-cli --help  # for a list of command-line options.
    ./lux-cli help    # When the daemon is running, to get a list of RPC commands
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
