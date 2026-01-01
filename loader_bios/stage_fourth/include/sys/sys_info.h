#pragma once
#ifndef __SYS_INFO_H
#define __SYS_INFO_H

#include <typedefs.h>
#include <e820/e820.h>
#include <gfx/gfx.h>
#include <acpi/acpi.h>
#include <lapic/lapic.h>
#include <status/status.h>
#include "sys_info_lapic.h"
#include "sys_info_ioapic.h"
#include "sys_info_ioapic_iso.h"

#pragma pack(push, 1)
typedef struct _sys_info_t {
	e820_reg_t*				memory_map;
	size_t					memory_map_length;

	gfx_video_mode_t		video_mode;				

	bool					vga_present;
	bool					vbe_present;
	bool					i8042_present;
	bool					cpuid_present;
	bool					fpu_present;				// 0x34

	/**
	 * No SSE:	0x00
	 * SSE:		0x01
	 * SSE2:	0x02
	 * SSE3:	0x03
	 * SSE4.1:	0x41
	 * SSE4.2:	0x42
	 */
	size_t					sse_version;
	bool					xsave_present;
	bool					osxsave_present;			// 0x3a
	bool					avx_present;
	bool					apic_present;
	bool					msr_present;

	uint32_t				acpi_rsdp_address;
	uint8_t					acpi_rsdp_version;
	uint32_t				acpi_rsdt_address;
	uint32_t				acpi_fadt_address;
	uint32_t				acpi_madt_address;

	/**
	 * @warning dynarr(!)
	 */
	sys_info_lapic_t*		lapics;
	size_t					num_lapics;

	/**
	 * @warning dynarr(!)
	 */
	sys_info_ioapic_t*		ioapics;
	size_t					num_ioapics;

	/**
	 * @warning dynarr(!)
	 */
	sys_info_ioapic_iso_t*	ioapic_isos;
	size_t					num_ioapic_isos;
} sys_info_t;
#pragma pack(pop)

#endif