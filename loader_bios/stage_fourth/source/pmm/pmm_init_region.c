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

	uint64_t first_bitmap;
	uint64_t first_page_info;
	uint64_t first_page;
	size_t num_pages = pmm_compute_region_info(
		base,
		length,
		&first_bitmap,
		&first_page_info,
		&first_page
	);

	// Init region
	pmm_reg_t* pmm_reg = (pmm_reg_t*)((uintptr_t)base);
	pmm_reg->base_address = base;
	pmm_reg->length = length;
	pmm_reg->num_free_pages = num_pages;
	pmm_reg->num_busy_pages = 0;
	pmm_reg->bitmap_offset = first_bitmap - base;
	pmm_reg->page_info_offset = first_page_info - base;
	pmm_reg->page_offset = first_page - base;
	pmm_reg->next_reg_address = next_reg;

	// Init bitmap
	uint8_t* pmm_reg_bitmap = (uint8_t*)(uintptr_t)first_bitmap;
	const size_t bitmap_size = (pmm_reg->num_free_pages + 7) / 8;
	for (size_t i = 0; i < bitmap_size; i++) pmm_reg_bitmap[i] = 0;

	// Init page infos
	pmm_page_t* pmm_page_infos = (pmm_page_t*)(uintptr_t)first_page_info;
	for (size_t i = 0; i < pmm_reg->num_free_pages; i++) {
		pmm_page_infos[i].flags = 0;
		pmm_page_infos[i].chain_length = 0;
	}

	return true;
}