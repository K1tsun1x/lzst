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
		uint8_t* bmp = (uint8_t*)((uintptr_t)reg + (uintptr_t)reg->bitmap_offset);
		pmm_page_t* page_info = (pmm_page_t*)((uintptr_t)reg + (uintptr_t)reg->page_info_offset);
		uintptr_t base_pages = (uintptr_t)reg + (uintptr_t)reg->page_offset;

		size_t i_start = 0;
		if (reg->num_free_pages >= num_needed_pages) {
			while (i_start < reg->num_total_pages) {
				if (PMM_BMP_PAGE_BUSY(bmp, i_start)) {
					i_start += 1;
					continue;
				}

				size_t count = 0;
				while (
					i_start + count < reg->num_total_pages &&
					count < num_needed_pages &&
					!PMM_BMP_PAGE_BUSY(bmp, i_start + count)
				) count += 1;

				if (count == num_needed_pages) {
					for (size_t k = 0; k < count; k++) {
						PMM_BMP_MARK_PAGE_BUSY(bmp, i_start + k);
						page_info[i_start + k].flags = flags;
						page_info[i_start + k].chain_length = num_needed_pages;
					}

					reg->num_free_pages -= count;
					reg->num_busy_pages += count;

					EXIT_CRITICAL_SECTION();
					
					void* res = (void*)(base_pages + PMM_PAGE_SIZE * i_start);
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