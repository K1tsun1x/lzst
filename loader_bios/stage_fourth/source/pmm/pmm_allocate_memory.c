#include <pmm/pmm.h>

extern uintptr_t PMM_FIRST_REGION_BASE_ADDRESS;

extern spinlock_t __PMM_LOCK;

void* pmm_allocate_memory(
	size_t size,
	uint64_t flags
) {
	if (!PMM_FIRST_REGION_BASE_ADDRESS || !size) return NULL;

	ENTER_CRITICAL_SECTION();

	flags |= PMM_PAGE_FLAG_BUSY;

	size_t num_needed_pages = ALIGN_UP_P2((uintptr_t)size, PMM_PAGE_SIZE) / PMM_PAGE_SIZE;

	pmm_reg_t* reg = (pmm_reg_t*)PMM_FIRST_REGION_BASE_ADDRESS;
	while (reg != NULL) {
		pmm_page_t* page_infos = (pmm_page_t*)((uintptr_t)reg + (uintptr_t)reg->page_info_offset);
		uintptr_t pages = (uintptr_t)reg + (uintptr_t)reg->page_offset;

		size_t i_start = 0;
		if (reg->num_free_pages >= num_needed_pages) {
			while (i_start < reg->num_total_pages) {
				if (page_infos[i_start].flags & PMM_PAGE_FLAG_BUSY) {
					i_start += 1;
					continue;
				}

				size_t count = 0;
				while (
					i_start + count < reg->num_total_pages &&
					count < num_needed_pages &&
					!(page_infos[i_start + count].flags & PMM_PAGE_FLAG_BUSY)
				) count += 1;

				if (count == num_needed_pages) {
					for (size_t k = 0; k < count; k++) {
						page_infos[i_start + k].flags |= PMM_PAGE_FLAG_BUSY;
						page_infos[i_start + k].chain_length = num_needed_pages;
					}

					reg->num_free_pages -= count;
					reg->num_busy_pages += count;

					EXIT_CRITICAL_SECTION();
					
					void* res = (void*)(pages + PMM_PAGE_SIZE * i_start);
					if (flags & PMM_MEM_FLAG_ZEROED) memset(res, 0, size);
					return res;
				}

				i_start += count + 1;
			}
		}
		
		reg = (pmm_reg_t*)(uintptr_t)reg->next_reg_address;
	}

	EXIT_CRITICAL_SECTION();
	return NULL;
}