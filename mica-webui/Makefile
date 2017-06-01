#
# Copyright (C) 2015 John Crispin <blogic@openwrt.org>
#
# This is free software, licensed under the GPL 2 license.
#

include $(TOPDIR)/rules.mk


PKG_NAME:=mica-webui
PKG_VERSION:=2016-04-10
PKG_RELEASE=$(PKG_SOURCE_VERSION)


PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/MiCa-boards/MiCa7688-WebUI.git
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=master
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.gz

include $(INCLUDE_DIR)/package.mk

define Package/mica-webui
  TITLE:=MiCa7688 Webui
  DEPENDS:=@TARGET_ramips_mt7688
  HIDDEN:=1
endef

define Build/Configure
	true
endef

define Build/Compile
	true
endef

define Package/mica-webui/install
	$(INSTALL_DIR) $(1)/www/build
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/app/build/* $(1)/www/build/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/app/index.html $(1)/www/index_7688.html
endef

$(eval $(call BuildPackage,mica-webui))
