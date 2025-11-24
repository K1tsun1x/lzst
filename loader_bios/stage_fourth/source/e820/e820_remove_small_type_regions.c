#include <e820/e820.h>

size_t e820_remove_small_type_regions(
	e820_reg_t* regs,
	size_t num_regs,
	uint64_t min_reg_size,
	uint32_t reg_type
) {
	for (size_t i = 0; i < num_regs; i++) {
		if (regs[i].type != reg_type) continue;

		if (regs[i].length < min_reg_size) {
			num_regs -= 1;
			if (i < num_regs) memmove(&regs[i], &regs[i + 1], sizeof(*regs) * (num_regs - i));
			i -= 1;
		}
	}

	return num_regs;
}