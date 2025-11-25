#pragma once
#ifndef __BOOT_INFO_H
#define __BOOT_INFO_H

#include <gfx/gfx_video_mode.h>
#include <e820/e820_reg.h>

typedef struct _boot_info_t {
	uint8_t				boot_drive;

	bool				vga_present;
	bool				vbe_present;
	bool				i8042_present;
	bool				cpuid_present;
	bool				fpu_present;
	
	/**
	 * No SSE:	0x00
	 * SSE:		0x01
	 * SSE2:	0x02
	 * SSE3:	0x03
	 * SSE4.1:	0x41
	 * SSE4.2:	0x42
	 */
	size_t				sse_version;
	bool				avx_present;

	gfx_video_mode_t	video_mode;

	e820_reg_t*			memory_map;
	size_t				memory_map_length;

	uint32_t			acpi_rsdp_address;
	uint64_t			acpi_xsdp_address;
	uint8_t				acpi_rsdp_version;
	uint8_t				acpi_xsdp_version;
	uint32_t			acpi_rsdt_address;
	uint64_t			acpi_xsdt_address;
	uint64_t			acpi_fadt_address;
	uint64_t			acpi_madt_address;
} boot_info_t, *pboot_info_t;

#endif