#pragma once
#ifndef __E820_REG_H
#define __E820_REG_H

#include "e820_reg_type.h"

#pragma pack(push, 1)
typedef struct _e820_reg_t {
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

	e820_reg_type_t		type;
} e820_reg_t;
#pragma pack(pop)

#endif