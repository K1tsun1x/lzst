#pragma once
#ifndef __BOOT_INFO_H
#define __BOOT_INFO_H

#include <gfx/gfx_video_mode.h>
#include <e820/e820_reg.h>
#include "boot_info_lapic.h"
#include "boot_info_ioapic.h"
#include "boot_info_ioapic_int_src_override.h"

#include <status/status.h>
#include <dynarr/dynarr.h>
#include <cpuid486/cpuid486.h>
#include <acpi/acpi.h>
#include <lapic/lapic.h>
#include <fpu/fpu.h>

#pragma pack(push, 1)
typedef struct _boot_info_t {
	uint8_t									boot_drive;
	bool									vga_present;
	bool									vbe_present;
	bool									i8042_present;
	bool									cpuid_present;
	bool									fpu_present;
	/**
	 * No SSE:	0x00
	 * SSE:		0x01
	 * SSE2:	0x02
	 * SSE3:	0x03
	 * SSE4.1:	0x41
	 * SSE4.2:	0x42
	 */
	size_t									sse_version;
	bool									osxsave_present;
	bool									avx_present;
	bool									apic_present;
	bool									msr_present;
	gfx_video_mode_t						video_mode;
	e820_reg_t*								memory_map;
	size_t									memory_map_length;
	uint32_t								acpi_rsdp_address;
	uint8_t									acpi_rsdp_version;
	uint32_t								acpi_rsdt_address;
	uint32_t								acpi_fadt_address;
	uint32_t								acpi_madt_address;

	/**
	 * @warning dynarr(!)
	 */
	boot_info_lapic_t*						lapics;
	size_t									num_lapics;

	/**
	 * @warning dynarr(!)
	 */
	boot_info_ioapic_t*						ioapics;
	size_t									num_ioapics;

	/**
	 * @warning dynarr(!)
	 */
	boot_info_ioapic_int_src_override_t*	ioapic_int_src_overrides;
	size_t									num_ioapic_int_src_overrides;
} boot_info_t;
#pragma pack(pop)

void boot_info_get_features(boot_info_t* boot_info);
status_t boot_info_parse_acpi_tables(boot_info_t* boot_info);

#endif