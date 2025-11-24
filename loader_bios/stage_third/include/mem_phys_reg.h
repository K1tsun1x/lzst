#pragma once
#ifndef __MEM_PHYS_REG_H
#define __MEM_PHYS_REG_H

#include "mem_phys_reg_type.h"

#pragma pack(push, 1)
typedef struct _boot_mem_reg_t {
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
	boot_mem_reg_type_t	type;
} boot_mem_reg_t;
#pragma pack(pop)

#endif