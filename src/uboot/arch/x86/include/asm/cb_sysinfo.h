/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * This file is part of the libpayload project.
 *
 * Copyright (C) 2008 Advanced Micro Devices, Inc.
 */

#ifndef _COREBOOT_SYSINFO_H
#define _COREBOOT_SYSINFO_H

#include <asm/coreboot_tables.h>
#include <linux/types.h>

/* Maximum number of memory range definitions */
#define SYSINFO_MAX_MEM_RANGES	32
/* Allow a maximum of 8 GPIOs */
#define SYSINFO_MAX_GPIOS	8
/* Up to 10 MAC addresses */
#define SYSINFO_MAX_MACS 10
/* Track the first 32 unimplemented tags */
#define SYSINFO_MAX_UNIMPL	32

/**
 * struct sysinfo_t - Information passed to U-Boot from coreboot
 *
 * Coreboot passes on a lot of information using a list of individual data
 * structures identified by a numeric tag. These are parsed in U-Boot to produce
 * this struct. Some of the pointers here point back to the tagged data
 * structure, since it is assumed to remain around while U-Boot is running.
 *
 * The 'cbsysinfo' command can display this information.
 *
 * @cpu_khz: CPU frequence in KHz (e.g. 1100000)
 * @serial: Pointer to the serial information, NULL if none
 * @ser_ioport: Not actually provided by a tag and not used on modern hardware,
 *	which typicaally uses a memory-mapped port
 * @ser_base: Not used at all, but present to match up with the coreboot data
 *	structure
 * @n_memranges: Number of memory ranges
 * @memrange: List of memory ranges:
 *	@base: Base address of range
 *	@size: Size of range in bytes
 *	@type: Type of range (CB_MEM_RAM, etc.)
 * @option_table: Provides a pointer to the CMOS RAM options table, which
 *	indicates which options are available. The header is followed by a list
 *	of struct cb_cmos_entries records, so that an option can be found from
 *	its name. This is not used in U-Boot. NULL if not present
 * @cmos_range_start: Start bit of the CMOS checksum range (in fact this must
 *	be a multiple of 8)
 * @cmos_range_end: End bit of the CMOS checksum range (multiple of 8). This is
 *	the inclusive end.
 * @cmos_checksum_location: Location of checksum, multiplied by 8. This is the
 *	byte offset into the CMOS RAM of the first checksum byte. The second one
 *	follows immediately. The checksum is a simple 16-bit sum of all the
 *	bytes from offset cmos_range_start / 8 to cmos_range_end / 8, inclusive,
 *	in big-endian format (so sum >> 8 is stored in the first byte).
 * @vbnv_start: Start offset of CMOS RAM used for Chromium OS verified boot
 *	(typically 0x34)
 * @vbnv_size: Number of bytes used by Chromium OS verified boot (typically
 *	0x10)
 * @extra_version: Extra version information, typically ""
 * @build: Build date, e.g. "Wed Nov 18 02:51:58 UTC 2020"
 * @compile_time: Compilation time, e.g. "02:51:58"
 * @compile_by: Who compiled coreboot (never set?)
 * @compile_host: Name of the machine that compiled coreboot (never set?)
 * @compile_domain: Domain name of the machine that compiled coreboot (never
 *	set?)
 * @compiler: Name of the compiler used to build coreboot (never set?)
 * @linker: Name of the linker used to build coreboot (never set?)
 * @assembler: Name of the assembler used to build coreboot (never set?)
 * @cb_version: Coreboot version string, e.g. v1.9308_26_0.0.22-2599-g232f22c75d
 * @framebuffer: Address of framebuffer tag, or NULL if none. See
 *	struct cb_framebuffer for the definition
 * @num_gpios: Number of verified-boot GPIOs
 * @gpios: List of GPIOs:
 *	@port: GPIO number, or 0xffffffff if not a GPIO
 *	@polarity: CB_GPIO_ACTIVE_LOW or CB_GPIO_ACTIVE_HIGH
 *	@value: Value of GPIO (0 or 1)
 *	@name: Name of GPIO
 *
 *	A typical list is:
 *	  id: port     polarity val name
 *	   0:    -  active-high   1 write protect
 *	   1:    -  active-high   0 recovery
 *	   2:    -  active-high   1 lid
 *	   3:    -  active-high   0 power
 *	   4:    -  active-high   0 oprom
 *	   5:   29  active-high   0 EC in RW
 *
 * @num_macs: Number of MAC addresses
 * @macs: List of MAC addresses
 * @serialno: Serial number, or NULL (never set?)
 * @mbtable: Address of the multiboot table, or NULL. This is a
 *	struct multiboot_header, not used in U-Boot
 * @header: Address of header, if there is a CB_TAG_FORWARD, else NULL
 * @mainboard: Pointer to mainboard info or NULL. Typically the vendor is
 *	"Google" and the part number is ""
 * @vboot_handoff: Pointer to Chromium OS verified boot hand-off information.
 *	This is struct vboot_handoff, providing access to internal information
 *	generated by coreboot when this is being used
 * @vboot_handoff_size: Size of hand-off information (typically 0xc0c)
 * @vdat_addr: Pointer to Chromium OS verified boot data, which uses
 *	struct chromeos_acpi. It sits in the Intel Global NVS struct, after the
 *	first 0x100 bytes
 * @vdat_size: Size of this data, typically 0xf00
 * @smbios_start: Address of SMBIOS tables
 * @smbios_size: Size of SMBIOS tables (e.g. 0x800)
 * @x86_rom_var_mtrr_index: MTRR number used for ROM caching. Not used in U-Boot
 * @tstamp_table: Pointer to timestamp_table, struct timestamp_table
 * @cbmem_cons: Pointer to the console dump, struct cbmem_console. This provides
 *	access to the console output generated by coreboot, typically about 64KB
 *	and mostly PCI enumeration info
 * @mrc_cache: Pointer to memory-reference-code cache, typically NULL
 * acpi_gnvs: @Pointer to Intel Global NVS struct, see struct acpi_global_nvs
 * @board_id: Board ID indicating the board variant, typically 0xffffffff
 * @ram_code: RAM code indicating the SDRAM type, typically 0xffffffff
 * @wifi_calibration: WiFi calibration info, NULL if none
 * @ramoops_buffer: Address of kernel Ramoops buffer
 * @ramoops_buffer_size: Sizeof of Ramoops buffer, typically 1MB
 * @spi_flash: Information about SPI flash:
 *	@size: Size in bytes, e.g. 16MB
 *	@sector_size; Sector size of flash device, e.g. 4KB
 *	@erase_cmd: Command used to erase flash, or 0 if not used
 * @fmap_offset: SPI-flash offset of the flash map (FMAP) table. This has a
 *	__FMAP__ header. It provides information about the different top-level
 *	sections in the SPI flash, e.g. 0x204000
 * @cbfs_offset: SPI-flash offset of the Coreboot Filesystem (CBFS) used for
 *	read-only data, e.g. 0x205000. This is typically called 'COREBOOT' in
 *	the flash map. It holds various coreboot binaries as well as
 *	video-configuration files and graphics data for the Chromium OS
 *	verified boot user interface.
 * @cbfs_size: Size of CBFS, e.g. 0x17b000
 * @boot_media_size; Size of boot media (i.e. SPI flash), e.g. 16MB
 * @mtc_start; Start of MTC region (Nvidia private data), 0 if not used. See
 *	https://chromium.googlesource.com/chromiumos/third_party/coreboot/+/chromeos-2013.04/src/soc/nvidia/tegra210/mtc.c
 * @mtc_size: Size of MTC region
 * @chromeos_vpd: Chromium OS Vital Product Data region, typically NULL, meaning
 *	not used
 * @rsdp: Pointer to ACPI RSDP table
 * @unimpl_count: Number of entries in unimpl_map[]
 * @unimpl: List of unimplemented IDs (bottom 8 bits only)
 * @table_size: Number of bytes taken up by the sysinfo table
 * @rec_count: Number of records in the sysinfo table
 */
struct sysinfo_t {
	unsigned int cpu_khz;
	struct cb_serial *serial;
	unsigned short ser_ioport;
	unsigned long ser_base; // for mmapped serial

	int n_memranges;

	struct memrange {
		unsigned long long base;
		unsigned long long size;
		unsigned int type;
	} memrange[SYSINFO_MAX_MEM_RANGES];

	struct cb_cmos_option_table *option_table;
	u32 cmos_range_start;
	u32 cmos_range_end;
	u32 cmos_checksum_location;
	u32 vbnv_start;
	u32 vbnv_size;

	char *version;
	char *extra_version;
	char *build;
	char *compile_time;
	char *compile_by;
	char *compile_host;
	char *compile_domain;
	char *compiler;
	char *linker;
	char *assembler;

	char *cb_version;

	struct cb_framebuffer *framebuffer;

	int num_gpios;
	struct cb_gpio gpios[SYSINFO_MAX_GPIOS];
	int num_macs;
	struct mac_address macs[SYSINFO_MAX_MACS];
	char *serialno;

	unsigned long *mbtable; /** Pointer to the multiboot table */

	struct cb_header *header;
	struct cb_mainboard *mainboard;

	void	*vboot_handoff;
	u32	vboot_handoff_size;
	void	*vdat_addr;
	u32	vdat_size;
	u64 smbios_start;
	u32 smbios_size;

	int x86_rom_var_mtrr_index;

	void		*tstamp_table;
	void		*cbmem_cons;
	void		*mrc_cache;
	void		*acpi_gnvs;
	u32		board_id;
	u32		ram_code;
	void		*wifi_calibration;
	u64	ramoops_buffer;
	u32	ramoops_buffer_size;
	struct {
		u32 size;
		u32 sector_size;
		u32 erase_cmd;
	} spi_flash;
	u64 fmap_offset;
	u64 cbfs_offset;
	u64 cbfs_size;
	u64 boot_media_size;
	u64 mtc_start;
	u32 mtc_size;
	void	*chromeos_vpd;
	void *rsdp;
	u32 unimpl_count;
	u8 unimpl[SYSINFO_MAX_UNIMPL];
	uint table_size;
	uint rec_count;
};

extern struct sysinfo_t lib_sysinfo;

/**
 * get_coreboot_info() - parse the coreboot sysinfo table
 *
 * Parses the coreboot table if found, setting the GD_FLG_SKIP_LL_INIT flag if
 * so.
 *
 * @info: Place to put the parsed information
 * Return: 0 if OK, -ENOENT if no table found
 */
int get_coreboot_info(struct sysinfo_t *info);

/**
 * cb_get_sysinfo() - get a pointer to the parsed coreboot sysinfo
 *
 * Return: pointer to sysinfo, or NULL if not available
 */
const struct sysinfo_t *cb_get_sysinfo(void);

#endif
