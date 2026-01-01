#pragma once
#ifndef __SYS_H
#define __SYS_H

#include <string.h>
#include <cpuid486/cpuid486.h>
#include <fpu/fpu.h>
#include "sys_info.h"

void sys_init(
	gfx_video_mode_t* video_mode,
	bool vga_present,
	bool vbe_present,
	bool i8042_present
);

status_t sys_parse_acpi_tables(sys_info_t* sys_info);

void sys_get_info(sys_info_t* buffer);
void sys_set_info(const sys_info_t* buffer);

XTRN_C bool LOADERCALL sys_osxsave_present(void);
XTRN_C bool LOADERCALL sys_fpu_present(void);

static inline void sys_set_mem_info(
	sys_info_t* buffer,
	e820_reg_t* memory_map,
	size_t memory_map_length
) {
	buffer->memory_map = memory_map;
	buffer->memory_map_length = memory_map_length;
	sys_set_info(buffer);
}

#endif