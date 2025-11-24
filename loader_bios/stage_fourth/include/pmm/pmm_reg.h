#pragma once
#ifndef __PMM_REG_H
#define __PMM_REG_H

#include <typedefs.h>

#pragma pack(push, 1)
typedef struct _pmm_reg_t {
	uint64_t			phys_base;
	uint64_t			num_free_pages;
	uint64_t			num_busy_pages;
	uint64_t			phys_page;				// address
	uint64_t			phys_next_reg;			// address
} pmm_reg_t;
#pragma pack(pop)

#endif