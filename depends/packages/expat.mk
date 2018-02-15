package=expat
<<<<<<< HEAD
$(package)_version=2.1.0
$(package)_download_path=http://sourceforge.net/projects/expat/files/expat/$($(package)_version)
$(package)_file_name=$(package)-$($(package)_version).tar.gz
$(package)_sha256_hash=823705472f816df21c8f6aa026dd162b280806838bb55b3432b0fb1fcca7eb86
=======
$(package)_version=2.2.0
$(package)_download_path=https://downloads.sourceforge.net/project/expat/expat/$($(package)_version)
$(package)_file_name=$(package)-$($(package)_version).tar.bz2
$(package)_sha256_hash=d9e50ff2d19b3538bd2127902a89987474e1a4db8e43a66a4d1a712ab9a504ff
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

define $(package)_set_vars
$(package)_config_opts=--disable-static
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
