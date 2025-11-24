#pragma once
#ifndef __PMM_REG_H
#define __PMM_REG_H

#include <typedefs.h>

#pragma pack(push, 1)
typedef struct _pmm_reg32_t {
	uint32_t			num_free_pages;
	uint32_t			num_busy_pages;
	uint32_t			page_infos;			// address
	uint32_t			next_reg_info;		// address
} pmm_reg32_t;
#pragma pack(pop)

#endif