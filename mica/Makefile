# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.

include $(TOPDIR)/rules.mk

PKG_NAME:=mica
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/mica
  TITLE:=MiCa Smart board support package
  DEPENDS:=@TARGET_ramips_mt7688 \
  	+gdbserver +curl +strace +coreutils +coreutils-stty \
  	+avahi-nodbus-daemon +mountd +mjpg-streamer \
	+uhttpd +rpcd +rpcd-mod-iwinfo +git +git-http \
	+python +python-pyserial +python-pip +hidapi \
	+libstdcpp \
	+luci +luci-theme-openwrt +luci-app-mjpg-streamer +luci-lib-json \
	+rpcd-mod-rpcsys +cgi-io +avrdude +spi-tools +uboot-envtools \
	+kmod-fs-vfat +kmod-fs-exfat +kmod-i2c-core \
	+kmod-nls-base +kmod-nls-cp437 +kmod-nls-iso8859-1 \
	+kmod-nls-iso8859-15 +kmod-nls-iso8859-2 +kmod-nls-utf8 \
	+kmod-sdhci +kmod-sdhci-mt7620 +kmod-usb-storage \
	+kmod-video-core +kmod-video-uvc \
	+tcpdump-mini +mica-webui \
	+kmod-mt76 +nano +kmod-fs-ext4 +kmod-fs-nfs +kmod-fs-ntfs \
	+kmod-i2c-mt7628 +kmod-usb-hid +kmod-pwm-mediatek \
	
   #+libmraa +libupm +node +node-hid +node-cylon-firmata

  CATEGORY:=MiCa
  DEFAULT:=y
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
endef

define Build/Compile
        $(TARGET_CC) $(TARGET_CFLAGS) $(EXTRA_CFLAGS) -Wall -Werror -o $(PKG_BUILD_DIR)/pinmux src/pinmux.c ; \
        $(TARGET_CC) $(TARGET_CFLAGS) $(EXTRA_CFLAGS) -Wall -Werror -o $(PKG_BUILD_DIR)/refclk src/refclk.c
endef

define Package/mica/install
	$(INSTALL_DIR) $(1)/sbin
	
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/pinmux $(1)/sbin/mt7688_pinmux
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/refclk $(1)/sbin/mt7688_reclk
	$(CP) ./files/* $(1)
endef

$(eval $(call BuildPackage,mica))
