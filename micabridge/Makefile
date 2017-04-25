#
# Copyright (C) 2006-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=micabridge
PKG_VERSION:=2016-04-10
PKG_RELEASE=$(PKG_SOURCE_VERSION)


PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/emavap/MiCaBridge.git
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=master
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.gz

include $(INCLUDE_DIR)/package.mk

define Package/micabridge
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Arduino Mica bridge library
  URL:=http://arduino.cc/
  DEPENDS:=+python
endef

define Package/micabridge/description
  Arduino MICA bridge library
endef

define Build/Compile
	true
endef

define Package/micabridge/install
	mkdir -p $(1)/usr/lib/python2.7/bridge
	$(CP) $(PKG_BUILD_DIR)/bridge/*.py $(1)/usr/lib/python2.7/bridge/
	$(CP) ./files/* $(1)
endef

$(eval $(call BuildPackage,micabridge))
