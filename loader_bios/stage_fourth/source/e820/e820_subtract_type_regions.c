#include <e820/e820.h>

size_t e820_subtract_type_regions(
	e820_reg_t* regs,
	size_t num_regs,
	const e820_reg_t* extra_regs,
	size_t num_extra_regs,
	uint32_t reg_type
) {
	for (size_t i = 0; i < num_regs; i++) {
		if (regs[i].type != reg_type) continue;

		for (size_t j = 0; j < num_extra_regs; j++) {
			const uint64_t first_end = regs[i].base + regs[i].length;
			e820_reg_overlap_t reg_overlap = e820_get_reg_overlap(&regs[i], &extra_regs[j]);
			if (reg_overlap == E820_REG_OVERLAP_NONE) continue;

			const uint64_t second_end = extra_regs[j].base + extra_regs[j].length;
			switch (reg_overlap) {
				case E820_REG_OVERLAP_INSIDE:
					for (size_t k = num_regs; k > i; k--) regs[k] = regs[k - 1];
					regs[i + 1].base = extra_regs[j].base + extra_regs[j].length;
					regs[i + 1].length = first_end - second_end;
					regs[i + 1].type = regs[i].type;

					regs[i].length = extra_regs[j].base - regs[i].base;

					num_regs += 1;
					break;
				case E820_REG_OVERLAP_OUTSIDE:
					regs[i].type = E820_REG_TYPE_RESERVED;
					break;
				case E820_REG_OVERLAP_START:
					regs[i].length -= second_end - regs[i].base;
					regs[i].base = second_end;
					break;
				case E820_REG_OVERLAP_END:
					regs[i].length = extra_regs[j].base - regs[i].base;
					break;
				default: break;
			}

			// recheck modified region
			i -= 1;
			break;
		}
	}

	return num_regs;
}