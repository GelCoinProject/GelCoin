package=freetype
<<<<<<< HEAD
$(package)_version=2.5.3
$(package)_download_path=http://downloads.sourceforge.net/$(package)
$(package)_file_name=$(package)-$($(package)_version).tar.bz2
$(package)_sha256_hash=c0848b29d52ef3ca27ad92e08351f023c5e24ce8cea7d8fe69fc96358e65f75e
=======
$(package)_version=2.7.1
$(package)_download_path=http://download.savannah.gnu.org/releases/$(package)
$(package)_file_name=$(package)-$($(package)_version).tar.bz2
$(package)_sha256_hash=3a3bb2c4e15ffb433f2032f50a5b5a92558206822e22bfe8cbe339af4aa82f88
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

define $(package)_set_vars
  $(package)_config_opts=--without-zlib --without-png --disable-static
  $(package)_config_opts_linux=--with-pic
endef

define $(package)_config_cmds
  $($(package)_autoconf)
endef

define $(package)_build_cmds
  $(MAKE)
endef

define $(package)_stage_cmds
  $(MAKE) DESTDIR=$($(package)_staging_dir) install
endef
