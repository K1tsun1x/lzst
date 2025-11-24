#include <e820/e820.h>

void e820_sort_regions(e820_reg_t* regs, size_t num_regs) {
	// insertion sort
	for (size_t i = 1; i < num_regs; i++) {
		e820_reg_t key = regs[i];

		size_t j = i;
		for (; j > 0 && regs[j - 1].base > key.base; --j) regs[j] = regs[j - 1];
		regs[j] = key;
	}
}