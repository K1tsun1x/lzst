#include <pmm/pmm.h>

size_t pmm_compute_region_info(
	uint64_t base,
	uint64_t length,
	uint64_t* first_bitmap,
	uint64_t* first_page_info,
	uint64_t* first_page
) {
	size_t res = length / (PMM_PAGE_SIZE + sizeof(pmm_page_t) + 1);
	while (res > 0) {
		uint64_t first_bmp = ALIGN_UP_P2(base + sizeof(pmm_reg_t), 8);
		size_t bitmap_size = (res + 7) / 8;

		uint64_t pg_info = ALIGN_UP_P2(first_bmp + bitmap_size, 8);
		uint64_t first_pg = ALIGN_UP_P2(pg_info + res * sizeof(pmm_page_t), PMM_PAGE_SIZE);
		uint64_t total_used = first_pg - base + res * PMM_PAGE_SIZE;

		if (total_used <= length) {
			if (first_bitmap) *first_bitmap = first_bmp;
			if (first_page_info) *first_page_info = pg_info;
			if (first_page) *first_page = first_pg;
			break;
		}

		res -= 1;
	}

	return res;
}