#include <pmm/pmm.h>

void* pmm_reallocate_memory(void* ptr, size_t new_size, uint64_t new_flags) {
	if (!ptr) return pmm_allocate_memory(new_size, new_flags);
	if (!new_size) {
		pmm_free_memory(ptr);
		return NULL;
	}

	size_t index;
	pmm_reg_t* reg;
	if (!pmm_find_allocated_memory(ptr, &reg, &index)) return NULL;

	const size_t num_needed_pages = ALIGN_UP_P2(new_size, PMM_PAGE_SIZE) / PMM_PAGE_SIZE;
	const pmm_page_t* pages = (pmm_page_t*)((uintptr_t)reg + (uintptr_t)reg->page_info_offset);

	void* new_ptr = pmm_allocate_memory(new_size, new_flags);
	if (!new_ptr) return NULL;

	const size_t num_copy_pages = num_needed_pages > pages[index].chain_length ? pages[index].chain_length : num_needed_pages;
	if (num_copy_pages > 0) memcpy(new_ptr, ptr, num_copy_pages * PMM_PAGE_SIZE);
	pmm_free_memory(ptr);

	return new_ptr;
}