#pragma once
#ifndef __MEM_PHYS_REG_H
#define __MEM_PHYS_REG_H

#include "mem_phys_reg_type.h"

#pragma pack(push, 1)
typedef struct _mem_phys_reg_t {
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
	mem_phys_reg_type_t	type;
} mem_phys_reg_t, *pmem_phys_reg_t;
#pragma pack(pop)

#endif