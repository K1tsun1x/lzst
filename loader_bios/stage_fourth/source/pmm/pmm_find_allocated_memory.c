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
		const uintptr_t reg_base = (uintptr_t)creg->base_address;
		
		uint8_t* bmp = (uint8_t*)((uintptr_t)creg + (uintptr_t)creg->bitmap_offset);
		pmm_page_t* page_info = (pmm_page_t*)((uintptr_t)creg + (uintptr_t)creg->page_info_offset);
		uintptr_t base_pages = (uintptr_t)creg + (uintptr_t)creg->page_offset;
		const uintptr_t end_pages = base_pages + PMM_PAGE_SIZE * creg->num_total_pages;

		const uintptr_t ptr_offset = (uintptr_t)ptr - base_pages;
		const size_t i_start_ptr = ptr_offset / PMM_PAGE_SIZE;

		if (
			(uintptr_t)ptr < base_pages ||
			(uintptr_t)ptr >= end_pages ||
			i_start_ptr >= creg->num_total_pages ||
			!PMM_BMP_PAGE_BUSY(bmp, i_start_ptr) ||
			!page_info[i_start_ptr].chain_length
		) {
			creg = (pmm_reg_t*)(uintptr_t)creg->next_reg_address;
			continue;
		}

		if (reg) *reg = (pmm_reg_t*)reg_base;
		if (index) *index = i_start_ptr;

		EXIT_CRITICAL_SECTION();
		return true;
	}

	EXIT_CRITICAL_SECTION();
	return false;
}