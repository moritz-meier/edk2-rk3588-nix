/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2000-2010
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * (C) Copyright 2001 Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Andreas Heppel <aheppel@sysgo.de>
 */

#include <config.h>
#include <env_callback.h>
#include <linux/stringify.h>

#include <generated/environment.h>

#ifdef DEFAULT_ENV_INSTANCE_EMBEDDED
env_t embedded_environment __UBOOT_ENV_SECTION__(environment) = {
	ENV_CRC,	/* CRC Sum */
#ifdef CONFIG_SYS_REDUNDAND_ENVIRONMENT
	1,		/* Flags: valid */
#endif
	{
#elif defined(DEFAULT_ENV_INSTANCE_STATIC)
static char default_environment[] = {
#elif defined(CONFIG_DEFAULT_ENV_IS_RW)
char default_environment[] = {
#else
const char default_environment[] = {
#endif
#ifndef CONFIG_USE_DEFAULT_ENV_FILE
#ifdef	CONFIG_ENV_CALLBACK_LIST_DEFAULT
	ENV_CALLBACK_VAR "=" CONFIG_ENV_CALLBACK_LIST_DEFAULT "\0"
#endif
#ifdef	CONFIG_ENV_FLAGS_LIST_DEFAULT
	ENV_FLAGS_VAR "=" CONFIG_ENV_FLAGS_LIST_DEFAULT "\0"
#endif
#ifdef	CONFIG_USE_BOOTARGS
	"bootargs="	CONFIG_BOOTARGS			"\0"
#endif
#ifdef	CONFIG_BOOTCOMMAND
	"bootcmd="	CONFIG_BOOTCOMMAND		"\0"
#endif
#if defined(CONFIG_BOOTDELAY)
	"bootdelay="	__stringify(CONFIG_BOOTDELAY)	"\0"
#endif
#if !defined(CONFIG_OF_SERIAL_BAUD) && defined(CONFIG_BAUDRATE) && (CONFIG_BAUDRATE >= 0)
	"baudrate="	__stringify(CONFIG_BAUDRATE)	"\0"
#endif
#ifdef	CONFIG_LOADS_ECHO
	"loads_echo="	__stringify(CONFIG_LOADS_ECHO)	"\0"
#endif
#ifdef	CONFIG_ETHPRIME
	"ethprime="	CONFIG_ETHPRIME			"\0"
#endif
#ifdef	CONFIG_USE_IPADDR
	"ipaddr="	CONFIG_IPADDR			"\0"
#endif
#ifdef	CONFIG_USE_SERVERIP
	"serverip="	CONFIG_SERVERIP			"\0"
#endif
#ifdef	CONFIG_SYS_DISABLE_AUTOLOAD
	"autoload=0\0"
#endif
#ifdef	CONFIG_PREBOOT_DEFINED
	"preboot="	CONFIG_PREBOOT			"\0"
#endif
#ifdef	CONFIG_USE_ROOTPATH
	"rootpath="	CONFIG_ROOTPATH			"\0"
#endif
#ifdef	CONFIG_USE_GATEWAYIP
	"gatewayip="	CONFIG_GATEWAYIP		"\0"
#endif
#ifdef	CONFIG_USE_NETMASK
	"netmask="	CONFIG_NETMASK			"\0"
#endif
#ifdef	CONFIG_USE_HOSTNAME
	"hostname="	CONFIG_HOSTNAME			"\0"
#endif
#ifdef CONFIG_USE_BOOTFILE
	"bootfile="	CONFIG_BOOTFILE			"\0"
#endif
#ifdef	CONFIG_SYS_LOAD_ADDR
	"loadaddr="	__stringify(CONFIG_SYS_LOAD_ADDR)"\0"
#endif
#ifdef	CONFIG_ENV_VARS_UBOOT_CONFIG
	"arch="		CONFIG_SYS_ARCH			"\0"
#ifdef CONFIG_SYS_CPU
	"cpu="		CONFIG_SYS_CPU			"\0"
#endif
#ifdef CONFIG_SYS_BOARD
	"board="	CONFIG_SYS_BOARD		"\0"
	"board_name="	CONFIG_SYS_BOARD		"\0"
#endif
#ifdef CONFIG_SYS_VENDOR
	"vendor="	CONFIG_SYS_VENDOR		"\0"
#endif
#ifdef CONFIG_SYS_SOC
	"soc="		CONFIG_SYS_SOC			"\0"
#endif
#ifdef CONFIG_USB_HOST
	"usb_ignorelist="
#ifdef CONFIG_USB_KEYBOARD
	/* Ignore Yubico devices. Currently only a single USB keyboard device is
	 * supported and the emulated HID keyboard Yubikeys present is useless
	 * as keyboard.
	 */
	"0x1050:*,"
#endif
	"\0"
#endif
#ifdef CONFIG_ENV_IMPORT_FDT
	"env_fdt_path="	CONFIG_ENV_FDT_PATH		"\0"
#endif
#endif
#if defined(CONFIG_BOOTCOUNT_BOOTLIMIT) && (CONFIG_BOOTCOUNT_BOOTLIMIT > 0)
	"bootlimit="	__stringify(CONFIG_BOOTCOUNT_BOOTLIMIT)"\0"
#endif
#ifdef CONFIG_MTDIDS_DEFAULT
	 "mtdids="	CONFIG_MTDIDS_DEFAULT		"\0"
#endif
#ifdef CONFIG_MTDPARTS_DEFAULT
	"mtdparts="	CONFIG_MTDPARTS_DEFAULT		"\0"
#endif
#ifdef CONFIG_EXTRA_ENV_TEXT
	/* This is created in the Makefile */
	CONFIG_EXTRA_ENV_TEXT
#endif
#ifdef	CFG_EXTRA_ENV_SETTINGS
	CFG_EXTRA_ENV_SETTINGS
#endif
#ifdef CONFIG_OF_SERIAL_BAUD
	/* Padding for baudrate at the end when environment is writable */
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
#endif
	"\0"
#else /* CONFIG_USE_DEFAULT_ENV_FILE */
#include "generated/defaultenv_autogenerated.h"
#endif
#ifdef DEFAULT_ENV_INSTANCE_EMBEDDED
	}
#endif
};

#if !defined(USE_HOSTCC) && !defined(DEFAULT_ENV_INSTANCE_EMBEDDED)
#include <env_internal.h>
static_assert(sizeof(default_environment) <= ENV_SIZE,
	      "Default environment is too large");
#endif
