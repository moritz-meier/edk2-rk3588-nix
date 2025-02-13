/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2016 Rockchip Electronics Co., Ltd
 */

#ifndef __ROCKPI4_RK3399_H
#define __ROCKPI4_RK3399_H

#define ROCKPI_4B_IDBLOADER_IMAGE_GUID \
	EFI_GUID(0x02f4d760, 0xcfd5, 0x43bd, 0x8e, 0x2d, \
		 0xa4, 0x2a, 0xcb, 0x33, 0xc6, 0x60)

#define ROCKPI_4B_UBOOT_IMAGE_GUID \
	EFI_GUID(0x4ce292da, 0x1dd8, 0x428d, 0xa1, 0xc2, \
		 0x77, 0x74, 0x3e, 0xf8, 0xb9, 0x6e)

#define ROCKPI_4C_IDBLOADER_IMAGE_GUID \
	EFI_GUID(0xfd68510c, 0x12d3, 0x4f0a, 0xb8, 0xd3, \
		 0xd8, 0x79, 0xe1, 0xd3, 0xa5, 0x40)

#define ROCKPI_4C_UBOOT_IMAGE_GUID \
	EFI_GUID(0xb81fb4ae, 0xe4f3, 0x471b, 0x99, 0xb4, \
		 0x0b, 0x3d, 0xa5, 0x49, 0xce, 0x13)

#define ROCKCHIP_DEVICE_SETTINGS \
		"stdin=serial,usbkbd\0" \
		"stdout=serial,vidconsole\0" \
		"stderr=serial,vidconsole\0"

#include <configs/rk3399_common.h>

#endif
