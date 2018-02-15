<<<<<<< HEAD
packages:=boost openssl libevent
darwin_packages:=zeromq
linux_packages:=zeromq
native_packages := native_ccache native_comparisontool

qt_native_packages = native_protobuf
qt_packages = qrencode protobuf

qt_linux_packages= qt expat dbus libxcb xcb_proto libXau xproto freetype fontconfig libX11 xextproto libXext xtrans
qt_darwin_packages=qt
qt_mingw32_packages=qt


=======
packages:=boost openssl libevent zeromq
native_packages := native_ccache

qt_native_packages = native_protobuf
qt_packages = qrencode protobuf zlib

qt_x86_64_linux_packages:=qt expat dbus libxcb xcb_proto libXau xproto freetype fontconfig libX11 xextproto libXext xtrans
qt_i686_linux_packages:=$(qt_x86_64_linux_packages)
qt_arm_linux_packages:=$(qt_x86_64_linux_packages)
qt_aarch64_linux_packages:=$(qt_x86_64_linux_packages)

qt_darwin_packages=qt
qt_mingw32_packages=qt

>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
wallet_packages=bdb

upnp_packages=miniupnpc

<<<<<<< HEAD
ifneq ($(build_os),darwin)
darwin_native_packages=native_cctools native_cdrkit native_libdmg-hfsplus
=======
darwin_native_packages = native_biplist native_ds_store native_mac_alias

ifneq ($(build_os),darwin)
darwin_native_packages += native_cctools native_cdrkit native_libdmg-hfsplus
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
endif
