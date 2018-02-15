
Debian
====================
<<<<<<< HEAD
This directory contains files used to package gelcoind/gelcoin-qt
for Debian-based Linux systems. If you compile gelcoind/gelcoin-qt yourself, there are some useful files here.

## gelcoin: URI support ##


gelcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install gelcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your gelcoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/gelcoin128.png` to `/usr/share/pixmaps`

gelcoin-qt.protocol (KDE)
=======
This directory contains files used to package luxd/lux-qt
for Debian-based Linux systems. If you compile luxd/lux-qt yourself, there are some useful files here.

## lux: URI support ##


lux-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install lux-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your luxqt binary to `/usr/bin`
and the `../../share/pixmaps/lux128.png` to `/usr/share/pixmaps`

lux-qt.protocol (KDE)
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

