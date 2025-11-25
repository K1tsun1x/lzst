#include <pmm/pmm.h>

extern spinlock_t __PMM_LOCK;

bool pmm_free_memory(const void* ptr) {
	if (
		!PMM_FIRST_REGION_BASE_ADDRESS ||
		!ptr ||
		(uintptr_t)ptr & (PMM_PAGE_SIZE - 1)
	) return false;

	irq_flags_t irq_flags = irq_disable();
	spinlock_acquire(&__PMM_LOCK);

	pmm_reg_t* reg = (pmm_reg_t*)PMM_FIRST_REGION_BASE_ADDRESS;
	while (reg != NULL) {
		uint8_t* bmp = (uint8_t*)((uintptr_t)reg + (uintptr_t)reg->bitmap_offset);
		pmm_page_t* page_info = (pmm_page_t*)((uintptr_t)reg + (uintptr_t)reg->page_info_offset);
		uintptr_t base_pages = (uintptr_t)reg + (uintptr_t)reg->page_offset;
		const uintptr_t end_pages = base_pages + PMM_PAGE_SIZE * reg->num_total_pages;

		const uintptr_t ptr_offset = (uintptr_t)ptr - base_pages;
		const size_t i_start_ptr = ptr_offset / PMM_PAGE_SIZE;

		if (
			(uintptr_t)ptr < base_pages ||
			(uintptr_t)ptr >= end_pages ||
			i_start_ptr >= reg->num_total_pages ||
			!PMM_BMP_PAGE_BUSY(bmp, i_start_ptr) ||
			!page_info[i_start_ptr].chain_length
		) {
			reg = (pmm_reg_t*)(uintptr_t)reg->next_reg_address;
			continue;
		}

		const size_t num_pages_to_free = page_info[i_start_ptr].chain_length;
		for (size_t i = 0; i < num_pages_to_free; i++) {
			PMM_BMP_MARK_PAGE_FREE(bmp, i_start_ptr + i);
			page_info[i_start_ptr + i].flags = 0;
			page_info[i_start_ptr + i].chain_length = 0;
		}
		
		reg->num_free_pages += num_pages_to_free;
		reg->num_busy_pages -= num_pages_to_free;

		spinlock_release(&__PMM_LOCK);
		irq_restore(irq_flags);
		return true;
	}

	spinlock_release(&__PMM_LOCK);
	irq_restore(irq_flags);
	return false;
}