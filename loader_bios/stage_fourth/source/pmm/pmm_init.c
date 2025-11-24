#include <pmm/pmm.h>

size_t pmm_init(
	e820_reg_t* mem_regs,
	const size_t num_mem_regs,
	const e820_reg_t* extra_regs,
	const size_t num_extra_regs
) {
	UNREFERENCED_PARAMETER(mem_regs);
	UNREFERENCED_PARAMETER(num_mem_regs);
	UNREFERENCED_PARAMETER(extra_regs);
	UNREFERENCED_PARAMETER(num_extra_regs);
	
	// FIXME: not implemented yet ...

	return num_mem_regs;
}