#!/bin/sh
append DRIVERS "ralink"

devidx=0

write_ralink() {
	local dir=$1
	local devtype=$2
	local dev=$3
	local mode=$4
	local channel=$5
	local sta=apcli0

	[ -d /sys/module/$dir ] || return
	[ -d "/sys/class/net/$dev" ] || return
	MAC=$(dd bs=1 skip=7 count=3 if=/dev/mtd2 2>/dev/null | hexdump -v -n 3 -e '3/1 "%02X"')
	SSID=MT_Base_${MAC}

        uci -q batch <<EOF

    set wireless.radio0=wifi-device
	set wireless.radio0.type='ralink'
	set wireless.radio0.variant='$devtype'
	set wireless.radio0.country='BE'
	set wireless.radio0.hwmode='$mode'
	set wireless.radio0.htmode='HT40'
	set wireless.radio0.channel=auto
	set wireless.radio0.disabled='1'
	set wireless.radio0.mica_mode='ap'
	set wireless.ap=wifi-iface
	set wireless.ap.device='radio0'
	set wireless.ap.mode='ap'
	set wireless.ap.network='lan'
	set wireless.ap.ifname='$dev'
	set wireless.ap.ssid='Openwrt'
	set wireless.ap.encryption='none' 
	set wireless.sta=wifi-iface
	set wireless.sta.device='radio0'
	set wireless.sta.mode='sta'
	set wireless.sta.network='wan'
	set wireless.sta.ifname='$sta'
	set wireless.sta.ssid='UplinkAp'
	set wireless.sta.key='SecretKey'
	set wireless.sta.encryption='none'
	
EOF
        uci -q commit wireless
}

detect_ralink() {
	[ -z "$(uci get wireless.@wifi-device[-1].type 2> /dev/null)" ] || return 0

	cpu=$(awk 'BEGIN{FS="[ \t]+: MediaTek[ \t]"} /system type/ {print $2}' /proc/cpuinfo | cut -d" " -f1)
	case $cpu in
	MT7688)
		write_ralink mt_wifi mt7628 ra0 11g
		;;
	esac

	return 0
}
