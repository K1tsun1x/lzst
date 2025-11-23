#pragma once
#ifndef __BOOTLOADER_INFO_H
#define __BOOTLOADER_INFO_H

#include "mem_phys_reg.h"
#include "video_mode.h"

typedef struct _bootloader_info_t {
	uint8_t				boot_drive;

	bool				vga_present;
	bool				vbe_present;
	bool				i8042_present;
	bool				cpuid_present;
	bool				fpu_present;
	
	/**
	 * No SSE:	0
	 * SSE:		0x01
	 * SSE2:	0x02
	 * SSE3:	0x03
	 * SSE4.1:	0x41
	 * SSE4.2:	0x42
	 */
	size_t				sse_version;
	bool				avx_present;

	video_mode_t		video_mode;

	mem_phys_reg_t*		memory_map;
	size_t				memory_map_length;
} bootloader_info_t, *pbootloader_info_t;

#endif