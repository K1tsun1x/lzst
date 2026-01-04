#include <pmm/pmm.h>

bool pmm_init_region(
	uint64_t base,
	uint64_t length,
	uint64_t next_reg
) {
#ifndef X64
	if (base > 0xffffffffULL) return false;

	uint64_t end = base + length;
	if (end > 0x0000000100000000ULL) return false;
#endif

	uint64_t first_page_info;
	uint64_t first_page;
	size_t num_pages = pmm_compute_region_info(
		base,
		length,
		&first_page_info,
		&first_page
	);

	// Init region
	pmm_reg_t* reg = (pmm_reg_t*)((uintptr_t)base);
	reg->base_address = base;
	reg->length = length;
	reg->num_free_pages = num_pages;
	reg->num_busy_pages = 0;
	reg->num_total_pages = num_pages;
	reg->page_info_offset = first_page_info - base;
	reg->page_offset = first_page - base;
	reg->next_reg_address = next_reg;

	// Init page infos
	pmm_page_t* page_infos = (pmm_page_t*)(uintptr_t)first_page_info;
	for (size_t i = 0; i < reg->num_free_pages; i++) {
		page_infos[i].flags = 0;
		page_infos[i].chain_length = 0;
	}

	return true;
}