#include <e820/e820.h>

size_t e820_align_type_regions(e820_reg_t* regs, size_t num_regs, uint64_t alignment, uint32_t reg_type) {
	for (size_t i = 0; i < num_regs; i++) {
		if (regs[i].type != reg_type) continue;
		
		const uint64_t old_base = regs[i].base;
		uint64_t old_end = old_base + regs[i].length;
		if (old_end < old_base) old_end = UINT64_MAX;

		const uint64_t start = ALIGN_UP_P2(old_base, alignment);
		const uint64_t end = ALIGN_DOWN_P2(old_end, alignment);
		if (start >= end) {
			num_regs -= 1;
			if (i < num_regs) memmove(&regs[i], &regs[i + 1], sizeof(*regs) * (num_regs - i));
			i -= 1;
		}
		else {
			regs[i].base = start;
			regs[i].length = end - regs[i].base;
		}
	}

	return num_regs;
}