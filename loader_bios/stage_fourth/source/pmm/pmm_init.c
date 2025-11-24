#include <pmm/pmm.h>

size_t pmm_init(
	e820_reg_t* regs,
	size_t num_regs,
	const e820_reg_t* extra_regs,
	size_t num_extra_regs
) {
	// 1. Subtract extra
	num_regs = e820_subtract_type_regions(regs, num_regs, extra_regs, num_extra_regs, E820_REG_TYPE_NORMAL);

	// 2. Substract map
	const e820_reg_t extra_map = {
		(uint64_t)(uintptr_t)regs,
		(uint64_t)(sizeof(e820_reg_t) * (num_regs * 2)),
		E820_REG_TYPE_RESERVED
	};

	num_regs = e820_subtract_type_regions(regs, num_regs, &extra_map, 1, E820_REG_TYPE_NORMAL);

	// 3. Sort
	e820_sort_regions(regs, num_regs);

	// 4. Align
	num_regs = e820_align_type_regions(regs, num_regs, PMM_PAGE_SIZE, E820_REG_TYPE_NORMAL);

	// 5. Remove small
	num_regs = e820_remove_small_type_regions(regs, num_regs, PMM_PAGE_SIZE << 1, E820_REG_TYPE_NORMAL);

	// 6. Merge continuous
	num_regs = e820_coalesce_type_regions(regs, num_regs, E820_REG_TYPE_NORMAL);

	// FIXME: not implemented yet...

	return num_regs;
}