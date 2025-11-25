#pragma once
#ifndef __PMM_REG_H
#define __PMM_REG_H

#include <typedefs.h>

#pragma pack(push, 1)
typedef struct _pmm_reg_t {
	uint64_t			base_address;
	uint64_t			length;					// in bytes
	uint64_t			num_free_pages;
	uint64_t			num_busy_pages;
	uint64_t			bitmap_offset;			// offset
	uint64_t			page_info_offset;		// offset
	uint64_t			page_offset;			// offset
	uint64_t			next_reg_address;		// offset
} pmm_reg_t;
#pragma pack(pop)

#endif