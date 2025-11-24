#include <e820/e820.h>

size_t e820_coalesce_type_regions(
	e820_reg_t* regs,
	size_t num_regs,
	uint32_t reg_type
) {
	for (size_t i = 0; i < num_regs - 1; i++) {
		if (regs[i].type != reg_type) continue;
		
		uint64_t i_start = regs[i].base;
		uint64_t i_end = i_start + regs[i].length;
		uint64_t j_start = regs[i + 1].base;
		const uint64_t j_end = j_start + regs[i + 1].length;

		if (regs[i].type == regs[i + 1].type && i_end >= j_start) {
			uint64_t new_start = i_start < j_start ? i_start : j_start;
			uint64_t new_end = i_end > j_end ? i_end : j_end;

			regs[i].base = new_start;
			regs[i].length = new_end - regs[i].base;

			num_regs -= 1;
			memmove(&regs[i + 1], &regs[i + 2], sizeof(*regs) * (num_regs - i - 1));
			i -= 1;
		}
	}

	return num_regs;
}