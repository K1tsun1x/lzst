#include <pmm/pmm.h>

uintptr_t PMM_FIRST_REGION_BASE_ADDRESS = 0;

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

	// 7. Init regions
	for (size_t i = 0; i < num_regs; i++) {
		if (regs[i].type != E820_REG_TYPE_NORMAL) continue;

		uint64_t next_reg = 0;
		for (size_t j = i + 1; j < num_regs; j++) {
			if (regs[j].type != E820_REG_TYPE_NORMAL) continue;
			
			next_reg = regs[j].base;
			break;
		}

		if (
			pmm_init_region(regs[i].base, regs[i].length, next_reg)
		) {
			if (
				PMM_FIRST_REGION_BASE_ADDRESS == 0
			) PMM_FIRST_REGION_BASE_ADDRESS = regs[i].base;
		}
		else regs[i].type = E820_REG_TYPE_UNUSABLE;
	}

	return num_regs;
}