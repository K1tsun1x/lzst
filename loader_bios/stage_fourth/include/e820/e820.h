#pragma once
#ifndef __E820_H
#define __E820_H

#include <align.h>
#include <string.h>
#include "e820_reg.h"
#include "e820_reg_overlap.h"

void e820_sort_regions(e820_reg_t* regs, size_t num_regs);
size_t e820_align_type_regions(e820_reg_t* regs, size_t num_regs, uint64_t alignment, uint32_t reg_type);

size_t e820_remove_small_type_regions(
	e820_reg_t* regs,
	size_t num_regs,
	uint64_t min_reg_size,
	uint32_t reg_type
);

size_t e820_coalesce_type_regions(
	e820_reg_t* regs,
	size_t num_regs,
	uint32_t reg_type
);

size_t e820_subtract_type_regions(
	e820_reg_t* regs,
	size_t num_regs,
	const e820_reg_t* extra_regs,
	size_t num_extra_regs,
	uint32_t reg_type
);

#endif