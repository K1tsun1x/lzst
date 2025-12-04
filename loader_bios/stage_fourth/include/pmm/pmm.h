#pragma once
#ifndef __PMM_H
#define __PMM_H

#include <e820/e820.h>
#include <spinlock/spinlock.h>
#include <critical-section/critical-section.h>
#include "pmm_reg.h"
#include "pmm_page.h"

#define PMM_PAGE_SIZE					0x1000
#define PMM_BMP_PAGE_BUSY(bmp, i)		(((uint8_t*)bmp)[(i) >> 3] & (1 << ((i) & 7)))
#define PMM_BMP_MARK_PAGE_BUSY(bmp, i)	(((uint8_t*)bmp)[(i) >> 3] |= (1 << ((i) & 7)))
#define PMM_BMP_MARK_PAGE_FREE(bmp, i)	(((uint8_t*)bmp)[(i) >> 3] &= ~(1 << ((i) & 7)))

size_t pmm_init(
	e820_reg_t* regs,
	size_t num_regs,
	const e820_reg_t* extra_regs,
	size_t num_extra_regs
);

bool pmm_init_region(
	uint64_t base,
	uint64_t length,
	uint64_t next_reg
);

size_t pmm_compute_region_info(
	uint64_t base,
	uint64_t length,
	uint64_t* first_bitmap,
	uint64_t* first_page_info,
	uint64_t* first_page
);

void* pmm_allocate_memory(size_t size, uint64_t flags);
size_t pmm_free_memory(const void* ptr);
bool pmm_find_allocated_memory(void* ptr, pmm_reg_t** reg, size_t* index);
void* pmm_reallocate_memory(void* ptr, size_t new_size, uint64_t new_flags);

extern uintptr_t PMM_FIRST_REGION_BASE_ADDRESS;

#endif