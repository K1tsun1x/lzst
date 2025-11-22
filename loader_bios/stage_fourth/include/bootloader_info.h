#pragma once
#ifndef __BOOTLOADER_INFO_H
#define __BOOTLOADER_INFO_H

#include "video_mode.h"

typedef struct _bootloader_info_t {
	uint8_t				boot_drive;

	bool				vga_present;
	bool				vbe_present;
	bool				i8042_present;
	bool				cpuid_present;
	bool				fpu_present;

	/**
	 * No SSE: 0
	 * SSE: 1
	 * SSE2: 2
	 */
	size_t				sse_version;

	video_mode_t		video_mode;
} bootloader_info_t, *pbootloader_info_t;

#endif