#pragma once
#ifndef __VBE_INFO_H
#define __VBE_INFO_H

#include "typedefs.h"

#pragma pack(push, 1)
typedef struct _vbe_info_t {
	char		signature[4];			// VBE_INFO_SIGNATURE
	uint16_t	version;				// 0x0300 for VBE 3.0
	uint16_t	oem_string_ptr[2];		// far ptr
	uint8_t		capabilities[4];
	uint16_t	video_mode_ptr[2];		// far ptr
	uint16_t	total_memory;			// as number of 64KB blocks
	uint8_t		reserved[492];
} vbe_info_t, *pvbe_info_t;
#pragma pack(pop)

#endif