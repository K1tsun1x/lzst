#include <pmm/pmm.h>

extern spinlock_t __PMM_LOCK;

size_t pmm_free_memory(const void* ptr) {
	if (
		!PMM_FIRST_REGION_BASE_ADDRESS ||
		!ptr ||
		(uintptr_t)ptr & (PMM_PAGE_SIZE - 1)
	) return 0;

	ENTER_CRITICAL_SECTION();

	pmm_reg_t* reg = (pmm_reg_t*)PMM_FIRST_REGION_BASE_ADDRESS;
	while (reg != NULL) {
		pmm_page_t* page_infos = (pmm_page_t*)((uintptr_t)reg + (uintptr_t)reg->page_info_offset);
		uintptr_t pages_start = (uintptr_t)reg + (uintptr_t)reg->page_offset;
		const uintptr_t pages_end = pages_start + PMM_PAGE_SIZE * reg->num_total_pages;
		
		const uintptr_t ptr_offset = (uintptr_t)ptr - pages_start;
		const size_t i_start_ptr = ptr_offset / PMM_PAGE_SIZE;

		if (
			(uintptr_t)ptr < pages_start ||
			(uintptr_t)ptr >= pages_end ||
			i_start_ptr >= reg->num_total_pages ||
			!(page_infos[i_start_ptr].flags & PMM_PAGE_FLAG_BUSY) ||
			!page_infos[i_start_ptr].chain_length
		) {
			reg = (pmm_reg_t*)(uintptr_t)reg->next_reg_address;
			continue;
		}

		const size_t num_pages_to_free = page_infos[i_start_ptr].chain_length;
		for (size_t i = 0; i < num_pages_to_free; i++) {
			page_infos[i_start_ptr + i].flags = 0;
			page_infos[i_start_ptr + i].chain_length = 0;
		}
		
		reg->num_free_pages += num_pages_to_free;
		reg->num_busy_pages -= num_pages_to_free;

		EXIT_CRITICAL_SECTION();
		return num_pages_to_free;
	}

	EXIT_CRITICAL_SECTION();
	return 0;
}