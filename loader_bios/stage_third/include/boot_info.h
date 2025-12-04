#pragma once
#ifndef __BOOTLOADER_INFO_H
#define __BOOTLOADER_INFO_H

#include "video_mode.h"
#include "mem_phys_reg.h"

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
	video_mode_t							video_mode;
	boot_mem_reg_t*							memory_map;
	size_t									memory_map_length;
	uint32_t								acpi_rsdp_address;
	uint8_t									acpi_rsdp_version;
	uint32_t								acpi_rsdt_address;
	uint32_t								acpi_fadt_address;
	uint32_t								acpi_madt_address;

	/**
	 * @warning dynarr(!)
	 */
	void*									lapics;
	size_t									num_lapics;

	/**
	 * @warning dynarr(!)
	 */
	void*									ioapics;
	size_t									num_ioapics;

	/**
	 * @warning dynarr(!)
	 */
	void*									ioapic_isos;
	size_t									num_ioapic_isos;
} boot_info_t;
#pragma pack(pop)

#endif