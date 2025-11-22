#pragma once
#ifndef __E820_ARD_H
#define __E820_ARD_H

#include "e820_ard_type.h"

#pragma pack(push, 1)
typedef struct _e820_ard_t {
	union {
		struct {
			uint32_t	base_low;
			uint32_t	base_high;
		};
		uint64_t		base;
	};
	union {
		struct {
			uint32_t	length_low;
			uint32_t	length_high;
		};
		uint64_t		length;
	};
	uint32_t			type;
	uint32_t			ea;
} e820_ard_t, *pe820_ard_t;
#pragma pack(pop)

#endif