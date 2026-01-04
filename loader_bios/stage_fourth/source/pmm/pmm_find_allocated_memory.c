#include <pmm/pmm.h>

extern spinlock_t __PMM_LOCK;

bool pmm_find_allocated_memory(void* ptr, pmm_reg_t** reg, size_t* index) {
	if (
		!PMM_FIRST_REGION_BASE_ADDRESS ||
		!ptr ||
		(uintptr_t)ptr & (PMM_PAGE_SIZE - 1)
	) return false;
	
	ENTER_CRITICAL_SECTION();

	pmm_reg_t* creg = (pmm_reg_t*)PMM_FIRST_REGION_BASE_ADDRESS;
	while (creg != NULL) {
		pmm_page_t* page_infos = (pmm_page_t*)((uintptr_t)creg + (uintptr_t)creg->page_info_offset);
		uintptr_t pages_start = (uintptr_t)creg + (uintptr_t)creg->page_offset;
		const uintptr_t pages_end = pages_start + PMM_PAGE_SIZE * creg->num_total_pages;
		
		const uintptr_t ptr_offset = (uintptr_t)ptr - pages_start;
		const size_t i_start_ptr = ptr_offset / PMM_PAGE_SIZE;

		if (
			(uintptr_t)ptr < pages_start ||
			(uintptr_t)ptr >= pages_end ||
			i_start_ptr >= creg->num_total_pages ||
			!(page_infos[i_start_ptr].flags & PMM_PAGE_FLAG_BUSY) ||
			!page_infos[i_start_ptr].chain_length
		) {
			creg = (pmm_reg_t*)(uintptr_t)creg->next_reg_address;
			continue;
		}

		if (reg) *reg = creg;
		if (index) *index = i_start_ptr;

		EXIT_CRITICAL_SECTION();
		return true;
	}

	EXIT_CRITICAL_SECTION();
	return false;
}